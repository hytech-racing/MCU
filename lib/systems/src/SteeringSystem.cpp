#include "SteeringSystem.h"
#include <cmath>

void SteeringSystem::tick(const SteeringSystemTick_s &intake)
{
    // System works at 100hz
    // 1. Polls upper steering sensor
    // 2. Computes internal state
    if (intake.tick.triggers.trigger100)
    {
        filteredAngleSecondary_ = steeringFilters_[1].filtered_result(intake.secondaryConversion.conversion);
        primaryConversion_.status = SteeringEncoderStatus_e::STEERING_ENCODER_ERROR;
        steeringData_.status = SteeringSystemStatus_e::STEERING_SYSTEM_NOMINAL;
        steeringData_ = {
            .angle = filteredAngleSecondary_,
            .status = SteeringSystemStatus_e::STEERING_SYSTEM_DEGRADED};
    }

    // Report at 50Hz
    if (intake.tick.triggers.trigger50)
    {
        reportSteeringStatus(
            steeringData_.angle,
            0,
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
