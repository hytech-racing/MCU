#ifndef DASHBOARDINTERFACE
#define DASHBOARDINTERFACE
/* Enum for the modes on the dial, corresponds directly to dial index pos. */
enum DialMode_e
{
    MODE_1,
    MODE_2,
    ACCEL_LAUNCH_CONTROL,
    SKIDPAD,
    AUTOCROSS,
    ENDURANCE,
};

/* Enum for defined LED colors. ON will be LED's default color on dashboard*/
enum LEDColors_e
{
    OFF,
    ON,
    YELLOW,
    RED,
};

/* Enum to index the LED array. Each LED in the CAN message is represented in no particular order. */
enum DashLED_e
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
    bool start_button_status_;
    bool startButtonPressed() { return  start_button_status_; };
};

#endif /* DASHBOARDINTERFACE */
