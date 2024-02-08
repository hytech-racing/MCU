/* Include files */
/* System Includes*/
#include <Arduino.h>

/* Libraries */
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "MCU_rev15_defs.h"

/* Interfaces */
#include "HytechCANInterface.h"
#include "MCP_ADC.h"
#include "ORBIS_BR10.h"
#include "MCUInterface.h"
#include "AMSInterface.h"
#include "WatchdogInterface.h"
#include "DashboardInterface.h"
#include "InverterInterface.h"
#include "TelemetryInterface.h"

/* Systems */
#include "SysClock.h"
#include "Buzzer.h"
#include "SafetySystem.h"
#include "DrivetrainSystem.h"
#include "PedalsSystem.h"
#include "TorqueControllerMux.h"

/* State machine */
#include "MCUStateMachine.h"


/* External info sources */
/* Two CAN lines on Main ECU rev15 */
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> INV_CAN; // Inverter CAN (now both are on same line)
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN; // telemetry CAN (basically everything except inverters)

/* Set up CAN circular buffer */
using CircularBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
/* Sensors */
MCP_ADC<8> ADC1(ADC1_CS);
MCP_ADC<4> ADC2(ADC2_CS);
MCP_ADC<4> ADC3(ADC3_CS);
OrbisBR10 steering1(STEERING_SERIAL);

/* Declare interfaces */
DashboardInterface dashboard(&CAN2_txBuffer);
AMSInterface ams_interface(SOFTWARE_OK);
WatchdogInterface wd_interface(WATCHDOG_INPUT);
MCUInterface main_ecu(&CAN3_txBuffer);
TelemetryInterface telem_interface(&CAN3_txBuffer);

using InverterInterfaceType = InverterInterface<CircularBufferType>;
InverterInterfaceType fl_inv(&CAN2_txBuffer, ID_MC1_SETPOINTS_COMMAND, 9, 8);
InverterInterfaceType fr_inv(&CAN2_txBuffer, ID_MC2_SETPOINTS_COMMAND, 9, 8);
InverterInterfaceType rl_inv(&CAN2_txBuffer, ID_MC3_SETPOINTS_COMMAND, 9, 8);
InverterInterfaceType rr_inv(&CAN2_txBuffer, ID_MC4_SETPOINTS_COMMAND, 9, 8);


/* Declare systems */
SysClock sys_clock;
BuzzerController buzzer(BUZZER_ON_INTERVAL);
SafetySystem safety_system(&ams_interface, &wd_interface);  // Tie ams and wd interface to safety system (by pointers)
PedalsSystem pedals_system({100, 100, 3000, 3000, 0.1}, {100, 100, 3000, 3000, 0.05});
SteeringSystem steering_system(&steering1);  // Unify member reference and pointers? tied by reference in this case
using DrivetrainSystemType = DrivetrainSystem<InverterInterfaceType>;
auto drivetrain = DrivetrainSystemType({&fl_inv, &fr_inv, &rl_inv, &rr_inv}, INVERTER_ENABLING_TIMEOUT_INTERVAL); // Tie inverter interfaces to drivetrain system (by pointers)
/*
    Hypothetical controllers, need more implementation details
        TorqueControllerSimple simple_mode;
        TorqueControllerSimple normal_force_mode;
        TorqueControllerSimple endurance_derating_mode;
        TorqueControllerSimple launch_control_mode;
        TorqueControllerSimple torque_vectoring_mode;
*/
TorqueControllerMux torque_controller_mux;


/* Declare state machine */
MCUStateMachine<DrivetrainSystemType> fsm(&buzzer, &drivetrain, &dashboard, &pedals_system, &torque_controller_mux, &ams_interface);    // need more implemetation details. associated interfaces and systems tied by pointers

CANInterfaces<CircularBufferType> CAN_interfaces = {&fl_inv, &fr_inv, &rl_inv, &rr_inv, &dashboard, &ams_interface};

/* tick interfaces */
void tick_all_interfaces(const SysTick_s& current_system_tick);
/* Tick all systems */
void tick_all_systems(const SysTick_s& current_system_tick);

