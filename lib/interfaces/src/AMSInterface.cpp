#include "AMSInterface.h"
#include "SysClock.h"

void AMSInterface::init(SysTick_s &initial_tick) {
    
    // Set pin mode
    pinMode(pin_software_ok_, OUTPUT);

    set_heartbeat(initial_tick.millis);

    last_tick_ = initial_tick;

    // Initializes the bms_voltages_ member variable to an invalid state. This will
    // get overridden once retrieve_voltage_CAN() has been called at least once.
    CAN_message_t can_msg;
    uint16_t avg = 0x9999U, low = 0xFFFFU, high = 0x1111U, nan = 0x0000U;
    memcpy(&can_msg.buf, &avg, sizeof(uint16_t));
    memcpy(&can_msg.buf[2], &low, sizeof(uint16_t));
    memcpy(&can_msg.buf[4], &high, sizeof(uint16_t));
    memcpy(&can_msg.buf[6], &nan, sizeof(uint16_t));
    retrieve_voltage_CAN(can_msg);

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
    last_heartbeat_time_ = curr_millis;
}

bool AMSInterface::heartbeat_received(unsigned long curr_millis) {
    // if((curr_millis - last_heartbeat_time_) >= HEARTBEAT_INTERVAL){
    //     Serial.println("ERROR");
    //     Serial.println(curr_millis);
    //     Serial.println(last_heartbeat_time_);
    //     Serial.println(curr_millis - last_heartbeat_time_);
    // }
    
    return ((curr_millis - last_heartbeat_time_) < HEARTBEAT_INTERVAL);
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
    while (HYTECH_low_voltage_ro_fromS(bms_voltages_.low_voltage_ro) - VOLTAGE_LOOKUP_TABLE[i] < 0) {
        i++;
    }
    charge_ = ( (100 - i) / 100.0) * MAX_PACK_CHARGE;
    SoC_ = (charge_ / MAX_PACK_CHARGE) * 100;

    return charge_;
}

void AMSInterface::calculate_SoC_em(SysTick_s &tick) {
    unsigned long delta_time_micros = tick.micros - last_tick_.micros;
    
    float current = HYTECH_em_current_ro_fromS(em_measurements_.em_current_ro); // Current in amps
    
    // coulombs = amps * microseconds * (1sec / 1000000 microsec)
    charge_ -= (current * delta_time_micros) / 1000000;
    
    SoC_ = (charge_ / MAX_PACK_CHARGE) * 100;
}

void AMSInterface::calculate_SoC_acu(SysTick_s &tick) {
    unsigned long delta_time_micros = tick.micros - last_tick_.micros;

    // Converts analog read (from 0 to 4095) into some value (0.0 to 3.3)
    float current = HYTECH_current_shunt_read_ro_fromS(acu_shunt_measurements_.current_shunt_read_ro);

    // shunt_voltage ranges from -3.33 to 2.635
    float shunt_voltage = (current * (9.22 / 5.1)) - 3.3 - 0.03;

    // calc_current ranges from -666 to 527.176
    float calc_current = (shunt_voltage / 0.005);
    charge_ -= (calc_current * delta_time_micros) / 1000000;

    SoC_ = (charge_ / MAX_PACK_CHARGE) * 100;
}

void AMSInterface::tick(SysTick_s &tick) {

    // If AMSInterface has a valid reading in bms_voltages_ and the charge is not
    // yet initialized, then call initialize_charge.
    if (!has_initialized_charge_) {

        bool bms_voltages_is_invalid = bms_voltages_.low_voltage_ro == 0xFFFFU && bms_voltages_.high_voltage_ro == 0x1111U;

        if (!bms_voltages_is_invalid) {
            initialize_charge();
            has_initialized_charge_ = true;
        }

    }

    // Only calculate the updated SoC if charge has been properly initialized.
    if (has_initialized_charge_) {
        // Do not edit this block! If both calculate_SoC_em AND calculate_SoC_acu are run,
        // then the charge will be subtracted from the SoC member variable twice.
        if (use_em_for_soc_) {
            calculate_SoC_em(tick);
        } else {
            calculate_SoC_acu(tick);
        }
    }

    last_tick_ = tick;
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

void AMSInterface::retrieve_em_measurement_CAN(CAN_message_t &can_msg) {
    Unpack_EM_MEASUREMENT_hytech(&em_measurements_, can_msg.buf, can_msg.len);
}

void AMSInterface::retrieve_current_shunt_CAN(const CAN_message_t &can_msg) {
    Unpack_ACU_SHUNT_MEASUREMENTS_hytech(&acu_shunt_measurements_, can_msg.buf, can_msg.len);
}



