#include "SteeringInterface.h"
#include "AnalogSensor.h"
#include <SPI.h>

// Digital Encoder = Primary Sensor
// Analog Encoder = Secondary Sensor

// Definitions
#define DEFAULT_STEERING_SERIAL_SPEED 115200

class SteeringSensorDual : SteeringInterface
{
private:
    HardwareSerial* serial;
    AnalogMultiSensor* secondarySensorADC;
    const int secondarySensorChannelIndex;
public:
// Constructors
    SteeringSensorDual(HardwareSerial* serial_, int serialSpeed_, AnalogMultiSensor* secondarySensorADC_, const int secondarySensorChannelIndex_)
    : serial(serial_)
    , secondarySensorADC(secondarySensorADC_)
    , secondarySensorChannelIndex(secondarySensorChannelIndex_)
    {
        serial->begin(serialSpeed_);
    }
    SteeringSensorDual(HardwareSerial* serial_, AnalogMultiSensor* secondarySensorADC_, const int secondarySensorChannelIndex_)
    : SteeringSensorDual(serial_, DEFAULT_STEERING_SERIAL_SPEED, secondarySensorADC_, secondarySensorChannelIndex_) {}

// Functions
    std::tuple<float, bool> getSteeringAngle()
    {
        return {0.0, false};
    }
};