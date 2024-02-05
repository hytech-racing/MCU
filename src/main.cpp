// /* Prototype main function for logic soothing */

// /* Include files */
#include <Arduino.h>
#include "MCUStateMachine.h"
#include "InverterInterface.h"
#include "ADC_SPI.h"
// #include "MessageHandler.h"
#include "DrivetrainSystem.h"
#include "PedalsSystem.h"

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "MCU_rev15_defs.h"

/* Interfaces */
#include "HytechCANInterface.h"
#include "MCP3208.h"
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
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> INV_CAN;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;
/* Set up CAN circular buffer */
using CircularBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
/* Sensors */
MCP3208 ADC1(ADC1_CS);
MCP3208 ADC2(ADC2_CS);
MCP3208 ADC3(ADC3_CS);
OrbisBR10 steering1(STEERING_SERIAL);

/* Declare interfaces */
DashboardInterface dashboard;
AMSInterface ams_interface(SOFTWARE_OK);
WatchdogInterface wd_interface(WATCHDOG_INPUT);
MCUInterface<CircularBufferType> main_ecu(&CAN3_txBuffer);
TelemetryInterface<CircularBufferType> telem_interface(&CAN3_txBuffer);
using InverterInterfaceType = InverterInterface<CircularBufferType>;
InverterInterfaceType fl_inv(&CAN2_txBuffer, ID_MC1_SETPOINTS_COMMAND);
InverterInterfaceType fr_inv(&CAN2_txBuffer, ID_MC2_SETPOINTS_COMMAND);
InverterInterfaceType rl_inv(&CAN2_txBuffer, ID_MC3_SETPOINTS_COMMAND);
InverterInterfaceType rr_inv(&CAN2_txBuffer, ID_MC4_SETPOINTS_COMMAND);
/* Declare systems */
SysClock sys_clock;
BuzzerController buzzer(BUZZER_ON_INTERVAL);
SafetySystem safety_system(&ams_interface, &wd_interface);  // Tie ams and wd interface to safety system (by pointers)
PedalsSystem pedals;
SteeringSystem steering_system(steering1);  // Unify member reference and pointers? tied by reference in this case
using DrivetrainSystemType = DrivetrainSystem<InverterInterfaceType>;
auto drivetrain = DrivetrainSystemType({&fl_inv, &fr_inv, &rl_inv, &rr_inv}, INVERTER_ENABLING_TIMEOUT_INTERVAL); // Tie inverter interfaces to drivetrain system (by pointers)
// Hypothetical controllers, need more implementation details
TorqueControllerSimple simple_mode;
TorqueControllerSimple normal_force_mode;
TorqueControllerSimple endurance_derating_mode;
TorqueControllerSimple launch_control_mode;
TorqueControllerSimple torque_vectoring_mode;
TorqueControllerMux torque_controller_mux;  // would prob need to tie controllers to mux as well?
/* Declare state machine */
MCUStateMachine<DrivetrainSystemType> fsm(&buzzer, &drivetrain, &dashboard);    // need more implemetation details. associated interfaces and systems tied by pointers

/* Global instantiations */
SysTick_s curr_tick;

/* Function declarations */
/* CAN functions */
void init_all_CAN();
void dispatch_all_CAN();
void dispatch_inv_CAN();
void dispatch_telem_CAN();
void update_and_enqueue_all_CAN();
/* External value readings */
void sample_all_external_readings();
/* Process all readings */
void process_all_value_readings();

void setup() {

    /* Tick system clock */
    curr_tick = sys_clock.tick(micros());

    /* Initialize CAN communication */
    init_all_CAN();

    /* Initialize interface */
    main_ecu.init();    // pin mode, initial shutdown circuit readings, 
    wd_interface.init(curr_tick);   // pin mode, initialize wd kick time
    ams_interface.init(curr_tick);  // pin mode, initialize last heartbeat time

    /* Initialize system */
    safety_system.init();   // write software_ok high, write wd_input high, set software ok state true
    // ControllerMux set initial max torque to 10 NM, torque mode to 0 (could be done at construction or have an init function)
    // Drivetrain set all inverters disabled, write inv_en and inv_24V_en hight, set inverter_has_error to false if using

    /* Present action for 5s */
    delay(SETUP_PRESENT_ACTION_INTERVAL);

    /* Set start up status */
    // fsm either initialize state to STARTUP/TRACTIVE_SYSTEM_NOT_ACTIVE or enable external set state
    // ControllerMux set max torque to 21 NM, torque mode to whatever makes most sense

}

void loop() {

    /* Tick system clock */
    curr_tick = sys_clock.tick(micros());

    /* Interfaaces retrieve values */
    // Distribute incoming CAN messages
    dispatch_all_CAN();
    // Sensors sample and cache
    sample_all_external_readings();
    
    /* System process readings prior to ticking state machine */
    process_all_value_readings();

    /* Update and enqueue CAN messages */
    update_and_enqueue_all_CAN();

    /* Inverter procedure before entering state machine */
    // Drivetrain check if inverters have error
    // Drivetrain reset inverters

    /* Tick state machine */
    fsm.tick_state_machine(curr_tick);

    /* Tick safety system */
    safety_system.software_shutdown(curr_tick);
}

