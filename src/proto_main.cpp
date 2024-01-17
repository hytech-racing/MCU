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



// BuzzerController buzzer(500);

// DashDriver dash_interface;

// InverterComponent lf_inv(100);
// InverterComponent rf_inv(100);

// InverterComponent lr_inv(100);
// InverterComponent rr_inv(100);


// DrivetrainComponent drivetrain({&lf_inv, &rf_inv, &lr_inv, &rr_inv});
// MCUStateMachine state_machine(&buzzer, &drivetrain, &dash_interface);


/* Two CAN lines on Main ECU rev15 */
// FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> INV_CAN;
// FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;
// CAN_message_t msg;
// MessageHandler<FlexCAN_T4_Base, CAN_message_t> msg_writer(&FRONT_INV_CAN, &msg, 100, millis());

AMSInterface ams_interface;
MCUInterface main_ecu(&ams_interface);

void setup() {
    main_ecu.init();
}

void loop() {
    main_ecu.poll_CAN();
    main_ecu.read_mcu_status();
    main_ecu.send_CAN_inverter_setpoints();
    main_ecu.send_CAN_mcu_status();
    main_ecu.send_CAN_mcu_pedal_readings();
    main_ecu.send_CAN_mcu_load_cells();
    main_ecu.send_CAN_mcu_potentiometers();
    main_ecu.send_CAN_mcu_analog_readings();
    main_ecu.send_CAN_imu_accelerometer();
    main_ecu.send_CAN_imu_gyroscope();
    main_ecu.send_CAN_bms_coulomb_counts();
    // msg_writer.handle_sending(millis());
    // msg_writer.test();
    // state_machine.get_state();
}