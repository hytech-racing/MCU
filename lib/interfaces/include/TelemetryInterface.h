#ifndef __TELEMETRY_INTERFACE_H__
#define __TELEMETRY_INTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "SysClock.h"
#include "AnalogSensorsInterface.h"
#include "SteeringEncoderInterface.h"

class TelemetryInterface
{
public:
    TelemetryInterface() = default;

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

    /* Send outbound telemetry CAN messages */    
    void send_CAN_mcu_pedal_readings(CAN_message_t &msg);
    void send_CAN_mcu_load_cells(CAN_message_t &msg);
    void send_CAN_mcu_front_potentiometers(CAN_message_t &msg);
    void send_CAN_mcu_rear_potentiometers(CAN_message_t &msg);
    void send_CAN_mcu_analog_readings(CAN_message_t &msg);

    /* Tick SysClock to send CAN */
    void tick(
        const SysTick_s &tick, 
        CAN_message_t &msg, 
        const AnalogConversionPacket_s<8> &adc1, 
        const AnalogConversionPacket_s<4> &adc2,
        const AnalogConversionPacket_s<4> &adc3,
        const SteeringEncoderConversion_s &encoder
    );

private:
    /* Outbound telemetry CAN messages */
    MCU_pedal_readings          mcu_pedal_readings_;
    MCU_load_cells              mcu_load_cells_;
    MCU_front_potentiometers    mcu_front_potentiometers_;
    MCU_rear_potentiometers     mcu_rear_potentiometers_;
    MCU_analog_readings         mcu_analog_readings_;    
};

#endif /* __TELEMETRY_INTERFACE_H__ */
