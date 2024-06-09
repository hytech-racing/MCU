#include "SteeringSystem.h"
#include <cmath>

void SteeringSystem::tick(const SteeringSystemTick_s &intake)
{
    // System works at 100hz
    // 1. Polls upper steering sensor
    // 2. Computes internal state
    if (intake.tick.triggers.trigger100)
    {
        // Poll upper steering sensor
        primarySensor_->sample();
        primaryConversion_ = primarySensor_->convert();

        // Filter both sensor angle readings
        filteredAnglePrimary_ = steeringFilters_[0].filtered_result(primaryConversion_.angle);
        filteredAngleSecondary_ = steeringFilters_[1].filtered_result(intake.secondaryConversion.conversion);        

        // Both sensors are nominal and agree
        // #ifdef ARDUINO_TEENSY41
        // if (
        //     (primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL)
        //     && (intake.secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_GOOD)
        //     && (abs(filteredAnglePrimary_ - filteredAngleSecondary_) < STEERING_DIVERGENCE_WARN_THRESHOLD)
        // )
        // #else
        // if (
        //     (primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL)
        //     && (intake.secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_GOOD)
        //     && (std::abs(filteredAnglePrimary_ - filteredAngleSecondary_) < STEERING_DIVERGENCE_WARN_THRESHOLD)
        // )
        // #endif
        // {
        //     steeringData_ = {
        //         .angle = filteredAnglePrimary_,
        //         .status = SteeringSystemStatus_e::STEERING_SYSTEM_NOMINAL
        //     };
        // }
        // // One or both sensors are marginal
        // // Sensors disagree by STEERING_DIVERGENCE_WARN_THRESHOLD degrees and less than STEERING_DIVERGENCE_ERROR_THRESHOLD degrees
        // #ifdef ARDUINO_TEENSY41
        // else if (
        //     (primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_MARGINAL)
        //     || ((primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL) && (intake.secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED))
        //     || ((abs(filteredAnglePrimary_ - filteredAngleSecondary_) >= STEERING_DIVERGENCE_WARN_THRESHOLD) && (abs(filteredAnglePrimary_ - filteredAngleSecondary_) < STEERING_DIVERGENCE_ERROR_THRESHOLD))
        // )
        // #else
        // else if (
        //     (primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_MARGINAL)
        //     || ((primaryConversion_.status == SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL) && (intake.secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED))
        //     || ((std::abs(filteredAnglePrimary_ - filteredAngleSecondary_) >= STEERING_DIVERGENCE_WARN_THRESHOLD) && (abs(filteredAnglePrimary_ - filteredAngleSecondary_) < STEERING_DIVERGENCE_ERROR_THRESHOLD))
        // )
        // #endif
        // {
        //     steeringData_ = {
        //         .angle = filteredAnglePrimary_,
        //         .status = SteeringSystemStatus_e::STEERING_SYSTEM_MARGINAL
        //     };
        // }
        // Upper steering sensor reports error or is not detected, lower sensor is nominal
        if ((intake.secondaryConversion.status == AnalogSensorStatus_e::ANALOG_SENSOR_GOOD))
        {
            steeringData_ = {
                .angle = filteredAngleSecondary_,
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

    // Report at 50Hz
    if (intake.tick.triggers.trigger50)
    {
        reportSteeringStatus(
            steeringData_.angle,
            filteredAnglePrimary_,
            filteredAngleSecondary_,
            static_cast<uint8_t>(steeringData_.status),
            static_cast<uint8_t>(primaryConversion_.status),
            static_cast<uint8_t>(intake.secondaryConversion.status));
    }
    

}

void SteeringSystem::reportSteeringStatus(const float angle,
                                          const float filteredAngleEncoder,
                                          const float filteredAngleAnalog,
                                          const uint8_t systemStatus,
                                          const uint8_t encoderStatus,
                                          const uint8_t analogSensorStatus)
{
    telemHandle_->update_steering_status_CAN_msg(
        angle,
        filteredAngleEncoder,
        filteredAngleAnalog,
        systemStatus,
        encoderStatus,
        analogSensorStatus);
}
