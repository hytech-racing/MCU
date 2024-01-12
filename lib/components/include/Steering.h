/* Steering component */
#ifndef __STEERING_H__
#define __STEERING_H__

#include "LowerSteeringSensor.h"
#include "UpperSteeringSensor.h"

struct SteeringDriverInterface {
    int steeringChannel1;
    int steeringChannel2;
};

class SteeringComponent {
    public:
        SteeringComponent(const LowerSteeringSensor* driver_1, const UpperSteeringSensor* driver_2) {
            // TODO change scaling factors with params
            this->driver_1 = driver_1;
            this->driver_2 = driver_2;
        }

        float get_all_angles() {
            lower_steering_angle = driver_1->get_steering_angle();
            upper_steering_angle = driver_2->get_steering_angle();
        }

        bool get_desired_angle(float* steering_angle) {
            if (fabs(lower_steering_angle - upper_steering_angle) < difference_thresh) {
                *steering_angle = (lower_steering_angle + upper_steering_angle) / 2.0;
                return true;
            }
            else {
                return false;
            }
        };

    private:        

        const LowerSteeringSensor* driver_1;
        const UpperSteeringSensor* driver_2;

        float scaling_;
        float lower_steering_angle;
        float upper_steering_angle;
        
        float difference_thresh = 1.0f;
};

#endif
#pragma once
