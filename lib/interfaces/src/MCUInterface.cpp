#include "MCUInterface.h"

/* Member functions */

/* Initialize shutdown circuit input readings */
void MCUInterface::init()
{

    // Set initial shutdown circuit readings
    bms_ok_high = false;
    imd_ok_high = false;

    // Enable inverters (?)
    // Should be called from drivetrain
}

/* Read shutdown system values (Not ticked, just in main loop)*/
void MCUInterface::read_mcu_status()
{

    measure_shutdown_circuit_input();
    measure_shutdown_circuit_voltage();
}

/* Measure shutdown circuits' input */
void MCUInterface::measure_shutdown_circuit_input()
{

    bms_ok_high = digitalRead(pins_.pin_bms_ok_read);
    imd_ok_high = digitalRead(pins_.pin_imd_ok_read);
    bspd_ok_high = digitalRead(pins_.pin_bspd_ok_read);
    software_ok_high = digitalRead(pins_.pin_software_ok_read);
}

/* Measure shutdown circuits' voltages */
void MCUInterface::measure_shutdown_circuit_voltage()
{

    shutdown_b_above_threshold = digitalRead(pins_.pin_bots_ok_read);
    shutdown_c_above_threshold = digitalRead(pins_.pin_imd_ok_read);
    shutdown_d_above_threshold = digitalRead(pins_.pin_bms_ok_read);
    shutdown_e_above_threshold = digitalRead(pins_.pin_bspd_ok_read);
}

/* Write brake light */
void MCUInterface::set_brake_light(bool brake_pedal_is_active)
{

    digitalWrite(pins_.pin_brake_light_ctrl, brake_pedal_is_active);
}

void MCUInterface::enable_inverters_pin()
{
    digitalWrite(pins_.pin_inv_en, HIGH);
    digitalWrite(pins_.pin_inv_24V_en, HIGH);
}
void MCUInterface::disable_inverters_pin()
{
    digitalWrite(pins_.pin_inv_en, LOW);
    digitalWrite(pins_.pin_inv_24V_en, LOW);
}
/* Shutdown circuit input state */
// BMS
bool MCUInterface::bms_ok_is_high()
{
    return bms_ok_high;
}
// OKHS (IMD)
bool MCUInterface::imd_ok_is_high()
{
    return imd_ok_high;
}

/* Send CAN message */
// MCU status
void MCUInterface::enqueue_CAN_mcu_status()
{

    CAN_message_t msg;
    mcu_status_.write(msg.buf);
    msg.id = ID_MCU_STATUS;
    msg.len = sizeof(mcu_status_);
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg));

    msg_queue_->push_back(buf, sizeof(CAN_message_t));
}

/* Update MCU_status CAN */
// MCUInterface
void MCUInterface::update_mcu_status_CAN()
{
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
void MCUInterface::update_mcu_status_CAN_fsm(int fsm_state_enum_val)
{
    mcu_status_.set_state(static_cast<MCU_STATE>(fsm_state_enum_val));
}
// DriveTrain
void MCUInterface::update_mcu_status_CAN_drivetrain(bool has_error)
{
    // Drivetrain returns struct in main loop
    // drivetrain.drive_error_occured()
    mcu_status_.set_inverters_error(has_error); // could also be called has_error
}
// SafetySystem
void MCUInterface::update_mcu_status_CAN_safety(bool is_ok)
{
    // SafetySystem returns struct in main loop
    // safety_system.get_software_is_ok()
    mcu_status_.set_software_is_ok(is_ok);
}
// AMSInterface
void MCUInterface::update_mcu_status_CAN_ams(bool is_critical)
{
    // AMSInterface returns struct in main loop
    // ams_interface.pack_charge_is_critical()
    mcu_status_.set_pack_charge_critical(is_critical);
}
// TorqueControllerMux
// Would need an agreement on
void MCUInterface::update_mcu_status_CAN_TCMux(int torque_mode, float max_torque)
{
    // TorqueControllerMux returns struct in main loop
    mcu_status_.set_torque_mode(torque_mode);
    mcu_status_.set_max_torque(static_cast<uint8_t>(max_torque));
}
// DashboardInterface
void MCUInterface::update_mcu_status_CAN_dashboard(bool is_pressed)
{
    // DashboardInterface (?) returns struct in main loop
    // dash.lauchControlButtonPressed()
    if (is_pressed)
        mcu_status_.toggle_launch_ctrl_active();
}
// BuzzerSystem
void MCUInterface::update_mcu_status_CAN_buzzer(bool is_on)
{
    // Buzzer returns struct in main loop
    // buzzer.buzzer_is_on()
    mcu_status_.set_activate_buzzer(is_on);
}
// PedalSystem
// Would need to agree on
void MCUInterface::update_mcu_status_CAN_pedals(const PedalsSystemData_s &pedals)
{
    // PedalSystem returns struct in main loop
    mcu_status_.set_brake_pedal_active(pedals.brakePressed);
    // mcu_status_.set_mech_brake_active();
    mcu_status_.set_no_accel_implausability(!pedals.accelImplausible);
    mcu_status_.set_no_brake_implausability(!pedals.brakeImplausible);
    mcu_status_.set_no_accel_brake_implausability(!(pedals.brakeAndAccelPressedImplausibility));
}

void MCUInterface::tick(int fsm_state,
                        bool inv_has_error,
                        bool software_is_ok,
                        int torque_mode,
                        float max_torque,
                        bool buzzer_is_on,
                        const PedalsSystemData_s &pedals_data,
                        bool pack_charge_is_critical,
                        bool button_is_pressed)
{
    // State machine
    update_mcu_status_CAN_fsm(fsm_state);
    // Systems
    update_mcu_status_CAN_drivetrain(inv_has_error);
    update_mcu_status_CAN_safety(software_is_ok);
    update_mcu_status_CAN_TCMux(torque_mode, max_torque);
    update_mcu_status_CAN_buzzer(buzzer_is_on);
    update_mcu_status_CAN_pedals(pedals_data);
    // External Interfaces
    update_mcu_status_CAN_ams(pack_charge_is_critical);
    update_mcu_status_CAN_dashboard(button_is_pressed);
    // Internal values
    update_mcu_status_CAN();
    // Push into buffer
    enqueue_CAN_mcu_status();
}
