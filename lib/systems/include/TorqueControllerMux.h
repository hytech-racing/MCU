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
#include "TelemetryInterface.h"

const float MAX_SPEED_FOR_MODE_CHANGE = 5.0;        // m/s
const float MAX_TORQUE_DELTA_FOR_MODE_CHANGE = 0.5; // Nm

/// @brief multiplexer class for managing available torque controllers
class TorqueControllerMux
{
private:
    TorqueControllerNone torqueControllerNone_;
    TorqueControllerSimple torqueControllerSimple_;
    TorqueControllerLoadCellVectoring torqueControllerLoadCellVectoring_;
    TorqueControllerSimpleLaunch torqueControllerSimpleLaunch_;
    TorqueControllerSlipLaunch torqueControllerSlipLaunch_;
    TorqueControllerCASEWrapper tcCASEWrapper_;

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

    TorqueController_e muxMode_ = TorqueController_e::TC_NO_CONTROLLER;
    DialMode_e currDialMode_ = DialMode_e::MODE_0;

    TorqueControllerOutput_s controllerOutputs_[static_cast<int>(TorqueController_e::TC_NUM_CONTROLLERS)];
    
    // Handle array for all torque controllers
    TorqueControllerBase* controllers[static_cast<int>(TorqueController_e::TC_NUM_CONTROLLERS)] = {
        static_cast<TorqueControllerBase*>(&torqueControllerNone_),
        static_cast<TorqueControllerBase*>(&torqueControllerSimple_),
        static_cast<TorqueControllerBase*>(&torqueControllerLoadCellVectoring_),
        static_cast<TorqueControllerBase*>(&torqueControllerSimpleLaunch_),
        static_cast<TorqueControllerBase*>(&torqueControllerSlipLaunch_),
        static_cast<TorqueControllerBase*>(&tcCASEWrapper_)
    };

    // Status tracking structure for visibility
    TCMuxStatus_s tcMuxStatus_;

    DrivetrainCommand_s drivetrainCommand_;
    TorqueLimit_e torqueLimit_ = TorqueLimit_e::TCMUX_FULL_TORQUE;
    bool torqueLimitButtonPressed_ = false;
    unsigned long torqueLimitButtonPressedTime_ = 0;
    TelemetryInterface *telemHandle_;

public:
    /// @brief torque controller mux in which default instances of all torque controllers are created for use
    TorqueControllerMux(TelemetryInterface *telemInterface)
    : torqueControllerNone_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_NO_CONTROLLER)])
    , torqueControllerSimple_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_SAFE_MODE)])
    , torqueControllerLoadCellVectoring_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_LOAD_CELL_VECTORING)])
    , torqueControllerSimpleLaunch_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_SIMPLE_LAUNCH)])
    , torqueControllerSlipLaunch_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_SLIP_LAUNCH)])
    , tcCASEWrapper_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_CASE_SYSTEM)])
    , telemHandle_(telemInterface) {}


    /// @brief torque controller mux constructor that leaves all other TCs with defaults accept for simple TC
    /// @param simpleTCRearTorqueScale the scaling from 0 to 2 in which 2 is full rear torque allocation, 0 is full front, 1 = balanced
    /// @param simpleTCRegenTorqueScale scaling from 0 to 2 in which 0 is full rear regen and 2 is full front regen, 1 = balanced
    TorqueControllerMux(float simpleTCRearTorqueScale, float simpleTCRegenTorqueScale, TelemetryInterface *telemInterface)
    : torqueControllerNone_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_NO_CONTROLLER)])
    , torqueControllerSimple_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_SAFE_MODE)], simpleTCRearTorqueScale, simpleTCRegenTorqueScale)
    , torqueControllerLoadCellVectoring_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_LOAD_CELL_VECTORING)], 1.0, simpleTCRegenTorqueScale)
    , torqueControllerSimpleLaunch_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_SIMPLE_LAUNCH)])
    , torqueControllerSlipLaunch_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_SLIP_LAUNCH)])
    , tcCASEWrapper_(controllerOutputs_[static_cast<int>(TorqueController_e::TC_CASE_SYSTEM)])
    , telemHandle_(telemInterface) {}

    // Functions
    /// @brief tick controllers to calculate drivetrain command
    void tick(
        const SysTick_s &tick,
        const DrivetrainDynamicReport_s &drivetrainData,
        const PedalsSystemData_s &pedalsData,
        const SteeringSystemData_s &steeringData,
        const LoadCellInterfaceOutput_s &loadCellData,
        DialMode_e dashboardDialMode,
        float accDerateFactor,
        bool dashboardTorqueModeButtonPressed,
        const vector_nav &vn_data, 
        const DrivetrainCommand_s &CASECommand
    );

    /// @brief apply corresponding limits on drivetrain command calculated by torque controller
    void applyRegenLimit(DrivetrainCommand_s* command, const DrivetrainDynamicReport_s* drivetrain);
    void applyTorqueLimit(DrivetrainCommand_s* command);
    void applyPowerLimit(DrivetrainCommand_s* command, const DrivetrainDynamicReport_s* drivetrain);
    void applyPosSpeedLimit(DrivetrainCommand_s* command);
    void applyDerate(DrivetrainCommand_s* command, float accDerateFactor);

    /// @brief GETTERS
    const DrivetrainCommand_s &getDrivetrainCommand()
    {
        return drivetrainCommand_;
    };
    
    const TorqueLimit_e getTorqueLimit()
    {
        return torqueLimit_;
    };

    const float getMaxTorque()
    {
        return torqueLimitMap_[torqueLimit_];
    }

    const DialMode_e getDialMode()
    {
        return currDialMode_;
    }

    const TorqueController_e getDriveMode()
    {
        return muxMode_;
    }
    

    TorqueControllerBase* activeController()
    {
        // check to make sure that there is actually a controller
        // at the muxMode_ idx
        if (controllers[muxMode_] != NULL) {
            return controllers[muxMode_];
        } else {
            return static_cast<TorqueControllerBase*>(&torqueControllerNone_);
        }
    }

    /// @brief report TCMux status through Telemetry via CAN
    void reportTCMuxStatus();
};

#endif /* __TORQUECTRLMUX_H__ */
