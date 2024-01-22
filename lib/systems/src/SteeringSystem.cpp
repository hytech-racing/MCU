#include <SteeringSystem.h>

SteeringSystemOutput_s SteeringSystem::evaluate(SteeringEncoderConversion_s* primaryConversion, AnalogConversion_s* secondaryConversion)
{
    // Both sensors are nominal
    if ((primaryConversion->status == STEERING_ENCODER_NOMINAL) && (secondaryConversion->status == ANALOG_SENSOR_GOOD))
    {
        return {primaryConversion->angle, STEERING_SYSTEM_NOMINAL};
    }

    // One or both sensors are marginal
    // Sensors disagree by STEERING_DIVERGENCE_WARN_THRESHOLD degrees and less than STEERING_DIVERGENCE_ERROR_THRESHOLD degrees
    if ((primaryConversion->status == STEERING_ENCODER_MARGINAL)
        || (secondaryConversion->status == ANALOG_SENSOR_CLAMPED)
        || ((std::abs(primaryConversion->angle - secondaryConversion->conversion) > STEERING_DIVERGENCE_WARN_THRESHOLD) && (std::abs(primaryConversion->angle - secondaryConversion->conversion) < STEERING_DIVERGENCE_ERROR_THRESHOLD)))
    {
        return {primaryConversion->angle, STEERING_SYSTEM_MARGINAL};
    }

    // Upper steering sensor reports error, lower sensor is nominal
    if ((primaryConversion->status == STEERING_ENCODER_ERROR) && (secondaryConversion->status == ANALOG_SENSOR_GOOD))
    {
        return {secondaryConversion->conversion, STEERING_SYSTEM_DEGRADED};
    }

    // Fall through case
    // Complete failure of steering sensing
    return {
        .angle = 0.0, 
        .status = STEERING_SYSTEM_ERROR,
    };
}