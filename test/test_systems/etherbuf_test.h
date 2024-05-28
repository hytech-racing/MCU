#include "etherbuf.h"

HTE_can_tunnel lastReceived;
HTE_em_measurement lastReceived2;

void etherbufCANHandler(HTE_can_tunnel* can_tunnel)
{
    lastReceived = *can_tunnel;
}

void etherbufEMMeasurementHandler(HTE_em_measurement* EMWrapper)
{
    lastReceived2 = *EMWrapper;
}

TEST(EtherbufTesting, etherbuf_simple_serdes)
{
    Etherbuf eb;
    HTE_can_tunnel message;
    const int sizeOfBuffer = 1000;
    char buffer[sizeOfBuffer] = {0};
    eb.registerHandler_can_tunnel((void*)&etherbufCANHandler);
    eb.registerHandler_em_measurement((void*)&etherbufEMMeasurementHandler);

    // pack 2 messages
    message.messages_count = 2;
    message.timestamp = 0;
    message.messages[0] = (_HTE_can_tunnel_CANMessage)
    {
        .id = 0x10,
        .data = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8}
    };
    message.messages[1] = (_HTE_can_tunnel_CANMessage)
    {
        .id = 0x20,
        .data = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x00}
    };

    size_t bytes_written = eb.toEtherbuf_can_tunnel(buffer, sizeOfBuffer, message);
    // With ethernet you'd pass the size of the packet in place of `bytes_written`
    eb.handleIncomingMessage(buffer, bytes_written);

    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(lastReceived.messages[i].id, message.messages[i].id);
        for (int j = 0; j < 8; j++)
        {
            EXPECT_EQ(lastReceived.messages[i].data[j], message.messages[i].data[j]);
        }
    }

    // pack a message with a different ID
    HTE_em_measurement message2;
    message2.em_current = 1234;
    message2.em_voltage = 5000;

    bytes_written = eb.toEtherbuf_em_measurement(buffer, sizeOfBuffer, message2);
    eb.handleIncomingMessage(buffer, bytes_written);

    EXPECT_EQ(message2.em_current, lastReceived2.em_current);
    EXPECT_EQ(message2.em_voltage, lastReceived2.em_voltage);
}