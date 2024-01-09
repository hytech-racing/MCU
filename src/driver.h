#include "ADC_SPI.h"

class SteeringDriver {
    public:
        SteeringDriver(const ADC_SPI* sensor, int data_channel) {
            sensor_ = sensor;
            channel_ = data_channel;
            // other params set here for scaling
        };

        float get_steering_angle(); 
    private:
        float scale_to_degrees_(int steer_val);
        
        // pointer to shared data bus
        const ADC_SPI * sensor_;
        
        int channel_;
};