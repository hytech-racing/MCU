#include "PedalsInterface.h"
#include "AnalogSensor.h"
#include <cmath>

// Definitions
#define PEDALS_IMPLAUSIBLE_PERCENT 0.10         // 10% allowed deviation FSAE T.4.2.4
#define PEDALS_MARGINAL_PERCENT 0.07            // Report pedals are marginal. Allows us to detect pedals may need recalibration
#define PEDALS_RAW_TOO_LOW (0.5 / 5 * 4096)     // FSAE T.4.2.10 Pedals are implausible below 0.5V raw reading
#define PEDALS_RAW_TOO_HIGH (4.5 / 5 * 4096)    // FSAE T.4.2.10 Pedals are implausible above 4.5V raw reading

class PedalsDual : PedalsInterface
{
private:
    AnalogChannel* accelSensor1;
    AnalogChannel* accelSensor2;
    AnalogChannel* brakeSensor1;
    AnalogChannel* brakeSensor2;
public:
// Constructors
    PedalsDual(AnalogChannel* accelSensor1_, AnalogChannel* accelSensor2_, AnalogChannel* brakeSensor1_, AnalogChannel* brakeSensor2_)
    : accelSensor1(accelSensor1_)
    , accelSensor2(accelSensor2_)
    , brakeSensor1(brakeSensor1_)
    , brakeSensor2(brakeSensor2_) {}
// Functions
    std::tuple<float, float, PedalsStatus_s> getPedalsAndStatus()
    {
        // Intentionally not checking whether these channels are being clamped
        // because this is expected at both ends of the pedal travel
        float accelPercent1 = std::get<0>(accelSensor1->convert());
        float accelPercent2 = std::get<0>(brakeSensor2->convert());
        float brakePercent1 = std::get<0>(accelSensor1->convert());
        float brakePercent2 = std::get<0>(brakeSensor2->convert());
        int accelRaw1 = accelSensor1->lastSample;
        int accelRaw2 = accelSensor2->lastSample;
        int brakeRaw1 = brakeSensor1->lastSample;
        int brakeRaw2 = brakeSensor2->lastSample;

        float accelAverage = (accelPercent1 + accelPercent2) / 2.0;
        float brakeAverage = (brakePercent1 + brakePercent2) / 2.0;

        float accelReturn;
        float brakeReturn;

        bool accelInRange1 = (accelRaw1 < PEDALS_RAW_TOO_HIGH) && (accelRaw1 > PEDALS_RAW_TOO_LOW);
        bool accelInRange2 = (accelRaw2 < PEDALS_RAW_TOO_HIGH) && (accelRaw2 > PEDALS_RAW_TOO_LOW);
        bool brakeInRange1 = (brakeRaw1 < PEDALS_RAW_TOO_HIGH) && (brakeRaw1 > PEDALS_RAW_TOO_LOW);
        bool brakeInRange2 = (brakeRaw2 < PEDALS_RAW_TOO_HIGH) && (brakeRaw2 > PEDALS_RAW_TOO_LOW);

        // If any one of the sensors is detected short or open, don't use it in the average
        // This counts as implausibility, BUT, we don't have to act on it for another 100ms
        // Let the system handle persistent implausibilities. If we have unreliable wiring, 
        // the system can detect this and alert us. It's not the job of the pedal interface
        // to inhibit driving unless both sensors on a pedal cannot be resolved.

        if (accelInRange1 && accelInRange2)
            accelReturn = accelAverage;
        else if (accelInRange1)
            accelReturn = accelPercent1;
        else if (accelInRange2)
            accelReturn = accelPercent2;
        else
            accelReturn = 0.0;

        if (brakeInRange1 && brakeInRange2)
            brakeReturn = brakeAverage;
        else if (brakeInRange1)
            brakeReturn = brakePercent1;
        else if (brakeInRange2)
            brakeReturn = brakePercent2;
        else
            brakeReturn = 0.0;

        // Check implausibility
        // T.4.2.4
        // T.4.2.10
        if (   (std::abs(accelPercent1 - accelPercent2) / accelAverage) > PEDALS_IMPLAUSIBLE_PERCENT
            || (std::abs(brakePercent1 - brakePercent2) / brakeAverage) > PEDALS_IMPLAUSIBLE_PERCENT
            || !accelInRange1
            || !accelInRange2
            || !brakeInRange1
            || !brakeInRange2)
        {
            return {accelReturn, brakeReturn, PEDALS_IMPLAUSIBLE};
        }

        // Check whether pedals are marginal
        if (   (std::abs(accelPercent1 - accelPercent2) / accelAverage) > PEDALS_MARGINAL_PERCENT
            || (std::abs(brakePercent1 - brakePercent2) / brakeAverage) > PEDALS_MARGINAL_PERCENT)
        {
            return {accelReturn, brakeReturn, PEDALS_MARGINAL};
        }

        return {accelReturn, brakeReturn, PEDALS_NOMINAL};
    }
};