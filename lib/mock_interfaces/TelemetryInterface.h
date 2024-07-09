#ifndef __TELEMETRY_INTERFACE__
#define __TELEMETRY_INTERFACE__

#include <stdint.h>

#include "TorqueControllerData.h"

class TelemetryInterface
{
private:
    /* data */
public:
    TelemetryInterface(/* args */) {};
    ~TelemetryInterface() {};

    void update_TCMux_status_CAN_msg(
        const TCMuxStatus_s &tcMuxStatus
    ) {};

    void update_steering_status_CAN_msg(
        const float steering_system_angle,
        const float filtered_angle_encoder,
        const float filtered_angle_analog,
        const uint8_t steering_system_status,
        const uint8_t steering_encoder_status,
        const uint8_t steering_analog_status
    ) {};
};


#endif