#ifndef DASHBOARDINTERFACE
#define DASHBOARDINTERFACE

#include "SharedDataTypes.h"
/*
    Enum for the car's torque limits
    MOVE ME! - ideally into a TorqueControllerDefs.h file
    to prevent circular dependencies
*/




/* Enum for defined LED colors. ON will be LED's default color on dashboard*/
enum class LEDColors_e
{
    OFF,
    ON,
    YELLOW,
    RED,
};

/* Enum to index the LED array. Each LED in the CAN message is represented in no particular order. */
enum class DashLED_e
{
    BOTS_LED,
    LAUNCH_CONTROL_LED,
    MODE_LED,
    MECH_BRAKE_LED,
    COCKPIT_BRB_LED,
    INERTIA_LED,
    GLV_LED,
    CRIT_CHARGE_LED,
    START_LED,
    MC_ERROR_LED,
    IMD_LED,
    AMS_LED,
};

class DashboardInterface
{
private:
public:
    bool buzzer = false;
    bool start_button_status_;
    bool startButtonPressed() { return  start_button_status_; };
    bool checkBuzzer(){ return buzzer; };
};

#endif /* DASHBOARDINTERFACE */
