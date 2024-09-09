#ifndef __MCU_INTERFACE_H__
#define __MCU_INTERFACE_H__

/* Standard Includes */
#include <stdint.h>

/* Library Includes */
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "hytech.h"

/* System Includes */
#include "MessageQueueDefine.h"
#include "PedalsSystem.h"

/* Constant definitions */
const int DEFAULT_BMS_OK_READ         = 17;      // SHDN_D_READ
const int DEFAULT_BMS_SENSE_PIN       = 16;      // BMS_OK_SENSE
const int DEFAULT_IMD_OK_READ         = 10;      // SHDN_C_READ
const int DEFAULT_IMD_SENSE_PIN       = 18;      // OKHS_SENSE
const int DEFAULT_BSPD_OK_READ        = 39;      // SHDN_E_READ
const int DEFAULT_SOFTWARE_OK_READ    = 25;      // SHDN_F_READ Watchdog Combined
const int DEFAULT_BOTS_OK_READ        = 24;      // SHDN_B_READ
const int DEFAULT_BRB_OK_READ         = 26;      // SHDN_G_READ
const int DEFAULT_BRAKE_LIGHT_CTRL    = 6;       // Pin for controlling brake lights
const int DEFAULT_INVERTER_ENABLE     = 9;       // ENABLE pin for inverters
const int DEFAULT_INVERTER_24V_ENABLE = 7;       // ENABLE pin for inverters' 24V

/**
 * Struct to keep track of MCU pinouts.
 */
struct MainECUHardwareReadPins_s
{
    // shutdown read pins
    int pin_bms_ok_read;
    int pin_imd_ok_read;
    int pin_bspd_ok_read;
    int pin_software_ok_read;
    int pin_bots_ok_read;
    int pin_brb_ok_read;
    // brake light pin
    int pin_brake_light_ctrl;
    // inverter enable pins
    int pin_inv_en;
    int pin_inv_24V_en;
};

/**
 * Default MCU pinouts.
 */
static const MainECUHardwareReadPins_s DEFAULT_PINS = {DEFAULT_BMS_OK_READ,DEFAULT_IMD_OK_READ, DEFAULT_BSPD_OK_READ, DEFAULT_SOFTWARE_OK_READ,
                                                     DEFAULT_BOTS_OK_READ, DEFAULT_BRB_OK_READ, DEFAULT_BRAKE_LIGHT_CTRL, DEFAULT_INVERTER_ENABLE, DEFAULT_INVERTER_24V_ENABLE};

/**
 * Class representing the MCU interface, containing all the pinouts and sensing.
 */
class MCUInterface
{
private:
    /**
     * Circular buffer for the CAN message queue. The MCU repo can enqueue messages onto the Telem CAN using
     * this message queue.
     */
    CANBufferType *msg_queue_;

    /**
     * MainECUHardwareReadPins_s struct for this object's pinout.
     */
    MainECUHardwareReadPins_s pins_;

    /**
     * Outbound MCU_STATUS message.
     */
    MCU_STATUS_t mcu_status_;

    /**
     * Inputs from the SHDN circuit. These booleans get updated in 
     */
    bool bms_ok_high_;
    bool imd_ok_high_;
    bool bspd_ok_high_;
    bool software_ok_high_;
    bool brb_ok_high_;

    /**
     * Shutdown circuit to check if each shutdown line is high.
     */ 
    bool shutdown_b_above_threshold_; // BOTS
    bool shutdown_c_above_threshold_; // IMD
    bool shutdown_d_above_threshold_; // AMS
    bool shutdown_e_above_threshold_; // BSPD
    bool shutdown_g_above_threshold_; // BRB

    /**
     * Measures the inputs into the shutdown relays. These are all digital signals.
     * 
     * bms_ok_high_, imd_ok_high_, bspd_ok_high_, software_ok_high_, and brb_ok_high_
     */
    void measure_shutdown_circuit_input();

    /**
     * Measures whether or not the shutdown circuit voltages are above the threshold.
     * These are very similar to the outputs from measure_shutdown_circuit_input(), but
     * some are slightly different.
     */ 
    void measure_shutdown_circuit_voltage();

    /**
     * Updates the MCU_STATUS member variable from the other boolean member variables.
     */
    void update_mcu_status_CAN();

public:

    /**
     * Constructor for creating a new MCUInterface object. This required a struct specifying the
     * MCU pinout.
     */
    MCUInterface(CANBufferType *msg_output_queue, const MainECUHardwareReadPins_s &pins):
        msg_queue_(msg_output_queue),
        pins_(pins){};

    /**
     * Overloaded constructor that uses the DEFAULT_PINS by default.
     */
    MCUInterface(CANBufferType *msg_output_queue):        
        MCUInterface(msg_output_queue, DEFAULT_PINS)
    {};

    /**
     * Initalization function to set the pin mode and initialize the OK flags to FALSE.
     */
    void init();

    /**
     * Calls the measure_shutdown_circuit_input() and measure_shutdown_circuit_voltage() functions
     * to update the member variables from the digital pins.
     */
    void read_mcu_status();

    /**
     * Calls digitalWrite() on the brake light pin with the given boolean.
     */ 
    void set_brake_light(bool brake_pedal_is_active); // Called from PedalInterface/System

    /**
     * Calls digitalWrite() on the inverter enable and inverter 24V enable pins.
     */
    void enable_inverters_pin();

    /**
     * Calls digitalWrite() on the inverter enable and inverter 24V enable pins.
     */
    void disable_inverters_pin();

    /**
     * Getter for bms_ok_high_, imd_ok_high_, brb_ok_high_, and bots_ok_.
     */
    bool bms_ok_is_high();
    bool imd_ok_is_high();
    bool brb_ok_is_high();
    bool get_bots_ok();

    /**
     * Enqueue MCU_status CAN
     */
    void enqueue_CAN_mcu_status();

    /**
     * Tick MCUInterface at 10HZ
     */
    void tick(
        int fsm_state,
        bool inv_has_error,
        bool software_is_ok,
        int drive_mode,
        int torque_mode,
        float max_torque,
        bool buzzer_is_on,
        const PedalsSystemData_s &pedals_data,
        bool pack_charge_is_critical,
        bool button_is_pressed);
};

#endif /* __MCU_INTERFACE_H__ */
