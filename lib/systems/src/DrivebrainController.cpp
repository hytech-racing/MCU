#include "DrivebrainController.h"


TorqueControllerOutput_s DrivebrainController::evaluate(const SharedCarState_s &state)
{

    auto sys_tick = state.systick;
    auto db_input = state.db_data;     
    
    // cases for timing_failure:
    // 1 if the last_receive_time_millis < 0, then we have not received any messages from the db (initialized at -1 in constructor)
    bool no_messages_received = db_input.last_receive_time_millis < 0;
    
    // 2 if the DB_prev_MCU_recv_millis < 0, then the drivebrain has not received a time from the MCU 
    // (meaning that the MCU is not sending properly or the drivebrain is not receiving properly or it has 
    // yet to receive from the MCU yet)
    bool drivebrain_has_not_received_time = (db_input.DB_prev_MCU_recv_millis < 0);

    // 3 if the time between the current MCU sys_tick.millis time and the last millis time that the drivebrain received is too high
    bool message_too_latent = (::abs((int)(sys_tick.millis - db_input.DB_prev_MCU_recv_millis)) > (int)_params.allowed_latency);
   

    bool timing_failure = (message_too_latent || no_messages_received || drivebrain_has_not_received_time);

    // only in the case that our speed is low enough (<1 m/s) do we want to clear the fault
    
    bool is_active_controller = state.tc_mux_status.active_controller_mode == _params.assigned_controller_mode;

    if ((!is_active_controller) && (!timing_failure))
    {
        // timing failure should be false here
        _timing_failure = false;
    }

    TorqueControllerOutput_s output;
    if (!timing_failure && (!_timing_failure))
    {
        _last_setpoint_millis = db_input.last_receive_time_millis;

        db_input.speed_setpoints_rpm.copy_to_arr(output.command.speeds_rpm); 
        db_input.torque_limits_nm.copy_to_arr(output.command.inverter_torque_limit); 
    }
    else
    {
        _timing_failure = true;
        output.command = {{0.0f}, {0.0f}};
    }
    return output;
}