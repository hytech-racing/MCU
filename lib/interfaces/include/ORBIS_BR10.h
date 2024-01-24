#ifndef __ORBIS_H__
#define __ORBIS_H__

#include <Arduino.h>
#include "SteeringEncoderInterface.h"

// Definitions
#define ORBIS_BR10_DEFAULT_SERIAL_SPEED             115200
#define ORBIS_BR10_SCALE                            0.0219726562 // 360 degrees per 14 bits
#define ORBIS_BR10_BITMASK_GENERAL_WARNING          (0b1 << 0)
#define ORBIS_BR10_BITMASK_GENERAL_ERROR            (0b1 << 1)
#define ORBIS_BR10_BITMASK_GENERAL                  (ORBIS_BR10_BITMASK_GENERAL_WARNING | ORBIS_BR10_BITMASK_GENERAL_ERROR)
#define ORBIS_BR10_BITMASK_DETAILED_COUNTER_ERROR   (0b1 << 3)
#define ORBIS_BR10_BITMASK_DETAILED_SPEED_HIGH      (0b1 << 4)
#define ORBIS_BR10_BITMASK_DETAILED_TEMP_RANGE      (0b1 << 5)
#define ORBIS_BR10_BITMASK_DETAILED_DIST_FAR        (0b1 << 6)
#define ORBIS_BR10_BITMASK_DETAILED_DIST_NEAR       (0b1 << 7)
#define ORBIS_BR10_BITMASK_DETAILED                 (ORBIS_BR10_BITMASK_DETAILED_COUNTER_ERROR | ORBIS_BR10_BITMASK_DETAILED_SPEED_HIGH | ORBIS_BR10_BITMASK_DETAILED_TEMP_RANGE | ORBIS_BR10_BITMASK_DETAILED_DIST_FAR | ORBIS_BR10_BITMASK_DETAILED_DIST_NEAR)

class OrbisBR10 : SteeringEncoderInterface
{
private:
// Data
    HardwareSerial* serial;
    int serialSpeed;
    AnalogChannel channel;
    int data;
    char status;
public:
// Constructors
    OrbisBR10(HardwareSerial* serial_, int serialSpeed_);
    OrbisBR10(HardwareSerial* serial_);

// Functions
    void sample();
    SteeringEncoderConversion_s convert();
    void setOffset(float newOffset);
};

#endif /* __ORBIS_H__ */