#ifndef __SAFETY_SYSTEM_H__
#define __SAFETY_SYSTEM_H__

#include "AMSInterface.h"
#include "WatchdogInterface.h"

class SafetySystem
{
public:
    SafetySystem(AMSInterface *ams, WatchdogInterface *wd): 
        ams_(ams), 
        wd_(wd) {};

    /* Initialization */
    void init();

    /* Monitor software state every cycle */
    void software_shutdown(unsigned long curr_time);

    /* Exchange businsess logic values */
    bool get_software_is_ok();


private:
    /* Associated interfaces */
    AMSInterface        *ams_;
    WatchdogInterface   *wd_;

    /* Software ok status */
    bool software_is_ok;
};

#endif /* __SAFETY_SYSTEM_H__ */
