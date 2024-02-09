#include "MCP_ADC.h"
#include <SPI.h>

template <int MCP_ADC_NUM_CHANNELS>
MCP_ADC<MCP_ADC_NUM_CHANNELS>::MCP_ADC(const int spiPinCS, const int spiPinSDI, const int spiPinSDO, const int spiPinCLK, const int spiSpeed)
: spiPinCS_(spiPinCS)
, spiPinSDI_(spiPinSDI)
, spiPinSDO_(spiPinSDO)
, spiPinCLK_(spiPinCLK)
, spiSpeed_(spiSpeed)
{
    for (int i = 0; i < MCP_ADC_NUM_CHANNELS; i++)
    {
        MCP_ADC<MCP_ADC_NUM_CHANNELS>::channels_[i] = AnalogChannel();
    }

    pinMode(spiPinCS_, OUTPUT);
    pinMode(spiPinSDI_, INPUT);
    pinMode(spiPinSDO_, OUTPUT);
    pinMode(spiPinCLK_, OUTPUT);

    digitalWrite(spiPinCS_, HIGH);
}

template <int MCP_ADC_NUM_CHANNELS>
MCP_ADC<MCP_ADC_NUM_CHANNELS>::MCP_ADC(const int spiPinCS__)
: MCP_ADC<MCP_ADC_NUM_CHANNELS>(spiPinCS__, MCP_ADC_DEFAULT_SPI_SDI, MCP_ADC_DEFAULT_SPI_SDO, MCP_ADC_DEFAULT_SPI_CLK, MCP_ADC_DEFAULT_SPI_SPEED) {}

template <int MCP_ADC_NUM_CHANNELS>
void MCP_ADC<MCP_ADC_NUM_CHANNELS>::tick()
{
    MCP_ADC<MCP_ADC_NUM_CHANNELS>::sample();
    MCP_ADC<MCP_ADC_NUM_CHANNELS>::convert();
}

template <int MCP_ADC_NUM_CHANNELS>
void MCP_ADC<MCP_ADC_NUM_CHANNELS>::sample()
{
    uint16_t command = (
        (0b1 << 15) |    // start bit
        (0b1 << 14)      // single ended mode
    );

    SPI.beginTransaction(SPISettings(spiSpeed_, MSBFIRST, SPI_MODE0));

    for (int channelIndex = 0; channelIndex < MCP_ADC_NUM_CHANNELS; channelIndex++)
    {
        digitalWrite(spiPinCS_, LOW);
        uint16_t value = SPI.transfer16(command | channelIndex << 11);
        MCP_ADC<MCP_ADC_NUM_CHANNELS>::channels_[channelIndex].lastSample = (value & 0x0FFF);
        digitalWrite(spiPinCS_, HIGH);
        delayMicroseconds(1); // MCP_ADC Tcsh = 500ns
    }
    
    SPI.endTransaction();
}
