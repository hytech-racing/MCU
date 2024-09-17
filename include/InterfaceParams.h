#ifndef INTERFACEPARAMS
#define INTERFACEPARAMS
#include "NativeEthernet.h"

namespace EthParams
{
    uint8_t default_MCU_MAC_address[6] = 
    {0x04, 0xe9, 0xe5, 0x10, 0x1f, 0x22};

    const IPAddress default_MCU_ip(192, 168, 1, 30);
    const IPAddress default_TCU_ip(192, 168, 1, 69);

    const uint16_t default_protobuf_send_port = 2001;
    const uint16_t default_protobuf_recv_port = 2000;

    const IPAddress default_netmask(255, 255, 255, 0);
    const IPAddress default_gateway(192, 168, 0, 1);

    const uint16_t default_buffer_size = 512;
}
#endif