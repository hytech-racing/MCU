// /* Prototype main function for logic soothing */

// /* Include files */
#include <Arduino.h>
// #include "MCUStateMachine.h"
#include "FlexCAN_T4.h"
// #include "HyTech_CAN.h"

#include "ADC_SPI.h"
// #include "MessageHandler.h"
#include "MCUInterface.h"
#include "AMSInterface.h"
#include "WatchdogInterface.h"
#include "DashboardInterface.h"
#include "InverterInterface.h"
#include "TelemetryInterface.h"

#include "SafetySystem.h"

#include "HytechCANInterface.h"



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
CAN_message_t msg;

AMSInterface ams_interface;
MCUInterface main_ecu(&ams_interface);
WatchdogInterface wd_interface(&main_ecu);
DashboardInterface dashboard();
InverterInterface inv_interface[4];
TelemetryInterface telem_interface();

SafetySystem safety_system(&ams_interface, wd_interface);

/* CAN functions */
void init_all_CAN();
void init_all_CAN_og();
void dispatch_all_CAN();
void send_CAN_1Hz();
void send_CAN_10Hz();
void send_CAN_20Hz();
void send_CAN_50Hz();

void setup() {

    /* Initialize CAN communication */
    init_all_CAN();

    /* Initialize interface */
    main_ecu.init();        // mcu_status_init()

    wd_interface.init();    // pinMode(WD_INPUT)
    ams_interface.init();   // pinMode(SW_OK)

    /* Initialize system */
    safety_system.init();   // dW(SW_OK)
                            // dW(WD_INPUT)
                            // ams set sw is ok


}

void loop() {

    dispatch_all_CAN();



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
}

void init_all_CAN_og() {
    //Inverter CAN line
    INV_CAN.begin();
    INV_CAN.setBaudRate(INV_CAN_SPEED);
    INV_CAN.enableMBInterrupts();
    INV_CAN.onReceive(parse_inv_CAN_message);

    // Telemetry CAN line
    TELEM_CAN.begin();
    TELEM_CAN.setBaudRate(TELEM_CAN_SPEED);    
    TELEM_CAN.enableMBInterrupts();    
    TELEM_CAN.onReceive(parse_telem_CAN_message);

    delay(500);
}

void dispatch_all_CAN(AllMsgs &received_can_msgs) {
    dispatch_inv_CAN();
    dispatch_telem_CAN()
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
        case ID_MC1_STATUS:    inv_interface[0].retrieve_status_CAN(recvd_msg);    break;
        case ID_MC2_STATUS:    inv_interface[1].retrieve_status_CAN(recvd_msg);    break;
        case ID_MC3_STATUS:    inv_interface[2].retrieve_status_CAN(recvd_msg);    break;
        case ID_MC3_STATUS:    inv_interface[3].retrieve_status_CAN(recvd_msg);    break;
        // Motor temperature
        case ID_MC1_TEMPS:     inv_interface[0].retrieve_status_CAN(recvd_msg);    break;
        case ID_MC2_TEMPS:     inv_interface[1].retrieve_status_CAN(recvd_msg);    break;
        case ID_MC3_TEMPS:     inv_interface[2].retrieve_status_CAN(recvd_msg);    break;
        case ID_MC4_TEMPS:     inv_interface[3].retrieve_status_CAN(recvd_msg);    break;
        // Motor energy
        case ID_MC1_ENERGY:    inv_interface[0].retrieve_energy_CAN(recvd_msg);    break;
        case ID_MC2_ENERGY:    inv_interface[1].retrieve_energy_CAN(recvd_msg);    break;
        case ID_MC3_ENERGY:    inv_interface[2].retrieve_energy_CAN(recvd_msg);    break;
        case ID_MC4_ENERGY:    inv_interface[3].retrieve_energy_CAN(recvd_msg);    break;
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
            ams_interface.retrieve_coulomb_count_CAN(recvd_msg);
            break;
        case ID_BMS_STATUS:
            ams_interface.retrieve_status_CAN(recvd_msg);
            break;
        case ID_BMS_TEMPERATURES:
            ams_interface.retrieve_temp_CAN(recvd_msg);
            break;
        case ID_BMS_VOLTAGES:
            ams_interface.retrieve_voltage_CAN(recvd_msg);
            break;
        // Dashboard status
        case ID_DASHBOARD_STATUS:
            dashboard.retrieve_CAN(recvd_msg);
            break;
        default:
            break;
        }
    }
}

