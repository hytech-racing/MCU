#ifndef PEDALSSYSTEM
#define PEDALSSYSTEM
#include <math.h>
#include <tuple>
#include "AnalogSensorsInterface.h"

#include "SysClock.h"
struct PedalsSystemData_s
{

    bool accelImplausible;
    bool brakeImplausible;
    bool brakePressed;
    bool brakeAndAccelPressedImplausibility;
    bool implausibilityExceededMaxDuration;
    float accelPercent;
    float brakePercent;
};

/// @brief Pedals params struct that will hold min / max that will be used for evaluateion.
//          NOTE: min and max may be need to be flipped depending on the sensor. (looking at you brake pedal sensor 2)
struct PedalsParams
{
    int min_sense_1;
    int min_sense_2;
    int max_sense_1;
    int max_sense_2;
    float activation_percentage;
};

class PedalsSystem
{
public:
    const PedalsSystemData_s &getPedalsSystemData()
    {
        return data_;
    }
    PedalsSystem(const PedalsParams &accelParams, const PedalsParams &brakeParams)
    {
        accelParams_ = accelParams;
        brakeParams_ = brakeParams;
        implausibilityStartTime_=0;
        // Setting of min and maxes for pedals via config file
    };
    
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

    bool max_duration_of_implausibility_exceeded_(unsigned long curr_time);
    bool evaluate_pedal_implausibilities_(const AnalogConversion_s &pedalData1,
                                          const AnalogConversion_s &pedalData2,
                                          const PedalsParams &params,
                                          float max_percent_diff);

    bool evaluate_brake_and_accel_pressed_(const AnalogConversion_s &accelPedalData1,
                                           const AnalogConversion_s &accelPedalData2,
                                           const AnalogConversion_s &brakePedalData1,
                                           const AnalogConversion_s &brakePedalData2);
    bool pedal_is_active_(float pedal1ConvertedData, float pedal2ConvertedData, float percent_threshold);
    PedalsParams accelParams_;
    PedalsParams brakeParams_;
    unsigned long implausibilityStartTime_;
};

#endif /* PEDALSSYSTEM */
