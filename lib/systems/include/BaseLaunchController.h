#ifndef __BASELAUNCHCONTROLLER_H__
#define __BASELAUNCHCONTROLLER_H__
#include "SharedDataTypes.h"
#include "BaseController.h"
#include <algorithm>
#include <math.h> 

/// @brief Modes to define launch behavior, where each one waits for acceleration request threshold to move to next mode
/// LAUNCH_NOT_READY keeps speed at 0 and makes sure pedals are not pressed
/// LAUNCH_READY keeps speed at 0 and makes sure break is not pressed
/// LAUNCHING uses respective algorithm to set speed set point and requests torque from motors to reach it
enum class LaunchStates_e
{
    NO_LAUNCH_MODE,
    LAUNCH_NOT_READY,
    LAUNCH_READY,
    LAUNCHING
};

/// @brief contains constants for tick behavior/progression and defaults
namespace BaseLaunchControllerParams
{
    const int16_t DEFAULT_LAUNCH_SPEED_TARGET = 1500;
    const float const_accel_time = 100; // time to use launch speed target in ms
    const float launch_ready_accel_threshold = .1;
    const float launch_ready_brake_threshold = .2;
    const float launch_ready_speed_threshold = 5.0 * METERS_PER_SECOND_TO_RPM; // rpm
    const float launch_go_accel_threshold = .9;
    const float launch_stop_accel_threshold = .5;
}

class BaseLaunchController : public virtual Controller
{
protected:
    TorqueControllerOutput_s writeout_;
    uint32_t time_of_launch_;
    double initial_ecef_x_;
    double initial_ecef_y_;
    double initial_ecef_z_;
    LaunchStates_e launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
    uint32_t current_millis_;
    float launch_speed_target_ = 0.0;
    int16_t init_speed_target_ = 0;

public:
    /// @brief Constructor for template launch controller
    /// @param initial_speed_target used only in simple launch controller algorithm
    /// @note requires one method: calc_launch_algo
    BaseLaunchController(int16_t initial_speed_target)
        : init_speed_target_(initial_speed_target)
    {
        writeout_.command = BaseControllerParams::TC_COMMAND_NO_TORQUE;
        writeout_.ready = true;
    }

    /// @brief ticks launch controller to progress through launch states when conditions are met
    void tick(const SysTick_s &tick,
              const PedalsSystemData_s &pedalsData,
              const float wheel_rpms[],
              const VectornavData_s &vn_data);
    LaunchStates_e get_launch_state() { return launch_state_; }
    /// @brief calculates how speed target, the speed the car is trying to achieve during launch, is set and/or increased during launch
    /// @param vn_data vector data like speed and coordinates
    /// @note defines important variation in launch controller tick/evaluation as the launch controllers share a tick method defined in this parent class implementation
    /// @note all launch algorithms are implemented in LaunchControllerAlgos.cpp
    virtual void calc_launch_algo(const VectornavData_s &vn_data) = 0;
    /// @note refer to parent class
    TorqueControllerOutput_s evaluate(const SharedCarState_s &state) override;
};
#endif // __BASELAUNCHCONTROLLER_H__