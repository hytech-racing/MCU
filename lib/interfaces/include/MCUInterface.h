#ifndef __MCU_INTERFACE__
#define __MCU_INTERFACE__

#include <stdint.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

#define INV_CAN_SPEED 500000
#define TELEM_CAN_SPEED 1000000

class MCUInterface
{

public:
    MCUInterface(/* args */);

    void init();

    void read_mcu_status();    
    
    void send_CAN_inverter_setpoint()
    void send_CAN_mcu_status();
    void send_CAN_mcu_pedal_readings();
    void send_CAN_mcu_load_cells();
    void send_CAN_mcu_potentiometers();
    void send_CAN_mcu_analog_readings();
    void send_CAN_imu_accelerometer();
    void send_CAN_imu_gyroscope();
    void send_CAN_bms_coulomb_counts();

    // void set_mcu_status();

    static FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> FRONT_INV_CAN;
    static FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> REAR_INV_CAN;
    static FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;
    static CAN_message_t msg;

    /* CAN messages */
    // MCU onboard readings
    static MCU_status                  mcu_status;
    static MCU_pedal_readings          mcu_pedal_readings;
    static MCU_load_cells              mcu_load_cells;
    static MCU_front_potentiometers    mcu_front_potentiometers;
    static MCU_rear_potentiometers     mcu_rear_potentiometers;
    static MCU_analog_readings         mcu_analog_readings;
    static IMU_accelerometer           imu_accelerometer;
    static IMU_gyroscope               imu_gyroscope;
    // Motor control
    static MC_status                   mc_status[4];
    static MC_temps                    mc_temps[4];
    static MC_energy                   mc_energy[4];
    static MC_setpoints_command        mc_setpoints_command[4];
    // ACU CAN
    static BMS_coulomb_counts          bms_coulomb_counts;
    static BMS_status                  bms_status;
    static BMS_temperatures            bms_temperatures;
    static BMS_voltages                bms_voltages;
    // Dashboard CAN
    static Dashboard_status            dashboard_status;

private:
    /* Private utility functions */
    void measure_shutdown_circuit_input();
    void measure_shutdown_circuit_voltage();

    


    uint16_t bms_ok_high;
    uint16_t imd_ok_high;
    uint16_t bspd_ok_high;
    uint16_t software_ok_high;
    
    uint16_t shutdown_b_above_threshold;
    uint16_t shutdown_c_above_threshold;
    uint16_t shutdown_d_above_threshold;
    uint16_t shutdown_e_above_threshold;
};




#endif /* __MCU_INTERFACE__ */
