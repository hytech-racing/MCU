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

        // Following used for generated code
        .AbsoluteTorqueLimit = AMK_MAX_TORQUE, // N-m, Torque limit used for yaw pid torque split overflow
        .yaw_pid_p = 1.369,
        .yaw_pid_i = 0.25,
        .yaw_pid_d = 0.0,
        .tcs_pid_p_lowerBound_front = 35.0, // if tcs_pid_p_lowerBound_front > tcs_pid_p_upperBound_front, inverse relationship, no error
        .tcs_pid_p_upperBound_front = 55.0,
        .tcs_pid_p_lowerBound_rear = 28.0,
        .tcs_pid_p_upperBound_rear = 35.0,
        .tcs_pid_i = 0.0,
        .tcs_pid_d = 0.0,
        .useLaunch = false,
        .usePIDTV = true,
        .useTCSLimitedYawPID = true,
        .useNormalForce = false,
        .useTractionControl = true,
        .usePowerLimit = true,
        .usePIDPowerLimit = false,
        .useDecoupledYawBrakes = true,
        .useDiscontinuousYawPIDBrakes = false,
        .tcsSLThreshold = 0.2,
        .launchSL = 0.2,
        .launchDeadZone = 20.0,        // N-m
        .launchVelThreshold = 0.75,    // m/s
        .tcsVelThreshold = 2.5,        // m/s
        .yawPIDMaxDifferential = 10.0, // N-m
        .yawPIDErrorThreshold = 0.1,   // rad/s
        .yawPIDVelThreshold = 1.0,     // m/s
        .yawPIDCoastThreshold = 2.5,   // m/s
        .yaw_pid_brakes_p = 0.25,
        .yaw_pid_brakes_i = 0.0,
        .yaw_pid_brakes_d = 0.0,
        .decoupledYawPIDBrakesMaxDIfference = 2, // N-m
        .discontinuousBrakesPercentThreshold = 0.4,
        .TorqueMode = AMK_MAX_TORQUE, // N-m
        .RegenLimit = -10.0,          // N-m
        .useNoRegen5kph = true,
        .useTorqueBias = true,
        .DriveTorquePercentFront = 0.5,
        .BrakeTorquePercentFront = 0.6,
        .MechPowerMaxkW = 63.0,            // kW
        .launchLeftRightMaxDiff = 2.0,     // N-m
        .tcs_pid_lower_rpm_front = 0.0,    // RPM
        .tcs_pid_upper_rpm_front = 5000.0, // RPM
        .tcs_pid_lower_rpm_rear = 0.0,     // RPM
        .tcs_pid_upper_rpm_rear = 5000.0,  // RPM

        // Following used for calculate_torque_request in CASESystem.tpp
        .max_rpm = AMK_MAX_RPM,
        .max_regen_torque = AMK_MAX_TORQUE,
        .max_torque = AMK_MAX_TORQUE,
    };
    CASESystem case_system(&faked_msg_q, 100, 70, 550, case_config);
}
