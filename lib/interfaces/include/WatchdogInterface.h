#ifndef __WATCHDOG_INTERFACE_H__
#define __WATCHDOG_INTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

#define WATCHDOG_INPUT  32

#define WATCHDOG_KICK_INTERVAL  7    // milliseconds

class WatchdogInterface
{
public:
    WatchdogInterface() = default;
    // WatchdogInterface(): watchdog_state(HIGH) {};

    /* Initialize interface pin mode */
    void init(unsigned long curr_time);

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
