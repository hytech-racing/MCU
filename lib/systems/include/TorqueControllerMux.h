#ifndef __TORQUECTRLMUX_H__
#define __TORQUECTRLMUX_H__

#include <TorqueControllers.h>
#include <DrivetrainSystem.h>
#include <PedalsSystem.h>
#include <SteeringSystem.h>
#include "DashboardInterface.h"
#include "AnalogSensorsInterface.h"

enum TorqueControllerMode_e
{
    TCMUX_NO_TORQUE = 0,
    TCMUX_SAFE_MODE = 1,
};

struct TorqueMuxSelectionData_e
{
    TorqueControllerMode_e muxMode;
    bool shiftAllowed; // is it safe to change mode?
};

class TorqueControllerMux
{
private:
    TorqueControllerMode_e muxMode_;
    DrivetrainCommand_s drivetrainCommand_;
public:
// Constructors
    TorqueControllerMux()
    {
        torqueCtrlMuxMode = TCMUX_NO_TORQUE;
    }
// Functions
    DrivetrainCommand_s calculateDrivetrainCommand(
        const DrivetrainDynamicReport_s &drivetrainData,
        const PedalsSystemData_s &pedalsData,
        const SteeringSystemData_s &steeringData,
        const DashboardInterface &dashboardData,
        const AnalogConversion_s &loadFLData,
        const AnalogConversion_s &loadFRData,
        const AnalogConversion_s &loadRLData,
        const AnalogConversion_s &loadRRData
    );
};

#endif /* __TORQUECTRLMUX_H__ */
