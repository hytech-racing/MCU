#include "TelemetryInterface.h"
/* Update CAN messages */
// Main loop
// MCP3208 returns structure
void TelemetryInterface::update_pedal_readings_CAN_msg(float accel_percent,
                                                       float brake_percent,
                                                       float mech_brake_percent)
{

    MCU_PEDAL_READINGS_t pedal_readings;

    pedal_readings.accel_percent_float_ro = HYTECH_accel_percent_float_ro_toS(accel_percent * 100);
    pedal_readings.brake_percent_float_ro = HYTECH_brake_percent_float_ro_toS(brake_percent * 100);
    pedal_readings.mechanical_brake_percent_float_ro = HYTECH_mechanical_brake_percent_float_ro_toS(mech_brake_percent * 100);

    enqueue_new_CAN<MCU_PEDAL_READINGS_t>(&pedal_readings, &Pack_MCU_PEDAL_READINGS_hytech);
}
void TelemetryInterface::update_pedal_readings_raw_CAN_msg(const AnalogConversion_s &accel_1,
                                                           const AnalogConversion_s &accel_2,
                                                           const AnalogConversion_s &brake_1,
                                                           const AnalogConversion_s &brake_2)
{
    MCU_PEDAL_RAW_t pedal_read;

    pedal_read.accel_1_raw = accel_1.raw;
    pedal_read.accel_2_raw = accel_2.raw;
    pedal_read.brake_1_raw = brake_1.raw;
    pedal_read.brake_2_raw = brake_2.raw;

    enqueue_new_CAN<MCU_PEDAL_RAW_t>(&pedal_read, &Pack_MCU_PEDAL_RAW_hytech);
}
// MCP3204 returns structure
void TelemetryInterface::update_suspension_CAN_msg(const AnalogConversion_s &lc_fl,
                                                   const AnalogConversion_s &lc_fr,
                                                   const AnalogConversion_s &pots_fl,
                                                   const AnalogConversion_s &pots_fr)
{
    MCU_SUSPENSION_t sus;
    sus.load_cell_fl = lc_fl.raw;
    sus.load_cell_fr = lc_fr.raw;
    sus.potentiometer_fl = pots_fl.raw;
    sus.potentiometer_fr = pots_fr.raw;

    enqueue_new_CAN<MCU_SUSPENSION_t>(&sus, &Pack_MCU_SUSPENSION_hytech);
}
// SteeringDual and MCP3208 return structures
void TelemetryInterface::update_analog_readings_CAN_msg(const SteeringEncoderConversion_s &steer1,
                                                        const AnalogConversion_s &steer2,
                                                        const AnalogConversion_s &current,
                                                        const AnalogConversion_s &reference,
                                                        const AnalogConversion_s &glv)
{
    // do sth with mcu_analog_readings_
    mcu_analog_readings_.set_steering_1(steer1.raw);
    mcu_analog_readings_.set_steering_2(steer2.raw);
    mcu_analog_readings_.set_hall_effect_current(current.raw - reference.raw);  // this is wrong btw. should let analog channel do the math but not necessary atm
    mcu_analog_readings_.set_glv_battery_voltage(glv.conversion * FIXED_POINT_PRECISION);

    enqueue_CAN<MCU_analog_readings>(mcu_analog_readings_, ID_MCU_ANALOG_READINGS);
}

void TelemetryInterface::update_drivetrain_rpms_CAN_msg(InvInt_t *fl, InvInt_t *fr, InvInt_t *rl, InvInt_t *rr)
{
    DRIVETRAIN_RPMS_TELEM_t rpms;
    rpms.fl_motor_rpm = fl->get_speed();
    rpms.fr_motor_rpm = fr->get_speed();
    rpms.rl_motor_rpm = rl->get_speed();
    rpms.rr_motor_rpm = rr->get_speed();

    enqueue_new_CAN<DRIVETRAIN_RPMS_TELEM_t>(&rpms, &Pack_DRIVETRAIN_RPMS_TELEM_hytech);
}

