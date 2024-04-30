#ifndef ETHERNETINTERFACE
#define ETHERNETINTERFACE

#include <Arduino.h>
#include <QNEthernet.h>

EthernetUDP udp_ethernet;

void init_ethernet_device();
/// @brief sends all udp packets in queue
void handle_sending();
/// @brief receives all udp packets
void handle_recvs();

#endif