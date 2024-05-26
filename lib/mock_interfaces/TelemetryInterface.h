#ifndef TELEMETRYINTERFACE
#define TELEMETRYINTERFACE

#include "stdint.h"


// #include "AnalogSensorsInterface.h"
// #include "SteeringEncoderInterface.h"
// #include "hytech.h"
// #include "InverterInterface.h"
// #include "TorqueControllersData.h"
// using InvInt_t = InverterInterface<CANBufferType>;

// const int FIXED_POINT_PRECISION = 10000;

struct TelemetryInterfaceReadChannels
{
    int accel1_channel;
    int accel2_channel;
    int brake1_channel;
    int brake2_channel;
    int pots_fl_channel;
    int pots_fr_channel;
    int loadcell_fl_channel;
    int loadcell_fr_channel;
    int analog_steering_channel;
    int current_channel;
    int current_ref_channel;
    int glv_sense_channel;
    int therm_fl_channel;
    int therm_fr_channel;
};

class TelemetryInterface
{
private:
    /* Outbound telemetry CAN messages */
    // MCU_analog_readings mcu_analog_readings_;
    // /* CAN Tx buffer */
    // CANBufferType *msg_queue_;
    // /* ADC read channels */
    // TelemetryInterfaceReadChannels channels_;

public:
    TelemetryInterface() {};

};

#endif /* TELEMETRYINTERFACE */