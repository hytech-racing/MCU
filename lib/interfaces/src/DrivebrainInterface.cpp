#include "DrivebrainInterface.h"
#include "hytech.h"

void DrivebrainInterface::receive_db_torque_lim_message(CAN_message_t& msg, unsigned long curr_millis)
{
    DRIVEBRAIN_TORQUE_LIM_INPUT_t db_data;
    Unpack_DRIVEBRAIN_TORQUE_LIM_INPUT_hytech(&db_data, msg.buf, msg.len);
    _current_drivebrain_data.last_torque_lim_receive_time_millis = curr_millis;

    auto fl = HYTECH_drivebrain_torque_fl_ro_fromS(db_data.drivebrain_torque_fl_ro);
    auto fr = HYTECH_drivebrain_torque_fr_ro_fromS(db_data.drivebrain_torque_fr_ro);
    auto rl = HYTECH_drivebrain_torque_rl_ro_fromS(db_data.drivebrain_torque_rl_ro);
    auto rr = HYTECH_drivebrain_torque_rr_ro_fromS(db_data.drivebrain_torque_rr_ro);
    
    _current_drivebrain_data.torque_limits_nm.FL = (float)fl;
    _current_drivebrain_data.torque_limits_nm.FR = (float)fr;
    _current_drivebrain_data.torque_limits_nm.RL = (float)rl;
    _current_drivebrain_data.torque_limits_nm.RR = (float)rr;
    
}

void DrivebrainInterface::receive_db_speed_setpoint_message(CAN_message_t& msg, unsigned long curr_millis)
{
    DRIVEBRAIN_SPEED_SET_INPUT_t db_data;
    Unpack_DRIVEBRAIN_SPEED_SET_INPUT_hytech(&db_data, msg.buf, msg.len);

    _current_drivebrain_data.last_speed_setpoint_receive_time_millis = curr_millis;
    _current_drivebrain_data.speed_setpoints_rpm.FL = (float)db_data.drivebrain_set_rpm_fl;
    _current_drivebrain_data.speed_setpoints_rpm.FR = (float)db_data.drivebrain_set_rpm_fr;
    _current_drivebrain_data.speed_setpoints_rpm.RL = (float)db_data.drivebrain_set_rpm_rl;
    _current_drivebrain_data.speed_setpoints_rpm.RR = (float)db_data.drivebrain_set_rpm_rr;
    
}