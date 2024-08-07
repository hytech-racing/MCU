#ifndef __WATCHDOG_INTERFACE_H__
#define __WATCHDOG_INTERFACE_H__

#include <Arduino.h>

/**
 * The interval at which we will kick the watchdog IC, in milliseconds.
 * Every WATCHDOG_KICK_INTERVAL, we either write the digital pin high
 * or low, so our actual period is 2 * WATCHDOG_KICK_INTERVAL.
 */
const unsigned long WATCHDOG_KICK_INTERVAL = 10;    // milliseconds

/**
 * Interface for Watchdog. Through WatchdogInterface, we can kick the watchdog
 * IC periodically. If the MCU stops sending a kick, then Watchdog will open
 * the shutdown circuit.
 */
class WatchdogInterface
{
private:
    /**
     * Watchdog last kicked time, in milliseconds
     */
    unsigned long watchdog_time_;

    /**
     * Watchdog current state (HIGH or LOW).
     */
    bool watchdog_state_;

    /**
     * Hardware interface pins.
     */
    int pin_watchdog_input_;
    
public:

    /**
     * Generic constructor for WatchdogInterface.
     * @param wd_input_pin The pin on the Teensy that connects to the Watchdog IC.
     */
    WatchdogInterface(int wd_input_pin):
        pin_watchdog_input_(wd_input_pin)
    {};

    /**
     * Initialize interface pin mode, sets the watchdog_time_ member variable to
     * curr_millis, and writes the watchdog_state_ HIGH.
     */
    void init(unsigned long curr_millis);

    /**
     * Writes the watchdog pin HIGH. Does not check if enough time has elapsed.
     */
    void set_start_state() {digitalWrite(pin_watchdog_input_, HIGH);}

    /**
     * Checks if enough time has elapsed. If so, then this toggles the watchdog_state_
     * member variable, writes the digital pin appropriately, and updates the
     * watchdog_time_ member variable.
     */
    void kick_watchdog(unsigned long curr_millis);

    /* ---------- Getters ---------- */
    bool get_watchdog_state() {return watchdog_state_;}
    unsigned long get_watchdog_time() {return watchdog_time_;}

    /* ---------- Setters ---------- */
    void set_watchdog_state(bool state) {watchdog_state_ = state;}
    void set_watchdog_time(unsigned long time) {watchdog_time_ = time;}

};

#endif /* __WATCHDOG_INTERFACE_H__ */
