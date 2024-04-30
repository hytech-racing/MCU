#ifndef ETHERNETINTERFACE
#define ETHERNETINTERFACE

#include <Arduino.h>
#include "ht_msgs.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "ParamMsgInterface.h"
#include <QNEthernet.h>

uint8_t union_port_ethernet_buffer[512];
// EthernetUDP udp_ethernet;

void init_ethernet_device();
/// @brief sends all udp packets in queue
void handle_sending();
/// @brief receives all udp packets
void handle_recvs();

template <struct interface, struct msg_struct>
void append_to_interface_queue(interface * msg_interface_queue, msg_struct msg)
{
    uint8_t buf[sizeof(msg)];
    memmove(buf, &msg, sizeof(msg))
    msg_interface_queue->push_back(buf, sizeof(msg_struct));
}

void handle_pb_stream_union_msg(pb_istream_t *stream)
{
    ht_eth_big_union msg = ht_eth_big_union_init_zero;
    if(pb_decode(stream, ht_eth_big_union_fields, &msg))
    {
        switch(msg.which_msg)
        {
            case ht_eth_big_union_config_msg_tag:
                ht_eth_config cfg_msg = msg.msg.config_msg;
                uint8_t buf[sizeof(cfg_msg)];
                memmove(buf, &cfg_msg, sizeof(cfg_msg))
                param_msg_interface->push_back(buf, sizeof(ht_eth_config));
                break;
        }
    }
}

void process_ethernet_port_buffer()
{
    // get the number of msgs in the queue to be de-serialized
    while(union_port.available())
    {
        int size = union_port.parsePacket();
        if(size > 0)
        {
            union_port.read(union_port_ethernet_buffer, size);
            pb_istream_t stream = pb_istream_from_buffer(union_port_ethernet_buffer, size);
            handle_pb_stream_union_msg(&stream);
        }
    }
}

template <typename message_queue>
struct ETHInterfaces
{
    ParamMsgInterface<message_queue> *param_msg_interface;
};
#endif