#ifndef __DASHBOARDINTERFACE_H__
#define __DASHBOARDINTERFACE_H__

/* Library Includes */
#include "FlexCAN_T4.h"
#include "hytech.h"

/* Interface Includes */
#include "MCUInterface.h"
#include "InverterInterface.h"

/* System Includes */
#include "MessageQueueDefine.h"
#include "TorqueControllers.h"

/**
 * Enum for the car's torque limits.
 * MOVE ME! - ideally into a TorqueControllerDefs.h file
 * to prevent circular dependencies
 */
enum class TorqueLimit_e
{
    TCMUX_LOW_TORQUE = 0,
    TCMUX_MID_TORQUE = 1,
    TCMUX_FULL_TORQUE = 2,
    TCMUX_NUM_TORQUE_LIMITS = 3,
};

/**
 * Enum for the modes on the dial, corresponds directly to dial index pos.
 */
enum class DialMode_e
{   
    /* No torque vectoring */
    MODE_0,
    /* Normal force torque vectoring */
    MODE_1,
    /* PID torque vectoring */
    MODE_2,
    /* Launch Ctrl */
    MODE_3,
    MODE_4,
    MODE_5,
};

/**
 * Enum for defined LED colors. ON will be LED's default color on dashboard
 */
enum class LEDColors_e
{
    OFF,
    ON,
    YELLOW,
    RED,
};

/**
 * Enum to index the LED array. Each LED in the CAN message is represented in
 * no particular order.
 */
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

/**
 * Struct holding the state of Dashboard buttons
 */
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

/**
 * Struct holding all data for the DashboardInterface (inputs and outputs)
 */
struct DashComponentInterface_s
{
    /* READ DATA */
    DialMode_e dial_mode;
    DialMode_e cur_dial_mode;
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

/**
 * The DashboardInterface is an interface that handles all data to and from the dashboard.
 * Through a set of setters and getters (not explicitly named set/get) the state machine,
 * other interfaces, and systems can update the information on the dashboard.
 * Currently this is written to be a 1 to 1 representation of the current state of the dashboard,
 * almost no display logic for the below basic components is handled by the dash.
 */
class DashboardInterface
{
private:
    /**
     * Pointer to the circular buffer to write new messages.
     */
    CANBufferType *msg_queue_;

    /**
     * The instantiated data struct used to access data by member function
     */
    DashComponentInterface_s data_;

public:
    /**
     * Constructor for new DashboardInterface. The Dashboard is only initialized with
     * a the pointer to the telem CAN buffer to write new messages.
     * 
     * @param msg_output_queue Pointer to the telem CAN circular buffer
     */
    DashboardInterface(CANBufferType *msg_output_queue)
    {
        msg_queue_ = msg_output_queue;
    };

    /**
     * This read() function takes in a reference to a new CAN message, unpack it and
     * stores all of the information into the DashComponentInterface for later access.
     * 
     * @param can_msg is the reference to a new CAN message CAN_message_t
     */
    void read(const CAN_message_t &can_msg);

    /**
     * Write function packs a message based on the current data in the interface and
     * pushes it to the TX buffer.
     * 
     * @return The CAN message that the write() function just pushed to the buffer.
     */
    CAN_message_t write();

    /**
     * Tick DashboardInterface at 10hz to gather data and send a new CAN message.
     */
    void tick(MCUInterface* mcu,
                int car_state, 
                bool buzzer, 
                bool drivetrain_error, 
                TorqueLimit_e torque,
                float min_cell_voltage,
                AnalogConversion_s glv_voltage,
                int launch_state,
                DialMode_e dial_mode);

    /**
     * Getter for the dashboard's current dial position (drive profile).
     * @return returns a DialMode_e enum with the current dial position.
     */
    DialMode_e getDialMode();
    
    /**
     * Returns whether the safety system is OK.
     * Note: I don't think this is currently used, as it is never set in Dashboard code.
     */
    bool safetySystemOK();

    /**
     * Getter for the start button.
     * @return True if the button is currently pressed, false otherwise.
     */
    bool startButtonPressed();

    /**
     * Getter for the mark button.
     * @return True if the button is currently pressed, false otherwise.
     */
    bool specialButtonPressed();

    /**
     * Getter for the torque button.
     * @return True if the button is currently pressed, false otherwise.
     */
    bool torqueModeButtonPressed();

    /**
     * Getter for the inverter reset button (clears error codes).
     * @return True if the button is currently pressed, false otherwise.
     */
    bool inverterResetButtonPressed();

    /**
     * Getter for the launch control button.
     * Note: I don't think this is currently used, as it is never set in Dashboard code.
     * @return True if the button is currently pressed, false otherwise.
     */
    bool launchControlButtonPressed();

    /**
     * Getter for the torque mode/level button.
     * @return True if the button is currently pressed, false otherwise.
     */
    bool torqueLoadingButtonPressed();

    /**
     * Getter for the dimmer button (this logic handled on dash).
     * @return True if the button is currently pressed, false otherwise.
     */
    bool nightModeButtonPressed();

    /**
     * Getter for the left paddle shifter.
     * @return True if the button is currently pressed, false otherwise.
     */
    bool leftShifterButtonPressed();

    /**
     * Getter for the right paddle shifter.
     * @return True if the button is currently pressed, false otherwise.
     */
    bool rightShifterButtonPressed();

    /**
     * Getter for the current shutdown threshold on the dashboard.
     * Note: I don't think this is currently used, as it is never set in Dashboard code.
     * that sets this bit.
     */
    bool shutdownHAboveThreshold();

    /**
     * Setter for the buzzer. The Dashboard itself handles the timer code, so even if
     * the soundBuzzer(true) function is only called for one CAN frame, the Dashboard
     * will still ensure that the buzzer sounds for the full duration.
     * 
     * @param s True to start the buzzer, false otherwise.
     */
    void soundBuzzer(bool s);

    /**
     * Getter for the current buzzer state. Notably, even if soundBuzzer(false) is called,
     * the Dashboard ensures that the buzzer sounds for the full duration. In that state,
     * even though soundBuzzer(false) is sent over CAN, checkBuzzer() will still return
     * true if the buzzer is currently sounding.
     * 
     * @return True if the buzzer is currently sounding, according to the Dash. False otherwise.
     */
    bool checkBuzzer();

    /**
     * Setter for the dash LEDs .
     * 
     * @param led DashLED_e enum that corresponds to the LED's value in the LED array
     * @param color LEDColors_e enum that corresponds to the color/state of the set LED
     */
    void setLED(DashLED_e led, LEDColors_e color);

};

#endif /* __DASHBOARDINTERFACE_H__ */
