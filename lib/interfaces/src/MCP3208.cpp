#include "MCP3208.h"
#include <SPI.h>

MCP3208::MCP3208(const int spiPinCS, const int spiPinSDI, const int spiPinSDO, const int spiPinCLK, const int spiSpeed)
: spiPinCS_(spiPinCS)
, spiPinSDI_(spiPinSDI)
, spiPinSDO_(spiPinSDO)
, spiPinCLK_(spiPinCLK)
, spiSpeed_(spiSpeed)
{
    for (int i = 0; i < MCP3208_NUM_CHANNELS; i++)
    {
        channels[i] = AnalogChannel();
    }

    pinMode(spiPinCS_, OUTPUT);
    pinMode(spiPinSDI_, INPUT);
    pinMode(spiPinSDO_, OUTPUT);
    pinMode(spiPinCLK_, OUTPUT);

    digitalWrite(spiPinCS_, HIGH);
}

MCP3208::MCP3208(const int spiPinCS__)
: MCP3208(spiPinCS__, MCP3208_DEFAULT_SPI_SDI, MCP3208_DEFAULT_SPI_SDO, MCP3208_DEFAULT_SPI_CLK, MCP3208_DEFAULT_SPI_SPEED) {}

void MCP3208::tick(const SysTick_s &tick)
{
    // Sample at 100hz
    if (tick.triggers.trigger100)
    {
        sample();
        convert();
    }
}

void MCP3208::sample()
{
    uint16_t command = (
        (0b1 << 15) |    // start bit
        (0b1 << 14)      // single ended mode
    );

    SPI.beginTransaction(SPISettings(spiSpeed_, MSBFIRST, SPI_MODE0));

    for (int channelIndex = 0; channelIndex < MCP3208_NUM_CHANNELS; channelIndex++)
    {
        digitalWrite(spiPinCS_, LOW);
        uint16_t value = SPI.transfer16(command | channelIndex << 11);
        channels[channelIndex].lastSample = (value & 0x0FFF);
        digitalWrite(spiPinCS_, HIGH);
        delayMicroseconds(1); // MCP3208 Tcsh = 500ns
    }
    
    SPI.endTransaction();
}