void TelemetryInterface::update_drivetrain_err_status_CAN_msg(InvInt_t *fl, InvInt_t *fr, InvInt_t *rl, InvInt_t *rr)
{

    if (1)
    { // We should only write error status if some error has occurred, but for now, this is just an if(1)
        DRIVETRAIN_ERR_STATUS_TELEM_t errors;
        errors.mc1_diagnostic_number = fl->get_error_status();
        errors.mc2_diagnostic_number = fr->get_error_status();
        errors.mc3_diagnostic_number = rl->get_error_status();
        errors.mc4_diagnostic_number = rr->get_error_status();
        enqueue_new_CAN<DRIVETRAIN_ERR_STATUS_TELEM_t>(&errors, &Pack_DRIVETRAIN_ERR_STATUS_TELEM_hytech);
    }
}

void TelemetryInterface::update_drivetrain_status_telem_CAN_msg(
    InvInt_t *fl,
    InvInt_t *fr,
    InvInt_t *rl,
    InvInt_t *rr,
    bool accel_implaus,
    bool brake_implaus,
    float accel_per,
    float brake_per)
{
    DRIVETRAIN_STATUS_TELEM_t status;

    status.mc1_dc_on = fl->get_dc_on();
    status.mc1_derating_on = fl->get_derating_on();
    status.mc1_error = fl->get_error();
    status.mc1_inverter_on = fl->get_inverter_on();
    status.mc1_quit_dc = fl->get_quit_dc_on();
    status.mc1_quit_inverter_on = fl->get_quit_inverter_on();
    status.mc1_system_ready = fl->inverter_system_ready();
    status.mc1_warning = fl->get_warning();

    status.mc2_dc_on = fr->get_dc_on();
    status.mc2_derating_on = fr->get_derating_on();
    status.mc2_error = fr->get_error();
    status.mc2_inverter_on = fr->get_inverter_on();
    status.mc2_quit_dc = fr->get_quit_dc_on();
    status.mc2_quit_inverter_on = fr->get_quit_inverter_on();
    status.mc2_system_ready = fr->inverter_system_ready();
    status.mc2_warning = fr->get_warning();

    status.mc3_dc_on = rl->get_dc_on();
    status.mc3_derating_on = rl->get_derating_on();
    status.mc3_error = rl->get_error();
    status.mc3_inverter_on = rl->get_inverter_on();
    status.mc3_quit_dc = rl->get_quit_dc_on();
    status.mc3_quit_inverter_on = rl->get_quit_inverter_on();
    status.mc3_system_ready = rl->inverter_system_ready();
    status.mc3_warning = rl->get_warning();

    status.mc4_dc_on = rr->get_dc_on();
    status.mc4_derating_on = rr->get_derating_on();
    status.mc4_error = rr->get_error();
    status.mc4_inverter_on = rr->get_inverter_on();
    status.mc4_quit_dc = rr->get_quit_dc_on();
    status.mc4_quit_inverter_on = rr->get_quit_inverter_on();
    status.mc4_system_ready = rr->inverter_system_ready();
    status.mc4_warning = rr->get_warning();

    status.accel_implausible = accel_implaus;
    status.brake_implausible = brake_implaus;
    status.brake_percent = (uint8_t)(abs(brake_per) * 100);
    status.accel_percent = (uint8_t)(abs(accel_per) * 100);

    MC_temps mc1_temps = fl->get_temps_msg();
    MC_temps mc2_temps = fr->get_temps_msg();
    MC_temps mc3_temps = rl->get_temps_msg();
    MC_temps mc4_temps = rr->get_temps_msg();

    MC_setpoints_command mc1_cmd = fl->get_cmd_msg();
    MC_setpoints_command mc2_cmd = fr->get_cmd_msg();
    MC_setpoints_command mc3_cmd = rl->get_cmd_msg();
    MC_setpoints_command mc4_cmd = rr->get_cmd_msg();

    enqueue_CAN<MC_temps>(mc1_temps, ID_MC1_TEMPS);
    enqueue_CAN<MC_temps>(mc2_temps, ID_MC2_TEMPS);
    enqueue_CAN<MC_temps>(mc3_temps, ID_MC3_TEMPS);
    enqueue_CAN<MC_temps>(mc4_temps, ID_MC4_TEMPS);
    enqueue_CAN<MC_setpoints_command>(mc1_cmd, ID_MC1_SETPOINTS_COMMAND);
    enqueue_CAN<MC_setpoints_command>(mc2_cmd, ID_MC2_SETPOINTS_COMMAND);
    enqueue_CAN<MC_setpoints_command>(mc3_cmd, ID_MC3_SETPOINTS_COMMAND);
    enqueue_CAN<MC_setpoints_command>(mc4_cmd, ID_MC4_SETPOINTS_COMMAND);
    enqueue_new_CAN<DRIVETRAIN_STATUS_TELEM_t>(&status, &Pack_DRIVETRAIN_STATUS_TELEM_hytech);
}

