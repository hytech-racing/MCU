#include "DrivebrainETHInterface.h"
#include "SharedDataTypes.h"
#include <Arduino.h>

hytech_msgs_MCUOutputData DrivebrainETHInterface::make_db_msg(const SharedCarState_s &shared_state)
{
    hytech_msgs_MCUOutputData out;
    out.accel_percent = shared_state.pedals_data.accelPercent;
    out.brake_percent = shared_state.pedals_data.brakePercent;
    out.rpm_data = {shared_state.drivetrain_data.measuredSpeeds[0],
                    shared_state.drivetrain_data.measuredSpeeds[1],
                    shared_state.drivetrain_data.measuredSpeeds[2],
                    shared_state.drivetrain_data.measuredSpeeds[3]};
    return out;
}

void DrivebrainETHInterface::receive_pb_msg(const hytech_msgs_MCUCommandData &msg_in, unsigned long curr_millis)
{
    // Serial.println("msg recvd in here");
    veh_vec<float> nm_lim;
    nm_lim.construct(msg_in.torque_limit_nm.FL, msg_in.torque_limit_nm.FR, msg_in.torque_limit_nm.RL, msg_in.torque_limit_nm.RR);

    veh_vec<float> speed_set;
    speed_set.construct(msg_in.desired_rpms.FL, msg_in.desired_rpms.FR, msg_in.desired_rpms.RL, msg_in.desired_rpms.RR);
    // Serial.println(msg_in.desired_rpms.FL);

    _latest_data.torque_limits_nm = nm_lim;
    _latest_data.speed_setpoints_rpm = speed_set;
    _latest_data.last_receive_time_millis = curr_millis;
}