#ifndef __MCU_INTERFACE_H__
#define __MCU_INTERFACE_H__

#include <stdint.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "SysClock.h"
#include "MCUStateMachine.h"

#define BMS_OK_READ         5   // SHDN_D_READ
#define IMD_OK_READ         4   // SHDN_C_READ
#define BSPD_OK_READ        6   // SHDN_E_READ
#define SOFTWARE_OK_READ    25  // SHDN_F_READ Watchdog Combined
#define BOTS_OK_READ        3   // SHDN_B_READ
#define BRAKE_LIGHT_CTRL    7

class MCUInterface
{
public:
    MCUInterface() = default;

    /* Initialize shutdown circuit input readings */
    void init();

    /* Read from Main ECU */
    void read_mcu_status();
    /* Write to Main ECU */
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

    /* Send MCU_status CAN  */
    void send_CAN_mcu_status(CAN_message_t &msg);

    /* Tick SysClock to send CAN at 10Hz */
    void tick(const SysTick_s &tick);

private:
    /* Private utility functions */
    void measure_shutdown_circuit_input();
    void measure_shutdown_circuit_voltage();
    void update_mcu_status_CAN();

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
};

#endif /* __MCU_INTERFACE_H__ */
