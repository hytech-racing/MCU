#ifndef __SAFETY_SYSTEM_TEST_H__
#define __SAFETY_SYSTEM_TEST_H__

#include <gtest/gtest.h>
#include "AMSInterface.h"
#include "WatchdogInterface.h"
#include "SafetySystem.h"
#include "SysClock.h"


TEST(SafetySystemTest, test_software_shutdown) {
    SysClock sys_clock;

    SysTick_s curr_tick = sys_clock.tick(0);

    AMSInterface ams_interface(0, 0, 0, 0, 0);
    WatchdogInterface wd_interface(0);
    SafetySystem safety_system(&ams_interface, &wd_interface);

    ams_interface.init(curr_tick.millis);
    wd_interface.init(curr_tick.millis);
    safety_system.init();

    ASSERT_EQ(safety_system.get_software_is_ok(), true);

    // 10 milliseconds later
    curr_tick = sys_clock.tick(10 * 1000);
    ams_interface.set_heartbeat(curr_tick.millis);
    
    safety_system.software_shutdown(curr_tick);

    ASSERT_EQ(safety_system.get_software_is_ok(), true);

    // 45 milliseconds later
    curr_tick = sys_clock.tick(45 * 1000);
    safety_system.software_shutdown(curr_tick);

    ASSERT_EQ(ams_interface.heartbeat_received(curr_tick.millis), false);

    ASSERT_EQ(safety_system.get_software_is_ok(), false);

}




#endif /* __SAFETY_SYSTEM_TEST_H__ */