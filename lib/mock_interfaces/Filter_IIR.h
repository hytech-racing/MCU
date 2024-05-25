/* IIR digital low pass filter */
#ifndef __FILTER_IIR__
#define __FILTER_IIR__

#include <stdint.h>

#define DEFAULT_ALPHA 0.0

template <typename dataType>
class Filter_IIR
{

public:
    /**
     * Constructors
     */
    Filter_IIR(float alpha, dataType init_val=0) {
        set_alpha(alpha);
        prev_reading = init_val;
    }
    Filter_IIR() {
        Filter_IIR(DEFAULT_ALPHA);
    }

    void set_alpha(float alpha);
    dataType get_prev_reading() const {return prev_reading;}

    dataType filtered_result(dataType new_val);
    
private:    
    float alpha;
    dataType prev_reading;
};

template <typename dataType>
void Filter_IIR<dataType>::set_alpha(float alpha) {
    if (alpha > 1.0) {
        this->alpha = 1.0;
    }
    else if (alpha < 0.0) {
        this->alpha = 0.0;
    }
    else
    {
        this->alpha = alpha;
    }
}

template <typename dataType>
dataType Filter_IIR<dataType>::filtered_result(dataType new_val) {
    prev_reading = (1 - alpha) * new_val + alpha * prev_reading;

    return prev_reading;
}

template <typename dataType, int N>
class FilterIIRMulti
{
protected:
    Filter_IIR<dataType> filter_channels_[N];
public:
    virtual void setAlphas(int channel, float alpha) 
    {
    filter_channels_[channel].set_alpha(alpha);
    }
};

#endif
#pragma once