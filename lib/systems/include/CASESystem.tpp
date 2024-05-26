#include "CASESystem.h"

template <typename message_queue>
DrivetrainCommand_s CASESystem<message_queue>::evaluate(
    const SysTick_s &tick,
    const vector_nav &vn_data,
    const SteeringSystemData_s &steering_data,
    const DrivetrainDynamicReport_s &drivetrain_data,
    const veh_vec<AnalogConversion_s> &load_cell_vals,
    const PedalsSystemData_s &pedals_data,
    float power_kw,
    CAR_STATE fsm_state,
    bool start_button_pressed,
    uint8_t vn_status)
{
    HT08_CASE::ExtU_HT08_CASE_T in;

    // in. as defined in HT08_CASE.h, ExtU_HT08_CASE_T
    in.SteeringWheelAngleDeg = steering_data.angle;
    
    in.CurrentElectricalPowerkW = power_kw;
    in.Vy_B = vn_data.velocity_y;
    // in.YawRaterads = 2.5; // THIS IS FAKE TODO HACK
    in.YawRaterads = vn_data.angular_rates.z;
    in.InitialTorqueAvgDriverRequest = calculate_torque_request(pedals_data, max_regen_torque_, max_rpm_);
    // FAKE
    // in.Vx_B = 5;
    in.Vx_B = vn_data.velocity_x;
    // REAL
    in.MotorOmegaFLRPM = drivetrain_data.measuredSpeeds[0];
    in.MotorOmegaFRRPM = drivetrain_data.measuredSpeeds[1];
    in.MotorOmegaRLRPM = drivetrain_data.measuredSpeeds[2];
    in.MotorOmegaRRRPM = drivetrain_data.measuredSpeeds[3];

    // FAKE, 566.273 rpm = 1 m/s
    // in.MotorOmegaFLRPM = 566.27330024 * 5;
    // in.MotorOmegaFRRPM = 566.27330024 * 10;
    // in.MotorOmegaRLRPM = 566.27330024 * 1.36;
    // in.MotorOmegaRRRPM = 566.27330024 * 1.36;

    // FAKE max rpm
    // in.MotorOmegaFLRPM = 20000;
    // in.MotorOmegaFRRPM = 20000;
    // in.MotorOmegaRLRPM = 20000;
    // in.MotorOmegaRRRPM = 20000;    

    in.FZFL = load_cell_vals.FL.conversion;
    in.FZFR = load_cell_vals.FR.conversion;
    in.FZRL = load_cell_vals.RL.conversion;
    in.FZRR = load_cell_vals.RR.conversion;

    if ((vn_active_start_time_ == 0) && (vn_status >= 2))
    {
        vn_active_start_time_ = tick.millis;
    }
    else if (vn_status < 2)
    {
        vn_active_start_time_ = 0;
    }



    case_.setExternalInputs(&in);
    if ((tick.millis - last_eval_time_) >= 1)
    {
        case_.step();
        last_eval_time_ = tick.millis;
    }

    auto res = case_.getExternalOutputs();

    handle_CAN_sending_(tick, res);

    // send these out at the send period
    
    DrivetrainCommand_s command;

    command.torqueSetpoints[0] = res.FinalTorqueFL;
    command.torqueSetpoints[1] = res.FinalTorqueFR;
    command.torqueSetpoints[2] = res.FinalTorqueRL;
    command.torqueSetpoints[3] = res.FinalTorqueRR;

    command.speeds_rpm[0] = get_rpm_setpoint(res.FinalTorqueFL);
    command.speeds_rpm[1] = get_rpm_setpoint(res.FinalTorqueFR);
    command.speeds_rpm[2] = get_rpm_setpoint(res.FinalTorqueRL);
    command.speeds_rpm[3] = get_rpm_setpoint(res.FinalTorqueRR);

    return command;
}

template <typename message_queue>
float CASESystem<message_queue>::calculate_torque_request(const PedalsSystemData_s &pedals_data, float max_regen_torque, float max_rpm)
{
    // accelRequest goes between 1.0 and -1.0
    float accelRequest = pedals_data.accelPercent - pedals_data.regenPercent;
    float torqueRequest;

    if (accelRequest >= 0.0)
    {
        // Positive torque request
        torqueRequest = accelRequest * AMK_MAX_TORQUE;
    }
    else
    {
        // Negative torque request
        torqueRequest = max_regen_torque * accelRequest;
    }
    return torqueRequest;
}

template <typename message_queue>
void CASESystem<message_queue>::handle_CAN_sending_(const SysTick_s &tick, const HT08_CASE::ExtY_HT08_CASE_T& res)
{
    if ((tick.millis - last_controller_pt1_send_time_) >= (controller_send_period_ms_))
    {
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_normal_torque);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_normal_dist);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_pid_yaw);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_power_lim);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_slip_targets);

        last_controller_pt1_send_time_ = tick.millis;
    }

    // tcs controller 
    if (((tick.millis - last_controller_pt1_send_time_) >= (vehicle_math_offset_ms_ / 3)) &&
        ((tick.millis - last_controller_pt2_send_time_) > controller_send_period_ms_))
    {

        // enqueue_matlab_msg(message_queue_, res.controllerBus_controller_initia);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_pid_input);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_pid_output);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_torque);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_status);
        // enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_pn);

        last_controller_pt2_send_time_ = tick.millis;
    }

    // controller
    if (((tick.millis - last_controller_pt2_send_time_) >= (vehicle_math_offset_ms_ / 3)) &&
        ((tick.millis - last_controller_pt3_send_time_) > controller_send_period_ms_))
    {

        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_regen_5kph_status);
        // enqueue_matlab_msg(message_queue_, res.controllerBus_controller_power_lim_corner_pow);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_torque_setup);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_power_lim);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_power_lim_torque);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_power_lim_corner_pow);

        last_controller_pt3_send_time_ = tick.millis;
    }
    // vehm
    if (((tick.millis - last_controller_pt1_send_time_) >= vehicle_math_offset_ms_) &&
        ((tick.millis - last_vehm_send_time_) > controller_send_period_ms_))
    {
        enqueue_matlab_msg(message_queue_, res.controllerBus_vehm_alpha);
        enqueue_matlab_msg(message_queue_, res.controllerBus_vehm_sl);
        enqueue_matlab_msg(message_queue_, res.controllerBus_vehm_long_corner_vel);
        enqueue_matlab_msg(message_queue_, res.controllerBus_vehm_wheel_steer_avg_deg);
        enqueue_matlab_msg(message_queue_, res.controllerBus_vehm_kin_desired_yaw_rate_rad_s);
        enqueue_matlab_msg(message_queue_, res.controllerBus_vehm_beta);
        enqueue_matlab_msg(message_queue_, res.controllerBus_vehm_wheel_lin_vel);

        last_vehm_send_time_ = tick.millis;
    }


    // configs
    if ((tick.millis - last_lowest_priority_controller_send_time_) >= (lowest_priority_controller_send_period_ms_))
    {
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_boolean);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_config);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_yaw_pid_config);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_saturation_config);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_differential_config);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_rpm_schedule_config);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_normal_load_schedule_config);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_config);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_config_cont);
        enqueue_matlab_msg(message_queue_, res.controllerBus_controller_tcs_pid_config);

        last_lowest_priority_controller_send_time_ = tick.millis;
    }
}