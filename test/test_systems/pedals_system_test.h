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

PedalsParams gen_positive_and_negative_slope_params()
{
    PedalsParams params;
    params.min_pedal_1 = 2000;
    params.max_pedal_1 = 1000;
    params.min_pedal_2 = 1000;
    params.max_pedal_2 = 2000;
    params.activation_percentage = 0.25;
    params.mechanical_activation_percentage = 0.4;
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
    params.activation_percentage = 0.25;
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
    AnalogConversion_s test_pedal_val_half_pressed = {1500, 0.5, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};

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

    for(auto set : pedal_pairs_w_expected_val)
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
// TEST(PedalsSystemTesting, test_accel_and_brake_pressed_at_same_time_and_activation)
// {
//     AnalogConversion_s test_accel1_val = {2000, 0.6, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
//     AnalogConversion_s test_brake_val = {3000, 1.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
//     auto params = gen_params();
//     PedalsSystem pedals(params, params);
//     auto data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
//     EXPECT_TRUE(data.brakeAndAccelPressedImplausibility);
//     EXPECT_TRUE(data.brakePressed);
// }

// // T.4.2.5 FSAE rules 2024 v1
// TEST(PedalsSystemTesting, test_implausibility_duration)
// {
//     AnalogConversion_s test_accel1_val = {2000, 0.6, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
//     AnalogConversion_s test_brake_val = {3000, 1.0, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
//     auto params = gen_params();
//     PedalsSystem pedals(params, params);
//     auto data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1000);
//     EXPECT_TRUE(data.brakeAndAccelPressedImplausibility);
//     EXPECT_TRUE(data.brakePressed);
//     EXPECT_FALSE(data.implausibilityExceededMaxDuration);

//     data = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, test_brake_val, 1200);
//     EXPECT_TRUE(data.implausibilityExceededMaxDuration);

//     auto data2 = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, 1000);
//     EXPECT_TRUE(data2.brakeAndAccelPressedImplausibility);
//     EXPECT_TRUE(data2.brakePressed);
//     EXPECT_FALSE(data2.implausibilityExceededMaxDuration);

//     data2 = pedals.evaluate_pedals(test_accel1_val, test_accel1_val, test_brake_val, 1200);
//     EXPECT_TRUE(data2.implausibilityExceededMaxDuration);
// }

// TEST(PedalsSystemTesting, single_brake_pedal_test_limits)
// {
//     // accel min and max on raw
//     AnalogConversion_s test_accel1_val = {0, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
//     AnalogConversion_s test_accel2_val = {200, 0.3, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
//     AnalogConversion_s test_brake1_val = {200, 0.01, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
//     AnalogConversion_s test_brake2_val = {500, 0.01, AnalogSensorStatus_e::ANALOG_SENSOR_GOOD};
//     auto params = gen_params();
//     PedalsSystem pedals(params, params);

//     auto data = pedals.evaluate_pedals(test_accel1_val, test_accel2_val, test_brake1_val, test_brake2_val, 1000);
//     EXPECT_TRUE(data.brakeImplausible);
// }

#endif /* PEDALS_SYSTEM_TEST */
