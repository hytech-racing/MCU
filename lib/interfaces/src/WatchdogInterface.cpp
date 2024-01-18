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

/*  */
// void SafetyInterface::set_software_is_ok() {
//     mcu_->mcu_status.set_software_is_ok(true);
// }

// void SafetyInterface::set_software_is_not_ok() {
//     mcu_->mcu_status.set_software_is_ok(false);
// }

void WatchdogInterface::kick_watchdog(unsigned long curr_time) {
    if ((curr_time - watchdog_time) > WATCHDOG_KICK_INTERVAL) {
        watchdog_state = !watchdog_state;
        digitalWrite(WATCHDOG_INPUT, watchdog_state);
        watchdog_time = curr_time;
    }
}

// bool SafetyInterface::software_is_ok() {
//     return mcu_->mcu_status.get_software_is_ok();
// }