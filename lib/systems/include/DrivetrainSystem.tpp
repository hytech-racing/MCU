#include "DrivetrainSystem.h"

template <typename InverterType>
void DrivetrainSystem<InverterType>::tick(const SysTick_s &tick)
{
    curr_system_millis_ = tick.millis;
}

template <typename InverterType>
bool DrivetrainSystem<InverterType>::inverter_init_timeout(unsigned long curr_time)
{
    return ((int)(curr_time - drivetrain_initialization_phase_start_time_) > init_time_limit_ms_);
}

/*----------------------------------------------------------------------------------------*/
// async command functions
/*----------------------------------------------------------------------------------------*/
template <typename InverterType>
bool DrivetrainSystem<InverterType>::handle_inverter_startup(unsigned long curr_time)
{
    if (drivetrain_ready_() && !hv_en_requested_)
    {
        enable_drivetrain_hv_(curr_time);
        hv_en_requested_ = true;
        return false;
    }
    else if (drivetrain_ready_() && check_drivetrain_quit_dc_on_() && !enable_requested_ && hv_en_requested_)
    {
        request_enable_();
        enable_requested_ = true;
        return false;
    }
    bool all_ready = (drivetrain_ready_() && check_drivetrain_quit_dc_on_() && drivetrain_enabled_());
    return all_ready;
}

template <typename InverterType>
void DrivetrainSystem<InverterType>::enable_drivetrain_hv_(unsigned long curr_time)
{
    for (auto inv_pointer : inverters_)
    {
        inv_pointer->request_enable_hv();
    }
    drivetrain_initialization_phase_start_time_ = curr_time;
}

template <typename InverterType>
void DrivetrainSystem<InverterType>::request_enable_()
{
    for (auto inv_pointer : inverters_)
    {
        inv_pointer->request_enable_inverter();
    }
}
/*----------------------------------------------------------------------------------------*/
// rate limited commands. we will only be commanding one of these at a time.
/*----------------------------------------------------------------------------------------*/
template <typename InverterType>
void DrivetrainSystem<InverterType>::command_drivetrain_no_torque()
{
    if ((curr_system_millis_ - last_no_torque_cmd_time_) > min_cmd_period_)
    {
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->command_no_torque();
        }
        last_no_torque_cmd_time_ = curr_system_millis_;
    }
}

template <typename InverterType>
void DrivetrainSystem<InverterType>::reset_drivetrain()
{
    if ((curr_system_millis_ - last_reset_cmd_time_) > min_cmd_period_)
    {
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->command_reset();
        }
        last_reset_cmd_time_ = curr_system_millis_;
    }
}

template <typename InverterType>
void DrivetrainSystem<InverterType>::disable()
{
    if ((curr_system_millis_ - last_disable_cmd_time_) > min_cmd_period_)
    {
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->disable();
        }
        last_disable_cmd_time_ = curr_system_millis_;
    }
}

template <typename InverterType>
void DrivetrainSystem<InverterType>::command_drivetrain(const DrivetrainCommand_s &data)
{
    if ((curr_system_millis_ - last_general_cmd_time_) > min_cmd_period_)
    {
        int index = 0;
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->handle_command({data.torqueSetpoints[index], data.speeds_rpm[index]});
            index++;
        }
        last_general_cmd_time_ = curr_system_millis_;
    }
}
/*----------------------------------------------------------------------------------------*/
// feedback functions
/*----------------------------------------------------------------------------------------*/
template <typename InverterType>
bool DrivetrainSystem<InverterType>::drivetrain_error_occured()
{
    for (auto inv_pointer : inverters_)
    {
        if (inv_pointer->error())
        {
            return true;
        }
    }
    return false;
}

template <typename InverterType>
bool DrivetrainSystem<InverterType>::hv_over_threshold_on_drivetrain()
{
    for (auto inv_pointer : inverters_)
    {
        if (!(inv_pointer->dc_bus_voltage() > min_hv_voltage_))
        {
            return false;
        }
    }
    return true;
}
template <typename InverterType>
bool DrivetrainSystem<InverterType>::drivetrain_ready_()
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

template <typename InverterType>
bool DrivetrainSystem<InverterType>::check_drivetrain_quit_dc_on_()
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

template <typename InverterType>
bool DrivetrainSystem<InverterType>::drivetrain_enabled_()
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

template <typename InverterType>
DrivetrainDynamicReport_s DrivetrainSystem<InverterType>::get_current_data()
{
    DrivetrainDynamicReport_s data;
    // TODO idk
    data.measuredInverterFLPackVoltage = inverters_[0]->dc_bus_voltage();
    int inverter_ind = 0;
    for (auto inv_pointer : inverters_)
    {
        auto iq = inv_pointer->get_torque_current(); // iq in A
        auto id = inv_pointer->get_mag_current();    // id in A
        data.measuredSpeeds[inverter_ind] = (float)inv_pointer->get_speed();
        data.measuredTorqueCurrents[inverter_ind] = iq;
        data.measuredMagnetizingCurrents[inverter_ind] = id;

        // TODO
        // data.measuredTorques[inverter_ind] = inv_pointer->get_actual_torque();
        inverter_ind++;
    }
    return data;
}