#ifndef TELEMETRYINTERFACE
#define TELEMETRYINTERFACE

#include "stdint.h"
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
// #include "hytech.h"
#include "MessageQueueDefine.h"
#include "AnalogSensorsInterface.h"
#include "SteeringEncoderInterface.h"

class TelemetryInterface
{
private:
    /* Outbound telemetry CAN messages */
    MCU_pedal_readings          mcu_pedal_readings_;
    MCU_load_cells              mcu_load_cells_;
    MCU_front_potentiometers    mcu_front_potentiometers_;
    MCU_rear_potentiometers     mcu_rear_potentiometers_;
    MCU_analog_readings         mcu_analog_readings_;
    /* CAN Tx buffer */
    CANBufferType *msg_queue_;

public:
    TelemetryInterface(CANBufferType *msg_output_queue):
        msg_queue_(msg_output_queue) {};

    /* Update CAN messages (main loop) */
    // Interfaces
    void update_pedal_readings_CAN_msg(
        const AnalogConversion_s &accel1,
        const AnalogConversion_s &accel2,
        const AnalogConversion_s &brake1,
        const AnalogConversion_s &brake2
    );
    void update_load_cells_CAN_msg(
        const AnalogConversion_s &lc_fl,
        const AnalogConversion_s &lc_fr
    );
    void update_potentiometers_CAN_msg(
        const AnalogConversion_s &pots_fl,
        const AnalogConversion_s &pots_fr
    );
    void update_analog_readings_CAN_msg(
        const SteeringEncoderConversion_s &steer1,
        const AnalogConversion_s &steer2,
        const AnalogConversion_s &current,
        const AnalogConversion_s &reference,
        const AnalogConversion_s &glv
    );

    /* Enqueue outbound telemetry CAN messages */    
    void enqueue_CAN_mcu_pedal_readings();
    void enqueue_CAN_mcu_load_cells();
    void enqueue_CAN_mcu_front_potentiometers();
    void enqueue_CAN_mcu_rear_potentiometers();
    void enqueue_CAN_mcu_analog_readings();

    /* Tick at 50Hz to send CAN */
    void tick(
        const AnalogConversionPacket_s<8> &adc1,
        const AnalogConversionPacket_s<4> &adc2,
        const AnalogConversionPacket_s<4> &adc3,
        const SteeringEncoderConversion_s &encoder
    );

};

#endif /* TELEMETRYINTERFACE */
