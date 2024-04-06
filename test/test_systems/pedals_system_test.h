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
#include "MCU_rev15_defs.h"



TEST(PedalsSystemTesting, test_accel_and_brake_limits_plausibility)
{
    // accel min and max on raw
    AnalogConversion_s test_accel1_val = {0, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_accel2_val = {200, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {200, 0.01, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    PedalsParams params;
    params.min_pedal_1 = 1000;
    params.max_pedal_1 = 2000;
    params.min_pedal_2 = 1000;
    params.max_pedal_2 = 2000;
    params.activation_percentage = 0.1;
    params.deadzone_margin = DEFAULT_PEDAL_DEADZONE;
    params.implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN;
    PedalsSystem pedals(params, params, 0.0f);



    // this should be implausible since test accel1 and accel2 have values less than the min (1000)
    auto data = pedals.evaluate_pedals(test_accel1_val, test_accel2_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.accelImplausible);
    // ensuring that both accel in either position (since they have the same config, this should fail too)
    data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.accelImplausible);
    

    // testing accel raw greater than max
    test_accel1_val.raw = 4000;
    data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.accelImplausible);

    // brake min and max on raw. testing that if accel is implaus and brake implaus (less than min) we still guchi
    test_accel1_val.raw = 300;
    test_brake_val.raw = 0;
    data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeImplausible);

    // testing brake greater than max 
    test_brake_val.raw = 40000;
    data = pedals.evaluate_pedals(test_accel2_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeImplausible);

    // testing good values still good
    test_accel1_val.raw = 1300;
    test_brake_val.raw = 1300;

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

    PedalsParams params2;
    params2.min_pedal_1 = 100;
    params2.min_pedal_2 = 100;
    params2.max_pedal_1 = 3000;
    params2.max_pedal_2 = 3000;
    params2.activation_percentage = 0.1;
    params2.deadzone_margin = DEFAULT_PEDAL_DEADZONE;
    params2.implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN;

    PedalsSystem pedals(params2, params2, 0.0f);
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
    AnalogConversion_s test_accel1_val = {2000, 0.6, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {3000, 1.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    PedalsParams params2;
    params2.min_pedal_1 = 100;
    params2.min_pedal_2 = 100;
    params2.max_pedal_1 = 3000;
    params2.max_pedal_2 = 3000;
    params2.activation_percentage = 0.1;
    params2.deadzone_margin = DEFAULT_PEDAL_DEADZONE;
    params2.implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN;

    PedalsSystem pedals(params2, params2, 0.0f);
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
    AnalogConversion_s test_accel1_val = {2000, 0.6, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {3000, 1.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    PedalsParams params2;
    params2.min_pedal_1 = 100;
    params2.max_pedal_1 = 100;
    params2.min_pedal_2 = 3000;
    params2.max_pedal_2 = 3000;
    params2.activation_percentage = 0.1;
    params2.deadzone_margin = DEFAULT_PEDAL_DEADZONE;
    params2.implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN;

    PedalsSystem pedals(params2, params2, 0.0f);
    auto data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeAndAccelPressedImplausibility);
    EXPECT_TRUE(data.brakePressed);
    EXPECT_FALSE(data.implausibilityExceededMaxDuration);

    data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1200);


    EXPECT_TRUE(data.implausibilityExceededMaxDuration);
}

#endif /* PEDALS_SYSTEM_TEST */
