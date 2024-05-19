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

/// @brief this class with both take in sensor inputs as well as handle calculations for various derived states of the car.
//         this class will also handle output onto the CAN bus of data
/// @tparam message_queue the msg queue that is being used with the underlying msging interfaces
template <typename socket_type>
class CASESystem
{
public:
    /// @brief constructor for state estimator system.
    /// @param socket_pointer the pointer to socket that will have the output message sent over it
    /// @param controller_send_period_ms the period in which messages will be sent in milliseconds.
    /// @param max_rpm the max rpm to command in the final speed setpoint for positive torque
    /// @param max_regen_torque
    CASESystem(
        socket_type *socket_pointer,
        unsigned long controller_send_period_ms,
        float max_rpm,
        float max_regen_torque)
    {
        
        max_rpm_ = max_rpm;
        max_regen_torque_ = max_regen_torque;
        socket_pointer_ = socket_pointer;
        case_.initialize();
        auto case_config = create_case_config_from_config_msg(DEFAULT_CONFIG);
        case_.set_InstP(case_config);
        vn_active_start_time_ = 0;
        
        last_out_time_ = 0;
        controller_send_period_ms_ = controller_send_period_ms;
    }

    /// @brief function that evaluates the CASE (controller and state estimation) system. updates the internal pstate_ and returns controller result
    /// @param tick current system tick
    /// @param vector_nav vectornav data
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

