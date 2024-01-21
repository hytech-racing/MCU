#include "WatchdogInterface.h"

/* Static members */
bool WatchdogInterface::watchdog_state = HIGH;

void WatchdogInterface::init() {
    // set_software_is_ok();

    pinMode(WATCHDOG_INPUT, OUTPUT);
    // pinMode(SOFTWARE_OK, OUTPUT);

    // digitalWrite(WATCHDOG_INPUT, HIGH);
    // digitalWrite(SOFTWARE_OK, HIGH);
}

void WatchdogInterface::set_start_state() {
    digitalWrite(WATCHDOG_INPUT, HIGH);
}

void WatchdogInterface::kick_watchdog(unsigned long curr_time) {
    if ((curr_time - watchdog_time) > WATCHDOG_KICK_INTERVAL) {
        watchdog_state = !watchdog_state;
        digitalWrite(WATCHDOG_INPUT, watchdog_state);
        watchdog_time = curr_time;
    }
}


