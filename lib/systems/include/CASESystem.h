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
#include "param_adjust.h"

/// @brief this class with both take in sensor inputs as well as handle calculations for various derived states of the car.
//         this class will also handle output onto the CAN bus of data
/// @tparam message_queue the msg queue that is being used with the underlying msging interfaces
template <typename message_queue>
class CASESystem
{
public:
    /// @brief constructor for state estimator system.
    /// @param message_queue the pointer to msg out queue
    /// @param controller_send_period_ms the period in which messages will be sent in milliseconds.
    /// @param max_rpm the max rpm to command in the final speed setpoint for positive torque
    /// @param max_regen_torque
    CASESystem(
        message_queue *msg_queue,
        unsigned long controller_send_period_ms,
        unsigned long vehicle_math_offset_ms,
        unsigned long lowest_controller_send_period_ms,
        float max_rpm,
        float max_regen_torque)
    {
        max_rpm_ = max_rpm;
        max_regen_torque_ = max_regen_torque;
        message_queue_ = msg_queue;
        case_.initialize();
        auto case_config = create_case_config_from_config_msg(DEFAULT_CONFIG);
        case_.set_InstP(case_config);
        
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

    float calculate_torque_request(const PedalsSystemData_s &pedals_data, float max_regen_torque, float max_rpm);

    /// @brief configuration function to determine what CASE is using / turn on and off different features within CASE
    /// @param config the configuration struct we will be setting
    void update_config_from_param_interface(ParameterInterface &param_interface_ref)
    {
        if (param_interface_ref.new_CASE_config_available())
        {
            config cfg = param_interface_ref.get_CASE_config();

            auto case_config = create_case_config_from_config_msg(cfg);

            case_.set_InstP(case_config);
        }
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
    void handle_CAN_sending_(const SysTick_s& tick, const HT08_CASE::ExtY_HT08_CASE_T& res);
    message_queue *message_queue_;
    HT08_CASE case_;
    float max_rpm_, max_regen_torque_;
    
    unsigned long vn_active_start_time_, last_eval_time_, vehicle_math_offset_ms_, last_controller_pt1_send_time_, last_controller_pt2_send_time_, last_controller_pt3_send_time_, last_vehm_send_time_, controller_send_period_ms_, lowest_priority_controller_send_period_ms_, last_lowest_priority_controller_send_time_;
};

#include "CASESystem.tpp"
#endif