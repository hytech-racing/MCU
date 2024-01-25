#include "TelemetryInterface.h"

/* Send CAN messages */
// Pedal readings
void TelemetryInterface::send_CAN_mcu_pedal_readings(CAN_message_t &msg) {
    // update_pedal_readings_CAN_msg();
    mcu_pedal_readings_.write(msg.buf);
    msg.id = ID_MCU_PEDAL_READINGS;
    msg.len = sizeof(mcu_pedal_readings_);
}
// Loadcell readings
void TelemetryInterface::send_CAN_mcu_load_cells(CAN_message_t &msg) {
    // update_load_cells_CAN_msg();
    mcu_load_cells_.write(msg.buf);
    msg.id = ID_MCU_LOAD_CELLS;
    msg.len = sizeof(mcu_load_cells_);
}
// Suspension potentiometers
// Front
void TelemetryInterface::send_CAN_mcu_front_potentiometers(CAN_message_t &msg) {
    // update_front_pots_CAN_msg();
    mcu_front_potentiometers_.write(msg.buf);
    msg.id = ID_MCU_FRONT_POTS;
    msg.len = sizeof(mcu_front_potentiometers_);
}
// Rear
void TelemetryInterface::send_CAN_mcu_rear_potentiometers(CAN_message_t &msg) {
    // update_rear_pots_CAN_msg();
    mcu_rear_potentiometers_.write(msg.buf);
    msg.id = ID_MCU_REAR_POTS;
    msg.len = sizeof(mcu_rear_potentiometers_);
}
// Analog sensor readings
void TelemetryInterface::send_CAN_mcu_analog_readings(CAN_message_t &msg) {
    mcu_analog_readings_.write(msg.buf);
    msg.id = ID_MCU_ANALOG_READINGS;
    msg.len = sizeof(mcu_analog_readings_);
}

/* Update CAN messages */
// Main loop
// PedalDual returns structure
void TelemetryInterface::update_pedal_readings_CAN_msg() {
    // do sth with mcu_pedal_readings_
    // mcu_pedal_readings_.set_accelerator_pedal_1();
    // mcu_pedal_readings_.set_accelerator_pedal_2();
    // mcu_pedal_readings_.set_brake_pedal_1();
    // mcu_pedal_readings_.set_brake_pedal_2();
}
// MCP3208 returns structure
void TelemetryInterface::update_load_cells_CAN_msg() {
    // do sth with mcu_load_cells_
    // mcu_load_cells_.set_RL_load_cell();
    // mcu_load_cells_.set_RR_load_cell();
    // mcu_load_cells_.set_FL_load_cell();
    // mcu_load_cells_.set_FR_load_cell();
}
// MCP3208 returns structure
void TelemetryInterface::update_potentiometers_CAN_msg() {
    // do sth with mcu_front_potentiometers_
    // mcu_front_potentiometers_.set_pot1();
    // mcu_front_potentiometers_.set_pot3();

    // do sth with mcu_rear_potentiometers_
    // mcu_rear_potentiometers_.set_pot4();
    // mcu_rear_potentiometers_.set_pot6();
}
// SteeringDual and MCP3208 return structures
void TelemetryInterface::update_analog_readings_CAN_msg() {
    // do sth with mcu_analog_readings_
    // mcu_analog_readings_.set_steering_1();
    // mcu_analog_readings_.set_steering_2();
    // mcu_analog_readings_.set_hall_effect_current();
    // mcu_analog_readings_.set_glv_battery_voltage();
}