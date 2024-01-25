#ifndef INVERTERINTERFACE
#define INVERTERINTERFACE

#include <stdint.h>

#include "MC_setpoints_command.h"
#include "MC_energy.h"
#include "MC_status.h"
#include "MC_temps.h"

#include "FlexCAN_T4.h"

struct InverterCommand
{

    int16_t speed_setpoint;
    int16_t positive_torque_limit;
    int16_t negative_torque_limit;
};
template <typename message_queue>
class InverterInterface
{
public:
    InverterInterface(message_queue *msg_output_queue, uint32_t can_id)
    {
        msg_queue_ = msg_output_queue;
        can_id_ = can_id;
    }

    uint32_t get_id() { return can_id_; };

    // receive functions
    void receive_energy_msg(CAN_message_t &msg);
    void receive_status_msg(CAN_message_t &msg);
    void receive_temp_msg(CAN_message_t &msg);

    // send msg functions
    void request_enable_hv();
    void request_enable_inverter();
    void command_no_torque();
    void handle_command(const InverterCommand &command);

    
    bool inverter_system_ready()
    {
        return system_ready_;
    }
    
    bool dc_quit_on()
    {
        return quit_dc_on_;
    }
    bool quit_inverter_on()
    {
        return quit_inverter_on_;
    }

    // TODO set this from can msg
    uint16_t dc_bus_voltage()
    {
        return dc_bus_voltage_;
    }

private:
    void write_cmd_msg_to_queue_(const MC_setpoints_command &msg);
    int16_t speed_;
    uint16_t dc_bus_voltage_;
    bool quit_dc_on_;
    bool quit_inverter_on_;
    bool system_ready_;
    message_queue *msg_queue_;
    uint32_t can_id_;
};

#include "InverterInterface.tpp"
#endif /* INVERTERINTERFACE */
