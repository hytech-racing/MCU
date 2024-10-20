#ifndef __TC_MUX_V2_TESTING_H__
#define __TC_MUX_V2_TESTING_H__

#include "TorqueControllerMux.h"
#include "TorqueControllers.h"
#include "TorqueControllers.h"
#include "fake_controller_type.h"
#include <gtest/gtest.h>

template <typename quad_array_type>
void set_four_outputs(quad_array_type &out, float val)
{
    out[0] = val;
    out[1] = val;
    out[2] = val;
    out[3] = val;
}

template <typename controller_type>
void set_outputs(controller_type &controller, float mps, float torque)
{
    controller.output.command.speeds_rpm[0] = METERS_PER_SECOND_TO_RPM * mps;
    controller.output.command.speeds_rpm[1] = METERS_PER_SECOND_TO_RPM * mps;
    controller.output.command.speeds_rpm[2] = METERS_PER_SECOND_TO_RPM * mps;
    controller.output.command.speeds_rpm[3] = METERS_PER_SECOND_TO_RPM * mps;
    controller.output.command.inverter_torque_limit[0] = torque;
    controller.output.command.inverter_torque_limit[1] = torque;
    controller.output.command.inverter_torque_limit[2] = torque;
    controller.output.command.inverter_torque_limit[3] = torque;
}
template <typename controller_type>
void set_output_rpm(controller_type &controller, float rpm, float torque)
{
    controller.output.command.speeds_rpm[0] = rpm;
    controller.output.command.speeds_rpm[1] = rpm;
    controller.output.command.speeds_rpm[2] = rpm;
    controller.output.command.speeds_rpm[3] = rpm;
    controller.output.command.inverter_torque_limit[0] = torque;
    controller.output.command.inverter_torque_limit[1] = torque;
    controller.output.command.inverter_torque_limit[2] = torque;
    controller.output.command.inverter_torque_limit[3] = torque;
}

//construction testing
TEST(TorqueControllerMuxTesting, test_construction)
{
    TestControllerType inst1, inst2;
    TorqueControllerMux<2> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2)}, {false, false});
}
TEST(TorqueControllerMuxTesting, test_construction_bypass_limits)
{
    TestControllerType inst1, inst2;
    set_output_rpm(inst1, 500, 30.0);
    set_output_rpm(inst2, 500, 30.0);
    TorqueControllerMux<2> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2)}, {true, false});
 
    DrivetrainDynamicReport_s drivetrain_data = {};
    for (int i = 0; i < 4; i++)
    {
        drivetrain_data.measuredSpeeds[i] = 500.0f;
    }
    //onlhy use mode 0 for the input state in all tests and then test if they would act the same, idk how to do that
    SharedCarState_s mode_1_input_state({}, {}, drivetrain_data, {}, {.accelPercent = 0.5f, .brakePercent = 0.0f, .regenPercent = 0.0}, {}, {}, {});
 
    auto drive_command = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_LOW_TORQUE, mode_1_input_state);
 
    ASSERT_EQ(drive_command.inverter_torque_limit[0], 30.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[1], 30.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[2], 30.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[3], 30.0f);
 
    ASSERT_EQ(test.get_tc_mux_status().output_is_bypassing_limits, true);
 
    inst1.output.command.inverter_torque_limit[0] = 5;
    drive_command = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_LOW_TORQUE, mode_1_input_state);
 
    ASSERT_EQ(drive_command.inverter_torque_limit[0], 5.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[1], 30.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[2], 30.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[3], 30.0f);
 
    ASSERT_EQ(test.get_tc_mux_status().output_is_bypassing_limits, true);
}
template<int num_controllers>
void test_with_n_controllers() {
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    std::array<TestControllerType, num_controllers> controller_instances; 
    std::array<Controller*, num_controllers> controller_ptrs; 
    std::array<bool, num_controllers> error_flags{}; 

    for (int i = 0; i < num_controllers; ++i) {
        controller_ptrs[i] = static_cast<Controller*>(&controller_instances[i]);
    }

    // Instantiate TorqueControllerMux with the current number of controllers
    TorqueControllerMux<num_controllers> mux(controller_ptrs, error_flags);

    // Test the getDrivetrainCommand method
    auto result = mux.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);

    // Assert no error has occurred
    ASSERT_EQ(mux.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
}
// Test case for different numbers of controllers (hardcoded bc needs a const)
TEST(TorqueControllerMuxTesting, test_variable_length_controllers)
{
    test_with_n_controllers<1>();
    test_with_n_controllers<2>();
    test_with_n_controllers<3>();
    test_with_n_controllers<4>();
    test_with_n_controllers<5>();
    test_with_n_controllers<6>();
    test_with_n_controllers<7>();
    test_with_n_controllers<8>();
    test_with_n_controllers<9>();
    test_with_n_controllers<10>();
}
TEST(TorqueControllerMuxTesting, test_construction_with_new_controller_orgs)
{
    // mode 0
    TorqueControllerSimple tc_simple(1.0f, 1.0f);
    // mode 1
    TorqueControllerLoadCellVectoring tc_vec;
    // mode 2
    DummyQueue_s q;
    CASESystem<DummyQueue_s> case_sys(&q, 100, 70, 550, {});
    TorqueControllerCASEWrapper<DummyQueue_s> case_wrapper(&case_sys);

    // mode 3
    TorqueControllerSimpleLaunch simple_launch;
    // mode 4
    TorqueControllerSlipLaunch slip_launch;

    TorqueControllerMux<5>
        torque_controller_mux({static_cast<Controller *>(&tc_simple),
                               static_cast<Controller *>(&tc_vec),
                               static_cast<Controller *>(&case_wrapper),
                               static_cast<Controller *>(&simple_launch),
                               static_cast<Controller *>(&slip_launch)},
                              {false, false, true, false, false});
}
 
