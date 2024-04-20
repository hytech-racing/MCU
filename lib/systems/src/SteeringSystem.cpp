#include "SteeringSystem.h"
#include <cmath>

void SteeringSystem::tick(const SteeringSystemTick_s &intake)
{
    // Periodically check if the upper sensor is alive
    if (intake.tick.triggers.trigger1)
    {
        primarySensorAlive_ = primarySensor_->isAlive();
    }
    // System works at 100hz
    // 1. Polls upper steering sensor
    // 2. Computes internal state
    if (intake.tick.triggers.trigger100)
    {
        // Poll upper steering sensor
        primarySensor_->sample();
        primaryConversion_ = primarySensor_->convert();

        // Compute internal state

        // Both sensors are nominal
        if (
            (primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL)
            && (intake.secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_GOOD)
            && primarySensorAlive_    
        )
        {
            steeringData_ = {
                .angle = primaryConversion_.angle,
                .status = SteeringSystemStatus_e::STEERING_SYSTEM_NOMINAL
            };
        }
        // One or both sensors are marginal
        // Sensors disagree by STEERING_DIVERGENCE_WARN_THRESHOLD degrees and less than STEERING_DIVERGENCE_ERROR_THRESHOLD degrees
        else if (
            primarySensorAlive_
            &&
            ((primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_MARGINAL)
            || (intake.secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED)
            || ((std::abs(primaryConversion_.angle - intake.secondaryConversion.conversion) > STEERING_DIVERGENCE_WARN_THRESHOLD) && (std::abs(primaryConversion_.angle - intake.secondaryConversion.conversion) < STEERING_DIVERGENCE_ERROR_THRESHOLD)))
        )
        {
            steeringData_ = {
                .angle = primaryConversion_.angle,
                .status = SteeringSystemStatus_e::STEERING_SYSTEM_MARGINAL
            };
        }
        // Upper steering sensor reports error or is not detected, lower sensor is nominal
        else if (
            ((primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_ERROR) || !primarySensorAlive_)
            && (intake.secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_GOOD)
        )
        {
            steeringData_ = {
                .angle = intake.secondaryConversion.conversion,
                .status = SteeringSystemStatus_e::STEERING_SYSTEM_DEGRADED
            };
        }
        // Fall through case
        // Complete failure of steering sensing
        else
        {
            steeringData_ = {
                .angle = 0.0,
                .status = SteeringSystemStatus_e::STEERING_SYSTEM_ERROR
            };
        }
    }
}