void TelemetryInterface::update_drivetrain_torque_telem_CAN_msg(
    InvInt_t *fl,
    InvInt_t *fr,
    InvInt_t *rl,
    InvInt_t *rr)
{
    // TODO: change this to use actual torque values from inverter
    // Torque current just temporary for gearbox seal validation
    DRIVETRAIN_TORQUE_TELEM_t torque;
    torque.fl_motor_torque = fl->get_motor_torque();
    torque.fr_motor_torque = fr->get_motor_torque();
    torque.rl_motor_torque = rl->get_motor_torque();
    torque.rr_motor_torque = rr->get_motor_torque();

    enqueue_new_CAN<DRIVETRAIN_TORQUE_TELEM_t>(&torque, &Pack_DRIVETRAIN_TORQUE_TELEM_hytech);
}

void TelemetryInterface::update_drivetrain_torque_filter_out_telem_CAN_msg(
                                                                InvInt_t* fl,
                                                                InvInt_t* fr,
                                                                InvInt_t* rl,
                                                                InvInt_t* rr)
{
    // TODO: change this to use actual torque values from inverter
    // Torque current just temporary for gearbox seal validation
    DRIVETRAIN_FILTER_OUT_TORQUE_TEL_t torque;
    torque.fl_motor_torque = fl->get_commanded_torque();
    torque.fr_motor_torque = fr->get_commanded_torque();
    torque.rl_motor_torque = rl->get_commanded_torque();
    torque.rr_motor_torque = rr->get_commanded_torque();

    enqueue_new_CAN<DRIVETRAIN_FILTER_OUT_TORQUE_TEL_t>(&torque, &Pack_DRIVETRAIN_FILTER_OUT_TORQUE_TEL_hytech);
}

// Pack_PENTHOUSE_ACCUM_MSG_hytech
void TelemetryInterface::update_penthouse_accum_CAN_msg(const AnalogConversion_s &current, const AnalogConversion_s &reference)
{
    PENTHOUSE_ACCUM_MSG_t message;
    message.hall_curr_ref = reference.raw;
    message.hall_curr_signal = current.raw;

    enqueue_new_CAN<PENTHOUSE_ACCUM_MSG_t>(&message, &Pack_PENTHOUSE_ACCUM_MSG_hytech);
}

void TelemetryInterface::update_steering_status_CAN_msg(const float steering_system_angle,
                                                        const float filtered_angle_encoder,
                                                        const float filtered_angle_analog,
                                                        const uint8_t steering_system_status,
                                                        const uint8_t steering_encoder_status,
                                                        const uint8_t steering_analog_status)
{
    STEERING_SYSTEM_REPORT_t msg;

    msg.steering_system_angle_ro = HYTECH_steering_system_angle_ro_toS(steering_system_angle);
    msg.steering_encoder_angle_ro = HYTECH_steering_encoder_angle_ro_toS(filtered_angle_encoder);
    msg.steering_analog_angle_ro = HYTECH_steering_analog_angle_ro_toS(filtered_angle_analog);
    msg.steering_system_status = steering_system_status;
    msg.steering_encoder_status = steering_encoder_status;
    msg.steering_analog_status = steering_analog_status;

    enqueue_new_CAN<STEERING_SYSTEM_REPORT_t>(&msg, &Pack_STEERING_SYSTEM_REPORT_hytech);
}

