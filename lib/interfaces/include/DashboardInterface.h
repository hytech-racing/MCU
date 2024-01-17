#ifndef __DASHBOARDINTERFACE_H__
#define __DASHBOARDINTERFACE_H__

enum DialMode_s
{
    MODE_1,
    MODE_2,
    ACCEL_LAUNCH_CONTROL,
    SKIDPAD,
    AUTOCROSS,
    ENDURANCE,
};

class DashboardInterface
{
private:
public:
    DialMode_s getDialMode();
    bool nightModeButtonPressed();
    bool inverterResetButtonPressed();
    bool torqueVectoringOffButtonPressed();
    bool startButtonPressed();
    bool torqueButtonPressed();
    bool specialButtonPressed();
};

#endif /* __DASHBOARDINTERFACE_H__ */
