#ifndef __TORQUECONTROLLERS_H__
#define __TORQUECONTROLLERS_H__

#include <Utility.h>
#include <DrivetrainSystem.h>
#include <PedalsSystem.h>
#include "AnalogSensorsInterface.h"
#include "DashboardInterface.h"
#include "PhysicalParameters.h"
#include "VectornavInterface.h"
#include "SteeringSystem.h"
#include "LoadCellInterface.h"

#include "accel_lookup.h"

#include "TorqueControllersData.h"


/* CONTROLLER CONSTANTS */

const float MAX_POWER_LIMIT = 63000.0; // max mechanical power limit in KW

/* MOTOR CONSTANTS */

const float AMK_MAX_RPM = 20000;
// 10MPH LIMIT for lot testing lmao
// const float AMK_MAX_RPM = (13.4 * METERS_PER_SECOND_TO_RPM); // 30mph
// const float AMK_MAX_RPM = (4.47 * METERS_PER_SECOND_TO_RPM); // 10mph
// const float AMK_MAX_RPM = (2.235 * METERS_PER_SECOND_TO_RPM); // 5mph
// const float AMK_MAX_RPM = (.89 * METERS_PER_SECOND_TO_RPM); // 1mph
// const float
const float AMK_MAX_TORQUE = 21.42;
const float MAX_REGEN_TORQUE = 10.0;

/* LAUNCH CONSTANTS */

const float DEFAULT_LAUNCH_RATE = 11.76;
const int16_t DEFAULT_LAUNCH_SPEED_TARGET = 1500;

const float DEFAULT_SLIP_RATIO = 0.2f;
const float const_accel_time = 100; // time to use launch speed target in ms

const float launch_ready_accel_threshold = .1;
const float launch_ready_brake_threshold = .2;
const float launch_ready_speed_threshold = 5.0 * METERS_PER_SECOND_TO_RPM; // rpm
const float launch_go_accel_threshold = .9;
const float launch_stop_accel_threshold = .5;

/* DRIVETRAIN STRUCTS */

const DrivetrainCommand_s TC_COMMAND_NO_TORQUE = {
    .speeds_rpm = {0.0, 0.0, 0.0, 0.0},
    .torqueSetpoints = {0.0, 0.0, 0.0, 0.0}};

struct TorqueControllerOutput_s
{
    DrivetrainCommand_s command;
    bool ready;
};

/* TC STRUCTS */
struct TCCaseWrapperTick_s
{
    const DrivetrainCommand_s &command;
    const SteeringSystemData_s &steeringData;
};

/* ENUMS */

enum TorqueController_e
{
    TC_NO_CONTROLLER = 0,
    TC_SAFE_MODE = 1,
    TC_LOAD_CELL_VECTORING = 2,
    TC_SIMPLE_LAUNCH = 3,
    TC_SLIP_LAUNCH = 4,
    TC_LOOKUP_LAUNCH = 5,
    TC_CASE_SYSTEM = 6,
    TC_NUM_CONTROLLERS = 7,
};

enum class LaunchStates_e
{
    NO_LAUNCH_MODE,
    LAUNCH_NOT_READY,
    LAUNCH_READY,
    LAUNCHING
};

/* TORQUE CONTROLLERS */

/*
    Base torque controller to allow access to internal torque controller members
*/
class TorqueControllerBase
{
public:
    /* returns the launch state for the purpose of lighting the dahsboard LED and unit testing. To be overridden in launch torque modes */
    virtual LaunchStates_e get_launch_state() { return LaunchStates_e::NO_LAUNCH_MODE; }
};

template <TorqueController_e TorqueControllerType>
class TorqueController : public TorqueControllerBase
{
protected:

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
    /// @brief simple TC with tunable F/R torque balance. Accel torque balance can be tuned independently of regen torque balance
    /// @param writeout the reference to the torque controller output being sent that contains the drivetrain command
    /// @param rearTorqueScale 0 to 2 scale on forward torque to rear wheels. 0 = FWD, 1 = Balanced, 2 = RWD
    /// @param regenTorqueScale same as rearTorqueScale but applies to regen torque split. 0 = All regen torque on the front, 1 = 50/50, 2 = all regen torque on the rear
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
    float frontRegenTorqueScale_ = 1.0;
    float rearRegenTorqueScale_ = 1.0;
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
    /// @brief load cell TC with tunable F/R torque balance. Accel torque balance can be tuned independently of regen torque balance
    /// @param writeout the reference to the torque controller output being sent that contains the drivetrain command
    /// @param rearTorqueScale 0 to 2 scale on forward torque to rear wheels. 0 = FWD, 1 = Balanced, 2 = RWD
    /// @param regenTorqueScale same as rearTorqueScale but applies to regen torque split. 0 = All regen torque on the front, 1 = 50/50, 2 = all regen torque on the rear
    TorqueControllerLoadCellVectoring(TorqueControllerOutput_s &writeout, float rearTorqueScale, float regenTorqueScale)
        : writeout_(writeout),
          frontTorqueScale_(2.0 - rearTorqueScale),
          rearTorqueScale_(rearTorqueScale),
          frontRegenTorqueScale_(2.0 - regenTorqueScale),
          rearRegenTorqueScale_(regenTorqueScale)
    {
        writeout_.command = TC_COMMAND_NO_TORQUE;
        writeout_.ready = false;
    }
    TorqueControllerLoadCellVectoring(TorqueControllerOutput_s &writeout) : TorqueControllerLoadCellVectoring(writeout, 1.0, 1.0) {}

