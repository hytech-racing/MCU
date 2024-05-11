#include "SimpleController.h"

void TorqueControllerSimple::tick(const SysTick_s &tick, const PedalsSystemData_s &pedalsData)
{

    // Calculate torque commands at 100hz
    if (tick.triggers.trigger100)
    {
        // Both pedals are not pressed and no implausibility has been detected
        // accelRequest goes between 1.0 and -1.0
        float accelRequest = pedalsData.accelPercent - pedalsData.regenPercent;
        float torqueRequest;

        if (accelRequest >= 0.0)
        {
            // Positive torque request
            torqueRequest = accelRequest * PhysicalParameters::AMK_MAX_TORQUE;

            // writeout_.command.speeds_rpm[FL] = accelRequest * PhysicalParameters::AMK_MAX_RPM;
            // writeout_.command.speeds_rpm[FR] = accelRequest * PhysicalParameters::AMK_MAX_RPM;pid_input_
            // writeout_.command.speeds_rpm[RL] = accelRequest * PhysicalParameters::AMK_MAX_RPM;
            // writeout_.command.speeds_rpm[RR] = accelRequest * PhysicalParameters::AMK_MAX_RPM;
            writeout_.command.speeds_rpm[FL] = PhysicalParameters::AMK_MAX_RPM;
            writeout_.command.speeds_rpm[FR] = PhysicalParameters::AMK_MAX_RPM;
            writeout_.command.speeds_rpm[RL] = PhysicalParameters::AMK_MAX_RPM;
            writeout_.command.speeds_rpm[RR] = PhysicalParameters::AMK_MAX_RPM;

            writeout_.command.torqueSetpoints[FL] = torqueRequest * frontTorqueScale_;
            writeout_.command.torqueSetpoints[FR] = torqueRequest * frontTorqueScale_;
            writeout_.command.torqueSetpoints[RL] = torqueRequest * rearTorqueScale_;
            writeout_.command.torqueSetpoints[RR] = torqueRequest * rearTorqueScale_;
        }
        else
        {
            // Negative torque request
            torqueRequest = PhysicalParameters::MAX_REGEN_TORQUE * accelRequest * -1.0;

            writeout_.command.speeds_rpm[FL] = 0.0;
            writeout_.command.speeds_rpm[FR] = 0.0;
            writeout_.command.speeds_rpm[RL] = 0.0;
            writeout_.command.speeds_rpm[RR] = 0.0;

            writeout_.command.torqueSetpoints[FL] = torqueRequest * frontRegenTorqueScale_;
            writeout_.command.torqueSetpoints[FR] = torqueRequest * frontRegenTorqueScale_;
            writeout_.command.torqueSetpoints[RL] = torqueRequest * rearRegenTorqueScale_;
            writeout_.command.torqueSetpoints[RR] = torqueRequest * rearRegenTorqueScale_;
        }
    }
}

TorqueControllerOutput_s TorqueControllerSimple::evaluate(const car_state &state)
{
    tick(state.systick, state.pedals_data);
    return writeout_;
}