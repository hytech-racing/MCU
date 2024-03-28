#ifndef __TORQUECTRLMUX_H__
#define __TORQUECTRLMUX_H__

#include <unordered_map>
#include "TorqueControllers.h"
#include "DrivetrainSystem.h"
#include "PedalsSystem.h"
#include "SteeringSystem.h"
#include "DashboardInterface.h"
// #include "AnalogSensorsInterface.h"

const float MAX_SPEED_FOR_MODE_CHANGE = 5.0;        // m/s
const float MAX_TORQUE_DELTA_FOR_MODE_CHANGE = 0.5; // Nm

/// @brief
class TorqueControllerMux
{
private:
    // Use this to map the dial to TCMUX modes
    std::unordered_map<DialMode_e, TorqueController_e> dialModeMap_ = {
        {DialMode_e::MODE_0, TorqueController_e::TC_SAFE_MODE},
        {DialMode_e::MODE_1, TorqueController_e::TC_SAFE_MODE},
        {DialMode_e::MODE_2, TorqueController_e::TC_LOAD_CELL_VECTORING},
        {DialMode_e::MODE_3, TorqueController_e::TC_PID_VECTORING},
        {DialMode_e::MODE_4, TorqueController_e::TC_NO_CONTROLLER},
        {DialMode_e::MODE_5, TorqueController_e::TC_NO_CONTROLLER},
    };
    std::unordered_map<TorqueLimit_e, float> torqueLimitMap_ = {
        {TorqueLimit_e::TCMUX_LOW_TORQUE, 10.0},
        {TorqueLimit_e::TCMUX_MID_TORQUE, 15.0},
        {TorqueLimit_e::TCMUX_FULL_TORQUE, 20.0}};
    TorqueControllerOutput_s controllerOutputs_[static_cast<int>(TorqueController_e::TC_NUM_CONTROLLERS)];
    TorqueControllerNone torqueControllerNone_;
    TorqueControllerSimple torqueControllerSimple_;
    TorqueControllerLoadCellVectoring torqueControllerLoadCellVectoring_;
    TorqueControllerPIDTV torqueControllerPIDTV_;
    TorqueController_e muxMode_ = TorqueController_e::TC_NO_CONTROLLER;
    DrivetrainCommand_s drivetrainCommand_;
    TorqueLimit_e torqueLimit_ = TorqueLimit_e::TCMUX_LOW_TORQUE;
    bool torqueLimitButtonPressed_ = false;
    unsigned long torqueLimitButtonPressedTime_ = 0;

public:
    /// @brief torque controller mux in which default instances of all torque controllers are created for use
    TorqueControllerMux()
        : torqueControllerNone_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_NO_CONTROLLER)]),
          torqueControllerSimple_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_SAFE_MODE)]),
          torqueControllerLoadCellVectoring_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_LOAD_CELL_VECTORING)]),
          torqueControllerPIDTV_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_PID_VECTORING)]) {}

    /// @brief torque controller mux constructor that leaves all other TCs with defaults accept for simple TC
    /// @param simpleTCRearTorqueScale the scaling from 0 to 2 in which 2 is full rear torque allocation, 0 is full front, 1 = balanced
    /// @param simpleTCRegenTorqueScale scaling from 0 to 2 in which 0 is full rear regen and 2 is full front regen, 1 = balanced
    TorqueControllerMux(float simpleTCRearTorqueScale, float simpleTCRegenTorqueScale)
        : torqueControllerNone_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_NO_CONTROLLER)]),
          torqueControllerSimple_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_SAFE_MODE)], simpleTCRearTorqueScale, simpleTCRegenTorqueScale),
          torqueControllerLoadCellVectoring_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_LOAD_CELL_VECTORING)]),
          torqueControllerPIDTV_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_PID_VECTORING)]) {}
    // Functions
    void tick(
        const SysTick_s &tick,
        const DrivetrainDynamicReport_s &drivetrainData,
        const PedalsSystemData_s &pedalsData,
        const SteeringSystemData_s &steeringData,
        const AnalogConversion_s &loadFLData,
        const AnalogConversion_s &loadFRData,
        const AnalogConversion_s &loadRLData,
        const AnalogConversion_s &loadRRData,
        DialMode_e dashboardDialMode,
        bool dashboardTorqueModeButtonPressed,
        float vx_b, 
        float wheel_angle_rad,
        float yaw_rate);
    const DrivetrainCommand_s &getDrivetrainCommand()
    {
        return drivetrainCommand_;
    };
    const TorqueLimit_e &getTorqueLimit()
    {
        return torqueLimit_;
    };
    const float getMaxTorque()
    {
        return torqueLimitMap_[torqueLimit_];
    }
};

#endif /* __TORQUECTRLMUX_H__ */
