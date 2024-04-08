#ifndef TORQUECONTROLLERSDATA
#define TORQUECONTROLLERSDATA

struct PIDTVTorqueControllerData
{
    float controller_input;
    float controller_output;
    float fl_torque_delta;
    float fr_torque_delta;
    float rl_torque_delta;
    float rr_torque_delta;
};

#endif