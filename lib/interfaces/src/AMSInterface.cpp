#include "AMSInterface.h"

void AMSInterface::init(unsigned long curr_millis) {
    
    // Set pin mode
    pinMode(pin_software_ok_, OUTPUT);

    set_heartbeat(curr_millis);

}

void AMSInterface::set_start_state() {
    
    digitalWrite(pin_software_ok_, HIGH);
    
}

//SETTERS//
void AMSInterface::set_state_ok_high(bool ok_high) {
    if (ok_high)
        digitalWrite(pin_software_ok_, HIGH);
    else
        digitalWrite(pin_software_ok_, LOW);
}

void AMSInterface::set_heartbeat(unsigned long curr_millis) {
    last_heartbeat_time = curr_millis;
}

bool AMSInterface::heartbeat_received(unsigned long curr_millis) {
    // if((curr_millis - last_heartbeat_time) >= HEARTBEAT_INTERVAL){
    //     Serial.println("ERROR");
    //     Serial.println(curr_millis);
    //     Serial.println(last_heartbeat_time);
    //     Serial.println(curr_millis - last_heartbeat_time);
    // }
    
    return ((curr_millis - last_heartbeat_time) < HEARTBEAT_INTERVAL);
}

bool AMSInterface::is_below_pack_charge_critical_low_thresh() {
    return (bms_voltages_.get_low() < PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD);
}

bool AMSInterface::is_below_pack_charge_critical_total_thresh() {
    return (bms_voltages_.get_total() < PACK_CHARGE_CRIT_TOTAL_THRESHOLD);
}

bool AMSInterface::pack_charge_is_critical() {
    return (is_below_pack_charge_critical_low_thresh() || is_below_pack_charge_critical_total_thresh());
}

//GETTERS//
float AMSInterface::get_filtered_max_cell_temp() {
    bms_high_temp = bms_temperatures_.get_high_temperature() / 100.0;
    filtered_max_cell_temp = filtered_max_cell_temp * cell_temp_alpha + (1.0 - cell_temp_alpha) * bms_high_temp;
    return filtered_max_cell_temp;
}

float AMSInterface::get_acc_derate_factor() {
    float voltage_lim_factor = 1.0;
    float startDerateVoltage = 3.5;
    float endDerateVoltage = 3.2;
    float voltage_lim_max = 1;
    float voltage_lim_min = 0.2;

    float temp_lim_factor = 1.0;
    float startDerateTemp = 50;
    float stopDerateTemp = 58;
    float temp_lim_max = 1;
    float temp_lim_min = 0.2;

    float filtered_min_cell_voltage = get_filtered_min_cell_voltage();
    //float_map equivalient because new code is bad 
    voltage_lim_factor = (filtered_min_cell_voltage - startDerateVoltage) * (voltage_lim_min - voltage_lim_max) / (endDerateVoltage - startDerateVoltage) + voltage_lim_max;
    voltage_lim_factor = max(min(voltage_lim_max, voltage_lim_factor), voltage_lim_min);

    temp_lim_factor = (filtered_max_cell_temp - startDerateTemp) * (temp_lim_min - temp_lim_max) / (stopDerateTemp - startDerateTemp) + temp_lim_max;
    temp_lim_factor = max(min(temp_lim_factor, temp_lim_max), temp_lim_min);
    
    acc_derate_factor = min(temp_lim_factor,voltage_lim_factor);
    return acc_derate_factor;
}
    
}

float AMSInterface::get_filtered_min_cell_voltage() {
    bms_low_voltage = bms_voltages_.get_low() / 10000.0;
    filtered_min_cell_voltage = filtered_min_cell_voltage * cell_temp_alpha + (1.0 - cell_voltage_alpha) * bms_low_voltage;
    return filtered_min_cell_voltage;
}

//RETRIEVE CAN MESSAGES//
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


