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
        command.posTorqueLimits[i] = std::min(command.posTorqueLimits[i], torqueLimit);
    }
}

// TorqueControllerSimple

void TorqueControllerSimple::tick(const SysTick_s& tick, const PedalsSystemData_s& pedalsData, float torqueLimit)
{
    // Calculate torque commands at 100hz
    if (tick.triggers.trigger100)
    {
        if ((pedalsData.pedalsCommand != PedalsCommanded_e::PEDALS_BOTH_PRESSED) && (pedalsData.persistentImplausibilityDetected == false))
        {
            // Both pedals are not pressed and no implausibility has been detected
            // accelRequest goes between 1.0 and -1.0
            float accelRequest = pedalsData.accelPercent - pedalsData.brakePercent;
            float torqueRequest;

            if (accelRequest > 0.0)
            {
                // Positive torque request
                data_.speeds[FL] = AMK_MAX_RPM;
                data_.speeds[FR] = AMK_MAX_RPM;
                data_.speeds[RL] = AMK_MAX_RPM;
                data_.speeds[RR] = AMK_MAX_RPM;

                data_.posTorqueLimits[FL] = torqueRequest * frontTorqueScale_;
                data_.posTorqueLimits[FR] = torqueRequest * frontTorqueScale_;
                data_.posTorqueLimits[RL] = torqueRequest * rearTorqueScale_;
                data_.posTorqueLimits[RR] = torqueRequest * rearTorqueScale_;

                data_.negTorqueLimits[FL] = 0.0;
                data_.negTorqueLimits[FR] = 0.0;
                data_.negTorqueLimits[RL] = 0.0;
                data_.negTorqueLimits[RR] = 0.0;
            }
            else
            {
                // Negative torque request
                torqueRequest = MAX_REGEN_TORQUE * torqueRequest * -1.0; // TODO: determine whether negative torque limits are signed
                
                data_.speeds[FL] = 0.0;
                data_.speeds[FR] = 0.0;
                data_.speeds[RL] = 0.0;
                data_.speeds[RR] = 0.0;

                data_.posTorqueLimits[FL] = 0.0;
                data_.posTorqueLimits[FR] = 0.0;
                data_.posTorqueLimits[RL] = 0.0;
                data_.posTorqueLimits[RR] = 0.0;

                data_.negTorqueLimits[FL] = torqueRequest;
                data_.negTorqueLimits[FR] = torqueRequest;
                data_.negTorqueLimits[RL] = torqueRequest;
                data_.negTorqueLimits[RR] = torqueRequest;
            }

            // Apply the torque limit
            TCPosTorqueLimit(data_, torqueLimit);
        }
        else
        {
            // Both pedals are pressed or an implausibility has been detected
            // Zero out torque
            data_.speeds[FL] = 0.0;
            data_.speeds[FR] = 0.0;
            data_.speeds[RL] = 0.0;
            data_.speeds[RR] = 0.0;

            data_.posTorqueLimits[FL] = 0.0;
            data_.posTorqueLimits[FR] = 0.0;
            data_.posTorqueLimits[RL] = 0.0;
            data_.posTorqueLimits[RR] = 0.0;

            data_.negTorqueLimits[FL] = 0.0;
            data_.negTorqueLimits[FR] = 0.0;
            data_.negTorqueLimits[RL] = 0.0;
            data_.negTorqueLimits[RR] = 0.0;
        }

        writeout_ = data_;
    }
}