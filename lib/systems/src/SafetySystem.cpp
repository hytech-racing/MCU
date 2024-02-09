#include "SafetySystem.h"

/* Initialize SafetySystem */
void SafetySystem::init() {
    // Initialize interface output
    ams_->set_start_state();    
    wd_->set_start_state();
    // Initial state is ok
    software_is_ok = true;
}

/* Monitor AMS heartbeat and kick watchdog */
void SafetySystem::software_shutdown(const SysTick_s &tick) {
    software_is_ok = true;

    // If AMS heartbeat is not received within reasonable interval
    // Set software is not ok
    if (!ams_->heartbeat_received()) {
        software_is_ok = false;
    }
    if (software_is_ok)
        ams_->set_state_ok_high(true);
    else
        ams_->set_state_ok_high(false);

    // Kick watchdog every software cycle
    wd_->kick_watchdog(tick);
}

/* Return software ok */
bool SafetySystem::get_software_is_ok() {
    return software_is_ok;
}