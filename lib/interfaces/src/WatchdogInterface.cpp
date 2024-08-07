#include "WatchdogInterface.h"

void WatchdogInterface::init(unsigned long curr_millis)
{
    // Set pin mode        
    pinMode(pin_watchdog_input_, OUTPUT);

    watchdog_time_ = curr_millis;
    set_watchdog_state(HIGH);
}

void WatchdogInterface::kick_watchdog(unsigned long curr_millis)
{

    if ((curr_millis - watchdog_time_) > WATCHDOG_KICK_INTERVAL) {
        set_watchdog_state(!watchdog_state_);
        digitalWrite(pin_watchdog_input_, watchdog_state_);
        set_watchdog_time(curr_millis);
    }

}