    void tick(
        const SysTick_s &tick,
        const PedalsSystemData_s &pedalsData,
        float torqueLimit,
        const LoadCellInterfaceOutput_s &loadCellData
    );
};

class BaseLaunchController
{
protected:
    TorqueControllerOutput_s &writeout_;
    uint32_t time_of_launch_;
    double initial_ecef_x_;
    double initial_ecef_y_;
    double initial_ecef_z_;
    LaunchStates_e launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
    uint32_t current_millis_;
    float launch_speed_target_ = 0.0;
    int16_t init_speed_target_ = 0.0;
public:
    BaseLaunchController(TorqueControllerOutput_s &writeout, int16_t initial_speed_target)
        : writeout_(writeout),
          init_speed_target_(initial_speed_target)
    {
        writeout.command = TC_COMMAND_NO_TORQUE;
        writeout_.ready = true;
    }

    void tick(const SysTick_s &tick,
              const PedalsSystemData_s &pedalsData,
              const float wheel_rpms[],
              const vector_nav *vn_data);

    virtual void calc_launch_algo(const vector_nav *vn_data) = 0;
};

class TorqueControllerSimpleLaunch : public TorqueController<TC_SIMPLE_LAUNCH>, public BaseLaunchController
{
private:
    float launch_rate_target_;

public:
    /*!
        SIMPLE LAUNCH CONTROLLER
        This launch controller is based off of a specified launch rate and an initial speed target
        It will ramp up the speed target linearlly over time to accelerate
        @param launch_rate specified launch rate in m/s^2
        @param initial_speed_target the initial speed commanded to the wheels
    */
    TorqueControllerSimpleLaunch(TorqueControllerOutput_s &writeout, float launch_rate, int16_t initial_speed_target)
        : BaseLaunchController(writeout, initial_speed_target),
          launch_rate_target_(launch_rate) {}

    TorqueControllerSimpleLaunch(TorqueControllerOutput_s &writeout) : TorqueControllerSimpleLaunch(writeout, DEFAULT_LAUNCH_RATE, DEFAULT_LAUNCH_SPEED_TARGET) {}

    LaunchStates_e get_launch_state() override { return launch_state_; }

    void calc_launch_algo(const vector_nav *vn_data) override;
};

class TorqueControllerSlipLaunch : public TorqueController<TC_SLIP_LAUNCH>, public BaseLaunchController
{
private:
    float slip_ratio_;

public:
    /*!
        SLIP LAUNCH CONTROLLER
        This launch controller is based off of a specified slip constant. It will at all times attempt
        to keep the wheelspeed at this certain higher percent of the body velocity of the car to keep it
        in constant slip
        @param slip_ratio specified launch rate in m/s^2
        @param initial_speed_target the initial speed commanded to the wheels
    */
    TorqueControllerSlipLaunch(TorqueControllerOutput_s &writeout, float slip_ratio, int16_t initial_speed_target)
        : BaseLaunchController(writeout, initial_speed_target),
          slip_ratio_(slip_ratio) {}

    TorqueControllerSlipLaunch(TorqueControllerOutput_s &writeout) : TorqueControllerSlipLaunch(writeout, DEFAULT_SLIP_RATIO, DEFAULT_LAUNCH_SPEED_TARGET) {}

    LaunchStates_e get_launch_state() override { return launch_state_; }

    void calc_launch_algo(const vector_nav *vn_data) override;
};

class TorqueControllerLookupLaunch : public TorqueController<TC_LOOKUP_LAUNCH>, BaseLaunchController
{
private:
    bool init_position = false;

public:
    /*!
        Lookup Launch Controller
        This launch controller is based off of a matlab and symlink generated lookup table.
        This has been converted to a C array with some basic python code using the array index
        as the input for the controller
        @param slip_ratio specified launch rate in m/s^2
        @param initial_speed_target the initial speed commanded to the wheels
    */
    TorqueControllerLookupLaunch(TorqueControllerOutput_s &writeout, int16_t initial_speed_target)
        : BaseLaunchController(writeout, initial_speed_target) {}

    TorqueControllerLookupLaunch(TorqueControllerOutput_s &writeout) : TorqueControllerLookupLaunch(writeout, DEFAULT_LAUNCH_SPEED_TARGET) {}

    LaunchStates_e get_launch_state() override { return launch_state_; }

    void calc_launch_algo(const vector_nav *vn_data) override;
};

class TorqueControllerCASEWrapper : public TorqueController<TC_CASE_SYSTEM>
{
public:
    void tick(const TCCaseWrapperTick_s &intake);
    TorqueControllerCASEWrapper(TorqueControllerOutput_s &writeout) : writeout_(writeout)
    {
        writeout_ = writeout;
    }

private:
    TorqueControllerOutput_s &writeout_;
};

#endif /* __TORQUECONTROLLERS_H__ */
