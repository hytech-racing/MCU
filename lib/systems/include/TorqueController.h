#ifndef __TORQUECONTROLLER_H__
#define __TORQUECONTROLLER_H__

// #include "PedalsInterface.h"
// #include "DashboardInterface.h"
// #include "SteeringInterface.h"
// #include "InvertersInterface.h"

// Definitions
#define TC_FL 0
#define TC_FR 1
#define TC_RL 2
#define TC_RR 3

enum TCLaunchState_s
{
    TC_LAUNCH_NOT_READY = 0,
    TC_LAUNCH_READY = 1,
    TC_LAUNCHING = 2,
};

enum TCVectoringMode_s
{
    TC_VECTOR_MODE_NONE = 0,
};

class TorqueController
{
private:
    float totalPowerLimit;
    float torqueLimitMode;
    float powerLimits[4];
    float torqueLimits[4];
    float speedTargets[4];
public:
};

#endif /* __TORQUECONTROLLER_H__ */
