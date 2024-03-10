#include "TelemetryInterface.h"

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

    enqueue_CAN<MCU_pedal_readings>(mcu_pedal_readings_, ID_MCU_PEDAL_READINGS);
}
// MCP3204 returns structure
void TelemetryInterface::update_load_cells_CAN_msg(const AnalogConversion_s &lc_fl,
                                                   const AnalogConversion_s &lc_fr) {
    // do sth with mcu_load_cells_
    mcu_load_cells_.set_FL_load_cell(lc_fl.raw);
    mcu_load_cells_.set_FR_load_cell(lc_fr.raw);
    // mcu_load_cells_.set_RL_load_cell(lc_fl.raw);
    // mcu_load_cells_.set_RR_load_cell(lc_fr.raw);    

    enqueue_CAN<MCU_load_cells>(mcu_load_cells_, ID_MCU_LOAD_CELLS);
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

    enqueue_CAN<MCU_front_potentiometers>(mcu_front_potentiometers_, ID_MCU_FRONT_POTS);
    // enqueue_CAN<MCU_rear_potentiometers>(mcu_rear_potentiometers_, ID_MCU_REAR_POTS);
}
// SteeringDual and MCP3208 return structures
void TelemetryInterface::update_analog_readings_CAN_msg(const SteeringEncoderConversion_s &steer1,
                                                        const AnalogConversion_s &steer2,
                                                        const AnalogConversion_s &current,
                                                        const AnalogConversion_s &reference,
                                                        const AnalogConversion_s &glv) {
    // do sth with mcu_analog_readings_
    mcu_analog_readings_.set_steering_1(static_cast<int16_t>(steer1.angle * FIXED_POINT_PRECISION));
    mcu_analog_readings_.set_steering_2(steer2.raw);
    mcu_analog_readings_.set_hall_effect_current(current.raw - reference.raw);
    // Serial.println("hall effect current: ");
    // Serial.println(mcu_analog_readings_.get_hall_effect_current());
    mcu_analog_readings_.set_glv_battery_voltage(glv.raw);

    enqueue_CAN<MCU_analog_readings>(mcu_analog_readings_, ID_MCU_ANALOG_READINGS);
}

void TelemetryInterface::update_drivetrain_rpms_CAN_msg(InvInt_t* fl, InvInt_t* fr, InvInt_t* rl, InvInt_t* rr) {
    DRIVETRAIN_RPMS_TELEM_t rpms;
    rpms.fl_motor_rpm = fl->get_speed();
    rpms.fr_motor_rpm = fr->get_speed();
    rpms.rl_motor_rpm = rl->get_speed();
    rpms.rr_motor_rpm = rr->get_speed();
    
    enqueue_new_CAN<DRIVETRAIN_RPMS_TELEM_t>(&rpms, &Pack_DRIVETRAIN_RPMS_TELEM_hytech);
}

void TelemetryInterface::update_drivetrain_err_status_CAN_msg(InvInt_t* fl, InvInt_t* fr, InvInt_t* rl, InvInt_t* rr) {

    if (1) {
        DRIVETRAIN_ERR_STATUS_TELEM_t errors;
        errors.mc1_diagnostic_number = fl->get_error_status();
        errors.mc2_diagnostic_number = fr->get_error_status();
        errors.mc3_diagnostic_number = rl->get_error_status();
        errors.mc4_diagnostic_number = rr->get_error_status();
        enqueue_new_CAN<DRIVETRAIN_ERR_STATUS_TELEM_t>(&errors, &Pack_DRIVETRAIN_ERR_STATUS_TELEM_hytech);
    }
    
}

/* Send CAN messages */
template<typename T>
void TelemetryInterface::enqueue_CAN(T msg_class, uint32_t  id) {
    
    CAN_message_t msg;
    msg_class.write(msg.buf);
    msg.id = id;
    msg.len = sizeof(msg_class);
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(CAN_message_t));

    msg_queue_->push_back(buf, sizeof(CAN_message_t));

}

/* Send inverter CAN messages with new CAN library */
template<typename U>
void TelemetryInterface::enqueue_new_CAN(U* structure, uint32_t (* pack_function)(U*, uint8_t*, uint8_t*, uint8_t*)) {
    CAN_message_t can_msg;
    can_msg.id = pack_function(structure, can_msg.buf, &can_msg.len, (uint8_t*) &can_msg.flags.extended);
    uint8_t buf[sizeof(CAN_message_t)] = {};
    memmove(buf, &can_msg, sizeof(CAN_message_t));
    msg_queue_->push_back(buf, sizeof(CAN_message_t));
}


/* Tick SysClock */
void TelemetryInterface::tick(const AnalogConversionPacket_s<8> &adc1,
                              const AnalogConversionPacket_s<4> &adc2,
                              const AnalogConversionPacket_s<4> &adc3,
                              const SteeringEncoderConversion_s &encoder,
                              const InvInt_t* fl,
                              const InvInt_t* fr,
                              const InvInt_t* rl,
                              const InvInt_t* rr) {

    // Pedals
    update_pedal_readings_CAN_msg(adc1.conversions[channels_.accel1_channel],
                                  adc1.conversions[channels_.accel2_channel],
                                  adc1.conversions[channels_.brake1_channel],
                                  adc1.conversions[channels_.brake2_channel]);
    // enqueue_CAN_mcu_pedal_readings();
    // Analog readings
    update_analog_readings_CAN_msg(encoder,
                                   adc1.conversions[channels_.analog_steering_channel],
                                   adc1.conversions[channels_.current_channel],
                                   adc1.conversions[channels_.current_ref_channel],
                                   adc1.conversions[channels_.glv_sense_channel]);
    // enqueue_CAN_mcu_analog_readings();
    // Load cells
    update_load_cells_CAN_msg(adc2.conversions[channels_.loadcell_fl_channel],
                              adc3.conversions[channels_.loadcell_fr_channel]);
    // enqueue_CAN_mcu_load_cells();
    // Pots
    update_potentiometers_CAN_msg(adc2.conversions[channels_.pots_fl_channel],
                                  adc3.conversions[channels_.pots_fr_channel]);

    update_drivetrain_rpms_CAN_msg(fl, fr, rl, rr);
    update_drivetrain_err_status_CAN_msg(fl, fr, rl, rr);
    // enqueue_CAN_mcu_front_potentiometers();
    // enqueue_CAN_mcu_rear_potentiometers();

}
