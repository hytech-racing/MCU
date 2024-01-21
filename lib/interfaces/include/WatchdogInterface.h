#ifndef __WATCHDOG_INTERFACE_H__
#define __WATCHDOG_INTERFACE_H__

#include "MCUInterface.h"

// #define SOFTWARE_OK     28
#define WATCHDOG_INPUT  32

#define WATCHDOG_KICK_INTERVAL  7    // milliseconds

class WatchdogInterface
{
public:
    WatchdogInterface(MCUInterface *mcu): mcu_(mcu), watchdog_time(millis()) {};

    void init();

    void set_start_state();

    void kick_watchdog(unsigned long curr_time);


private:
    MCUInterface *mcu_;
    unsigned long watchdog_time;
    static bool watchdog_state;

};




#endif /* __WATCHDOG_INTERFACE_H__ */
