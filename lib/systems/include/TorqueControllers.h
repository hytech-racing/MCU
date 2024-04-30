#ifndef __TORQUECONTROLLERS_H__
#define __TORQUECONTROLLERS_H__

#include <Utility.h>
#include <DrivetrainSystem.h>
#include <PedalsSystem.h>
#include <SteeringSystem.h>
#include "AnalogSensorsInterface.h"
#include "DashboardInterface.h"
#include "PhysicalParameters.h"
#include "VectornavInterface.h"
#include "SteeringSystem.h"
#include "LoadCellInterface.h"
#include "HytechCANInterface.h"

#include "accel_lookup.h"

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
    .torqueSetpoints = {0.0, 0.0, 0.0, 0.0}
};

struct TorqueControllerInput_s
{
    const SysTick_s &tick;
    const PedalsSystemData_s &pedals;
    const vector_nav &vn;
    const SteeringSystemData_s &steering;
    const LoadCellInterfaceOutput_s &lc;
    const DrivetrainDynamicReport_s &drivetrain;
    const float &torqueLimit;
};

struct TorqueControllerOutput_s
{
    DrivetrainCommand_s command;
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

enum class ControllerStates_e
{
    NOT_READY,
    READY,
    ACTIVE,
    SLEEPING
};

/* TORQUE CONTROLLERS */

/*
    Base torque controller class
*/
class TorqueController
{
protected:
    bool ready = false;
    bool active = false;
    TorqueControllerOutput_s writeout_ = {.command = TC_COMMAND_NO_TORQUE};

public:
    // constructor is needed here for the use of maps in the mux
    // if there is no constructor in the base class, it will complain
    // that it cannot construct an object for the map if it doesn't exist
    TorqueController() {}
    /* writeout getter that returns a torque controller's drivetrain command*/
    virtual TorqueControllerOutput_s writeout() const { return writeout_; }

    /* getter that returns the controller's readiness */
    bool is_ready() const { return ready; }
    /* getter that returns the controller's activeness */
    bool is_active() const { return active; }

    /* set the controller as active */
    void activate() {if (ready) active = true; }

    /* set the controller as inactive */
    void deactivate() { active = false; }

    /* returns the launch state for the purpose of lighting the dahsboard LED and unit testing. To be overridden in launch torque modes */
    virtual LaunchStates_e get_launch_state() const { return LaunchStates_e::NO_LAUNCH_MODE; }

    float get_torque_request(const PedalsSystemData_s &pedals, const float &torqueLimit)
    {
        float accelRequest = pedals.accelPercent - pedals.regenPercent;
        float torqueRequest = 0.0;

        if (accelRequest >= 0.0)
        {
            torqueRequest = accelRequest * torqueLimit;
        } else
        {
            torqueRequest = std::min(torqueLimit, MAX_REGEN_TORQUE) * accelRequest;
        }

        return torqueRequest;
    }

    virtual void tick(const TorqueControllerInput_s &in) { return; }
};

class TorqueControllerNone : public TorqueController
{
private:
public:
    TorqueControllerNone()
    {
        ready = true;
    }
};

/// @brief Simple torque controller that only considers pedal inputs and torque limit
class TorqueControllerSimple : public TorqueController
{
private:
    float frontTorqueScale_ = 1.0;
    float rearTorqueScale_ = 1.0;
    float frontRegenTorqueScale_ = 1.0;
    float rearRegenTorqueScale_ = 1.0;

public:
    /// @brief simple TC with tunable F/R torque balance. Accel torque balance can be tuned independently of regen torque balance
    /// @param writeout the reference to the torque controller output being sent that contains the drivetrain command
    /// @param rearTorqueScale 0 to 2 scale on forward torque to rear wheels. 0 = FWD, 1 = Balanced, 2 = RWD
    /// @param regenTorqueScale same as rearTorqueScale but applies to regen torque split. 0 = All regen torque on the front, 1 = 50/50, 2 = all regen torque on the rear
    TorqueControllerSimple( float rearTorqueScale, float regenTorqueScale)
        : frontTorqueScale_(2.0 - rearTorqueScale),
          rearTorqueScale_(rearTorqueScale),
          frontRegenTorqueScale_(2.0 - regenTorqueScale),
          rearRegenTorqueScale_(regenTorqueScale)
          {
            ready = true;
          }

    TorqueControllerSimple() : TorqueControllerSimple(1.0, 1.0) {}

    void tick(const TorqueControllerInput_s &in) override;
};

class TorqueControllerLoadCellVectoring : public TorqueController
{
private:
    float frontTorqueScale_ = 1.0;
    float rearTorqueScale_ = 1.0;
    float frontRegenTorqueScale_ = 1.0;
    float rearRegenTorqueScale_ = 1.0;
    // /*
    // FIR filter designed with
    // http://t-filter.appspot.com

