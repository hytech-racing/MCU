#ifndef BASECONTROLLER
#define BASECONTROLLER
#include "SharedDataTypes.h"

/// @brief defines namespace for definition of a drivetrain command with no torque for clearer code in the Muxer
/// This can be used to define other specific car states in the future
namespace BaseControllerParams
{
    const DrivetrainCommand_s TC_COMMAND_NO_TORQUE = {
        .speeds_rpm = {0.0, 0.0, 0.0, 0.0},
        .inverter_torque_limit = {0.0, 0.0, 0.0, 0.0}};

}
 /// @brief Base class for all controllers, which define drivetrain command containing different variations of 
/// speed set points and necessary torque set points to be requested from the motors in order to achieve said speeds.
 /// required method(s): evaluate
class Controller
{
public:
    /// @brief This mehod must be implemented by every controller in the Tc Muxer. This is called in the Muxer whenever the drivetrain command is obtained.
    /// @ref TorqueControllerMux.cpp to see that in every tick of the system, the active controller must be ticked through this method
    /// @param state with all sensor information to properly define torque set points
    /// @return TorqueControllerOutput_s This is a Drivetrain command passed along with a state boolean to ensure car controllers are working properly
    virtual TorqueControllerOutput_s evaluate(const SharedCarState_s &state) = 0;
};

#endif