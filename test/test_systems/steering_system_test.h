#ifndef STEERING_SYSTEM_TEST
#define STEERING_SYSTEM_TEST
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SteeringSystem.h"

#define PRIMARY_ALPHA   (0.6)
#define SECONDARY_ALPHA (0.6)
#define WARN_DISCREPANCY_OFFSET (0.5)
#define ERR_DISCREPANCY_OFFSET (0.5)
#define WARN_FILTER_LATENCY (6)
#define ERR_FILTER_LATENCY (7)

TEST(SteeringSystemTesting, test_steering_nominal)
{
    float angles_to_test[5] = {-120.0f, -60.0f, 0.0f, 60.0f, 120.0f};
    // Boilerplate definitions for the testing aparatus
    SysClock sys_clock;
    SysTick_s sys_tick = sys_clock.tick(0);
    SteeringEncoderInterface primarySensor;
    SteeringSystem steeringSystem(&primarySensor, PRIMARY_ALPHA, SECONDARY_ALPHA);
    Filter_IIR<float> mockAngleFilters[2] = {PRIMARY_ALPHA, SECONDARY_ALPHA};

    // Sweep through a few angles where the sensors agree perfectly and check the system is nominal
    for (float angle: angles_to_test)
    {
        primarySensor.mockConversion.angle = angle;
        primarySensor.mockConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL;
        steeringSystem.tick(
            (SteeringSystemTick_s)
            {
                .tick = sys_tick,
                .secondaryConversion = (AnalogConversion_s)
                {
                    .raw = 0,
                    .conversion = angle,
                    .status = AnalogSensorStatus_e::ANALOG_SENSOR_GOOD
                }
            }
        );

        ASSERT_TRUE(steeringSystem.getSteeringSystemData().angle == mockAngleFilters[0].filtered_result(angle));
        ASSERT_TRUE(steeringSystem.getSteeringSystemData().status == SteeringSystemStatus_e::STEERING_SYSTEM_NOMINAL);
    }
}

TEST(SteeringSystemTesting, test_steering_primary_is_marginal)
{
    // Boilerplate definitions for the testing aparatus
    SysClock sys_clock;
    SysTick_s sys_tick = sys_clock.tick(0);
    SteeringEncoderInterface primarySensor;
    SteeringSystem steeringSystem(&primarySensor, PRIMARY_ALPHA, SECONDARY_ALPHA);
    Filter_IIR<float> mockAngleFilters[2] = {PRIMARY_ALPHA, SECONDARY_ALPHA};
    float angle = 0.0f;

    primarySensor.mockConversion.angle = angle;
    primarySensor.mockConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_MARGINAL;
    steeringSystem.tick(
        (SteeringSystemTick_s)
        {
            .tick = sys_tick,
            .secondaryConversion = (AnalogConversion_s)
            {
                .raw = 0,
                .conversion = angle,
                .status = AnalogSensorStatus_e::ANALOG_SENSOR_GOOD
            }
        }
    );
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().angle == mockAngleFilters[0].filtered_result(angle));
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().status == SteeringSystemStatus_e::STEERING_SYSTEM_MARGINAL);
}

TEST(SteeringSystemTesting, test_steering_secondary_is_marginal)
{
    // Boilerplate definitions for the testing aparatus
    SysClock sys_clock;
    SysTick_s sys_tick = sys_clock.tick(0);
    SteeringEncoderInterface primarySensor;
    SteeringSystem steeringSystem(&primarySensor, PRIMARY_ALPHA, SECONDARY_ALPHA);
    Filter_IIR<float> mockAngleFilters[2] = {PRIMARY_ALPHA, SECONDARY_ALPHA};
    float angle = 0.0f;

    primarySensor.mockConversion.angle = angle;
    primarySensor.mockConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL;
    steeringSystem.tick(
        (SteeringSystemTick_s)
        {
            .tick = sys_tick,
            .secondaryConversion = (AnalogConversion_s)
            {
                .raw = 0,
                .conversion = angle,
                .status = AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED
            }
        }
    );
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().angle == mockAngleFilters[0].filtered_result(angle));
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().status == SteeringSystemStatus_e::STEERING_SYSTEM_MARGINAL);
}

