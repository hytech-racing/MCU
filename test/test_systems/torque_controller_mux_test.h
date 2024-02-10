#ifndef TORQUE_CONTROLLER_MUX_TEST
#define TORQUE_CONTROLLER_MUX_TEST

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SysClock.h>
#include <TorqueControllerMux.h>
#include <PedalsSystem.h>
#include <SteeringSystem.h>
#include "AnalogSensorsInterface.h"
#include "DashboardInterface.h"
#include "PhysicalParameters.h"

// TODO: Find out why this test intermittently fails
// TEST(TorqueControllerMuxTesting, test_torque_button)
// {
//     const int SERIES_LENGTH = 10;
//     SysClock clock = SysClock();
//     SysTick_s cur_tick;
//     TorqueControllerMux torque_controller_mux = TorqueControllerMux();

//     bool buttonTimeSeries[SERIES_LENGTH]; // 50hz time series
//     // Cycle back to low test
//     buttonTimeSeries[1] = true;
//     buttonTimeSeries[3] = true;
//     buttonTimeSeries[5] = true;
//     // Cycle only on button release test
//     for (int i = 7; i < SERIES_LENGTH; i++)
//         buttonTimeSeries[i] = true;

//     ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_LOW_TORQUE);

//     // Run test
//     for (int i = 0; i < SERIES_LENGTH; i++)
//     {
//         cur_tick = clock.tick(i * 1000 * 20); // 20 ms increments
//         torque_controller_mux.tick(
//             cur_tick,
//             (const DrivetrainDynamicReport_s) {},
//             (const PedalsSystemData_s) {},
//             (const SteeringSystemData_s) {},
//             (const AnalogConversion_s) {},
//             (const AnalogConversion_s) {},
//             (const AnalogConversion_s) {},
//             (const AnalogConversion_s) {},
//             DialMode_e::MODE_1,
//             buttonTimeSeries[i]
//         );
//         // Test conditions
//         if (i == 2)
//             ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_MID_TORQUE);
//         if (i == 4)
//             ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_FULL_TORQUE);
//         if (i == 6)
//             ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_LOW_TORQUE);
//         if (i == SERIES_LENGTH - 1)
//             ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_LOW_TORQUE);
//     }
// }

TEST(TorqueControllerMuxTesting, test_torque_delta_prevents_mode_change)
{
    SysClock clock = SysClock();
    SysTick_s cur_tick;
    cur_tick = clock.tick(0);
    TorqueControllerMux torque_controller_mux = TorqueControllerMux();
    DrivetrainCommand_s resulting_torque_command;

    DrivetrainDynamicReport_s simulated_drivetrain_dynamics = {
        .measuredInverterFLPackVoltage = 550,
        .measuredSpeeds = {0.0, 0.0, 0.0, 0.0},
        .measuredTorques = {0.0, 0.0, 0.0, 0.0},
        .measuredTorqueCurrents = {0.0, 0.0, 0.0, 0.0},
        .measuredMagnetizingCurrents = {0.0, 0.0, 0.0, 0.0}
    };

    PedalsSystemData_s simulated_full_accel_press = {
        .accelImplausible = false,
        .brakeImplausible = false,
        .brakePressed = false,
        .brakeAndAccelPressedImplausibility = false,
        .implausibilityExceededMaxDuration = false,
        .accelPercent = 1.0,
        .brakePercent = 0.0
    };

    PedalsSystemData_s simulated_no_accel_press = {
        .accelImplausible = false,
        .brakeImplausible = false,
        .brakePressed = false,
        .brakeAndAccelPressedImplausibility = false,
        .implausibilityExceededMaxDuration = false,
        .accelPercent = 0.0,
        .brakePercent = 0.0
    };

    // Press the pedal and observe whether torque mode changes
    // Torque mode should not change since the requested torque is vastly different from the currently requested torque (0)
    torque_controller_mux.tick(
        cur_tick,
        simulated_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_1,
        false
    );

    resulting_torque_command = torque_controller_mux.getDrivetrainCommand();

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        ASSERT_LE(resulting_torque_command.torqueSetpoints[i], 0.0001);
        ASSERT_LE(resulting_torque_command.speeds_rpm[i], 0.0001);
    }

    // Release the pedal. The mode should change now
    torque_controller_mux.tick(
        cur_tick,
        simulated_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_1,
        false
    );

    // Now press the pedal again. Torque should be requested
    torque_controller_mux.tick(
        cur_tick,
        simulated_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_1,
        false
    );

    resulting_torque_command = torque_controller_mux.getDrivetrainCommand();

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        ASSERT_GT(resulting_torque_command.torqueSetpoints[i], 5.0);
        ASSERT_GT(resulting_torque_command.speeds_rpm[i], 5.0);
    }    
}

