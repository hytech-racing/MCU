#ifndef BASECONTROLLER
#define BASECONTROLLER
#include "SharedDataTypes.h"

/// @brief defines namespace for definition of a drivetrain command with no torque for clearer code in the Muxer
namespace BaseControllerParams
{
    const DrivetrainCommand_s TC_COMMAND_NO_TORQUE = {
        .speeds_rpm = {0.0, 0.0, 0.0, 0.0},
        .torqueSetpoints = {0.0, 0.0, 0.0, 0.0}};

}
/**
 * @brief Base class for all controller
 *        required method(s): evaluate
 */
class Controller
{
public:
    /// @brief This ticks specific controller/system it belongs to. This is called in the Muxer whenever the drivetrain command is obtained.
    /// @param state with all sensor information to properly define torque set points
    /// @return TorqueControllerOutput_s
    virtual TorqueControllerOutput_s evaluate(const SharedCarState_s &state) = 0;
};

#endif