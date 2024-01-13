#include "ADCDriver.h"

void ADCDriver::read_all_adcs() {
    for (int i = 0; i < channel_count; i++)
    {
        adc_readings[i] = _adc->read_channel(i);
    }    
}

uint16_t ADCDriver::get_adc_channel(int channel) {
    return adc_readings[channel];
}