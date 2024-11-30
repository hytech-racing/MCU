#include <Arduino.h>
// SPDX-FileCopyrightText: (c) 2022-2024 Shawn Silverman <shawn@pobox.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <algorithm>
#include <QNEthernet.h>
#include "MicroMetro.h"
#include "ethtest.h"

using namespace qindesign::network;

unsigned char src[] = {0x0, 0xe0, 0x4c, 0xef, 0xf8, 0x6};

// Custom EtherType constant
constexpr uint16_t kCustomEtherType = 0x8001;
uint32_t counter;
EthernetPacket frame;
int numFrames, framesSent, delayus, frameSize;
MicroMetro send_timer(100);

// Main program setup.
void setup()
{
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
    if (!Ethernet.begin())
    {
        printf("Failed to start Ethernet\r\n");
        return;
    }
    EthernetFrame.setReceiveQueueSize(256);

    const uint8_t destinationMAC[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    const uint8_t sourceMAC[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01};
    memcpy(frame.destinationMAC, destinationMAC, 6);
    memcpy(frame.sourceMAC, sourceMAC, 6);
    reverseEndianMemcpy(&(frame.ethertype), &kCustomEtherType, 2);
    frameSize = 64; // Default frame size
}

// Function to send Ethernet frames based on user input from Serial
void sendFrames()
{
    while (framesSent < numFrames && send_timer.check())
    {
        // Get the current time in microseconds
        frame.data.timestamp = (uint32_t) micros();
        frame.data.counter = counter++;
        EthernetFrame.send((const uint8_t *)&frame, 14 + frameSize);
        framesSent++;
        if (framesSent == numFrames)
        {
            Serial.printf("Done\n");
        }
    }
}

void readFrames()
{
    int size = EthernetFrame.parseFrame();
    if (size <= 0)
    {
        return;
    }
    if (size < EthernetFrame.minFrameLen() - 4)
    {
        printf("SHORT Frame[%d] \r\n", size);
        return;
    }

    const EthernetPacket *pkt = (const EthernetPacket *) EthernetFrame.data();

    printf("Frame[%d]: %d us\n", pkt->data.counter, micros()-pkt->data.timestamp);
}

void readSerial()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');

        // Assume user input in format: <frameCount> <delayTimeMicroseconds> <frameSize>
        int frameCount = 0;
        unsigned long delayTime = 0;

        if (sscanf(command.c_str(), "%d %lu %d", &frameCount, &delayTime, &frameSize) == 3)
        {
            Serial.printf("Sending %d frames with a delay of %lu microseconds and frame size of %d bytes.\r\n", frameCount, delayTime, frameSize);
            send_timer.interval(delayTime);
            send_timer.reset();
            framesSent = 0;
            numFrames = frameCount;
        }
        else
        {
            Serial.println("Invalid command format. Please use: <frameCount> <delayTimeMicroseconds> <frameSize>");
        }
    }
}

// Main program loop.
void loop()
{
    sendFrames();
    readFrames();
    readSerial();
}