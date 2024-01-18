#ifndef INVERTERINTERFACE
#define INVERTERINTERFACE

#include <stdint.h>

#include "MC_setpoints_command.h"
#include "MC_energy.h"
#include "MC_status.h"
#include "MC_temps.h"

struct InverterCommand
{
    bool enable_hv;
    bool inverter_enable;
    bool driver_enable;
    int16_t speed_setpoint;
    int16_t positive_torque_limit;
    int16_t negative_torque_limit;
};

class InverterInterface
{
    public:
        InverterInterface(){

        }
        
        void handle_command(const InverterCommand& command);
        

};

#endif /* INVERTERINTERFACE */
