#include <SPI.h>
#include "MCP_ADC.h"
const int SS_PIN = 34;   // assuming MOSI 11, MISO 12, SCK 13


MCP_ADC<8> a1 = MCP_ADC<8>(34);
MCP_ADC<4> a2 = MCP_ADC<4>(33);
MCP_ADC<4> a3 = MCP_ADC<4>(29);


void setup()
{
    SPI.begin();
    a1.init();
    a2.init();
    a3.init();
}

void loop()
{
    Serial.println("looped");
    a1.tick();
    a2.tick();
    a3.tick();
}