TEST(TorqueControllerMuxTesting, test_speed_delta_prevents_mode_change)
{
    SysClock clock = SysClock();
    SysTick_s cur_tick;
    cur_tick = clock.tick(0);
    TorqueControllerMux torque_controller_mux = TorqueControllerMux();
    DrivetrainCommand_s resulting_torque_command;

    DrivetrainDynamicReport_s simulated_slow_drivetrain_dynamics = {
        .measuredInverterFLPackVoltage = 550,
        .measuredSpeeds = {
            ((MAX_SPEED_FOR_MODE_CHANGE - 0.1f) * METERS_PER_SECOND_TO_RPM), 
            ((MAX_SPEED_FOR_MODE_CHANGE - 0.1f) * METERS_PER_SECOND_TO_RPM), 
            ((MAX_SPEED_FOR_MODE_CHANGE - 0.1f) * METERS_PER_SECOND_TO_RPM), 
            ((MAX_SPEED_FOR_MODE_CHANGE - 0.1f) * METERS_PER_SECOND_TO_RPM)
        },
        .measuredTorques = {0.0, 0.0, 0.0, 0.0},
        .measuredTorqueCurrents = {0.0, 0.0, 0.0, 0.0},
        .measuredMagnetizingCurrents = {0.0, 0.0, 0.0, 0.0}
    };

    DrivetrainDynamicReport_s simulated_fast_drivetrain_dynamics = {
        .measuredInverterFLPackVoltage = 550,
        .measuredSpeeds = {
            ((MAX_SPEED_FOR_MODE_CHANGE + 0.1f) * METERS_PER_SECOND_TO_RPM), 
            ((MAX_SPEED_FOR_MODE_CHANGE + 0.1f) * METERS_PER_SECOND_TO_RPM), 
            ((MAX_SPEED_FOR_MODE_CHANGE + 0.1f) * METERS_PER_SECOND_TO_RPM), 
            ((MAX_SPEED_FOR_MODE_CHANGE + 0.1f) * METERS_PER_SECOND_TO_RPM)
        },
        .measuredTorques = {0.0, 0.0, 0.0, 0.0},
        .measuredTorqueCurrents = {0.0, 0.0, 0.0, 0.0},
        .measuredMagnetizingCurrents = {0.0, 0.0, 0.0, 0.0}
    };

    PedalsSystemData_s simulated_full_accel_press = {
        .accelImplausible = false,
        .brakeImplausible = false,
        .brakePressed = false,
        .brakeAndAccelPressedImplausibility = false,
        .implausibilityExceededMaxDuration = false,
        .accelPercent = 1.0,
        .brakePercent = 0.0
    };

    PedalsSystemData_s simulated_no_accel_press = {
        .accelImplausible = false,
        .brakeImplausible = false,
        .brakePressed = false,
        .brakeAndAccelPressedImplausibility = false,
        .implausibilityExceededMaxDuration = false,
        .accelPercent = 0.0,
        .brakePercent = 0.0
    };

    // Pretend the drivetrain is moving above MAX_SPEED_FOR_MODE_CHANGE and attempt mode shift (TC_NO_CONTROLLER to TC_SAFE_MODE) via tick
    // Torque mode should not change since the car is moving
    torque_controller_mux.tick(
        cur_tick,
        simulated_fast_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_1,
        false
    );

    resulting_torque_command = torque_controller_mux.getDrivetrainCommand();

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        ASSERT_LE(resulting_torque_command.torqueSetpoints[i], 0.0001);
        ASSERT_LE(resulting_torque_command.speeds_rpm[i], 0.0001);
    }

    // Tell TCMUX vehicle is stationary. Mode should change
    torque_controller_mux.tick(
        cur_tick,
        simulated_slow_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_1,
        false
    );

    // Now press the pedal. Torque should be requested
    torque_controller_mux.tick(
        cur_tick,
        simulated_slow_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_1,
        false
    );

    resulting_torque_command = torque_controller_mux.getDrivetrainCommand();

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        ASSERT_GT(resulting_torque_command.torqueSetpoints[i], 5.0);
        ASSERT_GT(resulting_torque_command.speeds_rpm[i], 5.0);
    }    
}

#endif /* TORQUE_CONTROLLER_MUX_TEST */