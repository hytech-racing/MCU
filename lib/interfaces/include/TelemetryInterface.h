#ifndef TELEMETRYINTERFACE
#define TELEMETRYINTERFACE

#include "stdint.h"
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

#include "MessageQueueDefine.h"
#include "AnalogSensorsInterface.h"
#include "SteeringEncoderInterface.h"
#include "hytech.h"
#include "InverterInterface.h"
#include "TorqueControllersData.h"
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
    int therm_fl_channel;
    int therm_fr_channel;
};

class TelemetryInterface
{
private:
    /* Outbound telemetry CAN messages */
    MCU_analog_readings mcu_analog_readings_;
    /* CAN Tx buffer */
    CANBufferType *msg_queue_;
    /* ADC read channels */
    TelemetryInterfaceReadChannels channels_;

public:
    TelemetryInterface(CANBufferType *msg_output_queue, const TelemetryInterfaceReadChannels &channels) : msg_queue_(msg_output_queue),
                                                                                                          channels_(channels){};

    /* GETTERS for basic conversions that don't have a home */

    AnalogConversion_s get_glv_voltage(const AnalogConversionPacket_s<8> &adc1)
    {
        return adc1.conversions[channels_.glv_sense_channel];
    }

    /* Update CAN messages (main loop) */
    // Interfaces
    void update_front_thermistors_CAN_msg(
        const AnalogConversion_s &therm_fl,
        const AnalogConversion_s &therm_fr
    );
    void update_pedal_readings_CAN_msg(
        float accel_percent,
        float brake_percent,
        float mech_brake_percent
    );
    void update_pedal_readings_raw_CAN_msg(
        const AnalogConversion_s &accel_1,
        const AnalogConversion_s &accel_2,
        const AnalogConversion_s &brake_1,
        const AnalogConversion_s &brake_2
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
        InvInt_t *fl,
        InvInt_t *fr,
        InvInt_t *rl,
        InvInt_t *rr
    );
    void update_drivetrain_err_status_CAN_msg(
        InvInt_t *fl,
        InvInt_t *fr,
        InvInt_t *rl,
        InvInt_t *rr
    );
    void update_drivetrain_status_telem_CAN_msg(
        InvInt_t *fl,
        InvInt_t *fr,
        InvInt_t *rl,
        InvInt_t *rr,
        bool accel_implaus,
        bool brake_implaus,
        float accel_per,
        float brake_per
    );
    void update_drivetrain_torque_telem_CAN_msg(
        InvInt_t *fl,
        InvInt_t *fr,
        InvInt_t *rl,
        InvInt_t *rr
    );
    void update_penthouse_accum_CAN_msg(
        const AnalogConversion_s &current,
        const AnalogConversion_s &reference
    );
    void update_TCMux_status_CAN_msg(
        const TCMuxStatus_s &tcMuxStatus
    );
    void update_steering_status_CAN_msg(
        const float steering_system_angle,
        const float filtered_angle_encoder,
        const float filtered_angle_analog,
        const uint8_t steering_system_status,
        const uint8_t steering_encoder_status,
        const uint8_t steering_analog_status
    );    

    /* Enqueue outbound telemetry CAN messages */
    template <typename T>
    void enqueue_CAN(T can_msg, uint32_t id);

    template <typename U>
    void enqueue_new_CAN(U *structure, uint32_t (*pack_function)(U *, uint8_t *, uint8_t *, uint8_t *));

    void enqeue_controller_CAN_msg(const PIDTVTorqueControllerData &data);

    // TODO dont pass in pointer to inverter interface here we will break shit with this
    /* Tick at 50Hz to send CAN */
    void tick(
        const AnalogConversionPacket_s<8> &adc1,
        const AnalogConversionPacket_s<4> &adc2,
        const AnalogConversionPacket_s<4> &adc3,
        const AnalogConversionPacket_s<2> &mcu_adc,
        const SteeringEncoderConversion_s &encoder,
        InvInt_t *fl,
        InvInt_t *fr,
        InvInt_t *rl,
        InvInt_t *rr,
        bool accel_implaus,
        bool brake_implaus,
        float accel_per,
        float brake_per,
        const AnalogConversion_s &accel_1,
        const AnalogConversion_s &accel_2,
        const AnalogConversion_s &brake_1,
        const AnalogConversion_s &brake_2,
        float mech_brake_active_percent,
        const PIDTVTorqueControllerData &data);
};

#endif /* TELEMETRYINTERFACE */