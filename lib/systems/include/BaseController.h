#ifndef BASECONTROLLER
#define BASECONTROLLER
#include "SharedDataTypes.h"

/// @brief definition for a drivetrain command with no torque
namespace BaseControllerParams
{
    const DrivetrainCommand_s TC_COMMAND_NO_TORQUE = {
        .speeds_rpm = {0.0, 0.0, 0.0, 0.0},
        .torqueSetpoints = {0.0, 0.0, 0.0, 0.0}};

}
/**
 * @brief Base class for all controller
 * @note required method(s): evaluate
 */
class Controller
{
public:
    /// @brief ticks specific controller/system it belongs to
    /// @param SharedCarState_s state 
    /// @return TorqueControllerOutput_s
    virtual TorqueControllerOutput_s evaluate(const SharedCarState_s &state) = 0;
};

#endif