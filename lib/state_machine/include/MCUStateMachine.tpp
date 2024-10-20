
#include "MCUStateMachine.h"
template <typename DrivetrainSysType>
void MCUStateMachine<DrivetrainSysType>::tick_state_machine(unsigned long current_millis, const SharedCarState_s &current_car_state)
{
    switch (get_state())
    {
    case CAR_STATE::STARTUP:

        hal_println("in startup state");
        set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
        break;

    case CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
    {
        // if TS is above HV threshold, move to Tractive System Active
        drivetrain_->disable_no_pins();
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, current_millis);
        }
        break;
    }

    case CAR_STATE::TRACTIVE_SYSTEM_ACTIVE:
    {
        if (buzzer_->buzzer_is_on())
        {
            buzzer_->deactivate();
        }
        // TODO migrate to new pedals system
        auto data = pedals_->getPedalsSystemData();
        drivetrain_->disable_no_pins();
        if (!drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
            break;
        }
        if (dashboard_->startButtonPressed() && (data.brakePressed))
        {
            set_state_(CAR_STATE::ENABLING_INVERTERS, current_millis);
            break;
        }
        break;
    }

    case CAR_STATE::ENABLING_INVERTERS:
    {

        if (!drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
            break;
        }
        // If motor controllers have error, even though hv is over threshold
        if (drivetrain_->drivetrain_error_occured())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, current_millis);
        }
        // TODO handle drivetrain init timeout
        if (drivetrain_->handle_inverter_startup(current_millis))
        {
            set_state_(CAR_STATE::WAITING_READY_TO_DRIVE_SOUND, current_millis);
            break;
        }
        break;
    }
    case CAR_STATE::WAITING_READY_TO_DRIVE_SOUND:
    {
        // TODO handle the drivetrain state change back to startup phase 1 and/or move this into
        //      the drivetrain state machine handling

        if (!drivetrain_->hv_over_threshold_on_drivetrain())
        {
            hal_println("drivetrain not over thresh in WRTD?");
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
            break;
        }

        drivetrain_->command_drivetrain_no_torque();

        // if the ready to drive sound has been playing for long enough, move to ready to drive mode
        if (buzzer_->done(current_millis, dashboard_->checkBuzzer()))
        {
            set_state_(CAR_STATE::READY_TO_DRIVE, current_millis);
        }
        break;
    }

    case CAR_STATE::READY_TO_DRIVE:
    {
        auto data = pedals_->getPedalsSystemData();

        if (!drivetrain_->hv_over_threshold_on_drivetrain())
        {
            hal_println("drivetrain not over thresh?");
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
            break;
        }

        if (drivetrain_->drivetrain_error_occured())
        {

            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, current_millis);
            break;
        }

        if (safety_system_->get_software_is_ok() && !data.implausibilityExceededMaxDuration)
        {
            drivetrain_->command_drivetrain(controller_mux_->getDrivetrainCommand(dashboard_->getDialMode(), dashboard_->getTorqueLimitMode(), current_car_state));
        }
        else
        {
            drivetrain_->command_drivetrain_no_torque();
        }

        break;
    }
    }
}

template <typename DrivetrainSysType>
void MCUStateMachine<DrivetrainSysType>::set_state_(CAR_STATE new_state, unsigned long curr_time)
{

    handle_exit_logic_(current_state_, curr_time);

    current_state_ = new_state;

    handle_entry_logic_(new_state, curr_time);
}

template <typename DrivetrainSysType>
void MCUStateMachine<DrivetrainSysType>::handle_exit_logic_(CAR_STATE prev_state, unsigned long curr_time)
{
    switch (get_state())
    {
    case CAR_STATE::STARTUP:
        break;
    case CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
        break;
    case CAR_STATE::TRACTIVE_SYSTEM_ACTIVE:
        break;
    case CAR_STATE::ENABLING_INVERTERS:
        break;
    case CAR_STATE::WAITING_READY_TO_DRIVE_SOUND:
        break;
    case CAR_STATE::READY_TO_DRIVE:
    {
        // deactivate buzzer and reset it to turn on again later
        buzzer_->deactivate();
        break;
    }
    }
}
template <typename DrivetrainSysType>
void MCUStateMachine<DrivetrainSysType>::handle_entry_logic_(CAR_STATE new_state, unsigned long curr_time)
{
    switch (new_state)
    {
    case CAR_STATE::STARTUP:
        break;
    case CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
        break;
    case CAR_STATE::TRACTIVE_SYSTEM_ACTIVE:
        break;

    case CAR_STATE::ENABLING_INVERTERS:
    {
        break;
    }
    case CAR_STATE::WAITING_READY_TO_DRIVE_SOUND:
    {
        // make dashboard sound buzzer
        buzzer_->activate_buzzer(curr_time);
        break;
    }
    case CAR_STATE::READY_TO_DRIVE:
    {
        break;
    }
    }
}