/* Send CAN messages */
template <typename T>
void TelemetryInterface::enqueue_CAN(T msg_class, uint32_t id)
{

    CAN_message_t msg;
    msg_class.write(msg.buf);
    msg.id = id;
    msg.len = sizeof(msg_class);
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(CAN_message_t));

    msg_queue_->push_back(buf, sizeof(CAN_message_t));
}

/* Send inverter CAN messages with new CAN library */
template <typename U>
void TelemetryInterface::enqueue_new_CAN(U *structure, uint32_t (*pack_function)(U *, uint8_t *, uint8_t *, uint8_t *))
{
    CAN_message_t can_msg;
    can_msg.id = pack_function(structure, can_msg.buf, &can_msg.len, (uint8_t *)&can_msg.flags.extended);
    uint8_t buf[sizeof(CAN_message_t)] = {};
    memmove(buf, &can_msg, sizeof(CAN_message_t));
    msg_queue_->push_back(buf, sizeof(CAN_message_t));
}


/* Tick SysClock */
void TelemetryInterface::tick(const AnalogConversionPacket_s<8> &adc1,
                              const AnalogConversionPacket_s<4> &adc2,
                              const AnalogConversionPacket_s<4> &adc3,
                              const SteeringEncoderConversion_s &encoder,
                              InvInt_t *fl,
                              InvInt_t *fr,
                              InvInt_t *rl,
                              InvInt_t *rr,
                              bool accel_implaus,
                              bool brake_implaus,
                              float accel_per,
                              float brake_per,
                              const AnalogConversion_s &accel_1,
                              const AnalogConversion_s &accel_2,
                              const AnalogConversion_s &brake_1,
                              const AnalogConversion_s &brake_2,
                              float mech_brake_active_percent,
                              const TorqueControllerMuxError &current_mux_status)
{

    MCU_ERROR_STATES_t error_states;
    error_states.torque_controller_mux_status = static_cast<uint8_t>(current_mux_status);
    enqueue_new_CAN<MCU_ERROR_STATES_t>(&error_states, &Pack_MCU_ERROR_STATES_hytech);

    // Pedals
    update_pedal_readings_CAN_msg(accel_per,
                                  brake_per,
                                  mech_brake_active_percent);

    update_pedal_readings_raw_CAN_msg(accel_1,
                                      accel_2,
                                      brake_1,
                                      brake_2);
    // Analog readings
    update_analog_readings_CAN_msg(encoder,
                                   adc1.conversions[channels_.analog_steering_channel],
                                   adc1.conversions[channels_.current_channel],
                                   adc1.conversions[channels_.current_ref_channel],
                                   adc1.conversions[channels_.glv_sense_channel]);
    // Load cells
    update_suspension_CAN_msg(adc2.conversions[channels_.loadcell_fl_channel],
                              adc3.conversions[channels_.loadcell_fr_channel],
                              adc2.conversions[channels_.pots_fl_channel],
                              adc3.conversions[channels_.pots_fr_channel]);

    update_drivetrain_rpms_CAN_msg(fl, fr, rl, rr);
    update_drivetrain_err_status_CAN_msg(fl, fr, rl, rr);
    update_drivetrain_status_telem_CAN_msg(fl, fr, rl, rr, accel_implaus, brake_implaus, accel_per, brake_per);
    update_drivetrain_torque_telem_CAN_msg(fl, fr, rl, rr);
    update_drivetrain_torque_filter_out_telem_CAN_msg(fl, fr, rl, rr);

    update_penthouse_accum_CAN_msg(adc1.conversions[channels_.current_channel],
                                   adc1.conversions[channels_.current_ref_channel]);

}