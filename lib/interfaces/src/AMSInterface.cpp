#include "AMSInterface.h"
#include "SysClock.h"

/* Send inverter CAN messages with new CAN library */
template<typename U>
void AMSInterface::enqueue_new_CAN(U* structure, uint32_t (* pack_function)(U*, uint8_t*, uint8_t*, uint8_t*)) {
    CAN_message_t can_msg;
    can_msg.id = pack_function(structure, can_msg.buf, &can_msg.len, (uint8_t*) &can_msg.flags.extended);
    uint8_t buf[sizeof(CAN_message_t)] = {};
    memmove(buf, &can_msg, sizeof(CAN_message_t));
    msg_queue_->push_back(buf, sizeof(CAN_message_t));
}

void AMSInterface::init(SysTick_s &initial_tick) {
    
    // Set pin mode
    pinMode(pin_software_ok_, OUTPUT);

    set_heartbeat(initial_tick.millis);

    last_tick_ = initial_tick;

    timestamp_start_ = -1; //starts at -1

    // Initializes the bms_voltages_ member variable to an invalid state. This will
    // get overridden once retrieve_voltage_CAN() has been called at least once.
    bms_voltages_.low_voltage_ro = 0xFFFFU;
    bms_voltages_.high_voltage_ro = 0x1111U;

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
    bms_low_voltage = HYTECH_low_voltage_ro_fromS(bms_voltages_.low_voltage_ro);
    filtered_min_cell_voltage = filtered_min_cell_voltage * cell_temp_alpha + (1.0 - cell_voltage_alpha) * bms_low_voltage;
    return filtered_min_cell_voltage;
}

float AMSInterface::initialize_charge() {
    int i = 0;
    float lowest_voltage = HYTECH_low_voltage_ro_fromS(bms_voltages_.low_voltage_ro);

    while (lowest_voltage - VOLTAGE_LOOKUP_TABLE[i] < 0) {
        i++;
    }
    charge_ = ( (100 - i) / 100.0) * MAX_PACK_CHARGE;
    SoC_ = (charge_ / MAX_PACK_CHARGE) * 100;

    return charge_;
}

void AMSInterface::calculate_SoC_em(const SysTick_s &tick) {
    unsigned long delta_time_micros = tick.micros - last_tick_.micros;
    
    float current = HYTECH_em_current_ro_fromS(em_measurements_.em_current_ro); // Current in amps
    
    // coulombs = amps * microseconds * (1sec / 1000000 microsec)
    charge_ -= (current * delta_time_micros) / 1000000;
    
    SoC_ = (charge_ / MAX_PACK_CHARGE) * 100;
}

void AMSInterface::calculate_SoC_acu(const SysTick_s &tick) {
    unsigned long delta_time_micros = tick.micros - last_tick_.micros;

    // Converts analog read (from 0 to 4095) into some value (0.0 to 3.3)
    // float current = HYTECH_current_shunt_read_ro_fromS(acu_shunt_measurements_.current_shunt_read_ro);

    // shunt_voltage ranges from -3.33 to 2.635
    // float shunt_voltage = (current * (9.22 / 5.1)) - 3.3 - 0.03;

    // calc_current ranges from -666 to 527.176
    // float calc_current = (shunt_voltage / 0.005);
    charge_ -= (HYTECH_current_shunt_read_ro_fromS(acu_shunt_measurements_.current_shunt_read_ro) * delta_time_micros) / 1000000;

    SoC_ = (charge_ / MAX_PACK_CHARGE) * 100;
}

void AMSInterface::tick(const SysTick_s &tick) {

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

    // If AMSInterface has a valid reading in bms_voltages_ and enough time has passed since init(), then initialize charge
    if (!has_initialized_charge_ && ((tick.millis - timestamp_start_) >= DEFAULT_INITIALIZATION_WAIT_INTERVAL)) {
    
        initialize_charge();
        has_initialized_charge_ = true;

    }

    // Send CAN message
    // enqueue_state_of_charge_CAN();
    STATE_OF_CHARGE_t soc_struct;
    soc_struct.charge_percentage_ro = HYTECH_charge_percentage_ro_toS(SoC_);
    soc_struct.charge_coulombs_ro = HYTECH_charge_coulombs_ro_toS(charge_);
    soc_struct.min_cell_voltage_est_ro = HYTECH_min_cell_voltage_est_ro_toS(VOLTAGE_LOOKUP_TABLE[100 - (int) SoC_]);
    enqueue_new_CAN<STATE_OF_CHARGE_t>(&soc_struct, Pack_STATE_OF_CHARGE_hytech);

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

    if (!has_received_bms_voltage_)
    {
        has_received_bms_voltage_ = true;
        timestamp_start_ = last_tick_.millis;
    }
    
}

void AMSInterface::retrieve_em_measurement_CAN(CAN_message_t &can_msg) {
    Unpack_EM_MEASUREMENT_hytech(&em_measurements_, can_msg.buf, can_msg.len);
}

void AMSInterface::retrieve_current_shunt_CAN(const CAN_message_t &can_msg) {
    Unpack_ACU_SHUNT_MEASUREMENTS_hytech(&acu_shunt_measurements_, can_msg.buf, can_msg.len);
}

void AMSInterface::calculate_acc_derate_factor() {
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
}

float AMSInterface::get_acc_derate_factor() {
    calculate_acc_derate_factor();
    return acc_derate_factor;
}


