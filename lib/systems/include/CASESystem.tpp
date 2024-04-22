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

    // in. as defined in HT08_CASE.h
    in.SteeringWheelAngleDeg = steering_data.angle;

    in.TorqueAverageNm = calculate_torque_request(pedals_data, config_.max_regen_torque, config_.max_rpm);

    in.YawRaterads = vn_data.angular_rates.z;

    // REAL
    in.Vx_B = vn_data.velocity_x;

    // FAKE
    // in.Vx_B = 5;

    in.FZFL = load_cell_vals.FL.conversion;
    in.FZFR = load_cell_vals.FR.conversion;
    in.FZRL = load_cell_vals.RL.conversion;
    in.FZRR = load_cell_vals.RR.conversion;

    in.CurrentPowerkW = power_kw;

    // REAL
    in.MotorOmegaFLrpm = drivetrain_data.measuredSpeeds[0];
    in.MotorOmegaFRrpm = drivetrain_data.measuredSpeeds[1];
    in.MotorOmegaRLrpm = drivetrain_data.measuredSpeeds[2];
    in.MotorOmegaRRrpm = drivetrain_data.measuredSpeeds[3];

    // FAKE
    // in.MotorOmegaFLrpm = 566.27330024 * 6.3;
    // in.MotorOmegaFRrpm = 566.27330024 * 6.3;
    // in.MotorOmegaRRrpm = 566.27330024 * 6.3;
    // in.MotorOmegaRLrpm = 566.27330024 * 6.3;

    in.usePIDTV = config_.usePIDTV;
    in.useNormalForce = config_.useNormalForce;
    in.usePowerLimit = config_.usePowerLimit;
    in.usePIDPowerLimit = config_.usePIDPowerLimit;
    in.useLaunch = config_.useLaunch;

    in.Vy_B = vn_data.velocity_y;

    in.YawPIDConfig[0] = config_.yaw_pid_p;
    in.YawPIDConfig[1] = config_.yaw_pid_i;
    in.YawPIDConfig[2] = config_.yaw_pid_d;

    in.AbsoluteTorqueLimit = config_.AbsoluteTorqueLimit;

    in.useTractionControl = config_.useTractionControl;

    in.TCS_SLThreshold = config_.tcsSLThreshold;
    in.LaunchSL = config_.launchSL;
    in.LaunchDeadZone = config_.launchDeadZone;

    in.TCSPIDConfig[0] = config_.tcs_pid_p;
    in.TCSPIDConfig[1] = config_.tcs_pid_i;
    in.TCSPIDConfig[2] = config_.tcs_pid_d;

    in.LaunchVelThreshold = config_.launchVelThreshold;
    in.TCSVelThreshold = config_.tcsVelThreshold;

    in.YawPIDErrorThreshold = config_.yawPIDErrorThreshold;
    in.YawPIDVelThreshold = config_.yawPIDVelThreshold;
    in.YawPIDCoastThreshold = config_.yawPIDCoastThreshold;

    in.useTCSLimitedYawPID = config_.useTCSLimitedYawPID;

    in.YawPIDMaxDifferential = config_.yawPIDMaxDifferential;

    in.useDecoupledYawBrakes = config_.useDecoupledYawBrakes;

    in.YawPIDBrakesConfig[0] = config_.yaw_pid_brakes_p;
    in.YawPIDBrakesConfig[1] = config_.yaw_pid_brakes_i;
    in.YawPIDBrakesConfig[2] = config_.yaw_pid_brakes_d;

    in.decoupledYawPIDBrakesMaxDIffere = config_.decoupledYawPIDBrakesMaxDIfference;

    in.useDiscontinuousYawPIDBrakes = config_.useDiscontinuousYawPIDBrakes;

    in.discontinuousBrakesPercentThres = config_.discontinuousBrakesPercentThreshold;

    in.TorqueMode = config_.TorqueMode;

    in.RegenLimit = config_.RegenLimit;

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
        if ((fsm_state == CAR_STATE::READY_TO_DRIVE) && (start_button_pressed))
        {
            in.YawPIDConfig[1] = 0.0f;
        }
        case_.step();
        last_eval_time_ = tick.millis;
    }

    auto res = case_.getExternalOutputs();

    // send these out at the send period

    if ((tick.millis - last_controller_pt1_send_time_) >= (controller_send_period_ms_))
    {
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_boolea);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_normal);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_norm_p);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_pid_ya);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_pid__p);

        last_controller_pt1_send_time_ = tick.millis;
    }

    if (((tick.millis - last_controller_pt1_send_time_) >= (vehicle_math_offset_ms_ / 3)) &&
        ((tick.millis - last_controller_pt2_send_time_) > controller_send_period_ms_))
    {

        // enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_power_);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_powe_p);
        // enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_pow_pn);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_initia);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_tcs_pi);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_tcs__p);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_tcs_to);
        enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_tcs_st);

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
        // enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_tcs_co);
        last_vehm_send_time_ = tick.millis;
    }

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