void parse_inv_CAN_message(const CAN_message_t &RX_msg) {
    CAN_message_t rx_msg = RX_msg;
    switch (rx_msg.id) {
    // Motor status
    case ID_MC1_STATUS:    inv_interface[0].retrieve_status_CAN(rx_msg);    break;
    case ID_MC2_STATUS:    inv_interface[1].retrieve_status_CAN(rx_msg);    break;
    case ID_MC3_STATUS:    inv_interface[2].retrieve_status_CAN(rx_msg);    break;
    case ID_MC3_STATUS:    inv_interface[3].retrieve_status_CAN(rx_msg);    break;
    // Motor temperature
    case ID_MC1_TEMPS:     inv_interface[0].retrieve_status_CAN(rx_msg);    break;
    case ID_MC2_TEMPS:     inv_interface[1].retrieve_status_CAN(rx_msg);    break;
    case ID_MC3_TEMPS:     inv_interface[2].retrieve_status_CAN(rx_msg);    break;
    case ID_MC4_TEMPS:     inv_interface[3].retrieve_status_CAN(rx_msg);    break;
    // Motor energy
    case ID_MC1_ENERGY:    inv_interface[0].retrieve_energy_CAN(rx_msg);    break;
    case ID_MC2_ENERGY:    inv_interface[1].retrieve_energy_CAN(rx_msg);    break;
    case ID_MC3_ENERGY:    inv_interface[2].retrieve_energy_CAN(rx_msg);    break;
    case ID_MC4_ENERGY:    inv_interface[3].retrieve_energy_CAN(rx_msg);    break;
    default:               break;
  }
}

void parse_telem_CAN_message(const CAN_message_t &RX_msg) {
    CAN_message_t rx_msg = RX_msg;
    switch (rx_msg.id)
    {
    // AMS CAN
    case ID_BMS_COULOMB_COUNTS:
        ams_interface.retrieve_coulomb_count_CAN(rx_msg);
        break;
    case ID_BMS_STATUS:
        ams_interface.retrieve_status_CAN(rx_msg);
        break;
    case ID_BMS_TEMPERATURES:
        ams_interface.retrieve_temp_CAN(rx_msg);
        break;
    case ID_BMS_VOLTAGES:
        ams_interface.retrieve_voltage_CAN(rx_msg);
        break;
    // Dashboard status
    case ID_DASHBOARD_STATUS:
        dashboard.retrieve_CAN(rx_msg);
        break;
    default:
        break;
    }
}

/* Hardware timer (?) */
void send_CAN_1Hz() {
    CAN_message_t msg;
    ams_interface.send_CAN_bms_coulomb_counts(msg);
    TELEM_CAN.write(msg);
}

void send_CAN_10Hz() {
    
    main_ecu.send_CAN_mcu_status(msg);
    TELEM_CAN.write(msg);
}

void send_CAN_20Hz() {
    telem_interface.send_CAN_mcu_pedal_readings(msg);
    TELEM_CAN.write(msg);    
    telem_interface.send_CAN_mcu_analog_readings(msg);
    TELEM_CAN.write(msg);
}

void send_CAN_50Hz() {
    for (int i = 0; i < 4; i++) {
        inv_interface[i].send_CAN_inverter_setpoints(msg);
        TELEM_CAN.write(msg);
    }

    telem_interface.send_CAN_mcu_load_cells(msg);
    TELEM_CAN.write(msg);
    telem_interface.send_CAN_mcu_front_potentiometers(msg);
    TELEM_CAN.write(msg);
    telem_interface.send_CAN_mcu_rear_potentiometers(msg);
    TELEM_CAN.write(msg);
}