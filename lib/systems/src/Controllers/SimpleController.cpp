#include "Controllers/SimpleController.h"

void TorqueControllerSimple::tick(const PedalsSystemData_s &pedalsData)
{

    // Both pedals are not pressed and no implausibility has been detected
    // accelRequest goes between 1.0 and -1.0
    float accelRequest = pedalsData.accelPercent - pedalsData.regenPercent;
    float torqueRequest;

    if (accelRequest >= 0.0)
    {
        // Positive torque request
        torqueRequest = accelRequest * PhysicalParameters::AMK_MAX_TORQUE;

        writeout_.command.speeds_rpm[FL] = PhysicalParameters::AMK_MAX_RPM;
        writeout_.command.speeds_rpm[FR] = PhysicalParameters::AMK_MAX_RPM;
        writeout_.command.speeds_rpm[RL] = PhysicalParameters::AMK_MAX_RPM;
        writeout_.command.speeds_rpm[RR] = PhysicalParameters::AMK_MAX_RPM;

        writeout_.command.inverter_torque_limit[FL] = torqueRequest * frontTorqueScale_;
        writeout_.command.inverter_torque_limit[FR] = torqueRequest * frontTorqueScale_;
        writeout_.command.inverter_torque_limit[RL] = torqueRequest * rearTorqueScale_;
        writeout_.command.inverter_torque_limit[RR] = torqueRequest * rearTorqueScale_;
    }
    else
    {
        // Negative torque request
        torqueRequest = PhysicalParameters::MAX_REGEN_TORQUE * accelRequest * -1.0;

        writeout_.command.speeds_rpm[FL] = 0.0;
        writeout_.command.speeds_rpm[FR] = 0.0;
        writeout_.command.speeds_rpm[RL] = 0.0;
        writeout_.command.speeds_rpm[RR] = 0.0;

        writeout_.command.inverter_torque_limit[FL] = torqueRequest * frontRegenTorqueScale_;
        writeout_.command.inverter_torque_limit[FR] = torqueRequest * frontRegenTorqueScale_;
        writeout_.command.inverter_torque_limit[RL] = torqueRequest * rearRegenTorqueScale_;
        writeout_.command.inverter_torque_limit[RR] = torqueRequest * rearRegenTorqueScale_;
    }
}

TorqueControllerOutput_s TorqueControllerSimple::evaluate(const SharedCarState_s &state)
{
    tick(state.pedals_data);
    return writeout_;
}