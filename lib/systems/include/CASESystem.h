#ifndef CASESYSTEM
#define CASESYSTEM

#include "HT08_CASE.h"
#include "HytechCANInterface.h"
#include "PedalsSystem.h"
#include "DrivetrainSystem.h"
#include "SteeringSystem.h"
#include "MCUStateMachine.h"
#include "ProtobufMsgInterface.h"
#include "ParameterInterface.h"

struct CASEConfiguration
{
    float AbsoluteTorqueLimit;
    float yaw_pid_p;
    float yaw_pid_i;
    float yaw_pid_d;
    float tcs_pid_p_lowerBound_front;
    float tcs_pid_p_upperBound_front;
    float tcs_pid_p_lowerBound_rear;
    float tcs_pid_p_upperBound_rear;
    float tcs_pid_i;
    float tcs_pid_d;
    bool useLaunch;
    bool usePIDTV;
    bool useTCSLimitedYawPID;
    bool useNormalForce;
    bool useTractionControl;
    bool usePowerLimit;
    bool usePIDPowerLimit;
    bool useDecoupledYawBrakes;
    bool useDiscontinuousYawPIDBrakes;
    float tcsSLThreshold;
    float launchSL;
    float launchDeadZone;
    float launchVelThreshold;
    float tcsVelThreshold;
    float yawPIDMaxDifferential;
    float yawPIDErrorThreshold;
    float yawPIDVelThreshold;
    float yawPIDCoastThreshold;
    float yaw_pid_brakes_p;
    float yaw_pid_brakes_i;
    float yaw_pid_brakes_d;
    float decoupledYawPIDBrakesMaxDIfference;
    float discontinuousBrakesPercentThreshold;
    float TorqueMode;
    float RegenLimit;
    bool useNoRegen5kph;
    bool useTorqueBias;
    float DriveTorquePercentFront;
    float BrakeTorquePercentFront;
    float MechPowerMaxkW;
    float launchLeftRightMaxDiff;
    float tcs_pid_lower_rpm_front;
    float tcs_pid_upper_rpm_front;
    float tcs_pid_lower_rpm_rear;
    float tcs_pid_upper_rpm_rear;
    float maxNormalLoadBrakeScalingFront;
    float tcs_saturation_front;
    float tcs_saturation_rear;
    float TCSGenLeftRightDiffLowerBound;
    float TCSGenLeftRightDiffUpperBound;
    float TCSWheelSteerLowerBound;
    float TCSWheelSteerUpperBound;
    bool useRPM_TCS_GainSchedule;
    bool useNL_TCS_GainSchedule;
    float TCS_NL_startBoundPerc_FrontAxle;
    float TCS_NL_endBoundPerc_FrontAxle;
    float TCS_NL_startBoundPerc_RearAxle;
    float TCS_NL_endBoundPerc_RearAxle;
    bool useNL_TCS_SlipSchedule;
    float launchSL_startBound_Front;
    float launchSL_endBound_Front;
    float launchSL_startBound_Rear;
    float launchSL_endBound_Rear;
    float TCS_SL_startBound_Front;
    float TCS_SL_endBound_Front;
    float TCS_SL_startBound_Rear;
    float TCS_SL_endBound_Rear;
    float TCS_SL_NLPerc_startBound_Front;    
    float TCS_SL_NLPerc_endBound_Front;
    float TCS_SL_NLPerc_startBound_Rear;
    float TCS_SL_NLPerc_endBound_Rear;

    float max_rpm;
    float max_regen_torque;
    float max_torque;
};

