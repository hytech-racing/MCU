#include "CASESystem.h"

template <typename message_queue>
const pstate &CASESystem<message_queue>::evaluate(const SysTick_s &tick,
                                                  const xy_vec &body_velocity_ms,
                                                  float yaw_rate_rads,
                                                  float steering_norm,
                                                  const veh_vec &wheel_rpms,
                                                  const veh_vec &load_cell_vals,
                                                  const veh_vec &wheel_torques_nm,
                                                  float power_kw)
{
    HT08_CONTROL_SYSTEM::ExtU_HT08_CONTROL_SYSTEM_T in;

    float steering_value = steering_norm * 130;

    in.usePIDTV = config_.usePIDTV;
    in.useNormalForce = config_.useNormalForce;
    in.usePowerLimit = config_.usePowerLimit;
    in.usePIDPowerLimit = config_.usePIDPowerLimit;
    in.useLaunch = config_.useLaunch;

    in.SteeringWheelAngleDeg = steering_value;

    float nm_avg = (wheel_torques_nm.FL + wheel_torques_nm.FR + wheel_torques_nm.RL + wheel_torques_nm.RR) / 4.0f;
    in.TorqueAverageNm = nm_avg;

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
    case_.step();
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

    if( ((tick.millis - last_controller_pt1_send_time_) >= (vehicle_math_offset_ms_/2)) &&
        ((tick.millis - last_controller_pt2_send_time_) > controller_send_period_ms_) )
    {
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_pid__p);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_power_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_powe_p);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_pow_pn);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_initia);
        last_controller_pt2_send_time_ = tick.millis;
    }
    
    if ( ((tick.millis - last_controller_pt1_send_time_) >= vehicle_math_offset_ms_) &&
         ((tick.millis - last_vehm_send_time_) > controller_send_period_ms_)
        )
    {
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_alpha_deg);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_sl);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_long_corner_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_wheel_steer_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_kin_desired_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_vehm_beta_deg);
        last_vehm_send_time_ = tick.millis;
    }
    return state_;
}