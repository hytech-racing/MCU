#ifndef __TORQUECONTROLLERS_H__
#define __TORQUECONTROLLERS_H__

#include <Utility.h>
#include <DrivetrainSystem.h>
#include <PedalsSystem.h>
#include <SteeringSystem.h>
#include "AnalogSensorsInterface.h"
#include "DashboardInterface.h"
#include "PhysicalParameters.h"

#include "PID_TV.h"

const float AMK_MAX_RPM = 20000;
// 10MPH LIMIT for lot testing lmao
// const float AMK_MAX_RPM = (13.4 * METERS_PER_SECOND_TO_RPM); // 30mph
// const float AMK_MAX_RPM = (4.47 * METERS_PER_SECOND_TO_RPM); // 10mph
// const float AMK_MAX_RPM = (2.235 * METERS_PER_SECOND_TO_RPM); // 5mph
// const float AMK_MAX_RPM = (.89 * METERS_PER_SECOND_TO_RPM); // 1mph
// const float
const float AMK_MAX_TORQUE = 20.0; // TODO: update this with the true value
const float MAX_REGEN_TORQUE = 10.0;

const DrivetrainCommand_s TC_COMMAND_NO_TORQUE = {
    .speeds_rpm = {0.0, 0.0, 0.0, 0.0},
    .torqueSetpoints = {0.0, 0.0, 0.0, 0.0}};

struct TorqueControllerOutput_s
{
    DrivetrainCommand_s command;
    bool ready;
};

enum TorqueController_e
{
    TC_NO_CONTROLLER = 0,
    TC_SAFE_MODE = 1,
    TC_LOAD_CELL_VECTORING = 2,
    TC_PID_VECTORING = 3,
    TC_NUM_CONTROLLERS = 4,
};

/// @brief If a command fed through this function exceeds the specified power limit, all torques will be scaled down equally
/// @param command
/// @param drivetrainData
/// @param powerLimit In watts, not kilowatts
/// @param
/// @return A scaled down DrivetrainCommand_s
static DrivetrainCommand_s TCPowerLimitScaleDown(
    DrivetrainCommand_s command,
    DrivetrainDynamicReport_s *drivetrainData,
    float powerLimit);

/// @brief Apply a per-wheel torque limit
/// @param command
/// @param torqueLimits
/// @param
/// @return A torque-limited DrivetrainCommand_s
static DrivetrainCommand_s TCTorqueLimit(
    DrivetrainCommand_s command,
    float torqueLimits[NUM_MOTORS]);

template <TorqueController_e TorqueControllerType>
class TorqueController
{
protected:

    void TCPowerLimitScaleDown(
        DrivetrainCommand_s &command,
        const DrivetrainDynamicReport_s &drivetrainData,
        float powerLimit)
    {
        // TODO
        // probably requires AMS interface
    }
    void TCPosTorqueLimit(DrivetrainCommand_s &command, float torqueLimit)
    {
        for (int i = 0; i < NUM_MOTORS; i++)
        {
            command.torqueSetpoints[i] = std::min(command.torqueSetpoints[i], torqueLimit);
        }
    }

public:
};

class TorqueControllerNone : public TorqueController<TC_NO_CONTROLLER>
{
private:
public:
    TorqueControllerNone(TorqueControllerOutput_s &writeout)
    {
        writeout.command = TC_COMMAND_NO_TORQUE;
        writeout.ready = true;
    };
};

/// @brief Simple torque controller that only considers pedal inputs and torque limit
class TorqueControllerSimple : public TorqueController<TC_SAFE_MODE>
{
private:
    TorqueControllerOutput_s &writeout_;
    float frontTorqueScale_ = 1.0;
    float rearTorqueScale_ = 1.0;
    float frontRegenTorqueScale_ = 1.0;
    float rearRegenTorqueScale_ = 1.0;

public:
    /// @brief simple TC in which a scaling can be applied to both regen and accel torques for scaling accel request (accel percent - regen percent)
    /// @param writeout the reference to the torque controller output being sent that contains the drivetrain command
    /// @param rearTorqueScale the 0 to 2 scaling with which 0 represents 200 percent of the accel percent with which to request torque from front wheels, 2 being vice versa to the rear and 1 being balanced.
    /// @param regenTorqueScale same as rearTorqueScale, accept applied to negative accel percents which correspond to regen

