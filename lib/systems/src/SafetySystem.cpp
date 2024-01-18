#include "SafetySystem.h"

void SafetySystem::init() {
    software_ok_init();
    watchdog_init();
}

void SafetySystem::software_ok_init() {
    ams_->set_start_state();
    ams_->set_software_is_ok();
}

void SafetySystem::watchdog_init() {
    wd_->set_start_state();
}

void SafetySystem::software_shutdown() {
    ams_->set_software_is_ok();

    if (!ams_->heartbeat_received(millis())) {
        ams_->set_software_is_not_ok();
    }

    if (ams_->software_is_ok())
        ams_->set_state_ok_high(true);
    else
        ams_->set_state_ok_high(false);

    wd_->kick_watchdog(millis());
}