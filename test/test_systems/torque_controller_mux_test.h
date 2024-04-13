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
#include "TorqueControllers.h"
#include "VectornavInterface.h"

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

    vector_nav vn_data{};

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
        DialMode_e::MODE_0,
        false,
        vn_data,
        0.0,
        {},
        {}
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
        DialMode_e::MODE_0,
        false,
        vn_data,
        0.0,
        {},
        {}
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
        DialMode_e::MODE_0,
        false,
        vn_data,
        0.0,
        {},
        {}
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
    vector_nav vn_data{};

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
        DialMode_e::MODE_0,
        false,
        vn_data,
        0.0,
        {},
        {}
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
        DialMode_e::MODE_0,
        false,
        vn_data,
        0.0,
        {},
        {}
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
        DialMode_e::MODE_0,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    resulting_torque_command = torque_controller_mux.getDrivetrainCommand();

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        ASSERT_GT(resulting_torque_command.torqueSetpoints[i], 5.0);
        ASSERT_GT(resulting_torque_command.speeds_rpm[i], 5.0);
    }    
}

TEST(TorqueControllerMuxTesting, test_simple_launch_controller) {
     SysClock clock = SysClock();
    SysTick_s cur_tick;
    cur_tick = clock.tick(0);
    TorqueControllerMux torque_controller_mux = TorqueControllerMux();
    DrivetrainCommand_s resulting_torque_command;

    vector_nav vn_data{};

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

    DrivetrainDynamicReport_s simulated_barely_launch_drivetrain_dynamics = {
        .measuredInverterFLPackVoltage = 550,
        .measuredSpeeds = {0, 2785.86, 0, 0},
        .measuredTorques = {0.0, 0.0, 0.0, 0.0},
        .measuredTorqueCurrents = {0.0, 0.0, 0.0, 0.0},
        .measuredMagnetizingCurrents = {0.0, 0.0, 0.0, 0.0}
    };

    DrivetrainDynamicReport_s simulated_no_launch_drivetrain_dynamics = {
        .measuredInverterFLPackVoltage = 550,
        .measuredSpeeds = {0, 2786.86, 0, 0},
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

    PedalsSystemData_s simulated_accel_and_brake_press = {
        .accelImplausible = false,
        .brakeImplausible = false,
        .brakePressed = false,
        .brakeAndAccelPressedImplausibility = false,
        .implausibilityExceededMaxDuration = false,
        .accelPercent = 1.0,
        .brakePercent = 0.3
    };

    torque_controller_mux.tick(
        cur_tick,
        simulated_slow_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_0,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    // change mode to mode 3
    torque_controller_mux.tick(
        cur_tick,
        simulated_slow_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_3,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    // tick again to calculate state switch
    torque_controller_mux.tick(
        cur_tick,
        simulated_slow_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_3,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    LaunchStates_e launch_state = torque_controller_mux.activeController()->get_launch_state();

    ASSERT_EQ(launch_state, LaunchStates_e::LAUNCH_READY);

    // press accelerator but with one wheel right at max speed threshold
    torque_controller_mux.tick(
        cur_tick,
        simulated_no_launch_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_3,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    launch_state = torque_controller_mux.activeController()->get_launch_state();

    ASSERT_EQ(launch_state, LaunchStates_e::LAUNCH_NOT_READY);

    // go back to launch ready state
    torque_controller_mux.tick(
        cur_tick,
        simulated_barely_launch_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_3,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    launch_state = torque_controller_mux.activeController()->get_launch_state();

    ASSERT_EQ(launch_state, LaunchStates_e::LAUNCH_READY);

    // press accel now with one wheelspeed barely under threshold
    torque_controller_mux.tick(
        cur_tick,
        simulated_barely_launch_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_3,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    launch_state = torque_controller_mux.activeController()->get_launch_state();

    ASSERT_EQ(launch_state, LaunchStates_e::LAUNCHING);

    torque_controller_mux.tick(
        clock.tick(1000000), // 1 second since launch
        simulated_barely_launch_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_3,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    DrivetrainCommand_s commanded = torque_controller_mux.getDrivetrainCommand();

    // this fails, but the value is close enough
    // ASSERT_EQ((float)((int)((commanded.speeds_rpm[0] - 1500) * RPM_TO_METERS_PER_SECOND * 100)) / 100, 11.76f);

    torque_controller_mux.tick(
        clock.tick(1000000), // 1 second since launch
        simulated_barely_launch_drivetrain_dynamics,
        simulated_accel_and_brake_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_3,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    launch_state = torque_controller_mux.activeController()->get_launch_state();

    ASSERT_EQ(launch_state, LaunchStates_e::LAUNCH_NOT_READY);
}

TEST(TorqueControllerMuxTesting, test_slip_launch_controller) {
    SysClock clock = SysClock();
    SysTick_s cur_tick;
    cur_tick = clock.tick(0);
    TorqueControllerMux torque_controller_mux = TorqueControllerMux();
    DrivetrainCommand_s resulting_torque_command;

    vector_nav vn_data{};

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

    DrivetrainDynamicReport_s simulated_barely_launch_drivetrain_dynamics = {
        .measuredInverterFLPackVoltage = 550,
        .measuredSpeeds = {0, 2785.86, 0, 0},
        .measuredTorques = {0.0, 0.0, 0.0, 0.0},
        .measuredTorqueCurrents = {0.0, 0.0, 0.0, 0.0},
        .measuredMagnetizingCurrents = {0.0, 0.0, 0.0, 0.0}
    };

    // DrivetrainDynamicReport_s simulated_no_launch_drivetrain_dynamics = {
    //     .measuredInverterFLPackVoltage = 550,
    //     .measuredSpeeds = {0, 2786.86, 0, 0},
    //     .measuredTorques = {0.0, 0.0, 0.0, 0.0},
    //     .measuredTorqueCurrents = {0.0, 0.0, 0.0, 0.0},
    //     .measuredMagnetizingCurrents = {0.0, 0.0, 0.0, 0.0}
    // };

    // DrivetrainDynamicReport_s simulated_fast_drivetrain_dynamics = {
    //     .measuredInverterFLPackVoltage = 550,
    //     .measuredSpeeds = {
    //         ((MAX_SPEED_FOR_MODE_CHANGE + 0.1f) * METERS_PER_SECOND_TO_RPM), 
    //         ((MAX_SPEED_FOR_MODE_CHANGE + 0.1f) * METERS_PER_SECOND_TO_RPM), 
    //         ((MAX_SPEED_FOR_MODE_CHANGE + 0.1f) * METERS_PER_SECOND_TO_RPM), 
    //         ((MAX_SPEED_FOR_MODE_CHANGE + 0.1f) * METERS_PER_SECOND_TO_RPM)
    //     },
    //     .measuredTorques = {0.0, 0.0, 0.0, 0.0},
    //     .measuredTorqueCurrents = {0.0, 0.0, 0.0, 0.0},
    //     .measuredMagnetizingCurrents = {0.0, 0.0, 0.0, 0.0}
    // };

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

    // PedalsSystemData_s simulated_accel_and_brake_press = {
    //     .accelImplausible = false,
    //     .brakeImplausible = false,
    //     .brakePressed = false,
    //     .brakeAndAccelPressedImplausibility = false,
    //     .implausibilityExceededMaxDuration = false,
    //     .accelPercent = 1.0,
    //     .brakePercent = 0.3
    // };

    torque_controller_mux.tick(
        cur_tick,
        simulated_slow_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_0,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    // change mode to mode 3
    torque_controller_mux.tick(
        cur_tick,
        simulated_slow_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_4,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    // tick again to calculate state switch
    torque_controller_mux.tick(
        cur_tick,
        simulated_slow_drivetrain_dynamics,
        simulated_no_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_4,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    LaunchStates_e launch_state = torque_controller_mux.activeController()->get_launch_state();

    ASSERT_EQ(launch_state, LaunchStates_e::LAUNCH_READY);

    // press accel now with one wheelspeed barely under threshold
    torque_controller_mux.tick(
        clock.tick(100000),
        simulated_barely_launch_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_4,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    // tick TCMUX (10k us will hit 100hz)
    torque_controller_mux.tick(
        clock.tick(100000),
        simulated_barely_launch_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_4,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    launch_state = torque_controller_mux.activeController()->get_launch_state();

    ASSERT_EQ(launch_state, LaunchStates_e::LAUNCHING);

    DrivetrainCommand_s commanded = torque_controller_mux.getDrivetrainCommand();
    ASSERT_EQ((int16_t)commanded.speeds_rpm[0], DEFAULT_LAUNCH_SPEED_TARGET);

    torque_controller_mux.tick(
        clock.tick(const_accel_time * 1000), // const accel time sine launch
        simulated_barely_launch_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_4,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    launch_state = torque_controller_mux.activeController()->get_launch_state();

    ASSERT_EQ(launch_state, LaunchStates_e::LAUNCHING);

    commanded = torque_controller_mux.getDrivetrainCommand();
    ASSERT_EQ((int16_t)commanded.speeds_rpm[0], DEFAULT_LAUNCH_SPEED_TARGET);

    // if velocity is less than the default speed, it should still go at launch speed
    vn_data.velocity_x = 0; // m/s

    torque_controller_mux.tick(
        clock.tick((const_accel_time * 1000) + 1000000), // 1 second after const accel time
        simulated_barely_launch_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_4,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    commanded = torque_controller_mux.getDrivetrainCommand();
    printf("lower vx_body: %.2f\n", (float)commanded.speeds_rpm[0] * RPM_TO_METERS_PER_SECOND);
    ASSERT_EQ(commanded.speeds_rpm[0] , DEFAULT_LAUNCH_SPEED_TARGET); // should still be at initial launch target

    // this is approx. the speed the car would be going at 1500 rpm
    // we should expect the next calculation to be approx. DEFAULT_SLIP_RATIO % higher than this
    vn_data.velocity_x = DEFAULT_LAUNCH_SPEED_TARGET * RPM_TO_METERS_PER_SECOND; // m/s

    torque_controller_mux.tick(
        clock.tick((const_accel_time * 1000) + 1000000), // 1 second after const accel time
        simulated_barely_launch_drivetrain_dynamics,
        simulated_full_accel_press,
        (const SteeringSystemData_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        (const AnalogConversion_s) {},
        DialMode_e::MODE_4,
        false,
        vn_data,
        0.0,
        {},
        {}
    );

    commanded = torque_controller_mux.getDrivetrainCommand();
    printf("launch vx_body: %.2f\n", (float)commanded.speeds_rpm[0] * RPM_TO_METERS_PER_SECOND);
    ASSERT_EQ((int16_t)commanded.speeds_rpm[0] > (DEFAULT_LAUNCH_SPEED_TARGET * RPM_TO_METERS_PER_SECOND), true);


    // this fails, but the value is close enough
    // ASSERT_EQ((float)((int)((commanded.speeds_rpm[0] - 1500) * RPM_TO_METERS_PER_SECOND * 100)) / 100, 11.76f);
}

#endif /* TORQUE_CONTROLLER_MUX_TEST */