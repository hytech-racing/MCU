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
}

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

struct DashComponentInterface_s
{
    /* READ DATA */
    // enum for dial position read by controller mux
    DialMode_e dial_mode;
    // Buttons struct for better naming
    DashButtons_s button;
    bool ssok; // safety system OK (IMD?) RENAME
    bool shutdown;
    bool buzzer_state;

    /* WRITTEN DATA */
    bool buzzer_cmd;
    //making it an array of ints to support enumerated LEDs as well as
    //gradient/value based LEDs
    LEDColors_e LED[12];
};


class DashboardInterface
{
private:

    DashComponentInterface_s _data;

public:
    Dashboard(){};

    void read(DASHBOARD_STATE_t* msg);
    DASHBOARD_MCU_STATE_t write();

    DialMode_s getDialMode();
    
    bool safetySystemOK();

    bool startButtonPressed();
    bool specialButtonPressed();
    bool torqueButtonPressed();
    bool inverterResetButtonPressed();
    bool launchControlButtonPressed();
    bool torqueLoadingButtonPressed();
    bool nightModeButtonPressed();
    bool torqueVectoringOffButtonPressed();

    void soundBuzzer();

    // LEDs in same order as dash rev. 7 placement

    void setLED(DashLED_e led, LEDColors_e color);
};

#endif /* __DASHBOARDINTERFACE_H__ */
