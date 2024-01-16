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
    virtual void sample();
    virtual std::tuple<float, upperSteeringStatus_s> getAngleAndStatus();
    virtual void setOffset(float newOffset);
};

#endif /* UPPERSTEERINGSENSOR */
