#include <Arduino.h>
#include <unity.h>

#include "AMSInterface.h"

void test_AMS_unpacking_BMS_status_message()
{
    /*
    Need clarification on what these states are.
    Why is nothing else in the message read by AMSInterface
    */
    BMS_status bms_status{};
    bms_status.set_state(5);

}

void test_AMS_unpacking_BMS_temperatures_message()
{

}

void test_AMS_unpacking_BMS_voltages_message()
{

}

void test_AMS_charge_critical_threshold()
{

}

void test_AMS_filtered_readings()
{

}

void test_AMS_heartbeat()
{   
    //setting arbitrary pin 20
    AMSInterface ams_interface(20);
    ams_interface.init(millis());
    ams_interface.set_start_state();
    TEST_ASSERT_EQUAL(true, ams_interface.heartbeat_received(millis()));
    delay(20);
    TEST_ASSERT_EQUAL(false, ams_interface.heartbeat_received(millis()));
}