#ifndef CASESYSTEM
#define CASESYSTEM

#include "HT08_CONTROL_SYSTEM.h"
#include "StateData.h"
#include "HytechCANInterface.h"
#include "PedalsSystem.h"


struct CASEConfiguration
{
    bool usePIDTV;
    bool useNormalForce;
    bool usePowerLimit;
    bool usePIDPowerLimit;
    bool useLaunch;
    float max_rpm;
    float max_regen_torque;
    float max_torque;
    float pid_p;
    float pid_i;
    float pid_d;
};

struct CASEControllerOutput
{
    veh_vec rpms;
    veh_vec torques;
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
    CASESystem(message_queue *can_queue, unsigned long controller_send_period_ms, unsigned long vehicle_math_offset_ms, const CASEConfiguration &config)
    {
        msg_queue_ = can_queue;
        case_.initialize();
        vn_active_start_time_ = 0;
        config_ = config;
        last_controller_pt1_send_time_ = 0;
        last_controller_pt2_send_time_ = 0;

        controller_send_period_ms_ = controller_send_period_ms;
        last_vehm_send_time_ = 0;
        vehicle_math_offset_ms_= vehicle_math_offset_ms;
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
    CASEControllerOutput evaluate(const SysTick_s &tick,
                           const xy_vec &body_velocity_ms,
                           float yaw_rate_rads,
                           float steering_norm,
                           const veh_vec &wheel_rpms,
                           const veh_vec &load_cell_vals,
                           const PedalsSystemData_s &pedals_data,
                           float power_kw,
                           bool reset_integral, 
                           uint8_t vn_status);

    void update_pid(float p, float i, float d)
    {
        config_.pid_p = p;
        config_.pid_p = i;
        config_.pid_p = d;
    }
    float calculate_torque_request(const PedalsSystemData_s &pedals_data, float max_regen_torque, float max_torque, float max_rpm);
    /// @brief configuration function to determine what CASE is using / turn on and off different features within CASE
    /// @param config the configuration struct we will be setting
    void configure(const CASEConfiguration &config)
    {
        config_ = config;
    }

private:
    CASEConfiguration config_;
    message_queue *msg_queue_;
    HT08_CONTROL_SYSTEM case_;
    pstate state_;

    unsigned long vn_active_start_time_, last_eval_time_, vehicle_math_offset_ms_, last_controller_pt1_send_time_, last_controller_pt2_send_time_,  last_vehm_send_time_, controller_send_period_ms_;
};

#include "CASESystem.tpp"
#endif