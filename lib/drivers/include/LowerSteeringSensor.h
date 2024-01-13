/* Analog bottom steering sensor */
#ifndef __LOWER_STEERING_SENSOR_H__
#define __LOWER_STEERING_SENSOR_H__

// #include "ADC_SPI.h"
#include "ADCDriver.h"

class LowerSteeringSensor {
    public:
        LowerSteeringSensor (const ADCDriver* adc, int data_channel, float slope, float offset) {
            _adc_driver = adc;
            channel_ = data_channel;
            steering_calibration_slope = slope;
            steering_calibration_offset = offset;
            // other params set here for scaling
        }

        void read_sensor() {
            angle_degree = (_adc_driver->get_adc_channel(channel_) * steering_calibration_slope + steering_calibration_offset);
        }

        void set_steering_angle() {
            return angle_degree;
        }

    private:
        // float scale_to_degrees_(int steer_val);
        
        // pointer to shared data bus
        // const ADC_SPI * sensor_;
        const ADCDriver* _adc_driver;
        
        int channel_;

        float steering_calibration_slope;
        float steering_calibration_offset;
        float angle_degree;
};

#endif /* __LOWER_STEERING_SENSOR_H__ */
#pragma once