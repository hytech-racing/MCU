#ifndef __DASHBOARD_DRIVER__
#define __DASHBOARD_DRIVER__

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

struct DashSystemInterface
{
    // enum for dial position read by controller mux
    DialMode dial_mode;
};

class DashboardInterface
{
public:
    DashboardInterface(){

    };
    DashSystemInterface evaluate_dashboard(
        const Dashboard_status &can_data);
    bool start_button_pressed();

private:
};

#endif /* __DASHBOARD_DRIVER__ */
