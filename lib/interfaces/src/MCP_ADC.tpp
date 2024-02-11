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

    // initializes the SPI bus by setting SCK, MOSI, and SS to outputs
    // pulling SCK and MOSI low, and SS high
    SPI.begin();
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
    // uint16_t command = (
    //     (0b1 << 15) |    // start bit
    //     (0b1 << 14)      // single ended mode
    // );
    byte command, b0, b1, b2;

    // initialize SPI bus. REQUIRED: call SPI.begin() before this
    SPI.beginTransaction(SPISettings(spiSpeed_, MSBFIRST, SPI_MODE0));

    for (int channelIndex = 0; channelIndex < MCP_ADC_NUM_CHANNELS; channelIndex++)
    {
        digitalWrite(spiPinCS_, LOW);
        command = ((0x01 << 7) |                    // start bit
                   (0x01 << 6) |                    // single or differential
                   ((channelIndex & 0x07) << 3));   // channel number
        b0 = SPI.transfer(command);
        b1 = SPI.transfer(0x00);
        b2 = SPI.transfer(0x00);

        // uint16_t value = SPI.transfer16(command | channelIndex << 11);
        uint16_t value = (b0 & 0x01) << 11 | (b1 & 0xFF) << 3 | (b2 & 0xE0) >> 5;
        MCP_ADC<MCP_ADC_NUM_CHANNELS>::channels_[channelIndex].lastSample = (value & 0x0FFF);
        digitalWrite(spiPinCS_, HIGH);
        delayMicroseconds(1); // MCP_ADC Tcsh = 500ns
    }
    
    SPI.endTransaction();
}
