#include "TelemetryInterface.h"

/* Send CAN messages */
// Pedal readings
void TelemetryInterface::send_CAN_mcu_pedal_readings(CAN_message_t &msg) {
    update_pedal_readings_CAN_msg();
    mcu_pedal_readings_.write(msg.buf);
    msg.id = ID_MCU_PEDAL_READINGS;
    msg.len = sizeof((*mcu_pedal_readings));
}

void TelemetryInterface::update_pedal_readings_CAN_msg() {
    // do sth with mcu_pedal_readings_
}

// Loadcell readings
void TelemetryInterface::send_CAN_mcu_load_cells(CAN_message_t &msg) {
    update_load_cells_CAN_msg();
    mcu_load_cells_.write(msg.buf);
    msg.id = ID_MCU_LOAD_CELLS;
    msg.len = sizeof((*mcu_load_cells));
}

void TelemetryInterface::update_load_cells_CAN_msg() {
    // do sth with mcu_load_cells_
}

// Suspension potentiometers
// Front
void TelemetryInterface::send_CAN_mcu_front_potentiometers(CAN_message_t &msg) {
    update_front_pots_CAN_msg();
    mcu_front_potentiometers_.write(msg.buf);
    msg.id = ID_MCU_FRONT_POTS;
    msg.len = sizeof((*mcu_front_potentiometers));
}

void TelemetryInterface::update_front_pots_CAN_msg() {
    // do sth with mcu_front_potentiometers_
}

// Rear
void TelemetryInterface::send_CAN_mcu_rear_potentiometers(CAN_message_t &msg) {
    update_rear_pots_CAN_msg();
    mcu_rear_potentiometers_.write(msg.buf);
    msg.id = ID_MCU_REAR_POTS;
    msg.len = sizeof((*mcu_rear_potentiometers));
}

void TelemetryInterface::update_rear_pots_CAN_msg() {
    // do sth with mcu_rear_potentiometers_
}

// Analog sensor readings
void TelemetryInterface::send_CAN_mcu_analog_readings(CAN_message_t &msg) {
    mcu_analog_readings_.write(msg.buf);
    msg.id = ID_MCU_ANALOG_READINGS;
    msg.len = sizeof((*mcu_analog_readings));
}

void TelemetryInterface::update_analog_readings_CAN_msg() {
    // do sth with mcu_analog_readings_
}