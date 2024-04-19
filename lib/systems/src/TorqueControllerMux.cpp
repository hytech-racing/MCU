#include "TorqueControllerMux.h"
#include "Utility.h"
#include "PhysicalParameters.h"

void TorqueControllerMux::tick(
        const SysTick_s &tick,
        const DrivetrainDynamicReport_s &drivetrainData,
        const PedalsSystemData_s &pedalsData,
        const SteeringSystemData_s &steeringData,
        const veh_vec<AnalogConversion_s> &loadCellData,
        DialMode_e dashboardDialMode,
        bool dashboardTorqueModeButtonPressed,
        const vector_nav &vn_data, 
        float wheel_angle_rad,
        const DrivetrainCommand_s &CASECommand
    )
{
    // Tick all torque controllers
    torqueControllerSimple_.tick(tick, pedalsData, torqueLimitMap_[torqueLimit_]);
    torqueControllerLoadCellVectoring_.tick(tick, pedalsData, torqueLimitMap_[torqueLimit_], loadCellData);
    torqueControllerSimpleLaunch_.tick(tick, pedalsData, drivetrainData.measuredSpeeds, &vn_data);
    torqueControllerSlipLaunch_.tick(tick, pedalsData, drivetrainData.measuredSpeeds, &vn_data);
    tcCASEWrapper_.tick(CASECommand);
    
    // Tick torque button logic at 50hz
    if (tick.triggers.trigger50)
    {
        // detect high-to-low transition and lock out button presses for DEBOUNCE_MILLIS ms
        if (
            torqueLimitButtonPressed_ == true && dashboardTorqueModeButtonPressed == false && tick.millis - torqueLimitButtonPressedTime_ > DEBOUNCE_MILLIS)
        {
            // WOW C++ is ass
            torqueLimit_ = static_cast<TorqueLimit_e>((static_cast<int>(torqueLimit_) + 1) % (static_cast<int>(TorqueLimit_e::TCMUX_NUM_TORQUE_LIMITS)));
            torqueLimitButtonPressedTime_ = tick.millis;
        }
        torqueLimitButtonPressed_ = dashboardTorqueModeButtonPressed;
    }

    // Tick TCMUX at 100hz
    if (tick.triggers.trigger100)
    {
        // Determine next state based on dashboard dial state
        // Only transisiton to the next state if:
        // Vehicle speed is below 5 m/s
        // AND torque delta between old and new controllers is < 0.5nm on every wheel
        // AND the selected torque controller is in the ready state
        if (muxMode_ != dialModeMap_[dashboardDialMode])
        {
            // Check if speed permits mode change
            bool speedPreventsModeChange = false;
            for (int i = 0; i < NUM_MOTORS; i++) {
                speedPreventsModeChange |= drivetrainData.measuredSpeeds[i] * RPM_TO_METERS_PER_SECOND >= MAX_SPEED_FOR_MODE_CHANGE;
            }

            // Check if torque delta permits mode change
            bool torqueDeltaPreventsModeChange = false;
            for (int i = 0; i < NUM_MOTORS; i++)
            {
                float torqueDelta = abs(
                    controllerOutputs_[static_cast<int>(muxMode_)].command.torqueSetpoints[i] - controllerOutputs_[static_cast<int>(dialModeMap_[dashboardDialMode])].command.torqueSetpoints[i]);

                if (torqueDelta > MAX_TORQUE_DELTA_FOR_MODE_CHANGE)
                {
                    torqueDeltaPreventsModeChange = true;
                    break;
                }
            }

            // Check if targeted controller is ready to be selected
            bool controllerNotReadyPreventsModeChange = (controllerOutputs_[static_cast<int>(dialModeMap_[dashboardDialMode])].ready == false);

            if (!(speedPreventsModeChange || torqueDeltaPreventsModeChange || controllerNotReadyPreventsModeChange))
            {
                muxMode_ = dialModeMap_[dashboardDialMode];
                cur_dial_mode_ = dashboardDialMode;
            }
        }

        // Check if the current controller is ready. If it has faulted, revert to safe mode
        // When the car goes below 5m/s, it will attempt to re-engage the faulted controller
        // It will stay in safe mode if the controller is still faulted
        if (controllerOutputs_[static_cast<int>(muxMode_)].ready == false)
        {
            muxMode_ = TorqueController_e::TC_SAFE_MODE;
        }

        drivetrainCommand_ = controllerOutputs_[static_cast<int>(muxMode_)].command;

        // apply torque limit before power limit to not power limit
        applyRegenLimit(&drivetrainCommand_, &drivetrainData);
        applyTorqueLimit(&drivetrainCommand_);
        applyPowerLimit(&drivetrainCommand_, &drivetrainData);
        applyPosSpeedLimit(&drivetrainCommand_);

    }
}

