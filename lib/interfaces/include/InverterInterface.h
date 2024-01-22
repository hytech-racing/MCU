#ifndef INVERTERINTERFACE
#define INVERTERINTERFACE

#include <stdint.h>
#include <tuple>
#include <variant>
#include "MC_setpoints_command.h"
#include "MC_energy.h"
#include "MC_status.h"
#include "MC_temps.h"
#include "FlexCAN_T4.h"
#include "CircularBuffer.h"

struct InverterCommand
{
    bool enable_hv;
    bool inverter_enable;
    bool driver_enable;
    int16_t speed_setpoint;
    int16_t positive_torque_limit;
    int16_t negative_torque_limit;
};
template <typename message_queue>
class InverterInterface
{
    public:
        InverterInterface(message_queue* msg_queue){
            
        }
        
        void request_enable_inverter();
        void command_no_torque();
        
        void handle_command(const InverterCommand& command);

        bool inverter_system_ready();
        bool dc_quit_on();
        bool quit_inverter_on();
        void request_enable_hv();

        /// @brief function to get the latest message to output
        /// @return tuple that says whether or not the message needs to be sent and the message itself

    private: 
        message_queue * msg_queue;
};

// #include "InverterInterface.tpp"
#endif /* INVERTERINTERFACE */