//logic testing
// ensure that swapping to a controller that has a higher desired output speed than previously
// commanded that we dont switch
TEST(TorqueControllerMuxTesting, test_controller_output_swap_logic)
{
    TestControllerType inst1, inst2;
    set_outputs(inst1, 0, 1);
    set_outputs(inst2, 6, 1);
    TorqueControllerMux<2> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2)}, {false, false});
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    set_four_outputs(state.drivetrain_data.measuredSpeeds, 10000.0);

    state.pedals_data = {};
    state.vn_data = {};

    auto out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);

    // auto out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);

    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::ERROR_SPEED_DIFF_TOO_HIGH);

    set_outputs(inst1, 0, 1);
    set_outputs(inst2, 0, 1);
    set_four_outputs(state.drivetrain_data.measuredSpeeds, 0);

    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);

    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_1);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
}
TEST(TorqueControllerMuxTesting, simple_switch_many_active_modes)
{
    TestControllerType inst1, inst2, inst3, inst4;
    set_outputs(inst1, 0, 1);
    set_outputs(inst2, 0, 1);
    set_outputs(inst3, 0, 1);
    set_outputs(inst4, 0, 1);
    TorqueControllerMux<4> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2), static_cast<Controller *>(&inst3), static_cast<Controller *>(&inst4)}, {false, false, false, false});
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    set_four_outputs(state.drivetrain_data.measuredSpeeds, 2);
 
    state.pedals_data = {};
    state.vn_data = {};
 
    auto out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
   
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_1);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
 
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_2, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_2);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
 
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_3, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_3);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
 
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_2, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_2);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
   
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
}
 
