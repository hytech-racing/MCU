#ifndef PROTOBUFMSGINTERFACE
#define PROTOBUFMSGINTERFACE

#include "ht_msgs.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "ParameterInterface.h"
#include "circular_buffer.h"
#include "NativeEthernet.h"
#include "MCU_rev15_defs.h"


struct ETHInterfaces
{
    ParameterInterface* param_interface;
};

using recv_function_t = void (*)(const uint8_t* buffer, size_t packet_size, ETHInterfaces& interfaces);

// this should be usable with arbitrary functions idk something
void handle_ethernet_socket_receive(EthernetUDP* socket, recv_function_t recv_function, ETHInterfaces& interfaces)
{
    int packet_size = socket->parsePacket();
    if(packet_size > 0)
    {
        // Serial.println("packet size");
        // Serial.println(packet_size);
        uint8_t buffer[EthParams::default_buffer_size];
        size_t read_bytes = socket->read(buffer, sizeof(buffer));
        socket->read(buffer, UDP_TX_PACKET_MAX_SIZE);
        recv_function(buffer, read_bytes, interfaces);
    }
}

void recv_pb_stream_union_msg(const uint8_t *buffer, size_t packet_size, ETHInterfaces& interfaces)
{
    pb_istream_t stream = pb_istream_from_buffer(buffer, packet_size);
    // Serial.println("running the function");
    HT_ETH_Union msg = HT_ETH_Union_init_zero;
    if (pb_decode(&stream, HT_ETH_Union_fields, &msg))
    {
        // Serial.println("decoded!");

        switch (msg.which_type_union)
        {
        case HT_ETH_Union_config__tag:
            interfaces.param_interface->update_config(msg.type_union.config_);
            break;
        default:
            break;
        }
    }
}



#endif