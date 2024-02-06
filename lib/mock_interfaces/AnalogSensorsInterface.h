#ifndef __ANALOGSENSOR_H__
#define __ANALOGSENSOR_H__

#include <tuple>
#include <algorithm>

enum class AnalogSensorStatus_e
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
    AnalogChannel(); 
// Functions
    /// @brief Calculate sensor output and whether result is in sensor's defined bounds. DOES NOT SAMPLE.
    /// @return Sensor's calculated output in real units, whether the result was clamped (AnalogSensorStatus_s)
    AnalogConversion_s convert();
};

template <int N>
class AnalogMultiSensor
{
public:
    AnalogConversionPacket_s<N> data;
// Functions

    /// @brief Used by systems to get data out of this device when it's self-actualizing sampling & conversion.
    /// @return Const ref to last data conversion.
    const AnalogConversionPacket_s<N>& get()
    {
        return data;
    }

    /// @brief Performs unit conversions on all channels
    void convert()
    {
        // for (int i = 0; i < N; i++)
        // {
        //     data.conversions[i] = channels_[i].convert();
        // }
    }

    /// @brief Commands the underlying device to sample all channels and internally store the results
    void sample();
};

#endif /* __ANALOGSENSOR_H__ */
