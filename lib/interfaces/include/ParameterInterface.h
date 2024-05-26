#ifndef PARAMETERINTERFACE
#define PARAMETERINTERFACE
#include "MCUStateMachine.h"
#include "ht_eth.pb.h"
#include "default_config.h"

// yes, i know this is a singleton. im prototyping rn.
// TODO review if I can just give this a pointer to an ethernet port
class ParameterInterface
{
public:
    ParameterInterface(): current_car_state_(CAR_STATE::STARTUP), params_need_sending_(false), got_new_CASE_config_(false), config_(DEFAULT_CONFIG) {}
    
    void update_car_state(const CAR_STATE& state)
    {
        current_car_state_ = state;
    }

    /// @brief function to be called by the protobuf message interface setting the CASE config message struct. 
    ///        only updates the config in the param server if the current state of the car is not in RTD
    /// @param config the received config struct from the wire
    void update_CASE_config(const config &config)
    {
        if(static_cast<int>(current_car_state_) < 5 ){
            config_ = config;
        }
        got_new_CASE_config_ = true;
    }

    /// @brief function to see if we have new CASE config available
    /// @return true if case config available, false otherwise
    bool new_CASE_config_available()
    {
        return got_new_CASE_config_;
    }
    
    
    /// @brief get the current CASE config. when ran this function conditionally resets the internal bool preventing 
    ///        continuous resetting of the CASE config
    /// @param reset if true, reset the CASE config update flag 
    /// @return current config
    config get_CASE_config(bool reset=true)
    {
        if(reset)
        {
            got_new_CASE_config_ = false;
        }
        
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
    bool got_new_CASE_config_ = false;
    config config_;
};

#endif