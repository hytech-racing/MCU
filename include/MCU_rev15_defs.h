#ifndef __MCU15_H__
#define __MCU15_H__

#include <Arduino.h>

// pindefs
#define ADC1_CS 34
#define STEERING_SERIAL &Serial5

// ADC1 channel defs
#define MCU15_ACCEL1_CHANNEL        2
#define MCU15_ACCEL2_CHANNEL        1
#define MCU15_BRAKE1_CHANNEL        5
#define MCU15_BRAKE2_CHANNEL        3
#define MCU15_GLV_SENSE_CHANNEL     4
#define MCU15_STEERING_CHANNEL      7
#define MCU15_CUR_POS_SENSE_CHANNEL 6
#define MCU15_CUR_NEG_SENSE_CHANNEL 0

#endif /* __MCU15_H__ */