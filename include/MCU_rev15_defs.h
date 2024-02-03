#ifndef __MCU15_H__
#define __MCU15_H__

// pindefs
const int ADC1_CS = 34;
const int ADC2_CS = 33;
const int ADC3_CS = 29;
const HardwareSerial* STEERING_SERIAL = &Serial5;
const int SOFTWARE_OK       = 28;
const int WATCHDOG_INPUT    = 32;

// ADC1 channel defs
const int MCU15_ACCEL1_CHANNEL          = 2;
const int MCU15_ACCEL2_CHANNEL          = 1;
const int MCU15_BRAKE1_CHANNEL          = 5;
const int MCU15_BRAKE2_CHANNEL          = 3;
const int MCU15_GLV_SENSE_CHANNEL       = 4;
const int MCU15_STEERING_CHANNEL        = 7;
const int MCU15_CUR_POS_SENSE_CHANNEL   = 6;
const int MCU15_CUR_NEG_SENSE_CHANNEL   = 0;

// Time intervals
const unsigned long SETUP_PRESENT_ACTION_INTERVAL       = 5000;
const unsigned long BUZZER_ON_INTERVAL                  = 2000;
const unsigned long INVERTER_ENABLING_TIMEOUT_INTERVAL  = 5000;

#endif /* __MCU15_H__ */