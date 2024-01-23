#ifndef __TORQUECONTROLLERS_H__
#define __TORQUECONTROLLERS_H__

#include <Utility.h>
#include <DrivetrainSystem.h>
#include <PedalsSystem.h>
#include "DashboardInterface.h"

/// @brief If a command fed through this function exceeds the specified power limit, all torques will be scaled down equally
/// @param command 
/// @param drivetrainData 
/// @param powerLimit In watts, not kilowatts
/// @param  
/// @return A scaled down DrivetrainCommand_s
static DrivetrainCommand_s TCPowerLimitScaleDown(
    DrivetrainCommand_s command,
    DrivetrainDynamicReport_s* drivetrainData,
    float powerLimit,
);

/// @brief Apply a per-wheel torque limit
/// @param command 
/// @param torqueLimits 
/// @param  
/// @return A torque-limited DrivetrainCommand_s
static DrivetrainCommand_s TCTorqueLimit(
    DrivetrainCommand_s command,
    float torqueLimits[NUM_MOTORS],
);

/// @brief Never commands torque
class TCNone
{
private:
public:
    DrivetrainCommand_s evaluate();
};

/// @brief Simple torque controller that only considers pedal inputs
class TorqueControllerSimple
{
private:
public:
    DrivetrainCommand_s evaluate(PedalsSystemOutput_s* pedalsData);
};

#endif /* __TORQUECONTROLLERS_H__ */
