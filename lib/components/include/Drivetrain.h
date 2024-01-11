#include "Inverter.h"

#include <array>

enum class DRIVETRAIN_STATE
{
    WAIT_SYSTEM_READY = 0,
    WAIT_QUIT_DC_ON = 1,
    WAIT_QUIT_INVERTER_ON = 2,
    RTD = 3
};



class DrivetrainComponent
{
public:
    /// @brief order of array: 0: FL, 1: FR, 2: RL, 3: RR
    /// @param inverterComponents inverter pointers
    DrivetrainComponent(const std::array<const InverterComponent *, 4> &inverterComponents)
        : inverterComponents_(inverterComponents)
    {
        state_ = DRIVETRAIN_STATE::WAIT_SYSTEM_READY;
    }

    

    /// @brief changes state of the all the inverters startup process to WAIT_QUIT_DC_ON
    /// @param curr_time current system tick time (millis())
    void enable_drivetrain_hv(unsigned long curr_time);
    void command_drivetrain_no_torque();
    void start_drivetrain(unsigned long curr_time);
    bool hv_over_threshold_on_drivetrain();
    bool drivetrain_ready();
    void disable();
    bool inverter_enable_timeout(unsigned long curr_time);
    bool drivetrain_error_occured();
    DRIVETRAIN_STATE handle_state_machine(unsigned long curr_time);
private:
    void set_drivetrain_driver_enable_(bool in);
    void set_drivetrain_enable_inverters_(bool in);
    
    bool check_drivetrain_quit_dc_on_();
    void set_state_(DRIVETRAIN_STATE new_state);

    DRIVETRAIN_STATE state_;
    std::array<const InverterComponent *, 4> inverterComponents_;
};
