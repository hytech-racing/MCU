#ifndef DRIVEBRAIN_CONTROLLER_TEST
#define DRIVEBRAIN_CONTROLLER_TEST
#include <gtest/gtest.h>
#include <DrivebrainController.h>
#include <DrivebrainData.h>


void runTick(DrivebrainController *controller, float last_torque_lim_receive_time_millis, float last_speed_setpoint_receive_time_millis, bool is_active_controller) {
    // DrivebrainController controller(*torque_controller_output_s, allowed_latency, allowed_jitter);
    DrivebrainData data;
    data.last_torque_lim_receive_time_millis = last_torque_lim_receive_time_millis;
    data.last_speed_setpoint_receive_time_millis = last_speed_setpoint_receive_time_millis;
    data.torque_limits_nm = {1, 1, 1, 1};
    data.speed_setpoints_rpm = {1, 1, 1, 1};

    SysTick_s systick;
    systick.millis = 1000;
    systick.micros = 1000;
    controller->tick(systick, data, is_active_controller);
}

TEST(DrivebrainControllerTesting, signals_sent_within_range) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 10, 10);
    runTick(&controller, 1001, 1009, true);

    EXPECT_TRUE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, speed_setpoint_too_latent) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 5, 5);
    runTick(&controller, 1001, 1006, true);

    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, torque_setpoint_too_latent) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 5, 5);
    runTick(&controller, 1006, 1001, true);

    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, msg_jitter_too_high) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 10, 5);
    runTick(&controller, 1001, 1009, true);

    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, speed_setpoint_too_latent_and_torque_setpoint_too_latent) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 5, 10);
    runTick(&controller, 1001, 1015, true);

    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}


TEST(DrivebrainControllerTesting, speed_setpoint_too_latent_and_msg_jitter_too_high) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 10, 5);
    runTick(&controller, 1011, 1001, true);

    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, torque_setpoint_too_latent_and_msg_jitter_too_high) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 10, 5);
    runTick(&controller, 1001, 1011, true);

    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, failing_stay_failing) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 10, 5);
    runTick(&controller, 1001, 1011, true);
    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

    runTick(&controller, 1001, 1001, true);
    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, failing_reset_success) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    DrivebrainController controller(torque_controller_output_s, 10, 5);
    runTick(&controller, 1001, 1011, true);
    // EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
    
    runTick(&controller, 1001, 1001, false);

    runTick(&controller, 1001, 1001, true);
    // EXPECT_TRUE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

#endif DRIVEBRAIN_CONTROLLER_TEST