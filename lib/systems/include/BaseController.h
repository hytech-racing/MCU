#ifndef BASECONTROLLER
#define BASECONTROLLER
#include "SharedDataTypes.h"
namespace BaseControllerParams
{
    const DrivetrainCommand_s TC_COMMAND_NO_TORQUE = {
        .speeds_rpm = {0.0, 0.0, 0.0, 0.0},
        .torqueSetpoints = {0.0, 0.0, 0.0, 0.0}};

}
class Controller
{
private:
    // common function for calculation of the limited torque request that goes into controllers
    float get_torque_request_(float torque_limit_nm, const PedalsSystemData_s &pedals_data) { return 0; };

public:
    virtual TorqueControllerOutput_s evaluate(const SharedCarState_s &state) = 0;
};

#endif