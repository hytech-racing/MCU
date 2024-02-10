#ifndef __TORQUECTRLMUX_H__
#define __TORQUECTRLMUX_H__

#include <unordered_map>
#include "TorqueControllers.h"
#include "DrivetrainSystem.h"
#include "PedalsSystem.h"
#include "SteeringSystem.h"
#include "DashboardInterface.h"
// #include "AnalogSensorsInterface.h"

const float maxSpeedForModeChange = 5.0; // m/s
const float maxTorqueDeltaForModeChange = 0.5; // Nm

enum class TorqueLimit_e
{
    TCMUX_LOW_TORQUE = 0,
    TCMUX_MID_TORQUE = 1,
    TCMUX_FULL_TORQUE = 2,
    TCMUX_NUM_TORQUE_LIMITS = 3,
};

class TorqueControllerMux
{
private:
    // Use this to map the dial to TCMUX modes
    std::unordered_map<DialMode_e, TorqueController_e> dialModeMap_ = {
        {DialMode_e::MODE_1, TC_SAFE_MODE},
        {DialMode_e::MODE_2, TC_SAFE_MODE},
        {DialMode_e::ACCEL_LAUNCH_CONTROL, TC_NO_CONTROLLER},
        {DialMode_e::SKIDPAD, TC_NO_CONTROLLER},
        {DialMode_e::AUTOCROSS, TC_NO_CONTROLLER},
        {DialMode_e::ENDURANCE, TC_NO_CONTROLLER},
    };
    std::unordered_map<TorqueLimit_e, float> torqueLimitMap_ = {
        {TorqueLimit_e::TCMUX_LOW_TORQUE, 10.0},
        {TorqueLimit_e::TCMUX_MID_TORQUE, 15.0},
        {TorqueLimit_e::TCMUX_FULL_TORQUE, 20.0}
    };
    DrivetrainCommand_s controllerCommands_[static_cast<int>(TC_NUM_CONTROLLERS)];
    TorqueControllerNone torqueControllerNone_;
    TorqueControllerSimple torqueControllerSimple_;
    TorqueController_e muxMode_;
    DrivetrainCommand_s drivetrainCommand_;
    TorqueLimit_e torqueLimit_;
    bool torqueLimitButtonPressed_;
    unsigned long torqueLimitButtonPressedTime_;
public:
// Constructors
    TorqueControllerMux()
    : torqueControllerNone_(controllerCommands_[static_cast<int>(TC_NO_CONTROLLER)])
    , torqueControllerSimple_(controllerCommands_[static_cast<int>(TC_SAFE_MODE)])
    {
        muxMode_ = TC_NO_CONTROLLER;
        torqueLimit_ = TorqueLimit_e::TCMUX_LOW_TORQUE;
    }
// Functions
    void tick(
        const SysTick_s& tick,
        const DrivetrainDynamicReport_s& drivetrainData,
        const PedalsSystemData_s& pedalsData,
        const SteeringSystemData_s& steeringData,
        const AnalogConversion_s& loadFLData,
        const AnalogConversion_s& loadFRData,
        const AnalogConversion_s& loadRLData,
        const AnalogConversion_s& loadRRData,
        DialMode_e dashboardDialMode,
        bool dashboardTorqueModeButtonPressed
    );
    const DrivetrainCommand_s& getDrivetrainCommand()
    {
        return drivetrainCommand_;
    };
    const TorqueLimit_e& getTorqueLimit()
    {
        return torqueLimit_;
    };
    const float getMaxTorque()
    {
        return torqueLimitMap_[torqueLimit_];
    }
};

#endif /* __TORQUECTRLMUX_H__ */
