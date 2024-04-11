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

float get_pedal_conversion_val(float min, float max, float data)
{
    float scale = 1.0f / (max - min);
    return ((data - min) * scale);
}
PedalsParams gen_positive_and_negative_slope_params()
{
    PedalsParams params;
    params.min_pedal_1 = 2000;
    params.max_pedal_1 = 1000;
    params.min_pedal_2 = 1000;
    params.max_pedal_2 = 2000;
    params.activation_percentage = 0.25;
    params.mechanical_activation_percentage = 0.4;
    params.deadzone_margin = .03;                    // .05
    params.implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN; // 0.1
    return params;
}

//
PedalsParams get_real_accel_pedal_params()
{
    PedalsParams params;
    params.min_pedal_1 = ACCEL1_PEDAL_MIN;
    params.max_pedal_1 = ACCEL1_PEDAL_MAX;
    params.min_pedal_2 = ACCEL2_PEDAL_MIN;
    params.max_pedal_2 = ACCEL2_PEDAL_MAX;
    params.activation_percentage = APPS_ACTIVATION_PERCENTAGE;
    params.mechanical_activation_percentage = APPS_ACTIVATION_PERCENTAGE;
    params.deadzone_margin = DEFAULT_PEDAL_DEADZONE;                    // .05
    params.implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN; // 0.1
    return params;
}
PedalsParams get_real_brake_pedal_params()
{
    PedalsParams params;
    params.min_pedal_1 = BRAKE1_PEDAL_MIN;
    params.max_pedal_1 = BRAKE1_PEDAL_MAX;
    params.min_pedal_2 = BRAKE2_PEDAL_MIN;
    params.max_pedal_2 = BRAKE2_PEDAL_MAX;
    params.activation_percentage = APPS_ACTIVATION_PERCENTAGE;
    params.mechanical_activation_percentage = BRAKE_MECH_THRESH;
    params.deadzone_margin = DEFAULT_PEDAL_DEADZONE;                    // .05
    params.implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN; // 0.1
    return params;
}

PedalsParams gen_positive_slope_only_params()
{
    PedalsParams params;
    params.min_pedal_1 = 1000;
    params.max_pedal_1 = 2000;
    params.min_pedal_2 = 1000;
    params.max_pedal_2 = 2000;
    params.activation_percentage = 0.1;
    params.mechanical_activation_percentage = 0.4;
    params.deadzone_margin = DEFAULT_PEDAL_DEADZONE;                    // .05
    params.implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN; // 0.1
    return params;
}

bool get_result_of_double_brake_test(PedalsSystem &pedals, const AnalogConversion_s &a1, const AnalogConversion_s &a2, const AnalogConversion_s &b1, const AnalogConversion_s &b2)
{
    auto data = pedals.evaluate_pedals(a1, a2, b1, b2, 1000);
    data = pedals.evaluate_pedals(a1, a2, b1, b2, 1110);
    return data.implausibilityExceededMaxDuration;
}

bool get_result_of_single_brake_test(PedalsSystem &pedals, const AnalogConversion_s &a1, const AnalogConversion_s &a2, const AnalogConversion_s &b1)
{
    auto data = pedals.evaluate_pedals(a1, a2, b1, 1000);
    data = pedals.evaluate_pedals(a1, a2, b1, 1110);
    return data.implausibilityExceededMaxDuration;
}

