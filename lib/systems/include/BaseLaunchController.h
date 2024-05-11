#ifndef __BASELAUNCHCONTROLLER_H__
#define __BASELAUNCHCONTROLLER_H__
#include "SharedDataTypes.h"
#include "BaseController.h"
#include <algorithm>
#include <math.h> 
enum class LaunchStates_e
{
    NO_LAUNCH_MODE,
    LAUNCH_NOT_READY,
    LAUNCH_READY,
    LAUNCHING
};

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
    int16_t init_speed_target_ = 0.0;

public:
    BaseLaunchController(int16_t initial_speed_target)
        : init_speed_target_(initial_speed_target)
    {
        writeout_.command = BaseControllerParams::TC_COMMAND_NO_TORQUE;
        writeout_.ready = true;
    }

    void tick(const SysTick_s &tick,
              const PedalsSystemData_s &pedalsData,
              const float wheel_rpms[],
              const vectornav &vn_data);
    LaunchStates_e get_launch_state() { return launch_state_; }
    virtual void calc_launch_algo(const vectornav &vn_data) = 0;
    TorqueControllerOutput_s evaluate(const car_state &state) override;
};
#endif // __BASELAUNCHCONTROLLER_H__