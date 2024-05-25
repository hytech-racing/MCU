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

        .AbsoluteTorqueLimit = AMK_MAX_TORQUE, // N-m
        .yaw_pid_p = 1.33369,
        .yaw_pid_i = 0.25,
        .yaw_pid_d = 0.0,
        .tcs_pid_p = 40.0,
        .tcs_pid_i = 0.0,
        .tcs_pid_d = 0.0,
        .useLaunch = false,
        .usePIDTV = true,
        .useTCSLimitedYawPID = true,
        .useNormalForce = false,
        .useTractionControl = true,
        .usePowerLimit = false,
        .usePIDPowerLimit = false,
        .useDecoupledYawBrakes = false,
        .useDiscontinuousYawPIDBrakes = true,
        .tcsSLThreshold = 0.2,
        .launchSL = 0.2,
        .launchDeadZone = 20,        // N-m
        .launchVelThreshold = 0.75,  // m/s
        .tcsVelThreshold = 2.5,      // m/s
        .yawPIDMaxDifferential = 10, // N-m
        .yawPIDErrorThreshold = 0.1, // rad/s
        .yawPIDVelThreshold = 1,     // m/s
        .yawPIDCoastThreshold = 2.5, // m/s
        .yaw_pid_brakes_p = 0.25,
        .yaw_pid_brakes_i = 0,
        .yaw_pid_brakes_d = 0,
        .decoupledYawPIDBrakesMaxDIfference = 2, // N-m
        .discontinuousBrakesPercentThreshold = 0.4,
        .TorqueMode = AMK_MAX_TORQUE, // N-m
        .RegenLimit = -10.0,          // N-m

        .max_rpm = AMK_MAX_RPM,
        .max_regen_torque = AMK_MAX_TORQUE,
        .max_torque = AMK_MAX_TORQUE,
    };
    CASESystem case_system(&faked_msg_q, 100, 70, case_config);
}