// resets the implaus time to zero by ticking with plausible data. should return true always.
bool reset_pedals_system_implaus_time(PedalsSystem &pedals)
{
    AnalogConversion_s test_accel_good_val = {1010, 0.01, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_good_val = {1010, 0.01, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    auto data = pedals.evaluate_pedals(test_accel_good_val, test_accel_good_val, test_brake_good_val, 1000);
    data = pedals.evaluate_pedals(test_accel_good_val, test_accel_good_val, test_brake_good_val, 1110);
    return (!data.implausibilityExceededMaxDuration);
}

// T.4.3.4, T.4.2.7, T.4.2.9, T.4.2.10 FSAE rules 2024 v1
TEST(PedalsSystemTesting, test_accel_and_brake_limits_plausibility)
{
    auto params = gen_positive_and_negative_slope_params();
    PedalsSystem pedals(params, params);

    AnalogConversion_s test_pedal_bad_val_min = {0, 0.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_bad_val_max = {4000, 2.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_good_val = {1200, 0.2, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    std::vector<std::tuple<AnalogConversion_s, AnalogConversion_s>> pedal_pairs;

    // check the possibilities of all min/max pairs for accel and good brake
    pedal_pairs.push_back({test_pedal_bad_val_min, test_pedal_bad_val_min});
    pedal_pairs.push_back({test_pedal_bad_val_min, test_pedal_bad_val_max});
    pedal_pairs.push_back({test_pedal_bad_val_max, test_pedal_bad_val_min});
    pedal_pairs.push_back({test_pedal_bad_val_max, test_pedal_bad_val_max});

    // T.4.2.7 , T.4.2.9 and T.4.2.10 (accel out of ranges min/max) testing
    for (auto pair : pedal_pairs)
    {
        auto p1 = std::get<0>(pair);
        auto p2 = std::get<1>(pair);
        bool t_4_2_7 = get_result_of_double_brake_test(pedals, p1, p2, test_pedal_good_val, test_pedal_good_val);
        EXPECT_TRUE(t_4_2_7);
        EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));

        t_4_2_7 = get_result_of_single_brake_test(pedals, p1, p2, test_pedal_good_val);
        EXPECT_TRUE(t_4_2_7);
        EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));
    }

    // ensure that all good is still good for d.p. brake
    bool t_4_2_7 = get_result_of_double_brake_test(pedals, test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, test_pedal_good_val);
    EXPECT_FALSE(t_4_2_7);
    EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));
    // ensure that all good is still good for s.p. brake
    t_4_2_7 = get_result_of_single_brake_test(pedals, test_pedal_good_val, test_pedal_good_val, test_pedal_good_val);
    EXPECT_FALSE(t_4_2_7);
    EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));

    // T.4.3.4 brake testing
    for (auto pair : pedal_pairs)
    {
        auto p1 = std::get<0>(pair);
        auto p2 = std::get<1>(pair);
        bool t_4_3_4 = get_result_of_double_brake_test(pedals, test_pedal_good_val, test_pedal_good_val, p1, p2);
        EXPECT_TRUE(t_4_3_4);
        EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));

        t_4_3_4 = get_result_of_single_brake_test(pedals, test_pedal_good_val, test_pedal_good_val, p1);
        EXPECT_TRUE(t_4_3_4);
        EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));
    }
}

// T.4.2.4 FSAE rules 2024 v1 (accel vals not within 10 percent of each other)
TEST(PedalsSystemTesting, test_accel_and_brake_percentages_implausibility)
{
    // accel percentage outside of range
    AnalogConversion_s test_pedal_pos_slope_val_not_pressed = {1000, 0.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_neg_slope_val_not_pressed = {2000, 0.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_val_half_pressed = {1500, 0.4, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    // the pos / neg slop gens pedal sens 1 with neg, and sensor 2 with pos. slope
    auto accel_params = gen_positive_and_negative_slope_params();
    auto brake_params = gen_positive_slope_only_params();
    PedalsSystem pedals(accel_params, brake_params);
    // bool is true if it is supposed to error, false otherwise
    std::vector<std::tuple<AnalogConversion_s, AnalogConversion_s, bool>> pedal_pairs_w_expected_val;

    // check the possibilities of all half pressed and not pressed with aligned slopes for sensor values
    pedal_pairs_w_expected_val.push_back({test_pedal_neg_slope_val_not_pressed, test_pedal_val_half_pressed, true});
    pedal_pairs_w_expected_val.push_back({test_pedal_val_half_pressed, test_pedal_pos_slope_val_not_pressed, true});
    pedal_pairs_w_expected_val.push_back({test_pedal_neg_slope_val_not_pressed, test_pedal_pos_slope_val_not_pressed, false});
    pedal_pairs_w_expected_val.push_back({test_pedal_val_half_pressed, test_pedal_val_half_pressed, false});

    for (auto set : pedal_pairs_w_expected_val)
    {
        auto p1 = std::get<0>(set);
        auto p2 = std::get<1>(set);
        // test accel
        bool res = get_result_of_double_brake_test(pedals, p1, p2, test_pedal_pos_slope_val_not_pressed, test_pedal_pos_slope_val_not_pressed);
        EXPECT_EQ(res, std::get<2>(set));
        EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));
        // TODO test double brake res (brakes not within req percentage) (not required by rules, still good to have)

        // testing single brake accel mode
        res = get_result_of_single_brake_test(pedals, p1, p2, test_pedal_pos_slope_val_not_pressed);
        EXPECT_EQ(res, std::get<2>(set));
        EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));
    }
}

