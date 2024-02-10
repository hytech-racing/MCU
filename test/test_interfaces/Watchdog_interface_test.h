#include <Arduino.h>
#include <unity.h>

#include "WatchdogInterface.h"

void test_watchdog_kick()
{
    // Hypothetical pin setup
    WatchdogInterface wd_interface(1);
    wd_interface.init(0);
    TEST_ASSERT_EQUAL(HIGH, wd_interface.get_watchdog_state());

}