#include <Arduino.h>
#include <unity.h>

#include "AMS_interface_test.h"
#include "dashboard_interface_test.h"
#include "Watchdog_interface_test.h"
#include "can_interface_test.h"

void setUp(void)
{
    init_can_interface();
}

void tearDown(void)
{

}

int runUnityTests(void) 
{
    UNITY_BEGIN();
    /* TEST DASHBOARD */
    RUN_TEST(test_dashboard_unpacking_can_message);
    RUN_TEST(test_dashboard_circular_buffer);
    /* TEST AMS */
    RUN_TEST(test_AMS_heartbeat);
    /* TEST WATCHDOG */
    RUN_TEST(test_watchdog_kick);
    // testing can interface
    RUN_TEST(test_can_interface_send)
    RUN_TEST(test_can_interface_send_and_receive_raw)

    return UNITY_END();
}

void setup() 
{
    delay(500);

    runUnityTests();
}

void loop() {}