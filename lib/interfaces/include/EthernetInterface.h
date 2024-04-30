#ifndef ETHERNETINTERFACE_H
#define ETHERNETINTERFACE_H

#include <stdint.h>
#include <QNEthernet.h>

namespace qn = qindesign::network;

namespace EthParams
{
    extern IPAddress ip_addr_;

    const IPAddress default_MCU_ip(192, 168, 1, 30);
    const IPAddress default_TCU_ip(192, 168, 1, 69);

    const uint16_t default_protobuf_port = 2000;

    const IPAddress default_netmask(255, 255, 255, 0);
    const IPAddress default_gateway(192, 168, 0, 1);

    const uint16_t default_buffer_size = 512;
}

void init_ethernet_device(IPAddress ip);

const uint16_t pb_port = 2000;

class EthernetInterface
{
private:
    uint8_t ethernet_rx_buffer[EthParams::default_buffer_size];

    qn::EthernetUDP protobuf_socket;

public:
    EthernetInterface() {}

    void initialize_sockets()
    {
        protobuf_socket.begin(EthParams::default_protobuf_port);
    }

    void send(uint8_t *buf, uint16_t len);
    void receive();
};
#endif