#include "SteeringSensor.h"

#include "Pedals.h"
#include "Steering.h"
enum class MCU_STATE
{
    STARTUP                      = 0,
    TRACTIVE_SYSTEM_NOT_ACTIVE   = 1,
    TRACTIVE_SYSTEM_ACTIVE       = 2,
    ENABLING_INVERTER            = 3,
    WAITING_READY_TO_DRIVE_SOUND = 4,
    READY_TO_DRIVE               = 5
};

class MCUStateMachine {
    public:
        MCUStateMachine() {

        }
        
        /// @brief our components can use this time to tell when to do things. We can set this ourselves for testing purposes instead of using metro timers
        /// @param current_millis the current millis() call
        void tick_state_machine(unsigned long current_millis);
        void get_state();
    private:
        void set_state_(MCU_STATE new_state);

        /// @brief the function run upon the entry of the car into a new state
        /// @param new_state the state in which we are entering
        void handle_entry_logic_(MCU_STATE new_state);
        
        /// @brief function run upon the exit of a state
        /// @param prev_state the state in which we are leaving
        void handle_exit_logic_(MCU_STATE prev_state);
        MCU_STATE current_state_;
        
        

};
