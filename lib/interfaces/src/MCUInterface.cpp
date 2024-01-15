#include "MCUInterface.h"

MCUInterface::MCUInterface(/* args */) {
}

// Initialize MCU communication
void MCUInterface::init() {
    FRONT_INV_CAN.begin();
    FRONT_INV_CAN.setBaudRate(INV_CAN_SPEED);
    REAR_INV_CAN.begin();
    REAR_INV_CAN.setBaudRate(INV_CAN_SPEED);
    TELEM_CAN.begin();
    TELEM_CAN.setBaudRate(TELEM_CAN_SPEED);
    FRONT_INV_CAN.enableMBInterrupts();
    REAR_INV_CAN.enableMBInterrupts();
    TELEM_CAN.enableMBInterrupts();
    FRONT_INV_CAN.onReceive(parse_front_inv_can_message);
    REAR_INV_CAN.onReceive(parse_rear_inv_can_message);
    TELEM_CAN.onReceive(parse_telem_can_message);
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

/* Send CAN message */
// Inverter setpoints
void MCUInterface::send_CAN_inverter_setpoint() {
    // FL inverter
    mc_setpoints_command[0].write(msg.buf);
    msg.id = ID_MC1_SETPOINTS_COMMAND;
    msg.len = sizeof(mc_setpoints_command[0]);
    FRONT_INV_CAN.write(msg);
    // FR inverter
    mc_setpoints_command[1].write(msg.buf);
    msg.id = ID_MC2_SETPOINTS_COMMAND;
    msg.len = sizeof(mc_setpoints_command[1]);
    FRONT_INV_CAN.write(msg);
    // RL inverter
    mc_setpoints_command[2].write(msg.buf);
    msg.id = ID_MC3_SETPOINTS_COMMAND;
    msg.len = sizeof(mc_setpoints_command[2]);
    REAR_INV_CAN.write(msg);
    // RR inverter
    mc_setpoints_command[3].write(msg.buf);
    msg.id = ID_MC4_SETPOINTS_COMMAND;
    msg.len = sizeof(mc_setpoints_command[3]);
    REAR_INV_CAN.write(msg);
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