//TorqueControllerMuxError testing
TEST(TorqueControllerMuxTesting, test_invalid_controller_request_error)
{
    TestControllerType inst1, inst2;
    TorqueControllerMux<2> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2)}, {false, false});
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    //test positve out of bounds
    auto res = test.getDrivetrainCommand(ControllerMode_e::MODE_2, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
   
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::ERROR_CONTROLLER_INDEX_OUT_OF_BOUNDS);
    for (int i =0; i< 4; i++)
    {
 
        ASSERT_EQ(res.speeds_rpm[i], 0.0);
        ASSERT_EQ(res.inverter_torque_limit[i], 0.0);
    }

    //reset to no error
    res = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);

    //test negative out of bounds
    res = test.getDrivetrainCommand(static_cast<ControllerMode_e>(-1), TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::ERROR_CONTROLLER_INDEX_OUT_OF_BOUNDS);
    for (int i =0; i< 4; i++)
    {
 
        ASSERT_EQ(res.speeds_rpm[i], 0.0);
        ASSERT_EQ(res.inverter_torque_limit[i], 0.0);
    }
}
TEST(TorqueControllerMuxTesting, test_null_pointer_error_state)
{
    TorqueControllerMux<1> test({nullptr}, {true});
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    auto res = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_LOW_TORQUE, state);
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(res.inverter_torque_limit[i], 0.0f);
        ASSERT_EQ(res.speeds_rpm[i], 0.0f);
    }
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::ERROR_CONTROLLER_NULL_POINTER);
}
TEST(TorqueControllerMuxTesting, test_torque_diff_swap_limit)
{
    TestControllerType inst1, inst2;
    set_outputs(inst1, 0.1, 1);
    set_outputs(inst2, 3, 10);
    TorqueControllerMux<2> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2)}, {false, false});
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});

    auto out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::ERROR_TORQUE_DIFF_TOO_HIGH);

    // tick it a bunch of times
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);

    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::ERROR_TORQUE_DIFF_TOO_HIGH);

    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);

    ASSERT_EQ(out1.inverter_torque_limit[0], 1);
    ASSERT_EQ(out1.inverter_torque_limit[1], 1);
    ASSERT_EQ(out1.inverter_torque_limit[2], 1);
    ASSERT_EQ(out1.inverter_torque_limit[3], 1);
}
TEST(TorqueControllerMuxTesting, test_speed_diff_swap_limit)
{
    TestControllerType inst1, inst2;
    TorqueControllerMux<2> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2)}, {false, false});
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    set_outputs(inst1, 0.1, 1);
    set_outputs(inst2, 3, 1);
 
    auto out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_1);
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);

    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    state.drivetrain_data = { 0, { 3000, 0, 0, 0 }, {}, {}, {} };

    // tick it a bunch of times
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
 
    ASSERT_EQ(test.get_tc_mux_status().active_error, TorqueControllerMuxError::ERROR_SPEED_DIFF_TOO_HIGH);
 
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
 
    ASSERT_EQ(out1.inverter_torque_limit[0], 1);
    ASSERT_EQ(out1.inverter_torque_limit[1], 1);
    ASSERT_EQ(out1.inverter_torque_limit[2], 1);
    ASSERT_EQ(out1.inverter_torque_limit[3], 1);
}

//Mode evaluation tests
TEST(TorqueControllerMuxTesting, test_mode0_evaluation)
{

    float max_torque = 21.42;
    // mode 0
    TorqueControllerSimple tc_simple(1.0f, 1.0f);
    // mode 1
    TorqueControllerLoadCellVectoring tc_vec;
    // mode 2
    DummyQueue_s q;
    CASESystem<DummyQueue_s> case_sys(&q, 100, 70, 550, {});
    TorqueControllerCASEWrapper<DummyQueue_s> case_wrapper(&case_sys);

    // mode 3
    TorqueControllerSimpleLaunch simple_launch;
    // mode 4
    TorqueControllerSlipLaunch slip_launch;
    TorqueControllerMux<5> torque_controller_mux({static_cast<Controller *>(&tc_simple),
                                                  static_cast<Controller *>(&tc_vec),
                                                  static_cast<Controller *>(&case_wrapper),
                                                  static_cast<Controller *>(&simple_launch),
                                                  static_cast<Controller *>(&slip_launch)},
                                                 {false, true, false, false, false});
    SharedCarState_s mode_0_input_state({}, {}, {}, {}, {.accelPercent = 0.5f, .brakePercent = 0.0f, .regenPercent = 0.0}, {}, {}, {});

    DrivetrainCommand_s out = torque_controller_mux.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, mode_0_input_state);
    ASSERT_NEAR(out.inverter_torque_limit[0], (max_torque / 2), 0.01);
    ASSERT_NEAR(out.inverter_torque_limit[1], (max_torque / 2), 0.01);
    ASSERT_NEAR(out.inverter_torque_limit[2], (max_torque / 2), 0.01);
    ASSERT_NEAR(out.inverter_torque_limit[3], (max_torque / 2), 0.01);
}

