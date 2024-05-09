#include "TorqueControllerMuxV2.h"

template <std::size_t num_controllers>
DrivetrainCommand_s TorqueControllerMuxv2<num_controllers>::getDrivetrainCommand(ControllerMode_e requested_controller_type,
                                                                                 TorqueLimit_e requested_torque_limit,
                                                                                 const car_state &input_state)
{
    TorqueControllerOutput_s current_output;

    current_output = controller_pointers_[static_cast<int>(current_status_.current_controller_mode_)]->evaluate(input_state);

    bool requesting_controller_change = requested_controller_type != current_status_.current_controller_mode_;

    if (requesting_controller_change)
    {
        TorqueControllerOutput_s proposed_output = controller_pointers_[static_cast<int>(requested_controller_type)]->evaluate(input_state);
        TorqueControllerMuxError error_state = can_switch_controller_(input_state.drivetrain_data, current_output.command, proposed_output.command);
        std::cout << "error state " << static_cast<int>(error_state) <<std::endl;
        if (error_state == TorqueControllerMuxError::NO_ERROR)
        {
            current_status_.current_controller_mode_ = requested_controller_type;
            current_output = proposed_output;
        }
        current_status_.current_error = error_state;
    }

    return current_output.command;
}

template <std::size_t num_controllers>
TorqueControllerMuxError TorqueControllerMuxv2<num_controllers>::can_switch_controller_(DrivetrainDynamicReport_s current_drivetrain_data,
                                                                                        DrivetrainCommand_s previous_controller_command,
                                                                                        DrivetrainCommand_s desired_controller_out)
{
    bool speedPreventsModeChange = false;
    // Check if torque delta permits mode change
    bool torqueDeltaPreventsModeChange = false;
    for (int i = 0; i < NUM_MOTORS; i++)
    {
        speedPreventsModeChange = (abs(current_drivetrain_data.measuredSpeeds[i] * RPM_TO_METERS_PER_SECOND) >= max_change_speed_);
        // only if the torque delta is positive do we not want to switch to the new one
        torqueDeltaPreventsModeChange = (desired_controller_out.torqueSetpoints[i] - previous_controller_command.torqueSetpoints[i]) > max_torque_pos_change_delta_;
        if (speedPreventsModeChange)
        {
            return TorqueControllerMuxError::ERROR_SPEED_DIFF_TOO_HIGH;
        }
        if (torqueDeltaPreventsModeChange)
        {
            return TorqueControllerMuxError::ERROR_TORQUE_DIFF_TOO_HIGH;
        }
    }
    return TorqueControllerMuxError::NO_ERROR;
}

/* Apply limit such that wheelspeed never goes negative */
template <std::size_t num_controllers>
DrivetrainCommand_s TorqueControllerMuxv2<num_controllers>::apply_positive_speed_limit_(const DrivetrainCommand_s &command)
{
    DrivetrainCommand_s out;
    out = command;
    for (int i = 0; i < NUM_MOTORS; i++)
    {
        out.speeds_rpm[i] = std::max(0.0f, command.speeds_rpm[i]);
    }
    return out;
}

template <std::size_t num_controllers>
DrivetrainCommand_s TorqueControllerMuxv2<num_controllers>::apply_torque_limit_(const DrivetrainCommand_s &command, float max_torque)
{
    DrivetrainCommand_s out = command;
    float avg_torque = 0;
    // get the average torque accross all 4 wheels
    for (int i = 0; i < NUM_MOTORS; i++)
    {

        avg_torque += abs(command.torqueSetpoints[i]);
    }
    avg_torque /= NUM_MOTORS;

    // if this is greather than the torque limit, scale down
    if (avg_torque > max_torque)
    {
        // get the scale of avg torque above max torque
        float scale = avg_torque / max_torque;
        // divide by scale to lower avg below max torque
        for (int i = 0; i < NUM_MOTORS; i++)
        {
            out.torqueSetpoints[i] = out.torqueSetpoints[i] / scale;
        }
    }
    return out;
}

/*
    Apply power limit such that the mechanical power of all wheels never
    exceeds the preset mechanical power limit. Scales all wheels down to
    preserve functionality of torque controllers
*/
template <std::size_t num_controllers>
DrivetrainCommand_s TorqueControllerMuxv2<num_controllers>::apply_power_limit_(const DrivetrainCommand_s &command, const DrivetrainDynamicReport_s &drivetrain, float power_limit, float max_torque)
{
    DrivetrainCommand_s out = command;
    float net_torque_mag = 0;
    float net_power = 0;

    // calculate current mechanical power
    for (int i = 0; i < NUM_MOTORS; i++)
    {
        // get the total magnitude of torque from all 4 wheels
        // sum up net torque
        net_torque_mag += abs(out.torqueSetpoints[i]);
        // calculate P = T*w for each wheel and sum together
        net_power += abs(out.torqueSetpoints[i] * (drivetrain.measuredSpeeds[i] * RPM_TO_RAD_PER_SECOND));
    }

    // only evaluate power limit if current power exceeds it
    if (net_power > (power_limit))
    {
        for (int i = 0; i < NUM_MOTORS; i++)
        {

            // TODO: SOMEBODY PLZ MAKE THIS WORK
            // enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_power_);

            // calculate the percent of total torque requested per wheel
            float torque_percent = abs(out.torqueSetpoints[i] / net_torque_mag);
            // based on the torque percent and max power limit, get the max power each wheel can use
            float power_per_corner = (torque_percent * power_limit);

            // power / omega (motor rad/s) to get torque per wheel
            out.torqueSetpoints[i] = abs(power_per_corner / (drivetrain.measuredSpeeds[i] * RPM_TO_RAD_PER_SECOND));
            out.torqueSetpoints[i] = std::max(0.0f, std::min(command.torqueSetpoints[i], max_torque));
        }
    }
    return out;
}

template <std::size_t num_controllers>
DrivetrainCommand_s TorqueControllerMuxv2<num_controllers>::apply_regen_limit_(const DrivetrainCommand_s &command, const DrivetrainDynamicReport_s &drivetrain_data)
{
    DrivetrainCommand_s out = command;
    const float noRegenLimitKPH = 10.0;
    const float fullRegenLimitKPH = 5.0;
    float maxWheelSpeed = 0.0;
    float torqueScaleDown = 0.0;
    bool allWheelsRegen = true; // true when all wheels are targeting speeds below the current wheel speed

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        maxWheelSpeed = std::max(maxWheelSpeed, abs(drivetrain_data.measuredSpeeds[i]) * RPM_TO_KILOMETERS_PER_HOUR);

        allWheelsRegen &= (command.speeds_rpm[i] < abs(drivetrain_data.measuredSpeeds[i]) || command.speeds_rpm[i] == 0);
    }

    // begin limiting regen at noRegenLimitKPH and completely limit regen at fullRegenLimitKPH
    // linearly interpolate the scale factor between noRegenLimitKPH and fullRegenLimitKPH
    torqueScaleDown = std::min(1.0f, std::max(0.0f, (maxWheelSpeed - fullRegenLimitKPH) / (noRegenLimitKPH - fullRegenLimitKPH)));

    if (allWheelsRegen)
    {
        for (int i = 0; i < NUM_MOTORS; i++)
        {
            out.torqueSetpoints[i] *= torqueScaleDown;
        }
    }
    return out;
}