    void set_output_msg_data_(CASE_msg &curr_msg, const HT08_CASE::ExtY_HT08_CASE_T &out)
    {
        curr_msg.FinalTorqueFL = out.FinalTorqueFL;
        curr_msg.FinalTorqueFR = out.FinalTorqueFR;
        curr_msg.FinalTorqueRL = out.FinalTorqueRL;
        curr_msg.FinalTorqueRR = out.FinalTorqueRR;
        curr_msg.VEHM_Beta_Deg = out.VEHM_Beta_Deg;
        curr_msg.VEHM_Alpha_FL_Deg = out.VEHM_Alpha_FL_Deg;
        curr_msg.VEHM_Alpha_FR_Deg = out.VEHM_Alpha_FR_Deg;
        curr_msg.VEHM_Alpha_RL_Deg = out.VEHM_Alpha_RL_Deg;
        curr_msg.VEHM_Alpha_RR_Deg = out.VEHM_Alpha_RR_Deg;
        curr_msg.VEHM_Long_Corner_Vel_FL_m_s = out.VEHM_Long_Corner_Vel_FL_m_s;
        curr_msg.VEHM_Long_Corner_Vel_FR_m_s = out.VEHM_Long_Corner_Vel_FR_m_s;
        curr_msg.VEHM_Long_Corner_Vel_RL_m_s = out.VEHM_Long_Corner_Vel_RL_m_s;
        curr_msg.VEHM_Long_Corner_Vel_RR_m_s = out.VEHM_Long_Corner_Vel_RR_m_s;
        curr_msg.VEHM_Kinematic_Desired_Yaw_Rate_Rad_s = out.VEHM_Kinematic_Desired_Yaw_Rate_Rad_s;
        curr_msg.VEHM_SL_FL = out.VEHM_SL_FL;
        curr_msg.VEHM_SL_FR = out.VEHM_SL_FR;
        curr_msg.VEHM_SL_RL = out.VEHM_SL_RL;
        curr_msg.VEHM_SL_RR = out.VEHM_SL_RR;
        curr_msg.VEHM_Wheel_Steer_Avg_Deg = out.VEHM_Wheel_Steer_Avg_Deg;
        curr_msg.VEHM_Wheel_Linear_Vel_FL_m_s = out.VEHM_Wheel_Linear_Vel_FL_m_s;
        curr_msg.VEHM_Wheel_Linear_Vel_FR_m_s = out.VEHM_Wheel_Linear_Vel_FR_m_s;
        curr_msg.VEHM_Wheel_Linear_Vel_RL_m_s = out.VEHM_Wheel_Linear_Vel_RL_m_s;
        curr_msg.VEHM_Wheel_Linear_Vel_RR_m_s = out.VEHM_Wheel_Linear_Vel_RR_m_s;
        curr_msg.CONTROLLER_Initial_Torque_Avg_Driver_Side_Request = out.CONTROLLER_Initial_Torque_Avg_Driver_Side_Request;
        curr_msg.CONTROLLER_Mode_Constrained_Torque_Request = out.CONTROLLER_Mode_Constrained_Torque_Request;
        curr_msg.CONTROLLER_Normal_Percent_FL = out.CONTROLLER_Normal_Percent_FL;
        curr_msg.CONTROLLER_Normal_Percent_FR = out.CONTROLLER_Normal_Percent_FR;
        curr_msg.CONTROLLER_Normal_Percent_RL = out.CONTROLLER_Normal_Percent_RL;
        curr_msg.CONTROLLER_Normal_Percent_RR = out.CONTROLLER_Normal_Percent_RR;
        curr_msg.CONTROLLER_Normal_Torque_FL = out.CONTROLLER_Normal_Torque_FL;
        curr_msg.CONTROLLER_Normal_Torque_FR = out.CONTROLLER_Normal_Torque_FR;
        curr_msg.CONTROLLER_Normal_Torque_RL = out.CONTROLLER_Normal_Torque_RL;
        curr_msg.CONTROLLER_Normal_Torque_RR = out.CONTROLLER_Normal_Torque_RR;
        curr_msg.CONTROLLER_Yaw_PID_Output = out.CONTROLLER_Yaw_PID_Output;
        curr_msg.CONTROLLER_Yaw_Rate_Error_Rad_s = out.CONTROLLER_Yaw_Rate_Error_Rad_s;
        curr_msg.CONTROLLER_Kinematic_Desired_Yaw_Rate_Rad_s = out.CONTROLLER_Kinematic_Desired_Yaw_Rate_Rad_s;
        curr_msg.CONTROLLER_Yaw_PID_Torque_FL = out.CONTROLLER_Yaw_PID_Torque_FL;
        curr_msg.CONTROLLER_Yaw_PID_Torque_FR = out.CONTROLLER_Yaw_PID_Torque_FR;
        curr_msg.CONTROLLER_Yaw_PID_Torque_RL = out.CONTROLLER_Yaw_PID_Torque_RL;
        curr_msg.CONTROLLER_Yaw_PID_Torque_RR = out.CONTROLLER_Yaw_PID_Torque_RR;
        curr_msg.CONTROLLER_Power_Limit_Error_kW = out.CONTROLLER_Power_Limit_Error_kW;
        curr_msg.CONTROLLER_Power_Limit_Status = out.CONTROLLER_Power_Limit_Status;
        curr_msg.CONTROLLER_Power_Limit_Torque_Adjustment = out.CONTROLLER_Power_Limit_Torque_Adjustment;
        curr_msg.CONTROLLER_Power_Limit_Corner_Power_FL_kW = out.CONTROLLER_Power_Limit_Corner_Power_FL_kW;
        curr_msg.CONTROLLER_Power_Limit_Corner_Power_FR_kW = out.CONTROLLER_Power_Limit_Corner_Power_FR_kW;
        curr_msg.CONTROLLER_Power_Limit_Corner_Power_RL_kW = out.CONTROLLER_Power_Limit_Corner_Power_RL_kW;
        curr_msg.CONTROLLER_Power_Limit_Corner_Power_RR_kW = out.CONTROLLER_Power_Limit_Corner_Power_RR_kW;
        curr_msg.CONTROLLER_Power_Limit_Torque_FL = out.CONTROLLER_Power_Limit_Torque_FL;
        curr_msg.CONTROLLER_Power_Limit_Torque_FR = out.CONTROLLER_Power_Limit_Torque_FR;
        curr_msg.CONTROLLER_Power_Limit_Torque_RL = out.CONTROLLER_Power_Limit_Torque_RL;
        curr_msg.CONTROLLER_Power_Limit_Torque_RR = out.CONTROLLER_Power_Limit_Torque_RR;
        curr_msg.CONTROLLER_TCS_Status_FL = out.CONTROLLER_TCS_Status_FL;
        curr_msg.CONTROLLER_TCS_Status_FR = out.CONTROLLER_TCS_Status_FR;
        curr_msg.CONTROLLER_TCS_Status_RL = out.CONTROLLER_TCS_Status_RL;
        curr_msg.CONTROLLER_TCS_Status_RR = out.CONTROLLER_TCS_Status_RR;
        curr_msg.CONTROLLER_TCS_PID_Input_FL = out.CONTROLLER_TCS_PID_Input_FL;
        curr_msg.CONTROLLER_TCS_PID_Input_FR = out.CONTROLLER_TCS_PID_Input_FR;
        curr_msg.CONTROLLER_TCS_PID_Input_RL = out.CONTROLLER_TCS_PID_Input_RL;
        curr_msg.CONTROLLER_TCS_PID_Input_RR = out.CONTROLLER_TCS_PID_Input_RR;
        curr_msg.CONTROLLER_TCS_Adjusted_PID_Output_FL = out.CONTROLLER_TCS_Adjusted_PID_Output_FL;
        curr_msg.CONTROLLER_TCS_Adjusted_PID_Output_FR = out.CONTROLLER_TCS_Adjusted_PID_Output_FR;
        curr_msg.CONTROLLER_TCS_Adjusted_PID_Output_RL = out.CONTROLLER_TCS_Adjusted_PID_Output_RL;
        curr_msg.CONTROLLER_TCS_Adjusted_PID_Output_RR = out.CONTROLLER_TCS_Adjusted_PID_Output_RR;
        curr_msg.CONTROLLER_TCS_Torque_FL = out.CONTROLLER_TCS_Torque_FL;
        curr_msg.CONTROLLER_TCS_Torque_FR = out.CONTROLLER_TCS_Torque_FR;
        curr_msg.CONTROLLER_TCS_Torque_RL = out.CONTROLLER_TCS_Torque_RL;
        curr_msg.CONTROLLER_TCS_Torque_RR = out.CONTROLLER_TCS_Torque_RR;
        curr_msg.CONTROLLER_Regen_5KPH_Torque_FL = out.CONTROLLER_Regen_5KPH_Torque_FL;
        curr_msg.CONTROLLER_Regen_5KPH_Torque_FR = out.CONTROLLER_Regen_5KPH_Torque_FR;
        curr_msg.CONTROLLER_Regen_5KPH_Torque_RL = out.CONTROLLER_Regen_5KPH_Torque_RL;
        curr_msg.CONTROLLER_Regen_5KPH_Torque_RR = out.CONTROLLER_Regen_5KPH_Torque_RR;
        curr_msg.CONTROLLER_Regen_5KPH_Status_FL = out.CONTROLLER_Regen_5KPH_Status_FL;
        curr_msg.CONTROLLER_Regen_5KPH_Status_FR = out.CONTROLLER_Regen_5KPH_Status_FR;
        curr_msg.CONTROLLER_Regen_5KPH_Status_RL = out.CONTROLLER_Regen_5KPH_Status_RL;
        curr_msg.CONTROLLER_Regen_5KPH_Status_RR = out.CONTROLLER_Regen_5KPH_Status_RR;
        curr_msg.CONTROLLER_Bias_Constrained_Torque_Avg_Front = out.CONTROLLER_Bias_Constrained_Torque_Avg_Front;
        curr_msg.CONTROLLER_Bias_Constrained_Torque_Avg_Rear = out.CONTROLLER_Bias_Constrained_Torque_Avg_Rear;
        curr_msg.CONTROLLER_TCS_PID_P_FL = out.CONTROLLER_TCS_PID_P_FL;
        curr_msg.CONTROLLER_TCS_PID_P_FR = out.CONTROLLER_TCS_PID_P_FR;
        curr_msg.CONTROLLER_TCS_PID_P_RL = out.CONTROLLER_TCS_PID_P_RL;
        curr_msg.CONTROLLER_TCS_PID_P_RR = out.CONTROLLER_TCS_PID_P_RR;
        curr_msg.CONTROLLER_TCS_SL_Target_Front = out.CONTROLLER_TCS_SL_Target_Front;
        curr_msg.CONTROLLER_TCS_SL_Target_Rear = out.CONTROLLER_TCS_SL_Target_Rear;
    }

