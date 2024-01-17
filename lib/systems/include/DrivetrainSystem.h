#ifndef DRIVETRAINSYSTEM
#define DRIVETRAINSYSTEM

#include "InverterSystem.h"

#include <array>

enum class DRIVETRAIN_STATE
{
    WAIT_SYSTEM_READY = 0,
    WAIT_QUIT_DC_ON = 1,
    WAIT_QUIT_INVERTER_ON = 2,
    RTD = 3
};

struct DrivetrainCommand
{
    float torque_lf;
    float speed_lf;

    float torque_rf;
    float speed_rf;
    
    float torque_lr;
    float speed_lr;
    
    float torque_rr;
    float speed_rr;
};

class DrivetrainSystem
{
public:
    /// @brief order of array: 0: FL, 1: FR, 2: RL, 3: RR
    /// @param inverters inverter pointers
    DrivetrainSystem(const std::array<const InverterSystem *, 4> &inverters)
        : inverters_(inverters)
    {
        state_ = DRIVETRAIN_STATE::WAIT_SYSTEM_READY;
    }

    

    /// @brief changes state of the all the inverters startup process to WAIT_QUIT_DC_ON
    /// @param curr_time current system tick time (millis())
    void enable_drivetrain_hv(unsigned long curr_time);
    void request_enable(unsigned long curr_time);
    void command_drivetrain_no_torque();
    void start_drivetrain(unsigned long curr_time);
    bool hv_over_threshold_on_drivetrain();
    bool drivetrain_ready();
    void disable();
    bool inverter_enable_timeout(unsigned long curr_time);
    bool drivetrain_error_occured();
    DRIVETRAIN_STATE handle_state_machine(unsigned long curr_time);

    void command_drivetrain(const DrivetrainCommand& data);
private:
    void set_drivetrain_driver_enable_(bool in);
    void set_drivetrain_enable_inverters_(bool in);
    
    bool check_drivetrain_quit_dc_on_();
    void set_state_(DRIVETRAIN_STATE new_state);

    DRIVETRAIN_STATE state_;
    std::array<const InverterSystem *, 4> inverters_;
};


#endif /* DRIVETRAINSYSTEM */
