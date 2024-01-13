/* Analog bottom steering sensor */
#ifndef __LOWER_STEERING_SENSOR_H__
#define __LOWER_STEERING_SENSOR_H__

#include "ADC_SPI.h"

class LowerSteeringSensor {
    public:
        LowerSteeringSensor (const ADC_SPI* sensor, int data_channel) {
            sensor_ = sensor;
            channel_ = data_channel;
            // other params set here for scaling
        }

        void read_sensor() {
            angle_degree = (sensor_->read_channel(channel_) * steering_calibration_slope + steering_calibration_offset);
        }

        float get_steering_angle() {
            return angle_degree;
        }

    private:
        float scale_to_degrees_(int steer_val);
        
        // pointer to shared data bus
        const ADC_SPI * sensor_;
        
        int channel_;

        float steering_calibration_slope = -0.111;
        float steering_calibration_offset = 260.0;
        float angle_degree;
};

#endif
#pragma once