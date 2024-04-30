#ifndef PROTOBUFMSGINTERFACE
#define PROTOBUFMSGINTERFACE

#include "ht_msgs.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "ParameterInterface.h"

struct ETHInterfaces
{
    ParameterInterface* param_interface;
};

void handle_pb_stream_union_msg(pb_istream_t *stream, ETHInterfaces& interfaces)
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

#endif