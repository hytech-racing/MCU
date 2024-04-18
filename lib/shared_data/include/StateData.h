#ifndef STATEDATA
#define STATEDATA

#include "Utility.h"

/// @brief the state that
struct pstate
{
    veh_vec<float> Alphadeg;
    veh_vec<float> LongitudinalCornerVelms;
    veh_vec<float> longitudinalSlip;
    xy_vec<float> bodyVel;
    float beta;
    float KinematicDesiredYawRaterads;
};

#endif