    // sampling frequency: 100 Hz

    // * 0 Hz - 10 Hz
    // gain = 1
    // desired ripple = 5 dB
    // actual ripple = 1.7659949026015025 dB

    // * 40 Hz - 50 Hz
    // gain = 0
    // desired attenuation = -40 dB
    // actual attenuation = -47.34009380570117 dB
    // */
    // const static int numFIRTaps_ = 5;
    // float FIRTaps_[numFIRTaps_] = {
    //     0.07022690881526232,
    //     0.27638313122745306,
    //     0.408090001549378,
    //     0.27638313122745306,
    //     0.07022690881526232};
    // int FIRCircBufferHead = 0; // index of the latest sample in the raw buffer
    // float loadCellForcesRaw_[4][numFIRTaps_] = {};
    // float loadCellForcesFiltered_[4] = {};
    // // Some checks that can disable the controller
    // const int errorCountThreshold_ = 25;
    // int loadCellsErrorCounter_[4] = {};
    // bool FIRSaturated_ = false;
    // bool ready_ = false;

public:
    /// @brief load cell TC with tunable F/R torque balance. Accel torque balance can be tuned independently of regen torque balance
    /// @param rearTorqueScale 0 to 2 scale on forward torque to rear wheels. 0 = FWD, 1 = Balanced, 2 = RWD
    /// @param regenTorqueScale same as rearTorqueScale but applies to regen torque split. 0 = All regen torque on the front, 1 = 50/50, 2 = all regen torque on the rear
    TorqueControllerLoadCellVectoring(float rearTorqueScale, float regenTorqueScale)
        : frontTorqueScale_(2.0 - rearTorqueScale),
          rearTorqueScale_(rearTorqueScale),
          frontRegenTorqueScale_(2.0 - regenTorqueScale),
          rearRegenTorqueScale_(regenTorqueScale) {}
    TorqueControllerLoadCellVectoring() : TorqueControllerLoadCellVectoring(1.0, 1.0) {}

    void tick(const TorqueControllerInput_s &in) override;
};

class BaseLaunchController : public TorqueController
{
protected:
    uint32_t time_of_launch_;
    double initial_ecef_x_;
    double initial_ecef_y_;
    double initial_ecef_z_;
    LaunchStates_e launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
    uint32_t current_millis_;
    float launch_speed_target_ = 0.0;
    int16_t init_speed_target_ = 0.0;
public:
    BaseLaunchController(int16_t initial_speed_target)
        : init_speed_target_(initial_speed_target) {}

    void tick(const TorqueControllerInput_s &in) override;

    virtual void calc_launch_algo(const vector_nav &vn_data) = 0;
};

class TorqueControllerSimpleLaunch : public BaseLaunchController
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
    TorqueControllerSimpleLaunch(float launch_rate, int16_t initial_speed_target)
        : BaseLaunchController(initial_speed_target),
          launch_rate_target_(launch_rate)
          {
            ready = true;
          }

    TorqueControllerSimpleLaunch() : TorqueControllerSimpleLaunch(DEFAULT_LAUNCH_RATE, DEFAULT_LAUNCH_SPEED_TARGET) {}

    LaunchStates_e get_launch_state() const override { return launch_state_; }

    void calc_launch_algo(const vector_nav &vn_data) override;
};

class TorqueControllerSlipLaunch : public BaseLaunchController
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
    TorqueControllerSlipLaunch(float slip_ratio, int16_t initial_speed_target)
        : BaseLaunchController(initial_speed_target),
          slip_ratio_(slip_ratio)
          {
            ready = true;
          }

    TorqueControllerSlipLaunch() : TorqueControllerSlipLaunch(DEFAULT_SLIP_RATIO, DEFAULT_LAUNCH_SPEED_TARGET) {}

    LaunchStates_e get_launch_state() const override { return launch_state_; }

    void calc_launch_algo(const vector_nav &vn_data) override;
};

class TorqueControllerLookupLaunch : public BaseLaunchController
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
    TorqueControllerLookupLaunch(int16_t initial_speed_target)
        : BaseLaunchController(initial_speed_target)
        {
            ready = true;
        }

    TorqueControllerLookupLaunch() : TorqueControllerLookupLaunch(DEFAULT_LAUNCH_SPEED_TARGET) {}

    LaunchStates_e get_launch_state() const override { return launch_state_; }

    void calc_launch_algo(const vector_nav &vn_data) override;
};

#endif /* __TORQUECONTROLLERS_H__ */
