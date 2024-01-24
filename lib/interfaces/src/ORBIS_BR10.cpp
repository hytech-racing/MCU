#include "ORBIS_BR10.h"

OrbisBR10::OrbisBR10(HardwareSerial* serial_, int serialSpeed_)
: serial(serial_)
, serialSpeed(serialSpeed_)
{
    channel = AnalogChannel(ORBIS_BR10_SCALE, 0.0);
    data = 0;
    // Initialize with all errors/warnings set
    status = ORBIS_BR10_BITMASK_GENERAL | ORBIS_BR10_BITMASK_DETAILED;

    serial->begin(serialSpeed);
}

OrbisBR10::OrbisBR10(HardwareSerial* serial_)
: OrbisBR10(serial_, ORBIS_BR10_DEFAULT_SERIAL_SPEED)
{

}

void OrbisBR10::sample()
{
    uint8_t readByte[3] = {0};

    serial->write(0x64);
    if (serial->available() >= 4 && serial->read() == 0x64) {
        readByte[0] = serial->read(); //lower half of steering
        readByte[1] = serial->read(); //upper half of steering
        readByte[2] = serial->read(); //error stream 
        data = (readByte[0] << 6) | (readByte[1] >> 2);
        status = readByte[1] & ORBIS_BR10_BITMASK_GENERAL;
        status |= readByte[2] & ORBIS_BR10_BITMASK_DETAILED;
    }
    else
    {
        // set the error flag
        status = ORBIS_BR10_BITMASK_GENERAL_ERROR;
    }
}

SteeringEncoderConversion_s OrbisBR10::convert()
{
    SteeringEncoderConversion_s returnConversion;               // struct to be returned
    AnalogConversion_s internalConversion = channel.convert();  // internal conversion result

    if (status & (ORBIS_BR10_BITMASK_GENERAL_ERROR | ORBIS_BR10_BITMASK_DETAILED_COUNTER_ERROR))
    {
        returnConversion.status = STEERING_ENCODER_ERROR;
    }
    else if (status == 0 && internalConversion.status == ANALOG_SENSOR_GOOD)
    {
        returnConversion.status = STEERING_ENCODER_NOMINAL;
    }
    else
    {
        returnConversion.status = STEERING_ENCODER_MARGINAL;
    }
    return ;
}

void OrbisBR10::setOffset(float newOffset)
{
    channel.offset = newOffset;
}
