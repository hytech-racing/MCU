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

    void init();

    void software_shutdown();


private:

    AMSInterface        *ams_;
    WatchdogInterface   *wd_;
};



#endif /* __SAFETY_SYSTEM_H__ */
