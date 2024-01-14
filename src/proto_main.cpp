/* Prototype main function for logic soothing */

/* Include files */
#include <Arduino.h>
#include "MCUStateMachine.h"
#include "FlexCAN_T4.h"

#include "ADC_SPI.h"
#include "MessageHandler.h"


BuzzerController buzzer(500);

DashDriver dash_interface;

InverterComponent lf_inv(100);
InverterComponent rf_inv(100);

InverterComponent lr_inv(100);
InverterComponent rr_inv(100);


DrivetrainComponent drivetrain({&lf_inv, &rf_inv, &lr_inv, &rr_inv});
MCUStateMachine state_machine(&buzzer, &drivetrain, &dash_interface);


FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> FRONT_INV_CAN;
CAN_message_t msg;
MessageHandler<FlexCAN_T4_Base, CAN_message_t> msg_writer(&FRONT_INV_CAN, &msg, 100, millis());


void setup() {
    
}

void loop() {
    msg_writer.handle_sending(millis());
    // msg_writer.test();
    // state_machine.get_state();
}