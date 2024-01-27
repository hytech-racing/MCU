#ifndef __TORQUECONTROLLERS_H__
#define __TORQUECONTROLLERS_H__

#include <Utility.h>
#include <DrivetrainSystem.h>
#include <PedalsSystem.h>
#include "DashboardInterface.h"

const float AMK_MAX_RPM = 20000.0;
const float AMK_MAX_TORQUE = 20.0; // TODO: update this with the true value
const float MAX_REGEN_TORQUE = 10.0;

/// @brief If a command fed through this function exceeds the specified power limit, all torques will be scaled down equally
/// @param command 
/// @param drivetrainData 
/// @param powerLimit In watts, not kilowatts
/// @param  
/// @return A scaled down DrivetrainCommand_s
static DrivetrainCommand_s TCPowerLimitScaleDown(
    DrivetrainCommand_s command,
    DrivetrainDynamicReport_s* drivetrainData,
    float powerLimit
);

/// @brief Apply a per-wheel torque limit
/// @param command 
/// @param torqueLimits 
/// @param  
/// @return A torque-limited DrivetrainCommand_s
static DrivetrainCommand_s TCTorqueLimit(
    DrivetrainCommand_s command,
    float torqueLimits[NUM_MOTORS]
);

/// @brief Simple torque controller that only considers pedal inputs and torque limit
class TorqueControllerSimple
{
private:
    DrivetrainCommand_s data_;
    float frontTorqueScale_;
    float rearTorqueScale_;
public:
    TorqueControllerSimple(float rearTorqueScale) : rearTorqueScale_(rearTorqueScale) {}
    TorqueControllerSimple() : TorqueControllerSimple(0.5) {}

    void tick(
        const SysTick_s &tick,
        const PedalsSystemData_s &pedalsData,
        const DashboardInterfaceOutput_s &dashboardData
    );

    const DrivetrainCommand_s& getDrivetrainCommand(){
        return data_;
    }
};

#endif /* __TORQUECONTROLLERS_H__ */