TEST(TorqueControllerMuxTesting, test_modeX_stationary)
{
    float max_torque = 21.42;
    TorqueControllerSimple tc_simple(1.0f, 1.0f);
    TorqueControllerLoadCellVectoring tc_vec;
    DummyQueue_s q;
    CASESystem<DummyQueue_s> case_sys(&q, 100, 70, 550, {});
    TorqueControllerCASEWrapper<DummyQueue_s> case_wrapper(&case_sys);
    TorqueControllerSimpleLaunch simple_launch;
    TorqueControllerSlipLaunch slip_launch;
    TorqueControllerMux<5> torque_controller_mux({static_cast<Controller *>(&tc_simple),
                                                  static_cast<Controller *>(&tc_vec),
                                                  static_cast<Controller *>(&case_wrapper),
                                                  static_cast<Controller *>(&simple_launch),
                                                  static_cast<Controller *>(&slip_launch)},
                                                 {false, false, false, false, false});


    for (int i = 0; i <= 4; ++i) {
        ControllerMode_e mode = static_cast<ControllerMode_e>(static_cast<int>(ControllerMode_e::MODE_0) + i);
        SharedCarState_s mode_X_input_state({}, {}, {}, {}, {.accelPercent = 0.0f, .brakePercent = 0.0f, .regenPercent = 0.0}, {}, {}, {});
        DrivetrainCommand_s out = torque_controller_mux.getDrivetrainCommand(mode, TorqueLimit_e::TCMUX_FULL_TORQUE, mode_X_input_state);
        ASSERT_EQ(out.inverter_torque_limit[0], 0);
        ASSERT_EQ(out.inverter_torque_limit[1], 0);
        ASSERT_EQ(out.inverter_torque_limit[2], 0);
        ASSERT_EQ(out.inverter_torque_limit[3], 0);
    }
}

 //limit testing
TEST(TorqueControllerMuxTesting, test_power_limit)
{
    TestControllerType inst1;
    set_output_rpm(inst1, 20000, 10.0);
    TorqueControllerMux<1> test({static_cast<Controller *>(&inst1)}, {false});

    DrivetrainDynamicReport_s drivetrain_data = {};
    for (int i = 0; i < 4; i++)
    {
        drivetrain_data.measuredSpeeds[i] = 500.0f;
    }
    SharedCarState_s mode_1_input_state({}, {}, drivetrain_data, {}, {.accelPercent = 0.5f, .brakePercent = 0.0f, .regenPercent = 0.0}, {}, {}, {});

    DrivetrainCommand_s res = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, mode_1_input_state);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(res.inverter_torque_limit[i], 10.0f);
    }
    for (int i = 0; i < 4; i++)
    {
        drivetrain_data.measuredSpeeds[i] = 20000.0f;
    }
    set_output_rpm(inst1, 20000, 21.0);

    SharedCarState_s mode_1_input_state_high_power({}, {}, drivetrain_data, {}, {.accelPercent = 1.0f, .brakePercent = 0.0f, .regenPercent = 0.0}, {}, {}, {});
    res = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, mode_1_input_state_high_power);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_LT(res.inverter_torque_limit[i], 7.6); // hardcoded value based on online calculator
    }
}

TEST(TorqueControllerMuxTesting, test_torque_limit)
{

    TestControllerType inst1;

    set_output_rpm(inst1, 500, 10.0);
    inst1.output.command.inverter_torque_limit[0] = 5;
    TorqueControllerMux<1> test({static_cast<Controller *>(&inst1)}, {false});

    DrivetrainDynamicReport_s drivetrain_data = {};
    for (int i = 0; i < 4; i++)
    {
        drivetrain_data.measuredSpeeds[i] = 500.0f;
    }

    SharedCarState_s mode_1_input_state({}, {}, drivetrain_data, {}, {.accelPercent = 0.5f, .brakePercent = 0.0f, .regenPercent = 0.0}, {}, {}, {});

    auto drive_command = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_LOW_TORQUE, mode_1_input_state);

    ASSERT_EQ(drive_command.inverter_torque_limit[0], 5.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[1], 10.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[2], 10.0f);
    ASSERT_EQ(drive_command.inverter_torque_limit[3], 10.0f);

    set_output_rpm(inst1, 500, 20.0);
    inst1.output.command.inverter_torque_limit[0] = 5;

    drive_command = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_LOW_TORQUE, mode_1_input_state);

    ASSERT_LT(drive_command.inverter_torque_limit[0], 3.5f);
    ASSERT_LT(drive_command.inverter_torque_limit[1], 12.5f);
    ASSERT_LT(drive_command.inverter_torque_limit[2], 12.5f);
    ASSERT_LT(drive_command.inverter_torque_limit[3], 12.5f);
    
    printf("torque 1: %.2f\n", drive_command.inverter_torque_limit[0]);
    printf("torque 2: %.2f\n", drive_command.inverter_torque_limit[1]);
    printf("torque 3: %.2f\n", drive_command.inverter_torque_limit[2]);
    printf("torque 4: %.2f\n", drive_command.inverter_torque_limit[3]);
}

