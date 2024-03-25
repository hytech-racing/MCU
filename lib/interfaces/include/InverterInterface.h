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
#include <Metro.h>
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
        id110_val_ = 1.0;
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
    void command_debug();
    /* sends torque and rpm setpoints to MC */
    void handle_command(const InverterCommand &command);
    /* send MC command reset message*/
    void command_reset();

    /* Returns the value stored in system_ready_, which is
       read from the MC in receive_status_msg() */
    bool inverter_system_ready()
    {
        return system_ready_;
    }

    /* Returns the value stored in error_, which is
       read from the MC in receive_status_msg() */
    bool get_error()
    {
        return error_;
    }

    /* Returns the value stored in error_, which is
       read from the MC in receive_status_msg() */
    bool get_warning()
    {
        return warning_;
    }

    /* Returns the value stored in quit_dc_on_, which is
       read from the MC in receive_status_msg() */
    bool get_quit_dc_on()
    {
        return quit_dc_on_;
    }

    /* Returns the value stored in dc_on_, which is
       read from the MC in receive_status_msg() */
    bool get_dc_on()
    {
        return dc_on_;
    }

    /* Returns the value stored in quit_inverter_on_, which is
       read from the MC in receive_status_msg() */
    bool get_quit_inverter_on()
    {
        return quit_inverter_on_;
    }

    /* Returns the value stored in inverter_on_, which is
       read from the MC in receive_status_msg() */
    bool get_inverter_on()
    {
        return inverter_on_;
    }

    /* Returns the value stored in derating_on_, which is
       read from the MC in receive_status_msg() */
    bool get_derating_on()
    {
        return derating_on_;
    }

    /* check for dc bus voltage */
    uint16_t dc_bus_voltage()
    {
        return dc_bus_voltage_;
    }

    int16_t get_speed() { return speed_; }
    float get_torque_current() { return torque_current_; }
    float get_mag_current() { return magnetizing_current_; }
    float get_actual_torque() { return actual_torque_nm_; }
    uint16_t get_error_status();
    MC_temps get_temps_msg() { return mc_temps_; }

private:
    float id110_val_;                            // for scaling to proper iq and id vals
    float torque_current_, magnetizing_current_; // iq and id in A respectively
    float actual_torque_nm_;
    /* write setpoints message to the CAN buffer */
    void write_cmd_msg_to_queue_(MC_setpoints_command msg);
    int16_t speed_;
    uint16_t dc_bus_voltage_;

    /* Booleans to store data from the MC. Updated in receive_status_msg() */
    bool system_ready_;
    bool error_;
    bool warning_;
    bool quit_dc_on_;
    bool dc_on_;
    bool quit_inverter_on_;
    bool inverter_on_;
    bool derating_on_;
    MC_temps mc_temps_;
    message_queue *msg_queue_;
    uint32_t can_id_;
    Metro timer_can_ = Metro(20);
    uint16_t diagnostic_number_;
};

#include "InverterInterface.tpp"
#endif /* INVERTERINTERFACE */
