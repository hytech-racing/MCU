#ifndef __DASHBOARDINTERFACE_H__
#define __DASHBOARDINTERFACE_H__

#include "MessageQueueDefine.h"
#include "FlexCAN_T4.h"
#include "ht_can.h"

enum DialMode_e
{
    MODE_2,
    MODE_3,
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
    LEDColors_e LED[13];
};


class DashboardInterface
{
private:

    DashComponentInterface_s _data;
    CANBufferType *msg_queue_;

public:

    Dashboard(CANBufferType *msg_output_queue)
    {
        msg_queue_ = msg_output_queue;
    };

    void read(const CAN_message_t &can_msg);
    void write();

    DialMode_e getDialMode();
    
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

    // LEDs in same order as dash rev. 8 placement

    void setLED(DashLED_e led, LEDColors_e color);
};

#endif /* __DASHBOARDINTERFACE_H__ */
