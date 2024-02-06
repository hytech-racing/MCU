#ifndef __PEDALSSYSTEM_H__
#define __PEDALSSYSTEM_H__
#include <math.h>
#include <tuple>

#include "AnalogSensorsInterface.h"
#include <SysClock.h>

// Definitions
const int PEDALS_IMPLAUSIBLE_DURATION   = 100;                  // Implausibility must be caught within 100ms
const float PEDALS_IMPLAUSIBLE_PERCENT  = 0.10;                 // 10% allowed deviation FSAE T.4.2.4
const float PEDALS_MARGINAL_PERCENT     = 0.07;                 // Report pedals are marginal. Allows us to detect pedals may need recalibration
const float PEDALS_RAW_TOO_LOW          = 0.5 / 5 * 4096;       // FSAE T.4.2.10 Pedals are implausible below 0.5V raw reading
const float PEDALS_RAW_TOO_HIGH         = 4.5 / 5 * 4096;       // FSAE T.4.2.10 Pedals are implausible above 4.5V raw reading

// Enums
enum class PedalsStatus_e
{
    PEDALS_NOMINAL = 0,
    PEDALS_MARGINAL = 1,
    PEDALS_IMPLAUSIBLE = 2,
};

enum class PedalsCommanded_e
{
    PEDALS_NONE_PRESSED = 0,
    PEDALS_ACCEL_PRESSED = 1,
    PEDALS_BRAKE_PRESSED = 2,
    PEDALS_BOTH_PRESSED = 3,
};

struct PedalsSystemData_s
{
    PedalsCommanded_e pedalsCommand;
    PedalsStatus_e accelStatus;
    PedalsStatus_e brakeStatus;
    bool implausibilityExceededMaxDuration;
    bool persistentImplausibilityDetected;
    float accelPercent;
    float brakePercent;
};

struct PedalsSystemParameters_s
{
    float pedalsImplausiblePercent;
    float pedalsMarginalPercent;
    float pedalsRawTooLow;
    float pedalsRawTooHigh;
    float accelPressedThreshold = 0.10;
    float brakePressedThreshold = 0.05;
};

class PedalsSystem
{
private:
// Data
    PedalsSystemParameters_s parameters_;
    int implausibilityDetectedTime_;
    PedalsSystemData_s data_;

    bool evaluate_brake_and_accel_pressed_();

    bool pedal_is_active_(int sense_1, int sense_2, const PedalsSystemParameters_s &pedalParams, float percent_threshold);

public:
// Constructors
    PedalsSystem(PedalsSystemParameters_s* parametersExt)
    {
        parameters_ = *parametersExt;
    }
    PedalsSystem()
    {
        parameters_.pedalsImplausiblePercent = PEDALS_IMPLAUSIBLE_PERCENT;
        parameters_.pedalsMarginalPercent = PEDALS_MARGINAL_PERCENT;
        parameters_.pedalsRawTooLow = PEDALS_RAW_TOO_LOW;
        parameters_.pedalsRawTooHigh = PEDALS_RAW_TOO_HIGH;
        parameters_.accelPressedThreshold = 0.1;
        parameters_.brakePressedThreshold = 0.05;
        
    }

// Functions
    
    // bool max_duration_of_implausibility_exceeded(unsigned long t);
    void tick(
        const SysTick_s &sysClock, 
        const AnalogConversion_s &accel1, 
        const AnalogConversion_s &accel2, 
        const AnalogConversion_s &brake1, 
        const AnalogConversion_s &brake2
    );
    const PedalsSystemData_s& getPedalsSystemData()
    {
        return data_;
    }
};

#endif /* __PEDALSSYSTEM_H__ */

