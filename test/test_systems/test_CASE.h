#pragma once

#include "TorqueControllers.h"
#include "CASESystem.h"
#include <gtest/gtest.h>

class FakeMessageQueue
{
public:
    FakeMessageQueue() {}
};

void enqueue_matlab_msg(FakeMessageQueue *, const CAN_MESSAGE_BUS &msg)
{
}

TEST(CASESystemTesting, test_vn_start_time)
{
    FakeMessageQueue faked_msg_q;
    CASEConfiguration case_config = {
        .torqueLimit = AMK_MAX_TORQUE, // N-m
        .yaw_pid_p = 1.0,
        .yaw_pid_i = .0,
        .yaw_pid_d = 0.0,
        .tcs_pid_p = 40.0,
        .tcs_pid_i = 0.0,
        .tcs_pid_d = 0.0,
        .useLaunch = false,
        .usePIDTV = true,
        .useTCSLimitedYawPID = false,
        .useNormalForce = false,
        .useTractionControl = false,
        .usePowerLimit = false,
        .usePIDPowerLimit = false,
        .tcsSLThreshold = 0.2,
        .launchSL = 0.2,
        .launchDeadZone = 20,        // N-m
        .launchVelThreshold = 0.75,  // m/s
        .tcsVelThreshold = 2.5,      // m/s
        .yawPIDMaxDifferential = 10, // N-m
        .yawPIDErrorThreshold = 0.1, // rad/s
        .yawPIDVelThreshold = 1,     // m/s
        .yawPIDCoastThreshold = 2.5, // m/s
        .max_rpm = AMK_MAX_RPM,
        .max_regen_torque = MAX_REGEN_TORQUE,
        .max_torque = AMK_MAX_TORQUE,
    };
    CASESystem case_system(&faked_msg_q, 100, 70, case_config);
}
