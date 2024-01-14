#ifndef __AMS_INTERFACE__
#define __AMS_INTERFACE__

class AMSInterface
{
    public:
        AMSInterface() {}
        bool ok_high();
        bool heartbeat_check(unsigned long curr_time);
    private:
};

#endif /* __AMS_INTERFACE__ */
