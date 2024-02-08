#ifndef INVERTERINTERFACE
#define INVERTERINTERFACE

#include <stdint.h>

#include "MC_setpoints_command.h"
#include "MC_energy.h"
#include "MC_status.h"
#include "MC_temps.h"

#include "FlexCAN_T4.h"
#include "MCUInterface.h"

#include <Arduino.h>
struct InverterCommand
{
    float torque_setpoint_nm;
    float speed_setpoint_rpm;
};
template <typename message_queue>
class InverterInterface
{
public:
    InverterInterface(message_queue *msg_output_queue, uint32_t can_id, int inverter_enable_pin, int inverter_24v_enable_pin)
    {

        msg_queue_ = msg_output_queue;
        can_id_ = can_id;
        pin_inv_en_ = inverter_enable_pin;
        pin_inv_24V_en_ = inverter_24v_enable_pin;
        pinMode(pin_inv_en_, OUTPUT);
        pinMode(pin_inv_24V_en_, OUTPUT);
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
    void command_reset();

    
    bool inverter_system_ready()
    {
        return system_ready_;
    }
    bool error()
    {
        return error_;
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
    int pin_inv_en_, pin_inv_24V_en_;
    void write_cmd_msg_to_queue_(const MC_setpoints_command &msg);
    int16_t speed_;
    uint16_t dc_bus_voltage_;
    bool error_;
    bool quit_dc_on_;
    bool quit_inverter_on_;
    bool system_ready_;
    message_queue *msg_queue_;
    uint32_t can_id_;
};

#include "InverterInterface.tpp"
#endif /* INVERTERINTERFACE */
