/* Prototype main function for logic soothing */

/* Include files */
#include <Arduino.h>
#include "MCUStateMachine.h"
#include "FlexCAN_T4.h"
#include "InverterInterface.h"
#include "ADC_SPI.h"
#include "MessageHandler.h"

#include "HytechCANInterface.h"

BuzzerController buzzer(500);

DashboardInterface dash_interface;

InverterInterface lf_inv;
InverterInterface rf_inv;

InverterInterface lr_inv;
InverterInterface rr_inv;

DashboardInterface dash;

DrivetrainSystem drivetrain({&lf_inv, &rf_inv, &lr_inv, &rr_inv}, 5000);
MCUStateMachine state_machine(&buzzer, &drivetrain, &dash_interface);

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> FRONT_INV_CAN;
CAN_message_t msg;
MessageHandler<FlexCAN_T4_Base, CAN_message_t> msg_writer(&FRONT_INV_CAN, &msg, 100, millis());

void setup()
{
    // drivetrain.give_inverters();
    FRONT_INV_CAN.begin();
    FRONT_INV_CAN.setBaudRate(500000);
    FRONT_INV_CAN.setMaxMB(16);
    FRONT_INV_CAN.enableFIFO();
    FRONT_INV_CAN.enableFIFOInterrupt();
    FRONT_INV_CAN.onReceive(on_can2_receive);
    FRONT_INV_CAN.mailboxStatus();
}

void loop()
{
    AllMsgs received_can_msgs;
    process_ring_buffer(received_can_msgs, CAN1_rxBuffer);
    process_ring_buffer(received_can_msgs, CAN2_rxBuffer);
    process_ring_buffer(received_can_msgs, CAN3_rxBuffer);

    if(std::get<0>(received_can_msgs.dashboard_status)){
        dash.receive(std::get<1>(received_can_msgs.dashboard_status));
    }
    
    msg_writer.handle_sending(millis());
    // msg_writer.test();
    // state_machine.get_state();
}