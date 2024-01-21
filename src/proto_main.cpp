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
// MessageHandler<FlexCAN_T4_Base, CAN_message_t> msg_writer(&FRONT_INV_CAN, &msg, 100, millis());

AMSInterface ams_interface;
MCUInterface main_ecu(&ams_interface);
WatchdogInterface wd_interface(&main_ecu);
DashboardInterface dashboard();
InverterInterface inv_interface[4];
TelemetryInterface telem_interface();

SafetySystem safety_system(&ams_interface, wd_interface);

/* CAN functions */
void init_all_CAN();
void process_all_CAN_buffer(AllMsgs &received_can_msgs);
void dispatch_all_CAN(AllMsgs &received_can_msgs);
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

    AllMsgs received_can_msgs;
    process_all_CAN_buffer(received_can_msgs);
    dispatch_all_CAN(received_can_msgs);



    msg_writer.handle_sending(millis());
    // msg_writer.test();
    // state_machine.get_state();
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

void process_all_CAN_buffer(AllMsgs &received_can_msgs) {
    process_ring_buffer(received_can_msgs, CAN2_rxBuffer);
    process_ring_buffer(received_can_msgs, CAN3_rxBuffer);
}

void dispatch_all_CAN(AllMsgs &received_can_msgs) {
    // Motor status
    if (std::get<0>(received_can_msgs.mc_1_status)) {
        inv_interface[0].retrieve_status_CAN(std::get<1>(received_can_msgs.mc_1_status));
    }
    else if (std::get<0>(received_can_msgs.mc_2_status)) {
        inv_interface[1].retrieve_status_CAN(std::get<1>(received_can_msgs.mc_2_status));
    }
    else if (std::get<0>(received_can_msgs.mc_3_status)) {
        inv_interface[2].retrieve_status_CAN(std::get<1>(received_can_msgs.mc_3_status));
    }
    else if (std::get<0>(received_can_msgs.mc_4_status)) {
        inv_interface[3].retrieve_status_CAN(std::get<1>(received_can_msgs.mc_4_status));
    }
    // Motor temperature
    else if (std::get<0>(received_can_msgs.mc_1_temps)) {
        inv_interface[0].retrieve_temp_CAN(std::get<1>(received_can_msgs.mc_1_status));
    }
    else if (std::get<0>(received_can_msgs.mc_2_temps)) {
        inv_interface[1].retrieve_temp_CAN(std::get<1>(received_can_msgs.mc_2_status));
    }
    else if (std::get<0>(received_can_msgs.mc_3_temps)) {
        inv_interface[2].retrieve_temp_CAN(std::get<1>(received_can_msgs.mc_3_status));
    }
    else if (std::get<0>(received_can_msgs.mc_4_temps)) {
        inv_interface[3].retrieve_temp_CAN(std::get<1>(received_can_msgs.mc_4_status));
    }
    // Motor energy
    else if (std::get<0>(received_can_msgs.mc_1_energy)) {
        inv_interface[0].retrieve_energy_CAN(std::get<1>(received_can_msgs.mc_1_status));
    }
    else if (std::get<0>(received_can_msgs.mc_2_energy)) {
        inv_interface[1].retrieve_energy_CAN(std::get<1>(received_can_msgs.mc_2_status));
    }
    else if (std::get<0>(received_can_msgs.mc_3_energy)) {
        inv_interface[2].retrieve_energy_CAN(std::get<1>(received_can_msgs.mc_3_status));
    }
    else if (std::get<0>(received_can_msgs.mc_4_energy)) {
        inv_interface[3].retrieve_energy_CAN(std::get<1>(received_can_msgs.mc_4_status));
    }
    // Inverter torque setpoints
    else if (std::get<0>(received_can_msgs.mc_1_setpoints)) {
        inv_interface[0].retrieve_setpoints_CAN(std::get<1>(received_can_msgs.mc_1_status));
    }
    else if (std::get<0>(received_can_msgs.mc_2_setpoints)) {
        inv_interface[1].retrieve_setpoints_CAN(std::get<1>(received_can_msgs.mc_2_status));
    }
    else if (std::get<0>(received_can_msgs.mc_3_setpoints)) {
        inv_interface[2].retrieve_setpoints_CAN(std::get<1>(received_can_msgs.mc_3_status));
    }
    else if (std::get<0>(received_can_msgs.mc_4_setpoints)) {
        inv_interface[3].retrieve_setpoints_CAN(std::get<1>(received_can_msgs.mc_4_status));
    }
    // AMS CAN
    else if (std::get<0>(received_can_msgs.bms_coulomb_counts)) {
        ams_interface.retrieve_coulomb_count_CAN(std::get<1>(received_can_msgs.bms_coulomb_counts));
    }
    else if (std::get<0>(received_can_msgs.bms_status)) {
        ams_interface.retrieve_status_CAN(std::get<1>(received_can_msgs.bms_status));
    }
    else if (std::get<0>(received_can_msgs.bms_temperatures)) {
        ams_interface.retrieve_temp_CAN(std::get<1>(received_can_msgs.bms_temperatures));
    }
    else if (std::get<0>(received_can_msgs.bms_voltages)) {
        ams_interface.retrieve_voltage_CAN(std::get<1>(received_can_msgs.bms_voltages));
    }
    // Dashboard status
    else if (std::get<0>(received_can_msgs.dashboard_status)) {
        dashboard.retrieve_CAN(std::get<1>(received_can_msgs.dashboard_status));
    }
}

void send_CAN_1Hz() {
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