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
// MCP3208 returns structure
void TelemetryInterface::update_pedal_readings_CAN_msg(const AnalogConversion_s &accel1,
                                                       const AnalogConversion_s &accel2,
                                                       const AnalogConversion_s &brake1,
                                                       const AnalogConversion_s &brake2) {
    // do sth with mcu_pedal_readings_
    mcu_pedal_readings_.set_accelerator_pedal_1(accel1.raw);
    mcu_pedal_readings_.set_accelerator_pedal_2(accel2.raw);
    mcu_pedal_readings_.set_brake_pedal_1(brake1.raw);
    mcu_pedal_readings_.set_brake_pedal_2(brake2.raw);
}
// MCP3204 returns structure
void TelemetryInterface::update_load_cells_CAN_msg(const AnalogConversion_s &lc_fl,
                                                   const AnalogConversion_s &lc_fr) {
    // do sth with mcu_load_cells_
    mcu_load_cells_.set_RL_load_cell(lc_fl.raw);
    mcu_load_cells_.set_RR_load_cell(lc_fr.raw);
    // mcu_load_cells_.set_FL_load_cell(lc_rl.raw);
    // mcu_load_cells_.set_FR_load_cell(lc_rr.raw);
}
// MCP3204 returns structure
void TelemetryInterface::update_potentiometers_CAN_msg(const AnalogConversion_s &pots_fl,
                                                       const AnalogConversion_s &pots_fr) {
    // do sth with mcu_front_potentiometers_
    mcu_front_potentiometers_.set_pot1(pots_fl.raw);
    mcu_front_potentiometers_.set_pot3(pots_fr.raw);

    // do sth with mcu_rear_potentiometers_
    // mcu_rear_potentiometers_.set_pot4(pots_rl.raw);
    // mcu_rear_potentiometers_.set_pot6(pots_rr.raw);
}
// SteeringDual and MCP3208 return structures
void TelemetryInterface::update_analog_readings_CAN_msg(const SteeringEncoderConversion_s &steer1,
                                                        const AnalogConversion_s &steer2,
                                                        const AnalogConversion_s &current,
                                                        const AnalogConversion_s &reference,
                                                        const AnalogConversion_s &glv) {
    // do sth with mcu_analog_readings_
    mcu_analog_readings_.set_steering_1(steer1.angle);
    mcu_analog_readings_.set_steering_2(steer2.raw);
    mcu_analog_readings_.set_hall_effect_current(current.raw - reference.raw);
    mcu_analog_readings_.set_glv_battery_voltage(glv.raw);
}

void TelemetryInterface::tick(const SysTick_s &tick, 
                              CAN_message_t &msg,
                              const AnalogConversionPacket_s<8> &adc1,
                              const AnalogConversionPacket_s<4> &adc2,
                              const AnalogConversionPacket_s<4> &adc3,
                              const SteeringEncoderConversion_s &encoder) {

    if (tick.triggers.trigger50) {
        // Pedals
        update_pedal_readings_CAN_msg(adc1.conversions[2], adc1.conversions[1], adc1.conversions[5], adc1.conversions[3]);
        send_CAN_mcu_pedal_readings(msg);
        // Analog readings
        update_analog_readings_CAN_msg(encoder, adc1.conversions[7], adc1.conversions[6], adc1.conversions[0], adc1.conversions[4]);
        send_CAN_mcu_analog_readings(msg);
        // Load cells
        update_load_cells_CAN_msg(adc2.conversions[2], adc3.conversions[2]);
        send_CAN_mcu_load_cells(msg);
        // Pots
        update_potentiometers_CAN_msg(adc2.conversions[3]. adc3.conversions[3]);
        send_CAN_mcu_front_potentiometers(msg);
        // send_CAN_mcu_rear_potentiometers(msg);
    }

}