#include "InverterInterface.h"

template <typename message_queue>
void InverterInterface<message_queue>::request_enable_hv()
{

    MC_setpoints_command mc_setpoints_command;

    mc_setpoints_command.set_hv_enable(true);
    ht_can_msg<MC_setpoints_command> mc_setpoints_command_msg = {can_id_, mc_setpoints_command, sizeof(mc_setpoints_command_msg)};
    msg_queue_->enqueue(mc_setpoints_command_msg);
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
    ht_can_msg<MC_setpoints_command> mc_setpoints_command_msg = {can_id_, mc_setpoints_command, sizeof(mc_setpoints_command_msg)};
    msg_queue_->enqueue(mc_setpoints_command_msg);
}

template <typename message_queue>
void InverterInterface<message_queue>::command_no_torque()
{
    MC_setpoints_command mc_setpoints_command;
    mc_setpoints_command.set_speed_setpoint(0);
    mc_setpoints_command.set_pos_torque_limit(0);
    mc_setpoints_command.set_neg_torque_limit(0);
    ht_can_msg<MC_setpoints_command> mc_setpoints_command_msg = {can_id_, mc_setpoints_command, sizeof(mc_setpoints_command_msg)};
    msg_queue_->enqueue(mc_setpoints_command_msg);
}

template <typename message_queue>
void InverterInterface<message_queue>::handle_command(const InverterCommand &command)
{
    MC_setpoints_command mc_setpoints_command;
    mc_setpoints_command.set_speed_setpoint(command.speed_setpoint);
    mc_setpoints_command.set_pos_torque_limit(command.positive_torque_limit);
    mc_setpoints_command.set_neg_torque_limit(command.negative_torque_limit);
    ht_can_msg<MC_setpoints_command> mc_setpoints_command_msg = {can_id_, mc_setpoints_command, sizeof(mc_setpoints_command_msg)};
    msg_queue_->enqueue(mc_setpoints_command_msg);
}

template <typename message_queue>
void InverterInterface<message_queue>::handle_receive(const MC_energy &msg)
{

}

template <typename message_queue>
void InverterInterface<message_queue>::handle_receive(const MC_status &msg)
{
    quit_dc_on_ = msg.get_quit_dc_on();
    system_ready_ = msg.get_system_ready();
    quit_inverter_on_ = msg.get_quit_inverter_on();
    
}

template <typename message_queue>
void InverterInterface<message_queue>::handle_receive(const MC_temps &msg)
{
}