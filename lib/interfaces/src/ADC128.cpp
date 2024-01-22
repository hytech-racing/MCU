#include "AnalogSensor.h"
#include <SPI.h>

// Definitions
#define ADC128_DEFAULT_SPI_SDI 12
#define ADC128_DEFAULT_SPI_SDO 11
#define ADC128_DEFAULT_SPI_CLK 13
#define ADC128_DEFAULT_SPI_SPEED 2000000

#define ADC128_NUM_CHANNELS 8

class ADC128 : public AnalogMultiSensor<ADC128_NUM_CHANNELS>
{
private:
    const int SPI_PIN_CS;
    const int SPI_PIN_SDI;
    const int SPI_PIN_SDO;
    const int SPI_PIN_CLK;
    const int SPI_SPEED;
public:
// Constructors
    ADC128(const int SPI_PIN_CS_, const int SPI_PIN_SDI_, const int SPI_PIN_SDO_, const int SPI_PIN_CLK_, const int SPI_SPEED_)
    : SPI_PIN_CS(SPI_PIN_CS_)
    , SPI_PIN_SDI(SPI_PIN_SDI_)
    , SPI_PIN_SDO(SPI_PIN_SDO_)
    , SPI_PIN_CLK(SPI_PIN_CLK_)
    , SPI_SPEED(SPI_SPEED_)
    {
        for (int i = 0; i < ADC128_NUM_CHANNELS; i++)
        {
            channels[i] = AnalogChannel();
        }

        pinMode(SPI_PIN_CS, OUTPUT);
        pinMode(SPI_PIN_SDI, INPUT);
        pinMode(SPI_PIN_SDO, OUTPUT);
        pinMode(SPI_PIN_CLK, OUTPUT);

        digitalWrite(SPI_PIN_CS, HIGH);
        // This may interfere with other devices on the SPI line.
        // May be better to bring clock high before bringing CS low.
        // digitalWrite(SPI_PIN_CLK, HIGH);
    }
    ADC128(const int SPI_PIN_CS_)
    : ADC128(SPI_PIN_CS_, ADC128_DEFAULT_SPI_SDI, ADC128_DEFAULT_SPI_SDO, ADC128_DEFAULT_SPI_CLK, ADC128_DEFAULT_SPI_SPEED) {}

// Functions
    void sample()
    {
        digitalWrite(SPI_PIN_CLK, HIGH);
        digitalWrite(SPI_PIN_CS, LOW);
        SPI.beginTransaction(SPISettings(SPI_SPEED, MSBFIRST, SPI_MODE3));

        for (int channelIndex = 0; channelIndex < ADC128_NUM_CHANNELS; channelIndex++)
        {
            uint16_t value = SPI.transfer16(channelIndex << 11);
            channels[channelIndex].lastSample = (value & 0x0FFF);
        }
        
        SPI.endTransaction();
        digitalWrite(SPI_PIN_CS, HIGH);
    }
};