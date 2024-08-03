#ifndef __UPPERSTEERINGSENSOR_H__
#define __UPPERSTEERINGSENSOR_H__

#include <tuple>

enum class SteeringEncoderStatus_e
{
    STEERING_ENCODER_NOMINAL = 0,
    STEERING_ENCODER_MARGINAL = 1,
    STEERING_ENCODER_ERROR = 2,
};

struct SteeringEncoderConversion_s
{
    int raw;
    float angle;
    SteeringEncoderStatus_e status;
};

class SteeringEncoderInterface
{
public:
// Mock data
    SteeringEncoderConversion_s mockConversion;
// Functions
    void sample()
    {
        return;
    };
    SteeringEncoderConversion_s convert()
    {
        return mockConversion;
    };
    void setOffset(float newOffset);
};

#endif /* __UPPERSTEERINGSENSOR_H__ */
