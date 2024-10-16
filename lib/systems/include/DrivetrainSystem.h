#ifndef DRIVETRAINSYSTEM
#define DRIVETRAINSYSTEM

#include "Utility.h"
#include <array>
#include "stdint.h"
#include "SysClock.h"
#include "MCUInterface.h"
#include "SharedDataTypes.h"


template <typename InverterType>
class DrivetrainSystem
{
public:
    /// @brief order of array: 0: FL, 1: FR, 2: RL, 3: RR
    /// @param inverters inverter pointers
    DrivetrainSystem(const std::array<InverterType *, 4> &inverters, MCUInterface *mcu_interface, int init_time_limit_ms, uint16_t min_hv_voltage = 60, int min_cmd_period_ms = 1)
        : inverters_(inverters), init_time_limit_ms_(init_time_limit_ms), min_hv_voltage_(min_hv_voltage), min_cmd_period_(min_cmd_period_ms)
    {
        // values from: https://www.amk-motion.com/amk-dokucd/dokucd/en/content/resources/pdf-dateien/fse/motor_data_sheet_a2370dd_dd5.pdf
        motor_pole_pairs_ = 5;
        lambda_magnetic_flux_wb_ = 1.0;
        hv_en_requested_ = false;
        enable_requested_ = false;
        reset_requested_ = false;
        last_reset_pressed_time_ = 0;
        reset_interval_ = 5000;     // ms
        curr_system_millis_ = 0;
        last_no_torque_cmd_time_ = 0;
        last_reset_cmd_time_ = 0;
        last_disable_cmd_time_ = 0;
        last_general_cmd_time_ = 0; // ms
        mcu_interface_ = mcu_interface;
        dynamic_data_ = {};
    }
    void tick(const SysTick_s &tick);

    void setup_retry()
    {
        reset_drivetrain();
        hv_en_requested_ = false;
        enable_requested_ = false;
    }

    bool handle_inverter_startup(unsigned long curr_time);
    // on entry logic
    void command_drivetrain_no_torque();
    void command_drivetrain_debug();
    // check to see if init time limit has passed
    bool inverter_init_timeout(unsigned long curr_time);

    bool hv_over_threshold_on_drivetrain();
    void disable();
    void disable_no_pins();
    bool drivetrain_error_occured();
    void reset_drivetrain();
    void command_drivetrain(const DrivetrainCommand_s &data);

    void enable_drivetrain_reset();
    void check_reset_condition();

    DrivetrainDynamicReport_s get_dynamic_data();

private:
    std::array<InverterType *, 4> inverters_;
    MCUInterface *mcu_interface_;
    int init_time_limit_ms_;
    uint16_t min_hv_voltage_;
    int motor_pole_pairs_;
    float lambda_magnetic_flux_wb_, L_d_inductance_H_;
    // startup statuses:
    bool hv_en_requested_, enable_requested_;
    // reset inverters
    bool reset_requested_;
    unsigned long last_reset_pressed_time_;
    unsigned long reset_interval_;
    /// @param curr_time current system tick time (millis()) that sets the init phase start time
    void enable_drivetrain_hv_(unsigned long curr_time);
    void request_enable_();
    // startup phase 1
    // status check for start of enable
    bool drivetrain_ready_();
    // startup phase 2
    bool check_drivetrain_quit_dc_on_();

    // final check for drivetrain initialization to check if quit inverter on
    bool drivetrain_enabled_();

    unsigned long curr_system_millis_;
    unsigned int min_cmd_period_;
    unsigned long last_no_torque_cmd_time_, last_reset_cmd_time_, last_disable_cmd_time_, last_general_cmd_time_;

    unsigned long drivetrain_initialization_phase_start_time_;
    DrivetrainCommand_s current_drivetrain_command_;
    DrivetrainDynamicReport_s dynamic_data_;
};

#include "DrivetrainSystem.tpp"
#endif /* DRIVETRAINSYSTEM */
