#ifndef __SAFETY_SYSTEM_TEST_H__
#define __SAFETY_SYSTEM_TEST_H__

#include <gtest/gtest.h>
#include "AMSInterface.h"
#include "WatchdogInterface.h"
#include "SafetySystem.h"
#include "SysClock.h"


TEST(SafetySystemTest, test_software_shutdown) {
    SysClock curr_tick;
    

    AMSInterface ams_interface(0);
    WatchdogInterface wd_interface(0);
    SafetySystem safety_system(&ams_interface, &wd_interface);

    ams_interface.set_heartbeat(0);
    wd_interface.
    curr_tick.tick(10);




}




#endif /* __SAFETY_SYSTEM_TEST_H__ */