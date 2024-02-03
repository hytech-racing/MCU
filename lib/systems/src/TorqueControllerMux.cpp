#include <TorqueControllerMux.h>
#include <Utility.h>

void TorqueControllerMux::tick(
        const SysTick_s& tick,
        const DrivetrainDynamicReport_s& drivetrainData,
        const PedalsSystemData_s& pedalsData,
        const SteeringSystemData_s& steeringData,
        const AnalogConversion_s& loadFLData,
        const AnalogConversion_s& loadFRData,
        const AnalogConversion_s& loadRLData,
        const AnalogConversion_s& loadRRData,
        DialMode_e dashboardDialMode,
        bool dashboardTorqueModeButtonPressed
    )
{
    // Tick all torque controllers
    torqueControllerSimple_.tick(tick, pedalsData, torqueLimit_);

    // Tick torque button logic at 50hz
    if (tick.triggers.trigger50)
    {
        // detect high-to-low transition and lock out button presses for DEBOUNCE_MILLIS ms
        if (
            torqueLimitButtonPressed_ 
            && dashboardTorqueModeButtonPressed
            && tick.millis - torqueLimitButtonPressedTime_ > DEBOUNCE_MILLIS
        )
        {
            // WOW C++ is ass
            torqueLimit_ = static_cast<TorqueLimit_e>((static_cast<int>(torqueLimit_) + 1) % static_cast<int>(TCMUX_NUM_TORQUE_LIMITS));
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
        if (muxMode_ != dialModeMap_[dashboardDialMode])
        {
            bool speedPreventsModeChange = false;
            for (int i = 0; i < NUM_MOTORS; i++)
                speedPreventsModeChange |= drivetrainData.measuredSpeeds[i] * RPM_TO_METERS_PER_SECOND >= maxSpeedForModeChange;

            bool torqueDeltaPreventsModeChange = false;
            for (int i = 0; i < NUM_MOTORS; i++)
            {
                float posTorqueDelta = abs(
                    controllerCommands_[static_cast<int>(muxMode_)].posTorqueLimits[i]
                    - controllerCommands_[static_cast<int>(dialModeMap_[dashboardDialMode])].posTorqueLimits[i]
                );
                float negTorqueDelta = abs(
                    controllerCommands_[static_cast<int>(muxMode_)].negTorqueLimits[i]
                    - controllerCommands_[static_cast<int>(dialModeMap_[dashboardDialMode])].negTorqueLimits[i]
                );
                if (posTorqueDelta > maxTorqueDeltaForModeChange || negTorqueDelta > maxTorqueDeltaForModeChange)
                {
                    torqueDeltaPreventsModeChange = true;
                    break;
                }
            }

            if (!(speedPreventsModeChange || torqueDeltaPreventsModeChange))
            {
                muxMode_ = dialModeMap_[dashboardDialMode];
            }
        }

        drivetrainCommand_ = controllerCommands_[static_cast<int>(muxMode_)];
    }
}