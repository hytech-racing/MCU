#ifndef DRIVETRAINSYSTEM
#define DRIVETRAINSYSTEM

#include "Utility.h"
#include <array>
#include "stdint.h"
struct DrivetrainCommand_s
{ 
    float speeds[NUM_MOTORS];
    float posTorqueLimits[NUM_MOTORS];
    float negTorqueLimits[NUM_MOTORS];
};

struct DrivetrainDynamicReport_s
{
    float measuredPackVoltage;
    float measuredSpeeds[NUM_MOTORS];
    float measuredTorques[NUM_MOTORS];
    float measuredTorqueCurrents[NUM_MOTORS];
    float measuredMagnetizingCurrents[NUM_MOTORS];
};

template<typename InverterType>
class DrivetrainSystem
{
public:
    /// @brief order of array: 0: FL, 1: FR, 2: RL, 3: RR
    /// @param inverters inverter pointers
    DrivetrainSystem(const std::array<InverterType *, 4> &inverters, int init_time_limit_ms )
        : inverters_(inverters),init_time_limit_ms_(init_time_limit_ms)
    {

        // TODO set min_hv_voltage_
    }

    // startup phase 1
    // status check for start of enable
    bool drivetrain_ready();
    /// @param curr_time current system tick time (millis()) that sets the init phase start time
    void enable_drivetrain_hv(unsigned long curr_time);
    
    // startup phase 2
    bool check_drivetrain_quit_dc_on();


    // on entry logic
    void request_enable();
    void command_drivetrain_no_torque();
    
    // final check for drivetrain initialization to check if quit inverter on
    bool drivetrain_enabled();
    
    // check to see if init time limit has passed 
    bool inverter_init_timeout(unsigned long curr_time);

    bool hv_over_threshold_on_drivetrain();
    void disable();
    bool drivetrain_error_occured();
    void reset_drivetrain();

    void command_drivetrain(const DrivetrainCommand_s& data);
private:

    uint16_t min_hv_voltage_;
    std::array<InverterType*, 4> inverters_;
    int init_time_limit_ms_;
    unsigned long drivetrain_initialization_phase_start_time_;
    
};

#include "DrivetrainSystem.tpp"
#endif /* DRIVETRAINSYSTEM */