#include "MCUStateMachine.h"
#include "Logger.h"
void MCUStateMachine::set_state(MCU_STATE new_state)
{
    hal_println("running exit logic")
    handle_exit_logic_(current_state_);

    current_state_ = new_state;

    hal_println("running entry logic")
    handle_entry_logic_(new_state);
}