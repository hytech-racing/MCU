// /* Prototype main function for logic soothing */

// /* Include files */
#include <Arduino.h>
#include "MCUStateMachine.h"

#include "ADC_SPI.h"

// // Sensors and hardware
// ADC_SPI ADC1(ADC1_CS, ADC_SPI_SPEED, ECU_SDI, ECU_SDO, ECU_CLK);
// ADC_SPI ADC2(ADC2_CS, ADC_SPI_SPEED, ECU_SDI, ECU_SDO, ECU_CLK);
// ADC_SPI ADC3(ADC3_CS, ADC_SPI_SPEED, ECU_SDI, ECU_SDO, ECU_CLK);
// // driver
// // component

BuzzerController buzzer(500);

DashDriver dash_interface;

InverterComponent lf_inv(100);
InverterComponent rf_inv(100);

InverterComponent lr_inv(100);
InverterComponent rr_inv(100);


DrivetrainComponent drivetrain({&lf_inv, &rf_inv, &lr_inv, &rr_inv});
MCUStateMachine state_machine(&buzzer, &drivetrain, &dash_interface);

void setup() {
    
}

void loop() {
    state_machine.tick_state_machine(millis());
}