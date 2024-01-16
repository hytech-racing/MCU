#ifndef __AMS_INTERFACE_H__
#define __AMS_INTERFACE_H__

#include "MCUInterface.h"

class AMSInterface
{
    public:
        AMSInterface() {}
        bool ok_high();
        bool heartbeat_check(unsigned long curr_time);
    private:
};

#endif /* __AMS_INTERFACE_H__ */
