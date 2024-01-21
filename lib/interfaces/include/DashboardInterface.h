#ifndef DASHBOARDDRIVER
#define DASHBOARDDRIVER

#include "Dashboard_status.h"
// The driver interface is used/returned by the driver

enum DialMode
{
    MODE_1,
    MODE_2,
    ACCEL_LAUNCH_CONTROL,
    SKIDPAD,
    AUTOCROSS,
    ENDURANCE
};

struct DashComponentInterface
{
    // enum for dial position read by controller mux
    DialMode dial_mode;
};
class DashDriver
{
public:
    DashDriver(){

    };
    DashComponentInterface evaluate_dashboard(
        const Dashboard_status &can_data);
    bool start_button_pressed();

private:
};

#endif /* DASHBOARDDRIVER */
