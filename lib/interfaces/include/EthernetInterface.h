#ifndef ETHERNETINTERFACE
#define ETHERNETINTERFACE

#include <Arduino.h>
#include <stdint.h>
#include "ht_msgs.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "ParamMsgInterface.h"
#include <QNEthernet.h>

uint8_t union_port_ethernet_buffer[512];

IPAddress ip_addr;
uint8_t mac_address[6];
bool connection_successful = false;

void init_ethernet_device(IPAddress ip);

/*
    The UDPSocket class holds a reference to the
    individual EthernetUDP socket. It is constructed
    using a port which the UDP socket will use
    when it is initialized. 
    Importantly, this must be done after the ethernet
    device is initialized with init_ethernet_device();
*/
class UDPSocket
{
private:
    EthernetUDP udp_;
    const uint16_t port_;
public:
    UDPSocket(uint16_t port): port_(port) {};

    /* Must be called in setup() to communicate with socket */
    void initialize_socket() {udp_.begin(port_)}

    /**
     * @brief Sends a udp packet from the provided buffer
     * @param data a constant uint8_t pointer to the data buffer
     * @param len the length of the data in the buffer to send
     * @return Returns a bool for if the buffer was sent successfully
    */
    bool send(const uint8_t *data, int len);

    /**
     * @brief Receives a udp packet, will return the size of packets received
     *         and move the data to the location of the buffer pointer passed in
     * @param data a uint8_t pointer to the data buffer to fill
     * @return Returns the size of the received packet, or -1 when there
     *         are no more packets available on the socket
    */
    int receive(uint8_t *data);
}

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