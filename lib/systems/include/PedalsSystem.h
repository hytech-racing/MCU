#ifndef PEDALSSYSTEM
#define PEDALSSYSTEM
#include <math.h>
#include <tuple>
#include "AnalogSensorsInterface.h"

#include "SysClock.h"

struct PedalsSystemData_s
{

    bool accelImplausible : 1;
    bool brakeImplausible : 1;
    bool brakePressed : 1;
    bool mechBrakeActive : 1;
    bool brakeAndAccelPressedImplausibility : 1;
    bool implausibilityExceededMaxDuration : 1;
    float accelPercent;
    float brakePercent;
    float regenPercent;
};

/// @brief Pedals params struct that will hold min / max that will be used for evaluateion.
//          NOTE: min and max may be need to be flipped depending on the sensor. (looking at you brake pedal sensor 2)
struct PedalsParams
{
    int min_pedal_1;
    int min_pedal_2;
    int max_pedal_1;
    int max_pedal_2;
    float activation_percentage;
    float deadzone_margin;
    float implausibility_margin;
};

class PedalsSystem
{
public:
    
    PedalsSystem(const PedalsParams &accelParams,
                 const PedalsParams &brakeParams,
                 float mechBrakeActiveThreshold)
    {
        accelParams_ = accelParams;
        brakeParams_ = brakeParams;
        implausibilityStartTime_ = 0;
        mechBrakeActiveThreshold_ = mechBrakeActiveThreshold;
        // Setting of min and maxes for pedals via config file
    }

    const PedalsSystemData_s &getPedalsSystemData()
    {
        return data_;
    }

    PedalsSystemData_s getPedalsSystemDataCopy()
    {
        return data_;
    }

    float getMechBrakeActiveThreshold()
    {
        return mechBrakeActiveThreshold_;
    }

    void tick(const SysTick_s &tick,
              const AnalogConversion_s &accel1,
              const AnalogConversion_s &accel2,
              const AnalogConversion_s &brake1,
              const AnalogConversion_s &brake2);

    PedalsSystemData_s evaluate_pedals(const AnalogConversion_s &accel1,
                                       const AnalogConversion_s &accel2,
                                       const AnalogConversion_s &brake1,
                                       const AnalogConversion_s &brake2,
                                       unsigned long curr_time);

private:
    PedalsSystemData_s data_;
    float remove_deadzone_(float conversion_input, float deadzone);
    bool max_duration_of_implausibility_exceeded_(unsigned long curr_time);

    /*
        Evaluate pedal implausibilities_ determines if there is a software implausibility
        in the pedals caused by them going out of range.

        Our max/min sensor ranges are calcuated from the pedal min/max values
        The pedal min/max values are defined in MCU_defs and are the real world raw
        values that we determine from the pedal output.

        The max/min sensor values are then a certain percent higher than these real world
        values as determined by the implausibility margin. This protects against physical
        damage to the sensor or pedal, but will not accidentally trip implausibility if 
        pedal values fluctuate
    */
    bool evaluate_pedal_implausibilities_(const AnalogConversion_s &pedalData1,
                                          const AnalogConversion_s &pedalData2,
                                          const PedalsParams &params,
                                          float max_percent_diff);

    bool evaluate_pedal_implausibilities_(const AnalogConversion_s &pedalData1,
                                          const PedalsParams &params,
                                          float max_percent_diff);

    bool evaluate_brake_and_accel_pressed_(const AnalogConversion_s &accelPedalData1,
                                           const AnalogConversion_s &accelPedalData2,
                                           const AnalogConversion_s &brakePedalData1,
                                           const AnalogConversion_s &brakePedalData2);
    bool pedal_is_active_(float pedal1ConvertedData, float pedal2ConvertedData, float percent_threshold);
    PedalsParams accelParams_;
    PedalsParams brakeParams_;
    float mechBrakeActiveThreshold_;
    unsigned long implausibilityStartTime_;
};

#endif /* PEDALSSYSTEM */
