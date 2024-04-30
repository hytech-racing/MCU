#include "EthernetInterface.h"

void init_ethernet_device()
{
    Ethernet.macAddress(mac_address);

    if (!Ethernet.begin())
    {
        Serial.println("Failed to start Ethernet");
    }
}