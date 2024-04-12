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

#include "accel_lookup.h"

#include "TorqueControllersData.h"
#include "PID_TV.h"
#ifndef M_PI 
#define M_PI 3.141592653589
#endif
/* MOTOR CONSTANTS */

const float AMK_MAX_RPM = 20000;
// 10MPH LIMIT for lot testing lmao
// const float AMK_MAX_RPM = (13.4 * METERS_PER_SECOND_TO_RPM); // 30mph
// const float AMK_MAX_RPM = (4.47 * METERS_PER_SECOND_TO_RPM); // 10mph
// const float AMK_MAX_RPM = (2.235 * METERS_PER_SECOND_TO_RPM); // 5mph
// const float AMK_MAX_RPM = (.89 * METERS_PER_SECOND_TO_RPM); // 1mph
// const float
const float AMK_MAX_TORQUE = 21.42; // TODO: update this with the true value
const float MAX_REGEN_TORQUE = 10.0;

/* LAUNCH CONSTANTS */

const float DEFAULT_LAUNCH_RATE = 11.76;
const int16_t DEFAULT_LAUNCH_SPEED_TARGET = 1500;

const float DEFAULT_SLIP_RATIO = 0.2f;
const float const_accel_time = 1500; // time to use launch speed target in ms

const float launch_ready_accel_threshold = .1;
const float launch_ready_brake_threshold = .2;
const float launch_ready_speed_threshold = 5.0 * METERS_PER_SECOND_TO_RPM; // rpm
const float launch_go_accel_threshold = .9;
const float launch_stop_accel_threshold = .5;

constexpr double EARTH_RADIUS_KM = 6371.0;
constexpr double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

/* DRIVETRAIN STRUCTS */

const DrivetrainCommand_s TC_COMMAND_NO_TORQUE = {
    .speeds_rpm = {0.0, 0.0, 0.0, 0.0},
    .torqueSetpoints = {0.0, 0.0, 0.0, 0.0}};

struct TorqueControllerOutput_s
{
    DrivetrainCommand_s command;
    bool ready;
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
    TC_PID_VECTORING = 6,
    TC_NUM_CONTROLLERS = 7,
};

enum class LaunchStates_e
{
    NO_LAUNCH_MODE,
    LAUNCH_NOT_READY,
    LAUNCH_READY,
    LAUNCHING
};

/* CONTROLLER FUNCTIONS */

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

class BaseLaunchController
{
protected:
    TorqueControllerOutput_s &writeout_;

    uint32_t time_of_launch;

    double initial_ecef_x;
    double initial_ecef_y;
    double initial_ecef_z;

    LaunchStates_e launch_state = LaunchStates_e::LAUNCH_NOT_READY;
    uint32_t current_millis;
    float launch_speed_target = 0.0;

    int16_t init_speed_target_;
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
              const vector_nav* vn_data);

    virtual void calc_launch_algo(const vector_nav* vn_data) = 0;
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

    LaunchStates_e get_launch_state() override { return launch_state; }

    void calc_launch_algo(const vector_nav* vn_data) override;
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

    LaunchStates_e get_launch_state() override { return launch_state; }

    void calc_launch_algo(const vector_nav* vn_data) override;
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
    
    LaunchStates_e get_launch_state() override { return launch_state; }
    
    void calc_launch_algo(const vector_nav* vn_data) override;
};

class TorqueControllerPIDTV: public TorqueController<TC_PID_VECTORING>
{
public: 
    void tick(const SysTick_s &tick, const PedalsSystemData_s &pedalsData, float vx_b, float wheel_angle_rad, float yaw_rate);
    TorqueControllerPIDTV(TorqueControllerOutput_s &writeout): writeout_(writeout)
    {
        tv_pid_.initialize();
        tv_pid_.setExternalInputs(&pid_input_);
        pid_input_.PID_P = 2.0;
        pid_input_.PID_I = 1.0;
        pid_input_.PID_D = 0.0;
        pid_input_.PID_N = 100;
        
    }
    
    PIDTVTorqueControllerData get_data(){
        PIDTVTorqueControllerData data;
        data.controller_input = tv_pid_.shit_in;
        data.controller_output = tv_pid_.shit_out;
        data.fl_torque_delta = pid_input_.FL_in - tv_pid_.getExternalOutputs().FL_out;
        data.fr_torque_delta = pid_input_.FR_in - tv_pid_.getExternalOutputs().FR_out;
        data.rl_torque_delta = pid_input_.RL_in - tv_pid_.getExternalOutputs().RL_out;
        data.rr_torque_delta = pid_input_.RR_in - tv_pid_.getExternalOutputs().RR_out;
        return data;
    }
private:
    TorqueControllerOutput_s &writeout_;
    
    PID_TV::ExtU_PID_TV_T pid_input_;
    PID_TV tv_pid_;
};

#endif /* __TORQUECONTROLLERS_H__ */
