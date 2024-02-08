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

TEST(TorqueControllerMuxTesting, test_torque_button)
{
    const int SERIES_LENGTH = 10;
    SysClock clock = SysClock();
    SysTick_s cur_tick;
    TorqueControllerMux torque_controller_mux = TorqueControllerMux();

    bool buttonTimeSeries[SERIES_LENGTH]; // 50hz time series
    // Cycle back to low test
    buttonTimeSeries[1] = true;
    buttonTimeSeries[3] = true;
    buttonTimeSeries[5] = true;
    // Cycle only on button release test
    for (int i = 7; i < SERIES_LENGTH; i++)
        buttonTimeSeries[i] = true;

    ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_LOW_TORQUE);

    // Run test
    for (int i = 0; i < SERIES_LENGTH; i++)
    {
        cur_tick = clock.tick(i * 1000 * 20); // 20 ms increments
        torque_controller_mux.tick(
            cur_tick,
            (const DrivetrainDynamicReport_s) {},
            (const PedalsSystemData_s) {},
            (const SteeringSystemData_s) {},
            (const AnalogConversion_s) {},
            (const AnalogConversion_s) {},
            (const AnalogConversion_s) {},
            (const AnalogConversion_s) {},
            DialMode_e::MODE_1,
            buttonTimeSeries[i]
        );
        // Test conditions
        if (i == 2)
            ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_MID_TORQUE);
        if (i == 4)
            ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_FULL_TORQUE);
        if (i == 6)
            ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_LOW_TORQUE);
        if (i == SERIES_LENGTH - 1)
            ASSERT_EQ(torque_controller_mux.getTorqueLimit(), TorqueLimit_e::TCMUX_LOW_TORQUE);
    }
}

#endif /* TORQUE_CONTROLLER_MUX_TEST */
