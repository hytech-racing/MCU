#ifndef __STEERINGINTERFACE_H__
#define __STEERINGINTERFACE_H__

#include <tuple>

class SteeringInterface
{
private:
public:
    // Returns steering angle and whether the measurement is valid, i.e., redundant sensors agree
    virtual std::tuple<float, bool> getSteeringAngle();
};

#endif /* __STEERINGINTERFACE_H__ */
