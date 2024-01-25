#include "InverterInterface.h"

template <typename message_queue>
void InverterInterface<message_queue>::write_cmd_msg_to_queue_(const MC_setpoints_command &msg_in)
{
    CAN_message_t msg;
    msg.id = can_id_;
    msg.len = sizeof(msg_in);
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg_in));
    msg_in.write(msg.buf);
    msg_queue_->push_back(msg, sizeof(CAN_message_t));
}

template <typename message_queue>
void InverterInterface<message_queue>::request_enable_hv()
{

    MC_setpoints_command mc_setpoints_command;
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
    mc_setpoints_command.set_driver_enable(true);
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

    write_cmd_msg_to_queue_(mc_setpoints_command);
}

template <typename message_queue>
void InverterInterface<message_queue>::handle_command(const InverterCommand &command)
{
    MC_setpoints_command mc_setpoints_command;
    mc_setpoints_command.set_speed_setpoint(command.speed_setpoint);
    mc_setpoints_command.set_pos_torque_limit(command.positive_torque_limit);
    mc_setpoints_command.set_neg_torque_limit(command.negative_torque_limit);

    write_cmd_msg_to_queue_(mc_setpoints_command);
}

template <typename message_queue>
void InverterInterface<message_queue>::receive_status_msg(const CAN_message_t &msg)
{
    status_.load(msg);
}