// EV.4.7.1 FSAE rules 2024 v1
TEST(PedalsSystemTesting, test_accel_and_brake_pressed_at_same_time_and_activation)
{
    // test with example data
    AnalogConversion_s test_pedal_val_half_pressed = {1500, 0.5, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    // the pos / neg slop gens pedal sens 1 with neg, and sensor 2 with pos. slope
    auto accel_params = gen_positive_and_negative_slope_params();
    auto brake_params = gen_positive_slope_only_params();
    PedalsSystem pedals(accel_params, brake_params);
    //
    EXPECT_TRUE(get_result_of_double_brake_test(pedals, test_pedal_val_half_pressed, test_pedal_val_half_pressed, test_pedal_val_half_pressed, test_pedal_val_half_pressed));
    EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));
    EXPECT_TRUE(get_result_of_single_brake_test(pedals, test_pedal_val_half_pressed, test_pedal_val_half_pressed, test_pedal_val_half_pressed));
    EXPECT_TRUE(reset_pedals_system_implaus_time(pedals));

    // test with real data (accel = ~37%) accel pressed
    float accel1 = 2583;
    float accel2 = 1068;
    float brake = 1510;
    pedals.setParams({ACCEL1_PEDAL_MIN, ACCEL2_PEDAL_MIN, ACCEL1_PEDAL_MAX, ACCEL2_PEDAL_MAX, APPS_ACTIVATION_PERCENTAGE, DEFAULT_PEDAL_DEADZONE, DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN, APPS_ACTIVATION_PERCENTAGE},
                     {BRAKE1_PEDAL_MIN, BRAKE2_PEDAL_MIN, BRAKE1_PEDAL_MAX, BRAKE2_PEDAL_MAX, BRAKE_ACTIVATION_PERCENTAGE, DEFAULT_PEDAL_DEADZONE, DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN, BRAKE_MECH_THRESH});
    float conv1 = get_pedal_conversion_val(ACCEL1_PEDAL_MIN, ACCEL1_PEDAL_MAX, accel1);
    float conv2 = get_pedal_conversion_val(ACCEL2_PEDAL_MIN, ACCEL2_PEDAL_MAX, accel2);
    float convb = get_pedal_conversion_val(BRAKE1_PEDAL_MIN, BRAKE1_PEDAL_MAX, brake);

    std::cout << conv1 << " " << conv2 << " " << convb << std::endl;
    AnalogConversion_s accel1_data = {accel1, conv1, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s accel2_data = {accel1, conv2, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s brake_data = {brake, convb, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    EXPECT_TRUE(get_result_of_single_brake_test(pedals, test_pedal_val_half_pressed, test_pedal_val_half_pressed, test_pedal_val_half_pressed));
}

// // T.4.2.5 FSAE rules 2024 v1
TEST(PedalsSystemTesting, test_implausibility_duration)
{
    AnalogConversion_s test_accel1_val = {2583, 0.37, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_accel2_val = {1068, 0.37, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {1510, get_pedal_conversion_val(BRAKE1_PEDAL_MIN, BRAKE1_PEDAL_MAX, 1510), AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    PedalsSystem pedals(get_real_accel_pedal_params(), get_real_brake_pedal_params());

    auto data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
    EXPECT_TRUE(data.brakeAndAccelPressedImplausibility);
    EXPECT_TRUE(data.brakePressed);
    EXPECT_FALSE(data.implausibilityExceededMaxDuration);

    data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1110);
    EXPECT_TRUE(data.implausibilityExceededMaxDuration);

    // testing the single brake pedal vals
    auto data2 = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, 1000);
    EXPECT_TRUE(data2.brakeAndAccelPressedImplausibility);
    EXPECT_TRUE(data2.brakePressed);
    EXPECT_FALSE(data2.implausibilityExceededMaxDuration);

    data2 = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, 1110);
    EXPECT_TRUE(data2.implausibilityExceededMaxDuration);
}

// EV.4.7.2 b FSAE rules 2024 v1
TEST(PedalsSystemTesting, implausibility_latching_until_accel_released_double_brake)
{
    AnalogConversion_s test_accel1_val = {2583, 0.37, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_accel2_val = {1068, 0.37, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {1510, get_pedal_conversion_val(BRAKE1_PEDAL_MIN, BRAKE1_PEDAL_MAX, 1510), AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    PedalsSystem pedals(get_real_accel_pedal_params(), get_real_brake_pedal_params());

    // should stay im
    EXPECT_TRUE(get_result_of_double_brake_test(pedals, test_accel1_val, test_accel2_val, test_brake_val, test_brake_val));

    test_brake_val.raw = 870;
    test_brake_val.conversion = 0.0;
    auto data = pedals.evaluate_pedals(test_accel1_val, test_accel2_val, test_brake_val, test_brake_val, 1600);
    // this should still be implause since accel is still pressed
    EXPECT_TRUE(data.implausibilityExceededMaxDuration);

    // reset accel to zero and try again this time it should pass
    test_accel1_val.raw = ACCEL1_PEDAL_MIN;
    test_accel2_val.raw = ACCEL2_PEDAL_MIN;
    test_accel1_val.conversion = 0.0;
    test_accel2_val.conversion = 0.0;
    data = pedals.evaluate_pedals(test_accel1_val, test_accel2_val, test_brake_val, test_brake_val, 1650);

    EXPECT_FALSE(data.implausibilityExceededMaxDuration);
}

TEST(PedalsSystemTesting, implausibility_latching_until_accel_released_single_brake)
{
    ////////////////////
    // repeat above with single pedal brake test:
    ////////////////////
    AnalogConversion_s test_accel1_val = {2583, 0.37, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_accel2_val = {1068, 0.37, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_brake_val = {1510, get_pedal_conversion_val(BRAKE1_PEDAL_MIN, BRAKE1_PEDAL_MAX, 1510), AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    PedalsSystem pedals2(get_real_accel_pedal_params(), get_real_brake_pedal_params());

    // first we fail
    EXPECT_TRUE(get_result_of_single_brake_test(pedals2, test_accel1_val, test_accel2_val, test_brake_val));

    test_brake_val.raw = 870;
    test_brake_val.conversion = 0.0;
    auto data2 = pedals2.evaluate_pedals(test_accel1_val, test_accel2_val, test_brake_val, 1600);
    // this should still be implause since accel is still pressed
    EXPECT_TRUE(data2.implausibilityExceededMaxDuration);

    // now we reset throttle back to 0
    test_accel1_val.raw = ACCEL1_PEDAL_MIN + 10;
    test_accel2_val.raw = ACCEL2_PEDAL_MIN + 30;
    test_accel1_val.conversion = 0.01;
    test_accel2_val.conversion = 0.05;
    data2 = pedals2.evaluate_pedals(test_accel1_val, test_accel2_val, test_brake_val, 1710);
    EXPECT_FALSE(data2.implausibilityExceededMaxDuration);
}

TEST(PedalsSystemTesting, deadzone_removal_calc_double_brake_ped)
{
    // accel value testing (0, 100 percent, 50 percent)
    AnalogConversion_s test_pedal_good_val = {1010, 0.03, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    PedalsSystem pedals(gen_positive_slope_only_params(), gen_positive_slope_only_params());
    auto data = pedals.evaluate_pedals(test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, 1000);
    EXPECT_NEAR(data.accelPercent, 0, .001);
    test_pedal_good_val.raw = 2059;
    test_pedal_good_val.conversion = 1.05;
    data = pedals.evaluate_pedals(test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, 1100);
    EXPECT_NEAR(data.accelPercent, 1, .001);
    test_pedal_good_val.raw = 1500;
    test_pedal_good_val.conversion = 0.5;
    data = pedals.evaluate_pedals(test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, 1200);
    EXPECT_NEAR(data.accelPercent, 0.5, .001);

    // brake value testing (0, 100 percent, 50 percent)
    AnalogConversion_s test_pedal_good_val_accel = {1050, 0.03, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_good_val_brake = {1050, 0.03, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, test_pedal_good_val_brake, 1300);
    EXPECT_NEAR(data.brakePercent, 0, .001);
    test_pedal_good_val_brake.raw = 2059;
    test_pedal_good_val_brake.conversion = 1.05;
    data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, test_pedal_good_val_brake, 1400);
    EXPECT_NEAR(data.brakePercent, 1, .001);
    test_pedal_good_val_brake.raw = 1500;
    test_pedal_good_val_brake.conversion = 0.5;
    data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, test_pedal_good_val_brake, 1500);
    EXPECT_NEAR(data.brakePercent, 0.5, .001);
}

TEST(PedalsSystemTesting, deadzone_removal_calc_single_brake_ped)
{
    // accel value testing (0, 100 percent, 50 percent)
    AnalogConversion_s test_pedal_good_val = {1010, 0.03, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    PedalsSystem pedals(gen_positive_slope_only_params(), gen_positive_slope_only_params());
    auto data = pedals.evaluate_pedals(test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, 1000);
    EXPECT_NEAR(data.accelPercent, 0, .001);
    test_pedal_good_val.raw = 2059;
    test_pedal_good_val.conversion = 1.05;
    data = pedals.evaluate_pedals(test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, 1100);
    EXPECT_NEAR(data.accelPercent, 1, .001);
    test_pedal_good_val.raw = 1500;
    test_pedal_good_val.conversion = 0.5;
    data = pedals.evaluate_pedals(test_pedal_good_val, test_pedal_good_val, test_pedal_good_val, 1200);
    EXPECT_NEAR(data.accelPercent, 0.5, .001);

    // brake value testing (0, 100 percent, 50 percent)
    AnalogConversion_s test_pedal_good_val_accel = {1010, 0.03, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_good_val_brake = {1010, 0.03, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, 1300);
    EXPECT_NEAR(data.brakePercent, 0, .01);
    test_pedal_good_val_brake.raw = 2059;
    test_pedal_good_val_brake.conversion = 1.05;
    data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, 1400);
    EXPECT_NEAR(data.brakePercent, 1, .001);
    test_pedal_good_val_brake.raw = 1500;
    test_pedal_good_val_brake.conversion = 0.5;
    data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, 1500);
    EXPECT_NEAR(data.brakePercent, 0.5, .001);
}

// testing mechanical brake and brake activation
TEST(PedalsSystemTesting, brake_value_testing_double)
{
    AnalogConversion_s test_pedal_good_val_accel = {1050, 0.05, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_good_val_brake = {1200, 0.2, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    auto params = gen_positive_slope_only_params();
    // taking out deadzone margin to ensure that brake vals are good
    params.deadzone_margin = 0;
    PedalsSystem pedals(params, params);
    auto data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, test_pedal_good_val_brake, 1300);
    EXPECT_NEAR(data.brakePercent, 0.2, .02);
    EXPECT_NEAR(data.regenPercent, 0.5, .02);

    EXPECT_TRUE(data.brakePressed);
    EXPECT_FALSE(data.mechBrakeActive);

    test_pedal_good_val_brake.raw = 1400;
    test_pedal_good_val_brake.conversion = .4;
    data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, test_pedal_good_val_brake, 1500);
    EXPECT_NEAR(data.brakePercent, 0.4, .03);
    EXPECT_TRUE(data.brakePressed);
    EXPECT_TRUE(data.mechBrakeActive);
    EXPECT_NEAR(data.regenPercent, 1, .03);


}

TEST(PedalsSystemTesting, brake_value_testing_single)
{
    AnalogConversion_s test_pedal_good_val_accel = {1050, 0.05, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_good_val_brake = {1200, 0.2, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    auto params = gen_positive_slope_only_params();
    // taking out deadzone margin to ensure that brake vals are good
    params.deadzone_margin = 0;
    PedalsSystem pedals(params, params);
    auto data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, 1300);
    EXPECT_NEAR(data.brakePercent, 0.2, .02);
    EXPECT_NEAR(data.regenPercent, 0.5, .02);

    EXPECT_TRUE(data.brakePressed);
    EXPECT_FALSE(data.mechBrakeActive);

    test_pedal_good_val_brake.raw = 1400;
    test_pedal_good_val_brake.conversion = .4;
    data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, 1500);
    EXPECT_NEAR(data.brakePercent, 0.4, .03);
    EXPECT_TRUE(data.brakePressed);
    EXPECT_TRUE(data.mechBrakeActive);
    EXPECT_NEAR(data.regenPercent, 1, .03);
}

TEST(PedalsSystemTesting, check_accel_never_negative_single)
{
    AnalogConversion_s test_pedal_good_val_accel = {930, -0.05, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_good_val_brake = {1200, 0.2, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    auto params = gen_positive_slope_only_params();
    // taking out deadzone margin to ensure that brake vals are good
    params.deadzone_margin = 0;
    PedalsSystem pedals(params, params);
    auto data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, 1300);
    EXPECT_FALSE(data.accelImplausible);
    EXPECT_EQ(data.accelPercent, 0);

}

TEST(PedalsSystemTesting, check_accel_never_negative_double)
{
    AnalogConversion_s test_pedal_good_val_accel = {930, -0.05, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_good_val_brake = {1200, 0.2, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    auto params = gen_positive_slope_only_params();
    // taking out deadzone margin to ensure that brake vals are good
    params.deadzone_margin = 0;
    PedalsSystem pedals(params, params);
    auto data = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, test_pedal_good_val_brake, 1300);
    EXPECT_FALSE(data.accelImplausible);
    EXPECT_EQ(data.accelPercent, 0);

}

TEST(PedalsSystemTesting, check_accel_pressed)
{
    AnalogConversion_s test_pedal_good_val_accel = {1200, 0.2, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
    AnalogConversion_s test_pedal_good_val_brake = {1001, 0.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

    auto params = gen_positive_slope_only_params();
    PedalsSystem pedals(params, params);
    PedalsSystem pedals_single(params, params);
    auto data_double = pedals.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, test_pedal_good_val_brake, 1300);
    EXPECT_TRUE(data_double.accelPressed);
    auto data_single = pedals_single.evaluate_pedals(test_pedal_good_val_accel, test_pedal_good_val_accel, test_pedal_good_val_brake, 1300);
    EXPECT_TRUE(data_single.accelPressed);
}


#endif /* PEDALS_SYSTEM_TEST */
