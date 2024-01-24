#ifndef __DASHBOARDINTERFACE_H__
#define __DASHBOARDINTERFACE_H__

#include "Dashboard_status.h"

enum DialMode_e
{
    MODE_1,
    MODE_2,
    ACCEL_LAUNCH_CONTROL,
    SKIDPAD,
    AUTOCROSS,
    ENDURANCE,
};

enum LEDColors_e
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
    DialMode_e dial_mode;
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

    DashComponentInterface data;

public:
    Dashboard(){};

    void read(const Dashboard_status &msg);

    DialMode_e getDialMode();

    bool startButtonPressed();
    bool specialButtonPressed();
    bool torqueButtonPressed();
    bool inverterResetButtonPressed();
    bool launchControlButtonPressed();
    bool torqueLoadingButtonPressed();
    bool nightModeButtonPressed();
    bool torqueVectoringOffButtonPressed();

    bool safetySystemOK();


    void soundBuzzer(bool state);

    void amsLED(LEDColors_e color);
    void imdLED(LEDColors_e color);
    void modeLED(LEDColors_e color);
    void mcErrorLED(LEDColors_e color);
    void startLED(LEDColors_e color);
    void InertiaSwitchLED(LEDColors_e color);
    void mechanicalBrakeLED(LEDColors_e color);
    void generalPurposeLED(LEDColors_e color);
    void botsLED(LEDColors_e color);
    void cockpitBrbLED(LEDColors_e color);
    void critChargeLED(LEDColors_e color);
    void glvLED(LEDColors_e color);
    void launchControlLED(LEDColors_e color);
};

#endif /* __DASHBOARDINTERFACE_H__ */
