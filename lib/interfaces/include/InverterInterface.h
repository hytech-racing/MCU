#ifndef INVERTERINTERFACE
#define INVERTERINTERFACE

/* System Includes */
#include <Arduino.h>
#include <Metro.h>

/* Library Includes */
#include <stdint.h>
#include "FlexCAN_T4.h"
#include "MCUInterface.h"

#include "MC_setpoints_command.h"
#include "MC_energy.h"
#include "MC_status.h"
#include "MC_temps.h"

/**
 * Struct holding torque and speed setpoint for a particular command to send the Inverter.
 */
struct InverterCommand
{
    float torque_setpoint_nm;
    float speed_setpoint_rpm;
};

/**
 * Templated class representing the interface with one inverter.
 * 
 * This class will read from the Inverter CAN line and stores the data, but does not directly
 * write the data to the Telemetry CAN line. Instead, the TelemetryInterface uses this class's
 * get() functions to write to the Telemetry CAN.
 * 
 * This class also provides an interface to command the Inverters.
 */
template <typename message_queue>
class InverterInterface
{
public:

    /* -------------------- CONSTRUCTOR -------------------- */

    /**
     * Constructor for this InverterInterface.
     * 
     * @param msg_output_queue The Inverter CAN line for this InverterInterface to both read
     *                         from and write to.
     * @param can_id           This InverterInterface's CAN ID. This should be unique for each
     *                         Inverter.
     */
    InverterInterface(message_queue *msg_output_queue, uint32_t can_id)
    {
        id110_val_ = 1.0;
        msg_queue_ = msg_output_queue;
        can_id_ = can_id;
    }



    /* -------------------- CAN RECEIVE FUNCTIONS -------------------- */

    /**
     * Reads this InverterInterface's energy CAN message from HytechCANInterface and updates
     * the dc_bus_voltage_ field. This function still uses the OLD CAN (hytech_can) library
     * and should NOT be used as an example.
     */
    void receive_energy_msg(CAN_message_t &msg);

    /**
     * Reads this InverterInterface's status CAN message from HytechCANInterface and updates
     * several status fields. This function still uses the OLD CAN (hytech_can) library and
     * should NOT be used as an example.
     */
    void receive_status_msg(CAN_message_t &msg);

    /**
     * Reads this InverterInterface's temperature CAN message from HytechCANInterface and
     * updates the mc_temps_ field. This function still uses the OLD CAN (hytech_can) library
     * and should NOT be used as an example.
     */
    void receive_temp_msg(CAN_message_t &msg);



    /* -------------------- COMMAND FUNCTIONS -------------------- */
    
    /**
     * Sends a motor controller command to this InverterInterface's msg_queue_ with the correct
     * CAN ID.
     */
    void disable();

    /**
     * Sends a new motor controller setpoints command over this InverterInterface's msg_queue_
     * that limits torque to 0 and does not enable the driver, but does enable high voltage.
     */
    void request_enable_hv();

    /**
     * Sends a new motor controller setpoints command over this InverterInterface's msg_queue_
     * that limits torque to 0, but enables the inverter and driver.
     */
    void request_enable_inverter();

    /**
     * Sends a new motor controller setpoint command over this InverterInterface's msg_queue_
     * that enables the inverter but requests zero torque.
     */
    void command_no_torque();

    /**
     * Sends a new motor controller setpoint command for 120 RPM, with a 1000 torque limit.
     * This command is only used for debugging purposes, as it does not take into account
     * pedal input.
     */
    void command_debug();

    /**
     * Sends torque and RPM setpoints to the InverterInterface. This function sets the torque
     * limit to be the input command.torque_setpoint_nm, and sets the speed speed setpoint to
     * be the given command.speed_setpoint_rpm.
     */
    void command_inverter(const InverterCommand &command);

    /**
     * Sends MC command reset message.
     */
    void command_reset();



    /* -------------------- GETTERS -------------------- */

    /**
     * Returns the value stored in system_ready_, which is read from the MC in receive_status_msg().
     */
    bool inverter_system_ready()
    {
        return system_ready_;
    }

    /**
     * Returns the value stored in error_, which is read from the MC in receive_status_msg().
     */
    bool get_error()
    {
        return error_;
    }

    /**
     * Returns the value stored in warning_, which is read from the MC in receive_status_msg().
     */
    bool get_warning()
    {
        return warning_;
    }

    /**
     * Returns the value stored in quit_dc_on_, which is read from the MC in receive_status_msg().
     */
    bool get_quit_dc_on()
    {
        return quit_dc_on_;
    }

    /**
     * Returns the value stored in dc_on_, which is read from the MC in receive_status_msg().
     */
    bool get_dc_on()
    {
        return dc_on_;
    }

    /**
     * Returns the value stored in quit_inverter_on_, which is read from the MC in receive_status_msg().
     */
    bool get_quit_inverter_on()
    {
        return quit_inverter_on_;
    }

