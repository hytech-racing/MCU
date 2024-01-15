#ifndef ANALOGSENSOR
#define ANALOGSENSOR

#include <tuple>
#include <algorithm>

class AnalogMultiSensor;

class AnalogChannel
{
private:
public:
// Data
    float scale;
    float offset;
    bool clamp;
    float clampLow;
    float clampHigh;
    int lastSample;
    float lastConversion;
    AnalogMultiSensor* parent;

// Constructors
    AnalogChannel(AnalogMultiSensor* parent_, float scale_, float offset_, bool clamp_, float clampLow_, float clampHigh_)
    : scale(scale_),
      offset(offset_),
      clamp(clamp_),
      clampLow(clampLow_),
      clampHigh(clampHigh_),
      parent(parent_) {}

    AnalogChannel(AnalogMultiSensor* parent_, float scale_, float offset_)
    : AnalogChannel(parent_, scale_, offset_, false, __FLT_MIN__, __FLT_MAX__) {}

    AnalogChannel(AnalogMultiSensor* parent_)
    : AnalogChannel(parent_, 1.0, 0.0, false, __FLT_MIN__, __FLT_MAX__) {}
    
// Functions
    // Returns conversion result and whether result was clamped
    std::tuple<float, bool> convert()
    {
        lastConversion = lastSample * scale + offset;
        return {
            clamp ? std::min(std::max(lastConversion, clampLow), clampHigh) : lastConversion,
            clamp ? lastConversion > clampHigh || lastConversion < clampLow : false
        };
    }
};

class AnalogMultiSensor
{
private:
public:
// Data
    AnalogChannel** channels;
    int numChannels;
// Constructors

// Functions
    virtual void sampleChannel(int channelIndex);
    virtual void sampleAll();
};

#endif /* ANALOGSENSOR */
