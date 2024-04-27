#ifndef __TORQUECTRLMUX_H__
#define __TORQUECTRLMUX_H__

#include <unordered_map>
#include <cmath>

#include "TorqueControllers.h"
#include "DrivetrainSystem.h"
#include "PedalsSystem.h"
#include "SteeringSystem.h"
#include "DashboardInterface.h"
#include "VectornavInterface.h"
#include "LoadCellInterface.h"

const float MAX_SPEED_FOR_MODE_CHANGE = 5.0;        // m/s
const float MAX_TORQUE_DELTA_FOR_MODE_CHANGE = 0.5; // Nm

/// @brief
class TorqueControllerMux
{
private:
    TorqueControllerNone torqueControllerNone_;
    TorqueControllerSimple torqueControllerSimple_;
    TorqueControllerLoadCellVectoring torqueControllerLoadCellVectoring_;
    TorqueControllerSimpleLaunch torqueControllerSimpleLaunch_;
    TorqueControllerSlipLaunch torqueControllerSlipLaunch_;

    // Use this to map the dial to TCMUX modes
    std::unordered_map<DialMode_e, TorqueController_e> dialModeMap_ = {
        {DialMode_e::MODE_0, TorqueController_e::TC_SAFE_MODE},
        {DialMode_e::MODE_1, TorqueController_e::TC_LOAD_CELL_VECTORING},
        {DialMode_e::MODE_2, TorqueController_e::TC_CASE_SYSTEM},
        {DialMode_e::MODE_3, TorqueController_e::TC_SIMPLE_LAUNCH},
        {DialMode_e::MODE_4, TorqueController_e::TC_SLIP_LAUNCH},
        {DialMode_e::MODE_5, TorqueController_e::TC_NO_CONTROLLER},
    };
    std::unordered_map<TorqueLimit_e, float> torqueLimitMap_ = {
        {TorqueLimit_e::TCMUX_LOW_TORQUE, 10.0},
        {TorqueLimit_e::TCMUX_MID_TORQUE, 15.0},
        {TorqueLimit_e::TCMUX_FULL_TORQUE, AMK_MAX_TORQUE}
    };

    std::unordered_map<TorqueController_e, TorqueController> controllerMap_;

    TorqueController_e muxMode_ = TorqueController_e::TC_NO_CONTROLLER;
    DialMode_e cur_dial_mode_ = DialMode_e::MODE_0;

    DrivetrainCommand_s drivetrainCommand_;
    TorqueLimit_e torqueLimit_ = TorqueLimit_e::TCMUX_LOW_TORQUE;
    bool torqueLimitButtonPressed_ = false;
    unsigned long torqueLimitButtonPressedTime_ = 0;

public:
    /// @brief torque controller mux in which default instances of all torque controllers are created for use
    TorqueControllerMux()
    : torqueControllerNone_()
    , torqueControllerSimple_()
    , torqueControllerLoadCellVectoring_()
    , torqueControllerSimpleLaunch_()
    , torqueControllerSlipLaunch_()
    {
        controllerMap_[TorqueController_e::TC_NO_CONTROLLER] = torqueControllerNone_;
        controllerMap_[TorqueController_e::TC_SAFE_MODE] = torqueControllerSimple_;
        controllerMap_[TorqueController_e::TC_LOAD_CELL_VECTORING] = torqueControllerLoadCellVectoring_;
        controllerMap_[TorqueController_e::TC_SIMPLE_LAUNCH] = torqueControllerSimpleLaunch_;
        controllerMap_[TorqueController_e::TC_SLIP_LAUNCH] = torqueControllerSlipLaunch_;
    }


    /// @brief torque controller mux constructor that leaves all other TCs with defaults accept for simple TC
    /// @param simpleTCRearTorqueScale the scaling from 0 to 2 in which 2 is full rear torque allocation, 0 is full front, 1 = balanced
    /// @param simpleTCRegenTorqueScale scaling from 0 to 2 in which 0 is full rear regen and 2 is full front regen, 1 = balanced
    TorqueControllerMux(float simpleTCRearTorqueScale, float simpleTCRegenTorqueScale)
    : torqueControllerNone_()
    , torqueControllerSimple_(simpleTCRearTorqueScale, simpleTCRegenTorqueScale)
    , torqueControllerLoadCellVectoring_(1.0, simpleTCRegenTorqueScale)
    , torqueControllerSimpleLaunch_()
    , torqueControllerSlipLaunch_()
    {
        controllerMap_[TorqueController_e::TC_NO_CONTROLLER] = torqueControllerNone_;
        controllerMap_[TorqueController_e::TC_SAFE_MODE] = torqueControllerSimple_;
        controllerMap_[TorqueController_e::TC_LOAD_CELL_VECTORING] = torqueControllerLoadCellVectoring_;
        controllerMap_[TorqueController_e::TC_SIMPLE_LAUNCH] = torqueControllerSimpleLaunch_;
        controllerMap_[TorqueController_e::TC_SLIP_LAUNCH] = torqueControllerSlipLaunch_;
    }
// Functions
    void tick(
        const SysTick_s &tick,
        const DrivetrainDynamicReport_s &drivetrainData,
        const PedalsSystemData_s &pedalsData,
        const SteeringSystemData_s &steeringData,
        const LoadCellInterfaceOutput_s &loadCellData,
        DialMode_e dashboardDialMode,
        bool dashboardTorqueModeButtonPressed,
        const vector_nav &vn_data, 
        const DrivetrainCommand_s &CASECommand
    );
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

    void applyRegenLimit(DrivetrainCommand_s* command, const DrivetrainDynamicReport_s* drivetrain);

    void applyTorqueLimit(DrivetrainCommand_s* command);

    void applyPowerLimit(DrivetrainCommand_s* command, const DrivetrainDynamicReport_s* drivetrain);

    void applyPosSpeedLimit(DrivetrainCommand_s* command);



    const DialMode_e getDialMode()
    {
        return cur_dial_mode_;
    }

    const TorqueController_e getDriveMode()
    {
        return muxMode_;
    }

    const TorqueController& activeController()
    {
        return controllerMap_[muxMode_];
    }
};

#endif /* __TORQUECTRLMUX_H__ */
