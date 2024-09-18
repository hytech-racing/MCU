#ifndef __LOOKUPLAUNCHCONTROLLER_H__
#define __LOOKUPLAUNCHCONTROLLER_H__
#include "BaseLaunchController.h"
#include "accel_lookup.h"

namespace LookupLaunchControllerParams
{
    const int16_t DEFAULT_LAUNCH_SPEED_TARGET = BaseLaunchControllerParams::DEFAULT_LAUNCH_SPEED_TARGET;
};
class TorqueControllerLookupLaunch : public virtual BaseLaunchController 
{
private:
    bool init_position = false;

public:
    /*!
        Lookup Launch Controller
        This launch controller is based off of a matlab and symlink generated lookup table.
        This has been converted to a C array with some basic python code using the array index
        as the input for the controller
        @param initial_speed_target the initial speed commanded to the wheels
    */
    TorqueControllerLookupLaunch(int16_t initial_speed_target)
        : BaseLaunchController(initial_speed_target) {}

    TorqueControllerLookupLaunch() : TorqueControllerLookupLaunch(LookupLaunchControllerParams::DEFAULT_LAUNCH_SPEED_TARGET) {}

    void calc_launch_algo(const VectornavData_s &vn_data) override;
};


#endif // __LOOKUPLAUNCHCONTROLLER_H__