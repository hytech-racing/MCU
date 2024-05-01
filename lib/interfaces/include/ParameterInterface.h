#ifndef PARAMETERINTERFACE
#define PARAMETERINTERFACE

#include "ht_msgs.pb.h"

// yes, i know this is a singleton. im prototyping rn.
class ParameterInterface
{
public:
    ParameterInterface()
    {
        config_ = {};
    }
    void update_config(const config &config)
    {
        config_ = config;
    }
    const config &get_config()
    {
        return config_;
    }

private:
    config config_;
};

#endif