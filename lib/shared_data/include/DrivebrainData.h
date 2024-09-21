#ifndef __DRIVEBRAINDATA_H__
#define __DRIVEBRAINDATA_H__

#include "Utility.h"

struct DrivebrainData_s
{
    unsigned long last_receive_time_millis;
    veh_vec<float> torque_limits_nm;
    veh_vec<float> speed_setpoints_rpm;
};

#endif // __DRIVEBRAINDATA_H__