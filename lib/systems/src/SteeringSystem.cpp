#include "SteeringSystem.h"

void SteeringSystem::tick(const SysTick_s &tick, const AnalogConversion_s &secondaryConversion)
{
    // System works at 100hz
    // 1. Polls upper steering sensor
    // 2. Computes internal state
    if (tick.triggers.trigger100)
    {
        // Poll upper steering sensor
        primarySensor_->sample();
        primaryConversion_ = primarySensor_->convert();

        // Compute internal state

        // Both sensors are nominal
        if ((primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL) && (secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_GOOD))
        {
            data_ = {
                .angle = primaryConversion_.angle,
                .status = SteeringSystemStatus_e::STEERING_SYSTEM_NOMINAL
            };
        }
        // One or both sensors are marginal
        // Sensors disagree by STEERING_DIVERGENCE_WARN_THRESHOLD degrees and less than STEERING_DIVERGENCE_ERROR_THRESHOLD degrees
        else if ((primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_MARGINAL)
            || (secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED)
            || ((std::abs(primaryConversion_.angle - secondaryConversion.conversion) > STEERING_DIVERGENCE_WARN_THRESHOLD) && (std::abs(primaryConversion_.angle - secondaryConversion.conversion) < STEERING_DIVERGENCE_ERROR_THRESHOLD)))
        {
            data_ = {
                .angle = primaryConversion_.angle,
                .status = SteeringSystemStatus_e::STEERING_SYSTEM_MARGINAL
            };
        }
        // Upper steering sensor reports error, lower sensor is nominal
        else if ((primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_ERROR) && (secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_GOOD))
        {
            data_ = {
                .angle = secondaryConversion.conversion,
                .status = SteeringSystemStatus_e::STEERING_SYSTEM_DEGRADED
            };
        }
        // Fall through case
        // Complete failure of steering sensing
        else
        {
            data_ = {
                .angle = 0.0,
                .status = SteeringSystemStatus_e::STEERING_SYSTEM_ERROR
            };
        }
    }
}
