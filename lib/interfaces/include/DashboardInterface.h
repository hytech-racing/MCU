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

struct DashboardInterfaceOutput_s
{
    DialMode_e dial_mode;
    DashButtons_s buttons;
    bool ssok;
    bool shutdown;
};

class DashboardInterface
{
private:
    DashboardInterfaceOutput_s dashState;
public:
// Constructors
    Dashboard();

// Functions
    /// @brief Send data to the dashboard
    void set(
        bool buzzerEnabled,
        DashLED_s LEDsState
    );
    /// @brief Get the state of the dashboard's signals
    /// @return DashboardInterfaceOutput_s
    DashboardInterfaceOutput_s convert();
};

#endif /* __DASHBOARDINTERFACE_H__ */
