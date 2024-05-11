#ifndef __TC_MUX_V2_TESTING_H__
#define __TC_MUX_V2_TESTING_H__

#include "TorqueControllerMux.h"
#include "TorqueControllers.h"
#include "fake_controller_type.h"

struct dummy_queue
{
};

void assert_good_output()

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
    controller.output.command.torqueSetpoints[0] = torque;
    controller.output.command.torqueSetpoints[1] = torque;
    controller.output.command.torqueSetpoints[2] = torque;
    controller.output.command.torqueSetpoints[3] = torque;
}



TEST(TorqueControllerMuxTesting, test_construction)
{
    TestControllerType inst1, inst2;
    TorqueControllerMux<2> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2)}, {false, false});
}

// TEST(TorqueControllerMuxTesting, test_)

// ensure that swapping to a controller that has a higher desired output speed than previously
// commanded that we dont switch
TEST(TorqueControllerMuxTesting, test_controller_output_swap_logic)
{
    TestControllerType inst1, inst2;
    set_outputs(inst1, 0, 1);
    set_outputs(inst2, 6, 1);
    TorqueControllerMux<2> test({static_cast<Controller *>(&inst1), static_cast<Controller *>(&inst2)}, {false, false});
    car_state state({}, {}, {}, {}, {}, {});
    set_four_outputs(state.drivetrain_data.measuredSpeeds, 10000.0);

    state.pedals_data = {};
    state.vn_data = {};

    auto out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);

    // auto out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_0, TorqueLimit_e::TCMUX_FULL_TORQUE, state);
    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);

    ASSERT_EQ(test.get_tc_mux_status().current_controller_mode_, ControllerMode_e::MODE_0);
    ASSERT_EQ(test.get_tc_mux_status().current_error, TorqueControllerMuxError::ERROR_SPEED_DIFF_TOO_HIGH);

    set_outputs(inst1, 0, 1);
    set_outputs(inst2, 0, 1);
    set_four_outputs(state.drivetrain_data.measuredSpeeds, 0);

    out1 = test.getDrivetrainCommand(ControllerMode_e::MODE_1, TorqueLimit_e::TCMUX_FULL_TORQUE, state);

    ASSERT_EQ(test.get_tc_mux_status().current_controller_mode_, ControllerMode_e::MODE_1);
    ASSERT_EQ(test.get_tc_mux_status().current_error, TorqueControllerMuxError::NO_ERROR);
}

TEST(TorqueControllerMuxTesting, test_construction_with_new_controller_orgs)
{
    // mode 0
    TorqueControllerSimple tc_simple(1.0f, 1.0f);
    // mode 1
    TorqueControllerLoadCellVectoring tc_vec;
    // mode 2
    dummy_queue q;
    CASESystem<dummy_queue> case_sys(&q, 100, 70, 550, {});
    TorqueControllerCASEWrapper<dummy_queue> case_wrapper(&case_sys);

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
                              {false, true, false, false, false});
}

TEST(TorqueControllerMuxTesting, test_evaluation)
{
    // mode 0
    TorqueControllerSimple tc_simple(1.0f, 1.0f);
    // mode 1
    TorqueControllerLoadCellVectoring tc_vec;
    // mode 2
    dummy_queue q;
    CASESystem<dummy_queue> case_sys(&q, 100, 70, 550, {});
    TorqueControllerCASEWrapper<dummy_queue> case_wrapper(&case_sys);

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

    
}
#endif // __TC_MUX_V2_TESTING_H__