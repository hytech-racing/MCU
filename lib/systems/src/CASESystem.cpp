#include "CASESystem.h"

void CASESystem::tick(const TorqueControllerInput_s &in)
{
    HT08_CASE::ExtU_HT08_CASE_T case_in;

    // case_in. as defined in HT08_CASE.h
    case_in.SteeringWheelAngleDeg = in.steering.angle;

    case_in.TorqueAverageNm = get_torque_request(in.pedals, in.torqueLimit);

    case_in.YawRaterads = in.vn.angular_rates.z;

    // REAL
    case_in.Vx_B = in.vn.velocity_x;

    // FAKE
    // case_in.Vx_B = 5;

    // can these use filtered values?
    case_in.FZFL = in.lc.loadCellConversions.FL.conversion;
    case_in.FZFR = in.lc.loadCellConversions.FR.conversion;
    case_in.FZRL = in.lc.loadCellConversions.RL.conversion;
    case_in.FZRR = in.lc.loadCellConversions.RR.conversion;

    case_in.CurrentElectricalPowerkW = MAX_POWER_LIMIT;

    // REAL
    case_in.MotorOmegaFLrpm = in.drivetrain.measuredSpeeds[0];
    case_in.MotorOmegaFRrpm = in.drivetrain.measuredSpeeds[1];
    case_in.MotorOmegaRLrpm = in.drivetrain.measuredSpeeds[2];
    case_in.MotorOmegaRRrpm = in.drivetrain.measuredSpeeds[3];

    // FAKE, 566.273 rpm = 1 m/s
    // case_in.MotorOmegaFLrpm = 566.27330024 * 1.36;
    // case_in.MotorOmegaFRrpm = 566.27330024 * 1.36;
    // case_in.MotorOmegaRRrpm = 566.27330024 * 1.36;
    // case_in.MotorOmegaRLrpm = 566.27330024 * 1.36;

    // FAKE max rpm
    // case_in.MotorOmegaFLrpm = AMK_MAX_RPM;
    // case_in.MotorOmegaFRrpm = AMK_MAX_RPM;
    // case_in.MotorOmegaRRrpm = AMK_MAX_RPM;
    // case_in.MotorOmegaRLrpm = AMK_MAX_RPM;

    case_in.usePIDTV = config_.usePIDTV;
    case_in.useNormalForce = config_.useNormalForce;
    case_in.usePowerLimit = config_.usePowerLimit;
    case_in.usePIDPowerLimit = config_.usePIDPowerLimit;
    case_in.useLaunch = config_.useLaunch;

    case_in.Vy_B = in.vn.velocity_y;

    case_in.YawPIDConfig[0] = config_.yaw_pid_p;
    case_in.YawPIDConfig[1] = config_.yaw_pid_i;
    case_in.YawPIDConfig[2] = config_.yaw_pid_d;

    case_in.AbsoluteTorqueLimit = config_.AbsoluteTorqueLimit;

    case_in.useTractionControl = config_.useTractionControl;

    case_in.TCS_SLThreshold = config_.tcsSLThreshold;
    case_in.LaunchSL = config_.launchSL;
    case_in.LaunchDeadZone = config_.launchDeadZone;

    case_in.TCSPIDConfig[0] = config_.tcs_pid_p;
    case_in.TCSPIDConfig[1] = config_.tcs_pid_i;
    case_in.TCSPIDConfig[2] = config_.tcs_pid_d;

    case_in.LaunchVelThreshold = config_.launchVelThreshold;
    case_in.TCSVelThreshold = config_.tcsVelThreshold;

    case_in.YawPIDErrorThreshold = config_.yawPIDErrorThreshold;
    case_in.YawPIDVelThreshold = config_.yawPIDVelThreshold;
    case_in.YawPIDCoastThreshold = config_.yawPIDCoastThreshold;

    case_in.useTCSLimitedYawPID = config_.useTCSLimitedYawPID;

    case_in.YawPIDMaxDifferential = config_.yawPIDMaxDifferential;

    case_in.useDecoupledYawBrakes = config_.useDecoupledYawBrakes;

    case_in.YawPIDBrakesConfig[0] = config_.yaw_pid_brakes_p;
    case_in.YawPIDBrakesConfig[1] = config_.yaw_pid_brakes_i;
    case_in.YawPIDBrakesConfig[2] = config_.yaw_pid_brakes_d;

    case_in.decoupledYawPIDBrakesMaxDIffere = config_.decoupledYawPIDBrakesMaxDIfference;

    case_in.useDiscontinuousYawPIDBrakes = config_.useDiscontinuousYawPIDBrakes;

    case_in.discontinuousBrakesPercentThres = config_.discontinuousBrakesPercentThreshold;

    case_in.TorqueMode = config_.TorqueMode;

    case_in.RegenLimit = config_.RegenLimit;

    case_in.useNoRegen5kph = config_.useNoRegen5kph;

    case_in.useTorqueBias = config_.useTorqueBias;

    case_in.DriveTorquePercentFront = config_.DriveTorquePercentFront;

    case_in.BrakeTorquePercentFront = config_.BrakeTorquePercentFront;

    case_in.MechPowerMaxkW = config_.MechPowerMaxkW;

    if ((vn_active_start_time_ == 0) && (in.vn.vn_status >= 2))
    {
        vn_active_start_time_ = in.tick.millis;
    }
    else if (in.vn.vn_status < 2)
    {
        vn_active_start_time_ = 0;
    }

    case_.setExternalInputs(&case_in);
    if ((in.tick.millis - last_eval_time_) >= 1)
    {
        case_.step();
        last_eval_time_ = in.tick.millis;
    }

    HT08_CASE::ExtY_HT08_CASE_T res = case_.getExternalOutputs();

    // send these out at the send period if the controller is active
    if (active){
        if ((in.tick.millis - last_controller_pt1_send_time_) >= (controller_send_period_ms_))
        {
            enqueue_matlab_msg(res.controllerBus_controller_boolea);
            enqueue_matlab_msg(res.controllerBus_controller_normal);
            enqueue_matlab_msg(res.controllerBus_controller_norm_p);
            enqueue_matlab_msg(res.controllerBus_controller_pid_ya);
            enqueue_matlab_msg(res.controllerBus_controller_pid__p);

            last_controller_pt1_send_time_ = in.tick.millis;
        }

        if (((in.tick.millis - last_controller_pt1_send_time_) >= (vehicle_math_offset_ms_ / 3)) &&
            ((in.tick.millis - last_controller_pt2_send_time_) > controller_send_period_ms_))
        {

            enqueue_matlab_msg(res.controllerBus_controller_initia);
            enqueue_matlab_msg(res.controllerBus_controller_tcs_pi);
            enqueue_matlab_msg(res.controllerBus_controller_tcs__p);
            enqueue_matlab_msg(res.controllerBus_controller_tcs_to);
            enqueue_matlab_msg(res.controllerBus_controller_tcs_st);

            last_controller_pt2_send_time_ = in.tick.millis;
        }

        if (((in.tick.millis - last_controller_pt2_send_time_) >= (vehicle_math_offset_ms_ / 3)) &&
            ((in.tick.millis - last_controller_pt3_send_time_) > controller_send_period_ms_))
        {

            enqueue_matlab_msg(res.controllerBus_controller_regen_);
            enqueue_matlab_msg(res.controllerBus_controller_rege_p);
            enqueue_matlab_msg(res.controllerBus_controller_torque);
            enqueue_matlab_msg(res.controllerBus_controller_power_);
            enqueue_matlab_msg(res.controllerBus_controller_powe_p);
            enqueue_matlab_msg(res.controllerBus_controller_pow_pn);

            last_controller_pt3_send_time_ = in.tick.millis;
        }

        if (((in.tick.millis - last_controller_pt1_send_time_) >= vehicle_math_offset_ms_) &&
            ((in.tick.millis - last_vehm_send_time_) > controller_send_period_ms_))
        {
            enqueue_matlab_msg(res.controllerBus_vehm_alpha_deg);
            enqueue_matlab_msg(res.controllerBus_vehm_sl);
            enqueue_matlab_msg(res.controllerBus_vehm_long_corner_);
            enqueue_matlab_msg(res.controllerBus_vehm_wheel_steer_);
            enqueue_matlab_msg(res.controllerBus_vehm_kin_desired_);
            enqueue_matlab_msg(res.controllerBus_vehm_beta_deg);
            enqueue_matlab_msg(res.controllerBus_vehm_wheel_lin_ve);
            // enqueue_matlab_msg(res.controllerBus_controller_tcs_co);
            last_vehm_send_time_ = in.tick.millis;
        }
    }

    writeout_.command.torqueSetpoints[0] = res.FinalTorqueFL;
    writeout_.command.torqueSetpoints[1] = res.FinalTorqueFR;
    writeout_.command.torqueSetpoints[2] = res.FinalTorqueRL;
    writeout_.command.torqueSetpoints[3] = res.FinalTorqueRR;

    writeout_.command.speeds_rpm[0] = get_rpm_setpoint(res.FinalTorqueFL);
    writeout_.command.speeds_rpm[1] = get_rpm_setpoint(res.FinalTorqueFR);
    writeout_.command.speeds_rpm[2] = get_rpm_setpoint(res.FinalTorqueRL);
    writeout_.command.speeds_rpm[3] = get_rpm_setpoint(res.FinalTorqueRR);
}