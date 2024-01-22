#ifndef __STEERINGSYSTEM_H__
#define __STEERINGSYSTEM_H__

#include "SteeringEncoderInterface.h"
#include "AnalogSensor.h"

// Digital Encoder = Primary Sensor
// Analog Encoder = Secondary Sensor

// Definitions
// TODO: evalaute reasonable thresholds for agreement
#define STEERING_DIVERGENCE_ERROR_THRESHOLD (5.0) // Steering sensors can disagree by 5 degrees before output is considered erroneous
#define STEERING_DIVERGENCE_WARN_THRESHOLD (2.5) // Warning condition will be raised when steering sensors diverge 2.5 degrees

// Enums
enum SteeringSystemStatus_e
{
    STEERING_SYSTEM_NOMINAL = 0,
    STEERING_SYSTEM_MARGINAL = 1,
    STEERING_SYSTEM_DEGRADED = 2,
    STEERING_SYSTEM_ERROR = 3,
};

// Structs
struct SteeringSystemOutput_s
{
    float angle;
    SteeringSystemStatus_e status;
};

class SteeringSystem
{
private:
public:
    /// @brief Computes steering angle and status of the steering system.
    /// @param secondaryAngle The computed steering angle as reported by the secondary steering sensor.
    /// @return SteeringSystemOutput_s contains steering angle and SteeringSystemStatus_e
    SteeringSystemOutput_s evaluate(
        SteeringEncoderConversion_s* primaryConversion, 
        AnalogConversion_s* secondaryConversion
    );
};

#endif /* __STEERINGSYSTEM_H__ */