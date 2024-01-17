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
// MCUInterface::MCUInterface(/* args */) {
// }

// Initialize MCU communication
void MCUInterface::init() {
    INV_CAN.begin();
    INV_CAN.setBaudRate(INV_CAN_SPEED);
    TELEM_CAN.begin();
    TELEM_CAN.setBaudRate(TELEM_CAN_SPEED);
    INV_CAN.enableMBInterrupts();
    TELEM_CAN.enableMBInterrupts();
    INV_CAN.onReceive(parse_inv_CAN_message);
    TELEM_CAN.onReceive(parse_telem_CAN_message);
    delay(500);
}

/* Read shutdown system values */
void MCUInterface::read_mcu_status() {

    measure_shutdown_circuit_input();
    measure_shutdown_circuit_voltage();  
    
}

/* Measure shutdown circuits' input */
void MCUInterface::measure_shutdown_circuit_input() {

    mcu_status.set_bms_ok_high(digitalRead(BMS_OK_READ));
    mcu_status.set_imd_ok_high(digitalRead(IMD_OK_READ));
    mcu_status.set_bspd_ok_high(digitalRead(BSPD_OK_READ));
    mcu_status.set_software_ok_high(digitalRead(SOFTWARE_OK_READ)); 
    
}

/* Measure shutdown circuits' voltages */
void MCUInterface::measure_shutdown_circuit_voltage() {

    mcu_status.set_shutdown_b_above_threshold(digitalRead(BOTS_OK_READ));
    mcu_status.set_shutdown_c_above_threshold(digitalRead(IMD_OK_READ));
    mcu_status.set_shutdown_d_above_threshold(digitalRead(BMS_OK_READ));
    mcu_status.set_shutdown_e_above_threshold(digitalRead(BSPD_OK_READ));
    
}

/* Write brake light */
void MCUInterface::set_brake_light(bool brake_pedal_is_active) {

    digitalWrite(BRAKE_LIGHT_CTRL, brake_pedal_is_active);

}

/* Send CAN message */
// Inverter setpoints
void MCUInterface::send_CAN_inverter_setpoints() {
    // FL inverter
    mc_setpoints_command[0].write(msg.buf);
    msg.id = ID_MC1_SETPOINTS_COMMAND;
    msg.len = sizeof(mc_setpoints_command[0]);
    INV_CAN.write(msg);
    // FR inverter
    mc_setpoints_command[1].write(msg.buf);
    msg.id = ID_MC2_SETPOINTS_COMMAND;
    msg.len = sizeof(mc_setpoints_command[1]);
    INV_CAN.write(msg);
    // RL inverter
    mc_setpoints_command[2].write(msg.buf);
    msg.id = ID_MC3_SETPOINTS_COMMAND;
    msg.len = sizeof(mc_setpoints_command[2]);
    INV_CAN.write(msg);
    // RR inverter
    mc_setpoints_command[3].write(msg.buf);
    msg.id = ID_MC4_SETPOINTS_COMMAND;
    msg.len = sizeof(mc_setpoints_command[3]);
    INV_CAN.write(msg);
}

// MCU status
void MCUInterface::send_CAN_mcu_status() {
    mcu_status.write(msg.buf);
    msg.id = ID_MCU_STATUS;
    msg.len = sizeof(mcu_status);
    TELEM_CAN.write(msg);
}

// Pedal readings
void MCUInterface::send_CAN_mcu_pedal_readings() {
    mcu_pedal_readings.write(msg.buf);
    msg.id = ID_MCU_PEDAL_READINGS;
    msg.len = sizeof(mcu_pedal_readings);
    TELEM_CAN.write(msg);
}

// Loadcell readings
void MCUInterface::send_CAN_mcu_load_cells() {
    mcu_load_cells.write(msg.buf);
    msg.id = ID_MCU_LOAD_CELLS;
    msg.len = sizeof(mcu_load_cells);
    TELEM_CAN.write(msg);
}

// Suspension potentiometers
void MCUInterface::send_CAN_mcu_potentiometers() {
    // Front
    mcu_front_potentiometers.write(msg.buf);
    msg.id = ID_MCU_FRONT_POTS;
    msg.len = sizeof(mcu_front_potentiometers);
    TELEM_CAN.write(msg);
    // Rear
    mcu_rear_potentiometers.write(msg.buf);
    msg.id = ID_MCU_REAR_POTS;
    msg.len = sizeof(mcu_rear_potentiometers);
    TELEM_CAN.write(msg);
}