/// @brief this class with both take in sensor inputs as well as handle calculations for various derived states of the car.
//         this class will also handle output onto the CAN bus of data
/// @tparam message_queue the msg queue that is being used with the underlying msging interfaces
template <typename message_queue>
class CASESystem
{
public:
    /// @brief constructor for state estimator system.
    /// @param can_queue the pointer to the message queue that will have the CAN messages put onto it
    /// @param send_period_ms the period in which messages will be put into the queue to be sent in milliseconds.
    /// @param vehicle_math_offset_ms the offset in ms from controller message sending that the vehicle math messages will be sent
    CASESystem(
        message_queue *can_queue,
        unsigned long controller_send_period_ms,
        unsigned long vehicle_math_offset_ms,
        unsigned long lowest_controller_send_period_ms,
        CASEConfiguration config)
    {
        msg_queue_ = can_queue;
        case_.initialize();
        vn_active_start_time_ = 0;
        config_ = config;
        last_controller_pt1_send_time_ = 0;
        last_controller_pt2_send_time_ = 0;
        last_controller_pt3_send_time_ = 0;
        last_lowest_priority_controller_send_time_ = 0;

        controller_send_period_ms_ = controller_send_period_ms;
        last_vehm_send_time_ = 0;
        vehicle_math_offset_ms_ = vehicle_math_offset_ms;
        lowest_priority_controller_send_period_ms_ = lowest_controller_send_period_ms;
    }

    /// @brief function that evaluates the CASE (controller and state estimation) system. updates the internal pstate_ and returns controller result
    /// @param tick current system tick
    /// @param body_velocity_ms body velocity vector
    /// @param yaw_rate_rads yaw rate in rad / s
    /// @param steering_norm steering value between -1 and 1 ish
    /// @param wheel_rpms wheel rpms
    /// @param pedals_data current pedals data
    /// @param load_cell_vals load cell forces in N
    /// @param power_kw current electrical power in kilo-watts
    /// @param reset_integral bool of whether or not to reset integral term
    /// @return controller output
    DrivetrainCommand_s evaluate(
        const SysTick_s &tick,
        const vector_nav &vn_data,
        const SteeringSystemData_s &steering_data,
        const DrivetrainDynamicReport_s &drivetrain_data,
        const veh_vec<AnalogConversion_s> &load_cell_vals,
        const PedalsSystemData_s &pedals_data,
        float power_kw,
        CAR_STATE fsm_state,
        bool start_button_pressed,
        uint8_t vn_status);

    // void update_pid(float yaw_p, float yaw_i, float yaw_d, float tcs_p, float tcs_i, float tcs_d, float brake_p, float brake_i, float brake_d)
    // {
    //     config_.yaw_pid_p = yaw_p;
    //     config_.yaw_pid_p = yaw_i;
    //     config_.yaw_pid_p = yaw_d;

    //     config_.tcs_pid_p = tcs_p;
    //     config_.tcs_pid_i = tcs_i;
    //     config_.tcs_pid_d = tcs_d;

    //     config_.yaw_pid_brakes_p = brake_p;
    //     config_.yaw_pid_brakes_i = brake_i;
    //     config_.yaw_pid_brakes_d = brake_d;
    // }

    float calculate_torque_request(const PedalsSystemData_s &pedals_data, float max_regen_torque, float max_rpm);
    /// @brief configuration function to determine what CASE is using / turn on and off different features within CASE
    /// @param config the configuration struct we will be setting