void init_all_CAN_devices() {
    // Inverter CAN line
    INV_CAN.begin();
    INV_CAN.setBaudRate(INV_CAN_BAUDRATE);
    INV_CAN.setMaxMB(16);
    INV_CAN.enableFIFO();
    INV_CAN.enableFIFOInterrupt();
    INV_CAN.onReceive(on_can2_receive);
    INV_CAN.mailboxStatus();

    // Telemetry CAN line
    TELEM_CAN.begin();
    TELEM_CAN.setBaudRate(TELEM_CAN_BAUDRATE);
    TELEM_CAN.setMaxMB(16);
    TELEM_CAN.enableFIFO();
    TELEM_CAN.enableFIFOInterrupt();
    TELEM_CAN.onReceive(on_can3_receive);
    TELEM_CAN.mailboxStatus();
}

void setup() {
    init_all_CAN_devices();
    /* Tick system clock */
    auto curr_tick = sys_clock.tick(micros());

    /* Initialize interface */
    main_ecu.init();    // initial shutdown circuit readings, 
    wd_interface.init(curr_tick);   // initialize wd kick time
    ams_interface.init(curr_tick);  // initialize last heartbeat time

    /* Initialize system */
    safety_system.init();   // write software_ok high, write wd_input high, set software ok state true
    // ControllerMux set initial max torque to 10 NM, torque mode to 0 (could be done at construction or have an init function)
    // Drivetrain set all inverters disabled, write inv_en and inv_24V_en hight, set inverter_has_error to false if using

    // delay for 1 second
    delay(1000);
    // ControllerMux set max torque to 21 NM, torque mode to whatever makes most sense

}

void loop() {

    auto cur_tick = sys_clock.tick(micros());
    process_ring_buffer(CAN2_rxBuffer, CAN_interfaces, cur_tick.millis);
    process_ring_buffer(CAN3_rxBuffer, CAN_interfaces, cur_tick.millis);
    // tick interfaces
    tick_all_interfaces(cur_tick);
    /* System process readings prior to ticking state machine */
    tick_all_systems(cur_tick);
    fsm.tick_state_machine(cur_tick.millis);
    /* Update and enqueue CAN messages */

    /* Inverter procedure before entering state machine */
    // Drivetrain check if inverters have error
    // Drivetrain reset inverters

    /* Tick safety system */
    safety_system.software_shutdown(cur_tick);
}

void tick_all_interfaces(const SysTick_s& current_system_tick) {
    // Tick all adcs
    ADC1.tick(current_system_tick);
    ADC2.tick(current_system_tick);
    ADC3.tick(current_system_tick);
    // Tick steering system
    steering_system.tick(current_system_tick, ADC1.get().conversions[MCU15_STEERING_CHANNEL]);
    // Read shutdown circuits    
    main_ecu.read_mcu_status();
    telem_interface.tick(current_system_tick,
                         ADC1.get(),
                         ADC2.get(),    // Add MCP3204 functionality for corner board
                         ADC3.get(),    // Add implementation to get()
                         steering1.convert());
}

void tick_all_systems(const SysTick_s& current_system_tick) {
    pedals_system.tick(
        current_system_tick,
        ADC1.get().conversions[MCU15_ACCEL1_CHANNEL],
        ADC1.get().conversions[MCU15_ACCEL2_CHANNEL],
        ADC1.get().conversions[MCU15_BRAKE1_CHANNEL],
        ADC1.get().conversions[MCU15_BRAKE2_CHANNEL]
    );
    steering_system.tick(
        current_system_tick,
        ADC1.get().conversions[MCU15_STEERING_CHANNEL]
    );
    drivetrain.tick(current_system_tick);
    torque_controller_mux.tick(
        current_system_tick,
        drivetrain.get_current_data(),
        pedals_system.getPedalsSystemData(),
        steering_system.getSteeringSystemData(),
        ADC2.get().conversions[0],                  // FL load cell reading. TODO: fix index
        ADC3.get().conversions[0],                  // FR load cell reading. TODO: fix index
        (const AnalogConversion_s) {},              // RL load cell reading. TODO: get data from rear load cells
        (const AnalogConversion_s) {},              // RR load cell reading. TODO: get data from rear load cells
        dashboard.getDialMode(),
        dashboard.torqueButtonPressed()
    );
    
}

