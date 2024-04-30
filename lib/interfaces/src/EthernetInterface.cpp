// #include "EthernetInterface.h"

IPAddress ip_addr_;

void init_ethernet_device(IPAddress ip)
{
    ip_addr_ = ip;
    qn::Ethernet.begin(ip, EthParams::default_netmask, EthParams::default_gateway);
}

void EthernetInterface::send()
{
    int num = 3;
    IPAddress ip_2(192, 168, 0, 24);
    memcpy(ethernet_rx_buffer, &num, sizeof(num));
    protobuf_socket.send(ip_2, pb_port, ethernet_rx_buffer, sizeof(ethernet_rx_buffer));
}

void EthernetInterface::receive()
{

}