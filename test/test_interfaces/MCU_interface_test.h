#include <Arduino.h>
#include <unity.h>

#include "MCUInterface.h"

Circular_Buffer <uint8_t, (uint32_t)16, sizeof(CAN_message_t)> mcu_CAN_buffer;

MCUInterface mcu_interface(&mcu_CAN_buffer);

void test_set_brake_light(void)
{
    mcu_interface.set_brake_light(true);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(7));
    mcu_interface.set_brake_light(false);
    TEST_ASSERT_EQUAL(LOW, digitalRead(7));
}

void test_mcu_circular_buffer(void)
{
    
}