#include <Arduino.h>
#include <unity.h>

#include "AMS_interface_test.h"
#include "dashboard_interface_test.h"
#include "Watchdog_interface_test.h"
#include "MCU_interface_test.h"
// #include "can_interface_test.h"

void setUp(void)
{
    // init_can_interface();
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
    /* TEST CAN INTERFACE */
    // RUN_TEST(test_can_interface_send)
    // RUN_TEST(test_can_interface_send_and_receive_raw)
    /* TEST MCU */
    RUN_TEST(test_set_brake_light);

    return UNITY_END();
}

void setup() 
{
    delay(500);

    runUnityTests();
}

void loop() {

}