    TorqueControllerSimple(TorqueControllerOutput_s &writeout, float rearTorqueScale, float regenTorqueScale)
        : writeout_(writeout),
          frontTorqueScale_(2.0 - rearTorqueScale),
          rearTorqueScale_(rearTorqueScale),
          frontRegenTorqueScale_(2.0 - regenTorqueScale),
          rearRegenTorqueScale_(regenTorqueScale)
    {
        writeout_.command = TC_COMMAND_NO_TORQUE;
        writeout_.ready = true;
    }
    TorqueControllerSimple(TorqueControllerOutput_s &writeout) : TorqueControllerSimple(writeout, 1.0, 1.0) {}

    void tick(const SysTick_s &tick, const PedalsSystemData_s &pedalsData, float torqueLimit);
};

class TorqueControllerLoadCellVectoring : public TorqueController<TC_LOAD_CELL_VECTORING>
{
private:
    TorqueControllerOutput_s &writeout_;
    float frontTorqueScale_ = 1.0;
    float rearTorqueScale_ = 1.0;
    /*
    FIR filter designed with
    http://t-filter.appspot.com

    sampling frequency: 100 Hz

    * 0 Hz - 10 Hz
    gain = 1
    desired ripple = 5 dB
    actual ripple = 1.7659949026015025 dB

    * 40 Hz - 50 Hz
    gain = 0
    desired attenuation = -40 dB
    actual attenuation = -47.34009380570117 dB
    */
    const static int numFIRTaps_ = 5;
    float FIRTaps_[numFIRTaps_] = {
        0.07022690881526232,
        0.27638313122745306,
        0.408090001549378,
        0.27638313122745306,
        0.07022690881526232};
    int FIRCircBufferHead = 0; // index of the latest sample in the raw buffer
    float loadCellForcesRaw_[4][numFIRTaps_] = {};
    float loadCellForcesFiltered_[4] = {};
    // Some checks that can disable the controller
    const int errorCountThreshold_ = 25;
    int loadCellsErrorCounter_[4] = {};
    bool FIRSaturated_ = false;
    bool ready_ = false;

public:
    TorqueControllerLoadCellVectoring(TorqueControllerOutput_s &writeout, float rearTorqueScale)
        : writeout_(writeout),
          frontTorqueScale_(2.0 - rearTorqueScale),
          rearTorqueScale_(rearTorqueScale)
    {
        writeout_.command = TC_COMMAND_NO_TORQUE;
        writeout_.ready = false;
    }
    TorqueControllerLoadCellVectoring(TorqueControllerOutput_s &writeout) : TorqueControllerLoadCellVectoring(writeout, 1.0) {}

    void tick(
        const SysTick_s &tick,
        const PedalsSystemData_s &pedalsData,
        float torqueLimit,
        const AnalogConversion_s &flLoadCellData,
        const AnalogConversion_s &frLoadCellData,
        const AnalogConversion_s &rlLoadCellData,
        const AnalogConversion_s &rrLoadCellData);
};

class TorqueControllerPIDTV: public TorqueController<TC_PID_VECTORING>
{
public: 
    void tick(const SysTick_s &tick, const PedalsSystemData_s &pedalsData, float vx_b, float wheel_angle_rad, float yaw_rate);
    TorqueControllerPIDTV(TorqueControllerOutput_s &writeout): writeout_(writeout)
    {
        tv_pid_.initialize();
        tv_pid_.setExternalInputs(&pid_input_);
        pid_input_.PID_P = 3.0;
        pid_input_.PID_I = 1.0;
        pid_input_.PID_D = 0.0;
        pid_input_.PID_N = 100;
    }
private:
    TorqueControllerOutput_s &writeout_;
    
    PID_TV::ExtU_PID_TV_T pid_input_;
    PID_TV tv_pid_;
};
#endif /* __TORQUECONTROLLERS_H__ */
