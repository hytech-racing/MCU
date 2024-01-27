#ifndef __MCP3208_H__
#define __MCP3208_H__

#include "AnalogSensorsInterface.h"

// Definitions
const int MCP3208_DEFAULT_SPI_SDI   = 12;
const int MCP3208_DEFAULT_SPI_SDO   = 11;
const int MCP3208_DEFAULT_SPI_CLK   = 13;
const int MCP3208_DEFAULT_SPI_SPEED = 2000000;
const int MCP3208_NUM_CHANNELS      = 8;

class MCP3208 : public AnalogMultiSensor<MCP3208_NUM_CHANNELS>
{
private:
    const int spiPinCS_;
    const int spiPinSDI_;
    const int spiPinSDO_;
    const int spiPinCLK_;
    const int spiSpeed_;
public:
// Constructors
    MCP3208(const int spiPinCS, const int spiPinSDI, const int spiPinSDO, const int spiPinCLK, const int spiSpeed);
    MCP3208(const int spiPinCS);

// Functions
    void tick(const SysTick_s &tick);
    void sample();
};

#endif /* __MCP3208_H__ */