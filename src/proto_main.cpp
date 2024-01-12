/* Prototype main function for logic soothing */

/* Include files */
#include <Arduino.h>

#include "ADC_SPI.h"

// Sensors and hardware
ADC_SPI ADC1(ADC1_CS, ADC_SPI_SPEED, ECU_SDI, ECU_SDO, ECU_CLK);
ADC_SPI ADC2(ADC2_CS, ADC_SPI_SPEED, ECU_SDI, ECU_SDO, ECU_CLK);
ADC_SPI ADC3(ADC3_CS, ADC_SPI_SPEED, ECU_SDI, ECU_SDO, ECU_CLK);
// driver
// component

void setup() {

}

void loop() {

}