TEST(SteeringSystemTesting, test_steering_divergence_warning)
{
    // Boilerplate definitions for the testing aparatus
    SysClock sys_clock;
    SysTick_s sys_tick = sys_clock.tick(0);
    SteeringEncoderInterface primarySensor;
    SteeringSystem steeringSystem(&primarySensor, PRIMARY_ALPHA, SECONDARY_ALPHA);
    Filter_IIR<float> mockAngleFilters[2] = {PRIMARY_ALPHA, SECONDARY_ALPHA};
    float mockPrimaryFilteredAngle;
    float mockSecondaryFilteredAngle;

    float primaryAngle = 0.0f;
    float secondaryAngle = primaryAngle + WARN_DISCREPANCY_OFFSET + STEERING_DIVERGENCE_WARN_THRESHOLD; // Edge discrepancy

    // Edge filter steps to align output
    for (int i = 0; i < WARN_FILTER_LATENCY; i++)
    {
        mockPrimaryFilteredAngle = mockAngleFilters[0].filtered_result(primaryAngle);
        mockSecondaryFilteredAngle = mockAngleFilters[1].filtered_result(secondaryAngle);

        primarySensor.mockConversion.angle = primaryAngle;
        primarySensor.mockConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL;
        steeringSystem.tick(
            (SteeringSystemTick_s)
            {
                .tick = sys_tick,
                .secondaryConversion = (AnalogConversion_s)
                {
                    .raw = 0,
                    .conversion = secondaryAngle,
                    .status = AnalogSensorStatus_e::ANALOG_SENSOR_GOOD
                }
            }
        );
    }
    
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().angle == mockPrimaryFilteredAngle);
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().status == SteeringSystemStatus_e::STEERING_SYSTEM_MARGINAL);
}

TEST(SteeringSystemTesting, test_steering_divergence_error)
{
    // Boilerplate definitions for the testing aparatus
    SysClock sys_clock;
    SysTick_s sys_tick = sys_clock.tick(0);
    SteeringEncoderInterface primarySensor;
    SteeringSystem steeringSystem(&primarySensor, PRIMARY_ALPHA, SECONDARY_ALPHA);
    Filter_IIR<float> mockAngleFilters[2] = {PRIMARY_ALPHA, SECONDARY_ALPHA};
    float mockPrimaryFilteredAngle;
    float mockSecondaryFilteredAngle;

    float primaryAngle = 0.0f;
    float secondaryAngle = primaryAngle + ERR_DISCREPANCY_OFFSET + STEERING_DIVERGENCE_ERROR_THRESHOLD;

    for (int i = 0; i < ERR_FILTER_LATENCY; i++)
    {
        mockPrimaryFilteredAngle = mockAngleFilters[0].filtered_result(primaryAngle);
        mockSecondaryFilteredAngle = mockAngleFilters[1].filtered_result(secondaryAngle);

        primarySensor.mockConversion.angle = primaryAngle;
        primarySensor.mockConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL;
        steeringSystem.tick(
            (SteeringSystemTick_s)
            {
                .tick = sys_tick,
                .secondaryConversion = (AnalogConversion_s)
                {
                    .raw = 0,
                    .conversion = secondaryAngle,
                    .status = AnalogSensorStatus_e::ANALOG_SENSOR_GOOD
                }
            }
        );
    }

    ASSERT_TRUE(steeringSystem.getSteeringSystemData().angle == 0.0f);
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().status == SteeringSystemStatus_e::STEERING_SYSTEM_ERROR);
}

TEST(SteeringSystemTesting, test_steering_primary_is_missing)
{
    // Boilerplate definitions for the testing aparatus
    SysClock sys_clock;
    SysTick_s sys_tick = sys_clock.tick(0);
    SteeringEncoderInterface primarySensor;
    SteeringSystem steeringSystem(&primarySensor, PRIMARY_ALPHA, SECONDARY_ALPHA);
    Filter_IIR<float> mockAngleFilters[2] = {PRIMARY_ALPHA, SECONDARY_ALPHA};
    float angle = 100.0f;

    primarySensor.mockConversion.angle = 0.0f;
    primarySensor.mockConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_ERROR;
    steeringSystem.tick(
        (SteeringSystemTick_s)
        {
            .tick = sys_tick,
            .secondaryConversion = (AnalogConversion_s)
            {
                .raw = 0,
                .conversion = angle,
                .status = AnalogSensorStatus_e::ANALOG_SENSOR_GOOD
            }
        }
    );
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().angle == mockAngleFilters[1].filtered_result(angle));
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().status == SteeringSystemStatus_e::STEERING_SYSTEM_DEGRADED);
}

TEST(SteeringSystemTesting, test_steering_primary_is_missing_and_secondary_is_marginal)
{
    // Boilerplate definitions for the testing aparatus
    SysClock sys_clock;
    SysTick_s sys_tick = sys_clock.tick(0);
    SteeringEncoderInterface primarySensor;
    SteeringSystem steeringSystem(&primarySensor, PRIMARY_ALPHA, SECONDARY_ALPHA);
    float angle = 100.0f;

    primarySensor.mockConversion.angle = 0.0f;
    primarySensor.mockConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_ERROR;
    steeringSystem.tick(
        (SteeringSystemTick_s)
        {
            .tick = sys_tick,
            .secondaryConversion = (AnalogConversion_s)
            {
                .raw = 0,
                .conversion = angle,
                .status = AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED
            }
        }
    );
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().angle == 0.0f);
    ASSERT_TRUE(steeringSystem.getSteeringSystemData().status == SteeringSystemStatus_e::STEERING_SYSTEM_ERROR);
}

#endif