TEST(TorqueControllerMuxTesting, test_apply_regen_limit) 
{
    TestControllerType inst1;
    set_output_rpm(inst1, 300, 10.0); 

    inst1.output.command.inverter_torque_limit[0] = 10; 
    TorqueControllerMux<1> test({static_cast<Controller *>(&inst1)}, {false});
    SharedCarState_s mode_1_input_state({}, {}, {}, {}, {.accelPercent = 0.5f, .brakePercent = 0.0f, .regenPercent = 0.0}, {}, {}, {});

    DrivetrainDynamicReport_s drivetrain_data_below_no_regen = {};
    drivetrain_data_below_no_regen.measuredSpeeds[0] = 12.0f / RPM_TO_KILOMETERS_PER_HOUR; 
    inst1.output.command.inverter_torque_limit[0] = 0.0f; 
    auto command_below_no_regen = test.getDrivetrainCommand(
        ControllerMode_e::MODE_0,
        TorqueLimit_e::TCMUX_LOW_TORQUE,
        mode_1_input_state
    );
    ASSERT_EQ(command_below_no_regen.inverter_torque_limit[0], 0.0f); 

    DrivetrainDynamicReport_s drivetrain_data_above_no_regen = {};
    drivetrain_data_above_no_regen.measuredSpeeds[0] = 15.0f / RPM_TO_KILOMETERS_PER_HOUR; 
    inst1.output.command.inverter_torque_limit[0] = 10.0f; 
    auto command_above_no_regen = test.getDrivetrainCommand(
        ControllerMode_e::MODE_0,
        TorqueLimit_e::TCMUX_LOW_TORQUE,
        mode_1_input_state
    );
    ASSERT_GT(command_above_no_regen.inverter_torque_limit[0], 0.0f); 
  
    DrivetrainDynamicReport_s drivetrain_data_between_limits = {};
    drivetrain_data_between_limits.measuredSpeeds[0] = 8.0f / RPM_TO_KILOMETERS_PER_HOUR; 
    inst1.output.command.inverter_torque_limit[0] = 10.0f; 
    auto command_between_limits = test.getDrivetrainCommand(
        ControllerMode_e::MODE_0,
        TorqueLimit_e::TCMUX_LOW_TORQUE,
        mode_1_input_state
    );
    ASSERT_LE(command_between_limits.inverter_torque_limit[0], 10.0f); 
} 



TEST(TorqueControllerMuxTesting, test_apply_positive_speed_limit) 
{
    TestControllerType inst1;
    set_output_rpm(inst1, -300, 10.0); 
    inst1.output.command.inverter_torque_limit[0] = 5;
    TorqueControllerMux<1> test({static_cast<Controller *>(&inst1)}, {false});
    SharedCarState_s mode_1_input_state({}, {}, {}, {}, {.accelPercent = 0.5f, .brakePercent = 0.0f, .regenPercent = 0.0}, {}, {}, {});

    // apply speed limit happens in here
    auto drive_command = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_LOW_TORQUE, mode_1_input_state);

    ASSERT_EQ(drive_command.speeds_rpm[0], 0.0f);
    ASSERT_EQ(drive_command.speeds_rpm[1], 0.0f);
    ASSERT_EQ(drive_command.speeds_rpm[2], 0.0f);
    ASSERT_EQ(drive_command.speeds_rpm[3], 0.0f);

    printf("Speed 1: %.2f\n", drive_command.speeds_rpm[0]);
    printf("Speed 2: %.2f\n", drive_command.speeds_rpm[1]);
    printf("Speed 3: %.2f\n", drive_command.speeds_rpm[2]);
    printf("Speed 4: %.2f\n", drive_command.speeds_rpm[3]);

} 

