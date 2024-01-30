/* Prototype main function for logic soothing */

/* Include files */
#include <Arduino.h>
#include "MCUStateMachine.h"
#include "FlexCAN_T4.h"
#include "InverterInterface.h"
#include "ADC_SPI.h"
#include "MessageHandler.h"
#include "DrivetrainSystem.h"
#include "PedalsSystem.h"

#include "HytechCANInterface.h"

using CircularBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
CircularBufferType buffer;

using InverterInterfaceType = InverterInterface<CircularBufferType>;

BuzzerController buzzer(500);

DashboardInterface dash_interface;

InverterInterfaceType fl_inv(&buffer, 69);
InverterInterfaceType fr_inv(&buffer, 69);

InverterInterfaceType rl_inv(&buffer, 69);
InverterInterfaceType rr_inv(&buffer, 69);

CANInterfaces<CircularBufferType> can_interfaces = {&fl_inv, &fr_inv, &rl_inv, &rr_inv};

using DrivetrainSystemType = DrivetrainSystem<InverterInterfaceType>;
auto drivetrain = DrivetrainSystemType({&fl_inv, &fr_inv, &rl_inv, &rr_inv}, 5000);

PedalsParams params_for_test = {1, 1, 10, 10, 1, 1, 9, 9};
PedalsSystem pedals(params_for_test, params_for_test);

MCUStateMachine<DrivetrainSystemType> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals);

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> FRONT_INV_CAN;

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

    process_ring_buffer(CAN1_rxBuffer, can_interfaces);
    process_ring_buffer(CAN2_rxBuffer, can_interfaces);
    process_ring_buffer(CAN3_rxBuffer, can_interfaces);

    // msg_writer.handle_sending(millis());
    // msg_writer.test();
    state_machine.get_state();
    send_all_CAN_msgs(buffer, &FRONT_INV_CAN);

}