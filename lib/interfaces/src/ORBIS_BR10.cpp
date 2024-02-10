#include "ORBIS_BR10.h"

OrbisBR10::OrbisBR10(HardwareSerial* serial, int serialSpeed)
: serial_(serial)
, serialSpeed_(serialSpeed)
{
    data_ = 0;
    offset_ = 0.0;
    // Initialize with all errors/warnings set
    status_ = ORBIS_BR10_BITMASK_GENERAL | ORBIS_BR10_BITMASK_DETAILED;

    serial_->begin(serialSpeed);
}

OrbisBR10::OrbisBR10(HardwareSerial* serial)
: OrbisBR10(serial, ORBIS_BR10_DEFAULT_SERIAL_SPEED)
{

}

void OrbisBR10::sample()
{
    uint8_t readByte[3] = {0};

    serial_->write(0x64);
    if (serial_->available() >= 4 && serial_->read() == 0x64) {
        readByte[0] = serial_->read(); //lower half of steering
        readByte[1] = serial_->read(); //upper half of steering
        readByte[2] = serial_->read(); //error stream 
        data_ = (readByte[0] << 6) | (readByte[1] >> 2);
        status_ = readByte[1] & ORBIS_BR10_BITMASK_GENERAL;
        status_ |= readByte[2] & ORBIS_BR10_BITMASK_DETAILED;
    }
    else
    {
        // set the error flag
        status_ = ORBIS_BR10_BITMASK_GENERAL_ERROR;
    }
}

SteeringEncoderConversion_s OrbisBR10::convert()
{
    SteeringEncoderConversion_s returnConversion;
    returnConversion.raw = data_;
    returnConversion.angle = (data_ * ORBIS_BR10_SCALE) + offset_;

    if (status_ & (ORBIS_BR10_BITMASK_GENERAL_ERROR | ORBIS_BR10_BITMASK_DETAILED_COUNTER_ERROR))
    {
        returnConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_ERROR;
    }
    else if (status_ == 0)
    {
        returnConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_NOMINAL;
    }
    else
    {
        returnConversion.status = SteeringEncoderStatus_e::STEERING_ENCODER_MARGINAL;
    }
    return returnConversion;
}

void OrbisBR10::setOffset(float newOffset)
{
    offset_ = newOffset;
}
