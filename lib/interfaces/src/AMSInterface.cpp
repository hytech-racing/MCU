#include <AMSInterface.h>

/* static members */
void AMSInterface::set_heartbeat(unsigned long curr_time) {
    last_heartbeat_time = curr_time;
}

unsigned long AMSInterface::last_heartbeat_time = millis();

/* Initialize */
void AMSInterface::init() {
    pinMode(SOFTWARE_OK, OUTPUT);
}

void AMSInterface::set_start_state() {
    digitalWrite(SOFTWARE_OK, HIGH);
}

void AMSInterface::set_state_ok_high(bool ok_high) {
    if (ok_high)
        digitalWrite(SOFTWARE_OK, HIGH);
    else
        digitalWrite(SOFTWARE_OK, LOW);
}

// SafetySystem
void AMSInterface::set_software_is_ok(bool is_ok) {
    software_is_ok = is_ok;
}
// SafetySystem
bool AMSInterface::software_is_ok() {
    return software_is_ok;
}

/* Check if AMS is ok */
// SafetySystem (?)
// Should be requested from MCUInterface instead
bool AMSInterface::ok_high() {
    return mcu_->mcu_status.get_bms_ok_high();
}

/* Check if AMS heartbeat is received */
bool AMSInterface::heartbeat_received(unsigned long curr_time) {
    return ((curr_time - last_heartbeat_time) < HEARTBEAT_INTERVAL);
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
void AMSInterface::get_filtered_min_cell_voltage() {
    bms_low_voltage = bms_voltages_.get_low() / 10000.0;
    filtered_min_cell_voltage = filtered_min_cell_voltage * cell_temp_alpha + (1.0 - cell_voltage_alpha) * bms_low_voltage;
    return filtered_min_cell_voltage;
}

void AMSInterface::retrieve_coulomb_count_CAN(CAN_message_t &recvd_msg) {
    bms_coulomb_counts_.load(recvd_msg.buf);
}

void AMSInterface::retrieve_status_CAN(CAN_message_t &recvd_msg) {
    bms_status_.load(recvd_msg.buf);
    set_heartbeat(millis());
}

void AMSInterface::retrieve_temp_CAN(CAN_message_t &recvd_msg) {
    bms_temperatures_.load(recvd_msg.buf);
}

void AMSInterface::retrieve_voltage_CAN(CAN_message_t &recvd_msg) {
    bms_voltages_.load(recvd_msg.buf);
}

void AMSInterface::send_CAN_bms_coulomb_counts(CAN_message_t &msg) {
    update_CAN_msg();
    bms_coulomb_counts_.write(msg.buf);
    msg.id = ID_BMS_COULOMB_COUNTS;
    msg.len = sizeof(bms_coulomb_counts_);
}

void AMSInterface::update_CAN_msg() {
    // do sth with bms_coulomb_counts
}
