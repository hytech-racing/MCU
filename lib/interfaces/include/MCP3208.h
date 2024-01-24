#ifndef __MCP3208_H__
#define __MCP3208_H__

#include "AnalogSensorsInterface.h"

// Definitions
#define MCP3208_DEFAULT_SPI_SDI 12
#define MCP3208_DEFAULT_SPI_SDO 11
#define MCP3208_DEFAULT_SPI_CLK 13
#define MCP3208_DEFAULT_SPI_SPEED 2000000

#define MCP3208_NUM_CHANNELS 8

class MCP3208 : public AnalogMultiSensor<MCP3208_NUM_CHANNELS>
{
private:
    const int SPI_PIN_CS;
    const int SPI_PIN_SDI;
    const int SPI_PIN_SDO;
    const int SPI_PIN_CLK;
    const int SPI_SPEED;
public:
// Constructors
    MCP3208(const int SPI_PIN_CS_, const int SPI_PIN_SDI_, const int SPI_PIN_SDO_, const int SPI_PIN_CLK_, const int SPI_SPEED_);
    MCP3208(const int SPI_PIN_CS_);

// Functions
    void sample();
};

#endif /* __MCP3208_H__ */