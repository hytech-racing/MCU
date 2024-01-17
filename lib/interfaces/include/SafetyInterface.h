#ifndef __SAFETY_INTERFACE_H__
#define __SAFETY_INTERFACE_H__

#include "MCUInterface.h"

#define SOFTWARE_OK     28
#define WATCHDOG_INPUT  32

#define WATCHDOG_KICK_INTERVAL  7    // milliseconds

class SafetyInterface
{
public:
    SafetyInterface(MCUInterface *mcu): mcu_(mcu), watchdog_time(millis()) {};

    void init();

    void set_software_is_ok();
    void set_software_is_not_ok();

    void kick_watchdog(unsigned long curr_time);

    bool software_is_ok();


private:
    MCUInterface *mcu_;
    unsigned long watchdog_time;
    static bool watchdog_state;

};




#endif /* __SAFETY_INTERFACE_H__ */