// Analog sensor readings
void MCUInterface::send_CAN_mcu_analog_readings() {
    mcu_analog_readings.write(msg.buf);
    msg.id = ID_MCU_ANALOG_READINGS;
    msg.len = sizeof(mcu_analog_readings);
    TELEM_CAN.write(msg);
}

// IMU accelerometer
void MCUInterface::send_CAN_imu_accelerometer() {
    imu_accelerometer.write(msg.buf);
    msg.id = ID_IMU_ACCELEROMETER;
    msg.len = sizeof(imu_accelerometer);
    TELEM_CAN.write(msg);
}

// IMU gyroscope
void MCUInterface::send_CAN_imu_gyroscope() {
    imu_gyroscope.write(msg.buf);
    msg.id = ID_IMU_GYROSCOPE;
    msg.len = sizeof(imu_gyroscope);
    TELEM_CAN.write(msg);
}

// BMS coulomb counting
void MCUInterface::send_CAN_bms_coulomb_counts() {
    bms_coulomb_counts.write(msg.buf);
    msg.id = ID_BMS_COULOMB_COUNTS;
    msg.len = sizeof(bms_coulomb_counts);
    TELEM_CAN.write(msg);
}

/* Poll CAN message */
void MCUInterface::poll_CAN() {
    INV_CAN.events();
    TELEM_CAN.events();
}

/* Process CAN message */
// Inverter
void MCUInterface::parse_inv_CAN_message(const CAN_message_t &RX_msg) {
    CAN_message_t rx_msg = RX_msg;
    switch (rx_msg.id) {
        // Front
        case ID_MC1_STATUS:     mc_status[0].load(rx_msg.buf);      break;
        case ID_MC2_STATUS:     mc_status[1].load(rx_msg.buf);      break;
        case ID_MC1_TEMPS:      mc_temps[0].load(rx_msg.buf);       break;
        case ID_MC2_TEMPS:      mc_temps[1].load(rx_msg.buf);       break;
        case ID_MC1_ENERGY:     mc_energy[0].load(rx_msg.buf);      break;
        case ID_MC2_ENERGY:     mc_energy[1].load(rx_msg.buf);      break;
        // Rear
        case ID_MC3_STATUS:     mc_status[2].load(rx_msg.buf);      break;
        case ID_MC4_STATUS:     mc_status[3].load(rx_msg.buf);      break;
        case ID_MC3_TEMPS:      mc_temps[2].load(rx_msg.buf);       break;
        case ID_MC4_TEMPS:      mc_temps[3].load(rx_msg.buf);       break;
        case ID_MC3_ENERGY:     mc_energy[2].load(rx_msg.buf);      break;
        case ID_MC4_ENERGY:     mc_energy[3].load(rx_msg.buf);      break;  
        default:                break;
    }
}

// Telemetry
void MCUInterface::parse_telem_CAN_message(const CAN_message_t &RX_msg) {
    CAN_message_t rx_msg = RX_msg;
    switch (rx_msg.id) {
        case ID_BMS_TEMPERATURES:              
            bms_temperatures.load(rx_msg.buf);
            break;
        case ID_BMS_VOLTAGES:
            bms_voltages.load(rx_msg.buf);
            break;
        case ID_BMS_COULOMB_COUNTS:
            bms_coulomb_counts.load(rx_msg.buf);
            break;
        case ID_BMS_STATUS:
            bms_status.load(rx_msg.buf);
            // BMS heartbeat timer
            // timer_bms_heartbeat.reset();
            // timer_bms_heartbeat.interval(BMS_HEARTBEAT_TIMEOUT);
            AMSInterface::set_heartbeat(millis());
            break;
        case ID_DASHBOARD_STATUS:
            dashboard_status.load(rx_msg.buf);
            break;
        default:
            break;
  }
}

FlexCAN_T4<TEENSY_INV_CAN, RX_SIZE_256, TX_SIZE_16> INV_CAN;
FlexCAN_T4<TEENSY_TELEM_CAN, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;