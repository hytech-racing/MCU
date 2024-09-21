#include "DrivebrainController.h"


TorqueControllerOutput_s DrivebrainController::evaluate(const SharedCarState_s &state)
{

    auto sys_tick = state.systick;
    auto db_input = state.db_data;     
    
    bool message_too_latent = (::abs((int)(sys_tick.millis - db_input.last_receive_time_millis)) > (int)_params.allowed_latency);
   

    bool timing_failure = (message_too_latent);

    // only in the case that our speed is low enough (<1 m/s) do we want to clear the fault
    
    bool is_active_controller = state.tc_mux_status.current_controller_mode_ == _params.assigned_controller_mode;

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
        db_input.torque_limits_nm.copy_to_arr(output.command.torqueSetpoints); 
    }
    else
    {
        _timing_failure = true;
        output.command = {{0.0f}, {0.0f}};
    }
    return output;
}