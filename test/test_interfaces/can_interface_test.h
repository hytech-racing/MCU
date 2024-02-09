#ifndef CAN_INTERFACE_TEST
#define CAN_INTERFACE_TEST
#include <Arduino.h>
#include <unity.h>
#include "hytechCANInterface.h"


FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> TEST_CAN1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> TEST_CAN2;   // Inverter CAN (now both are on same line)


void init_can_interface()
{
    TEST_CAN2.begin();
    TEST_CAN2.setBaudRate(INV_CAN_BAUDRATE);
    TEST_CAN2.setMaxMB(16);
    TEST_CAN2.enableFIFO();
    TEST_CAN2.enableFIFOInterrupt();
    TEST_CAN2.onReceive(on_can2_receive);
    TEST_CAN2.mailboxStatus();

    TEST_CAN1.begin();
    TEST_CAN1.setBaudRate(INV_CAN_BAUDRATE);
    TEST_CAN1.setMaxMB(16);
    TEST_CAN1.enableFIFO();
    TEST_CAN1.enableFIFOInterrupt();
    TEST_CAN1.onReceive(on_can1_receive);
    TEST_CAN1.mailboxStatus();
}

void test_can_interface_send()
{
    
    // send on CAN 2 a simple message from an interface
    // inverter
    using CircularBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
    using InverterInterfaceType = InverterInterface<CircularBufferType>;
    InverterInterfaceType fl_inv(&CAN2_txBuffer, ID_MC4_SETPOINTS_COMMAND, 9, 8);
    CANInterfaces<CircularBufferType> CAN_interfaces = {&fl_inv, &{}, &{}, &{}, &{}, &{}};

    fl_inv.request_enable_inverter();
    // ensure that the tx queue is of size 1
    TEST_ASSERT_EQUAL(CAN2_txBuffer.available(), 1);

    // handle send
    Serial.println("attempting send");
    send_all_CAN_msgs(CAN2_txBuffer, &TEST_CAN2);
    Serial.println("sent can message");
    TEST_ASSERT_EQUAL(CAN2_txBuffer.available(), 0);

    // clear for testing second test
    CAN1_rxBuffer.clear();
}

void test_can_interface_send_and_receive_raw()
{
    
    // send on CAN 2 and receive a simple message 
    
    // manually put a message on the can2 tx buffer
    CAN_message_t msg;
    msg.id = 69;
    msg.buf[0] = 69;
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg));
    CAN2_txBuffer.push_back(buf, sizeof(CAN_message_t));


    // ensure that the tx queue is of size 1
    TEST_ASSERT_EQUAL(CAN2_txBuffer.available(), 1);

    // handle send
    Serial.println("attempting send");
    send_all_CAN_msgs(CAN2_txBuffer, &TEST_CAN2);
    Serial.println("sent can message");

    // assuming that we have connected CAN1 to CAN2 we should now have a message in the CAN1_rx_buffer
    delay(1);
    TEST_ASSERT_EQUAL(CAN1_rxBuffer.available(), 1);

}


#endif /* CAN_INTERFACE_TEST */
