#ifndef CONTROLLERMUX
#define CONTROLLERMUX

#include "Pedals.h"
#include "DashboardDriver.h"
#include "Drivetrain.h"

class ControllerMux
{
    public:
        ControllerMux() {}
        DrivetrainCommand get_drivetrain_input(const PedalsComponentInterface& pedals_data_input, const DashComponentInterface& dash_input);
    private:
};

#endif /* CONTROLLERMUX */
