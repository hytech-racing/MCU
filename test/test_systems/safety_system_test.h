#ifndef __SAFETY_SYSTEM_TEST_H__
#define __SAFETY_SYSTEM_TEST_H__

#include <gtest/gtest.h>
#include "AMSInterface.h"
#include "WatchdogInterface.h"
#include "SafetySystem.h"
#include "SysClock.h"


TEST(SafetySystemTest, test_software_shutdown) {
    // Initial tick
    SysTick_s tick_zero;
    tick_zero.millis = 100L;
    tick_zero.micros = 100000L;

    AMSInterface ams_interface(0, 0, 0, 0, 0, 0);
    WatchdogInterface wd_interface(0);
    SafetySystem safety_system(&ams_interface, &wd_interface);

    ams_interface.init(tick_zero);
    wd_interface.init(tick_zero.millis);
    safety_system.init();

    ASSERT_EQ(safety_system.get_software_is_ok(), true);

    // 10 milliseconds later
    SysTick_s tick_one;
    tick_one.millis = 110L;
    tick_one.micros = 110000L;
    ams_interface.set_heartbeat(tick_one.millis);
    
    safety_system.software_shutdown(tick_one);

    ASSERT_EQ(safety_system.get_software_is_ok(), true);

    // 1999 milliseconds later (should be within 2000ms window)
    SysTick_s tick_two;
    tick_two.millis = 2109L;
    tick_two.micros = 2109000L;

    safety_system.software_shutdown(tick_two);

    ASSERT_EQ(ams_interface.heartbeat_received(tick_two.millis), true);


    // 1999 milliseconds later (should fail)
    SysTick_s tick_three;
    tick_three.millis = 2110L;
    tick_three.micros = 2110000L;

    safety_system.software_shutdown(tick_three);

    ASSERT_EQ(ams_interface.heartbeat_received(tick_three.millis), false);

    ASSERT_EQ(safety_system.get_software_is_ok(), false);

}




#endif /* __SAFETY_SYSTEM_TEST_H__ */