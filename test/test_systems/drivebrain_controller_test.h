#ifndef DRIVEBRAIN_CONTROLLER_TEST
#define DRIVEBRAIN_CONTROLLER_TEST
#include <gtest/gtest.h>
#include <DrivebrainController.h>
#include <DrivebrainData.h>

auto runTick(DrivebrainController *controller, float last_DB_receive_time_millis, float last_receive_time_millis, ControllerMode_e current_control_mode, unsigned long systick_millis)
{
    DrivebrainData_s data;
    data.last_receive_time_millis = last_receive_time_millis;
    data.DB_prev_MCU_recv_millis = last_DB_receive_time_millis;
    data.torque_limits_nm = {1, 1, 1, 1};
    data.speed_setpoints_rpm = {1, 1, 1, 1};

    SysTick_s systick;
    systick.millis = systick_millis;
    systick.micros = 1000;

    TorqueControllerMuxStatus status = {};
    status.active_controller_mode = current_control_mode;
    SharedCarState_s state(systick, {}, {}, {}, {}, {}, data, status);
    return controller->evaluate(state);
}

TEST(DrivebrainControllerTesting, signals_sent_within_range)
{
    DrivebrainController controller(10);
    auto torque_controller_output_s = runTick(&controller, 998, 1001, ControllerMode_e::MODE_4, 1002);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, setpoint_too_latent)
{
    DrivebrainController controller(5);
    auto torque_controller_output_s = runTick(&controller, 800, 1006, ControllerMode_e::MODE_4, 1012);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, failing_stay_failing)
{
    DrivebrainController controller(10);
    auto torque_controller_output_s = runTick(&controller, 200, 1011, ControllerMode_e::MODE_4, 1032);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

    torque_controller_output_s = runTick(&controller, 200, 1033, ControllerMode_e::MODE_4, 1033);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

    torque_controller_output_s = runTick(&controller, 400, 1034, ControllerMode_e::MODE_4, 1034);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, failing_reset_success)
{
    DrivebrainController controller(10);
    auto torque_controller_output_s = runTick(&controller, 300, 1011, ControllerMode_e::MODE_4, 1022);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

    torque_controller_output_s = runTick(&controller, 1020, 1021, ControllerMode_e::MODE_3, 1023);
    torque_controller_output_s = runTick(&controller, 1022, 1022, ControllerMode_e::MODE_4, 1024);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

#endif