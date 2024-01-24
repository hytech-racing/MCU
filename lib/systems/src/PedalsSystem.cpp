#include <Arduino.h>
#include <PedalsSystem.h>

PedalsSystemOutput_s PedalsSystem::evaluate(AnalogConversion_s* accel1, AnalogConversion_s* accel2, AnalogConversion_s* brake1, AnalogConversion_s* brake2)
{
    PedalsSystemOutput_s output;

    float accelAverage = (accel1->conversion + accel2->conversion) / 2.0;
    float brakeAverage = (brake1->conversion + brake2->conversion) / 2.0;

    bool accelInRange1 = (accel1->raw < parameters.pedalsRawTooHigh) && (accel1->raw > parameters.pedalsRawTooLow);
    bool accelInRange2 = (accel2->raw < parameters.pedalsRawTooHigh) && (accel2->raw > parameters.pedalsRawTooLow);
    bool brakeInRange1 = (brake1->raw < parameters.pedalsRawTooHigh) && (brake1->raw > parameters.pedalsRawTooLow);
    bool brakeInRange2 = (brake2->raw < parameters.pedalsRawTooHigh) && (brake2->raw > parameters.pedalsRawTooLow);

    if (accelInRange1 && accelInRange2)
        output.accelPercent = accelAverage;
    else if (accelInRange1)
        output.accelPercent = accel1->conversion;
    else if (accelInRange2)
        output.accelPercent = accel2->conversion;
    else
        output.accelPercent = 0.0;

    if (brakeInRange1 && brakeInRange2)
        output.brakePercent = brakeAverage;
    else if (brakeInRange1)
        output.brakePercent = brake1->conversion;
    else if (brakeInRange2)
        output.brakePercent = brake2->conversion;
    else
        output.brakePercent = 0.0;

    // Check instantaneous implausibility
    // T.4.2.4
    // T.4.2.10
    float accelDeviation = abs(accel1->conversion - accel2->conversion) / accelAverage;
    if ((accelDeviation >= parameters.pedalsImplausiblePercent) || !accelInRange1 || !accelInRange2)
    {
        output.accelStatus = PEDALS_IMPLAUSIBLE;
    }
    else if (accelDeviation >= parameters.pedalsMarginalPercent && accelDeviation < parameters.pedalsImplausiblePercent)
    {
        output.accelStatus = PEDALS_MARGINAL;
    }
    else
    {
        output.accelStatus = PEDALS_NOMINAL;
    }

    float brakeDeviation = abs(brake1->conversion - brake2->conversion) / brakeAverage;
    if ((brakeDeviation >= parameters.pedalsImplausiblePercent) || !brakeInRange1 || !brakeInRange2)
    {
        output.brakeStatus = PEDALS_IMPLAUSIBLE;
    }
    else if (brakeDeviation >= parameters.pedalsMarginalPercent && brakeDeviation < parameters.pedalsImplausiblePercent)
    {
        output.brakeStatus = PEDALS_MARGINAL;
    }
    else
    {
        output.brakeStatus = PEDALS_NOMINAL;
    }

    // Check if both pedals are pressed
    bool accelPressed = output.accelPercent > parameters.accelPressedThreshold;
    bool brakePressed = output.brakePercent > parameters.brakePressedThreshold;
    if (accelPressed && brakePressed)
        output.pedalsCommand = PEDALS_BOTH_PRESSED;
    else if (accelPressed)
        output.pedalsCommand = PEDALS_ACCEL_PRESSED;
    else if (brakePressed)
        output.pedalsCommand = PEDALS_BRAKE_PRESSED;
    else
        output.pedalsCommand = PEDALS_NONE_PRESSED;

    // Check for persistent implausibility
    if ((output.accelStatus == PEDALS_IMPLAUSIBLE) || (output.brakeStatus == PEDALS_IMPLAUSIBLE))
    {
        if (implausibilityDetectedTime == 0)
            implausibilityDetectedTime = millis();
        if (millis() - implausibilityDetectedTime >= PEDALS_IMPLAUSIBLE_DURATION)
            output.persistentImplausibilityDetected = true;
    }
    else
    {
        implausibilityDetectedTime = 0;
        output.persistentImplausibilityDetected = false;
    }

    return output;
}
