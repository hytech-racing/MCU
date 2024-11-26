#include <Arduino.h>
// SPDX-FileCopyrightText: (c) 2022-2024 Shawn Silverman <shawn@pobox.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

// RawFrameMonitor prints all unknown raw Ethernet frames. Known frame
// types won't be printed if the associated features are enabled and
// there's a handler for them. These may include:
// 1. IPv4 (0x0800)
// 2. ARP  (0x0806)
// 3. IPv6 (0x86DD) (if enabled)
//
// Currently, in order to receive frames not addressed to the device's
// MAC address or to a subscribed multicast address, the destination
// address must be tagged as "allowed" by calling
// `Ethernet.setMACAddressAllowed(mac, flag)`. Alternatively, enable
// promiscuous mode by defining the QNETHERNET_ENABLE_PROMISCUOUS_MODE
// macro.
//
// In order to use this example, define the
// QNETHERNET_ENABLE_RAW_FRAME_SUPPORT macro.
//
// Note: the configuration macros must either be defined in the project build
//       options or in the qnethernet_opts.h library file.
//
// This file is part of the QNEthernet library.

// C++ includes
#include <algorithm>

#include <QNEthernet.h>

using namespace qindesign::network;

// VLAN EtherType constants
constexpr uint16_t kEtherTypeVLAN = 0x8100u;
constexpr uint16_t kEtherTypeQinQ = 0x88A8u;

// We can access the frame's internal data buffer directly,
// so we don't need the following:
// // Buffer for reading frames.
// uint8_t buf[EthernetFrame.maxFrameLen()];

// Tracks the received frame count.
int frameCount = 0;

// Main program setup.
void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 4000) {
    // Wait for Serial
  }
  printf("Starting...\r\n");

  // Print the MAC address
  uint8_t mac[6];
  Ethernet.macAddress(mac);  // This is informative; it retrieves, not sets
  printf("MAC = %02x:%02x:%02x:%02x:%02x:%02x\r\n",
         mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  // Add listeners before starting Ethernet

  Ethernet.onLinkState([](bool state) {
    printf("[Ethernet] Link %s\r\n", state ? "ON" : "OFF");
  });

  Ethernet.onAddressChanged([]() {
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
    }
  });

  // Initialize Ethernet
  // Optionally turn DHCP off by uncommenting the following line:
  // Ethernet.setDHCPEnabled(false);
  printf("Starting Ethernet%s...\r\n",
         Ethernet.isDHCPEnabled() ? " with DHCP" : "");
  if (!Ethernet.begin()) {
    printf("Failed to start Ethernet\r\n");
    return;
  }
}

// Main program loop.
void loop() {
  // Example MAC addresses (replace with arbitrary MAC addresses as needed)
  const uint8_t destinationMAC[6] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
  const uint8_t sourceMAC[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01};
  // Example EtherType (e.g., IPv4)
  constexpr uint16_t etherType = 0x0800; 

  if (Serial.available())
  {
    int c = Serial.read();
    if (c == 'b')
    {
      int starttime = millis();
      //for (size_t i = 0; i < 1000; i++)
      while (millis()-starttime < 1000)
      {
        
        EthernetFrame.beginFrame(destinationMAC, sourceMAC, etherType);
        EthernetFrame.print("123123123132123123123132123123123132123123123132");
        if (!EthernetFrame.endFrame()) {
          break;
        }
        delayMicroseconds(50);
      }
      Serial.println("done");
    }
    
  }
  

  // Updated code
  //EthernetFrame.beginFrame(destinationMAC, sourceMAC, etherType);
  //EthernetFrame.print("123123123132");
  //EthernetFrame.endFrame();
  //delay(1000);
  //Serial.println("test");
}