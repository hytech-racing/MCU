#include "InverterInterface.h"

template <typename message_queue>
void InverterInterface<message_queue>::write_cmd_msg_to_queue_(MC_setpoints_command msg_in)
{
    auto test = msg_in;
    curr_cmd_ = msg_in;
    if (timer_can_.check()) {
        CAN_message_t msg;
        msg.id = can_id_;
        msg.len = sizeof(msg_in);
        test.write(msg.buf);
        uint8_t buf[sizeof(msg)];
        memmove(buf, &msg, sizeof(msg));
        msg_queue_->push_back(buf, sizeof(CAN_message_t));
    }
}

template <typename message_queue>
void InverterInterface<message_queue>::request_enable_hv()
{
    
    MC_setpoints_command mc_setpoints_command;
    mc_setpoints_command.set_speed_setpoint(0);
    mc_setpoints_command.set_pos_torque_limit(0);
    mc_setpoints_command.set_neg_torque_limit(0);
    mc_setpoints_command.set_remove_error(false);
    mc_setpoints_command.set_driver_enable(false);
    mc_setpoints_command.set_inverter_enable(false);
    mc_setpoints_command.set_hv_enable(true);
    write_cmd_msg_to_queue_(mc_setpoints_command);
}

template <typename message_queue>
void InverterInterface<message_queue>::request_enable_inverter()
{
    MC_setpoints_command mc_setpoints_command;
    mc_setpoints_command.set_speed_setpoint(0);
    mc_setpoints_command.set_pos_torque_limit(0);
    mc_setpoints_command.set_neg_torque_limit(0);
    mc_setpoints_command.set_remove_error(false);
    mc_setpoints_command.set_driver_enable(true);
    mc_setpoints_command.set_hv_enable(true);
    mc_setpoints_command.set_inverter_enable(true);
    // Serial.println("requesting enabling inverter");
    write_cmd_msg_to_queue_(mc_setpoints_command);
}
template <typename message_queue>
void InverterInterface<message_queue>::disable()
{
    MC_setpoints_command mc_setpoints_command;
    mc_setpoints_command.set_inverter_enable(false);
    mc_setpoints_command.set_hv_enable(false);
    mc_setpoints_command.set_driver_enable(false);
    mc_setpoints_command.set_remove_error(false);
    mc_setpoints_command.set_speed_setpoint(0);
    mc_setpoints_command.set_pos_torque_limit(0);
    mc_setpoints_command.set_neg_torque_limit(0);
    write_cmd_msg_to_queue_(mc_setpoints_command);
}
template <typename message_queue>
void InverterInterface<message_queue>::command_debug()
{
    MC_setpoints_command mc_setpoints_command;
    
    mc_setpoints_command.set_speed_setpoint(120);
    mc_setpoints_command.set_pos_torque_limit(1000);
    mc_setpoints_command.set_neg_torque_limit(0);
    mc_setpoints_command.set_driver_enable(true);
    mc_setpoints_command.set_hv_enable(true);
    mc_setpoints_command.set_inverter_enable(true);
    write_cmd_msg_to_queue_(mc_setpoints_command);
}

template <typename message_queue>
void InverterInterface<message_queue>::command_no_torque()
{
    MC_setpoints_command mc_setpoints_command;
    
    mc_setpoints_command.set_speed_setpoint(0);
    mc_setpoints_command.set_pos_torque_limit(0);
    mc_setpoints_command.set_neg_torque_limit(0);
    mc_setpoints_command.set_driver_enable(true);
    mc_setpoints_command.set_hv_enable(true);
    mc_setpoints_command.set_inverter_enable(true);
    write_cmd_msg_to_queue_(mc_setpoints_command);
}

template <typename message_queue>
void InverterInterface<message_queue>::handle_command(const InverterCommand &command)
{
    MC_setpoints_command mc_setpoints_command;
    mc_setpoints_command.set_driver_enable(true);
    mc_setpoints_command.set_hv_enable(true);
    mc_setpoints_command.set_inverter_enable(true);
    int16_t torque_cmd = (command.torque_setpoint_nm/21.42)*1000;
    
    // Serial.println(torque_cmd);
    mc_setpoints_command.set_speed_setpoint((int16_t)command.speed_setpoint_rpm);
    mc_setpoints_command.set_neg_torque_limit(-abs(torque_cmd));
    mc_setpoints_command.set_pos_torque_limit(abs(torque_cmd));
    write_cmd_msg_to_queue_(mc_setpoints_command);
}

template <typename message_queue>
void InverterInterface<message_queue>::command_reset()
{
    MC_setpoints_command mc_setpoints_command;
    mc_setpoints_command.set_remove_error(true);
    write_cmd_msg_to_queue_(mc_setpoints_command);
}

template <typename message_queue>
void InverterInterface<message_queue>::receive_status_msg(CAN_message_t &msg)
{
    MC_status mc_status;
    mc_status.load(msg.buf);

    system_ready_ = mc_status.get_system_ready();
    error_ = mc_status.get_error();
    warning_ = mc_status.get_warning();
    quit_dc_on_ = mc_status.get_quit_dc_on();
    dc_on_ = mc_status.get_dc_on();
    quit_inverter_on_ = mc_status.get_quit_inverter_on();
    inverter_on_ = mc_status.get_inverter_on();
    derating_on_ = mc_status.get_derating_on();

    speed_ = mc_status.get_speed();

    // TODO FIXME see 8.2.3 Units on page 83 of
    // https://www.amk-motion.com/amk-dokucd/dokucd/en/content/resources/pdf-dateien/pdk_205481_kw26-s5-fse-4q_en_.pdf#page=83&zoom=100,76,82
    // for the actual conversion. requires looking at the current params of the inverter
    // to get scalar for this.
    // torque_current_ = ((float)mc_status.get_torque_current() * id110_val_) / 16384.0;           // iq
    torque_current_ = mc_status.get_torque_current();
    magnetizing_current_ = ((float)mc_status.get_magnetizing_current() * id110_val_) / 16384.0; // id

    // TODO enable this on the inverters
    // actual torque in Nm is from the signal we can add in from here:
    // https://www.amk-motion.com/amk-dokucd/dokucd/en/content/resources/pdf-dateien/pdk_205481_kw26-s5-fse-4q_en_.pdf#page=75
    // it is given in units of 0.1% Mn or 0.1% of the max torque 9.8 Nm
    // actual_torque_nm_ = ((float)mc_status.get_actual_torque_value()) / (.001 * 9.8); 
    
    // if(error_)
    // {
    //     Serial.println("got error in dt");
    //     Serial.println(can_id_);
    // }
}

// TODO fill this in with the correct receiving
template <typename message_queue>
void InverterInterface<message_queue>::receive_energy_msg(CAN_message_t &msg)
{
    MC_energy mc_energy(&msg.buf[0]);
    dc_bus_voltage_ = mc_energy.get_dc_bus_voltage();
}

template <typename message_queue>
void InverterInterface<message_queue>::receive_temp_msg(CAN_message_t &msg)
{
    MC_temps mc_temps(&msg.buf[0]);
    // TODO use this (not currently being used in old main)
    mc_temps_ = mc_temps;
    diagnostic_number_ = mc_temps.get_diagnostic_number();
}

template <typename message_queue>
uint16_t InverterInterface<message_queue>::get_error_status()
{
    return diagnostic_number_;
}