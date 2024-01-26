/*
basic test cases for the pedals component class
version 1.0
rough draft
author: Lucas Plant
*/

#ifndef PEDALS_SYSTEM_TEST
#define PEDALS_SYSTEM_TEST
#include <unity.h>
#include <string>
#include "PedalsSystem.h"
#include <array>

/*
ToDo:
    edit pedals system file to accommodate friend wrapper
    methods to test:
        constructor
        evaluate pedals
        linearize_accel_pedal_values_
        evaluate pedal_implausibilities_
        evaluate_brake_and_accel_pressed_
        pedal_is_active


*/
struct PedalIsActiveTestCase
{
    // defines input and output params

    // input params
    PedalsDriverInterface pedalsinput;

    // expected output
    bool expect_active;
};



void test_pedal_is_active(void)
{
    PedalsParams params_for_test = {1, 1, 10, 10, 1, 1, 9, 9};
    PedalsSystem pedals_system(params_for_test, params_for_test);
    std::array<PedalIsActiveTestCase, 1> test_cases{{{{0, 0, 3, 3}, true}}};

    for (const auto &test_case : test_cases)
    {
        auto out = pedals_system.mech_brake_active(test_case.pedalsinput);
        TEST_ASSERT_EQUAL(test_case.expect_active, out);
    }
}




#endif /* PEDALS_SYSTEM_TEST */
