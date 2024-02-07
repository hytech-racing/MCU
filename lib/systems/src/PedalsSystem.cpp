#include "PedalsSystem.h"

// TODO parameterize percentages in constructor
void PedalsSystem::tick(const SysTick_s &tick, const AnalogConversion_s &accel1, const AnalogConversion_s &accel2, const AnalogConversion_s &brake1, const AnalogConversion_s &brake2)
{
    data_ = evaluate_pedals(accel1, accel2, brake1, brake2, tick.millis);
}
PedalsSystemData_s PedalsSystem::evaluate_pedals(const AnalogConversion_s &accel1,
                                                 const AnalogConversion_s &accel2,
                                                 const AnalogConversion_s &brake1,
                                                 const AnalogConversion_s &brake2,
                                                 unsigned long curr_time)
{
    PedalsSystemData_s out;
    out.accelImplausible = evaluate_pedal_implausibilities_(accel1, accel2, accelParams_, 0.1);
    out.brakeImplausible = evaluate_pedal_implausibilities_(brake1, brake2, brakeParams_, 0.25);
    out.brakeAndAccelPressedImplausibility = evaluate_brake_and_accel_pressed_(accel1, accel2, brake1, brake2);
    bool implausibility = (out.brakeAndAccelPressedImplausibility || out.brakeImplausible || out.accelImplausible);

    if (implausibility && (implausibilityStartTime_ == 0))
    {
        implausibilityStartTime_ = curr_time;
    }
    else if (!implausibility)
    {
        implausibilityStartTime_ = 0;
    }

    out.accelPercent = (accel1.conversion + accel2.conversion) / 2.0;
    out.brakePercent = (brake1.conversion + brake2.conversion) / 2.0;
    out.brakePressed = pedal_is_active_(brake1.conversion, brake2.conversion, brakeParams_.activation_percentage);
    out.implausibilityExceededMaxDuration = max_duration_of_implausibility_exceeded_(curr_time);
    return out;
}

// TODO parameterize duration in constructor
bool PedalsSystem::max_duration_of_implausibility_exceeded_(unsigned long curr_time)
{
    if (implausibilityStartTime_ != 0)
    {
        return ((curr_time - implausibilityStartTime_) > 100);
    }
    else
    {
        return false;
    }
}

bool PedalsSystem::evaluate_pedal_implausibilities_(const AnalogConversion_s &pedalData1,
                                                    const AnalogConversion_s &pedalData2,
                                                    const PedalsParams &params,
                                                    float max_percent_diff)
{
    // FSAE EV.5.5
    // FSAE T.4.2.10
    bool pedal_1_less_than_min = (pedalData1.raw < params.min_sense_1);
    bool pedal_2_less_than_min = (pedalData2.raw < params.min_sense_2);
    bool pedal_1_greater_than_max = (pedalData1.raw > params.max_sense_1);
    bool pedal_2_greater_than_max = (pedalData2.raw > params.max_sense_2);

    // check that the pedals are reading within 10% of each other
    // T.4.2.4
    bool sens_not_within_req_percent = (fabs(pedalData1.conversion - pedalData2.conversion) > max_percent_diff);

    bool pedalsClamped = (pedalData1.status == AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED || pedalData2.status == AnalogSensorStatus_e::ANALOG_SENSOR_CLAMPED);
    if (
        pedal_1_less_than_min ||
        pedal_2_less_than_min ||
        pedal_1_greater_than_max ||
        pedal_2_greater_than_max)
    {
        return true;
    }
    else if (sens_not_within_req_percent || pedalsClamped)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PedalsSystem::evaluate_brake_and_accel_pressed_(const AnalogConversion_s &accelPedalData1,
                                                     const AnalogConversion_s &accelPedalData2,
                                                     const AnalogConversion_s &brakePedalData1,
                                                     const AnalogConversion_s &brakePedalData2)
{

    bool accel_pressed = pedal_is_active_(accelPedalData1.conversion, accelPedalData2.conversion, accelParams_.activation_percentage); // .1
    bool brake_pressed = pedal_is_active_(brakePedalData2.conversion, brakePedalData1.conversion, brakeParams_.activation_percentage); // 0.05

    return (accel_pressed && brake_pressed);
}

bool PedalsSystem::pedal_is_active_(float pedal1ConvertedData, float pedal2ConvertedData, float percent_threshold)
{
    bool pedal_1_is_active = pedal1ConvertedData >= percent_threshold;
    bool pedal_2_is_active = pedal2ConvertedData >= percent_threshold;

    return (pedal_1_is_active || pedal_2_is_active);
}