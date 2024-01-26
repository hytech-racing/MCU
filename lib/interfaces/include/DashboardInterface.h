#ifndef DASHBOARDINTERFACE
#define DASHBOARDINTERFACE

#include "Dashboard_status.h"

enum DialMode_s
{
    MODE_1,
    MODE_2,
    ACCEL_LAUNCH_CONTROL,
    SKIDPAD,
    AUTOCROSS,
    ENDURANCE,
};

enum LEDColors_s
{
    OFF,
    ON,
    YELLOW,
    RED,
};

struct DashButtons_s
{
    bool start;
    bool mark;
    bool mode; // torque mode
    bool mc_cycle; // clears encoder error codes
    bool launch_ctrl;
    bool torque_mode; // torque loading
    bool led_dimmer;
};

struct DashLEDs_s
{
    uint8_t ams;
    uint8_t imd;
    uint8_t mode;
    uint8_t mc_error;
    uint8_t start;
    uint8_t inertia;
    uint8_t mech_brake;
    uint8_t gen_purp;
    uint8_t bots;
    uint8_t cockpit_brb;
    uint8_t crit_charge;
    uint8_t glv;
    uint8_t launch_control;
};

struct DashComponentInterface
{
    /* READ DATA */
    // enum for dial position read by controller mux
    DialMode_s dial_mode;
    // Buttons struct for better naming
    DashButtons_s button;
    bool ssok; // safety system OK (IMD?) RENAME
    bool shutdown;

    /* WRITTEN DATA */
    bool buzzer;
    DashLEDs_s LED;
};


class DashboardInterface
{
private:

    

public:
    DashboardInterface(){}

    void read(const Dashboard_status &msg);

    DialMode_s getDialMode();
    
    bool safetySystemOK();

    bool start_button_pressed();
    bool specialButtonPressed();
    bool torqueButtonPressed();
    bool inverterResetButtonPressed();
    bool launchControlButtonPressed();
    bool torqueLoadingButtonPressed();
    bool nightModeButtonPressed();
    bool torqueVectoringOffButtonPressed();

    void soundBuzzer();

    // LEDs in same order as dash rev. 7 placement
    void botsLED(LEDColors_s color);
    void launchControlLED(LEDColors_s color);
    void modeLED(LEDColors_s color);
    void mechanicalBrakeLED(LEDColors_s color);
    void cockpitBrbLED(LEDColors_s color);
    void InertiaSwitchLED(LEDColors_s color);
    void glvLED(LEDColors_s color);
    void critChargeLED(LEDColors_s color);
    void startLED(LEDColors_s color);
    void mcErrorLED(LEDColors_s color);
    void imdLED(LEDColors_s color);
    void amsLED(LEDColors_s color);
};

#endif /* DASHBOARDINTERFACE */
