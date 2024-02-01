#ifndef __TORQUECONTROLLERS_H__
#define __TORQUECONTROLLERS_H__

#include <Utility.h>
#include <DrivetrainSystem.h>
#include <PedalsSystem.h>
#include <SteeringSystem.h>
#include "AnalogSensorsInterface.h"
#include "DashboardInterface.h"

const float AMK_MAX_RPM = 20000.0;
const float AMK_MAX_TORQUE = 20.0; // TODO: update this with the true value
const float MAX_REGEN_TORQUE = 10.0;

enum TorqueController_e
{
    TC_NO_CONTROLLER = 0,
    TC_SAFE_MODE = 1,
    TC_NUM_CONTROLLERS = 2,
};

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

template <TorqueController_e TorqueControllerType>
class TorqueController
{
private:
public:
};

class TorqueControllerNone : public TorqueController<TC_NO_CONTROLLER>
{
private:
    DrivetrainCommand_s data_ = {
        .speeds = {0.0, 0.0, 0.0, 0.0},
        .posTorqueLimits = {0.0, 0.0, 0.0, 0.0},
        .negTorqueLimits = {0.0, 0.0, 0.0, 0.0}
    };
public:
    TorqueControllerNone(DrivetrainCommand_s& writeout)
    {
        writeout = data_;
    };
};

/// @brief Simple torque controller that only considers pedal inputs and torque limit
class TorqueControllerSimple : public TorqueController<TC_SAFE_MODE>
{
private:
    DrivetrainCommand_s& writeout_;
    DrivetrainCommand_s data_;
    float frontTorqueScale_;
    float rearTorqueScale_;
public:
    TorqueControllerSimple(DrivetrainCommand_s& writeout, float rearTorqueScale)
    : writeout_(writeout),
    rearTorqueScale_(rearTorqueScale) {}
    TorqueControllerSimple(DrivetrainCommand_s& writeout) : TorqueControllerSimple(writeout, 0.5) {}

    void tick(const SysTick_s& tick, const PedalsSystemData_s& pedalsData, float torqueLimit);
};

#endif /* __TORQUECONTROLLERS_H__ */
