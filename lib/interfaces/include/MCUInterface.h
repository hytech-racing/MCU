#ifndef __MCU_INTERFACE_H__
#define __MCU_INTERFACE_H__

#include <stdint.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "hytech.h"
#include "MessageQueueDefine.h"
#include "PedalsSystem.h"
#include "SharedDataTypes.h"

const int DEFAULT_BMS_OK_READ                = 17;      // SHDN_D_READ
const int DEFAULT_BMS_SENSE_PIN              = 16;      // BMS_OK_SENSE
const int DEFAULT_IMD_OK_READ                = 10;      // SHDN_C_READ
const int DEFAULT_IMD_SENSE_PIN              = 18;      // OKHS_SENSE
const int DEFAULT_BSPD_OK_READ               = 39;      // SHDN_E_READ
const int DEFAULT_SOFTWARE_OK_READ           = 25;      // SHDN_F_READ Watchdog Combined
const int DEFAULT_BOTS_OK_READ               = 24;      // SHDN_B_READ
const int DEFAULT_BRB_OK_READ                = 26;      // SHDN_G_READ
const int DEFAULT_BRAKE_LIGHT_CTRL           = 6;
const int DEFAULT_INVERTER_ENABLE            = 9;
const int DEFAULT_INVERTER_24V_ENABLE        = 7;
const int DEFAULT_BRAKE_PRESSURE_SENSOR_READ = 27;      // Read pin for brake pressure sensor.

/// @brief specifically designed so that Walker would be happy
struct MainECUHardwareReadPins
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
    int pin_brake_pressure_sensor_read;
};

static const MainECUHardwareReadPins DEFAULT_PINS = {DEFAULT_BMS_OK_READ,DEFAULT_IMD_OK_READ, DEFAULT_BSPD_OK_READ, DEFAULT_SOFTWARE_OK_READ,
                                                     DEFAULT_BOTS_OK_READ, DEFAULT_BRB_OK_READ, DEFAULT_BRAKE_LIGHT_CTRL, DEFAULT_INVERTER_ENABLE,
                                                     DEFAULT_INVERTER_24V_ENABLE, DEFAULT_BRAKE_PRESSURE_SENSOR_READ};

class MCUInterface
{
private:
    CANBufferType *msg_queue_;

    MainECUHardwareReadPins pins_;

    /* Outbound CAN message */
    MCU_STATUS_t mcu_status_;

    /* Shutdown circuit input */
    bool bms_ok_high;
    bool imd_ok_high;
    bool bspd_ok_high;
    bool software_ok_high;
    bool brb_ok_high;
    /* Shutdown circuit voltage */ 
    bool shutdown_b_above_threshold; // BOTS
    bool shutdown_c_above_threshold; // IMD
    bool shutdown_d_above_threshold; // AMS
    bool shutdown_e_above_threshold; // BSPD
    bool shutdown_g_above_threshold; // BRB

    /* Private utility functions */
    // Read all shutdown signals on ECU
    void measure_shutdown_circuit_input();
    void measure_shutdown_circuit_voltage();
    // Update CAN message content
    void update_mcu_status_CAN();

public:
    // PLEASE replace these long lists of parameters with structs
    // and put initialization in constructor body instead of initializer list     -- happy?
    // my retinas are in pain
    MCUInterface(CANBufferType *msg_output_queue, const MainECUHardwareReadPins &pins):
        // Member initialization list
        msg_queue_(msg_output_queue),
        pins_(pins){};

    // Overloading constructor
    MCUInterface(CANBufferType *msg_output_queue):        
        MCUInterface(msg_output_queue, DEFAULT_PINS)
    {};

    /* Initialize shutdown circuit input readings */
    void init();

    /* Read from Main ECU */
    void read_mcu_status();

    /* Write to Main ECU */
    void set_brake_light(bool brake_pedal_is_active); // Called from PedalInterface/System
    void enable_inverters_pin();
    void disable_inverters_pin();

    /* Feed to state machine */
    bool bms_ok_is_high();
    bool imd_ok_is_high();
    bool brb_ok_is_high();

    bool get_bots_ok();

    /* Update MCU_status CAN (main loop) */
    // State machine
    void update_mcu_status_CAN_fsm(int fsm_state);
    // Systems
    void update_mcu_status_CAN_drivetrain(bool has_error);
    void update_mcu_status_CAN_safety(bool is_ok);
    void update_mcu_status_CAN_TCMux(int drive_mode, int torque_mode, float max_torque);
    void update_mcu_status_CAN_buzzer(bool is_on);
    void update_mcu_status_CAN_pedals(const PedalsSystemData_s &pedals);
    // Interfaces
    void update_mcu_status_CAN_ams(bool is_critical);
    void update_mcu_status_CAN_dashboard(bool is_active);
    void update_brake_pressure_CAN();

    /* Enqueue MCU_status CAN  */
    void enqueue_CAN_mcu_status();

    /* Tick MCUInterface at 10HZ */
    void tick(
        int fsm_state,
        bool inv_has_error,
        bool software_is_ok,
        const TorqueControllerMuxStatus& tc_mux_status, 
        bool buzzer_is_on,
        const PedalsSystemData_s &pedals_data,
        bool pack_charge_is_critical,
        bool button_is_pressed);
};

#endif /* __MCU_INTERFACE_H__ */
