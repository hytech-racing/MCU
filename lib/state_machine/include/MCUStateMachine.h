#ifndef __MCU_STATE_MACHINE__
#define __MCU_STATE_MACHINE__

#include "Logger.h"
#include "InverterSystem.h"
#include "PedalsSystem.h"
#include "DrivetrainSystem.h"
#include "Buzzer.h"


#include "DashboardInterface.h"
#include "AMSInterface.h"
#include "IMDInterface.h"
#include "ControllerMux.h"
enum class CAR_STATE
{
    STARTUP = 0,
    TRACTIVE_SYSTEM_NOT_ACTIVE = 1,
    TRACTIVE_SYSTEM_ACTIVE = 2,
    ENABLING_INVERTER = 3,
    WAITING_READY_TO_DRIVE_SOUND = 4,
    READY_TO_DRIVE = 5
};

class MCUStateMachine
{
public:
    MCUStateMachine(BuzzerController *buzzer, DrivetrainSystem *drivetrain, DashboardInterface *dashboard)
    {
        buzzer_ = buzzer;
        drivetrain_ = drivetrain;
        dashboard_ = dashboard;
    }

    /// @brief our components can use this time to tell when to do things. We can set this ourselves for testing purposes instead of using metro timers
    /// @param current_millis the current millis() call
    void tick_state_machine(unsigned long current_millis);
    CAR_STATE get_state() { return current_state_; }

private:
    void set_state_(CAR_STATE new_state, unsigned long curr_time);

    /// @brief the function run upon the entry of the car into a new state
    /// @param new_state the state in which we are entering
    void handle_entry_logic_(CAR_STATE new_state, unsigned long curr_time);

    /// @brief function run upon the exit of a state
    /// @param prev_state the state in which we are leaving
    void handle_exit_logic_(CAR_STATE prev_state, unsigned long curr_time);
    CAR_STATE current_state_;

    /// @brief components within state machine
    BuzzerController *buzzer_;
    DrivetrainSystem *drivetrain_;
    PedalsSystem *pedals_;

    /// @brief drivers within state machine
    DashboardInterface *dashboard_;
    AMSInterface *bms_;
    IMDInterface *imd_;

    ControllerMux * controller_mux_;

};

#endif /* MCUSTATEMACHINE */
