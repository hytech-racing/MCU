#include <Arduino.h>
#include <unity.h>

#include "WatchdogInterface.h"

void test_watchdog_kick()
{
    // Hypothetical pin setup
    WatchdogInterface wd_interface(1);
    wd_interface.init(millis());
    TEST_ASSERT_EQUAL(HIGH, wd_interface.get_watchdog_state());
    delay(5);
    wd_interface.kick_watchdog(millis());
    TEST_ASSERT_EQUAL(HIGH, wd_interface.get_watchdog_state());
    delay(5);
    wd_interface.kick_watchdog(millis());
    TEST_ASSERT_EQUAL(LOW, wd_interface.get_watchdog_state());

}