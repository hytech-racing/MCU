#ifndef STEERING_SYSTEM_TEST
#define STEERING_SYSTEM_TEST
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SteeringSystem.h"

#define PRIMARY_ALPHA   (0.7)   // parameter used on car
#define SECONDARY_ALPHA (0.7)
#define WARN_DIVERGENCE_OFFSET (0.6)
#define ERR_DIVERGENCE_OFFSET (0.7)
#define WARN_FILTER_LATENCY (8)
#define ERR_FILTER_LATENCY (9)

TEST(SteeringSystemTesting, test_steering_nominal)
{
    float angles_to_test[5] = {-120.0f, -60.0f, 0.0f, 60.0f, 120.0f};
    // Boilerplate definitions for the testing aparatus
    SysClock sys_clock;
    SysTick_s sys_tick = sys_clock.tick(0);
    SteeringEncoderInterface primarySensor;
    TelemetryInterface telem_interface;
    SteeringSystem steeringSystem(&primarySensor, &telem_interface, PRIMARY_ALPHA, SECONDARY_ALPHA);
    // Filter refernce values for evaluation
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
    TelemetryInterface telem_interface;
    SteeringSystem steeringSystem(&primarySensor, &telem_interface, PRIMARY_ALPHA, SECONDARY_ALPHA);
    // Filter refernce values for evaluation
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
    TelemetryInterface telem_interface;
    SteeringSystem steeringSystem(&primarySensor, &telem_interface, PRIMARY_ALPHA, SECONDARY_ALPHA);
    // Filter refernce values for evaluation
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
    TelemetryInterface telem_interface;
    SteeringSystem steeringSystem(&primarySensor, &telem_interface, PRIMARY_ALPHA, SECONDARY_ALPHA);
    // Filter refernce values for evaluation
    Filter_IIR<float> mockAngleFilters[2] = {PRIMARY_ALPHA, SECONDARY_ALPHA};
    float mockPrimaryFilteredAngle;
    float mockSecondaryFilteredAngle;

    float primaryAngle = 0.0f;
    // Pend divergence to sensor readings
    // - IIR filter eq.: filtered_val = (1-alpha)*new_val + alpha*prev_val
    // - when divergence set exactly to system threshold
    //   - divergence magnitude gets shaved off, will not trigger above threshold
    //   - pend offset to divergence to trip threshold
    float secondaryAngle = primaryAngle + WARN_DIVERGENCE_OFFSET + STEERING_DIVERGENCE_WARN_THRESHOLD; // edge discrepancy

    // Latency due to filtering
    // - required steps of filtering for divergence to rise up to threshold with offset pended
    // - e.g. when alpha = 0.7, pending offset = 0.6, it takes a minimal of 8 steps of filtering to exceed warn threshold
    for (int i = 0; i < WARN_FILTER_LATENCY; i++)   // edge filter steps to align output
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
    TelemetryInterface telem_interface;
    SteeringSystem steeringSystem(&primarySensor, &telem_interface, PRIMARY_ALPHA, SECONDARY_ALPHA);
    // Filter refernce values for evaluation
    Filter_IIR<float> mockAngleFilters[2] = {PRIMARY_ALPHA, SECONDARY_ALPHA};
    float mockPrimaryFilteredAngle;
    float mockSecondaryFilteredAngle;

    float primaryAngle = 0.0f;
    // Pend divergence to sensor readings
    // - IIR filter eq.: filtered_val = (1-alpha)*new_val + alpha*prev_val
    // - when divergence set exactly to system threshold
    //   - divergence magnitude gets shaved off, will not trigger above threshold
    //   - pend offset to divergence to trip threshold
    float secondaryAngle = primaryAngle + ERR_DIVERGENCE_OFFSET + STEERING_DIVERGENCE_ERROR_THRESHOLD;  // edge discrepancy

    // Latency due to filtering
    // - required steps of filtering for divergence to rise up to threshold with offset pended
    // - e.g. when alpha = 0.7, pending offset = 0.6, it takes a minimal of 9 steps of filtering to exceed error threshold
    for (int i = 0; i < ERR_FILTER_LATENCY; i++)    // edge filter steps to align output
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
    TelemetryInterface telem_interface;
    SteeringSystem steeringSystem(&primarySensor, &telem_interface, PRIMARY_ALPHA, SECONDARY_ALPHA);
    // Filter refernce values for evaluation
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
    TelemetryInterface telem_interface;
    SteeringSystem steeringSystem(&primarySensor, &telem_interface, PRIMARY_ALPHA, SECONDARY_ALPHA);
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