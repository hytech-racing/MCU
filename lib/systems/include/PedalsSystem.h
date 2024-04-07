#ifndef PEDALSSYSTEM
#define PEDALSSYSTEM
#include <math.h>
#include <tuple>
#include "AnalogSensorsInterface.h"

#include "SysClock.h"

/// @brief system interface struct that contains the data from the pedal system
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
struct PedalsParams
{
    int min_pedal_1;
    int min_pedal_2;
    int max_pedal_1;
    int max_pedal_2;
    float activation_percentage;
    float deadzone_margin;
    float implausibility_margin;
    float mechanical_activation_percentage;
};

class PedalsSystem
{
public:
    /// @brief pedals system class that evaluates pedals for both accel and
    ///        brake percent as well as implausibilities
    /// @param accelParams accel pedal parameters. by rules, 2 sensors must be used for redundancy and evaluated w.r.t each other
    /// @param brakeParams brake pedal params. when used with only one pedal sensor, the pedal parameter evaluation for brakes only looks at the min and max for min_pedal_1 / max_pedal_1
    PedalsSystem(const PedalsParams &accelParams,
                 const PedalsParams &brakeParams)
    {
        accelParams_ = accelParams;
        brakeParams_ = brakeParams;
        implausibilityStartTime_ = 0;
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
        return brakeParams_.mechanical_activation_percentage;
    }

    /// @brief overloaded tick function that runs the evaluation of the pedals system.
    ///        evaluates brake using only min and max params for sensor 1 (min_pedal_1 / max_pedal_1).
    /// @param tick current system time tick
    /// @param accel1 accel 1 sensor reading with scaled and offset value from 0 to 1
    /// @param accel2 accel 2 sensor reading with scaled and offset value from 0 to 1
    /// @param brake brake sensor reading with scaled and offset value from 0 to 1
    void tick(const SysTick_s &tick,
              const AnalogConversion_s &accel1,
              const AnalogConversion_s &accel2,
              const AnalogConversion_s &brake);

    /// @brief
    /// @param tick
    /// @param accel1
    /// @param accel2
    /// @param brake1
    /// @param brake2
    void tick(const SysTick_s &tick,
              const AnalogConversion_s &accel1,
              const AnalogConversion_s &accel2,
              const AnalogConversion_s &brake1,
              const AnalogConversion_s &brake2);

    /// @brief
    /// @param accel1
    /// @param accel2
    /// @param brake1
    /// @param brake2
    /// @param curr_time
    /// @return
    PedalsSystemData_s evaluate_pedals(const AnalogConversion_s &accel1,
                                       const AnalogConversion_s &accel2,
                                       const AnalogConversion_s &brake1,
                                       const AnalogConversion_s &brake2,
                                       unsigned long curr_time);
    /// @brief
    /// @param accel1
    /// @param accel2
    /// @param brake
    /// @param curr_time
    /// @return
    PedalsSystemData_s evaluate_pedals(const AnalogConversion_s &accel1,
                                       const AnalogConversion_s &accel2,
                                       const AnalogConversion_s &brake,
                                       unsigned long curr_time);

private:
    PedalsSystemData_s data_{};
    PedalsParams accelParams_{};
    PedalsParams brakeParams_{};
    unsigned long implausibilityStartTime_;

    float remove_deadzone_(float conversion_input, float deadzone);
    bool max_duration_of_implausibility_exceeded_(unsigned long curr_time);

    /// @brief
    ///    Evaluate pedal implausibilities_ determines if there is a software implausibility
    ///    in the pedals caused by them going out of range.
    ///    Our max/min sensor ranges are calcuated from the pedal min/max values
    ///    The pedal min/max values are defined in MCU_defs and are the real world raw
    ///    values that we determine from the pedal output.
    ///    The max/min sensor values are then a certain percent higher than these real world
    ///    values as determined by the implausibility margin. This protects against physical
    ///    damage to the sensor or pedal, but will not accidentally trip implausibility if
    ///    pedal values fluctuate

    /// @param pedalData1
    /// @param pedalData2
    /// @param params
    /// @param max_percent_diff
    /// @return
    bool evaluate_pedal_implausibilities_(const AnalogConversion_s &pedalData1,
                                          const AnalogConversion_s &pedalData2,
                                          const PedalsParams &params,
                                          float max_percent_diff);

    /// @brief overloaded pedal implaus check that doesnt need to check for percent diff between sensors since only one sensor
    /// @param pedalData
    /// @param params
    /// @return
    bool evaluate_pedal_implausibilities_(const AnalogConversion_s &pedalData, const PedalsParams &params);

    /// @brief function to determine if the pedals and the brakes are pressed at the same time.
    ///        evaluates brake being pressed with mech brake activation threshold AFTER removing
    ///        deadzones for both brake and accel
    /// @param accelPedalData1
    /// @param accelPedalData2
    /// @param brakePedalData1
    /// @param brakePedalData2
    /// @return true if accel and brake pressed at the same time, false otherwise
    bool evaluate_brake_and_accel_pressed_(const AnalogConversion_s &accelPedalData1,
                                           const AnalogConversion_s &accelPedalData2,
                                           const AnalogConversion_s &brakePedalData1,
                                           const AnalogConversion_s &brakePedalData2);

    /// @brief overloaded version that evaluates with only one brake pedal value
    /// @param accelPedalData1
    /// @param accelPedalData2
    /// @param brakePedalData
    /// @return
    bool evaluate_brake_and_accel_pressed_(const AnalogConversion_s &accelPedalData1,
                                           const AnalogConversion_s &accelPedalData2,
                                           const AnalogConversion_s &brakePedalData);
    /// @brief
    /// @param pedalData
    /// @param min
    /// @param max
    /// @param implaus_margin_scale
    /// @return
    bool evaluate_min_max_pedal_implausibilities_(const AnalogConversion_s &pedalData,
                                                  int min,
                                                  int max,
                                                  float implaus_margin_scale);

    bool pedal_is_active_(float pedal1ConvertedData, float pedal2ConvertedData, float percent_threshold);
};

#endif /* PEDALSSYSTEM */
