#include "CASESystem.h"

template <typename message_queue>
CASEControllerOutput CASESystem<message_queue>::evaluate(const SysTick_s &tick,
                                                  const xy_vec &body_velocity_ms,
                                                  float yaw_rate_rads,
                                                  float steering_norm,
                                                  const veh_vec &wheel_rpms,
                                                  const veh_vec &load_cell_vals,
                                                  const PedalsSystemData_s &pedals_data,
                                                  float power_kw,
                                                  bool reset_integral, 
                                                  uint8_t vn_status)
{
    HT08_CONTROL_SYSTEM::ExtU_HT08_CONTROL_SYSTEM_T in;

    float steering_value = steering_norm * 130;
    in.PIDConfig[0] = config_.pid_p;
    in.PIDConfig[1] = config_.pid_i;
    in.PIDConfig[2] = config_.pid_d;

    // if((vn_active_start_time_ == 0) && (vn_status >=2))
    // {
    //     vn_active_start_time_ = tick.millis;
    // } else if(vn_status < 2)
    // {
    //     vn_active_start_time_ = 0;
    // }

    // bool vn_active_for_long_enough = (vn_active_start_time_ >= 5000);
    // if(vn_active_for_long_enough){
    in.usePIDTV = config_.usePIDTV;
    // } else {
        // in.usePIDTV = false;
    // }
    
    in.useNormalForce = config_.useNormalForce;
    in.usePowerLimit = config_.usePowerLimit;
    in.usePIDPowerLimit = config_.usePIDPowerLimit;
    in.useLaunch = config_.useLaunch;

    in.SteeringWheelAngleDeg = steering_value;

    in.TorqueAverageNm = calculate_torque_request(pedals_data, config_.max_regen_torque, config_.max_torque, config_.max_rpm);

    in.YawRaterads = yaw_rate_rads;
    in.Vx_B = body_velocity_ms.x;
    in.Vy_B = body_velocity_ms.y;

    in.FZFL = load_cell_vals.FL;
    in.FZFR = load_cell_vals.FR;
    in.FZRL = load_cell_vals.RL;
    in.FZRR = load_cell_vals.RR;
    in.CurrentPowerkW = power_kw;
    in.MotorOmegaFLrpm = wheel_rpms.FL;
    in.MotorOmegaFRrpm = wheel_rpms.FR;
    in.MotorOmegaRLrpm = wheel_rpms.RL;
    in.MotorOmegaRRrpm = wheel_rpms.RR;

    case_.setExternalInputs(&in);
    if( (tick.millis - last_eval_time_ ) >= 1 )
    {
        if(reset_integral)
        {
            in.PIDConfig[1] = 0.0f;
        }
        case_.step();
        last_eval_time_ = tick.millis;
    }
    
    auto res = case_.getExternalOutputs();

    // state_.Alphadeg.FL = res.AlphaFLDeg;
    // state_.Alphadeg.FR = res.AlphaFRDeg;
    // state_.Alphadeg.RL = res.AlphaRLDeg;
    // state_.Alphadeg.RR = res.AlphaRRDeg;
    // state_.bodyVel = body_velocity_ms;
    // state_.KinematicDesiredYawRaterads = res.KinematicDesiredYawRaterads;
    // state_.LongitudinalCornerVelms.FL = res.LongitudinalCornerVelWFLms;
    // state_.LongitudinalCornerVelms.FR = res.LongitudinalCornerVelWFRms;
    // state_.LongitudinalCornerVelms.RL = res.LongitudinalCornerVelWRLms;
    // state_.LongitudinalCornerVelms.RR = res.LongitudinalCornerVelWRRms;
    // state_.longitudinalSlip.FL = res.SLFL;
    // state_.longitudinalSlip.FR = res.SLFR;
    // state_.longitudinalSlip.RL = res.SLRL;
    // state_.longitudinalSlip.RR = res.SLRR;
    // state_.beta = res.BetaDeg;

    // send these out at the send period

    if ((tick.millis - last_controller_pt1_send_time_) >= (controller_send_period_ms_))
    {
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_boolea);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_normal);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_norm_p);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_pid_ya);
        last_controller_pt1_send_time_ = tick.millis;
    }

    if (((tick.millis - last_controller_pt1_send_time_) >= (vehicle_math_offset_ms_ / 2)) &&
        ((tick.millis - last_controller_pt2_send_time_) > controller_send_period_ms_))
    {
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_pid__p);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_power_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_powe_p);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_pow_pn);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_initia);
        last_controller_pt2_send_time_ = tick.millis;
    }

    if (((tick.millis - last_controller_pt1_send_time_) >= vehicle_math_offset_ms_) &&
        ((tick.millis - last_vehm_send_time_) > controller_send_period_ms_))
    {
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_alpha_deg);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_sl);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_long_corner_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_wheel_steer_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_kin_desired_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_beta_deg);
        last_vehm_send_time_ = tick.millis;
    }
    // TODO make these real
    veh_vec rpms;
    
    rpms.FL = get_rpm_setpoint(res.FinalTorqueFL);
    rpms.FR = get_rpm_setpoint(res.FinalTorqueFR);
    rpms.RL = get_rpm_setpoint(res.FinalTorqueRL);
    rpms.RR = get_rpm_setpoint(res.FinalTorqueRR);
    veh_vec torques;
    torques.FL = res.FinalTorqueFL;
    torques.FR = res.FinalTorqueFR;
    torques.RL = res.FinalTorqueRL;
    torques.RR = res.FinalTorqueRR;

    return {rpms, torques};
}

template <typename message_queue>
float CASESystem<message_queue>::calculate_torque_request(const PedalsSystemData_s &pedals_data, float max_regen_torque, float max_torque, float max_rpm)
{
    // Both pedals are not pressed and no implausibility has been detected
    // accelRequest goes between 1.0 and -1.0
    float accelRequest = pedals_data.accelPercent - pedals_data.regenPercent;
    float torqueRequest;

    if (accelRequest >= 0.0)
    {
        // Positive torque request
        torqueRequest = accelRequest * max_torque;
    }
    else
    {
        // Negative torque request
        torqueRequest = max_regen_torque * accelRequest * -1.0;

    }
    return torqueRequest;
}