//integration testing
TEST(TorqueControllerMuxTesting, test_tc_mux_status)
{
    TorqueControllerMuxError testErr = TorqueControllerMuxError::NO_ERROR;
    ControllerMode_e testMode = ControllerMode_e::MODE_0;
    TorqueLimit_e testTorqLim = TorqueLimit_e::TCMUX_FULL_TORQUE;
    TestControllerType inst1;
    set_outputs(inst1, 0, 1);
    TorqueControllerMux<1> test({static_cast<Controller *>(&inst1)}, { false });
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    set_four_outputs(state.drivetrain_data.measuredSpeeds, 2);

    state.pedals_data = {};
    state.vn_data = {};
 
    auto out1 = test.getDrivetrainCommand(testMode, testTorqLim, state);
    ASSERT_EQ(test.get_tc_mux_status().active_error, testErr);
    ASSERT_EQ(test.get_tc_mux_status().active_controller_mode, testMode);
    ASSERT_EQ(test.get_tc_mux_status().active_torque_limit_enum, testTorqLim);
}
//set shared car state so that it does not randomly pass and not pass anymore
TEST(TorqueControllerMuxTesting, test_real_controllers_output)
{
    //mode 0
    TorqueControllerSimple tc_simple(1.0f, 1.0f);
    // mode 1
    TorqueControllerLoadCellVectoring tc_vec;
    // mode 2
    DummyQueue_s q;
    CASEConfiguration config = {
    .TorqueMode = 0,  
    .max_torque = PhysicalParameters::AMK_MAX_TORQUE  
    };
    CASESystem<DummyQueue_s> case_sys(&q, 100, 70, 550, config);
    TorqueControllerCASEWrapper<DummyQueue_s> case_wrapper(&case_sys);
 
    // mode 3
    TorqueControllerSimpleLaunch simple_launch;
    // mode 4
    TorqueControllerSlipLaunch slip_launch;
 
    TorqueControllerMux<5>
        torque_controller_mux({static_cast<Controller *>(&tc_simple),
                               static_cast<Controller *>(&tc_vec),
                               static_cast<Controller *>(&case_wrapper),
                               static_cast<Controller *>(&simple_launch),
                               static_cast<Controller *>(&slip_launch)},
                              {false, false, false, false, false});
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    state.pedals_data = {};
    state.vn_data = {};
    state.drivetrain_data = { 0, {}, {}, {}, {} };

    auto out1 = torque_controller_mux.getDrivetrainCommand(ControllerMode_e::MODE_3, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(static_cast<int>(torque_controller_mux.get_tc_mux_status().active_error), static_cast<int>(TorqueControllerMuxError::NO_ERROR));
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_3);

    out1 = torque_controller_mux.getDrivetrainCommand(ControllerMode_e::MODE_4, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_4);

    out1 = torque_controller_mux.getDrivetrainCommand(ControllerMode_e::MODE_4, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_4);

    out1 = torque_controller_mux.getDrivetrainCommand(ControllerMode_e::MODE_3, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_3);
    
    out1 = torque_controller_mux.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
   
    out1 = torque_controller_mux.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
    ASSERT_EQ(torque_controller_mux.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_1);
}

