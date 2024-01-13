/* MCP3204/8 ADC component */
#ifndef __ADC_DRIVER_H__
#define __ADC_DRIVER_H__

#include <stdint.h>
#include "ADC_SPI.h"

// might not need an interface in this case? 
// seems dumb if one driver or component only request one value
// but instead we pass out a bunch

class ADCDriver
{
public:
    ADCDriver(const ADC_SPI* adc, int count) {
        _adc = adc;
        channel_count = (count > 8) ? 8 : count;
    }
    void read_all_adcs();
    uint16_t get_adc_channel(int channel;

private:
    const ADC_SPI* _adc;
    int channel_count;
    uint16_t adc_readings[8];
};

#endif /* __ADC_DRIVER_H__ */
#pragma once