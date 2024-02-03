#ifndef __WATCHDOG_INTERFACE_H__
#define __WATCHDOG_INTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "SysClock.h"

const unsigned long WATCHDOG_KICK_INTERVAL = 7    // milliseconds

class WatchdogInterface
{
public:
    WatchdogInterface(int wd_input_pin): pin_watchdog_input_(wd_input_pin) {};

    /* Initialize interface pin mode */
    void init(const SysTick_s &tick);

    /* Write to Main ECU */
    // Initialize output value
    void set_start_state();

    /* Kick watchdog */
    void kick_watchdog(const SysTick_s &tick);


private:
    /* Watchdog last kicked time */
    unsigned long watchdog_time;

    /* Watchdog output state */
    bool watchdog_state;

    /* Hardware interface pins */
    int pin_watchdog_input_;

};

#endif /* __WATCHDOG_INTERFACE_H__ */
