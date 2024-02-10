#include "TorqueControllers.h"
#include "Utility.h"
#include <algorithm>

static inline void TCPowerLimitScaleDown(
    DrivetrainCommand_s &command,
    const DrivetrainDynamicReport_s &drivetrainData,
    float powerLimit
)
{
    // TODO
    // probably requires AMS interface
}

static inline void TCPosTorqueLimit(DrivetrainCommand_s &command, float torqueLimit)
{
    for (int i = 0; i < NUM_MOTORS; i++)
    {
        command.torqueSetpoints[i] = std::min(command.torqueSetpoints[i], torqueLimit);
    }
}

// TorqueControllerSimple

void TorqueControllerSimple::tick(const SysTick_s& tick, const PedalsSystemData_s& pedalsData, float torqueLimit)
{
    // Calculate torque commands at 100hz
    if (tick.triggers.trigger100)
    {
        if ((!pedalsData.brakeAndAccelPressedImplausibility) && (pedalsData.implausibilityExceededMaxDuration== false))
        {
            // Both pedals are not pressed and no implausibility has been detected
            // accelRequest goes between 1.0 and -1.0
            float accelRequest = pedalsData.accelPercent - pedalsData.brakePercent;
            float torqueRequest;

            if (accelRequest >= 0.0)
            {
                // Positive torque request
                torqueRequest = accelRequest * AMK_MAX_TORQUE;

                data_.speeds_rpm[FL] = AMK_MAX_RPM;
                data_.speeds_rpm[FR] = AMK_MAX_RPM;
                data_.speeds_rpm[RL] = AMK_MAX_RPM;
                data_.speeds_rpm[RR] = AMK_MAX_RPM;

                data_.torqueSetpoints[FL] = torqueRequest * frontTorqueScale_;
                data_.torqueSetpoints[FR] = torqueRequest * frontTorqueScale_;
                data_.torqueSetpoints[RL] = torqueRequest * rearTorqueScale_;
                data_.torqueSetpoints[RR] = torqueRequest * rearTorqueScale_;
            }
            else
            {
                // Negative torque request
                torqueRequest = MAX_REGEN_TORQUE * accelRequest * -1.0; 
                
                data_.speeds_rpm[FL] = 0.0;
                data_.speeds_rpm[FR] = 0.0;
                data_.speeds_rpm[RL] = 0.0;
                data_.speeds_rpm[RR] = 0.0;

                data_.torqueSetpoints[FL] = torqueRequest;
                data_.torqueSetpoints[FR] = torqueRequest;
                data_.torqueSetpoints[RL] = torqueRequest;
                data_.torqueSetpoints[RR] = torqueRequest;
            }

            // Apply the torque limit
            TCPosTorqueLimit(data_, torqueLimit);
        }
        else
        {
            // Both pedals are pressed or an implausibility has been detected
            // Zero out torque
            data_.speeds_rpm[FL] = 0.0;
            data_.speeds_rpm[FR] = 0.0;
            data_.speeds_rpm[RL] = 0.0;
            data_.speeds_rpm[RR] = 0.0;

            data_.torqueSetpoints[FL] = 0.0;
            data_.torqueSetpoints[FR] = 0.0;
            data_.torqueSetpoints[RL] = 0.0;
            data_.torqueSetpoints[RR] = 0.0;

        }

        writeout_ = data_;
    }
}