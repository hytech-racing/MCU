#ifndef __STEERINGINTERFACE_H__
#define __STEERINGINTERFACE_H__

#include <tuple>

enum steeringStatus_s
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
    // Returns steering angle and whether the measurement is valid, i.e., redundant sensors agree
    virtual std::tuple<float, steeringStatus_s> getSteeringAngle();
};

#endif /* __STEERINGINTERFACE_H__ */