void set_state_mcu(SharedCarState_s & state)
{
        state.vn_data = {
        .velocity_x = 0.0f,
        .velocity_y = 0.0f,
        .velocity_z = 0.0f,
        .linear_accel_x = 0.0f,
        .linear_accel_y = 0.0f,
        .linear_accel_z = 0.0f,
        .uncompLinear_accel = { 0.0f, 0.0f, 0.0f },  
        .yaw = 0.0f,
        .pitch = 0.0f,
        .roll = 0.0f,
        .latitude = 0.0f,
        .longitude = 0.0f,
        .ecef_coords = { 0.0f, 0.0f, 0.0f },
        .gps_time = 0,
        .vn_status = 0,
        .angular_rates = { 0.0f, 0.0f, 0.0f }
    };
    state.steering_data = SteeringSystemData_s{
        .angle = 0,
        .status = SteeringSystemStatus_e::STEERING_SYSTEM_NOMINAL
    };
    state.drivetrain_data = DrivetrainDynamicReport_s{
        .measuredInverterFLPackVoltage = 26,     
        .measuredSpeeds = {0.0f, 0.0f, 0.0f, 0.0f}, 
        .measuredTorques = {0.0f, 0.0f, 0.0f, 0.0f}, 
        .measuredTorqueCurrents = {0.0f, 0.0f, 0.0f, 0.0f}, 
        .measuredMagnetizingCurrents = {0.0f, 0.0f, 0.0f, 0.0f} 
    };
    state.pedals_data = PedalsSystemData_s{
        .accelImplausible = false,                  
        .brakeImplausible = false,                   
        .brakePressed = false,                       
        .accelPressed = false,                       
        .mechBrakeActive = false,                    
        .brakeAndAccelPressedImplausibility = false, 
        .implausibilityExceededMaxDuration = false,  
        .accelPercent = 0.0f,                       
        .brakePercent = 0.0f,                       
        .regenPercent = 0.0f                        
    };
    state.loadcell_data = LoadCellInterfaceOutput_s{
        .loadCellForcesFiltered = {100.0f, 100.0f, 100.0f, 100.0f},  
        .loadCellConversions = { },  
        .FIRSaturated = true       
    };
    state.systick = SysTick_s{
        .millis = 10,
        .micros = 10,
        .triggers = TriggerBits_s{
            .trigger1000 = true,
            .trigger500 = true,
            .trigger100 = true,
            .trigger50 = true,
            .trigger10 = true,
            .trigger5 = true,
            .trigger1 = true
        },
    };
}

