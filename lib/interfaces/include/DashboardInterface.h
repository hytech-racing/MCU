#ifndef __DASHBOARDINTERFACE_H__
#define __DASHBOARDINTERFACE_H__

#include "MessageQueueDefine.h"
#include "FlexCAN_T4.h"
#include "hytech.h"
#include "MCUInterface.h"
#include "InverterInterface.h"
#include "SharedDataTypes.h"



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
    START_LED, /// from state machine. When READY_TO_DRIVE, set START_LED to true. See what else uses READY_TO_DRIVE so that you can update START_LED.
    MC_ERROR_LED, /// from DrivetrainSystem.cpp, get drivetrain_error_occurred()
    IMD_LED,
    AMS_LED,
};

/* Struct holding the state of Dashboard buttons */
struct DashButtons_s
{
    bool start;
    bool mark;
    bool mode; // torque mode
    bool mc_cycle; // clears encoder error codes
    bool launch_ctrl;
    bool torque_mode; // torque loading
    bool led_dimmer;
    bool left_shifter;
    bool right_shifter;
};


/* Struct holding all data for the DashboardInterface (inputs and outputs) */
struct DashComponentInterface_s
{
    /* READ DATA */
    // enum for dial position read by controller mux
    ControllerMode_e dial_mode;
    ControllerMode_e cur_dial_mode;
    TorqueLimit_e torque_limit_mode;
    // Buttons struct for better naming
    DashButtons_s button;
    bool ssok; // safety system OK (IMD?) RENAME
    bool shutdown;
    bool buzzer_state;

    /* WRITTEN DATA */
    bool buzzer_cmd;
    //making it an array of ints to support enumerated LEDs as well as
    //gradient/value based LEDs
    uint8_t LED[12] = {};
};

/*
    The DashboardInterface is an interface that handles all data to and from the dashboard.
    Through a set of setters and getters (not explicitly named set/get) the state machine,
    other interfaces, and systems can update the information on the dashboard.
    Currently this is written to be a 1 to 1 representation of the current state of the dashboard,
    almost no display logic for the below basic components is handled by the dash.
*/
class DashboardInterface
{
private:
    /* Pointer to the circular buffer to write new messages */
    CANBufferType *msg_queue_;
    /* The instantiated data struct used to access data by member functions */
    DashComponentInterface_s _data;
    bool prev_button_pressed_state_;
    void update_torque_mode_(bool button_pressed);

public:
    /*!
        Constructor for new DashboardInterface, All that it is inited with
        is the pointer to the telem circular buffer that is used to write new messages

        @param msg_output_queue Pointer to the telem CAN circular buffer
    */
    DashboardInterface(CANBufferType *msg_output_queue)
    {
        _data.torque_limit_mode = TorqueLimit_e::TCMUX_FULL_TORQUE;
        prev_button_pressed_state_ = false;
        msg_queue_ = msg_output_queue;
    };

    /*!
        read function will take in a reference to a new CAN message, unpack it,
        and will store all of the information into the DashComponentInterface for later access
        @param can_msg is the reference to a new CAN message CAN_message_t
    */
    void read(const CAN_message_t &can_msg);

    /* write function will Pack a message based on the current data in the interface and push it to the tx buffer */
    CAN_message_t write();

    /*
        Tick DashboardInterface at 10hz to gather data and send CAN message
    */
    void tick10(MCUInterface* mcu,
                int car_state, 
                bool buzzer, 
                bool drivetrain_error, 
                TorqueLimit_e torque,
                float min_cell_voltage,
                AnalogConversion_s glv_voltage,
                int launch_state,
                ControllerMode_e dial_mode);

    /*!
        getter for the dashboard's current dial position (drive profile)
        @return returns a ControllerMode_e enum with the current dial position
    */
    ControllerMode_e getDialMode();
    TorqueLimit_e getTorqueLimitMode();
    /* gets whether the safety system is ok (wtf is a safety system - rename this)*/
    bool safetySystemOK();

    /* getter for the start button */
    bool startButtonPressed();
    /* getter for the mark button */
    bool specialButtonPressed();
    /* getter for the torque button (does not currently exist on dash ) */
    bool torqueModeButtonPressed();
    /* getter for the inverter reset button (clears error codes ) */
    bool inverterResetButtonPressed();
    /* getter for the launch control button */
    bool launchControlButtonPressed();
    /* getter for the torque mode/level button */
    bool torqueLoadingButtonPressed();
    /* getter for the dimmer button (this logic handled on dash ) */
    bool nightModeButtonPressed();
    bool leftShifterButtonPressed();
    bool rightShifterButtonPressed();
    /* getter for the current shutdown threshold on the dashboard*/
    bool shutdownHAboveThreshold();
    /* setter for the buzzer */
    void soundBuzzer(bool s);
    /* getter for the buzzer */
    bool checkBuzzer();

    // LEDs in same order as dash rev. 7 placement

    /*!
        setter for the dash LEDs 
        @param led DashLED_e enum that corresponds to the LED's value in the LED array
        @param color LEDColors_e enum that corresponds to the color/state of the set LED
    */
    void setLED(DashLED_e led, LEDColors_e color);
};

#endif /* __DASHBOARDINTERFACE_H__ */
