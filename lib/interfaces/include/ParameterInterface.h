#ifndef PARAMETERINTERFACE
#define PARAMETERINTERFACE
#include "MCUStateMachine.h"
#include "ht_eth.pb.h"

// yes, i know this is a singleton. im prototyping rn.
// TODO review if I can just give this a pointer to an ethernet port
class ParameterInterface
{
public:
    ParameterInterface(): current_car_state_(CAR_STATE::STARTUP), params_need_sending_(false), config_({}) {}
    
    void update_car_state(const CAR_STATE& state)
    {
        current_car_state_ = state;
    }
    void update_config(const config &config)
    {
        if(static_cast<int>(current_car_state_) < 5 ){
            config_ = config;
        }
        
    }
    config get_config()
    {
        return config_;
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

private:
    CAR_STATE current_car_state_;
    bool params_need_sending_ = false;
    config config_;
    
};

#endif