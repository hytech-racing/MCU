#ifndef DRIVEBRAIN_CONTROLLER_TEST
#define DRIVEBRAIN_CONTROLLER_TEST
#include <gtest/gtest.h>
#include <DrivebrainController.h>
#include <DrivebrainData.h>

auto runTick(DrivebrainController *controller, float last_torque_lim_receive_time_millis, float last_speed_setpoint_receive_time_millis, ControllerMode_e current_control_mode)
{
    DrivebrainData_s data;
    data.last_torque_lim_receive_time_millis = last_torque_lim_receive_time_millis;
    data.last_speed_setpoint_receive_time_millis = last_speed_setpoint_receive_time_millis;
    data.torque_limits_nm = {1, 1, 1, 1};
    data.speed_setpoints_rpm = {1, 1, 1, 1};

    SysTick_s systick;
    systick.millis = 1000;
    systick.micros = 1000;

    TorqueControllerMuxStatus status = {};
    status.current_controller_mode_ = current_control_mode;
    SharedCarState_s state(systick, {}, {}, {}, {}, {}, data, status);
    return controller->evaluate(state);
}

TEST(DrivebrainControllerTesting, signals_sent_within_range)
{
    DrivebrainController controller(10, 10);
    auto torque_controller_output_s = runTick(&controller, 1001, 1009, ControllerMode_e::MODE_4);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, speed_setpoint_too_latent)
{
    DrivebrainController controller(5, 5);
    auto torque_controller_output_s = runTick(&controller, 1001, 1006, ControllerMode_e::MODE_4);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, torque_setpoint_too_latent)
{
    DrivebrainController controller(5, 5);
    auto torque_controller_output_s = runTick(&controller, 1006, 1001, ControllerMode_e::MODE_4);

    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, msg_jitter_too_high)
{
    DrivebrainController controller(10, 5);
    auto torque_controller_output_s = runTick(&controller, 1001, 1009, ControllerMode_e::MODE_4);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, speed_setpoint_too_latent_and_torque_setpoint_too_latent)
{
    DrivebrainController controller(5, 10);
    auto torque_controller_output_s = runTick(&controller, 1001, 1015, ControllerMode_e::MODE_4);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, speed_setpoint_too_latent_and_msg_jitter_too_high)
{
    DrivebrainController controller(10, 5);
    auto torque_controller_output_s = runTick(&controller, 1011, 1001, ControllerMode_e::MODE_4);

    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, torque_setpoint_too_latent_and_msg_jitter_too_high)
{
    DrivebrainController controller(10, 5);
    auto torque_controller_output_s = runTick(&controller, 1001, 1011, ControllerMode_e::MODE_4);

    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, failing_stay_failing)
{
    DrivebrainController controller(10, 5);
    auto torque_controller_output_s = runTick(&controller, 1001, 1011, ControllerMode_e::MODE_4);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

    torque_controller_output_s = runTick(&controller, 1001, 1001, ControllerMode_e::MODE_4);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, failing_reset_success)
{
    DrivebrainController controller(10, 5);
    auto torque_controller_output_s = runTick(&controller, 1001, 1011, ControllerMode_e::MODE_4);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

    torque_controller_output_s = runTick(&controller, 1001, 1001, ControllerMode_e::MODE_3);

    torque_controller_output_s = runTick(&controller, 1001, 1001, ControllerMode_e::MODE_4);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

#endif