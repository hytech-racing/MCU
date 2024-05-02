#ifndef __MCU15_H__
#define __MCU15_H__

#include "PedalsSystem.h"
#include "NativeEthernet.h"

namespace EthParams
{
    uint8_t default_MCU_MAC_address[6] = 
    {0x04, 0xe9, 0xe5, 0x10, 0x1f, 0x22};

    const IPAddress default_MCU_ip(192, 168, 1, 30);
    const IPAddress default_TCU_ip(192, 168, 1, 69);

    const uint16_t default_protobuf_send_port = 2000;
    const uint16_t default_protobuf_recv_port = 2001;

    const IPAddress default_netmask(255, 255, 255, 0);
    const IPAddress default_gateway(192, 168, 0, 1);

    const uint16_t default_buffer_size = 512;
}

// pindefs
const int ADC1_CS = 34;
const int ADC2_CS = 33;
const int ADC3_CS = 29;
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

// Time intervals
const unsigned long SETUP_PRESENT_ACTION_INTERVAL       = 1000;
const unsigned long BUZZER_ON_INTERVAL                  = 2000;
const unsigned long INVERTER_ENABLING_TIMEOUT_INTERVAL  = 5000;

// Communication speeds
const unsigned long INV_CAN_BAUDRATE    = 500000;
const unsigned long TELEM_CAN_BAUDRATE  = 500000;

// APPS/Brake pedal parameters
// All of these values are the PEDAL min/max
// the sensor min/max that trip implaus are calculated
// in the PedalsSystem constructor
const int ACCEL1_PEDAL_MAX = 3330;
const int ACCEL2_PEDAL_MAX = 388;

const int ACCEL1_PEDAL_MIN = 2124;
const int ACCEL2_PEDAL_MIN = 1517;

const int BRAKE1_PEDAL_MAX = 2200;
const int BRAKE2_PEDAL_MAX = 2200;

const int BRAKE1_PEDAL_MIN = 785;
const int BRAKE2_PEDAL_MIN = 785;

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

const float LOADCELL_FL_SCALE = 0.0553;
const float LOADCELL_FL_OFFSET = 15.892 / LOADCELL_FL_SCALE;

const float LOADCELL_FR_SCALE = 0.0512;
const float LOADCELL_FR_OFFSET = 17.196 / LOADCELL_FR_SCALE;

const float LOADCELL_RL_SCALE = 0.1147;
const float LOADCELL_RL_OFFSET = 21.842 / LOADCELL_RL_SCALE;

const float LOADCELL_RR_SCALE = 0.0588;
const float LOADCELL_RR_OFFSET = 19.576 / LOADCELL_RR_SCALE;

// Steering parameters
const float PRIMARY_STEERING_SENSE_OFFSET = -21.18; // units are degrees
const int SECONDARY_STEERING_SENSE_LEFTMOST_BOUND = 812;
const int SECONDARY_STEERING_SENSE_RIGHTMOST_BOUND = 3179;
const int SECONDARY_STEERING_SENSE_CENTER = 1970;
const float STEERING_RANGE_DEGREES = 256.05f;

#endif /* __MCU15_H__ */