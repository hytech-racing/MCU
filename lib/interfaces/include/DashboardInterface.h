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
    virtual DialMode_s getDialMode();
    virtual bool nightModeButtonPressed();
    virtual bool inverterResetButtonPressed();
    virtual bool torqueVectoringOffButtonPressed();
    virtual bool startButtonPressed();
    virtual bool torqueButtonPressed();
    virtual bool specialButtonPressed();
};

#endif /* __DASHBOARDINTERFACE_H__ */
