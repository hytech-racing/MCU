#include "DrivetrainSystem.h"

bool DrivetrainSystem::inverter_init_timeout(unsigned long curr_time)
{
    return ((int)(curr_time - drivetrain_initialization_phase_start_time_) > init_time_limit_ms_);
}

// command functions
void DrivetrainSystem::enable_drivetrain_hv(unsigned long curr_time)
{

    for (auto inv_pointer : inverters_)
    {
        inv_pointer->request_enable_hv();
    }
    drivetrain_initialization_phase_start_time_ = curr_time;
}

void DrivetrainSystem::request_enable()
{
    for (auto inv_pointer : inverters_)
    {
        inv_pointer->request_enable_inverter();
    }
}

void DrivetrainSystem::command_drivetrain_no_torque()
{
    for (auto inv_pointer : inverters_)
    {
        inv_pointer->command_no_torque();
    }
}

// feedback functions
bool DrivetrainSystem::drivetrain_ready()
{
    for (auto inv_pointer : inverters_)
    {
        if (!inv_pointer->inverter_system_ready())
        {
            return false;
        }
    }
    return true;
}

bool DrivetrainSystem::check_drivetrain_quit_dc_on()
{
    for (auto inv_pointer : inverters_)
    {
        if (!inv_pointer->dc_quit_on())
        {
            return false;
        }
    }
    return true;
}

bool DrivetrainSystem::drivetrain_enabled()
{
    for (auto inv_pointer : inverters_)
    {
        if (!inv_pointer->quit_inverter_on())
        {
            return false;
        }
    }
    return true;
}