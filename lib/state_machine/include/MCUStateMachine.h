#ifndef __MCU_STATE_MACHINE__
#define __MCU_STATE_MACHINE__

#include "SysClock.h"
#include "Logger.h"

#include "PedalsSystem.h"
#include "DrivetrainSystem.h"
#include "Buzzer.h"
#include "TorqueControllerMux.h"

#include "DashboardInterface.h"
#include "AMSInterface.h"
// #include "IMDInterface.h"

enum class CAR_STATE
{
    STARTUP = 0,
    TRACTIVE_SYSTEM_NOT_ACTIVE = 1,
    TRACTIVE_SYSTEM_ACTIVE = 2,
    ENABLING_INVERTERS = 3,
    WAITING_DRIVETRAIN_QUIT_DC_ON = 4,
    WAITING_DRIVETRAIN_ENABLED = 5,
    WAITING_READY_TO_DRIVE_SOUND = 6,
    READY_TO_DRIVE = 7
};

template <typename DrivetrainSysType>
class MCUStateMachine
{
public:
    MCUStateMachine(BuzzerController *buzzer, DrivetrainSysType *drivetrain, DashboardInterface *dashboard, PedalsSystem *pedals)
    {
        buzzer_ = buzzer;
        drivetrain_ = drivetrain;
        dashboard_ = dashboard;
        pedals_ = pedals;
    }

    /// @brief our components can use this time to tell when to do things. We can set this ourselves for testing purposes instead of using metro timers
    /// @param current_millis the current millis() call
    void tick_state_machine(const SysTick_s &tick);
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
    DrivetrainSysType *drivetrain_;
    PedalsSystem *pedals_;

    /// @brief drivers within state machine
    DashboardInterface *dashboard_;
    AMSInterface *bms_;
    IMDInterface *imd_;

    TorqueControllerMux* controller_mux_;

};
#include "MCUStateMachine.tpp"
#endif /* MCUSTATEMACHINE */
