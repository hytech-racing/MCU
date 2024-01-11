#include "Inverter.h"

#include <array>

class DrivetrainComponent
{
public:

    /// @brief order of array: 0: FL, 1: FR, 2: RL, 3: RR
    /// @param inverterComponents inverter pointers
    DrivetrainComponent(const std::array<const InverterComponent *, 4> &inverterComponents)
        : inverterComponents_(inverterComponents)
    {
    }

    /// @brief changes state of the all the inverters startup process to WAIT_QUIT_DC_ON
    /// @param curr_time current system tick time (millis())
    void enable_drivetrain_hv(unsigned long curr_time);
    
    void start_drivetrain(unsigned long curr_time);
    bool hv_over_threshold_on_all_inverters();
    bool all_inverters_ready();
private:
    std::array<const InverterComponent *, 4> inverterComponents_;
};
