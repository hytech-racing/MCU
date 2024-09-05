#include "DrivebrainController.h"

void DrivebrainController::tick(const SysTick_s &sys_tick, DrivebrainData db_input)
{
    _writeout.ready = false;

    bool speed_setpoint_too_latent = (::abs((int)(sys_tick.millis - db_input.last_speed_setpoint_receive_time_millis)) > (int)_params.allowed_latency);
    bool torque_setpoint_too_latent = (::abs((int)(sys_tick.millis - db_input.last_torque_lim_receive_time_millis)) > (int)_params.allowed_latency);
    bool msg_jitter_too_high = (::abs((int)(db_input.last_speed_setpoint_receive_time_millis - db_input.last_torque_lim_receive_time_millis)) > (int)_params.allowed_jitter);

    if (!(speed_setpoint_too_latent || torque_setpoint_too_latent || msg_jitter_too_high))
    {
        _writeout.ready = true;

        _last_sent_speed_setpoint_millis = db_input.last_speed_setpoint_receive_time_millis;
        _last_sent_torque_lim_millis = db_input.last_torque_lim_receive_time_millis;

        db_input.speed_setpoints_rpm.copy_to_arr(_writeout.command.speeds_rpm);
        db_input.torque_limits_nm.copy_to_arr(_writeout.command.torqueSetpoints);
    }
    else
    {
        _writeout.ready = false;
        _writeout.command = {}; // set command to all zeros if bad latency is apparent
    }
}