#ifndef __DRIVEBRAINCONTROLLER_H__
#define __DRIVEBRAINCONTROLLER_H__

#include "DrivebrainInterface.h"
#include "TorqueControllers.h"
#include "DrivebrainData.h"
#include "BaseController.h"
#include "SharedDataTypes.h"

// TODO - [x] need to validate that the times that are apparent in the drivebrain data
//            and ensure that they are within tolerence to current sys-tick

// TODO - [ ] if the drivebrain controller is currently the active controller,
//            the latency fault should be latching

//              meaning that if we fail any of the latency checks while active we cannot clear the timing failure fault
//              unless we switch to another controller and back again. in reality, the CAN line or ethernet conditions
//              probably wont improve randomly during runtime so it will keep faulting. primarily this is just to make sure
//              we dont keep going from latent to not latent while driving and thus the driver gets jittered and the
//              drivetrain will keep "powering up" and "powering down"

class DrivebrainController : public Controller
{
public:

    DrivebrainController(unsigned long allowed_latency, unsigned long allowed_jitter,
                         float max_fault_clear_speed_m_s = 1.0,
                         ControllerMode_e assigned_controller_mode = ControllerMode_e::MODE_4)
    {
        _params = {allowed_jitter, allowed_latency, max_fault_clear_speed_m_s, assigned_controller_mode};
    }

    TorqueControllerOutput_s evaluate(const SharedCarState_s &state);

private:
    struct
    {
        unsigned long allowed_jitter;
        unsigned long allowed_latency;
        float max_fault_clear_speed_m_s;
        ControllerMode_e assigned_controller_mode;
    } _params;

    bool _timing_failure = false;
    unsigned long _last_sent_torque_lim_millis = -1;
    unsigned long _last_sent_speed_setpoint_millis = -1;
};

#endif // __DRIVEBRAINCONTROLLER_H__