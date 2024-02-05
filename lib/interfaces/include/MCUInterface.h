#ifndef __MCU_INTERFACE_H__
#define __MCU_INTERFACE_H__

#include <stdint.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "hytech.h"
#include "SysClock.h"
#include "MCUStateMachine.h"

const int DEFAULT_BMS_OK_READ       = 5;   // SHDN_D_READ
const int DEFAULT_IMD_OK_READ       = 4;   // SHDN_C_READ
const int DEFAULT_BSPD_OK_READ      = 6;   // SHDN_E_READ
const int DEFAULT_SOFTWARE_OK_READ  = 25;  // SHDN_F_READ Watchdog Combined
const int DEFAULT_BOTS_OK_READ      = 3;   // SHDN_B_READ
const int DEFAULT_BRAKE_LIGHT_CTRL  = 7;
const int DEFAULT_INVERTER_EN       = 9;
const int DEFAULT_INVERTER_24V_EN   = 8;

class MCUInterface
{
private:
    /* Private utility functions */
    void measure_shutdown_circuit_input();
    void measure_shutdown_circuit_voltage();
    void update_mcu_status_CAN();

    /* Outbound CAN message */
    MCU_status mcu_status_;
    /* CAN Tx buffer */
    CANBufferType *msg_queue_;

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

    /* Hardware interface pins */
    int pin_bms_ok_read_;
    int pin_imd_ok_read_;
    int pin_bspd_ok_read_;
    int pin_software_ok_read_;
    int pin_bots_ok_read_;
    int pin_brake_light_ctrl_;
    int pin_inv_en_;
    int pin_inv_24V_en_;

public:
    MCUInterface(){};
    // MCUInterface(message_queue *msg_output_queue, int bms_pin, int imd_pin, int bspd_pin, int sw_ok_pin, int bots_ok_pin, int brake_light_pin, int inv_pin, int inv_24V_pin): 
    //     msg_queue_(msg_output_queue),
    //     pin_bms_ok_read_(bms_pin),
    //     pin_imd_ok_read_(imd_pin),
    //     pin_bspd_ok_read_(bspd_pin),
    //     pin_software_ok_read_(sw_ok_pin),
    //     pin_bots_ok_read_(bots_ok_pin),
    //     pin_brake_light_ctrl_(brake_light_pin),
    //     pin_inv_en_(inv_pin),
    //     pin_inv_24V_en_(inv_24V_pin)
    // {
    //     // Set pin mode
    //     pinMode(pin_brake_light_ctrl_, OUTPUT);
    //     pinMode(pin_inv_en_, OUTPUT);
    //     pinMode(pin_inv_24V_en_, OUTPUT);
    // };
    // MCUInterface(message_queue *msg_output_queue):
    //     MCUInterface(msg_output_queue, DEFAULT_BMS_OK_READ, DEFAULT_IMD_OK_READ, DEFAULT_BSPD_OK_READ, DEFAULT_SOFTWARE_OK_READ, DEFAULT_BOTS_OK_READ, DEFAULT_BRAKE_LIGHT_CTRL, DEFAULT_INVERTER_EN, DEFAULT_INVERTER_24V_EN) {};

    /* Initialize shutdown circuit input readings */
    void init();

    /* Read from Main ECU */
    void read_mcu_status();
    /* Write to Main ECU */
    void set_inverter_enable(bool enable);              // Called from DrivetrainSystem
    void set_inverter_24V_enable(bool enable_24V);      // Called from DrivetrainSystem
    void set_brake_light(bool brake_pedal_is_active);   // Called from PedalInterface/System

    /* Feed to state machine */
    bool bms_ok_is_high();
    bool imd_ok_is_high();

    /* Update MCU_status CAN (main loop) */
    // State machine
    void update_mcu_status_CAN_fsm(CAR_STATE fsm_state);
    // Systems
    void update_mcu_status_CAN_drivetrain(bool has_error);
    void update_mcu_status_CAN_safety(bool is_ok);
    void update_mcu_status_CAN_TCMux();
    void update_mcu_status_CAN_buzzer(bool is_on);
    void update_mcu_status_CAN_pedals();
    // Interfaces
    void update_mcu_status_CAN_ams(bool is_critical);
    void update_mcu_status_CAN_dashboard(bool is_pressed);

    /* Enqueue MCU_status CAN  */
    void enqueue_CAN_mcu_status(CAN_message_t &msg);

    /* Tick SysClock to send CAN at 10Hz */
    void tick(
        const SysTick_s &tick,
        CAR_STATE fsm_state,
        bool inv_has_error,
        bool software_is_ok,
        // TCMux return
        bool buzzer_is_on,
        // Pedal system return
        bool pack_charge_is_critical,
        bool button_is_pressed
    );

};

#endif /* __MCU_INTERFACE_H__ */
