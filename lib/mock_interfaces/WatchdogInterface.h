#ifndef __WATCHDOG_INTERFACE_H__
#define __WATCHDOG_INTERFACE_H__

#include "SysClock.h"
const unsigned long WATCHDOG_KICK_INTERVAL = 7;    // milliseconds

class WatchdogInterface
{
private:
    /* Watchdog last kicked time */
    unsigned long watchdog_time;

    /* Watchdog output state */
    bool watchdog_state;

    /* Hardware interface pins */
    int pin_watchdog_input_;
    
public:
    WatchdogInterface(int wd_input_pin){};

    /* Initialize interface pin mode */
    void init(unsigned long curr_millis) {return;};

    /* Write to Main ECU */
    // Initialize output value
    void set_start_state() {return;};

    /* Kick watchdog */
    void kick_watchdog(unsigned long curr_millis) {};

};

#endif /* __WATCHDOG_INTERFACE_H__ */
