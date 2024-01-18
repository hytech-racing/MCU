#include <AMSInterface.h>

/* static members */
void AMSInterface::set_heartbeat(unsigned long curr_time) {
    last_heartbeat_time = curr_time;
}

unsigned long AMSInterface::last_heartbeat_time = millis();

/* Initialize */
void AMSInterface::init() {
    set_software_is_ok();

    pinMode(SOFTWARE_OK, OUTPUT);
    digitalWrite(SOFTWARE_OK, HIGH);

    mcu_->mcu_status.set_bms_ok_high(false);
}

void AMSInterface::set_software_is_ok() {
    mcu_->mcu_status.set_software_is_ok(true);
}

void AMSInterface::set_software_is_not_ok() {
    mcu_->mcu_status.set_software_is_ok(false);
}

bool AMSInterface::software_is_ok() {
    return mcu_->mcu_status.get_software_is_ok();
}

/* Check if AMS is ok */
bool AMSInterface::ok_high() {
    return mcu_->mcu_status.get_bms_ok_high();
}

/* Check if AMS heartbeat is received */
bool AMSInterface::heartbeat_check(unsigned long curr_time) {
    return ((curr_time - last_heartbeat_time) < HEARTBEAT_INTERVAL);
}

/* Check if lowest cell temperature is below threshold */
bool AMSInterface::is_below_pack_charge_critical_low_thresh() {
    return (mcu_->bms_voltages.get_low() < PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD);
}

/* Check if total pack charge is above threshold */
bool AMSInterface::is_above_pack_charge_critical_total_thresh() {
    return (mcu_->bms_voltages.get_total() < PACK_CHARGE_CRIT_TOTAL_THRESHOLD);
}

/* Decide whether pack charge is critical */
void AMSInterface::set_pack_charge_critical(bool is_critical) {
    mcu_->mcu_status.set_pack_charge_critical(is_critical);
}

/* IIR filter and return filtered max cell temperature */
float AMSInterface::get_filtered_max_cell_temp() {
    bms_high_temp = mcu_->bms_temperatures.get_high_temperature() / 100.0;
    filtered_max_cell_temp = filtered_max_cell_temp * cell_temp_alpha + (1.0 - cell_temp_alpha) * bms_high_temp;
    return filtered_max_cell_temp;
}

/* IIR filter and return filtered min cell voltage */
void AMSInterface::get_filtered_min_cell_voltage() {
    bms_low_voltage = mcu_->bms_voltages.get_low() / 10000.0;
    filtered_min_cell_voltage = filtered_min_cell_voltage * cell_temp_alpha + (1.0 - cell_voltage_alpha) * bms_low_voltage;
    return filtered_min_cell_voltage;
}

