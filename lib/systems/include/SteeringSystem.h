#ifndef __STEERINGSYSTEM_H__
#define __STEERINGSYSTEM_H__

#include "SteeringEncoderInterface.h"
#include "AnalogSensorsInterface.h"
#include "SysClock.h"
#include "SharedDataTypes.h"
// Digital Encoder = Primary Sensor
// Analog Encoder = Secondary Sensor

// Definitions
// TODO: evalaute reasonable thresholds for agreement
#define STEERING_DIVERGENCE_ERROR_THRESHOLD (14.0) // Steering sensors can disagree by 5 degrees before output is considered erroneous
#define STEERING_DIVERGENCE_WARN_THRESHOLD (8.0) // Warning condition will be raised when steering sensors diverge 2.5 degrees



// Structs
struct SteeringSystemTick_s
{
    const SysTick_s &tick;
    const AnalogConversion_s &secondaryConversion;
};


class SteeringSystem
{
private:
    SteeringEncoderInterface *primarySensor_;
    SteeringEncoderConversion_s primaryConversion_;
    SteeringSystemData_s steeringData_;
public:
    SteeringSystem(SteeringEncoderInterface *primarySensor)
    : primarySensor_(primarySensor)
    {}

    /// @brief Computes steering angle and status of the steering system.
    /// @param secondaryAngle The computed steering angle as reported by the secondary steering sensor.
    /// @return SteeringSystemOutput_s contains steering angle and SteeringSystemStatus_e
    void tick(const SteeringSystemTick_s &intake);

    /// @brief Get a reference to the steering system's data
    /// @return const SteeringSystemData_s&
    const SteeringSystemData_s& getSteeringSystemData()
    {
        return steeringData_;
    }
};

#endif /* __STEERINGSYSTEM_H__ */