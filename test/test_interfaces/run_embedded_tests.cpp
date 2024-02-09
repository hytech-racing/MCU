#include <Arduino.h>
#include <unity.h>

#include "AMS_interface_test.h"
#include "dashboard_interface_test.h"

void setUp(void)
{

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
    

    return UNITY_END();
}

void setup() 
{
    delay(2000);

    runUnityTests();
}

void loop() {}