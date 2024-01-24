#include "MCP3208.h"
#include <SPI.h>

MCP3208::MCP3208(const int SPI_PIN_CS_, const int SPI_PIN_SDI_, const int SPI_PIN_SDO_, const int SPI_PIN_CLK_, const int SPI_SPEED_)
: SPI_PIN_CS(SPI_PIN_CS_)
, SPI_PIN_SDI(SPI_PIN_SDI_)
, SPI_PIN_SDO(SPI_PIN_SDO_)
, SPI_PIN_CLK(SPI_PIN_CLK_)
, SPI_SPEED(SPI_SPEED_)
{
    for (int i = 0; i < MCP3208_NUM_CHANNELS; i++)
    {
        channels[i] = AnalogChannel();
    }

    pinMode(SPI_PIN_CS, OUTPUT);
    pinMode(SPI_PIN_SDI, INPUT);
    pinMode(SPI_PIN_SDO, OUTPUT);
    pinMode(SPI_PIN_CLK, OUTPUT);

    digitalWrite(SPI_PIN_CS, HIGH);
}

MCP3208::MCP3208(const int SPI_PIN_CS_)
: MCP3208(SPI_PIN_CS_, MCP3208_DEFAULT_SPI_SDI, MCP3208_DEFAULT_SPI_SDO, MCP3208_DEFAULT_SPI_CLK, MCP3208_DEFAULT_SPI_SPEED) {}

void MCP3208::sample()
{
    uint16_t command = (
        (0b1 << 15) |    // start bit
        (0b1 << 14)      // single ended mode
    );

    SPI.beginTransaction(SPISettings(SPI_SPEED, MSBFIRST, SPI_MODE0));

    for (int channelIndex = 0; channelIndex < MCP3208_NUM_CHANNELS; channelIndex++)
    {
        digitalWrite(SPI_PIN_CS, LOW);
        uint16_t value = SPI.transfer16(command | channelIndex << 11);
        channels[channelIndex].lastSample = (value & 0x0FFF);
        digitalWrite(SPI_PIN_CS, HIGH);
        delayMicroseconds(1); // MCP3208 Tcsh = 500ns
    }
    
    SPI.endTransaction();
}
