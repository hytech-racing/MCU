#ifndef __DRIVEBRAINDATA_H__
#define __DRIVEBRAINDATA_H__

#include "Utility.h"

struct DrivebrainData_s
{
    /// @brief the latest time that the MCU received a message w.r.t the current tick's millis
    int64_t last_receive_time_millis = -1;
    /// @brief the latest MCU last_receive_time_millis that the drivebrain received
    int64_t DB_prev_MCU_recv_millis = -1;
    veh_vec<float> torque_limits_nm;
    veh_vec<float> speed_setpoints_rpm;
};

#endif // __DRIVEBRAINDATA_H__