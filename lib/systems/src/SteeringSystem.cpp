#include "SteeringSystem.h"
#include <cmath>

// basic interpolation for steering where steering data = x and wheel angle = y
double interpolateSteering(double x, double x1, double x2, double y1, double y2) {
    if (x1 == x2) {
        return y1;
    }
    return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

// normalizing steering values (and flipping signs to based on fsae convention)
double normalizeSteering(double value, double minVal, double maxVal) {
    if (minVal == maxVal) {
        return 0;
    }
    return -(value - minVal) / (minVal - maxVal); // double check if sign change is valid
}

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
        // steeringDataMap and wheelSteerRange both contain min and max values
        primaryConversion_.angle = interpolateSteering(primaryConversion_.raw, steeringDataMap[0], steeringDataMap[1], wheelSteerRange[0], wheelSteerRange[1]);
        primaryConversion_.angle = normalizeSteering(primaryConversion_.angle, wheelSteerRange[0], wheelSteerRange[1]);
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
