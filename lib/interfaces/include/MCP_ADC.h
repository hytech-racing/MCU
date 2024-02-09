#ifndef __MCP_ADC_H__
#define __MCP_ADC_H__

#include "AnalogSensorsInterface.h"

// Definitions
const int MCP_ADC_DEFAULT_SPI_SDI   = 12;
const int MCP_ADC_DEFAULT_SPI_SDO   = 11;
const int MCP_ADC_DEFAULT_SPI_CLK   = 13;
const int MCP_ADC_DEFAULT_SPI_SPEED = 2000000;

template <int MCP_ADC_NUM_CHANNELS>
class MCP_ADC : public AnalogMultiSensor<MCP_ADC_NUM_CHANNELS>
{
private:
    const int spiPinCS_;
    const int spiPinSDI_;
    const int spiPinSDO_;
    const int spiPinCLK_;
    const int spiSpeed_;
public:
// Constructors
    MCP_ADC(int spiPinCS, const int spiPinSDI, const int spiPinSDO, const int spiPinCLK, const int spiSpeed);
    MCP_ADC(int spiPinCS);

// Functions
    /* Tick at 100Hz */
    void tick();
    void sample();
};

#include "MCP_ADC.tpp"

#endif /* __MCP_ADC_H__ */