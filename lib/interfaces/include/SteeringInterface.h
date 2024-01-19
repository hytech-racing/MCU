#ifndef __STEERINGINTERFACE_H__
#define __STEERINGINTERFACE_H__

#include <tuple>

enum SteeringStatus_s
{
    STEERING_NOMINAL = 0,   // all sensors are nominal
    STEERING_MARGINAL = 1,  // one or more sensors is reporting a warning
    STEERING_DEGRADED = 2,  // one or more sensors is reporting an error, all others are nominal
    STEERING_ERROR = 3,     // one or more sensors is reporting an error, no sensors are nominal
};

class SteeringInterface
{
private:
public:  
    /// @brief Calculate steering angle and status (nominal, marginal, degraded, error). DOES NOT SAMPLE.
    /// @return Steering angle (0 is centered, negative is left), SteeringStatus_s
    virtual std::tuple<float, SteeringStatus_s> getSteeringAngle();
};

#endif /* __STEERINGINTERFACE_H__ */