    void update_config_from_param_interface(ParameterInterface &param_interface_ref)
    {
        config cfg = param_interface_ref.get_config();
        config_.AbsoluteTorqueLimit = cfg.AbsoluteTorqueLimit;
        config_.yaw_pid_p = cfg.yaw_pid_p;
        config_.yaw_pid_i = cfg.yaw_pid_i;
        config_.yaw_pid_d = cfg.yaw_pid_d;
        config_.tcs_pid_p_lowerBound_front = cfg.tcs_pid_p_lowerBound_front;
        config_.tcs_pid_p_upperBound_front = cfg.tcs_pid_p_upperBound_front;
        config_.tcs_pid_p_lowerBound_rear = cfg.tcs_pid_p_lowerBound_rear;
        config_.tcs_pid_p_upperBound_rear = cfg.tcs_pid_p_upperBound_rear;
        config_.tcs_pid_i = cfg.tcs_pid_i;
        config_.tcs_pid_d = cfg.tcs_pid_d;
        config_.useLaunch = cfg.useLaunch;
        config_.usePIDTV = cfg.usePIDTV;
        config_.useTCSLimitedYawPID = cfg.useTCSLimitedYawPID;
        config_.useNormalForce = cfg.useNormalForce;
        config_.useTractionControl = cfg.useTractionControl;
        config_.usePowerLimit = cfg.usePowerLimit;
        config_.usePIDPowerLimit = cfg.usePIDPowerLimit;
        config_.useDecoupledYawBrakes = cfg.useDecoupledYawBrakes;
        config_.useDiscontinuousYawPIDBrakes = cfg.useDiscontinuousYawPIDBrakes;
        config_.tcsSLThreshold = cfg.tcsSLThreshold;
        config_.launchSL = cfg.launchSL;
        config_.launchDeadZone = cfg.launchDeadZone;
        config_.launchVelThreshold = cfg.launchVelThreshold;
        config_.tcsVelThreshold = cfg.tcsVelThreshold;
        config_.yawPIDMaxDifferential = cfg.yawPIDMaxDifferential;
        config_.yawPIDErrorThreshold = cfg.yawPIDErrorThreshold;
        config_.yawPIDVelThreshold = cfg.yawPIDVelThreshold;
        config_.yawPIDCoastThreshold = cfg.yawPIDCoastThreshold;
        config_.yaw_pid_brakes_p = cfg.yaw_pid_brakes_p;
        config_.yaw_pid_brakes_i = cfg.yaw_pid_brakes_i;
        config_.yaw_pid_brakes_d = cfg.yaw_pid_brakes_d;
        config_.decoupledYawPIDBrakesMaxDIfference = cfg.decoupledYawPIDBrakesMaxDIfference;
        config_.discontinuousBrakesPercentThreshold = cfg.discontinuousBrakesPercentThreshold;
        config_.TorqueMode = cfg.TorqueMode;
        config_.RegenLimit = cfg.RegenLimit;
        config_.useNoRegen5kph = cfg.useNoRegen5kph;
        config_.useTorqueBias = cfg.useTorqueBias;
        config_.DriveTorquePercentFront = cfg.DriveTorquePercentFront;
        config_.BrakeTorquePercentFront = cfg.BrakeTorquePercentFront;
        config_.MechPowerMaxkW = cfg.MechPowerMaxkW;
        config_.launchLeftRightMaxDiff = cfg.launchLeftRightMaxDiff;
        config_.tcs_pid_lower_rpm_front = cfg.tcs_pid_lower_rpm_front;
        config_.tcs_pid_upper_rpm_front = cfg.tcs_pid_upper_rpm_front;
        config_.tcs_pid_lower_rpm_rear = cfg.tcs_pid_lower_rpm_rear;
        config_.tcs_pid_upper_rpm_rear = cfg.tcs_pid_upper_rpm_rear;
        config_.maxNormalLoadBrakeScalingFront = cfg.maxNormalLoadBrakeScalingFront;
        config_.max_rpm = cfg.max_rpm;
        config_.max_regen_torque = cfg.max_regen_torque;
        config_.max_torque = cfg.max_torque;
    }
    float get_rpm_setpoint(float final_torque)
    {
        if (final_torque > 0)
        {
            return config_.max_rpm;
        }
        else
        {
            return 0;
        }
    }

private:
    CASEConfiguration config_;
    message_queue *msg_queue_;
    HT08_CASE case_;

    unsigned long vn_active_start_time_, last_eval_time_, vehicle_math_offset_ms_, last_controller_pt1_send_time_, last_controller_pt2_send_time_, last_controller_pt3_send_time_, last_vehm_send_time_, controller_send_period_ms_, lowest_priority_controller_send_period_ms_, last_lowest_priority_controller_send_time_;
};

#include "CASESystem.tpp"
#endif