    /**
     * Returns the value stored in inverter_on_, which is read from the MC in receive_status_msg().
     */
    bool get_inverter_on()
    {
        return inverter_on_;
    }

    /**
     * Returns the value stored in derating_on_, which is read from the MC in receive_status_msg().
     */
    bool get_derating_on()
    {
        return derating_on_;
    }

    /**
     * Returns the value stored in the dc_bus_voltage_ member variable, which gets updated in
     * the receive_energy_msg() function.
     * 
     * @return The DC bus voltage for this InverterInterface.
     */
    uint16_t dc_bus_voltage()
    {
        return dc_bus_voltage_;
    }

    /**
     * Returns this InverterInterface's can_id_.
     */
    uint32_t get_id() { return can_id_; };

    /**
     * Returns the value stored in the speed_ member variable, in RPMs.
     */
    int16_t get_speed_rpm() { return speed_rpm_; }
    
    /**
     * Returns the value stored in the torque_current_ member variable, this should be in amps,
     * but requires id110_val_ to be set correctly. See the following link for more details.
     * 
     * https://www.amk-motion.com/amk-dokucd/dokucd/en/content/resources/pdf-dateien/pdk_205481_kw26-s5-fse-4q_en_.pdf#page=83&zoom=100,76,82
     */
    float get_torque_current() { return torque_current_; }

    /**
     * Returns the value stored in the magnetizing_current member variable, this should be in
     * amps but requires id110_val_ to be set correctly. See the following link for more details.
     * 
     * https://www.amk-motion.com/amk-dokucd/dokucd/en/content/resources/pdf-dateien/pdk_205481_kw26-s5-fse-4q_en_.pdf#page=83&zoom=100,76,82
     */
    float get_mag_current() { return magnetizing_current_; }

    /**
     * Returns the value stored in the actual_torque_nm_ member variable.
     * WARNING! This is not currently being set! The get() function will work, but will not return
     * an accurate value!
     */
    float get_actual_torque() { return actual_torque_nm_; }

    /**
     * Returns this InverterInterface's diagnostic_number_.
     */
    uint16_t get_error_status() { return diagnostic_number_; }

    /**
     * Retreives the last MC_temps message that this InverterInterface received. Generally bad
     * practice, since getter functions exist for most (if not all) of these values. This
     * function uses the OLD CAN (hytech_can) library and should not be used as an example.
     */
    MC_temps get_temps_msg() { return mc_temps_; }

    /**
     * Retreives the value of the curr_cmd_ member variable, which is the last
     * MC_setpoints_command that was written to the Inverter CAN.
     */
    MC_setpoints_command get_cmd_msg() { return curr_cmd_; }

private:
    /**
     * Value for scaling proper iq and id values. See the following link for more details.
     * 
     * https://www.amk-motion.com/amk-dokucd/dokucd/en/content/resources/pdf-dateien/pdk_205481_kw26-s5-fse-4q_en_.pdf#page=83&zoom=100,76,82
     */
    float id110_val_;

    /**
     * The iq and id values in A, respectively.
     */
    float torque_current_, magnetizing_current_;

    /**
     * WARNING! Not currently updated/used.
     */
    float actual_torque_nm_;

    /**
     * The current speed of this wheel in RPM.
     */
    int16_t speed_rpm_;

    /**
     * The current DC bus voltage, in volts.
     */
    uint16_t dc_bus_voltage_;

    /**
     * The diagnostic number of this inverter. See the datasheet for more details.
     */
    uint16_t diagnostic_number_;

    /**
    * Booleans to store data from the MC. Updated in receive_status_msg().
    */
    bool system_ready_;
    bool error_;
    bool warning_;
    bool quit_dc_on_;
    bool dc_on_;
    bool quit_inverter_on_;
    bool inverter_on_;
    bool derating_on_;

    /**
     * The last MC_setpoints_command to be written to the Inverter CAN line. This gets updated
     * in the write() function. This is not the best object-oriented design, since most (all?)
     * of these values have their own getter functions.
     */
    MC_setpoints_command curr_cmd_;

    /**
     * The last MC_temps message this InverterInterface received. This gets updated in the
     * receive_temp_msg() function. This is not the best object-oriented design, since the
     * values in mc_temps_ should be accessible elsewhere.
     */
    MC_temps mc_temps_;

    /**
     * The circular buffer to queue new CAN messages to. All InverterInterfaces typically
     * share the same Inverter CAN line.
     */
    message_queue *msg_queue_;

    /**
     * This inverter's CAN ID.
     */
    uint32_t can_id_;

    /**
     * Timer for writing to the CAN line. This limits sending CAN messages to 50hz. This is
     * deprecated, as we now prefer to use SysTick_s to enforce speed limits, so do NOT use
     * this as an example.
     */
    Metro timer_can_ = Metro(20);

    /**
     * Write setpoints message to the CAN buffer.
     */
    void write_cmd_msg_to_queue_(MC_setpoints_command msg);

};

#include "InverterInterface.tpp"
#endif /* INVERTERINTERFACE */
