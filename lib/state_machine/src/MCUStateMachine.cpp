#include "MCUStateMachine.h"

void MCUStateMachine::tick_state_machine(unsigned long current_millis)
{
    switch (mcu_status.get_state())
    {
    case MCU_STATE::STARTUP:
        break;

    case MCU_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:

        // if TS is above HV threshold, move to Tractive System Active
        if (drivetrain_->hv_over_threshold_on_any_inverter())
        {

            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
        }
        break;

    case MCU_STATE::TRACTIVE_SYSTEM_ACTIVE:
        if (!drivetrain_->hv_over_threshold_on_all_inverters())
        {
            set_state(MCU_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);
            break;
        }

        if (drivetrain_->all_inverters_ready())
        {
            drivetrain_->enable_drivetrain_hv(current_millis);
        }
        if (dashboard_->start_button_pressed() && pedals_->mech_brake_active())
        {
            set_state(MCU_STATE::ENABLING_INVERTER);
        }
        break;

    // TODO: below in the scope of this function
    case MCU_STATE::ENABLING_INVERTER:
        check_TS_active();
        // inverter enabling timed out
        if (timer_inverter_enable.check())
        {

            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
        }

        switch (inverter_startup_state)
        {
        case INVERTER_STARTUP_STATE::WAIT_SYSTEM_READY:
            if (check_all_inverters_system_ready())
            {
                set_all_inverters_dc_on(true);
                inverter_startup_state = INVERTER_STARTUP_STATE::WAIT_QUIT_DC_ON;
            }
            break;

        case INVERTER_STARTUP_STATE::WAIT_QUIT_DC_ON:
            if (check_all_inverters_quit_dc_on())
            {
                set_all_inverters_no_torque();
                set_all_inverters_driver_enable(true);
                set_all_inverters_inverter_enable(true);
                inverter_startup_state = INVERTER_STARTUP_STATE::WAIT_QUIT_INVERTER_ON;
            }
            break;

        case INVERTER_STARTUP_STATE::WAIT_QUIT_INVERTER_ON:
            if (check_all_inverters_quit_inverter_on())
            {

                set_state(MCU_STATE::WAITING_READY_TO_DRIVE_SOUND);
            }
            break;
        }
        break;

    case MCU_STATE::WAITING_READY_TO_DRIVE_SOUND:
        check_TS_active();

        // if the ready to drive sound has been playing for long enough, move to ready to drive mode
        if (timer_ready_sound.check())
        {

            set_state(MCU_STATE::READY_TO_DRIVE);
        }
        break;

    case MCU_STATE::READY_TO_DRIVE:
        check_TS_active();

        if (check_all_inverters_error())
        {
            set_all_inverters_disabled();
            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
        }

        calculate_pedal_implausibilities();

        if (
            pedal_implausability_duration <= 100 &&
            mcu_status.get_bms_ok_high() &&
            mcu_status.get_imd_ok_high()

        )
        {
            set_inverter_torques();
        }
        else if (mcu_status.get_bms_ok_high() && mcu_status.get_imd_ok_high())
        {
            set_inverter_torques_regen_only();
        }
        else
        {
            Serial.println("not calculating torque");
            Serial.printf("no brake implausibility: %d\n", mcu_status.get_no_brake_implausability());
            Serial.printf("no accel implausibility: %d\n", mcu_status.get_no_accel_implausability());
            Serial.printf("no accel brake implausibility: %d\n", mcu_status.get_no_accel_brake_implausability());
            Serial.printf("software is ok: %d\n", mcu_status.get_software_is_ok());
            Serial.printf("get bms ok high: %d\n", mcu_status.get_bms_ok_high());
            Serial.printf("get imd ok high: %d\n", mcu_status.get_imd_ok_high());
            set_all_inverters_no_torque();
        }

        break;
    }
}

void MCUStateMachine::set_state(MCU_STATE new_state)
{
    hal_println("running exit logic");
    handle_exit_logic_(current_state_);

    current_state_ = new_state;

    hal_println("running entry logic");
    handle_entry_logic_(new_state);
}

void MCUStateMachine::handle_exit_logic_(MCU_STATE prev_state, unsigned long curr_time)
{
    switch (mcu_status.get_state())
    {
    case MCU_STATE::STARTUP:
        break;
    case MCU_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
        break;
    case MCU_STATE::TRACTIVE_SYSTEM_ACTIVE:
        break;
    case MCU_STATE::ENABLING_INVERTER:

        break;
    case MCU_STATE::WAITING_READY_TO_DRIVE_SOUND:
        // make dashboard stop buzzer
        buzzer_->deactivate_buzzer();
        break;
    case MCU_STATE::READY_TO_DRIVE:
    {
        drivetrain_->start_drivetrain(curr_time);
        break;
    }
    }
}

void MCUStateMachine::handle_entry_logic_(MCU_STATE new_state, unsigned long curr_time)
{
    switch (new_state)
    {
    case MCU_STATE::STARTUP:
        break;
    case MCU_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
        break;
    case MCU_STATE::TRACTIVE_SYSTEM_ACTIVE:
    {
        drivetrain_->enable_drivetrain_hv(curr_time);
        break;
    }
    case MCU_STATE::ENABLING_INVERTER:
    {
        inverter_->request_enable_inverter();
        hal_println("MCU Sent enable command");
        break;
    }
    case MCU_STATE::WAITING_READY_TO_DRIVE_SOUND:
        // make dashboard sound buzzer
        buzzer_->activate_buzzer(curr_time);

        hal_println("RTDS enabled");
        break;
    case MCU_STATE::READY_TO_DRIVE:
        hal_println("Ready to drive");
        break;
    }
}