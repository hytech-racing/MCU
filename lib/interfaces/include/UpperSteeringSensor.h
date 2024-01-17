#ifndef UPPERSTEERINGSENSOR
#define UPPERSTEERINGSENSOR

#include "AnalogSensor.h"
#include <tuple>

enum upperSteeringStatus_s
{
    UPPER_STEERING_NOMINAL = 0,
    UPPER_STEERING_MARGINAL = 1,
    UPPER_STEERING_ERROR = 2,
};

class UpperSteeringSensor
{
public:
// Functions
    /// @brief Commands the underlying steering sensor to sample and hold the result
    virtual void sample();
    /// @brief Calculate steering angle and whether result is in sensor's defined bounds. DOES NOT SAMPLE.
    /// @return Calculated steering angle in degrees, upperSteeringStatus_s
    virtual std::tuple<float, upperSteeringStatus_s> getAngleAndStatus();
    /// @brief Set the upper steering sensor's offset. 0 degrees should be centered.
    /// @param newOffset 
    virtual void setOffset(float newOffset);
};

#endif /* UPPERSTEERINGSENSOR */
