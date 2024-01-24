#ifndef __PEDALSSYSTEM_H__
#define __PEDALSSYSTEM_H__
#include <math.h>
#include <tuple>

#include "AnalogSensorsInterface.h"

// Definitions
#define PEDALS_IMPLAUSIBLE_DURATION 100         // Implausibility must be caught within 100ms
#define PEDALS_IMPLAUSIBLE_PERCENT 0.10         // 10% allowed deviation FSAE T.4.2.4
#define PEDALS_MARGINAL_PERCENT 0.07            // Report pedals are marginal. Allows us to detect pedals may need recalibration
#define PEDALS_RAW_TOO_LOW (0.5 / 5 * 4096)     // FSAE T.4.2.10 Pedals are implausible below 0.5V raw reading
#define PEDALS_RAW_TOO_HIGH (4.5 / 5 * 4096)    // FSAE T.4.2.10 Pedals are implausible above 4.5V raw reading

// Enums
enum PedalsStatus_e
{
    PEDALS_NOMINAL = 0,
    PEDALS_MARGINAL = 1,
    PEDALS_IMPLAUSIBLE = 2,
};

enum PedalsCommanded_e
{
    PEDALS_NONE_PRESSED = 0,
    PEDALS_ACCEL_PRESSED = 1,
    PEDALS_BRAKE_PRESSED = 2,
    PEDALS_BOTH_PRESSED = 3,
};

struct PedalsSystemOutput_s
{
    PedalsCommanded_e pedalsCommand;
    PedalsStatus_e accelStatus;
    PedalsStatus_e brakeStatus;
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
    PedalsSystemParameters_s parameters;
    long implausibilityDetectedTime;
public:
// Constructors
    PedalsSystem(PedalsSystemParameters_s* parametersExt)
    {
        parameters = *parametersExt;
    }
    PedalsSystem()
    {
        parameters = {
            .pedalsImplausiblePercent = PEDALS_IMPLAUSIBLE_PERCENT,
            .pedalsMarginalPercent = PEDALS_MARGINAL_PERCENT,
            .pedalsRawTooLow = PEDALS_RAW_TOO_LOW,
            .pedalsRawTooHigh = PEDALS_RAW_TOO_HIGH,
        };
    }

// Functions
    PedalsSystemOutput_s evaluate(
        AnalogConversion_s* accel1,
        AnalogConversion_s* accel2,
        AnalogConversion_s* brake1,
        AnalogConversion_s* brake2
    );
};

#endif /* __PEDALSSYSTEM_H__ */

