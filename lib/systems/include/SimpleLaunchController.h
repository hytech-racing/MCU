#ifndef __SIMPLELAUNCHCONTROLLER_H__
#define __SIMPLELAUNCHCONTROLLER_H__
#include "BaseLaunchController.h"

/* LAUNCH CONSTANTS */
namespace SimpleLaunchControllerParams
{
    const float DEFAULT_LAUNCH_RATE = 11.76;
    const int16_t DEFAULT_LAUNCH_SPEED_TARGET = 1500;

};

class TorqueControllerSimpleLaunch : public BaseLaunchController
{
private:
    float launch_rate_target_;

public:
    /*!
        SIMPLE LAUNCH CONTROLLER
        This launch controller is based off of a specified launch rate and an initial speed target
        It will ramp up the speed target linearlly over time to accelerate
        @param launch_rate specified launch rate in m/s^2
        @param initial_speed_target the initial speed commanded to the wheels
    */
    TorqueControllerSimpleLaunch(float launch_rate, int16_t initial_speed_target)
        : BaseLaunchController(initial_speed_target),
          launch_rate_target_(launch_rate) {}

    TorqueControllerSimpleLaunch() : TorqueControllerSimpleLaunch(SimpleLaunchControllerParams::DEFAULT_LAUNCH_RATE,  SimpleLaunchControllerParams::DEFAULT_LAUNCH_SPEED_TARGET) {}

    LaunchStates_e get_launch_state() override { return launch_state_; }

    void calc_launch_algo(const vectornav &vn_data) override;
};
#endif // __SIMPLELAUNCHCONTROLLER_H__