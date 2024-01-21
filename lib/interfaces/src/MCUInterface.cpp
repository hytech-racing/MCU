#include "MCUInterface.h"

/* Static members */
/* CAN bus */
// FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> MCUInterface::FRONT_INV_CAN;
// FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> MCUInterface::REAR_INV_CAN;
// FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> MCUInterface::TELEM_CAN;
// CAN_message_t MCUInterface::msg;

/* CAN messages */
// MCU onboard readings
// MCU_status                  MCUInterface::mcu_status;
// MCU_pedal_readings          MCUInterface::mcu_pedal_readings;
// MCU_load_cells              MCUInterface::mcu_load_cells;
// MCU_front_potentiometers    MCUInterface::mcu_front_potentiometers;
// MCU_rear_potentiometers     MCUInterface::mcu_rear_potentiometers;
// MCU_analog_readings         MCUInterface::mcu_analog_readings;
// IMU_accelerometer           MCUInterface::imu_accelerometer;
// IMU_gyroscope               MCUInterface::imu_gyroscope;
// // Motor control
// MC_status                   MCUInterface::mc_status[4];
// MC_temps                    MCUInterface::mc_temps[4];
// MC_energy                   MCUInterface::mc_energy[4];
// MC_setpoints_command        MCUInterface::mc_setpoints_command[4];
// // ACU CAN
// BMS_coulomb_counts          MCUInterface::bms_coulomb_counts;
// BMS_status                  MCUInterface::bms_status;
// BMS_temperatures            MCUInterface::bms_temperatures;
// BMS_voltages                MCUInterface::bms_voltages;
// // Dashboard CAN
// Dashboard_status            MCUInterface::dashboard_status;

/* Member functions */

/* Initialize shutdown circuit input reading */
void MCUInterface::init() {
    bms_ok_high = false;
    imd_ok_high = false;
}

/* Read shutdown system values */
void MCUInterface::read_mcu_status() {

    measure_shutdown_circuit_input();
    measure_shutdown_circuit_voltage();  
    
}

/* Measure shutdown circuits' input */
void MCUInterface::measure_shutdown_circuit_input() {

    bms_ok_high = digitalRead(BMS_OK_READ);
    imd_ok_high = digitalRead(IMD_OK_READ);
    bspd_ok_high = digitalRead(BSPD_OK_READ);
    software_ok_high = digitalRead(SOFTWARE_OK_READ); 
    
}

/* Measure shutdown circuits' voltages */
void MCUInterface::measure_shutdown_circuit_voltage() {

    shutdown_b_above_threshold = digitalRead(BOTS_OK_READ);
    shutdown_c_above_threshold = digitalRead(IMD_OK_READ);
    shutdown_d_above_threshold = digitalRead(BMS_OK_READ);
    shutdown_e_above_threshold = digitalRead(BSPD_OK_READ);
    
}

/* Write brake light */
void MCUInterface::set_brake_light(bool brake_pedal_is_active) {

    digitalWrite(BRAKE_LIGHT_CTRL, brake_pedal_is_active);

}

/* Send CAN message */
// MCU status
void MCUInterface::send_CAN_mcu_status(CAN_message_t &msg) {
    update_CAN_msg();
    mcu_status_->write(msg.buf);
    msg.id = ID_MCU_STATUS;
    msg.len = sizeof(mcu_status);
    // TELEM_CAN.write(msg);
}

void MCUInterface::update_CAN_msg() {
    // Shutdown circuit input
    mcu_status.set_bms_ok_high(bms_ok_high);
    mcu_status.set_imd_ok_high(imd_ok_high);
    mcu_status.set_bspd_ok_high(bspd_ok_high);
    mcu_status.set_software_ok_high(software_ok_high);
    // Shutdown circuit voltage
    mcu_status.set_shutdown_b_above_threshold(shutdown_b_above_threshold);
    mcu_status.set_shutdown_c_above_threshold(shutdown_c_above_threshold);
    mcu_status.set_shutdown_d_above_threshold(shutdown_d_above_threshold);
    mcu_status.set_shutdown_e_above_threshold(shutdown_e_above_threshold);
}


