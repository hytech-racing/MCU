#ifndef TELEMETRYINTERFACE
#define TELEMETRYINTERFACE

/* System Includes */
#include "stdint.h"

/* Library */
#include "FlexCAN_T4.h"                 // From FlexCAN_T4
#include "HyTech_CAN.h"                 // from hytech_can library (deprecated, use can_lib library instead)
#include "hytech.h"                     // from can_lib library

/* Interface */
#include "MessageQueueDefine.h"
#include "AnalogSensorsInterface.h"
#include "SteeringEncoderInterface.h"
#include "InverterInterface.h"

/* Shared Data */
#include "TorqueControllersData.h"

/**
 * Typedef for InvInt_t. CANBufferType is defined in MessageQueueDefine.h, and
 * InverterInterface is defined in InverterInterface.h.
 */
using InvInt_t = InverterInterface<CANBufferType>;

/**
 * Const for fixed point precision of glv_battery_voltage field of MCU_analog_readings
 * CAN message. When we switch MCU_analog_readings to the new CAN library, use the
 * toS() and fromS() functions instead.
 */
const int GLV_BATTERY_VOLTAGE_FIXED_POINT_PRECISION = 1000;

/**
 * Read channels for the TelemetryInterface. These denote the read channels for each piece of
 * data, but these do not all come from the same ADC, so be careful. For instance, both
 * MCU15_FL_LOADCELL_CHANNEL and MCU15_FR_LOADCELL_CHANNEL are on "channel 2", but one comes
 * from ADC2 and the other comes from ADC3. Be sure to read from the correct ADC, as well as
 * the correct channel!
 */
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

/**
 * Class for the TelemetryInterface. The TelemetryInterface is responsible for
 * enqueuing new CAN messages onto the Telemetry CAN line. Most new messages
 * are sent in the tick() function, but some triggered manually by various
 * systems.
 */
class TelemetryInterface
{
private:
    /**
     * Outbound telemetry CAN messages.
     * 
     * TODO: Switch this to can_lib instead of HyTech_CAN
     */
    MCU_analog_readings mcu_analog_readings_;

    /**
     * CAN TX (transmission) buffer. CANBufferType is from MessageQueueDefine.h
     */
    CANBufferType *msg_queue_;

    /**
     * ADC read channels. See TelemetryInterfaceReadChannels struct definition.
     */
    TelemetryInterfaceReadChannels channels_;

public:

    /**
     * Generic constructor for TelemetryInterface.
     * @param msg_output_queue A ponter to a CANBuffer queue
     * @param channels The set of ADC channels for this TelemetryInterface to read from.
     */
    TelemetryInterface(CANBufferType *msg_output_queue, const TelemetryInterfaceReadChannels &channels) : msg_queue_(msg_output_queue),
                                                                                                          channels_(channels){};

    /* -------------------- Update CAN messages -------------------- */
    
    /**
     * Queues a CAN frame for the pedal readings with the given values. Uses the NEW can library (can_lib).
     * @param accel_percent The new accel_percent value to put on the Telemetry CAN line.
     * @param brake_percent The new brake_percent value to put on the Telemetry CAN line.
     * @param mech_brake_percent The new mech_brake_percent value to put on the Telemetry CAN line.
     */
    void update_pedal_readings_CAN_msg(
        float accel_percent,
        float brake_percent,
        float mech_brake_percent
    );

    /**
     * Queues a CAN frame for the raw pedal readings with the given values. Uses the NEW can library (can_lib).
     * @param accel_1 The new accel_1 analog conversion to put on the Telemetry CAN line.
     * @param accel_2 The new accel_2 analog conversion to put on the Telemetry CAN line.
     * @param brake_1 The new brake_1 analog conversion to put on the Telemetry CAN line.
     * @param brake_2 The new brake_2 analog conversion to put on the Telemetry CAN line.
     */
    void update_pedal_readings_raw_CAN_msg(
        const AnalogConversion_s &accel_1,
        const AnalogConversion_s &accel_2,
        const AnalogConversion_s &brake_1,
        const AnalogConversion_s &brake_2
    );

