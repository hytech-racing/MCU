#include "AMSInterface.h"

/* Pin mode output to watchdog reset */
void AMSInterface::init(unsigned long curr_millis) {

    set_heartbeat(curr_millis);

}

/* Initial ouput to watchdog reset */
void AMSInterface::set_start_state() {
    
    digitalWrite(pin_software_ok_, HIGH);
    
}

/* Set value to watchdog reset */
void AMSInterface::set_state_ok_high(bool ok_high) {
    if (ok_high)
        digitalWrite(pin_software_ok_, HIGH);
    else
        digitalWrite(pin_software_ok_, LOW);
}

/* Set AMS last heartbeat receive time */
void AMSInterface::set_heartbeat(unsigned long curr_millis) {
    last_heartbeat_time = curr_millis;
}

/* Check if AMS heartbeat is received */
bool AMSInterface::heartbeat_received(unsigned long curr_millis) {
    return ((curr_millis - last_heartbeat_time) < HEARTBEAT_INTERVAL);
}

/* Check if lowest cell temperature is below threshold */
// AMSSystem (?)
// No need for AMSSystem anymore, AMSInterface and WatchdogInterface go to SafetySystem
bool AMSInterface::is_below_pack_charge_critical_low_thresh() {
    return (bms_voltages_.get_low() < PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD);
}

/* Check if total pack charge is above threshold */
// AMSSystem
bool AMSInterface::is_below_pack_charge_critical_total_thresh() {
    return (bms_voltages_.get_total() < PACK_CHARGE_CRIT_TOTAL_THRESHOLD);
}

/* Decide whether pack charge is critical */
// AMSSystem (?)
bool AMSInterface::pack_charge_is_critical() {
    return (is_below_pack_charge_critical_low_thresh() || is_below_pack_charge_critical_total_thresh());
}

/* IIR filter and return filtered max cell temperature */
// AMSSystem (?)
float AMSInterface::get_filtered_max_cell_temp() {
    bms_high_temp = bms_temperatures_.get_high_temperature() / 100.0;
    filtered_max_cell_temp = filtered_max_cell_temp * cell_temp_alpha + (1.0 - cell_temp_alpha) * bms_high_temp;
    return filtered_max_cell_temp;
}

/* IIR filter and return filtered min cell voltage */
// AMSSystem (?)
float AMSInterface::get_filtered_min_cell_voltage() {
    bms_low_voltage = bms_voltages_.get_low() / 10000.0;
    filtered_min_cell_voltage = filtered_min_cell_voltage * cell_temp_alpha + (1.0 - cell_voltage_alpha) * bms_low_voltage;
    return filtered_min_cell_voltage;
}

/* Retrieve CAN messages */
void AMSInterface::retrieve_status_CAN(unsigned long curr_millis, CAN_message_t &recvd_msg) {
    bms_status_.load(recvd_msg.buf);
    set_heartbeat(curr_millis);
}

void AMSInterface::retrieve_temp_CAN(CAN_message_t &recvd_msg) {
    bms_temperatures_.load(recvd_msg.buf);
}

void AMSInterface::retrieve_voltage_CAN(CAN_message_t &recvd_msg) {
    bms_voltages_.load(recvd_msg.buf);
}


