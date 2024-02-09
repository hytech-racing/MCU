#ifndef __WATCHDOG_INTERFACE_H__
#define __WATCHDOG_INTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

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
    WatchdogInterface(int wd_input_pin): pin_watchdog_input_(wd_input_pin)
    {
        // Set pin mode        
        pinMode(pin_watchdog_input_, OUTPUT);
    };

    /* Initialize interface pin mode */
    void init(unsigned long curr_millis);

    /* Write to Main ECU */
    // Initialize output value
    void set_start_state();

    /* Kick watchdog */
    void kick_watchdog(unsigned long curr_millis);

};

#endif /* __WATCHDOG_INTERFACE_H__ */
