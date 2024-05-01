#ifndef TEST_ETHERNET
#define TEST_ETHERNET

#include <Arduino.h>
#include <unity.h>

#include "ProtobufMsgInterface.h"
#include "MCU_rev15_defs.h"

EthernetUDP protobuf_socket;
ParameterInterface params;
ETHInterfaces ethernet_interfaces = {&params};

void init_ethernet_device()
{
    Ethernet.begin(EthParams::default_MCU_MAC_address, EthParams::default_MCU_ip);
    protobuf_socket.begin(EthParams::default_protobuf_port);
}

void test_ethernet()
{
    while(1)
    {
        handle_ethernet_socket_receive(&protobuf_socket, &recv_pb_stream_union_msg, ethernet_interfaces);
        Serial.println(params.get_config().CASE_TORQUE_MAX);
        // Serial.println("asdf");
    }
    
    TEST_ASSERT_EQUAL(1, 1);
}

#endif