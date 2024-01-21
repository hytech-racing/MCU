#include "TelemetryInterface.h"

/* Send CAN messages */
// Pedal readings
void TelemetryInterface::send_CAN_mcu_pedal_readings(CAN_message_t &msg) {
    mcu_pedal_readings.write(msg.buf);
    msg.id = ID_MCU_PEDAL_READINGS;
    msg.len = sizeof((*mcu_pedal_readings));
}

// Loadcell readings
void TelemetryInterface::send_CAN_mcu_load_cells(CAN_message_t &msg) {
    mcu_load_cells.write(msg.buf);
    msg.id = ID_MCU_LOAD_CELLS;
    msg.len = sizeof((*mcu_load_cells));
}

// Suspension potentiometers
// Front
void TelemetryInterface::send_CAN_mcu_potentiometers(CAN_message_t &msg) {
    mcu_front_potentiometers.write(msg.buf);
    msg.id = ID_MCU_FRONT_POTS;
    msg.len = sizeof((*mcu_front_potentiometers));
}

// Rear
void TelemetryInterface::send_CAN_mcu_potentiometers(CAN_message_t &msg) {    
    mcu_rear_potentiometers.write(msg.buf);
    msg.id = ID_MCU_REAR_POTS;
    msg.len = sizeof((*mcu_rear_potentiometers));
}

// Analog sensor readings
void TelemetryInterface::send_CAN_mcu_analog_readings(CAN_message_t &msg) {
    mcu_analog_readings.write(msg.buf);
    msg.id = ID_MCU_ANALOG_READINGS;
    msg.len = sizeof((*mcu_analog_readings));
}