TEST(TorqueControllerMuxTesting, test_state_machine_progression_simple_controller)
{
    //recreating environment in CAR_STATE::READY_TO_DRIVE in MCU
    //which is when the tc mux is used to request torque from active controller
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    set_state_mcu(state);

    //make tc mux to see if under these conditions it is sending out correct commands
    //mode 0
    TorqueControllerSimple tc_simple(1.0f, 1.0f);
 
    TorqueControllerMux<1> test_mux0({static_cast<Controller *>(&tc_simple)}, {false});

    //expected command 

    DrivetrainCommand_s expected = DrivetrainCommand_s
    {
        .speeds_rpm = { PhysicalParameters::AMK_MAX_RPM , PhysicalParameters::AMK_MAX_RPM , PhysicalParameters::AMK_MAX_RPM , PhysicalParameters::AMK_MAX_RPM },
        .inverter_torque_limit = { 0 , 0 , 0 , 0 }
    };

    auto out1 = test_mux0.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test_mux0.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
    ASSERT_EQ(test_mux0.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
    for(int i = 0; i < 4; i++){
        ASSERT_EQ(expected.speeds_rpm[i], out1.speeds_rpm[i]);
        ASSERT_EQ(expected.inverter_torque_limit[i], out1.inverter_torque_limit[i]);
    }

    state.pedals_data.accelPercent = .5f;
    state.pedals_data.accelPressed = true;
    expected = DrivetrainCommand_s
    {
        .speeds_rpm = { PhysicalParameters::AMK_MAX_RPM , PhysicalParameters::AMK_MAX_RPM , PhysicalParameters::AMK_MAX_RPM , PhysicalParameters::AMK_MAX_RPM },
        .inverter_torque_limit = { PhysicalParameters::AMK_MAX_TORQUE*.5 , PhysicalParameters::AMK_MAX_TORQUE*.5 , PhysicalParameters::AMK_MAX_TORQUE*.5 , PhysicalParameters::AMK_MAX_TORQUE*.5}
    };
    out1 = test_mux0.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    for(int i = 0; i < 4; i++){
        ASSERT_EQ(expected.speeds_rpm[i], out1.speeds_rpm[i]);
        ASSERT_EQ(expected.inverter_torque_limit[i], out1.inverter_torque_limit[i]);
    }

    state.pedals_data.accelPercent = 0;
    state.pedals_data.regenPercent = .5f;
    state.pedals_data.accelPressed = true;
    expected = DrivetrainCommand_s
    {
        .speeds_rpm = { 0 , 0 , 0 , 0 },
        .inverter_torque_limit = { 0 , 0 , 0 , 0}
    };
    out1 = test_mux0.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    for(int i = 0; i < 4; i++){
        ASSERT_EQ(expected.speeds_rpm[i], out1.speeds_rpm[i]);
        ASSERT_EQ(expected.inverter_torque_limit[i], out1.inverter_torque_limit[i]);
    }
}
TEST(TorqueControllerMuxTesting, test_state_machine_progression_launch_controller)
{
    //recreating environment in CAR_STATE::READY_TO_DRIVE in MCU
    //which is when the tc mux is used to request torque from active controller
    SharedCarState_s state({}, {}, {}, {}, {}, {}, {}, {});
    set_state_mcu(state);

    //make tc mux to see if under these conditions it is sending out correct commands
    // mode 1
    TorqueControllerSimpleLaunch tc_sl;
   
    TorqueControllerMux<1> test_mux0({static_cast<Controller *>(&tc_sl)}, {false});

    //expected command for launch not ready

    DrivetrainCommand_s expected = DrivetrainCommand_s
    {
        .speeds_rpm = { 0 , 0 , 0 , 0 },
        .inverter_torque_limit = { 0 , 0 , 0 , 0 }
    };

    //makes sure launch not ready state is initialized and it moves to next state while outputting command with no torque or speed
    ASSERT_EQ(tc_sl.get_launch_state(), LaunchStates_e::LAUNCH_NOT_READY);
    auto out1 = test_mux0.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test_mux0.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
    ASSERT_EQ(test_mux0.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
    ASSERT_EQ(tc_sl.get_launch_state(), LaunchStates_e::LAUNCH_READY);
    for(int i = 0; i < 4; i++){
        ASSERT_EQ(expected.speeds_rpm[i], out1.speeds_rpm[i]);
        ASSERT_EQ(expected.inverter_torque_limit[i], out1.inverter_torque_limit[i]);
    }

    //ensures that from this state, it transitions from launch ready to launching when accelerator is pressed, still outputs a command with no torque or speed
    state.pedals_data.accelPercent = .9;
    out1 = test_mux0.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    ASSERT_EQ(test_mux0.get_tc_mux_status().active_error, TorqueControllerMuxError::NO_ERROR);
    ASSERT_EQ(test_mux0.get_tc_mux_status().active_controller_mode, ControllerMode_e::MODE_0);
    ASSERT_EQ(tc_sl.get_launch_state(), LaunchStates_e::LAUNCHING);
    for(int i = 0; i < 4; i++){
        ASSERT_EQ(expected.speeds_rpm[i], out1.speeds_rpm[i]);
        ASSERT_EQ(expected.inverter_torque_limit[i], out1.inverter_torque_limit[i]);
    }

    //ensures during launch that speed target increases and torque is requested
    expected = DrivetrainCommand_s
    {   
        //calculated values for rpm based on time elapsed + algo
        .speeds_rpm = { 7989 , 7989 , 7989 , 7989 },
        .inverter_torque_limit = { PhysicalParameters::AMK_MAX_TORQUE , PhysicalParameters::AMK_MAX_TORQUE , PhysicalParameters::AMK_MAX_TORQUE , PhysicalParameters::AMK_MAX_TORQUE}
    };
    state.systick.millis = 1000;
    out1 = test_mux0.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    for(int i = 0; i < 4; i++){
        ASSERT_EQ(expected.speeds_rpm[i], out1.speeds_rpm[i]);
        ASSERT_EQ(expected.inverter_torque_limit[i], out1.inverter_torque_limit[i]);
    }

    //again
    expected = DrivetrainCommand_s
    {
        //calculated values for rpm based on time elapsed + algo
        .speeds_rpm = { 14543 , 14543 , 14543 , 14543 },
        .inverter_torque_limit = { PhysicalParameters::AMK_MAX_TORQUE , PhysicalParameters::AMK_MAX_TORQUE , PhysicalParameters::AMK_MAX_TORQUE , PhysicalParameters::AMK_MAX_TORQUE}
    };
    state.systick.millis = 2000;
    out1 = test_mux0.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    for(int i = 0; i < 4; i++){
        ASSERT_EQ(expected.speeds_rpm[i], out1.speeds_rpm[i]);
        ASSERT_EQ(expected.inverter_torque_limit[i], out1.inverter_torque_limit[i]);
    }
    
}
#endif // __TC_MUX_V2_TESTING_H__