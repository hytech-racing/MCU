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
    InverterInterface(message_queue *msg_output_queue, uint32_t can_id)
    {
        // TODO fix me with correct value from config of inverter
        id110_val_= 1.0;
        msg_queue_ = msg_output_queue;
        can_id_ = can_id;
        
    }

    uint32_t get_id() { return can_id_; };

    // receive functions
    void receive_energy_msg(CAN_message_t &msg);
    void receive_status_msg(CAN_message_t &msg);
    void receive_temp_msg(CAN_message_t &msg);

    // send msg functions
    void disable();
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

    uint16_t dc_bus_voltage()
    {
        return dc_bus_voltage_;
    }

    int16_t get_speed() { return speed_; }
    float get_torque_current() {return torque_current_;}
    float get_mag_current() {return magnetizing_current_;}
    float get_actual_torque() {return actual_torque_nm_; }

private:
    float id110_val_;                            // for scaling to proper iq and id vals
    float torque_current_, magnetizing_current_; // iq and id in A respectively
    float actual_torque_nm_;
    void write_cmd_msg_to_queue_(MC_setpoints_command &msg);
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
