#include "PedalsSystem.h"
#include <iostream>

#include <algorithm>

// TODO parameterize percentages in constructor
void PedalsSystem::tick(const SysTick_s &tick, const AnalogConversion_s &accel1, const AnalogConversion_s &accel2, const AnalogConversion_s &brake1, const AnalogConversion_s &brake2)
{
    data_ = evaluate_pedals(accel1, accel2, brake1, brake2, tick.millis);
}

void PedalsSystem::tick(const SysTick_s &tick, const AnalogConversion_s &accel1, const AnalogConversion_s &accel2, const AnalogConversion_s &brake)
{
    data_ = evaluate_pedals(accel1, accel2, brake, tick.millis);
}


// TODO make it to where only when the pedal is released fully that the implausibility clears


PedalsSystemData_s PedalsSystem::evaluate_pedals(const AnalogConversion_s &accel1,
                                                 const AnalogConversion_s &accel2,
                                                 const AnalogConversion_s &brake,
                                                 unsigned long curr_time)
{
    PedalsSystemData_s out;

    out.accelPercent = ((accel1.conversion + accel2.conversion) / 2.0);
    out.accelPercent = remove_deadzone_(out.accelPercent, accelParams_.deadzone_margin);
    out.accelPercent = std::max(out.accelPercent, 0.0f);
    out.accelImplausible = evaluate_pedal_implausibilities_(accel1, accel2, accelParams_, 0.1);
    out.brakeImplausible = evaluate_pedal_implausibilities_(brake, brakeParams_);
    out.brakeAndAccelPressedImplausibility = evaluate_brake_and_accel_pressed_(accel1, accel2, brake);
    bool implausibility = (out.brakeAndAccelPressedImplausibility || out.brakeImplausible || out.accelImplausible);

    if (implausibility && (implausibilityStartTime_ == 0))
    {
        implausibilityStartTime_ = curr_time;
    }
    else if ((!implausibility) && (!(out.accelPercent > 0.05)))
    {
        implausibilityStartTime_ = 0;
    }

    
    out.brakePercent = brake.conversion;
    out.brakePercent = remove_deadzone_(out.brakePercent, brakeParams_.deadzone_margin);

    out.mechBrakeActive = out.brakePercent >= brakeParams_.mechanical_activation_percentage;
    out.regenPercent = std::max(std::min(out.brakePercent / brakeParams_.mechanical_activation_percentage, 1.0f), 0.0f);
    out.brakePressed = out.brakePercent > brakeParams_.activation_percentage;

    
    out.implausibilityExceededMaxDuration = max_duration_of_implausibility_exceeded_(curr_time);
    return out;
}

