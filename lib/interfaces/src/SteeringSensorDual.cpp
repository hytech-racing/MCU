#include "SteeringInterface.h"
#include "AnalogSensor.h"
#include "UpperSteeringSensor.h"
#include <cmath>

// Digital Encoder = Primary Sensor
// Analog Encoder = Secondary Sensor

// Definitions
// TODO: evalaute reasonable thresholds for agreement
#define STEERING_DIVERGENCE_ERROR_THRESHOLD (5.0) // Steering sensors can disagree by 5 degrees before output is considered erroneous
#define STEERING_DIVERGENCE_WARN_THRESHOLD (2.5) // Warning condition will be raised when steering sensors diverge 2.5 degrees

class SteeringSensorDual : SteeringInterface
{
private:
    UpperSteeringSensor* primarySensor;
    AnalogChannel* secondarySensor;
public:
// Constructors
    SteeringSensorDual(UpperSteeringSensor* primarySensor_, AnalogChannel* secondarySensor_)
    : primarySensor(primarySensor_)
    , secondarySensor(secondarySensor_) {}

// Functions
    std::tuple<float, steeringStatus_s> getSteeringAngle()
    {
        auto [primaryAngle, primaryStatus] = primarySensor->getAngleAndStatus();
        auto [secondaryAngle, secondaryStatus] = secondarySensor->convert();

        // Both sensors are nominal
        if ((primaryStatus == UPPER_STEERING_NOMINAL) && (secondaryStatus == ANALOG_SENSOR_GOOD))
        {
            return {primaryAngle, STEERING_NOMINAL};
        }

        // One or both sensors are marginal
        // Sensors disagree by STEERING_DIVERGENCE_WARN_THRESHOLD degrees and less than STEERING_DIVERGENCE_ERROR_THRESHOLD degrees
        if ((primaryStatus == UPPER_STEERING_MARGINAL)
            || (secondaryStatus == ANALOG_SENSOR_CLAMPED)
            || ((std::abs(primaryAngle - secondaryAngle) > STEERING_DIVERGENCE_WARN_THRESHOLD) && (std::abs(primaryAngle - secondaryAngle) < STEERING_DIVERGENCE_ERROR_THRESHOLD)))
        {
            return {primaryAngle, STEERING_MARGINAL};
        }

        // Upper steering sensor reports error, lower sensor is nominal
        if ((primaryStatus == UPPER_STEERING_ERROR) && (secondaryStatus == ANALOG_SENSOR_GOOD))
        {
            return {secondaryAngle, STEERING_DEGRADED};
        }

        // Fall through case
        // Complete failure of steering sensing
        return {0.0, STEERING_ERROR};
    }
};