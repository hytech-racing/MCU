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
    // 1. if system ready 
    
    if (drivetrain_ready_() && !check_drivetrain_quit_dc_on_() && !drivetrain_enabled_())
    {

        // Serial.println("drivetrain ready and enabling drivetrain hv");
        enable_drivetrain_hv_(curr_time);

        // hv_en_requested_ = true;
        return false;
    }
    else if (drivetrain_ready_() && check_drivetrain_quit_dc_on_() && !drivetrain_enabled_())
    {
        
        request_enable_();
    //     enable_requested_ = true;
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
    // mcu_interface_->enable_inverters_pin();
    for (auto inv_pointer : inverters_)
    {
        inv_pointer->request_enable_inverter();
    }
}
/*----------------------------------------------------------------------------------------*/
// rate limited commands. we will only be commanding one of these at a time.
/*----------------------------------------------------------------------------------------*/
template <typename InverterType>
void DrivetrainSystem<InverterType>::command_drivetrain_debug()
{
    // if ((curr_system_millis_ - last_no_torque_cmd_time_) > min_cmd_period_)
    // {
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->command_debug();
        }
        last_no_torque_cmd_time_ = curr_system_millis_;
    // }
}

template <typename InverterType>
void DrivetrainSystem<InverterType>::command_drivetrain_no_torque()
{
    // if ((curr_system_millis_ - last_no_torque_cmd_time_) > min_cmd_period_)
    // {
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->command_no_torque();
        }
        last_no_torque_cmd_time_ = curr_system_millis_;
    // }
}



template <typename InverterType>
void DrivetrainSystem<InverterType>::check_reset_condition()
{
    // if ((curr_system_millis_ - last_reset_pressed_time_) > reset_interval_)
    // {   
    reset_requested_ = false;
    // }
}

template <typename InverterType>
void DrivetrainSystem<InverterType>::reset_drivetrain()
{
    
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->command_reset();
        }  

}

template <typename InverterType>
void DrivetrainSystem<InverterType>::disable_no_pins()
{    
    // if ((curr_system_millis_ - last_disable_cmd_time_) > min_cmd_period_)
    // {
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->disable();
        }
        last_disable_cmd_time_ = curr_system_millis_;
    // }

}

template <typename InverterType>
void DrivetrainSystem<InverterType>::disable()
{    
    // if ((curr_system_millis_ - last_disable_cmd_time_) > min_cmd_period_)
    // {
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->disable();
        }
        last_disable_cmd_time_ = curr_system_millis_;
    // }

    mcu_interface_->disable_inverters_pin();
    mcu_interface_->enable_inverters_pin();
}

template <typename InverterType>
void DrivetrainSystem<InverterType>::command_drivetrain(const DrivetrainCommand_s &data)
{
    // if ((curr_system_millis_ - last_general_cmd_time_) > min_cmd_period_)
    // {
        int index = 0;
        for (auto inv_pointer : inverters_)
        {
            inv_pointer->handle_command({data.inverter_torque_limit[index], data.speeds_rpm[index]});
            index++;
        }
        // last_general_cmd_time_ = curr_system_millis_;
    // }
}
/*----------------------------------------------------------------------------------------*/
// feedback functions
/*----------------------------------------------------------------------------------------*/
template <typename InverterType>
bool DrivetrainSystem<InverterType>::drivetrain_error_occured()
{
    for (auto inv_pointer : inverters_)
    {
        if (inv_pointer->get_error())
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
    // return (inverters_[3]->dc_quit_on());
    for (auto inv_pointer : inverters_)
    {
        if (!inv_pointer->get_quit_dc_on())
        {
            return false;
        }
    }
    return true;
}

template <typename InverterType>
bool DrivetrainSystem<InverterType>::drivetrain_enabled_()
{

    // return (inverters_[3]->quit_inverter_on());
    for (auto inv_pointer : inverters_)
    {
        if (!inv_pointer->get_quit_inverter_on())
        {
            return false;
        }
    }
    return true;
}

template <typename InverterType>
DrivetrainDynamicReport_s DrivetrainSystem<InverterType>::get_dynamic_data()
{
    
    // TODO idk
    dynamic_data_.measuredInverterFLPackVoltage = inverters_[0]->dc_bus_voltage();
    int inverter_ind = 0;
    for (auto inv_pointer : inverters_)
    {
        auto iq = inv_pointer->get_motor_torque(); // iq in A
        auto id = inv_pointer->get_commanded_torque();    // id in A
        dynamic_data_.measuredSpeeds[inverter_ind] = inv_pointer->get_speed();
        dynamic_data_.measuredTorqueCurrents[inverter_ind] = iq;
        dynamic_data_.measuredMagnetizingCurrents[inverter_ind] = id;

        // TODO
        // data.measuredTorques[inverter_ind] = inv_pointer->get_actual_torque();
        inverter_ind++;
    }
    return dynamic_data_;
}