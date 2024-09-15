#include "AMSInterface.h"
#include "SysClock.h"

// Initializes the system state
void AMSInterface::init(SysTick_s &initial_tick) {
    pinMode(pin_software_ok_, OUTPUT);
    set_heartbeat(initial_tick.millis);
    last_tick_ = initial_tick;
    timestamp_start_ = -1;

    bms_voltages_.low_voltage_ro = 0xFFFFU;
    bms_voltages_.high_voltage_ro = 0x1111U;
}

void AMSInterface::set_start_state() {
    digitalWrite(pin_software_ok_, HIGH);
}

void AMSInterface::set_state_ok_high(bool ok_high) {
    digitalWrite(pin_software_ok_, ok_high ? HIGH : LOW);
}

void AMSInterface::set_heartbeat(unsigned long curr_millis) {
    last_heartbeat_time_ = curr_millis;
}

bool AMSInterface::heartbeat_received(unsigned long curr_millis) {
    return ((curr_millis - last_heartbeat_time_) < HEARTBEAT_INTERVAL);
}

void AMSInterface::enqueue_new_CAN(U* structure, uint32_t (*pack_function)(U*, uint8_t*, uint8_t*, uint8_t*)) {
    CAN_message_t can_msg;
    can_msg.id = pack_function(structure, can_msg.buf, &can_msg.len, (uint8_t*)&can_msg.flags.extended);
    uint8_t buf[sizeof(CAN_message_t)] = {};
    memmove(buf, &can_msg, sizeof(CAN_message_t));
    msg_queue_->push_back(buf, sizeof(CAN_message_t));
}

void AMSInterface::retrieve_status_CAN(unsigned long curr_millis, CAN_message_t &recvd_msg) {
    bms_status_.load(recvd_msg.buf);
    set_heartbeat(curr_millis);
}

void AMSInterface::retrieve_temp_CAN(CAN_message_t &recvd_msg) {
    bms_temperatures_.load(recvd_msg.buf);
}

void AMSInterface::retrieve_voltage_CAN(CAN_message_t &can_msg) {
    Unpack_BMS_VOLTAGES_hytech(&bms_voltages_, can_msg.buf, can_msg.len);

    if (!has_received_bms_voltage_) {
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
