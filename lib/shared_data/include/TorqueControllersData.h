#ifndef __TORQUE_CONTROLLERS_DATA__
#define __TORQUE_CONTROLLERS_DATA__

#include "DashboardInterface.h"
#include "TorqueControllers.h"

struct TCMuxStatus_s
{
    bool speedPreventsModeChange;
    bool torqueDeltaPreventsModeChange;
    bool controllerNotReadyPreventsModeChange;
    uint8_t modeIntended;
    uint8_t modeActual;
    uint8_t dialMode;


};

struct PIDTVTorqueControllerData
{
    float controller_input;
    float controller_output;
    float fl_torque_delta;
    float fr_torque_delta;
    float rl_torque_delta;
    float rr_torque_delta;
};

#endif  /* __TORQUE_CONTROLLERS_DATA__ */