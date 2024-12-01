#include <Arduino.h>
// SPDX-FileCopyrightText: (c) 2022-2024 Shawn Silverman <shawn@pobox.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <algorithm>
#include <QNEthernet.h>

#include "ethtest.h"
#include "InterfaceParams.h"

using namespace qindesign::network;

unsigned char src[] = {0x0, 0xe0, 0x4c, 0xef, 0xf8, 0x6};

// Custom EtherType constant
constexpr uint16_t kCustomEtherType = 0x8001;

EthernetUDP socket(256);

// Main program setup.
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    while (!Serial && millis() < 4000)
    {
        // Wait for Serial
    }
    printf("Starting...\r\n");

    // Print the MAC address
    uint8_t mac[6];
    Ethernet.macAddress(mac);
    printf("MAC = %02x:%02x:%02x:%02x:%02x:%02x\r\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // Add listeners before starting Ethernet
    Ethernet.onLinkState([](bool state)
                         { printf("[Ethernet] Link %s\r\n", state ? "ON" : "OFF"); });

    Ethernet.onAddressChanged([]()
                              {
    IPAddress ip = Ethernet.localIP();
    bool hasIP = (ip != INADDR_NONE);
    if (hasIP) {
      IPAddress subnet = Ethernet.subnetMask();
      IPAddress broadcast = Ethernet.broadcastIP();
      IPAddress gw = Ethernet.gatewayIP();
      IPAddress dns = Ethernet.dnsServerIP();

      printf("[Ethernet] Address changed:\r\n"
             "    Local IP     = %u.%u.%u.%u\r\n"
             "    Subnet       = %u.%u.%u.%u\r\n"
             "    Broadcast IP = %u.%u.%u.%u\r\n"
             "    Gateway      = %u.%u.%u.%u\r\n"
             "    DNS          = %u.%u.%u.%u\r\n",
             ip[0], ip[1], ip[2], ip[3],
             subnet[0], subnet[1], subnet[2], subnet[3],
             broadcast[0], broadcast[1], broadcast[2], broadcast[3],
             gw[0], gw[1], gw[2], gw[3],
             dns[0], dns[1], dns[2], dns[3]);
    } else {
      printf("[Ethernet] Address changed: No IP address\r\n");
    } });

    // Initialize Ethernet
    printf("Starting Ethernet%s...\r\n",
           Ethernet.isDHCPEnabled() ? " with DHCP" : "");
    Ethernet.begin(EthParams::default_VCR_MAC_address,EthParams::default_VCR_ip);
    socket.beginWithReuse(2000);
}

void readFrame()
{
    int packetSize = socket.parsePacket();
    if (packetSize >= 0) {  // non_negative_value >= 0
        digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ? 0 : 1);
        socket.send(EthParams::default_MCU_ip, 2000, socket.data(), packetSize);
    }
}

// Main program loop.
void loop()
{
    readFrame();
}