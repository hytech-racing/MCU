#ifndef ETHERNETINTERFACE
#define ETHERNETINTERFACE
#include <QNEthernet.h>

#include "circular_buffer.h"



class EthernetInterface
{
public:
    EthernetInterface() {};
    void begin(int port);
    /// @brief sends all udp packets in queue
    void handle_sending();
    /// @brief receives all udp packets
    void handle_recvs();

private:
    EthernetUDP udp_ethernet_;
}

#endif