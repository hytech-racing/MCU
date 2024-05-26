#ifndef PROTOBUFMSGINTERFACE
#define PROTOBUFMSGINTERFACE

#include "ht_eth.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "ParameterInterface.h"
#include "circular_buffer.h"
// #include "NativeEthernet.h"
#include "QNEthernet.h"
#include "MCU_rev15_defs.h"

namespace qn = qindesign::network;

struct ETHInterfaces
{
    ParameterInterface* param_interface;
};

using recv_function_t = void (*)(const uint8_t* buffer, size_t packet_size, ETHInterfaces& interfaces);

// this should be usable with arbitrary functions idk something
void handle_ethernet_socket_receive(qn::EthernetUDP* socket, recv_function_t recv_function, ETHInterfaces& interfaces)
{
    int packet_size = socket->parsePacket();
    if(packet_size > 0)
    {
        // Serial.println("packet size");
        // Serial.println(packet_size);
        uint8_t buffer[EthParams::default_buffer_size];
        size_t read_bytes = socket->read(buffer, sizeof(buffer));
        socket->read(buffer, EthParams::default_buffer_size);
        recv_function(buffer, read_bytes, interfaces);
    }
}

template <typename pb_struct>
bool handle_ethernet_socket_send_pb(qn::EthernetUDP* socket, const pb_struct& msg, const pb_msgdesc_t* msg_desc)
{
    socket->beginPacket(EthParams::default_TCU_ip, EthParams::default_protobuf_send_port);
    
    uint8_t buffer[EthParams::default_buffer_size];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    if (!pb_encode(&stream, msg_desc, &msg)) {
        // You can handle error more explicitly by looking at stream.errmsg
        Serial.println("error couldnt encode");
        return false;
    }
    auto message_length = stream.bytes_written;
    socket->write(buffer, message_length);
    socket->endPacket();
    
    return true;
}

// 
void recv_pb_stream_union_msg(const uint8_t *buffer, size_t packet_size, ETHInterfaces& interfaces)
{
    pb_istream_t stream = pb_istream_from_buffer(buffer, packet_size);
    HT_ETH_Union msg = HT_ETH_Union_init_zero;
    if (pb_decode(&stream, HT_ETH_Union_fields, &msg))
    {
        // Serial.println("decoded!");

        switch (msg.which_type_union)
        {
        case HT_ETH_Union_config__tag:
            interfaces.param_interface->update_CASE_config(msg.type_union.config_);
            break;
        case HT_ETH_Union_get_config__tag:
            interfaces.param_interface->set_params_need_sending();
            break;
        default:
            break;
        }
    }
}



#endif