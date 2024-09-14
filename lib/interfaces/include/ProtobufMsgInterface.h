#ifndef PROTOBUFMSGINTERFACE
#define PROTOBUFMSGINTERFACE

#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "circular_buffer.h"
#include "NativeEthernet.h"
#include "MCU_rev15_defs.h"
#include "InterfaceParams.h"

struct ETHInterfaces
{
};

using recv_function_t = void (*)(const uint8_t* buffer, size_t packet_size, ETHInterfaces& interfaces);

// this should be usable with arbitrary functions idk something
void handle_ethernet_socket_receive(EthernetUDP* socket, recv_function_t recv_function, ETHInterfaces& interfaces)
{
    int packet_size = socket->parsePacket();
    if(packet_size > 0)
    {
        Serial.println("packet size");
        Serial.println(packet_size);
        uint8_t buffer[EthParams::default_buffer_size];
        size_t read_bytes = socket->read(buffer, sizeof(buffer));
        socket->read(buffer, UDP_TX_PACKET_MAX_SIZE);
        recv_function(buffer, read_bytes, interfaces);
    }
}

template <typename pb_struct>
bool handle_ethernet_socket_send_pb(EthernetUDP* socket, const pb_struct& msg, const pb_msgdesc_t* msg_desc)
{
    socket->beginPacket(EthParams::default_TCU_ip, EthParams::default_protobuf_send_port);
    
    uint8_t buffer[EthParams::default_buffer_size];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    if (!pb_encode(&stream, msg_desc, &msg)) {
        // You can handle error more explicitly by looking at stream.errmsg
        return false;
    }
    auto message_length = stream.bytes_written;
    socket->write(buffer, message_length);
    socket->endPacket();
    return true;
}


template <typename pb_msg_type>
std::pair<pb_msg_type, bool> recv_pb_stream_msg(const uint8_t *buffer, size_t packet_size, ETHInterfaces& interfaces, const pb_msgdesc_t * desc_pointer)
{
    pb_istream_t stream = pb_istream_from_buffer(buffer, packet_size);
    pb_msg_type msg = {};
    if (pb_decode(&stream, desc_pointer, &msg))
    {
        return {msg, true};
    }
    return {msg, };
}



#endif