    /**
     * Queues a CAN frame for the suspension analog conversions with the given values. Uses the NEW can library (can_lib).
     * @param lc_fl The new lc_fl (front left load cell) value to put on the Telemetry CAN line.
     * @param lc_fr The new lc_fr (front right load cell) value to put on the Telemetry CAN line.
     * @param pots_fl The new pots_fl (front left suspension potentiometer) value to put on the Telemetry CAN line.
     * @param pots_fr The new pots_fr (front right suspension potentiometer) value to put on the Telemetry CAN line.
     */
    void update_suspension_CAN_msg(
        const AnalogConversion_s &lc_fl,
        const AnalogConversion_s &lc_fr,
        const AnalogConversion_s &pots_fl,
        const AnalogConversion_s &pots_fr
    );

    /**
     * Queues a CAN frame for the steering sensors, hall_effect_current, and GLV voltage.
     * Uses the OLD CAN library (HyTech_CAN)
     * 
     * This queues the hall_effect_current as the difference between the given current and
     * reference, which is technically redundant, since the PENTHOUSE_ACCUM_MSG includes
     * both current and reference independently.
     * 
     * This also will queue the GLV battery charge in mV, since it multiplies by
     * GLV_BATTERY_VOLTAGE_FIXED_POINT_RECISION.
     * 
     * @param steer1 The ORBISBR10 steering sensor data. (from shared-interfaces-lib)
     * @param steer2 The analog steering sensor data. (from ADC1)
     * @param current The current reading from the 8th order maxim filter.
     * @param reference The reference reading from the other 8th order maxim filter.
     * @param glv The charge on the GLV battery.
     */
    void update_analog_readings_CAN_msg(
        const SteeringEncoderConversion_s &steer1,
        const AnalogConversion_s &steer2,
        const AnalogConversion_s &current,
        const AnalogConversion_s &reference,
        const AnalogConversion_s &glv
    );

    /**
     * Enqueues a new CAN frame for the DRIVETRAIN_RPMS_TELEM_t message with the rpms of each wheel.
     * This function uses the NEW CAN library (can_lib)
     * @param fl The front left inverter interface.
     * @param fr The front right inverter interface.
     * @param rl The rear left inverter interface.
     * @param rr The rear right inverter interface.
     */
    void update_drivetrain_rpms_CAN_msg(
        InvInt_t *fl,
        InvInt_t *fr,
        InvInt_t *rl,
        InvInt_t *rr
    );

    /**
     * Enqueues a new CAN frame for the DRIVETRAIN_ERR_STATUS_TELEM_t message with the error number of each wheel.
     * This function uses the NEW CAN library (can_lib)
     * @param fl The front left inverter interface.
     * @param fr The front right inverter interface.
     * @param rl The rear left inverter interface.
     * @param rr The rear right inverter interface.
     */
    void update_drivetrain_err_status_CAN_msg(
        InvInt_t *fl,
        InvInt_t *fr,
        InvInt_t *rl,
        InvInt_t *rr
    );

    /**
     * Enqueues 9 new CAN frames. First, it enqueues the MC_TEMPS CAN message for each wheel, then the new
     * setpoint command for each wheel. Finally, it enqueues the DRIVETRAIN_STATUS_TELEM_t message that
     * contains the error status for each of the four inverters. The MC_TEMPS and MC_setpoints_command
     * messages are enqueued using the OLD CAN library, while the DRIVETRAIN_STATUS_TELEM message is
     * enqueued using the NEW CAN library.
     * 
     * MC1 is front left, MC2 is front right, MC3 is rear left, MC4 is rear right.
     * 
     * @param fl The front left inverter interface.
     * @param fr the front right inverter interface.
     * @param rl The rear left inverter interface.
     * @param rr The rear right inverter interface.
     * @param accel_implaus Whether or not the APPS is currently giving an implausible
     *                      value. This comes directly from the PedalsSystem.
     * @param brake_implaus Whether or not the brake sensors are reading an implausible
     *                      value. This comes directly from the PedalsSystem.
     * @param accel_per The current percent that the acceleration pedal is pressed,
     *                  according to the PedalsSystemData struct from the PedalsSystem.
     * @param brake_per The current percent that the brake pedal is pressed, according
     *                  to the PedalsSystemData struct from the PedalsSystem.
     */
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

    /**
     * Enqueues a new CAN frame for the DRIVETRAIN_TORQUE_TELEM_t message. This was
     * just temporary for gearbox seal validation, but it is still functional, so
     * it was not removed. Uses the NEW CAN library (can_lib).
     * @param fl The front left inverter interface.
     * @param fr the front right inverter interface.
     * @param rl The rear left inverter interface.
     * @param rr The rear right inverter interface.
     */
    void update_drivetrain_torque_telem_CAN_msg(
        InvInt_t *fl,
        InvInt_t *fr,
        InvInt_t *rl,
        InvInt_t *rr
    );