void init_all_CAN() {
    // Inverter CAN line
    INV_CAN.begin();
    INV_CAN.setBaudRate(500000);
    INV_CAN.setMaxMB(16);
    INV_CAN.enableFIFO();
    INV_CAN.enableFIFOInterrupt();
    INV_CAN.onReceive(on_can2_receive);
    INV_CAN.mailboxStatus();

    // Telemetry CAN line
    TELEM_CAN.begin();
    TELEM_CAN.setBaudRate(500000);
    TELEM_CAN.setMaxMB(16);
    TELEM_CAN.enableFIFO();
    TELEM_CAN.enableFIFOInterrupt();
    TELEM_CAN.onReceive(on_can3_receive);
    TELEM_CAN.mailboxStatus();

    delay(500);
}

void dispatch_all_CAN() {
    dispatch_inv_CAN();
    dispatch_telem_CAN();
}

void dispatch_inv_CAN() {
    while (CAN2_rxBuffer.available())
    {
        CAN_message_t recvd_msg;
        uint8_t buf[sizeof(CAN_message_t)];
        CAN2_rxBuffer.pop_front(buf, sizeof(CAN_message_t));
        memmove(&recvd_msg, buf, sizeof(recvd_msg));
        switch (recvd_msg.id)
        {
        // Motor status
        case ID_MC1_STATUS:    fl_inv.receive_status_msg(recvd_msg);    break;
        case ID_MC2_STATUS:    fr_inv.receive_status_msg(recvd_msg);    break;
        case ID_MC3_STATUS:    rl_inv.receive_status_msg(recvd_msg);    break;
        case ID_MC3_STATUS:    rr_inv.receive_status_msg(recvd_msg);    break;
        // Motor temperature
        case ID_MC1_TEMPS:     fl_inv.receive_temp_msg(recvd_msg);    break;
        case ID_MC2_TEMPS:     fr_inv.receive_temp_msg(recvd_msg);    break;
        case ID_MC3_TEMPS:     rl_inv.receive_temp_msg(recvd_msg);    break;
        case ID_MC4_TEMPS:     rr_inv.receive_temp_msg(recvd_msg);    break;
        // Motor energy
        case ID_MC1_ENERGY:    fl_inv.receive_energy_msg(recvd_msg);    break;
        case ID_MC2_ENERGY:    fr_inv.receive_energy_msg(recvd_msg);    break;
        case ID_MC3_ENERGY:    rl_inv.receive_energy_msg(recvd_msg);    break;
        case ID_MC4_ENERGY:    rr_inv.receive_energy_msg(recvd_msg);    break;
        default:               break;
        }
    }
}

void dispatch_telem_CAN() {
    while (CAN3_rxBuffer.available())
    {
        CAN_message_t recvd_msg;
        uint8_t buf[sizeof(CAN_message_t)];
        CAN3_rxBuffer.pop_front(buf, sizeof(CAN_message_t));
        memmove(&recvd_msg, buf, sizeof(recvd_msg));
        switch (recvd_msg.id)
        {
        // AMS CAN
        case ID_BMS_COULOMB_COUNTS:
            // ams_interface.retrieve_coulomb_count_CAN(recvd_msg);
            break;
        case ID_BMS_STATUS:
            ams_interface.retrieve_status_CAN(recvd_msg, curr_tick);
            break;
        case ID_BMS_TEMPERATURES:
            ams_interface.retrieve_temp_CAN(recvd_msg);
            break;
        case ID_BMS_VOLTAGES:
            ams_interface.retrieve_voltage_CAN(recvd_msg);
            break;
        // Dashboard status
        case ID_DASHBOARD_STATUS:
            dashboard.read(recvd_msg);
            break;
        default:
            break;
        }
    }
}

void update_and_enqueue_all_CAN() {
    // Drivetrain system
        // probably here as well
    // MCU interface
    // main_ecu.tick(curr_tick,
                //   fsm.get_state(),
                //   drivetrain.drivetrain_error_occured(),
                //   safety_system.get_software_is_ok(),
                  // TCMux return
                //   buzzer.buzzer_is_on(),
                  // Pedal system return
                //   ams_interface.pack_charge_is_critical(),
                //   dash.lauchControlButtonPressed());
    // Telemetry
    // telem_interface.tick(curr_tick,
                        //  ADC1.get(),
                        //  ADC2.get(),
                        //  ADC3.get(),
                        //  steering1.convert());
}

void sample_all_external_readings() {
    // Tick all adcs
    // ADC1.tick();
    // ADC2.tick();
    // ADC3.tick();
    // Tick steering system
    // steering1.tick();
    // Read shutdown circuits    
    main_ecu.read_mcu_status();
}

void process_all_value_readings() {
    // pedals.tick();
}