PedalsSystemData_s PedalsSystem::evaluate_pedals(const AnalogConversion_s &accel1,
                                                 const AnalogConversion_s &accel2,
                                                 const AnalogConversion_s &brake1,
                                                 const AnalogConversion_s &brake2,
                                                 unsigned long curr_time)
{

    PedalsSystemData_s out;
    out.accelPressed = pedal_is_active_(accel1.conversion, accel2.conversion, accelParams_, false);
    out.accelImplausible = evaluate_pedal_implausibilities_(accel1, accel2, accelParams_, 0.1);
    
    out.accelPercent = (accel1.conversion + accel2.conversion) / 2.0;
    out.accelPercent = remove_deadzone_(out.accelPercent, accelParams_.deadzone_margin);
    out.accelPercent = std::max(out.accelPercent, 0.0f);
    

    out.brakeImplausible = evaluate_pedal_implausibilities_(brake1, brake2, brakeParams_, 0.25);
    out.brakeAndAccelPressedImplausibility = evaluate_brake_and_accel_pressed_(accel1, accel2, brake1, brake2);
    bool implausibility = (out.brakeAndAccelPressedImplausibility || out.brakeImplausible || out.accelImplausible);

    if (implausibility && (implausibilityStartTime_ == 0))
    {
        implausibilityStartTime_ = curr_time;
    }
    else if ((!implausibility) && (!(out.accelPercent > 0.05)))
    {
        implausibilityStartTime_ = 0;
    }

    
    out.brakePercent = (brake1.conversion + brake2.conversion) / 2.0;
    
    out.brakePercent = remove_deadzone_(out.brakePercent, brakeParams_.deadzone_margin);

    out.regenPercent = std::max(std::min(out.brakePercent / brakeParams_.mechanical_activation_percentage, 1.0f), 0.0f);
    
    out.brakePressed = pedal_is_active_(brake1.conversion, brake2.conversion, brakeParams_, false);
    out.mechBrakeActive = pedal_is_active_(brake1.conversion, brake2.conversion, brakeParams_, true);
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

// only checks implaus based on first min / max
bool PedalsSystem::evaluate_pedal_implausibilities_(const AnalogConversion_s &pedalData, const PedalsParams &params)
{
    return evaluate_min_max_pedal_implausibilities_(pedalData, params.min_pedal_1, params.max_pedal_1, params.implausibility_margin);
}

bool PedalsSystem::evaluate_pedal_implausibilities_(const AnalogConversion_s &pedalData1,
                                                    const AnalogConversion_s &pedalData2,
                                                    const PedalsParams &params,
                                                    float max_percent_diff)
{
    bool pedal1_min_max_implaus = evaluate_min_max_pedal_implausibilities_(pedalData1, params.min_pedal_1, params.max_pedal_1, params.implausibility_margin);
    bool pedal2_min_max_implaus = evaluate_min_max_pedal_implausibilities_(pedalData2, params.min_pedal_2, params.max_pedal_2, params.implausibility_margin);
    bool sens_not_within_req_percent = (fabs(pedalData1.conversion - pedalData2.conversion) > max_percent_diff);
    if (pedal2_min_max_implaus || pedal2_min_max_implaus)
    {
        return true;
    }
    else if (sens_not_within_req_percent)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PedalsSystem::evaluate_min_max_pedal_implausibilities_(const AnalogConversion_s &pedalData,
                                                            int min,
                                                            int max,
                                                            float implaus_margin_scale)
{

    bool pedal_swapped = false;

    // get the pedal margin. The margin will be a percentage of the range of the measured max values
    int pedal_margin = abs(max - min) * implaus_margin_scale;

    if (min > max)
    {
        pedal_swapped = true;
        // swap the logic: need to check and see if it is greater than min and less than max
    }
    // FSAE EV.5.5
    // FSAE T.4.2.10
    bool pedal_less_than_min = pedal_swapped ? (pedalData.raw > (min + pedal_margin))
                                             : (pedalData.raw < (min - pedal_margin));

    bool pedal_greater_than_max = pedal_swapped ? (pedalData.raw < (max - pedal_margin))
                                                : (pedalData.raw > (max + pedal_margin));

    if (pedal_less_than_min)
    {
        return true;
    }
    else if (pedal_greater_than_max)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float PedalsSystem::remove_deadzone_(float conversion_input, float deadzone)
{
    float range = 1.0 - (deadzone * 2);
    // e.g. vals from 0 to 1, deadzone is .05, range is .1
    // subtract deadzone to be -.05 to .95 & clamp at 0
    float out = std::max(conversion_input - deadzone, 0.0f);
    // values now are 0 to .95
    // divide by range of values to scale up (.9)
    out /= range;
    // values are now 0 to 1.0555...
    // clamp at 0 to 1
    out = std::min(out, 1.0f);

    return out;
}

bool PedalsSystem::evaluate_brake_and_accel_pressed_(const AnalogConversion_s &accelPedalData1,
                                                     const AnalogConversion_s &accelPedalData2,
                                                     const AnalogConversion_s &brakePedalData)
{

    
    
    bool accel_pressed = pedal_is_active_(accelPedalData1.conversion, accelPedalData2.conversion, accelParams_, false); // .1
    float brake_pedal_real = remove_deadzone_(brakePedalData.conversion, brakeParams_.deadzone_margin);
    bool mech_brake_pressed = brake_pedal_real >= brakeParams_.mechanical_activation_percentage;
    bool both_pedals_implausible = (accel_pressed && mech_brake_pressed);
    return both_pedals_implausible;
}

bool PedalsSystem::evaluate_brake_and_accel_pressed_(const AnalogConversion_s &accelPedalData1,
                                                     const AnalogConversion_s &accelPedalData2,
                                                     const AnalogConversion_s &brakePedalData1,
                                                     const AnalogConversion_s &brakePedalData2)
{


    bool accel_pressed = pedal_is_active_(accelPedalData1.conversion, accelPedalData2.conversion, accelParams_, false); // .1
    bool mech_brake_pressed = pedal_is_active_(brakePedalData1.conversion, brakePedalData2.conversion, brakeParams_, true);  // 0.40
    
    
    bool both_pedals_implausible = (accel_pressed && mech_brake_pressed);
    return both_pedals_implausible;
}

bool PedalsSystem::pedal_is_active_(float pedal1ConvertedData, float pedal2ConvertedData, const PedalsParams& params, bool check_mech_activation)
{
    float val1_deadzone_removed = remove_deadzone_(pedal1ConvertedData, params.deadzone_margin);
    float val2_deadzone_removed = remove_deadzone_(pedal2ConvertedData, params.deadzone_margin);
    bool pedal_1_is_active;
    bool pedal_2_is_active;
    if(check_mech_activation)
    {
        pedal_1_is_active = val1_deadzone_removed >= params.mechanical_activation_percentage;
        pedal_2_is_active = val2_deadzone_removed >= params.mechanical_activation_percentage;
    } else {
        pedal_1_is_active = val1_deadzone_removed >= params.activation_percentage;
        pedal_2_is_active = val2_deadzone_removed >= params.activation_percentage;
    }
    return (pedal_1_is_active || pedal_2_is_active);
}