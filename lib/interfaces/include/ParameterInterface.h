#ifndef PARAMETERINTERFACE
#define PARAMETERINTERFACE
#include "MCUStateMachine.h"
#include "ht_eth.pb.h"

// yes, i know this is a singleton. im prototyping rn.
class ParameterInterface
{
public:
    ParameterInterface(CAR_STATE& car_state_ref): current_car_state_(car_state_ref), params_need_sending_(false), config_({}) {}
    
    void update_config(const config &config)
    {
        if(static_cast<int>(current_car_state_) < 5 ){
            config_ = config;
        }
        
    }
    
    void set_params_need_sending()
    {
        params_need_sending_ = true;
    }
    void reset_params_need_sending()
    {
        params_need_sending_ = false;
    }
    bool params_need_sending() { return params_need_sending_; }
    
    config get_config()
    {
        return config_;
    }

private:
    const CAR_STATE& current_car_state_;
    bool params_need_sending_ = false;
    config config_;
    
};

#endif