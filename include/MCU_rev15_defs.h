#ifndef __MCU15_H__
#define __MCU15_H__

// pindefs
const int ADC1_CS = 34;
const int ADC2_CS = 33;
const int ADC3_CS = 29;
const int SOFTWARE_OK       = 28;
const int WATCHDOG_INPUT    = 32;

// serial def
HardwareSerial* STEERING_SERIAL = &Serial5;

// ADC1 channel defs
const int MCU15_ACCEL1_CHANNEL          = 2;
const int MCU15_ACCEL2_CHANNEL          = 1;
const int MCU15_BRAKE1_CHANNEL          = 5;
const int MCU15_BRAKE2_CHANNEL          = 3;
const int MCU15_GLV_SENSE_CHANNEL       = 4;
const int MCU15_STEERING_CHANNEL        = 7;
const int MCU15_CUR_POS_SENSE_CHANNEL   = 6;
const int MCU15_CUR_NEG_SENSE_CHANNEL   = 0;
// ADC2 channel defs
const int MCU15_FL_POTS_CHANNEL         = 1;
const int MCU15_FR_POTS_CHANNEL         = 1;
const int MCU15_FL_LOADCELL_CHANNEL     = 2;
const int MCU15_FR_LOADCELL_CHANNEL     = 2;

// Time intervals
const unsigned long SETUP_PRESENT_ACTION_INTERVAL       = 1000;
const unsigned long BUZZER_ON_INTERVAL                  = 2000;
const unsigned long INVERTER_ENABLING_TIMEOUT_INTERVAL  = 5000;

// Communication speeds
const unsigned long INV_CAN_BAUDRATE    = 500000;
const unsigned long TELEM_CAN_BAUDRATE  = 500000;

// APPS/Brake pedal parameters
const int ACCEL1_MIN_THRESH = 2170;
const int ACCEL2_MIN_THRESH = 1550;
const int ACCEL1_MAX_THRESH = 3308;
const int ACCEL2_MAX_THRESH = 399;
const float APPS_ACTIVATION_PERCENTAGE = 0.1;

const int BRAKE1_MIN_THRESH = 2786;
const int BRAKE2_MIN_THRESH = 921;
const int BRAKE1_MAX_THRESH = 1223;
const int BRAKE2_MAX_THRESH = 2488;
const float BRKAE_ACTIVATION_PERCENTAGE = 0.05;
const float BRAKE_MECH_THRESH = 0.05; // TODO: Determine actual mech threshold

#endif /* __MCU15_H__ */