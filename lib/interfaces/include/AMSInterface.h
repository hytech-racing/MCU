#ifndef AMSINTERFACE
#define AMSINTERFACE

class AMSInterface
{
    public:
        AMSInterface() {}
        bool ok_high();
        bool heartbeat_check(unsigned long curr_time);
    private:
};

#endif /* AMSINTERFACE */
