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

/* Struct holding torque and speed setpoint */
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

    // getter for MC id
    uint32_t get_id() { return can_id_; };

    /* read energy messages handler from HytechCANInterface */
    void receive_energy_msg(CAN_message_t &msg);
    /* read status messages handler from HytechCANInterface */
    void receive_status_msg(CAN_message_t &msg);
    /* read temp messages handler from HytechCANInterface */
    void receive_temp_msg(CAN_message_t &msg);

    /* send MC disable message */
    void disable();
    /* send MC enable HV message */
    void request_enable_hv();
    /* send MC enable message */
    void request_enable_inverter();
    /* send MC command no torque message*/
    void command_no_torque();
    /* sends torque and rpm setpoints to MC */
    void handle_command(const InverterCommand &command);
    /* send MC command reset message*/
    void command_reset();

    /* check if MC is ready */
    bool inverter_system_ready()
    {
        return system_ready_;
    }

    /* check for errors */
    bool error()
    {
        return error_;
    }

    /*check for dc quit on */
    bool dc_quit_on()
    {
        return quit_dc_on_;
    }

    /* check for quit inverter on*/
    bool quit_inverter_on()
    {
        return quit_inverter_on_;
    }

    /* check for dc bus voltage */
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
    /* write setpoints message to the CAN buffer */
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
