#include <Arduino.h>
#include <unity.h>

#include "AMS_interface_test.h"
#include "dashboard_interface_test.h"
#include "Watchdog_interface_test.h"
#include "Coulomb_Counting_Tests.h"
#include "MCU_rev15_defs.h"

void tearDown(void)
{

}

int runUnityTests(void) 
{
    UNITY_BEGIN();
    /* TEST DASHBOARD */
    // RUN_TEST(test_dashboard_unpacking_can_message);
    // RUN_TEST(test_dashboard_circular_buffer);
    
    /* TEST CAN INTERFACE*/
    // RUN_TEST(test_can_interface_send)
    // RUN_TEST(test_can_interface_send_and_receive_raw)

    /* TEST TELEMETRY */
    // RUN_TEST(test_telemetry_update_CAN);

    /* TEST AMS */
    RUN_TEST(test_AMS_heartbeat);
    RUN_TEST(test_current_shunt_CAN_message);
    RUN_TEST(test_bms_voltages_CAN_message);
    RUN_TEST(test_em_measurements_CAN_message);

    /* TEST Coulomb Counting */
    RUN_TEST(test_initialize_charge);
    RUN_TEST(test_calculate_SoC_em);
    RUN_TEST(test_calculate_SoC_acu);

    return UNITY_END();
}

void on_can_receive() {} // do nothing

void setup() {

    delay(500);

    Serial.begin(115200);

    runUnityTests();

}

void loop() {
    
}