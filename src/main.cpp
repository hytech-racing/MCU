/* Include files */
/* System Includes*/
#include <Arduino.h>

/* Libraries */
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "MCU_rev15_defs.h"

// /* Interfaces */
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

/*
    DATA SOURCES
*/

/* Two CAN lines on Main ECU rev15 */
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> INV_CAN;   // Inverter CAN (now both are on same line)
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN; // telemetry CAN (basically everything except inverters)

/* Set up CAN circular buffer */
using CircularBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;

/* Sensors */
struct ADCs {
    MCP_ADC<8> a1 = MCP_ADC<8>(ADC1_CS);
    MCP_ADC<4> a2 = MCP_ADC<4>(ADC2_CS);
    MCP_ADC<4> a3 = MCP_ADC<4>(ADC3_CS);
} ADC;

OrbisBR10 steering1(STEERING_SERIAL);

/*
    INTERFACES
*/

DashboardInterface dashboard(&CAN2_txBuffer);
AMSInterface ams_interface(SOFTWARE_OK);
WatchdogInterface wd_interface(WATCHDOG_INPUT);
MCUInterface main_ecu(&CAN3_txBuffer);
TelemetryInterface telem_interface(&CAN3_txBuffer);

/* Inverter Interface Type */
using InvInt_t = InverterInterface<CircularBufferType>;
struct inverters {
    InvInt_t fl = InvInt_t(&CAN2_txBuffer, ID_MC1_SETPOINTS_COMMAND);
    InvInt_t fr = InvInt_t(&CAN2_txBuffer, ID_MC2_SETPOINTS_COMMAND);
    InvInt_t rl = InvInt_t(&CAN2_txBuffer, ID_MC3_SETPOINTS_COMMAND);
    InvInt_t rr = InvInt_t(&CAN2_txBuffer, ID_MC4_SETPOINTS_COMMAND);
} inv;

/*
    SYSTEMS
*/

SysClock sys_clock;
SteeringSystem steering_system(&steering1); // Unify member reference and pointers? tied by reference in this case
BuzzerController buzzer(BUZZER_ON_INTERVAL);
SafetySystem safety_system(&ams_interface, &wd_interface); // Tie ams and wd interface to safety system (by pointers)
PedalsSystem pedals_system({100, 100, 3000, 3000, 0.1}, {100, 100, 3000, 3000, 0.05});
using DriveSys_t = DrivetrainSystem<InvInt_t>;
DriveSys_t drivetrain = DriveSys_t({&inv.fl, &inv.fr, &inv.rl, &inv.rr}, &main_ecu, INVERTER_ENABLING_TIMEOUT_INTERVAL); // Tie inverter interfaces to drivetrain system (by pointers)
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
MCUStateMachine<DriveSys_t> fsm(&buzzer, &drivetrain, &dashboard, &pedals_system, &torque_controller_mux, &safety_system); // need more implemetation details. associated interfaces and systems tied by pointers

/*
    GROUPING STRUCTS (To limit parameter count in utilizing functions)
*/

CANInterfaces<CircularBufferType> CAN_receive_interfaces = {&inv.fl, &inv.fr, &inv.rl, &inv.rr, &dashboard, &ams_interface};

/*
    FUNCTION DEFINITIONS
*/

/* tick interfaces */
void tick_all_interfaces(const SysTick_s &current_system_tick);
/* Tick all systems */
void tick_all_systems(const SysTick_s &current_system_tick);

void init_all_CAN_devices()
{
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

/*
    SETUP
*/

void setup()
{   
    init_all_CAN_devices();

    SysTick_s curr_tick = sys_clock.tick(micros()); // get latest tick from sys clock

    /*
        Init Interfaces
    */

    main_ecu.init();                      // initial shutdown circuit readings,
    wd_interface.init(curr_tick.millis);  // initialize wd kick time
    ams_interface.init(curr_tick.millis); // initialize last heartbeat time

    /*
        Init Systems
    */
   
    safety_system.init();

    // delay for 1 second
    delay(1000);

    // ControllerMux set initial max torque to 10 NM, torque mode to 0 (could be done at construction or have an init function)
    // Drivetrain set all inverters disabled, write inv_en and inv_24V_en hight, set inverter_has_error to false if using
    // ControllerMux set max torque to 21 NM, torque mode to whatever makes most sense
}


void loop()
{

    SysTick_s curr_tick = sys_clock.tick(micros()); // get latest tick from sys clock

    // process received can messages
    process_ring_buffer(CAN2_rxBuffer, CAN_receive_interfaces, curr_tick.millis);
    process_ring_buffer(CAN3_rxBuffer, CAN_receive_interfaces, curr_tick.millis);

    // tick interfaces
    tick_all_interfaces(curr_tick);

    // tick systems
    tick_all_systems(curr_tick);

    //tick state machine
    fsm.tick_state_machine(curr_tick.millis);
    
    // tick safety system
    safety_system.software_shutdown(curr_tick);

    /* Update and enqueue CAN messages */
    /* Inverter procedure before entering state machine */
    send_all_CAN_msgs(CAN2_txBuffer, &INV_CAN);
    send_all_CAN_msgs(CAN3_txBuffer, &TELEM_CAN);
}

/*
    TICK INTERFACES
*/

void tick_all_interfaces(const SysTick_s &current_system_tick)
{

    TriggerBits_s t = current_system_tick.triggers;

    if (t.trigger10) // 10Hz
    {



    }
    else if (t.trigger50) // 50Hz
    {

        telem_interface.tick(ADC.a1.get(), ADC.a2.get(), ADC.a3.get(), steering1.convert());

    }
    else if (t.trigger100) // 100Hz
    {
        ADC.a1.tick();
        ADC.a2.tick();
        ADC.a3.tick();
    }

    // Untriggered

    main_ecu.tick(static_cast<int>(fsm.get_state()),
                  drivetrain.drivetrain_error_occured(),
                  safety_system.get_software_is_ok(),
                  buzzer.buzzer_is_on(),
                  ams_interface.pack_charge_is_critical(),
                  dashboard.launchControlButtonPressed());
}

/*
    TICK SYSTEMS
*/

void tick_all_systems(const SysTick_s &current_system_tick)
{

    // tick pedals system
    pedals_system.tick(
        current_system_tick,
        ADC.a1.get().conversions[MCU15_ACCEL1_CHANNEL],
        ADC.a1.get().conversions[MCU15_ACCEL2_CHANNEL],
        ADC.a1.get().conversions[MCU15_BRAKE1_CHANNEL],
        ADC.a1.get().conversions[MCU15_BRAKE2_CHANNEL]);

    // tick steering system
    steering_system.tick(
        current_system_tick,
        ADC.a1.get().conversions[MCU15_STEERING_CHANNEL]);

    // tick drivetrain system
    drivetrain.tick(current_system_tick);

    // tick torque controller mux
    torque_controller_mux.tick(
        current_system_tick,
        drivetrain.get_current_data(),
        pedals_system.getPedalsSystemData(),
        steering_system.getSteeringSystemData(),
        ADC.a2.get().conversions[0],    // FL load cell reading. TODO: fix index
        ADC.a3.get().conversions[0],    // FR load cell reading. TODO: fix index
        (const AnalogConversion_s){}, // RL load cell reading. TODO: get data from rear load cells
        (const AnalogConversion_s){}, // RR load cell reading. TODO: get data from rear load cells
        dashboard.getDialMode(),
        dashboard.torqueButtonPressed());
}
