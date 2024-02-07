
#include "MCUStateMachine.h"
template <typename DrivetrainSysType>
void MCUStateMachine<DrivetrainSysType>::tick_state_machine(unsigned long current_millis)
{
    switch (get_state())
    {
    case CAR_STATE::STARTUP:
        set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
        break;

    case CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
    {
        // if TS is above HV threshold, move to Tractive System Active
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, current_millis);
        }
        break;
    }

    case CAR_STATE::TRACTIVE_SYSTEM_ACTIVE:
    {
        // TODO migrate to new pedals system
        auto data = pedals_->getPedalsSystemData();
        if (!drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
            break;
        }
        if (dashboard_->startButtonPressed() && (data.pedalsCommand == PedalsCommanded_e::PEDALS_BRAKE_PRESSED))
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
        // TODO handle drivetrain init timeout
        if (drivetrain_->handle_inverter_startup())
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

        // if the ready to drive sound has been playing for long enough, move to ready to drive mode
        if (buzzer_->done(current_millis))
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

        // TODO:integrate the ams and the IMD
        if (
            // bms_->ok_high() &&
            // imd_->ok_high() &&
            !data.implausibilityExceededMaxDuration)
        {
            drivetrain_->command_drivetrain(controller_mux_->getDrivetrainCommand());
        }
        else
        {
            drivetrain_->command_drivetrain_no_torque();
            hal_println("not calculating torque");
            // hal_printf("no brake implausibility: %d\n", pedals_data.brakeImplausible);
            // hal_printf("no accel implausibility: %d\n", pedals_data.accelImplausible);
            // hal_printf("bms heartbeat: %d\n", bms_->heartbeat_check(current_millis));
            // hal_printf("get bms ok high: %d\n", bms_->ok_high());
            // hal_printf("get imd ok high: %d\n", imd_->ok_high());
        }

        break;
    }
    }
}

template <typename DrivetrainSysType>
void MCUStateMachine<DrivetrainSysType>::set_state_(CAR_STATE new_state, unsigned long curr_time)
{
    hal_println("running exit logic");

    hal_printf("\n to state: %i\n", new_state);
    handle_exit_logic_(current_state_, curr_time);

    current_state_ = new_state;

    hal_println("running entry logic");
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
        drivetrain_->disable();
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
        hal_println("RTDS enabled");
        break;
    }
    case CAR_STATE::READY_TO_DRIVE:
    {
        hal_printf("%i\n", curr_time);
        hal_println("Ready to drive");
        break;
    }
    }
}
