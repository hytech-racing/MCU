#ifndef __MCU15_H__
#define __MCU15_H__

#include "PedalsSystem.h"
#ifndef TESTING_SYSTEMS
#include "InterfaceParams.h"
#endif


// pindefs
const int ADC1_CS = 34;     // Main ECU
const int ADC2_CS = 33;     // FL corner board
const int ADC3_CS = 29;     // FR corner board
const int SOFTWARE_OK       = 8;
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
// ADC2 channel defs
const int MCU15_FL_POTS_CHANNEL         = 1;
const int MCU15_FR_POTS_CHANNEL         = 1;
const int MCU15_FL_LOADCELL_CHANNEL     = 2;
const int MCU15_FR_LOADCELL_CHANNEL     = 2;

//MCU teensy analog channels
const int MCU15_TEENSY_ADC_CHANNELS = 2;
// const int MCU15_NUM_THERMISTORS = 2;
const int MCU15_THERM_FL = 38;
const int MCU15_THERM_FR = 41;
// const int MCU15_THERM_FL_CHANNEL = 0;
// const int MCU15_THERM_FR_CHANNEL = 1;

const int DEFAULT_ANALOG_PINS[MCU15_TEENSY_ADC_CHANNELS] = {MCU15_THERM_FL, MCU15_THERM_FR};
// Time intervals
const unsigned long SETUP_PRESENT_ACTION_INTERVAL       = 1000;
const unsigned long BUZZER_ON_INTERVAL                  = 2000;
const unsigned long INVERTER_ENABLING_TIMEOUT_INTERVAL  = 5000;

//glv sense conversion
const float GLV_SENSE_SCALE = .0073 * 4.0865;
// Communication speeds
const unsigned long INV_CAN_BAUDRATE    = 500000;
const unsigned long TELEM_CAN_BAUDRATE  = 500000;

// APPS/Brake pedal parameters
// All of these values are the PEDAL min/max
// the sensor min/max that trip implaus are calculated
// in the PedalsSystem constructor
const int ACCEL1_PEDAL_MAX = 3240;  // 3330
const int ACCEL2_PEDAL_MAX = 440;   // 388

const int ACCEL1_PEDAL_MIN = 2124;
const int ACCEL2_PEDAL_MIN = 1517;

const int BRAKE1_PEDAL_MAX = 1745;  // 2200;
const int BRAKE2_PEDAL_MAX = 1935;  // 2200;

const int BRAKE1_PEDAL_MIN = 1235;  // 785;    // 1230 to 1750
const int BRAKE2_PEDAL_MIN = 2445;  // 785;    // 2450 to 1930

const int ACCEL1_PEDAL_OOR_MIN = 90;
const int ACCEL2_PEDAL_OOR_MIN = 90;

const int ACCEL1_PEDAL_OOR_MAX = 4000;
const int ACCEL2_PEDAL_OOR_MAX = 4000;

const int BRAKE1_PEDAL_OOR_MIN = 90;
const int BRAKE2_PEDAL_OOR_MIN = 90;

const int BRAKE1_PEDAL_OOR_MAX = 4000;
const int BRAKE2_PEDAL_OOR_MAX = 4000;

const float DEFAULT_PEDAL_DEADZONE = 0.05f;
const float DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN = 0.10f;

const float APPS_ACTIVATION_PERCENTAGE = 0.1f;
const float BRAKE_ACTIVATION_PERCENTAGE = 0.05f;
const float BRAKE_MECH_THRESH = 0.40f;

// Load Cell Defs to convert raw to lbs
// lbs = (raw + offset) * scale

const float LOADCELL_FL_SCALE = 0.0554;
const float LOADCELL_FL_OFFSET = 19.976 / LOADCELL_FL_SCALE;

const float LOADCELL_FR_SCALE = 0.0514;
const float LOADCELL_FR_OFFSET = 19.892 / LOADCELL_FR_SCALE;

const float LOADCELL_RL_SCALE = 0.0595;
const float LOADCELL_RL_OFFSET = 7.148 / LOADCELL_RL_SCALE;

const float LOADCELL_RR_SCALE = 0.06;
const float LOADCELL_RR_OFFSET = 23.761 / LOADCELL_RR_SCALE;

// Steering parameters
const float PRIMARY_STEERING_SENSE_OFFSET = 0.0; // units are degrees
const int SECONDARY_STEERING_SENSE_LEFTMOST_BOUND = 785;    // 794    // 812    // 130 deg
const int SECONDARY_STEERING_SENSE_RIGHTMOST_BOUND = 3087;    // 3075    // 3179    // 134 deg
const int SECONDARY_STEERING_SENSE_CENTER = 1945;    // 1960    // 1970
const float STEERING_RANGE_DEGREES = 257.0f;    // 253.0f    // 256.05f   // 134+130-7(slop)
const float STEERING_IIR_ALPHA = 0.7f;  // shaves off around 1 deg of max discrepancy

// TC parameters
const float SIMPLE_TC_REAR_TORQUE_SCALE  = 1.0;
const float SIMPLE_TC_REGEN_TORQUE_SCALE = 0.4;

#endif /* __MCU15_H__ */