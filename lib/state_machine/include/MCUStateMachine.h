#ifndef __MCU_STATE_MACHINE__
#define __MCU_STATE_MACHINE__

#include "SysClock.h"
#include "Logger.h"

#include "PedalsSystem.h"
#include "DrivetrainSystem.h"
#include "Buzzer.h"
#include "TorqueControllerMux.h"
#include "SafetySystem.h"
#include "DashboardInterface.h"
#include "AMSInterface.h"

enum class CAR_STATE
{
    STARTUP = 0,
    TRACTIVE_SYSTEM_NOT_ACTIVE = 1,
    TRACTIVE_SYSTEM_ACTIVE = 2,
    ENABLING_INVERTERS = 3,
    WAITING_READY_TO_DRIVE_SOUND = 4,
    READY_TO_DRIVE = 5
};

template <typename DrivetrainSysType>
class MCUStateMachine
{
public:
    MCUStateMachine(BuzzerController *buzzer,
                    DrivetrainSysType *drivetrain,
                    DashboardInterface *dashboard,
                    PedalsSystem *pedals,
                    TCMuxType *mux,
                    SafetySystem *safety_system)
    {
        current_state_ = CAR_STATE::STARTUP;
        buzzer_ = buzzer;
        drivetrain_ = drivetrain;
        dashboard_ = dashboard;
        pedals_ = pedals;
        controller_mux_ = mux;
        safety_system_ = safety_system;
    }

    // TODO update this to just use the car_state struct instead of having to pass in cm
    /// @brief function to tick the state machine. 
    /// @param cm current millis from systick
    /// @param current_car_state current state of the car (not to be confused with the CAR_STATE enum which is the state machine state)
    void tick_state_machine(unsigned long cm, const SharedCarState_s &current_car_state);

    CAR_STATE get_state() { return current_state_; }
    bool car_in_ready_to_drive() { return current_state_ == CAR_STATE::READY_TO_DRIVE; };

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
    // IMDInterface *imd_;
    SafetySystem *safety_system_;
    TCMuxType *controller_mux_;
    // RateLimitedLogger logger_;
};
#include "MCUStateMachine.tpp"
#endif /* MCUSTATEMACHINE */
