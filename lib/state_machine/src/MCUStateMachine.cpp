#include "MCUStateMachine.h"

void MCUStateMachine::tick_state_machine(unsigned long current_millis)
{
    switch (mcu_status.get_state())
    {
    case MCU_STATE::STARTUP:
        break;

    case MCU_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
    {
        // if TS is above HV threshold, move to Tractive System Active
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {

            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
        }
        break;
    }

    case MCU_STATE::TRACTIVE_SYSTEM_ACTIVE:
    {
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
    }

    case MCU_STATE::ENABLING_INVERTER:
    {
        // TODO handle the drivetrain state change back to startup phase 1 and/or move this into
        //      the drivetrain state machine handling
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
            break;
        }
        // inverter enabling timed out
        if (drivetrain_->inverter_enable_timeout(current_millis))
        {
            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
        }

        // TODO may wanna move this out of here
        auto drivetrain_state = drivetrain_->handle_state_machine();
        if (drivetrain_state == DRIVETRAIN_STATE::RTD)
        {
            set_state(MCU_STATE::WAITING_READY_TO_DRIVE_SOUND);
        }
        break;
    }

    case MCU_STATE::WAITING_READY_TO_DRIVE_SOUND:
    {
        // TODO handle the drivetrain state change back to startup phase 1 and/or move this into
        //      the drivetrain state machine handling
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
            break;
        }

        // if the ready to drive sound has been playing for long enough, move to ready to drive mode
        if (buzzer_->done())
        {

            set_state(MCU_STATE::READY_TO_DRIVE);
        }
        break;
    }

    case MCU_STATE::READY_TO_DRIVE:
    {
        // TODO handle the drivetrain state change back to startup phase 1 and/or move this into
        //      the drivetrain state machine handling
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
            break;
        }

        if (drivetrain_->drivetrain_error_occured())
        {
            drivetrain_->disable();
            set_state(MCU_STATE::TRACTIVE_SYSTEM_ACTIVE);
        }

        auto pedals_data = pedals_->evaluate_pedals();
        auto dashboard_data = dashboard_->evaluate_dashboard();

        // TODO: below in the scope of this function
        if (
            bms_->ok_high() &&
            imd_->ok_high())
        {

            // TODO make controller mux between torque controllers and handle passing of data
            //      into controller mux from pedals, steering, etc.
            // set_inverter_torques();
            auto controller_mux_->get_drivetrain_input(pedals_data, dashboard_data);
        }
        else
        {
            drivetrain_->command_drivetrain_no_torque();
            logger_->hal_println("not calculating torque");
            logger_->hal_printf("no brake implausibility: %d\n", pedals_data.brakeImplausible);
            logger_->hal_printf("no accel implausibility: %d\n", pedals_data.accelImplausible);
            logger_->hal_printf("bms heartbeat: %d\n", bms_->heartbeat_check(current_millis));
            logger_->hal_printf("get bms ok high: %d\n", bms_->ok_high());
            logger_->hal_printf("get imd ok high: %d\n", imd_->ok_high());
        }

        break;
    }
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