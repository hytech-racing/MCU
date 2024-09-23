#ifndef __SLIPLAUNCHCONTROLLER_H__
#define __SLIPLAUNCHCONTROLLER_H__
#include "SimpleLaunchController.h"

namespace SlipLaunchControllerParams
{
    const int16_t DEFAULT_LAUNCH_SPEED_TARGET = BaseLaunchControllerParams::DEFAULT_LAUNCH_SPEED_TARGET;
    const float DEFAULT_SLIP_RATIO = 0.2f;
};
class TorqueControllerSlipLaunch : public virtual BaseLaunchController
{
private:
    float slip_ratio_;

public:
    /*!
        SLIP LAUNCH CONTROLLER
        This launch controller is based off of a specified slip constant. It will at all times attempt
        to keep the wheelspeed at this certain higher percent of the body velocity of the car to keep it
        in constant slip
        @param slip_ratio specified launch rate in m/s^2
        @param initial_speed_target the initial speed commanded to the wheels
    */
    TorqueControllerSlipLaunch(float slip_ratio, int16_t initial_speed_target)
        : BaseLaunchController(initial_speed_target),
          slip_ratio_(slip_ratio) {}
    /// @brief default constructor for slip launch controller: DEFAULT_SLIP_RATIO = 0.2, DEFAULT_LAUNCH_SPEED_TARGET = 1500(rpm)
    TorqueControllerSlipLaunch() : TorqueControllerSlipLaunch(SlipLaunchControllerParams::DEFAULT_SLIP_RATIO, SlipLaunchControllerParams::DEFAULT_LAUNCH_SPEED_TARGET) {}
    /// @brief Increases speed target during launch linearly according to slip ratio to keep the cars wheels spinning faster than the velocity for increased traction
    /// @param VectornavData_s &vn_data 
    void calc_launch_algo(const VectornavData_s &vn_data) override;
};
#endif // __SLIPLAUNCHCONTROLLER_H__