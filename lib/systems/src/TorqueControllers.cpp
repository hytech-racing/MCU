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

static inline void TCPosTorqueLimit(
    DrivetrainCommand_s &command,
    float torqueLimits[NUM_MOTORS]
)
{
    for (int i = 0; i < NUM_MOTORS; i++)
    {
        command.posTorqueLimits[i] = std::min(command.posTorqueLimits[i], torqueLimits[i]);
    }
}

void TorqueControllerSimple::tick(const SysTick_s &tick, const PedalsSystemData_s &pedalsDatam, const DashboardInterfaceOutput_s &dashboardData)
{
    // Calculate torque commands at 100hz
    if (tick.triggers.trigger100)
    {
        if ((pedalsData.pedalsCommand != PEDALS_BOTH_PRESSED) && (pedalsData.persistentImplausibilityDetected == false))
        {
            // Both pedals are not pressed and no implausibility has been detected
            // accelRequest goes between 1.0 and -1.0
            float accelRequest = pedalsData.accelPercent - pedalsData.brakePercent;
            float torqueLim;
            float torqueRequest;

            if (dashboardData.torqueMode == TORQUE_MODE_HIGH)
                torqueLim = AMK_MAX_TORQUE;
            else if (dashboardData.torqueMode == TORQUE_MODE_MED)
                torqueLim = AMK_MAX_TORQUE * 0.75;
            else
                torqueLim = AMK_MAX_TORQUE * 0.50;

            if (accelRequest > 0.0)
            {
                // Positive torque request
                data_.speeds = {
                    [FL] = AMK_MAX_RPM,
                    [FR] = AMK_MAX_RPM,
                    [RL] = AMK_MAX_RPM,
                    [RR] = AMK_MAX_RPM
                };
                data_.posTorqueLimits = {
                    [FL] = torqueRequest * frontTorqueScale_,
                    [FR] = torqueRequest * frontTorqueScale_,
                    [RL] = torqueRequest * rearTorqueScale_,
                    [RR] = torqueRequest * rearTorqueScale_
                };
                data_.negTorqueLimits = {
                    [FL] = 0.0,
                    [FR] = 0.0,
                    [RL] = 0.0,
                    [RR] = 0.0
                };
            }
            else
            {
                // Negative torque request
                torqueRequest = MAX_REGEN_TORQUE * torqueRequest * -1.0; // TODO: determine whether negative torque limits are signed
                data_.speeds = {
                    [FL] = 0.0,
                    [FR] = 0.0,
                    [RL] = 0.0,
                    [RR] = 0.0
                };
                data_.posTorqueLimits = {
                    [FL] = 0.0,
                    [FR] = 0.0,
                    [RL] = 0.0,
                    [RR] = 0.0
                };
                data_.negTorqueLimits = {
                    [FL] = torqueRequest,
                    [FR] = torqueRequest,
                    [RL] = torqueRequest,
                    [RR] = torqueRequest
                };
            }

            // Apply the torque limit
            TCPosTorqueLimit(
                data_,
                {
                    [FL] = torqueLim,
                    [FR] = torqueLim,
                    [RL] = torqueLim,
                    [RR] = torqueLim
                }
            )
        }
        else
        {
            // Both pedals are pressed or an implausibility has been detected
            // Zero out torque
            data_.speeds = {
                [FL] = 0.0,
                [FR] = 0.0,
                [RL] = 0.0,
                [RR] = 0.0
            };
            data_.posTorqueLimits = {
                [FL] = 0.0,
                [FR] = 0.0,
                [RL] = 0.0,
                [RR] = 0.0
            };
            data_.negTorqueLimits = {
                [FL] = 0.0,
                [FR] = 0.0,
                [RL] = 0.0,
                [RR] = 0.0
            };
        }
    }
}