#pragma once

#include "CASESystem.h"
#include <gtest/gtest.h>

class FakeMessageQueue
{
    public:
        FakeMessageQueue() {}
    
};

void enqueue_matlab_msg(FakeMessageQueue *, const CAN_MESSAGE_BUS& msg)
{

}

TEST(CASESystemTesting, test_vn_start_time)
{
    FakeMessageQueue faked_msg_q;
    CASEConfiguration case_config = {true, true, false, false, false, AMK_MAX_RPM, MAX_REGEN_TORQUE, AMK_MAX_TORQUE, 1.0, 1.0, 0.0};
    CASESystem case_system(&faked_msg_q, 100, 70, case_config);
}

