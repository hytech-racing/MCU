#ifndef PROTOBUFMSGINTERFACE
#define PROTOBUFMSGINTERFACE

#include "ht_msgs.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "ParameterInterface.h"
#include "circular_buffer.h"


extern Circular_Buffer<uint8_t, (uint32_t)16, sizeof(ht_eth_big_union)> pb_tx_buffer;

struct ETHInterfaces
{
    ParameterInterface* param_interface;
};

void recv_pb_stream_union_msg(pb_istream_t *stream, ETHInterfaces& interfaces)
{
    ht_eth_big_union msg = ht_eth_big_union_init_zero;
    if (pb_decode(stream, ht_eth_big_union_fields, &msg))
    {
        switch (msg.which_msg)
        {
        case ht_eth_big_union_config_msg_tag:
            interfaces.param_interface->update_config(msg.msg.config_msg);
            break;
        default:
            break;
        }
    }
}

template <typename T, uint16_t _size, typename msg_type>
void send_pb_stream_msg(Circular_Buffer<T, _size, msg_type>& buffer, EthernetInterface *eth_int)
{
    while (buffer.available())
    {
        msg_type msg;
        uint8_t buf[sizeof(msg_type)];
        buffer.pop_front(buf, sizeof(msg_type));
        memmove(&msg, buf, sizeof(msg));
        // eth_int->send();
    }
}


#endif