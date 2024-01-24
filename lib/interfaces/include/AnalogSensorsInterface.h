#ifndef __ANALOGSENSOR_H__
#define __ANALOGSENSOR_H__

#include <tuple>
#include <algorithm>

enum AnalogSensorStatus_e
{
    ANALOG_SENSOR_GOOD = 0,
    ANALOG_SENSOR_CLAMPED = 1,
};

struct AnalogConversion_s
{
    int raw;
    float conversion;
    AnalogSensorStatus_e status;
};

template <int N>
struct AnalogConversionPacket_s
{
    AnalogConversion_s conversions[N];
};

class AnalogChannel
{
public:
// Data
    float scale;
    float offset;
    bool clamp;
    float clampLow;
    float clampHigh;
    int lastSample;

// Constructors
    AnalogChannel(float scale_, float offset_, bool clamp_, float clampLow_, float clampHigh_)
    : scale(scale_),
      offset(offset_),
      clamp(clamp_),
      clampLow(clampLow_),
      clampHigh(clampHigh_) {}
    AnalogChannel(float scale_, float offset_)
    : AnalogChannel(scale_, offset_, false, __FLT_MIN__, __FLT_MAX__) {}
    AnalogChannel()
    : AnalogChannel(1.0, 0.0, false, __FLT_MIN__, __FLT_MAX__) {}
    
// Functions
    /// @brief Calculate sensor output and whether result is in sensor's defined bounds. DOES NOT SAMPLE.
    /// @return Sensor's calculated output in real units, whether the result was clamped (AnalogSensorStatus_s)
    AnalogConversion_s convert()
    {
        float conversion = lastSample * scale + offset;
        return {
            lastSample,
            clamp ? std::min(std::max(conversion, clampLow), clampHigh) : conversion,
            clamp ? ((conversion > clampHigh || conversion < clampLow) ? ANALOG_SENSOR_CLAMPED : ANALOG_SENSOR_GOOD) : ANALOG_SENSOR_GOOD
        };
    }
};

template <int N>
class AnalogMultiSensor
{
public:
// Data
    AnalogChannel channels[N];
// Functions
    /// @brief Performs unit conversions on all channels
    /// @return Packet of <N> channel conversions and statuses
    AnalogConversionPacket_s<N> convert()
    {
        AnalogConversionPacket_s<N> packet;
        for (int i = 0; i < N; i++)
        {
            packet.conversions[i] = channels[i].convert();
        }
        return packet;
    }
    /// @brief Commands the underlying device to sample all channels and internally store the results
    virtual void sample();
};

#endif /* __ANALOGSENSOR_H__ */
