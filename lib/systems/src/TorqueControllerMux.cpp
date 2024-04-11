#include "TorqueControllerMux.h"
#include "Utility.h"
#include "PhysicalParameters.h"

#include <stdio.h>

void TorqueControllerMux::tick(
    const SysTick_s &tick,
    const DrivetrainDynamicReport_s &drivetrainData,
    const PedalsSystemData_s &pedalsData,
    const SteeringSystemData_s &steeringData,
    const AnalogConversion_s &loadFLData,
    const AnalogConversion_s &loadFRData,
    const AnalogConversion_s &loadRLData,
    const AnalogConversion_s &loadRRData,
    DialMode_e dashboardDialMode,
    bool dashboardTorqueModeButtonPressed,
    const vector_nav &vn_data,
    float wheel_angle_rad)
{
    // Tick all torque controllers
    torqueControllerSimple_.tick(tick, pedalsData, torqueLimitMap_[torqueLimit_]);
    torqueControllerLoadCellVectoring_.tick(tick, pedalsData, torqueLimitMap_[torqueLimit_], loadFLData, loadFRData, loadRLData, loadRRData);
    torqueControllerSimpleLaunch_.tick(tick, pedalsData, drivetrainData.measuredSpeeds, &vn_data);
    torqueControllerSlipLaunch_.tick(tick, pedalsData, drivetrainData.measuredSpeeds, &vn_data);
    // torqueControllerPIDTV_.tick(tick, pedalsData, vn_data.velocity_x, wheel_angle_rad, vn_data.yaw);
    
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

        applyPowerLimit(&drivetrainCommand_);
        applyTorqueLimit(&drivetrainCommand_);
        applyPosSpeedLimit(&drivetrainCommand_);

    }
}

/*
    Apply power limit such that the mechanical power of all wheels never
    exceeds the preset mechanical power limit. Scales all wheels down to
    preserve functionality of torque controllers
*/
void TorqueControllerMux::applyPowerLimit(DrivetrainCommand_s* command)
{
    float net_torque_mag = 0;
    float net_wheelspeed = 0;

    for (int i = 0; i < NUM_MOTORS; i++) {
        // get the total magnitude of torque from all 4 wheels
        #ifdef ARDUINO_TEENSY41 // screw arduino.h macros
        net_torque_mag += abs(command->torqueSetpoints[i]);
        net_wheelspeed += abs(command->speeds_rpm[i]);
        #else
        net_torque_mag += std::abs(command->torqueSetpoints[i]);
        net_wheelspeed += std::abs(command->speeds_rpm[i]);
        #endif
    }

    // get current total mechanical power
    float cur_power = net_torque_mag * (net_wheelspeed * RPM_TO_RAD_PER_SECOND);
    
    // only evaluate power limit if current power exceeds it
    if (cur_power > (MAX_POWER_LIMIT)) {
        for (int i = 0; i < NUM_MOTORS; i++) {
            // calculate the percent of total torque requested per wheel
            float torque_percent = command->torqueSetpoints[i] / net_torque_mag;
            // based on the torque percent and max power limit, get the max power each wheel can use
            float power_per_corner = (torque_percent * MAX_POWER_LIMIT);
            // power / omega (motor rad/s) to get torque per wheel
            command->torqueSetpoints[i] = power_per_corner / (command->speeds_rpm[i] * RPM_TO_RAD_PER_SECOND);

            // isn't this just always distributing max power to all wheels?
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
    
    printf("max torque: %.2f\n", max_torque);
    printf("avg torque: %.2f\n", avg_torque);
    // if this is greather than the torque limit, scale down
    if (avg_torque > max_torque) {
        // get the scale of avg torque above max torque
        float scale = avg_torque / max_torque;
        // divide by scale to lower avg below max torque
        printf("scale: %.2f\n", scale);
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