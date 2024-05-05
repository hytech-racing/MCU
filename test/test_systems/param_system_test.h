#ifndef PARAMS_SYSTEM_TEST
#define PARAMS_SYSTEM_TEST

#include "ParameterSystem.h"

// TODO may wanna do this with a fixed param lib, but for now the regular
//      param lib should be fine
TEST(ParamSystemTest, test_set_params) {
    int val = 20;
    set_parameter(Parameters::CASE_TORQUE_MAXInstance, val);
    EXPECT_EQ(Parameters::CASE_TORQUE_MAXInstance.get(), val);
}

TEST(ParamSystemTest, test_set_get_params) {
    int val = 20;
    set_parameter(Parameters::CASE_TORQUE_MAXInstance, val);
    EXPECT_EQ(get_parameter(Parameters::CASE_TORQUE_MAXInstance), val);
}

#endif