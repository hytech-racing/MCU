#ifndef __MCU_INTERFACE_H__
#define __MCU_INTERFACE_H__

#include <stdint.h>
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

#define INV_CAN_SPEED       500000
#define TELEM_CAN_SPEED     1000000
#define TEENSY_INV_CAN      CAN2
#define TEENSY_TELEM_CAN    CAN3

#define BMS_OK_READ         5   // SHDN_D_READ
#define IMD_OK_READ         4   // SHDN_C_READ
#define BSPD_OK_READ        6   // SHDN_E_READ
#define SOFTWARE_OK_READ    25  // SHDN_F_READ Watchdog Combined
#define BOTS_OK_READ        3   // SHDN_B_READ

class MCUInterface
{
public:
    MCUInterface() = default;
    // MCUInterface(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>* can1, FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16>* can2): inv_can_(can1), telem_can_(can2) {};

    void init();

    void read_mcu_status();

    /* Feed to system */
    // State machine
    MCU_STATE get_state()                   { return mcu_status.get_state(); }
    bool mech_brake_is_active()             { return mcu_status.get_mech_brake_active(); }
    bool bms_is_ok()                        { return mcu_status.get_bms_ok_high(); }
    bool imd_is_ok()                        { return mcu_status.get_imd_ok_high(); }
    bool no_brake_implausability()          { return mcu_status.get_no_brake_implausability(); }
    bool no_accel_implausability()          { return mcu_status.get_no_accel_implausability(); }
    bool no_accel_brake_implausability()    { return mcu_status.get_no_accel_brake_implausability(); }
    bool software_is_ok()                   { return mcu_status.get_software_is_ok(); }
    
    // Software shutdown
    // mcu_status.set_software_is_ok(true);
    // mcu_status.set_software_is_ok(false);
    // mcu_status.get_software_is_ok()

    // Parse telem CAN
    // bms voltage
    // mcu_status.set_pack_charge_critical(true);
    // mcu_status.set_pack_charge_critical(false);
    // dash
    // mcu_status.get_torque_mode()
    // mcu_status.set_max_torque(TORQUE_2);
    // mcu_status.set_torque_mode(2); break;
    // mcu_status.toggle_launch_ctrl_active();

    // Set state
    // mcu_status.get_state()
    // mcu_status.set_activate_buzzer(false);
    // mcu_status.set_state(new_state);
    // mcu_status.set_activate_buzzer(true);

    // Set inverter torque
    // mcu_status.get_max_torque()

    // Read all adcs
    // mcu_status.set_brake_pedal_active(mcu_pedal_readings.get_brake_pedal_1() >= BRAKE_ACTIVE);
    // mcu_status.get_brake_pedal_active()
    // mcu_status.set_mech_brake_active(mcu_pedal_readings.get_brake_pedal_1() >= BRAKE_THRESHOLD_MECH_BRAKE_1);

    // Check all inverters error
    // mcu_status.set_inverters_error(true);

    // Read mcu status
    // already implemented

    // Calculate pedal implausibilities
    // mcu_status.set_no_accel_implausability(false);
    // mcu_status.set_no_brake_implausability(false);
    // mcu_status.get_mech_brake_active()
    // mcu_status.set_no_accel_brake_implausability(false);
    // mcu_status.get_no_accel_implausability()
    // mcu_status.get_no_brake_implausability()
    // mcu_status.get_no_accel_brake_implausability()

    // Set up
    // mcu_status.set_max_torque(0);
    // mcu_status.set_torque_mode(0);
    // mcu_status.set_software_is_ok(true);
    // mcu_status.set_bms_ok_high(false);
    // mcu_status.set_imd_ok_high(false);
    // mcu_status.set_inverters_error(false);
    // mcu_status.set_max_torque(TORQUE_3);
    // mcu_status.set_torque_mode(3);

    // Loop
    // nah


    
    void send_CAN_inverter_setpoints();
    void send_CAN_mcu_status();
    void send_CAN_mcu_pedal_readings();
    void send_CAN_mcu_load_cells();
    void send_CAN_mcu_potentiometers();
    void send_CAN_mcu_analog_readings();
    void send_CAN_imu_accelerometer();
    void send_CAN_imu_gyroscope();
    void send_CAN_bms_coulomb_counts();

    void poll_CAN();
    // static void parse_front_inv_CAN_message(const CAN_message_t &RX_msg);
    // static void parse_rear_inv_CAN_message(const CAN_message_t &Rx_msg);
    // static void parse_telem_CAN_message(const CAN_message_t &Rx_msg);


    // void set_mcu_status();

    // static FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> FRONT_INV_CAN;
    // static FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> REAR_INV_CAN;
    // static FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;
    // static CAN_message_t msg;

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
    static void parse_inv_CAN_message(const CAN_message_t &RX_msg);
    static void parse_telem_CAN_message(const CAN_message_t &Rx_msg);

    /* Private data members */
    // FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> *inv_can_;
    // FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> *telem_can_;
    CAN_message_t msg;
    


    uint16_t bms_ok_high;
    uint16_t imd_ok_high;
    uint16_t bspd_ok_high;
    uint16_t software_ok_high;
    
    uint16_t shutdown_b_above_threshold;
    uint16_t shutdown_c_above_threshold;
    uint16_t shutdown_d_above_threshold;
    uint16_t shutdown_e_above_threshold;
};

extern FlexCAN_T4<TEENSY_INV_CAN, RX_SIZE_256, TX_SIZE_16> INV_CAN;
extern FlexCAN_T4<TEENSY_TELEM_CAN, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;

#endif /* __MCU_INTERFACE_H__ */
