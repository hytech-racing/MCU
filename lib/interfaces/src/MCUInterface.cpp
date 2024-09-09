#include "MCUInterface.h"

void MCUInterface::init()
{
    // Set pin mode
    pinMode(pins_.pin_inv_en, OUTPUT);
    pinMode(pins_.pin_inv_24V_en, OUTPUT);
    pinMode(pins_.pin_brake_light_ctrl, OUTPUT);

    // Set initial shutdown circuit readings
    bms_ok_high_ = false;
    imd_ok_high_ = false;
    brb_ok_high_ = false;
}

void MCUInterface::read_mcu_status()
{
    measure_shutdown_circuit_input();
    measure_shutdown_circuit_voltage();
}

void MCUInterface::measure_shutdown_circuit_input()
{
    bms_ok_high_ = digitalRead(DEFAULT_BMS_SENSE_PIN);
    imd_ok_high_ = digitalRead(DEFAULT_IMD_SENSE_PIN);
    
    bspd_ok_high_ = digitalRead(pins_.pin_bspd_ok_read);
    software_ok_high_ = digitalRead(pins_.pin_software_ok_read);
    brb_ok_high_ = digitalRead(pins_.pin_brb_ok_read);
}

void MCUInterface::measure_shutdown_circuit_voltage()
{
    shutdown_b_above_threshold_ = digitalRead(pins_.pin_bots_ok_read);
    shutdown_c_above_threshold_ = digitalRead(pins_.pin_imd_ok_read);
    shutdown_d_above_threshold_ = digitalRead(pins_.pin_bms_ok_read);
    shutdown_e_above_threshold_ = digitalRead(pins_.pin_bspd_ok_read);
    shutdown_g_above_threshold_ = digitalRead(pins_.pin_brb_ok_read);
}

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

bool MCUInterface::bms_ok_is_high()
{
    return bms_ok_high_;
}

bool MCUInterface::imd_ok_is_high()
{
    return imd_ok_high_;
}

bool MCUInterface::brb_ok_is_high()
{
    return brb_ok_high_;
}

bool MCUInterface::get_bots_ok()
{
    return shutdown_b_above_threshold_;
}

void MCUInterface::enqueue_CAN_mcu_status()
{
    CAN_message_t msg;
    
    msg.id = Pack_MCU_STATUS_hytech(&mcu_status_, msg.buf, &msg.len, (uint8_t*) &msg.flags.extended);

    uint8_t buf[sizeof(CAN_message_t)] = {};
    memmove(buf, &msg, sizeof(CAN_message_t));
    msg_queue_->push_back(buf, sizeof(CAN_message_t));
}

void MCUInterface::update_mcu_status_CAN()
{
    // Shutdown circuit input
    mcu_status_.bms_ok_high = bms_ok_high_;
    mcu_status_.imd_ok_high = imd_ok_high_;
    mcu_status_.bspd_ok_high = bspd_ok_high_;
    mcu_status_.software_ok_high = software_ok_high_;
    // Shutdown circuit voltage
    mcu_status_.shutdown_b_above_threshold = shutdown_b_above_threshold_;
    mcu_status_.shutdown_c_above_threshold = shutdown_c_above_threshold_;
    mcu_status_.shutdown_d_above_threshold = shutdown_d_above_threshold_;
    mcu_status_.shutdown_e_above_threshold = shutdown_e_above_threshold_;    
}

void MCUInterface::tick(int fsm_state,
                        bool inv_has_error,
                        bool software_is_ok,
                        int drive_mode,
                        int torque_mode,
                        float max_torque,
                        bool buzzer_is_on,
                        const PedalsSystemData_s &pedals_data,
                        bool pack_charge_is_critical,
                        bool button_is_pressed)
{
    mcu_status_.ecu_state = fsm_state;

    mcu_status_.inverter_error = inv_has_error;
    mcu_status_.software_ok = software_is_ok;
    
    mcu_status_.drive_mode = drive_mode;
    mcu_status_.torque_mode = torque_mode;
    mcu_status_.max_torque = static_cast<uint8_t>(max_torque);
    
    mcu_status_.drive_buzzer = buzzer_is_on;
    
    mcu_status_.brake_pedal_active = pedals_data.brakePressed;
    mcu_status_.no_accel_implausibility = !pedals_data.accelImplausible;
    mcu_status_.no_brake_implausibility = !pedals_data.brakeImplausible;
    mcu_status_.no_accel_or_brake_implausibility = !(pedals_data.brakeAndAccelPressedImplausibility);
    
    mcu_status_.pack_charge_critical = pack_charge_is_critical;

    mcu_status_.launch_control_active = button_is_pressed;

    update_mcu_status_CAN();

    // Push into buffer
    enqueue_CAN_mcu_status();
    set_brake_light(pedals_data.brakePressed);
}
