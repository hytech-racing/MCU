// /* Prototype main function for logic soothing */

// /* Include files */
#include <Arduino.h>
#include "MCUStateMachine.h"

#include "ADC_SPI.h"



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