#ifndef __WATCHDOG_INTERFACE_H__
#define __WATCHDOG_INTERFACE_H__

#include "MCUInterface.h"

// #define SOFTWARE_OK     28
#define WATCHDOG_INPUT  32

#define WATCHDOG_KICK_INTERVAL  7    // milliseconds

class WatchdogInterface
{
public:
    WatchdogInterface(): watchdog_time(millis()), watchdog_state(HIGH) {};

    /* Initialize interface pin mode */
    void init();

    /* Write to Main ECU */
    // Initialize output value
    void set_start_state();

    /* Kick watchdog */
    void kick_watchdog(unsigned long curr_time);


private:
    /* Watchdog last kicked time */
    unsigned long watchdog_time;

    /* Watchdog output state */
    bool watchdog_state;

};

#endif /* __WATCHDOG_INTERFACE_H__ */
