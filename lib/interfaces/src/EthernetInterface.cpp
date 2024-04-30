#include "EthernetInterface.h"

IPAddress ip_addr_;

void init_ethernet_device(IPAddress ip)
{
    ip_addr_ = ip;
    
    qn::Ethernet.begin(ip, EthParams::default_netmask, EthParams::default_gateway);
}

void EthernetInterface::send(uint8_t *buf, uint16_t len)
{
    protobuf_socket.send(EthParams::default_TCU_ip, pb_port, buf, len);
}

void EthernetInterface::receive()
{

    

}