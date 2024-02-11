#ifndef __MCU_INTERFACE_H__
#define __MCU_INTERFACE_H__

#include <stdint.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "MessageQueueDefine.h"
#include "PedalsSystem.h"

const int DEFAULT_BMS_OK_READ         = 5;      // SHDN_D_READ
const int DEFAULT_IMD_OK_READ         = 4;      // SHDN_C_READ
const int DEFAULT_BSPD_OK_READ        = 6;      // SHDN_E_READ
const int DEFAULT_SOFTWARE_OK_READ    = 25;     // SHDN_F_READ Watchdog Combined
const int DEFAULT_BOTS_OK_READ        = 3;      // SHDN_B_READ
const int DEFAULT_BRAKE_LIGHT_CTRL    = 7;
const int DEFAULT_INVERTER_ENABLE     = 9;
const int DEFAULT_INVERTER_24V_ENABLE = 8;

/// @brief specifically designed so that Walker would be happy
struct MainECUHardwareReadPins
{
    // shutdown read pins
    int pin_bms_ok_read;
    int pin_imd_ok_read;
    int pin_bspd_ok_read;
    int pin_software_ok_read;
    int pin_bots_ok_read;
    // brake light pin
    int pin_brake_light_ctrl;
    // inverter enable pins
    int pin_inv_en;
    int pin_inv_24V_en;
};

static const MainECUHardwareReadPins DEFAULT_PINS = {DEFAULT_BMS_OK_READ,DEFAULT_IMD_OK_READ, DEFAULT_BSPD_OK_READ, DEFAULT_SOFTWARE_OK_READ,
                                                     DEFAULT_BOTS_OK_READ, DEFAULT_BRAKE_LIGHT_CTRL, DEFAULT_INVERTER_ENABLE, DEFAULT_INVERTER_24V_ENABLE};

class MCUInterface
{
private:
    CANBufferType *msg_queue_;

    MainECUHardwareReadPins pins_;

    /* Outbound CAN message */
    MCU_status mcu_status_;

    /* Shutdown circuit input */
    bool bms_ok_high;
    bool imd_ok_high;
    bool bspd_ok_high;
    bool software_ok_high;
    /* Shutdown circuit voltage */
    bool shutdown_b_above_threshold;
    bool shutdown_c_above_threshold;
    bool shutdown_d_above_threshold;
    bool shutdown_e_above_threshold;

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
        pins_(pins)
    {
        // Set pin mode
        pinMode(pins_.pin_inv_en, OUTPUT);
        pinMode(pins_.pin_inv_24V_en, OUTPUT);
        pinMode(pins_.pin_brake_light_ctrl, OUTPUT);
    };
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

    /* Update MCU_status CAN (main loop) */
    // State machine
    void update_mcu_status_CAN_fsm(int fsm_state);
    // Systems
    void update_mcu_status_CAN_drivetrain(bool has_error);
    void update_mcu_status_CAN_safety(bool is_ok);
    void update_mcu_status_CAN_TCMux(int torque_mode, float max_torque);
    void update_mcu_status_CAN_buzzer(bool is_on);
    void update_mcu_status_CAN_pedals(const PedalsSystemData_s &pedals);
    // Interfaces
    void update_mcu_status_CAN_ams(bool is_critical);
    void update_mcu_status_CAN_dashboard(bool is_pressed);

    /* Enqueue MCU_status CAN  */
    void enqueue_CAN_mcu_status();

    /* Tick MCUInterface at 10HZ */
    void tick(
        int fsm_state,
        bool inv_has_error,
        bool software_is_ok,
        int torque_mode,
        float max_torque,
        bool buzzer_is_on,
        const PedalsSystemData_s &pedals_data,
        bool pack_charge_is_critical,
        bool button_is_pressed);
};

#endif /* __MCU_INTERFACE_H__ */
