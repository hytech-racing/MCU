#include "WatchdogInterface.h"

/* Pin mode output to watchdog WD */
void WatchdogInterface::init(unsigned long curr_millis) {
    // Set pin mode        
    pinMode(pin_watchdog_input_, OUTPUT);

    watchdog_time = curr_millis;
    set_watchdog_state(HIGH);

}

/* Initial output to watchdog WD */
void WatchdogInterface::set_start_state() {

    digitalWrite(pin_watchdog_input_, HIGH);
    
}

/* Toggle watchdog WD to kick dog */
void WatchdogInterface::kick_watchdog(unsigned long curr_millis) {

    unsigned long before_print = millis();
    if (watchdog_chillin) Serial.printf("wd ms %d\n", curr_millis - watchdog_time);
    unsigned long after_print = millis();
    if ((after_print - before_print) > 50) Serial.println(after_print - before_print);
    
    // if ((curr_millis - watchdog_time) > 15) {
    //     Serial.printf("wd ms %d\n", curr_millis - watchdog_time);
    //     watchdog_chillin = false;
    // }

    if ((curr_millis - watchdog_time) > WATCHDOG_KICK_INTERVAL) {
        watchdog_state = !watchdog_state;
        digitalWrite(pin_watchdog_input_, watchdog_state);
        watchdog_time = curr_millis;
    }

}

/* Get interface status */
bool WatchdogInterface::get_watchdog_state() {
    return watchdog_state;
}

/* Set interface status */
void WatchdogInterface::set_watchdog_state(bool state) {
    watchdog_state = state;
}

