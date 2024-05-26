#ifndef __STEERINGSYSTEM_H__
#define __STEERINGSYSTEM_H__

#include "SteeringEncoderInterface.h"
#include "AnalogSensorsInterface.h"
#include "Filter_IIR.h"
#include "SysClock.h"
#include "TelemetryInterface.h"

// Digital Encoder = Primary Sensor
// Analog Encoder = Secondary Sensor

// Definitions
// TODO: evalaute reasonable thresholds for agreement
#define STEERING_DIVERGENCE_ERROR_THRESHOLD (16.0) // Steering sensors can disagree by x degrees before output is considered erroneous
#define STEERING_DIVERGENCE_WARN_THRESHOLD (8.0) // Warning condition will be raised when steering sensors diverge x degrees
#define NUM_SENSORS 2
#define DEFAULT_STEERING_ALPHA (0.0)

// Enums
enum class SteeringSystemStatus_e
{
    STEERING_SYSTEM_NOMINAL = 0,
    STEERING_SYSTEM_MARGINAL = 1,
    STEERING_SYSTEM_DEGRADED = 2,
    STEERING_SYSTEM_ERROR = 3,
};

// Structs
struct SteeringSystemTick_s
{
    const SysTick_s &tick;
    const AnalogConversion_s &secondaryConversion;
};

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
    SteeringSystemData_s steeringData_;

    /**
     * Utility digital IIR filters
     * 0 : primary sensor filter
     * 1 : secondary sensor filter
     */
    Filter_IIR<float> steeringFilters_[NUM_SENSORS];
    float filteredAnglePrimary_;
    float filteredAngleSecondary_;

    TelemetryInterface *telemHandle_;
public:
    SteeringSystem(SteeringEncoderInterface *primarySensor, TelemetryInterface *telemInterface)
    : SteeringSystem(primarySensor, telemInterface, DEFAULT_STEERING_ALPHA)
    {}

    SteeringSystem(SteeringEncoderInterface *primarySensor, TelemetryInterface *telemInterface, float filterAlpha)
    : SteeringSystem(primarySensor, telemInterface, filterAlpha, filterAlpha)
    {}

    SteeringSystem(SteeringEncoderInterface *primarySensor, TelemetryInterface *telemInterface, float filterAlphaPrimary, float filterAlphaSecondary)
    : primarySensor_(primarySensor)
    , telemHandle_(telemInterface)
    {
        steeringFilters_[0] = Filter_IIR<float>(filterAlphaPrimary);
        steeringFilters_[1] = Filter_IIR<float>(filterAlphaSecondary);
        
    }

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

    void reportSteeringStatus(
        const float angle,
        const float filteredAngleEncoder,
        const float filteredAngleAnalog,
        const uint8_t systemStatus,
        const uint8_t encoderStatus,
        const uint8_t analogSensorStatus);
};

#endif /* __STEERINGSYSTEM_H__ */