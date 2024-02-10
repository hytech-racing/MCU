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
    float angle;
    int raw;
    SteeringEncoderStatus_e status;
};

class SteeringEncoderInterface
{
public:
// Functions
    /// @brief Commands the underlying steering sensor to sample and hold the result
    virtual void sample();
    /// @brief Calculate steering angle and whether result is in sensor's defined bounds. DOES NOT SAMPLE.
    /// @return Calculated steering angle in degrees, upperSteeringStatus_s
    virtual SteeringEncoderConversion_s convert();
    /// @brief Set the upper steering sensor's offset. 0 degrees should be centered.
    /// @param newOffset 
    virtual void setOffset(float newOffset);
};

#endif /* __UPPERSTEERINGSENSOR_H__ */