    void handle_sending_outputs_(const HT08_CASE::ExtY_HT08_CASE_T &out)
    {
        CASE_msg msg_out = CASE_msg_init_zero;
        set_output_msg_data_(msg_out, out);
        HT_ETH_Union union_out = HT_ETH_Union_init_zero;
        union_out.which_type_union = HT_ETH_Union_case_msg__tag;
        union_out.type_union.case_msg_ = msg_out;
        if (!handle_ethernet_socket_send_pb(socket_pointer_, union_out, HT_ETH_Union_fields))
        {   
            // TODO this means that something bad has happend
        }
    }

    HT08_CASE::InstP_HT08_CASE_T create_case_config_from_config_msg(const config &msg)
    {
        HT08_CASE::InstP_HT08_CASE_T case_config;
        auto cfg = msg;
        case_config.TCSVelThreshold = cfg.TCSVelThreshold;
        case_config.TCS_General_SideDifferential_LowerBound = cfg.TCS_General_SideDifferential_LowerBound;
        case_config.TCS_General_SideDifferential_UpperBound = cfg.TCS_General_SideDifferential_UpperBound;
        case_config.TCS_General_WheelSteer_LowerBound = cfg.TCS_General_WheelSteer_LowerBound;
        case_config.TCS_General_WheelSteer_UpperBound = cfg.TCS_General_WheelSteer_UpperBound;
        case_config.TCS_PID_D = cfg.TCS_PID_D;
        case_config.TCS_PID_I = cfg.TCS_PID_I;
        case_config.TCS_PID_NormalLoad_EndPercent_Front = cfg.TCS_PID_NormalLoad_EndPercent_Front;
        case_config.TCS_PID_NormalLoad_EndPercent_Rear = cfg.TCS_PID_NormalLoad_EndPercent_Rear;
        case_config.TCS_PID_NormalLoad_StartPercent_Front = cfg.TCS_PID_NormalLoad_StartPercent_Front;
        case_config.TCS_PID_NormalLoad_StartPercent_Rear = cfg.TCS_PID_NormalLoad_StartPercent_Rear;
        case_config.TCS_PID_P_LowerBound_Front = cfg.TCS_PID_P_LowerBound_Front;
        case_config.TCS_PID_P_LowerBound_Rear = cfg.TCS_PID_P_LowerBound_Rear;
        case_config.TCS_PID_P_UpperBound_Front = cfg.TCS_PID_P_UpperBound_Front;
        case_config.TCS_PID_P_UpperBound_Rear = cfg.TCS_PID_P_UpperBound_Rear;
        case_config.TCS_PID_RPM_Lower_Front = cfg.TCS_PID_RPM_Lower_Front;
        case_config.TCS_PID_RPM_Lower_Rear = cfg.TCS_PID_RPM_Lower_Rear;
        case_config.TCS_PID_RPM_Upper_Front = cfg.TCS_PID_RPM_Upper_Front;
        case_config.TCS_PID_RPM_Upper_Rear = cfg.TCS_PID_RPM_Upper_Rear;
        case_config.TCS_SL_NormalLoad_EndPercent_Front = cfg.TCS_SL_NormalLoad_EndPercent_Front;
        case_config.TCS_SL_NormalLoad_EndPercent_Rear = cfg.TCS_SL_NormalLoad_EndPercent_Rear;
        case_config.TCS_SL_NormalLoad_StartPercent_Front = cfg.TCS_SL_NormalLoad_StartPercent_Front;
        case_config.TCS_SL_NormalLoad_StartPercent_Rear = cfg.TCS_SL_NormalLoad_StartPercent_Rear;
        case_config.TCS_SL_Target_EndBound_Front = cfg.TCS_SL_Target_EndBound_Front;
        case_config.TCS_SL_Target_EndBound_Rear = cfg.TCS_SL_Target_EndBound_Rear;
        case_config.TCS_SL_Target_StartBound_Front = cfg.TCS_SL_Target_StartBound_Front;
        case_config.TCS_SL_Target_StartBound_Rear = cfg.TCS_SL_Target_StartBound_Rear;
        case_config.TCS_Saturation_Front = cfg.TCS_Saturation_Front;
        case_config.TCS_Saturation_Rear = cfg.TCS_Saturation_Rear;
        case_config.absTorqueLimit = cfg.absTorqueLimit;
        case_config.brakeTorquePercentFront = cfg.brakeTorquePercentFront;
        case_config.decoupledYawPIDBrakesMaxDifferential = cfg.decoupledYawPIDBrakesMaxDifferential;
        case_config.discontinuousBrakesPercentThreshold = cfg.discontinuousBrakesPercentThreshold;
        case_config.driveTorquePercentFront = cfg.driveTorquePercentFront;
        case_config.launchDeadZone = cfg.launchDeadZone;
        case_config.launchMaxSideDifferential = cfg.launchMaxSideDifferential;
        case_config.launchSL_Target_EndBound_Front = cfg.launchSL_Target_EndBound_Front;
        case_config.launchSL_Target_EndBound_Rear = cfg.launchSL_Target_EndBound_Rear;
        case_config.launchSL_Target_StartBound_Front = cfg.launchSL_Target_StartBound_Front;
        case_config.launchSL_Target_StartBound_Rear = cfg.launchSL_Target_StartBound_Rear;
        case_config.launchVelThreshold = cfg.launchVelThreshold;
        case_config.maxNormalLoadBrakeScalingFront = cfg.maxNormalLoadBrakeScalingFront;
        case_config.mechPowerMax_kW = cfg.mechPowerMax_kW;
        case_config.regenLimit = cfg.regenLimit;
        case_config.torqueMode = cfg.torqueMode;
        case_config.useDecoupledYawBrakes = cfg.useDecoupledYawBrakes;
        case_config.useDiscontinuousYawPIDBrakes = cfg.useDiscontinuousYawPIDBrakes;
        case_config.useLaunch = cfg.useLaunch;
        case_config.useNoRegen5kph = cfg.useNoRegen5kph;
        case_config.useNormalForce = cfg.useNormalForce;
        case_config.useNormalLoad_TCS_GainSchedule = cfg.useNormalLoad_TCS_GainSchedule;
        case_config.useNormalLoad_TCS_SL_Schedule = cfg.useNormalLoad_TCS_SL_Schedule;
        case_config.usePIDPowerLimit = cfg.usePIDPowerLimit;
        case_config.usePIDTV = cfg.usePIDTV;
        case_config.usePowerLimit = cfg.usePowerLimit;
        case_config.useRPM_TCS_GainSchedule = cfg.useRPM_TCS_GainSchedule;
        case_config.useTCSLimitedYawPID = cfg.useTCSLimitedYawPID;
        case_config.useTorqueBias = cfg.useTorqueBias;
        case_config.useTractionControl = cfg.useTractionControl;
        case_config.yawPIDCoastThreshold = cfg.yawPIDCoastThreshold;
        case_config.yawPIDErrorThreshold = cfg.yawPIDErrorThreshold;
        case_config.yawPIDMaxDifferential = cfg.yawPIDMaxDifferential;
        case_config.yawPIDVelThreshold = cfg.yawPIDVelThreshold;
        case_config.yaw_PID_Brakes_D = cfg.yaw_PID_Brakes_D;
        case_config.yaw_PID_Brakes_I = cfg.yaw_PID_Brakes_I;
        case_config.yaw_PID_Brakes_P = cfg.yaw_PID_Brakes_P;
        case_config.yaw_PID_D = cfg.yaw_PID_D;
        case_config.yaw_PID_I = cfg.yaw_PID_I;
        case_config.yaw_PID_P = cfg.yaw_PID_P;
        return case_config;
    }

    float calculate_torque_request(const PedalsSystemData_s &pedals_data, float max_regen_torque, float max_rpm);

    /// @brief configuration function to determine what CASE is using / turn on and off different features within CASE
    /// @param config the configuration struct we will be setting

    void update_config_from_param_interface(ParameterInterface &param_interface_ref)
    {
        config cfg = param_interface_ref.get_config();

        auto case_config = create_case_config_from_config_msg(cfg);
        
        case_.set_InstP(case_config);
    }
    float get_rpm_setpoint(float final_torque)
    {
        if (final_torque > 0)
        {
            return max_rpm_;
        }
        else
        {
            return 0;
        }
    }

private:
    
    socket_type *socket_pointer_;
    HT08_CASE case_;
    float max_rpm_, max_regen_torque_;
    unsigned long vn_active_start_time_, last_eval_time_, last_out_time_, controller_send_period_ms_;
};

#include "CASESystem.tpp"
#endif