#ifndef CASESYSTEM
#define CASESYSTEM


#include "HT08_CONTROL_SYSTEM.h"
#include "StateData.h"
#include "HytechCANInterface.h"

struct CASEConfiguration
{
    bool usePIDTV;
    bool useNormalForce;
    bool usePowerLimit;
    bool usePIDPowerLimit;
    bool useLaunch;
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
    /// @param send_period_ms the period in which messages will be put into the queue.
    CASESystem(message_queue *can_queue, unsigned long send_period_ms, const CASEConfiguration& config)
    {
        msg_queue_ = can_queue;
        case_.initialize();

        config_ = config;
        last_send_time_ = 0;
        send_period_ms_ = send_period_ms;
    }    

    /// @brief function that evaluates the CASE (controller and state estimation) system
    /// @param tick current system tick
    /// @param body_velocity_ms body velocity vector
    /// @param yaw_rate_rads yaw rate in rad / s
    /// @param steering_norm steering value between -1 and 1 ish
    /// @param wheel_rpms wheel rpms
    /// @param wheel_torques_nm current request wheel torque values
    /// @param load_cell_vals load cell forces in N
    /// @param power_kw current electrical power in kilo-watts
    /// @return state of the car
    const pstate &evaluate(const SysTick_s &tick, 
                           const xy_vec &body_velocity_ms,
                           float yaw_rate_rads,
                           float steering_norm,
                           const veh_vec &wheel_rpms,
                           const veh_vec& load_cell_vals,
                           const veh_vec &wheel_torques_nm,
                           float power_kw);
    
    /// @brief configuration function to determine what CASE is using / turn on and off different features within CASE
    /// @param config the configuration struct we will be setting
    void configure(const CASEConfiguration& config)
    {
        config_ = config;
    }
    

private:
    
    CASEConfiguration config_;
    message_queue *msg_queue_;
    HT08_CONTROL_SYSTEM case_;
    pstate state_;
    unsigned long last_send_time_, send_period_ms_;
};

#include "CASESystem.tpp"
#endif