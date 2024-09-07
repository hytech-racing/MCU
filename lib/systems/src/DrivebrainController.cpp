#include "DrivebrainController.h"

void DrivebrainController::tick(const SysTick_s &sys_tick, DrivebrainData db_input, bool is_active_controller)
{
    
    _writeout.ready = true;
    

    bool speed_setpoint_too_latent = (::abs((int)(sys_tick.millis - db_input.last_speed_setpoint_receive_time_millis)) > (int)_params.allowed_latency);
    bool torque_setpoint_too_latent = (::abs((int)(sys_tick.millis - db_input.last_torque_lim_receive_time_millis)) > (int)_params.allowed_latency);

    auto speed_sp_recv = db_input.last_speed_setpoint_receive_time_millis;
    auto t_sp_recv = db_input.last_torque_lim_receive_time_millis;
   
    bool msg_jitter_too_high;

    int diff = 0;
    if(t_sp_recv > speed_sp_recv)
    {
        msg_jitter_too_high = ( (t_sp_recv - speed_sp_recv) > _params.allowed_jitter);
        diff = (t_sp_recv - speed_sp_recv);
    } else if (speed_sp_recv > t_sp_recv){
        diff = (speed_sp_recv - t_sp_recv);
        msg_jitter_too_high = ( (speed_sp_recv - t_sp_recv) > _params.allowed_jitter);
    } else {
        msg_jitter_too_high = false;
    }
    
    bool timing_failure = (speed_setpoint_too_latent || torque_setpoint_too_latent || msg_jitter_too_high);

    // only in the case that this is the active controller do we want to clear our timing failure
    if ((!is_active_controller) && (!timing_failure))
    {
        // timing failure should be false here
        _timing_failure = false;
    }

    if (!timing_failure && (!_timing_failure))
    {
        _last_sent_speed_setpoint_millis = db_input.last_speed_setpoint_receive_time_millis;
        _last_sent_torque_lim_millis = db_input.last_torque_lim_receive_time_millis;

        db_input.speed_setpoints_rpm.copy_to_arr(_writeout.command.speeds_rpm);
        db_input.torque_limits_nm.copy_to_arr(_writeout.command.torqueSetpoints);
    }
    else
    {
        _timing_failure = true;
        _writeout.command = {0.0f, 0.0f, 0.0f ,0.0f }; // set command to all zeros if bad latency is apparent
    }
}