/*
basic test cases for the pedals component class
version 1.0
rough draft
author: Lucas Plant
*/


#ifndef PEDALS_SYSTEM_TEST
#define PEDALS_SYSTEM_TEST
#include <gtest/gtest.h>
#include <string>
#include "PedalsSystem.h"
#include <array>

TEST(PedalsSystemTesting, test_accel_and_brake_limits_plausibility)
{
    // accel min and max on raw
    AnalogConversion_s test_accel1_val = {0, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_accel2_val = {200, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {200, 0.01, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    PedalsSystem pedals({100, 100, 3000, 3000, 0.1}, {100, 100, 3000, 3000, 0.1});
    auto data = pedals.evaluate_pedals(test_accel1_val, test_accel2_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.accelImplausible);
    data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.accelImplausible);
    test_accel1_val.raw = 4000;
    data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.accelImplausible);
    test_accel1_val.raw = 300;
    // brake min and max on raw
    test_brake_val.raw = 0;
    data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeImplausible);
    test_brake_val.raw = 40000;
    data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeImplausible);

    test_accel1_val.raw = 200;
    test_brake_val.raw = 200;

    data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);

    EXPECT_FALSE(data.brakeImplausible);
    EXPECT_FALSE(data.accelImplausible);
}

TEST(PedalsSystemTesting, test_accel_and_brake_percentages_implausibility)
{
    // accel percentage outside of range
    AnalogConversion_s test_accel1_val = {200, 0.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_accel2_val = {200, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {200, 0.01, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    PedalsSystem pedals({100, 100, 3000, 3000, 0.1}, {100, 100, 3000, 3000, 0.1});
    auto data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);

    EXPECT_FALSE(data.brakeImplausible);
    EXPECT_TRUE(data.accelImplausible);

    // brake percentage outside of range
    test_brake_val.conversion = 0.5;
    auto test_b2 = test_brake_val;
    test_b2.conversion = 0.0;
    data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_b2, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeImplausible);
    EXPECT_FALSE(data.accelImplausible);

    data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);

    EXPECT_FALSE(data.brakeImplausible);
    EXPECT_FALSE(data.accelImplausible);
}

TEST(PedalsSystemTesting, test_accel_and_brake_pressed_at_same_time_and_activation)
{
    AnalogConversion_s test_accel1_val = {1000, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {1000, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    PedalsSystem pedals({100, 100, 3000, 3000, 0.1}, {100, 100, 3000, 3000, 0.1});
    auto data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeAndAccelPressedImplausibility);
    EXPECT_TRUE(data.brakePressed);

    test_brake_val.conversion = 0.0;

    data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);

    EXPECT_FALSE(data.brakeAndAccelPressedImplausibility);
    EXPECT_FALSE(data.brakePressed);
}

TEST(PedalsSystemTesting, test_implausibility_duration)
{
    AnalogConversion_s test_accel1_val = {1000, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {1000, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    PedalsSystem pedals({100, 100, 3000, 3000, 0.1}, {100, 100, 3000, 3000, 0.1});
    auto data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeAndAccelPressedImplausibility);
    EXPECT_TRUE(data.brakePressed);
    EXPECT_FALSE(data.implausibilityExceededMaxDuration);

    data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1200);


    EXPECT_TRUE(data.implausibilityExceededMaxDuration);
}

#endif /* PEDALS_SYSTEM_TEST */
