#include "MCUInterface.h"

/* MCU_status CAN note */
    // State machine
    // mcu_status.get_state();                          // Might not need anymore (moved to state machine)
    // mcu_status.get_mech_brake_active();              // Might not need anymore (moved to PedalInterface/System)
    // mcu_status.get_bms_ok_high()                     // Called from state machine
    // mcu_status.get_imd_ok_high()                     // Called from state machine
    // mcu_status.get_no_brake_implausability();        // Moved to PedalInterface/System
    // mcu_status.get_no_accel_implausability();        // Moved to PedalInterface/System
    // mcu_status.get_no_accel_brake_implausability();  // Moved to PedalInterface/System
    // mcu_status.get_software_is_ok();                 // Moved to AMSInterface
    
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

/* Member functions */

/* Initialize shutdown circuit input readings */
void MCUInterface::init() {
    bms_ok_high = false;
    imd_ok_high = false;
}

/* Read shutdown system values */
void MCUInterface::read_mcu_status() {

    measure_shutdown_circuit_input();
    measure_shutdown_circuit_voltage();  
    
}

/* Measure shutdown circuits' input */
void MCUInterface::measure_shutdown_circuit_input() {

    bms_ok_high = digitalRead(BMS_OK_READ);
    imd_ok_high = digitalRead(IMD_OK_READ);
    bspd_ok_high = digitalRead(BSPD_OK_READ);
    software_ok_high = digitalRead(SOFTWARE_OK_READ); 
    
}

/* Measure shutdown circuits' voltages */
void MCUInterface::measure_shutdown_circuit_voltage() {

    shutdown_b_above_threshold = digitalRead(BOTS_OK_READ);
    shutdown_c_above_threshold = digitalRead(IMD_OK_READ);
    shutdown_d_above_threshold = digitalRead(BMS_OK_READ);
    shutdown_e_above_threshold = digitalRead(BSPD_OK_READ);
    
}

/* Write brake light */
void MCUInterface::set_brake_light(bool brake_pedal_is_active) {

    digitalWrite(BRAKE_LIGHT_CTRL, brake_pedal_is_active);

}

/* Shutdown circuit input state */
// BMS
bool MCUInterface::bms_ok_is_high() {
    return bms_ok_high;
}
// OKHS (IMD)
bool MCUInterface::imd_ok_is_high() {
    return imd_ok_high;
}

/* Send CAN message */
// MCU status
void MCUInterface::send_CAN_mcu_status(CAN_message_t &msg) {
    update_mcu_status_CAN();
    mcu_status_.write(msg.buf);
    msg.id = ID_MCU_STATUS;
    msg.len = sizeof(mcu_status_);
    // TELEM_CAN.write(msg);
}

/* Update MCU_status CAN */
// MCUInterface
void MCUInterface::update_mcu_status_CAN() {
    // Shutdown circuit input
    mcu_status_.set_bms_ok_high(bms_ok_high);
    mcu_status_.set_imd_ok_high(imd_ok_high);
    mcu_status_.set_bspd_ok_high(bspd_ok_high);
    mcu_status_.set_software_ok_high(software_ok_high);
    // Shutdown circuit voltage
    mcu_status_.set_shutdown_b_above_threshold(shutdown_b_above_threshold);
    mcu_status_.set_shutdown_c_above_threshold(shutdown_c_above_threshold);
    mcu_status_.set_shutdown_d_above_threshold(shutdown_d_above_threshold);
    mcu_status_.set_shutdown_e_above_threshold(shutdown_e_above_threshold);
}

// Main loop
// State machine
void MCUInterface::update_mcu_status_CAN_fsm() {
    // State machine returns struct in main loop
        // mcu_status_.set_state(fsm_state);
}
//DriveTrain
void MCUInterface::update_mcu_status_CAN_drivetrain() {
    // Drivetrain returns struct in main loop
    mcu_status_.set_inverters_error(drive_train_->get_error_list());     // could also be called has_error
}
// AMSInterface
void MCUInterface::update_mcu_status_CAN_ams() {
    // AMSInterface returns struct in main loop
    mcu_status_.set_software_is_ok(ams_->software_is_ok());
    mcu_status_.set_pack_charge_critical(ams_->pack_charge_is_critical());
}
// DashboardInterface(?)
void MCUInterface::update_mcu_status_CAN_dashboard() {
    // DashboardInterface (?) returns struct in main loop
    mcu_status_.set_torque_mode(dash_->get_torque_mode());
    mcu_status_.set_max_torque(dash_->get_max_torque());
    mcu_status_.toggle_launch_ctrl_active(dash_->launch_ctrl_btn_pressed());
}
// BuzzerSystem
void MCUInterface::update_mcu_status_CAN_buzzer() {
    // Buzzer returns struct in main loop
        // mcu_status_.set_activate_buzzer();
}
// PedalSystem
void MCUInterface::update_mcu_status_CAN_pedals() {
    // PedalSystem returns struct in main loop
        // mcu_status_.set_brake_pedal_active();
        // mcu_status_.set_mech_brake_active();
        // mcu_status_.set_no_accel_implausability();
        // mcu_status_.set_no_brake_implausability();
        // mcu_status_.set_no_accel_brake_implausability();
}


