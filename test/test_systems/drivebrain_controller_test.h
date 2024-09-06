#ifndef DRIVEBRAIN_CONTROLLER_TEST
#define DRIVEBRAIN_CONTROLLER_TEST
#include <gtest/gtest.h>
#include <DrivebrainController.h>
#include <DrivebrainData.h>


void runTick(unsigned int allowed_latency, unsigned int allowed_jitter, float last_torque_lim_receive_time_millis, float last_speed_setpoint_receive_time_millis, TorqueControllerOutput_s *torque_controller_output_s) {
    DrivebrainController controller(*torque_controller_output_s, allowed_latency, allowed_jitter);
    DrivebrainData data;
    data.last_torque_lim_receive_time_millis = last_torque_lim_receive_time_millis;
    data.last_speed_setpoint_receive_time_millis = last_speed_setpoint_receive_time_millis;
    data.torque_limits_nm = {1, 1, 1, 1};
    data.speed_setpoints_rpm = {1, 1, 1, 1};

    SysTick_s systick;
    systick.millis = 1000;
    systick.micros = 1000;
    controller.tick(systick, data);
}

TEST(DrivebrainControllerTesting, signals_sent_within_range) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    runTick(10, 10, 1001, 1009, &torque_controller_output_s);

    EXPECT_TRUE(torque_controller_output_s.ready);
    EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, speed_setpoint_too_latent) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    runTick(5, 5, 1001, 1006, &torque_controller_output_s);

    EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_NE(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, torque_setpoint_too_latent) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    runTick(5, 5, 1006, 1001, &torque_controller_output_s);

    EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_NE(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, msg_jitter_too_high) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    runTick(10, 5, 1001, 1009, &torque_controller_output_s);

    EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_NE(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, speed_setpoint_too_latent_and_torque_setpoint_too_latent) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    runTick(5, 10, 1001, 1015, &torque_controller_output_s);

    EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_NE(torque_controller_output_s.command.speeds_rpm[0], 1);
}


TEST(DrivebrainControllerTesting, speed_setpoint_too_latent_and_msg_jitter_too_high) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    runTick(10, 5, 1011, 1001, &torque_controller_output_s);

    EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_NE(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, torque_setpoint_too_latent_and_msg_jitter_too_high) {
    TorqueControllerOutput_s torque_controller_output_s = {};
    runTick(10, 5, 1001, 1011, &torque_controller_output_s);

    EXPECT_FALSE(torque_controller_output_s.ready);
    EXPECT_NE(torque_controller_output_s.command.speeds_rpm[0], 1);
}

#endif DRIVEBRAIN_CONTROLLER_TEST