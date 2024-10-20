#include "DrivebrainETHInterface.h"
#include "SharedDataTypes.h"
#include <Arduino.h>

hytech_msgs_MCUOutputData DrivebrainETHInterface::make_db_msg(const SharedCarState_s &shared_state)
{
    hytech_msgs_MCUOutputData out;
    out.accel_percent = shared_state.pedals_data.accelPercent;
    out.brake_percent = shared_state.pedals_data.brakePercent;
    
    out.has_rpm_data = true;
    out.rpm_data.FL = shared_state.drivetrain_data.measuredSpeeds[0];
    out.rpm_data.FR = shared_state.drivetrain_data.measuredSpeeds[1];
    out.rpm_data.RL = shared_state.drivetrain_data.measuredSpeeds[2];
    out.rpm_data.RR = shared_state.drivetrain_data.measuredSpeeds[3];
    
    out.steering_angle_deg = shared_state.steering_data.angle;
    out.MCU_recv_millis = _latest_data.last_receive_time_millis;
    out.load_cell_data = {shared_state.raw_loadcell_data.raw_load_cell_data.FL,
                          shared_state.raw_loadcell_data.raw_load_cell_data.FR,
                          shared_state.raw_loadcell_data.raw_load_cell_data.RL,
                          shared_state.raw_loadcell_data.raw_load_cell_data.RR};
    out.has_load_cell_data = true;
    return out;
}

void DrivebrainETHInterface::receive_pb_msg(const hytech_msgs_MCUCommandData &msg_in, unsigned long curr_millis)
{
    veh_vec<float> nm_lim(msg_in.torque_limit_nm.FL, msg_in.torque_limit_nm.FR, msg_in.torque_limit_nm.RL, msg_in.torque_limit_nm.RR);

    veh_vec<float> speed_set(msg_in.desired_rpms.FL, msg_in.desired_rpms.FR, msg_in.desired_rpms.RL, msg_in.desired_rpms.RR);

    _latest_data.torque_limits_nm = nm_lim;
    _latest_data.speed_setpoints_rpm = speed_set;
    _latest_data.DB_prev_MCU_recv_millis = msg_in.prev_MCU_recv_millis;
    _latest_data.last_receive_time_millis = curr_millis; // current tick millis
}