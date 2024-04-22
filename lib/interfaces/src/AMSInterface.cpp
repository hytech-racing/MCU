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
    return (HYTECH_low_voltage_ro_fromS(bms_voltages_.low_voltage_ro) < PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD);
}

bool AMSInterface::is_below_pack_charge_critical_total_thresh() {
    return (HYTECH_total_voltage_ro_fromS(bms_voltages_.total_voltage_ro) < PACK_CHARGE_CRIT_TOTAL_THRESHOLD);
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

float AMSInterface::get_filtered_min_cell_voltage() {
    bms_low_voltage = HYTECH_low_voltage_ro_fromS(bms_voltages_.low_voltage_ro) / 10000.0;
    filtered_min_cell_voltage = filtered_min_cell_voltage * cell_temp_alpha + (1.0 - cell_voltage_alpha) * bms_low_voltage;
    return filtered_min_cell_voltage;
}

float AMSInterface::initialize_charge() {
    int i = 0;
    while (abs(HYTECH_low_voltage_ro_fromS(bms_voltages_.low_voltage_ro) - voltage_lookup_table[i]) <= abs(HYTECH_low_voltage_ro_fromS(bms_voltages_.low_voltage_ro) - voltage_lookup_table[i+1])) {
        i++;
    }
    charge = ((100 - i)/100) * MAX_PACK_CHARGE;
}

float AMSInterface::get_SoC_em() {
    current = em_measurements_.em_current_ro;
    charge -= (current * CC_integrator_timer) / 1000;
    SoC = (charge / MAX_PACK_CHARGE) * 100;
    return SoC;
}

float AMSInterface::get_SoC_acu() {
    current = HYTECH_current_shunt_read_ro_fromS(acu_shunt_measurements_.current_shunt_read_ro);
    shunt_voltage = (current * (9.22 / 5.1)) - 3.3 - 0.03;
    calc_current = (shunt_voltage / 0.005);
    charge -= (calc_current * CC_integrator_timer) / 1000;
    SoC = (charge / MAX_PACK_CHARGE) * 100;
    return SoC;
}

void AMSInterface::tick50() {
    get_SoC_em();
    get_SoC_acu();
}

//RETRIEVE CAN MESSAGES//
void AMSInterface::retrieve_status_CAN(unsigned long curr_millis, CAN_message_t &recvd_msg) {
    bms_status_.load(recvd_msg.buf);
    set_heartbeat(curr_millis);
}

void AMSInterface::retrieve_temp_CAN(CAN_message_t &recvd_msg) {
    bms_temperatures_.load(recvd_msg.buf);
}

void AMSInterface::retrieve_voltage_CAN(CAN_message_t &can_msg) {
    Unpack_BMS_VOLTAGES_hytech(&bms_voltages_, can_msg.buf, can_msg.len);
}


void AMSInterface::read_current_shunt_CAN(const CAN_message_t &can_msg) {
    Unpack_ACU_SHUNT_MEASUREMENTS_hytech(&acu_shunt_measurements_, can_msg.buf, can_msg.len);
}



