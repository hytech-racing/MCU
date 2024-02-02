#include "WatchdogInterface.h"

/* Pin mode output to watchdog WD */
void WatchdogInterface::init(const SysTick_s &tick) {
    watchdog_time = tick.millis;
    pinMode(pin_watchdog_input_, OUTPUT);
}

/* Initial output to watchdog WD */
void WatchdogInterface::set_start_state() {
    digitalWrite(pin_watchdog_input_, HIGH);
}

/* Toggle watchdog WD to kick dog */
void WatchdogInterface::kick_watchdog(const SysTick_s &tick) {
    if ((tick.millis - watchdog_time) > WATCHDOG_KICK_INTERVAL) {
        watchdog_state = !watchdog_state;
        digitalWrite(pin_watchdog_input_, watchdog_state);
        watchdog_time = tick.millis;
    }
}


