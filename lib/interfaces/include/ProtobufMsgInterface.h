#ifndef PROTOBUFMSGINTERFACE
#define PROTOBUFMSGINTERFACE

#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "circular_buffer.h"
#include <QNEthernet.h>

#include <functional>

struct ETHInterfaces
{
};

// this should be usable with arbitrary functions idk something
template <size_t buffer_size, typename pb_msg_type, class eth_interface>
void handle_ethernet_socket_receive(const SysTick_s& tick, qindesign::network::EthernetUDP *socket, std::function<void(unsigned long, const uint8_t *, size_t, eth_interface &, const pb_msgdesc_t *)> recv_function, eth_interface &interface, const pb_msgdesc_t *desc_pointer)
{
    int packet_size = socket->parsePacket();
    if (packet_size > 0)
        {
        uint8_t buffer[buffer_size];
        size_t read_bytes = socket->read(buffer, sizeof(buffer));
        socket->read(buffer, buffer_size);
        recv_function(tick.millis, buffer, read_bytes, interface, desc_pointer);
    }
}

template <typename pb_struct, size_t buffer_size>
bool handle_ethernet_socket_send_pb(IPAddress addr, uint16_t port, qindesign::network::EthernetUDP *socket, const pb_struct &msg, const pb_msgdesc_t *msg_desc)
{
    socket->beginPacket(addr, port);
    uint8_t buffer[buffer_size];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    if (!pb_encode(&stream, msg_desc, &msg))
    {
        // You can handle error more explicitly by looking at stream.errmsg
        return false;
    }
    auto message_length = stream.bytes_written;
    socket->write(buffer, message_length);
    socket->endPacket();
    return true;
}

template <typename pb_msg_type, class eth_interface>
void recv_pb_stream_msg(unsigned long curr_millis, const uint8_t *buffer, size_t packet_size, eth_interface &interface, const pb_msgdesc_t *desc_pointer)
{
    pb_istream_t stream = pb_istream_from_buffer(buffer, packet_size);
    pb_msg_type msg = {};
    if (pb_decode(&stream, desc_pointer, &msg))
    {
        interface.receive_pb_msg(msg, curr_millis);
    }
}

#endif