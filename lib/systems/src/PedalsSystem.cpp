#include <PedalsSystem.h>

void PedalsSystem::tick(const SysTick_s &tick, const AnalogConversion_s &accel1, const AnalogConversion_s &accel2, const AnalogConversion_s &brake1, const AnalogConversion_s &brake2)
{
    float accelAverage = (accel1.conversion + accel2.conversion) / 2.0;
    float brakeAverage = (brake1.conversion + brake2.conversion) / 2.0;

    bool accelInRange1 = (accel1.raw < parameters_.pedalsRawTooHigh) && (accel1.raw > parameters_.pedalsRawTooLow);
    bool accelInRange2 = (accel2.raw < parameters_.pedalsRawTooHigh) && (accel2.raw > parameters_.pedalsRawTooLow);
    bool brakeInRange1 = (brake1.raw < parameters_.pedalsRawTooHigh) && (brake1.raw > parameters_.pedalsRawTooLow);
    bool brakeInRange2 = (brake2.raw < parameters_.pedalsRawTooHigh) && (brake2.raw > parameters_.pedalsRawTooLow);

    if (accelInRange1 && accelInRange2)
        data_.accelPercent = accelAverage;
    else if (accelInRange1)
        data_.accelPercent = accel1.conversion;
    else if (accelInRange2)
        data_.accelPercent = accel2.conversion;
    else
        data_.accelPercent = 0.0;

    if (brakeInRange1 && brakeInRange2)
        data_.brakePercent = brakeAverage;
    else if (brakeInRange1)
        data_.brakePercent = brake1.conversion;
    else if (brakeInRange2)
        data_.brakePercent = brake2.conversion;
    else
        data_.brakePercent = 0.0;

    // Check instantaneous implausibility
    // T.4.2.4
    // T.4.2.10
    float accelDeviation = abs(accel1.conversion - accel2.conversion) / accelAverage;
    if ((accelDeviation >= parameters_.pedalsImplausiblePercent) || !accelInRange1 || !accelInRange2)
    {
        data_.accelStatus = PEDALS_IMPLAUSIBLE;
    }
    else if (accelDeviation >= parameters_.pedalsMarginalPercent && accelDeviation < parameters_.pedalsImplausiblePercent)
    {
        data_.accelStatus = PEDALS_MARGINAL;
    }
    else
    {
        data_.accelStatus = PEDALS_NOMINAL;
    }

    float brakeDeviation = abs(brake1.conversion - brake2.conversion) / brakeAverage;
    if ((brakeDeviation >= parameters_.pedalsImplausiblePercent) || !brakeInRange1 || !brakeInRange2)
    {
        data_.brakeStatus = PEDALS_IMPLAUSIBLE;
    }
    else if (brakeDeviation >= parameters_.pedalsMarginalPercent && brakeDeviation < parameters_.pedalsImplausiblePercent)
    {
        data_.brakeStatus = PEDALS_MARGINAL;
    }
    else
    {
        data_.brakeStatus = PEDALS_NOMINAL;
    }

    // Check if both pedals are pressed
    bool accelPressed = data_.accelPercent > parameters_.accelPressedThreshold;
    bool brakePressed = data_.brakePercent > parameters_.brakePressedThreshold;
    if (accelPressed && brakePressed)
        data_.pedalsCommand = PEDALS_BOTH_PRESSED;
    else if (accelPressed)
        data_.pedalsCommand = PEDALS_ACCEL_PRESSED;
    else if (brakePressed)
        data_.pedalsCommand = PEDALS_BRAKE_PRESSED;
    else
        data_.pedalsCommand = PEDALS_NONE_PRESSED;

    // Check for persistent implausibility
    if ((data_.accelStatus == PEDALS_IMPLAUSIBLE) || (data_.brakeStatus == PEDALS_IMPLAUSIBLE))
    {
        if (implausibilityDetectedTime_ == 0)
            implausibilityDetectedTime_ = tick.millis;
        if (tick.millis - implausibilityDetectedTime_ >= PEDALS_IMPLAUSIBLE_DURATION)
            data_.persistentImplausibilityDetected = true;
    }
    else
    {
        implausibilityDetectedTime_ = 0;
        data_.persistentImplausibilityDetected = false;
    }
}
