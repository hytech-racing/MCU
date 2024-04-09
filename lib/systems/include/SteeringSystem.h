#ifndef __STEERINGSYSTEM_H__
#define __STEERINGSYSTEM_H__

#include "SteeringEncoderInterface.h"
#include "AnalogSensorsInterface.h"
#include "SysClock.h"
#include "ORBIS_BR10.h" // digital sensor
#include "MCP_ADC.h" // analogue sensor 

// Digital Encoder = Primary Sensor
// Analog Encoder = Secondary Sensor

// Definitions
// TODO: evalaute reasonable thresholds for agreement
#define STEERING_DIVERGENCE_ERROR_THRESHOLD (5.0) // Steering sensors can disagree by 5 degrees before output is considered erroneous
#define STEERING_DIVERGENCE_WARN_THRESHOLD (2.5) // Warning condition will be raised when steering sensors diverge 2.5 degrees

// Enums
enum class SteeringSystemStatus_e
{
    STEERING_SYSTEM_NOMINAL = 0,
    STEERING_SYSTEM_MARGINAL = 1,
    STEERING_SYSTEM_DEGRADED = 2,
    STEERING_SYSTEM_ERROR = 3,
};

// Structs
struct SteeringSystemData_s
{
    float angle;
    SteeringSystemStatus_e status;
};

class SteeringSystem
{
private:
    SteeringEncoderInterface *primarySensor_;
    SteeringEncoderConversion_s primaryConversion_;
    SteeringSystemData_s data_;
    int steeringDataMap[2] = {-130, 130}; // max and min range of converted steering data (change depending on data)
    int wheelSteerRange[2] = {23, -23}; // max and min of final wheel steering (correct if actual limits of car are different)
public:
    SteeringSystem(SteeringEncoderInterface *primarySensor) : primarySensor_(primarySensor) {}

    /// @brief Computes steering angle and status of the steering system.
    /// @param secondaryAngle The computed steering angle as reported by the secondary steering sensor.
    /// @return SteeringSystemOutput_s contains steering angle and SteeringSystemStatus_e
    void tick(
        const SysTick_s &tick,
        const AnalogConversion_s &secondaryConversion
    );

    /// @brief Get a reference to the steering system's data
    /// @return const SteeringSystemData_s&
    const SteeringSystemData_s& getSteeringSystemData()
    {
        return data_;
    }
    double interpolateSteering(double x, double x1, double x2, double y1, double y2);
    double normalizeSteering(double value, double minVal, double maxVal);
};

#endif /* __STEERINGSYSTEM_H__ */