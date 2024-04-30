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
    void update_config(const ht_eth_config &config)
    {
        config_ = config;
    }
    const ht_eth_config &get_config()
    {
        return config_;
    }

private:
    ht_eth_config config_;
};

#endif