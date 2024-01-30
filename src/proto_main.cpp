// /* Prototype main function for logic soothing */

// /* Include files */
#include <Arduino.h>

#include "FlexCAN_T4.h"
// #include "HyTech_CAN.h"

/* Interfaces */
#include "HytechCANInterface.h"
#include "MCP3208.h"
#include "ORBIS_BR10.h"
#include "MCUInterface.h"
#include "AMSInterface.h"
#include "WatchdogInterface.h"
// #include "DashboardInterface.h"
// #include "InverterInterface.h"
#include "TelemetryInterface.h"
/* Systems */
#include "SafetySystem.h"
#include "SysClock.h"
/* State machine */
#include "MCUStateMachine.h"



// BuzzerController buzzer(500);

// DashDriver dash_interface;

// InverterComponent lf_inv(100);
// InverterComponent rf_inv(100);

// InverterComponent lr_inv(100);
// InverterComponent rr_inv(100);


// DrivetrainComponent drivetrain({&lf_inv, &rf_inv, &lr_inv, &rr_inv});
// MCUStateMachine state_machine(&buzzer, &drivetrain, &dash_interface);


/* Two CAN lines on Main ECU rev15 */
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> INV_CAN;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;
/* Set up CAN circular buffer */
using CircularBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
/* Sensors */
MCP3208 ADC1(ADC1_CS);
MCP3208 ADC2(ADC2_CS);
MCP3208 ADC3(ADC3_CS);
OrbisBR10 Steering1(Serial5);

/* Declare interfaces */
AMSInterface ams_interface;
MCUInterface<CircularBufferType> main_ecu(&CAN3_txBuffer);
WatchdogInterface wd_interface;
// DashboardInterface dashboard;
// InverterInterface inv_interface[4];
TelemetryInterface<CircularBufferType> telem_interface(&CAN3_txBuffer);
/* Declare systems */
SafetySystem safety_system(&ams_interface, &wd_interface);
SysClock sys_clock;
SysTick_s curr_tick;
/* Declare state machine */
MCUStateMachine fsm;

/* CAN functions */
void init_all_CAN();
void dispatch_all_CAN();
void dispatch_inv_CAN();
void dispatch_telem_CAN();
void update_and_enqueue_all_CAN();

void setup() {

    /* Tick system clock */
    curr_tick = sys_clock.tick(micros());

    /* Initialize CAN communication */
    init_all_CAN();

    /* Initialize interface */
    main_ecu.init();        // mcu_status_init()

    wd_interface.init(curr_tick);    // pinMode(WD_INPUT)
    ams_interface.init();   // pinMode(SW_OK)

    /* Initialize system */
    safety_system.init();   // dW(SW_OK)
                            // dW(WD_INPUT)
                            // ams set sw is ok


}

void loop() {

    /* Tick system clock */
    curr_tick = sys_clock.tick(micros());

    /* Interfaaces retrieve values */
    // Distribute incoming CAN messages
    dispatch_all_CAN();
    // Sensors sample and cache
    main_ecu.read_mcu_status();

    /* Tick state machine */
    
    /* Update and enqueue CAN messages */
    update_and_enqueue_all_CAN();

    /* Tick safety system */
    safety_system.software_shutdown(curr_tick);
}

void init_all_CAN() {
    // Inverter CAN line
    INV_CAN.begin();
    INV_CAN.setBaudRate(INV_CAN_SPEED);
    INV_CAN.setMaxMB(16);
    INV_CAN.enableFIFO();
    INV_CAN.enableFIFOInterrupt();
    INV_CAN.onReceive(on_can2_receive);
    INV_CAN.mailboxStatus();

    // Telemetry CAN line
    TELEM_CAN.begin();
    TELEM_CAN.setBaudRate(TELEM_CAN_SPEED);
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
    // while (CAN2_rxBuffer.available())
    // {
    //     CAN_message_t recvd_msg;
    //     uint8_t buf[sizeof(CAN_message_t)];
    //     CAN2_rxBuffer.pop_front(buf, sizeof(CAN_message_t));
    //     memmove(&recvd_msg, buf, sizeof(recvd_msg));
    //     switch (recvd_msg.id)
    //     {
    //     // Motor status
    //     case ID_MC1_STATUS:    inv_interface[0].retrieve_status_CAN(recvd_msg);    break;
    //     case ID_MC2_STATUS:    inv_interface[1].retrieve_status_CAN(recvd_msg);    break;
    //     case ID_MC3_STATUS:    inv_interface[2].retrieve_status_CAN(recvd_msg);    break;
    //     case ID_MC3_STATUS:    inv_interface[3].retrieve_status_CAN(recvd_msg);    break;
    //     // Motor temperature
    //     case ID_MC1_TEMPS:     inv_interface[0].retrieve_status_CAN(recvd_msg);    break;
    //     case ID_MC2_TEMPS:     inv_interface[1].retrieve_status_CAN(recvd_msg);    break;
    //     case ID_MC3_TEMPS:     inv_interface[2].retrieve_status_CAN(recvd_msg);    break;
    //     case ID_MC4_TEMPS:     inv_interface[3].retrieve_status_CAN(recvd_msg);    break;
    //     // Motor energy
    //     case ID_MC1_ENERGY:    inv_interface[0].retrieve_energy_CAN(recvd_msg);    break;
    //     case ID_MC2_ENERGY:    inv_interface[1].retrieve_energy_CAN(recvd_msg);    break;
    //     case ID_MC3_ENERGY:    inv_interface[2].retrieve_energy_CAN(recvd_msg);    break;
    //     case ID_MC4_ENERGY:    inv_interface[3].retrieve_energy_CAN(recvd_msg);    break;
    //     default:               break;
    //     }
    // }
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
            ams_interface.retrieve_coulomb_count_CAN(recvd_msg);
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
        // case ID_DASHBOARD_STATUS:
            // dashboard.retrieve_CAN(recvd_msg);
            // break;
        default:
            break;
        }
    }
}

void update_and_enqueue_all_CAN() {
    // MCU interface
    main_ecu.tick(curr_tick,
                  fsm.get_state(),
                  drivetrain.drive_error_occured(),
                  safety_system.get_software_is_ok(),
                  // TCMux return
                  buzzer.buzzer_is_on(),
                  // Pedal system return
                  ams_interface.pack_charge_is_critical(),
                  dash.lauchControlButtonPressed());
    // Telemetry
    telem_interface.tick(curr_tick,
                         ADC1.get(),
                         ADC2.get(),
                         ADC3.get(),
                         Steering1.convert());
}

