#ifndef STATEDATA
#define STATEDATA

/// @brief generic data vector type that can be used with tire and / or anything to do with 4 corners of the car.
struct veh_vec
{
    float FL;
    float FR;
    float RL;
    float RR;
};

struct xyz_vec
{
    float x;
    float y;
    float z;
};

struct xy_vec
{
    float x;
    float y;
};

/// @brief the state that
struct pstate
{
    veh_vec Alphadeg;
    veh_vec LongitudinalCornerVelms;
    veh_vec longitudinalSlip;
    xy_vec bodyVel;
    float beta;
    float KinematicDesiredYawRaterads;
};

#endif
