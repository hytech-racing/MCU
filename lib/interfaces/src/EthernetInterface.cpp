#include "EthernetInterface.h"

void init_ethernet_device(IPAddress ip)
{
    ip_addr = ip;

    Ethernet.macAddress(mac_address);

    if (!Ethernet.begin(mac_address, ip))
    {
        Serial.println("Failed to start Ethernet");
    } else {connection_successful = true;}
}

bool UDPSocket::send(const uint8_t *data, int len)
{

}

int UDPSocket::receive(uint8_t *data)
{
    
}