#ifndef TORQUECONTROLLERSDATA
#define TORQUECONTROLLERSDATA
#include <stdint.h>
#include "Utility.h"

struct PIDTVTorqueControllerData
{
    float controller_input;
    float controller_output;
    float fl_torque_delta;
    float fr_torque_delta;
    float rl_torque_delta;
    float rr_torque_delta;
};
enum class TorqueLimit_e
{
    TCMUX_LOW_TORQUE = 0,
    TCMUX_MID_TORQUE = 1,
    TCMUX_FULL_TORQUE = 2,
    TCMUX_NUM_TORQUE_LIMITS = 3,
};

/* Enum for the modes on the dial, corresponds directly to dial index pos. */
enum class ControllerMode_e
{
    /* No torque vectoring */
    MODE_0,
    /* Normal force torque vectoring */
    MODE_1,
    /* PID torque vectoring */
    MODE_2,
    /* Launch Ctrl */
    MODE_3,
    MODE_4,
    MODE_5,
};

struct PedalsSystemData_s
{
    bool accelImplausible : 1;
    bool brakeImplausible : 1;
    bool brakePressed : 1;
    bool accelPressed : 1;
    bool mechBrakeActive : 1;
    bool brakeAndAccelPressedImplausibility : 1;
    bool implausibilityExceededMaxDuration : 1;
    float accelPercent;
    float brakePercent;
    float regenPercent;
};
struct DrivetrainDynamicReport_s
{
    uint16_t measuredInverterFLPackVoltage;
    float measuredSpeeds[NUM_MOTORS];
    float measuredTorques[NUM_MOTORS];
    float measuredTorqueCurrents[NUM_MOTORS];
    float measuredMagnetizingCurrents[NUM_MOTORS];
};
struct DrivetrainCommand_s
{
    float speeds_rpm[NUM_MOTORS];
    float torqueSetpoints[NUM_MOTORS]; // FIXME: misnomer. This represents the magnitude of the torque the inverter can command to reach the commanded speed setpoint
};

const DrivetrainCommand_s TC_COMMAND_NO_TORQUE = {
    .speeds_rpm = {0.0, 0.0, 0.0, 0.0},
    .torqueSetpoints = {0.0, 0.0, 0.0, 0.0}};

struct TorqueControllerOutput_s
{
    DrivetrainCommand_s command;
    bool ready;
};
struct vectornav
{
    float velocity_x;
    float velocity_y;
    float velocity_z;
    float linear_accel_x;
    float linear_accel_y;
    float linear_accel_z;
    float uncompLinear_accel[3]; // 3D uncompensated linear acceleration
    float yaw;
    float pitch;
    float roll;
    double latitude;
    double longitude;
    double ecef_coords[3]; // x,y,z
    uint64_t gps_time;     // gps time
    uint8_t vn_status;     // status
    xyz_vec<float> angular_rates;
};

enum class TorqueControllerMuxError
{
    NO_ERROR = 0,
    ERROR_SPEED_DIFF_TOO_HIGH = 1,
    ERROR_TORQUE_DIFF_TOO_HIGH = 2
};

struct TorqueControllerMuxStatus
{
    TorqueControllerMuxError current_error;
    ControllerMode_e current_controller_mode_;
    bool output_is_bypassing_limits;
};

struct car_state
{
    // data
    SysTick_s systick;
    SteeringSystemData_s steering_data;
    DrivetrainDynamicReport_s drivetrain_data;
    LoadCellInterfaceOutput_s loadcell_data;
    PedalsSystemData_s pedals_data;
    vectornav vn_data;
};

#endif