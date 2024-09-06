#ifndef __DRIVEBRAINCONTROLLER_H__
#define __DRIVEBRAINCONTROLLER_H__

#include "DrivebrainInterface.h"
#include "TorqueControllers.h"
#include "DrivebrainData.h"

// TODO - [ ] need to validate that the times that are apparent in the drivebrain data
//      and ensure that they are within tolerence to current sys-tick
// TODO - [ ] set 
class DrivebrainController : public TorqueController<TC_DRIVEBRAIN>
{
public:
    void tick(const SysTick_s &sys_tick, DrivebrainData db_input);
    
    DrivebrainController(TorqueControllerOutput_s &writeout, unsigned long allowed_latency, unsigned long allowed_jitter) : _writeout(writeout)
    {
        _params = {allowed_jitter, allowed_latency};
    }

private:
    struct
    {
        unsigned long allowed_jitter;
        unsigned long allowed_latency;
    } _params;

    unsigned long _last_sent_torque_lim_millis = -1;
    unsigned long _last_sent_speed_setpoint_millis = -1;

    TorqueControllerOutput_s &_writeout;
};

#endif // __DRIVEBRAINCONTROLLER_H__