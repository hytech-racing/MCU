#ifndef AMSINTERFACE
#define AMSINTERFACE

class AMSInterface
{
public:
    bool ok_high_;
    bool heartbeat_status_;
    AMSInterface() {}
    bool ok_high() { return ok_high_; };
    bool heartbeat_check(unsigned long curr_time) { return heartbeat_status_; };

private:
};

#endif /* AMSINTERFACE */
