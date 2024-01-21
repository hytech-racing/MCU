#ifndef __MCU_INTERFACE_H__
#define __MCU_INTERFACE_H__

#include <stdint.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

#define INV_CAN_SPEED       500000
#define TELEM_CAN_SPEED     1000000
#define TEENSY_INV_CAN      CAN2
#define TEENSY_TELEM_CAN    CAN3

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

    void init();

    /* Read from Main ECU */
    void read_mcu_status();
    /* Write to Main ECU */
    void set_brake_light(bool brake_pedal_is_active);   // Called from PedalInterface/System

    /* Set by system */
    void set_state(MCU_STATE new_state)         { mcu_status.set_state(new_state); }    // Called from state machine (?)
    void set_inverters_error(bool has_error)    { mcu_status.set_inverters_error(has_error); }  // Called from DrivetrainSystem/InverterInterface(s)

    /* Feed to system */
    // State machine
    MCU_STATE get_state()                   { return mcu_status.get_state(); }          // Might not need anymore (moved to state machine)
    // bool mech_brake_is_active()             { return mcu_status.get_mech_brake_active(); }   // Might not need anymore (moved to PedalInterface/System)
    bool bms_ok_is_high()                        { return bms_ok_high; }     // Called from state machine
    bool imd_ok_is_high()                        { return imd_ok_high; }     // Called from state machine
    // bool no_brake_implausability()          { return mcu_status.get_no_brake_implausability(); }         // Moved to PedalInterface/System
    // bool no_accel_implausability()          { return mcu_status.get_no_accel_implausability(); }         // Moved to PedalInterface/System
    // bool no_accel_brake_implausability()    { return mcu_status.get_no_accel_brake_implausability(); }   // Moved to PedalInterface/System
    // bool software_is_ok()                   { return mcu_status.get_software_is_ok(); }  // Moved to AMSInterface
    
    // Software shutdown
    // mcu_status.set_software_is_ok(true);     // Called from/call AMSInterface
    // mcu_status.set_software_is_ok(false);    // Called from/call AMSInterface
    // mcu_status.get_software_is_ok()          // Moved to AMSInterface

    // Parse telem CAN
    // bms voltage
    // mcu_status.set_pack_charge_critical(true);   // Called from/call AMSInterface
    // dash
    // mcu_status.get_torque_mode()                 // Moved to DashboardInterface(?)
    // mcu_status.set_max_torque(TORQUE_2);         // Called from/call Dashboard/Inverter/Drivetrain/Whoever documents TORQUE
    // mcu_status.set_torque_mode(2);               // Same as ^
    // mcu_status.toggle_launch_ctrl_active();      // Called from/call DashboardInterface

    // Set state
    // mcu_status.get_state()                       // Moved to state machine
    // mcu_status.set_activate_buzzer(false);       // Called from(?) state machine
    // mcu_status.set_state(new_state);             // Called from/call state machine
    // mcu_status.set_activate_buzzer(true);        // Called from state machine

    // Set inverter torque
    // mcu_status.get_max_torque()                  // Moved to whoever caches TORQUE

    // Read all adcs                                // Setters called from/call PedalInterface/System
    // mcu_status.set_brake_pedal_active(mcu_pedal_readings.get_brake_pedal_1() >= BRAKE_ACTIVE); // pedal interface
    // mcu_status.get_brake_pedal_active()          // Moved to PedalInterface/System
    // mcu_status.set_mech_brake_active(mcu_pedal_readings.get_brake_pedal_1() >= BRAKE_THRESHOLD_MECH_BRAKE_1);

    // Check all inverters error
    // mcu_status.set_inverters_error(true);        // See above

    // Read mcu status
    // already implemented

    // Calculate pedal implausibilities
    // mcu_status.set_no_accel_implausability(false);       // Called from/call PedalInterface/System
    // mcu_status.set_no_brake_implausability(false);       // Same ^
    // mcu_status.get_mech_brake_active()                   // Moved to PedalInterface/System
    // mcu_status.set_no_accel_brake_implausability(false); // Called from/call PedalInterface/System
    // mcu_status.get_no_accel_implausability()             // Moved to PedalInterface/System
    // mcu_status.get_no_brake_implausability()             // Same ^
    // mcu_status.get_no_accel_brake_implausability()       // Same ^

    // Set up
    // mcu_status.set_max_torque(0);            // Moved to whoever documents TORQUE (functionality-wise, no need to call)
    // mcu_status.set_torque_mode(0);           // Same ^
    // mcu_status.set_software_is_ok(true);     // Moved to AMSInterface
    // mcu_status.set_bms_ok_high(false);       // MCUInterface
    // mcu_status.set_imd_ok_high(false);       // Same ^
    // mcu_status.set_inverters_error(false);   // Moved to InverterInterface(?)
    // mcu_status.set_max_torque(TORQUE_3);     // See above
    // mcu_status.set_torque_mode(3);           // Same ^

    // Loop
    // nah

    void send_CAN_mcu_status();


private:
    /* Private utility functions */
    void measure_shutdown_circuit_input();
    void measure_shutdown_circuit_voltage();
    void update_CAN_msg();

    MCU_status *mcu_status_;

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

// extern FlexCAN_T4<TEENSY_INV_CAN, RX_SIZE_256, TX_SIZE_16> INV_CAN;
// extern FlexCAN_T4<TEENSY_TELEM_CAN, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;

#endif /* __MCU_INTERFACE_H__ */
