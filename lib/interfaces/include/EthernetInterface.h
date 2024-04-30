#ifndef __ETHERNETINTERFACE_H__
#define __ETHERNETINTERFACE_H__

#include <Arduino.h>
#include "QNEthernet.h"

using namespace qindesign::network;

EthernetUDP udp;

uint8_t mac_address[6];

void init_ethernet_device();

#endif