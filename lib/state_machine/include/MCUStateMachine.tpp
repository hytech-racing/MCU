
#include "MCUStateMachine.h"
template <typename DrivetrainSysType>
void MCUStateMachine<DrivetrainSysType>::tick_state_machine(unsigned long current_millis)
{
    switch (get_state())
    {
    case CAR_STATE::STARTUP:

        hal_println("in startup state");
        set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
        break;

    case CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
    {
        // Serial.println("eror in ts not active:");
        // Serial.println(safety_system_->get_software_is_ok());
        // Serial.println();
        // hal_println("tractive system not active state");

        // auto data = pedals_->getPedalsSystemData();
        // auto mux_test = controller_mux_->getDrivetrainCommand();

        // hal_println("speeds 1 through 4");
        // Serial.println(mux_test.speeds_rpm[0]);
        // Serial.println(mux_test.speeds_rpm[1]);
        // Serial.println(mux_test.speeds_rpm[2]);
        // Serial.println(mux_test.speeds_rpm[3]);

        // hal_println("torqeus");
        // Serial.println(mux_test.torqueSetpoints[0]);
        // Serial.println(mux_test.torqueSetpoints[1]);
        // Serial.println(mux_test.torqueSetpoints[2]);
        // Serial.println(mux_test.torqueSetpoints[3]);
        // Serial.println();
        // Serial.print(data.brakeImplausible);
        // Serial.print(" ");
        // Serial.print(data.accelImplausible);
        // Serial.print(" ");
        // Serial.print(data.brakeAndAccelPressedImplausibility);
        // Serial.print(" ");
        // Serial.print(data.implausibilityExceededMaxDuration);
        // Serial.println();
        // Serial.print(data.accelPercent);
        // Serial.print(" ");
        // Serial.print(data.brakePercent);
        // Serial.print(" ");


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
        // hal_println("in tractive system active state");
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

        // hal_println("in enabling inverters state");
        if (!drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, current_millis);
            break;
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
        // auto test = controller_mux_->getDrivetrainCommand();

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

        if (safety_system_->get_software_is_ok())
        {
            drivetrain_->command_drivetrain(controller_mux_->getDrivetrainCommand());
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
    // hal_println("running exit logic");

    // hal_printf("\n to state: %i\n", new_state);
    handle_exit_logic_(current_state_, curr_time);

    current_state_ = new_state;

    // hal_println("running entry logic");
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
        // hal_println("RTDS enabled");
        break;
    }
    case CAR_STATE::READY_TO_DRIVE:
    {
        // hal_printf("%i\n", curr_time);
        // hal_println("Ready to drive");
        break;
    }
    }
}
