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
public:
    virtual TorqueControllerOutput_s evaluate(const SharedCarState_s &state) = 0;
};

#endif