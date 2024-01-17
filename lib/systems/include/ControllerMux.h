#ifndef CONTROLLERMUX
#define CONTROLLERMUX

#include "PedalsSystem.h"
#include "DashboardInterface.h"
#include "DrivetrainSystem.h"

class ControllerMux
{
    public:
        ControllerMux() {}
        DrivetrainCommand get_drivetrain_input(const PedalsSystemInterface& pedals_data_input, const DashSystemInterface& dash_input);
    private:
};

#endif /* CONTROLLERMUX */