    /**
     * Enqueues a new CAN frame for the PENTHOUSE_ACCUM_MSG_t message. This includes the
     * hall effect current and hall effect reference. This uses the NEW CAN library.
     * This CAN message makes the hall_effect_current data in the MCU_ANALOG_READINGS
     * message redundant, since that message only includes the difference between
     * these two values.
     * 
     * @param current The current reading from the 8th order maxim filter.
     * @param reference The reference reading from the other 8th order maxim filter.
     */
    void update_penthouse_accum_CAN_msg(
        const AnalogConversion_s &current,
        const AnalogConversion_s &reference
    );

    /**
     * Enqueues a new CAN frame for the TCMUX_STATUS_REPORT_t message. Uses the NEW CAN library.
     * Notably, this function is NOT called in the tick() function like most of the other CAN
     * frames. Instead, this function is called by the TorqueControllerMux system in its
     * reportTCMuxStatus() funtion. See TorqueControllerMux.cpp for the contents of this CAN message.
     * 
     * @param tcMuxStatus The current status of the torque controller multiplexer.
     */
    void update_TCMux_status_CAN_msg(
        const TCMuxStatus_s &tcMuxStatus
    );

    /**
     * Enqueues a new CAN frame for the STEERING_SYSTEM_REPORT_t message. Uses the NEW CAN library.
     * Notably, this function is NOT called in the tick() function like most of hte other CAN
     * frames. Instead, this function is called by the SteeringSystemp.cpp system in its
     * reportSteeringStatus() function.
     * 
     * See SteeringSystem.cpp for the contents of this CAN message.
     */
    void update_steering_status_CAN_msg(
        const float steering_system_angle,
        const float filtered_angle_encoder,
        const float filtered_angle_analog,
        const uint8_t steering_system_status,
        const uint8_t steering_encoder_status,
        const uint8_t steering_analog_status
    );

    /**
     * Enqueues a new CAN frame for the CONTROLLER_PID_TV_DATA_t and CONTROLLER_PID_TV_DELTA_DATA_t
     * messages.
     * 
     * @param The data to be put on the Telemetry CAN line. 
     */
    void enqeue_controller_CAN_msg(const PIDTVTorqueControllerData &data);



    /* -------------------- Enqueue outbound telemetry CAN messages -------------------- */

    /**
     * Enqueues the given CAN frame using the OLD CAN library (deprecated! Use enqueue_new_CAN when possible).
     * The ID of the CAN message MUST match up with the given struct, as this function will not check to ensure
     * the correct ID is given.
     * 
     * @param T The type of this CAN message.
     * @param can_msg The contents of this CAN message.
     * @param id The ID of this CAN message.
     */
    template <typename T>
    void enqueue_CAN(T can_msg, uint32_t id);

    /**
     * Enqueues the given CAN frame using the NEW CAN library (can_lib). See the above
     * update_CAN functions for usage examples.
     * 
     * @param structure The contents of this CAN frame.
     * @param pack_function The pack function to use for this frame.
     */
    template <typename U>
    void enqueue_new_CAN(U *structure, uint32_t (*pack_function)(U *, uint8_t *, uint8_t *, uint8_t *));



    /* -------------------- Primary public functions -------------------- */
    /**
     * Main tick() function for this TelemetryInterface. This function's main responsibility is to enqueue
     * the updated CAN frames for the Telemetry CAN line.
     * 
     * // TODO dont pass in pointer to inverter interface here we will break shit with this  -Ben
     */
    void tick(
        const AnalogConversionPacket_s<8> &adc1,
        const AnalogConversionPacket_s<4> &adc2,
        const AnalogConversionPacket_s<4> &adc3,
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



    /* -------------------- Getters -------------------- */
    
    /**
     * Getter for GLV voltage. May or may not belong here, OOP-design-wise. Note that
     * this function does NOT return the glv_voltage of this TelemtryInterface, but
     * rather returns the glv_voltage from the given adc1.
     * @param adc1 The ADC to retrieve the GLV voltage from. This MUST be the the correct ADC.
     * @return The GLV voltage, according to the given ADC.
     */
    AnalogConversion_s get_glv_voltage(const AnalogConversionPacket_s<8> &adc1)
    {
        return adc1.conversions[channels_.glv_sense_channel];
    }

};

#endif /* TELEMETRYINTERFACE */