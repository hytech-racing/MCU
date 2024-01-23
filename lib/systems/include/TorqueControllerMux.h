#ifndef __TORQUECTRLMUX_H__
#define __TORQUECTRLMUX_H__

#include <TorqueControllers.h>
#include <DrivetrainSystem.h>
#include <PedalsSystem.h>
#include <SteeringSystem.h>
#include "DashboardInterface.h"
#include "AnalogSensor.h"

enum TorqueControllerMode_e
{
    TCMUX_NO_TORQUE = 0,
    TCMUX_SAFE_MODE = 1,
};

class TorqueControllerMux
{
private:
    TorqueControllerMode_e torqueCtrlMuxMode;
    DashboardInterface* dashboardInterface;
public:
// Constructors
    TorqueControllerMux()
    {
        torqueCtrlMuxMode = TCMUX_NO_TORQUE;
    }
// Functions
    DrivetrainCommand_s calculateDrivetrainCommand(
        DrivetrainDynamicReport_s* drivetrainData,
        PedalsSystemOutput_s* pedalsData,
        SteeringSystemOutput_s* steeringData,
        DashComponentInterface* dashboardData,
        AnalogConversion_s* loadFLData,
        AnalogConversion_s* loadFRData,
        AnalogConversion_s* loadRLData,
        AnalogConversion_s* loadRRData,
    );
};

#endif /* __TORQUECTRLMUX_H__ */
