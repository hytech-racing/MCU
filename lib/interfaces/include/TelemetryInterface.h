#ifndef TELEMETRYINTERFACE
#define TELEMETRYINTERFACE

#include "stdint.h"
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
// #include "hytech.h"
#include "MessageQueueDefine.h"
#include "AnalogSensorsInterface.h"
#include "SteeringEncoderInterface.h"
#include "hytech.h"
#include "InverterInterface.h"

using InvInt_t = InverterInterface<CANBufferType>;

const int FIXED_POINT_PRECISION = 10000;

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
};

class TelemetryInterface
{
private:
    /* Outbound telemetry CAN messages */
    MCU_analog_readings         mcu_analog_readings_;
    /* CAN Tx buffer */
    CANBufferType *msg_queue_;
    /* ADC read channels */
    TelemetryInterfaceReadChannels channels_;

public:
    TelemetryInterface(CANBufferType *msg_output_queue, const TelemetryInterfaceReadChannels &channels):
        msg_queue_(msg_output_queue),
        channels_(channels) {};

    /* GETTERS for basic conversions that don't have a home*/

    AnalogConversion_s get_glv_voltage(const AnalogConversionPacket_s<8> &adc1) {
        return adc1.conversions[channels_.glv_sense_channel];
    }

    /* Update CAN messages (main loop) */
    // Interfaces
    void update_pedal_readings_CAN_msg(
        float accel_percent,
        float brake_percent,
        float mech_brake_percent
    );
    void update_suspension_CAN_msg(
        const AnalogConversion_s &lc_fl,
        const AnalogConversion_s &lc_fr,
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
    void update_drivetrain_rpms_CAN_msg(
        InvInt_t* fl, 
        InvInt_t* fr, 
        InvInt_t* rl, 
        InvInt_t* rr
    );
    void update_drivetrain_err_status_CAN_msg(
        InvInt_t* fl, 
        InvInt_t* fr, 
        InvInt_t* rl, 
        InvInt_t* rr
    );
    void update_drivetrain_status_telem_CAN_msg(
        InvInt_t* fl,
        InvInt_t* fr,
        InvInt_t* rl,
        InvInt_t* rr,
        bool accel_implaus,
        bool brake_implaus,
        float accel_per,
        float brake_per
    );
    void update_drivetrain_torque_telem_CAN_msg(
        InvInt_t* fl,
        InvInt_t* fr,
        InvInt_t* rl,
        InvInt_t* rr);
    void update_penthouse_accum_CAN_msg(
        const AnalogConversion_s &current,
        const AnalogConversion_s &reference
    );

    /* Enqueue outbound telemetry CAN messages */    
    // void enqueue_CAN_mcu_pedal_readings();
    // void enqueue_CAN_mcu_load_cells();
    // void enqueue_CAN_mcu_front_potentiometers();
    // void enqueue_CAN_mcu_rear_potentiometers();
    // void enqueue_CAN_mcu_analog_readings();

    template<typename T>
    void enqueue_CAN(T can_msg, uint32_t  id);

    template<typename U>
    void enqueue_new_CAN(U* structure, uint32_t (* pack_function)(U*, uint8_t*, uint8_t*, uint8_t*));

    /* Tick at 50Hz to send CAN */
    void tick(
        const AnalogConversionPacket_s<8> &adc1,
        const AnalogConversionPacket_s<4> &adc2,
        const AnalogConversionPacket_s<4> &adc3,
        const SteeringEncoderConversion_s &encoder,
        const InvInt_t* fl,
        const InvInt_t* fr,
        const InvInt_t* rl,
        const InvInt_t* rr,
        bool accel_implaus,
        bool brake_implaus,
        float accel_per,
        float brake_per,
        float mech_brake_active_percent
    );

};

#endif /* TELEMETRYINTERFACE */