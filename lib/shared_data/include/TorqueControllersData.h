#ifndef __TORQUE_CONTROLLERS_DATA__
#define __TORQUE_CONTROLLERS_DATA__

#include <stdint.h>

struct TCMuxStatus_s
{
    bool speedPreventsModeChange;
    bool torqueDeltaPreventsModeChange;
    bool controllerNotReadyPreventsModeChange;
    bool steeringSystemError;

    uint8_t modeIntended;
    uint8_t modeActual;
    uint8_t dialMode;

    uint8_t torqueMode;
    float maxTorque;
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