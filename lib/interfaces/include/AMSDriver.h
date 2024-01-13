#ifndef AMSDRIVER
#define AMSDRIVER

class AMSDriver
{
    public:
        AMSDriver() {}
        bool ok_high();
        bool heartbeat_check(unsigned long curr_time);
    private:
};

#endif /* AMSDRIVER */
