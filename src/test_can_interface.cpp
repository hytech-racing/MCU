
#include <FlexCAN_T4.h>
#include "HytechCANInterface.h"
#include "InverterInterface.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> TEST_CAN1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> TEST_CAN2; // Inverter CAN (now both are on same line)

CAN_message_t msg;

using CircularBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
using InverterInterfaceType = InverterInterface<CircularBufferType>;
InverterInterfaceType fl_inv(&CAN2_txBuffer, ID_MC1_SETPOINTS_COMMAND);
InverterInterfaceType fr_inv(&CAN2_txBuffer, ID_MC2_SETPOINTS_COMMAND);
InverterInterfaceType rl_inv(&CAN2_txBuffer, ID_MC3_SETPOINTS_COMMAND);
InverterInterfaceType rr_inv(&CAN2_txBuffer, ID_MC4_SETPOINTS_COMMAND);

CANInterfaces<CircularBufferType> CAN_interfaces = {&fl_inv, &fr_inv, &rl_inv, &rr_inv, 0, 0, 0};

void init_can_interface()
{
    TEST_CAN2.begin();
    TEST_CAN2.setBaudRate(500000);
    TEST_CAN2.setMaxMB(16);
    TEST_CAN2.enableFIFO();
    TEST_CAN2.enableFIFOInterrupt();
    TEST_CAN2.onReceive(on_can2_receive);
    TEST_CAN2.mailboxStatus();

    TEST_CAN1.begin();
    TEST_CAN1.setBaudRate(500000);
    TEST_CAN1.setMaxMB(16);
    TEST_CAN1.enableFIFO();
    TEST_CAN1.enableFIFOInterrupt();
    TEST_CAN1.enableMBInterrupts();
    TEST_CAN1.onReceive(on_can1_receive);
    TEST_CAN1.mailboxStatus();
}

void setup(void)
{
    while (!Serial)
    {
        // wait for Arduino Serial Monitor to be ready
    }
    init_can_interface();
}
bool ran_test = false;
void loop()
{
    // test for seeing if when CAN2 is connected to CAN1 the can1 rx buffer will get stuff
    // testing whether or not a CAN message can be sent

    if (!ran_test)
    {
        msg.id = random(0x1, 0x7FE);
        for (uint8_t i = 0; i < 8; i++)
            msg.buf[i] = i + 1;
        TEST_CAN2.write(msg);
        ran_test = true;
        delay(10);
        Serial.println("======= TEST 1 =======");
        Serial.println("can1 rx buffer size: (should be 1)");
        Serial.println(CAN1_rxBuffer.available());
        Serial.println("======= TEST 2 =======");

        Serial.println("can1 received message equal to sent msg");
        delay(10);
        if (CAN1_rxBuffer.available())
        {
            CAN_message_t recvd_msg;
            uint8_t buf[sizeof(CAN_message_t)];
            CAN1_rxBuffer.pop_front(buf, sizeof(CAN_message_t));
            memmove(&recvd_msg, buf, sizeof(recvd_msg));

            Serial.println("\tid = prev: (should be 1)");
            Serial.print("\t");
            Serial.println(recvd_msg.id == msg.id);
        }

        Serial.println("======= TEST 3 =======");
        // command the rl inverter to reset (sets the remove error flag on mc setpoints command)
        // queues onto tx buffer
        rl_inv.command_reset();
        // msg.id = random(0x1, 0x7FE);
        // for (uint8_t i = 0; i < 8; i++) msg.buf[i] = i + 1;
        // uint8_t buf2[sizeof(CAN_message_t)];
        // memmove(buf2, &msg, sizeof(msg));
        // CAN2_txBuffer.push_back(buf2, sizeof(CAN_message_t));
        // send all messages on tx buffer

        Serial.println("can2 tx buffer size: (should be 1)");

        Serial.println(CAN2_txBuffer.available());
        send_all_CAN_msgs(CAN2_txBuffer, &TEST_CAN2);

        Serial.println("can2 tx buffer size: (should be 0)");

        Serial.println(CAN2_txBuffer.available());
        Serial.println("sent on can2");
        delay(10);
        Serial.println("can1 rx buffer size: (should be 1) ");
        Serial.print(CAN1_rxBuffer.available());
        Serial.println();
        process_ring_buffer(CAN1_rxBuffer, CAN_interfaces, 1000);

        Serial.println("sent on can2");
        Serial.println("can1 rx buffer size: (should be 0) ");
        Serial.println(CAN1_rxBuffer.available());

        Serial.println("======= TEST 4 =======");

        rl_inv.command_reset();
        send_all_CAN_msgs(CAN2_txBuffer, &TEST_CAN2);

        delay(10);
        CAN_message_t recvd_msg;
        uint8_t buf[sizeof(CAN_message_t)];
        CAN1_rxBuffer.pop_front(buf, sizeof(CAN_message_t));
        memmove(&recvd_msg, buf, sizeof(recvd_msg));
        if (recvd_msg.id == ID_MC3_SETPOINTS_COMMAND)
        {
            MC_setpoints_command msg;
            msg.load(recvd_msg.buf);
            if (msg.get_remove_error())
            {

                Serial.println("GOOD received correct inverter reset");
            }
        } else{

                Serial.println("ERROR didnt receive correct id");
                Serial.println(recvd_msg.id);
                Serial.println(ID_MC3_SETPOINTS_COMMAND);
        }
    }
}