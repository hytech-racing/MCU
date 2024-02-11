#include <Arduino.h>
#include <unity.h>

#include "MCP_ADC.h"

// #define ADC_CS 10

void test_MCP_ADC_sample()
{
    Serial.println("Print sth");
    MCP_ADC<8> mcp3208(33);

    mcp3208.sample();
    mcp3208.convert();

    // // Serial.begin(115200);

    Serial.println("MCP3208 test on Main ECU rev14:");
    for(int i = 0; i < 8; ++i){
        Serial.print("Channel [");
        Serial.print(i);
        Serial.print("] : ");
        Serial.println(mcp3208.get().conversions[i].raw);
    }

}