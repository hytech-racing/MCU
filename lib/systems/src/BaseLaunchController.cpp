#include "BaseLaunchController.h"
#include <stdlib.h> /* abs */
void BaseLaunchController::tick(
    const SysTick_s &tick,
    const PedalsSystemData_s &pedalsData,
    const float wheel_rpms[],
    const VectornavData_s &vn_data)
{

    if (tick.triggers.trigger100)
    {

        current_millis_ = tick.millis;

        int16_t brake_torque_req = pedalsData.regenPercent * PhysicalParameters::MAX_REGEN_TORQUE;

        float max_speed = 0;
        for (int i = 0; i < 4; i++)
        {
            max_speed = std::max(max_speed, abs(wheel_rpms[i]));
        }

        writeout_.ready = true;

        switch (launch_state_)
        {
        case LaunchStates_e::LAUNCH_NOT_READY:
            // set torques and speed to 0
            writeout_.command.speeds_rpm[FL] = 0.0;
            writeout_.command.speeds_rpm[FR] = 0.0;
            writeout_.command.speeds_rpm[RL] = 0.0;
            writeout_.command.speeds_rpm[RR] = 0.0;

            writeout_.command.torqueSetpoints[FL] = brake_torque_req;
            writeout_.command.torqueSetpoints[FR] = brake_torque_req;
            writeout_.command.torqueSetpoints[RL] = brake_torque_req;
            writeout_.command.torqueSetpoints[RR] = brake_torque_req;

            // init launch vars
            launch_speed_target_ = 0;
            time_of_launch_ = tick.millis;
            // check speed is 0 and pedals not pressed
            if ((pedalsData.accelPercent < BaseLaunchControllerParams::launch_ready_accel_threshold) && (pedalsData.brakePercent < BaseLaunchControllerParams::launch_ready_brake_threshold) && (max_speed < BaseLaunchControllerParams::launch_ready_speed_threshold))
            {
                launch_state_ = LaunchStates_e::LAUNCH_READY;
            }

            break;
        case LaunchStates_e::LAUNCH_READY:
            // set torques and speed to 0
            writeout_.command.speeds_rpm[FL] = 0.0;
            writeout_.command.speeds_rpm[FR] = 0.0;
            writeout_.command.speeds_rpm[RL] = 0.0;
            writeout_.command.speeds_rpm[RR] = 0.0;

            writeout_.command.torqueSetpoints[FL] = brake_torque_req;
            writeout_.command.torqueSetpoints[FR] = brake_torque_req;
            writeout_.command.torqueSetpoints[RL] = brake_torque_req;
            writeout_.command.torqueSetpoints[RR] = brake_torque_req;

            // init launch vars
            launch_speed_target_ = 0;
            time_of_launch_ = current_millis_;

            // check speed is 0 and brake not pressed
            if ((pedalsData.brakePercent >= BaseLaunchControllerParams::launch_ready_brake_threshold) || (max_speed >= BaseLaunchControllerParams::launch_ready_speed_threshold))
            {
                launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
            }
            else if (pedalsData.accelPercent >= BaseLaunchControllerParams::launch_go_accel_threshold)
            {

                initial_ecef_x_ = vn_data.ecef_coords[0];
                initial_ecef_y_ = vn_data.ecef_coords[1];
                initial_ecef_z_ = vn_data.ecef_coords[2];

                launch_state_ = LaunchStates_e::LAUNCHING;
            }

            // check accel above launch threshold and launch
            break;
        case LaunchStates_e::LAUNCHING:
        { // use brackets to ignore 'cross initialization' of secs_since_launch
            // check accel below launch threshold and brake above
            if ((pedalsData.accelPercent <= BaseLaunchControllerParams::launch_stop_accel_threshold) || (pedalsData.brakePercent >= BaseLaunchControllerParams::launch_ready_brake_threshold))
            {
                launch_state_ = LaunchStates_e::LAUNCH_NOT_READY;
            }

            calc_launch_algo(vn_data);

            writeout_.command.speeds_rpm[FL] = launch_speed_target_;
            writeout_.command.speeds_rpm[FR] = launch_speed_target_;
            writeout_.command.speeds_rpm[RL] = launch_speed_target_;
            writeout_.command.speeds_rpm[RR] = launch_speed_target_;

            writeout_.command.torqueSetpoints[FL] = PhysicalParameters::AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[FR] = PhysicalParameters::AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[RL] = PhysicalParameters::AMK_MAX_TORQUE;
            writeout_.command.torqueSetpoints[RR] = PhysicalParameters::AMK_MAX_TORQUE;

            break;
        }
        default:
            break;
        }
    }
}

TorqueControllerOutput_s BaseLaunchController::evaluate(const SharedCarState_s &state)
{
    tick(state.systick, state.pedals_data, state.drivetrain_data.measuredSpeeds, state.vn_data);
    return writeout_;
}