#include "TorqueControllerMux.h"

template <std::size_t num_controllers>
DrivetrainCommand_s TorqueControllerMux<num_controllers>::getDrivetrainCommand(ControllerMode_e requested_controller_type,
                                                                               TorqueLimit_e requested_torque_limit,
                                                                               const SharedCarState_s &input_state)
{

    DrivetrainCommand_s empty_command = BaseControllerParams::TC_COMMAND_NO_TORQUE;

    TorqueControllerOutput_s current_output = {
        .command = empty_command,
        .ready = true};

    int req_controller_mode_index = static_cast<int>(requested_controller_type);
    int current_controller_mode_index = static_cast<int>(current_status_.current_controller_mode_);

    if ((std::size_t)req_controller_mode_index > ( controller_pointers_.size() - 1 ))
    {
        current_status_.current_error = TorqueControllerMuxError::ERROR_CONTROLLER_INDEX_OUT_OF_BOUNDS;
        return empty_command;
    }

    current_output = controller_pointers_[current_controller_mode_index]->evaluate(input_state);

    // std::cout << "output torques " << current_output.command.torqueSetpoints[0] << " " << current_output.command.torqueSetpoints[1] << " " << current_output.command.torqueSetpoints[2] << " " << current_output.command.torqueSetpoints[3] << std::endl;
    bool requesting_controller_change = requested_controller_type != current_status_.current_controller_mode_;

    if (requesting_controller_change)
    {
        TorqueControllerOutput_s proposed_output = controller_pointers_[req_controller_mode_index]->evaluate(input_state);
        TorqueControllerMuxError error_state = can_switch_controller_(input_state.drivetrain_data, current_output.command, proposed_output.command);
        // std::cout << "error state " << static_cast<int>(error_state) << std::endl;
        if (error_state == TorqueControllerMuxError::NO_ERROR)
        {
            current_status_.current_controller_mode_ = requested_controller_type;
            current_controller_mode_index = req_controller_mode_index;
            current_output = proposed_output;
        }
        current_status_.current_error = error_state;
    }
    if (!mux_bypass_limits_[current_controller_mode_index])
    {
        current_status_.current_torque_limit_enum = requested_torque_limit;
        // std::cout << "output torques before regen limit " << current_output.command.torqueSetpoints[0] << " " << current_output.command.torqueSetpoints[1] << " " << current_output.command.torqueSetpoints[2] << " " << current_output.command.torqueSetpoints[3] << std::endl;
        current_output.command = apply_regen_limit_(current_output.command, input_state.drivetrain_data);
        // std::cout << "output torques after regen limit " << current_output.command.torqueSetpoints[0] << " " << current_output.command.torqueSetpoints[1] << " " << current_output.command.torqueSetpoints[2] << " " << current_output.command.torqueSetpoints[3] << std::endl;
        current_output.command = apply_torque_limit_(current_output.command, torque_limit_map_[requested_torque_limit]);
        current_status_.current_torque_limit_value = torque_limit_map_[requested_torque_limit];
        current_output.command = apply_power_limit_(current_output.command, input_state.drivetrain_data, max_power_limit_, torque_limit_map_[requested_torque_limit]);
        // std::cout << "output torques after power limit " << current_output.command.torqueSetpoints[0] << " " << current_output.command.torqueSetpoints[1] << " " << current_output.command.torqueSetpoints[2] << " " << current_output.command.torqueSetpoints[3] << std::endl;
        current_output.command = apply_positive_speed_limit_(current_output.command);
    }
    else{
        current_status_.current_torque_limit_enum = TorqueLimit_e::TCMUX_FULL_TORQUE;
        current_status_.current_torque_limit_value= PhysicalParameters::AMK_MAX_TORQUE;
    }

    // std::cout << "output torques before return " << current_output.command.torqueSetpoints[0] << " " << current_output.command.torqueSetpoints[1] << " " << current_output.command.torqueSetpoints[2] << " " << current_output.command.torqueSetpoints[3] << std::endl;
    return current_output.command;
}

template <std::size_t num_controllers>
TorqueControllerMuxError TorqueControllerMux<num_controllers>::can_switch_controller_(DrivetrainDynamicReport_s current_drivetrain_data,
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
DrivetrainCommand_s TorqueControllerMux<num_controllers>::apply_positive_speed_limit_(const DrivetrainCommand_s &command)
{
    DrivetrainCommand_s out;
    out = command;
    for (int i = 0; i < NUM_MOTORS; i++)
    {
        out.speeds_rpm[i] = std::max(0.0f, out.speeds_rpm[i]);
    }
    return out;
}

template <std::size_t num_controllers>
DrivetrainCommand_s TorqueControllerMux<num_controllers>::apply_torque_limit_(const DrivetrainCommand_s &command, float max_torque)
{
    DrivetrainCommand_s out = command;
    float avg_torque = 0;
    // get the average torque accross all 4 wheels
    for (int i = 0; i < NUM_MOTORS; i++)
    {

        avg_torque += abs(out.torqueSetpoints[i]);
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
DrivetrainCommand_s TorqueControllerMux<num_controllers>::apply_power_limit_(const DrivetrainCommand_s &command, const DrivetrainDynamicReport_s &drivetrain, float power_limit, float max_torque)
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

    // std::cout <<"net power "<< net_power <<std::endl;
    // only evaluate power limit if current power exceeds it
    if (net_power > (power_limit))
    {
        // std::cout <<"net power too big" <<std::endl;
        for (int i = 0; i < NUM_MOTORS; i++)
        {

            // TODO: SOMEBODY PLZ MAKE THIS WORK
            // enqueue_matlab_msg(msg_queue_, res.controllerBus_controller_power_);

            // calculate the percent of total torque requested per wheel
            float torque_percent = abs(out.torqueSetpoints[i] / net_torque_mag);
            // based on the torque percent and max power limit, get the max power each wheel can use
            float power_per_corner = (torque_percent * power_limit);

            // std::cout <<"corner power " << power_per_corner <<std::endl;
            // power / omega (motor rad/s) to get torque per wheel
            out.torqueSetpoints[i] = abs(power_per_corner / (drivetrain.measuredSpeeds[i] * RPM_TO_RAD_PER_SECOND));
            // std::cout <<"adjusted torque setpoint " << out.torqueSetpoints[i] <<std::endl;
            out.torqueSetpoints[i] = std::max(0.0f, std::min(out.torqueSetpoints[i], max_torque));

            // std::cout <<"final torque setpoint " << out.torqueSetpoints[i] <<std::endl;
        }
    }
    return out;
}

template <std::size_t num_controllers>
DrivetrainCommand_s TorqueControllerMux<num_controllers>::apply_regen_limit_(const DrivetrainCommand_s &command, const DrivetrainDynamicReport_s &drivetrain_data)
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

        allWheelsRegen &= (out.speeds_rpm[i] < abs(drivetrain_data.measuredSpeeds[i]) || out.speeds_rpm[i] == 0);
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