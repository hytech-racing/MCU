#include "MCUStateMachine.h"
#include "PedalsSystem.h"
#include "SteeringSystem.h"
#include "DashboardInterface.h"
#include "AnalogSensorsInterface.h"
#include "TorqueControllerMux.h"

void MCUStateMachine::tick_state_machine(const SysTick_s &tick)
{
    switch (get_state())
    {
    case CAR_STATE::STARTUP:
        break;

    case CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
    {
        // if TS is above HV threshold, move to Tractive System Active
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, tick.millis);
        }
        break;
    }

    case CAR_STATE::TRACTIVE_SYSTEM_ACTIVE:
    {
        if (!drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE, tick.millis);
            break;
        }
        if (dashboard_->startButtonPressed() && pedals_->mech_brake_active())
        {
            set_state_(CAR_STATE::ENABLING_INVERTER, tick.millis);
            break;
        }
        break;
    }

    case CAR_STATE::ENABLING_INVERTER:
    {
        // TODO handle the drivetrain state change back to startup phase 1 and/or move this into
        //      the drivetrain state machine handling
        if (!drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, tick.millis);
            break;
        }

        if (drivetrain_->drivetrain_ready())
        {
            // entry logic: drivetrain_->enable_drivetrain_hv(tick.millis);
            set_state_(CAR_STATE::WAITING_DRIVETRAIN_QUIT_DC_ON, tick.millis);
            break;
        }
        break;
    }

    case CAR_STATE::WAITING_DRIVETRAIN_QUIT_DC_ON: {
        if (drivetrain_->check_drivetrain_quit_dc_on() && !drivetrain_->inverter_init_timeout(tick.millis)) {
            set_state_(CAR_STATE::WAITING_DRIVETRAIN_ENABLED, tick.millis);
            break;
        } else {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, tick.millis);
            break;
        } break;
    } case CAR_STATE::WAITING_DRIVETRAIN_ENABLED: {
        if (drivetrain_->drivetrain_enabled() && !drivetrain_->inverter_init_timeout(tick.millis)) {
            set_state_(CAR_STATE::WAITING_READY_TO_DRIVE_SOUND, tick.millis);
        } else {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, tick.millis);
            break;
        }

    } case CAR_STATE::WAITING_READY_TO_DRIVE_SOUND:
    {
        // TODO handle the drivetrain state change back to startup phase 1 and/or move this into
        //      the drivetrain state machine handling
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, tick.millis);
            break;
        }

        // if the ready to drive sound has been playing for long enough, move to ready to drive mode
        if (buzzer_->done(tick.millis))
        {
            set_state_(CAR_STATE::READY_TO_DRIVE, tick.millis);
        }
        break;
    }

    case CAR_STATE::READY_TO_DRIVE:
    {
        // TODO handle the drivetrain state change back to startup phase 1 and/or move this into
        //      the drivetrain state machine handling
        if (drivetrain_->hv_over_threshold_on_drivetrain())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, tick.millis);
            break;
        }

        if (drivetrain_->drivetrain_error_occured())
        {
            set_state_(CAR_STATE::TRACTIVE_SYSTEM_ACTIVE, tick.millis);
        }

        PedalsSystemOutput_s pedalsData;
        Dashboard_status dash_data;
        auto pedals_data = pedals_->evaluate_pedals(data, tick.millis);
        auto dashboard_data = dashboard_->evaluate_dashboard(dash_data);

        // TODO: below in the scope of this function
        if (
            bms_->ok_high() &&
            imd_->ok_high() &&
            !pedals_->max_duration_of_implausibility_exceeded(tick.millis))
        {
            // drivetrain_->command_drivetrain(controller_mux_->get_drivetrain_input(pedals_data, dashboard_data));
        }
        else
        {
            drivetrain_->command_drivetrain_no_torque();
            hal_println("not calculating torque");
            hal_printf("no brake implausibility: %d\n", pedals_data.brakeImplausible);
            hal_printf("no accel implausibility: %d\n", pedals_data.accelImplausible);
            hal_printf("bms heartbeat: %d\n", bms_->heartbeat_check(tick.millis));
            hal_printf("get bms ok high: %d\n", bms_->ok_high());
            hal_printf("get imd ok high: %d\n", imd_->ok_high());
        }

        break;
    }
    }
}

void MCUStateMachine::set_state_(CAR_STATE new_state, unsigned long curr_time)
{
    hal_println("running exit logic");
    handle_exit_logic_(current_state_, curr_time);

    current_state_ = new_state;

    hal_println("running entry logic");
    handle_entry_logic_(new_state, curr_time);
}

void MCUStateMachine::handle_exit_logic_(CAR_STATE prev_state, unsigned long curr_time)
{
    switch (get_state())
    {
    case CAR_STATE::STARTUP:
        break;
    case CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
        break;
    case CAR_STATE::TRACTIVE_SYSTEM_ACTIVE:
        break;
    case CAR_STATE::ENABLING_INVERTER:
        break;
    case CAR_STATE::WAITING_DRIVETRAIN_QUIT_DC_ON:
        break;
    case CAR_STATE::WAITING_DRIVETRAIN_ENABLED:
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

void MCUStateMachine::handle_entry_logic_(CAR_STATE new_state, unsigned long curr_time)
{
    switch (new_state)
    {
    case CAR_STATE::STARTUP:
        break;
    case CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE:
        break;
    case CAR_STATE::TRACTIVE_SYSTEM_ACTIVE:
        break;

    case CAR_STATE::ENABLING_INVERTER:
    {
        break;
    }
    case CAR_STATE::WAITING_DRIVETRAIN_QUIT_DC_ON:
    {
        drivetrain_->enable_drivetrain_hv(curr_time);
        break;
    }
    case CAR_STATE::WAITING_DRIVETRAIN_ENABLED:
    {
        drivetrain_->request_enable();
        drivetrain_->command_drivetrain_no_torque();
        break;
    }
    case CAR_STATE::WAITING_READY_TO_DRIVE_SOUND:
        // make dashboard sound buzzer
        buzzer_->activate_buzzer(curr_time);

        hal_println("RTDS enabled");
        break;
    case CAR_STATE::READY_TO_DRIVE:
        hal_println("Ready to drive");
        break;
    }
}