/*
    Apply limit to make sure that regenerative braking is not applied when
    wheelspeed is below 5kph on all wheels.
*/
void TorqueControllerMux::applyRegenLimit(DrivetrainCommand_s* command, const DrivetrainDynamicReport_s* drivetrain)
{
    const float noRegenLimitKPH = 10.0;
    const float fullRegenLimitKPH = 5.0;
    float maxWheelSpeed = 0.0;
    float torqueScaleDown = 0.0;
    bool allWheelsRegen = true; // true when all wheels are targeting speeds below the current wheel speed

    for (int i = 0; i < NUM_MOTORS; i++) {
        maxWheelSpeed = std::max(maxWheelSpeed, drivetrain->measuredSpeeds[i] * RPM_TO_KILOMETERS_PER_HOUR);
        allWheelsRegen &= (command->speeds_rpm[i] < drivetrain->measuredSpeeds[i]);
    }

    // begin limiting regen at noRegenLimitKPH and completely limit regen at fullRegenLimitKPH
    // linearly interpolate the scale factor between noRegenLimitKPH and fullRegenLimitKPH
    torqueScaleDown = std::min(1.0f, std::max(0.0f, (maxWheelSpeed - fullRegenLimitKPH) / (noRegenLimitKPH - fullRegenLimitKPH)));

    if (allWheelsRegen)
    {
        for (int i = 0; i < NUM_MOTORS; i++) {
            command->torqueSetpoints[i] *= torqueScaleDown;
        }
    }
}

/*
    Apply power limit such that the mechanical power of all wheels never
    exceeds the preset mechanical power limit. Scales all wheels down to
    preserve functionality of torque controllers
*/
void TorqueControllerMux::applyPowerLimit(DrivetrainCommand_s* command, const DrivetrainDynamicReport_s* drivetrain)
{
    float net_torque_mag = 0;
    float net_power = 0;

    // calculate current mechanical power
    for (int i = 0; i < NUM_MOTORS; i++) {
        // get the total magnitude of torque from all 4 wheels
        #ifdef ARDUINO_TEENSY41 // screw arduino.h macros
        net_torque_mag += abs(command->torqueSetpoints[i]);
        net_power += abs(command->torqueSetpoints[i] * (drivetrain->measuredSpeeds[i] * RPM_TO_RAD_PER_SECOND));
        #else
        // sum up net torque
        net_torque_mag += std::abs(command->torqueSetpoints[i]);
        // calculate P = T*w for each wheel and sum together
        net_power += std::abs(command->torqueSetpoints[i] * (drivetrain->measuredSpeeds[i] * RPM_TO_RAD_PER_SECOND));
        #endif
    }
    
    // only evaluate power limit if current power exceeds it
    if (net_power > (MAX_POWER_LIMIT)) {
        for (int i = 0; i < NUM_MOTORS; i++) {
            // calculate the percent of total torque requested per wheel
            float torque_percent = command->torqueSetpoints[i] / net_torque_mag;
            // based on the torque percent and max power limit, get the max power each wheel can use
            float power_per_corner = (torque_percent * MAX_POWER_LIMIT);
            // power / omega (motor rad/s) to get torque per wheel
            command->torqueSetpoints[i] = power_per_corner / (drivetrain->measuredSpeeds[i] * RPM_TO_RAD_PER_SECOND);
        }
    }

}

/*
    Apply limit such that the average wheel torque is never above the max
    torque allowed in the current torque mode.
    This will uniformally scale down all torques as to not affect the functionality
    of non-symmetrical torque controllers.
*/
void TorqueControllerMux::applyTorqueLimit(DrivetrainCommand_s* command)
{  
    float max_torque = getMaxTorque();
    float avg_torque = 0;

    // get the average torque accross all 4 wheels
    for (int i = 0; i < NUM_MOTORS; i++) {
        #ifdef ARDUINO_TEENSY41 // screw arduino.h macros
        avg_torque += abs(command->torqueSetpoints[i]);
        #else
        avg_torque += std::abs(command->torqueSetpoints[i]);
        #endif
    }
    avg_torque /= NUM_MOTORS;

    // if this is greather than the torque limit, scale down
    if (avg_torque > max_torque) {
        // get the scale of avg torque above max torque
        float scale = avg_torque / max_torque;
        // divide by scale to lower avg below max torque
        for (int i = 0; i < NUM_MOTORS; i++) {
            command->torqueSetpoints[i] /= scale;
        }
    }

}

/* Apply limit such that wheelspeed never goes negative */
void TorqueControllerMux::applyPosSpeedLimit(DrivetrainCommand_s* command) {
    for (int i = 0; i < NUM_MOTORS; i++)
    {
        command->torqueSetpoints[i] = std::max(0.0f, command->torqueSetpoints[i]);
    }
}