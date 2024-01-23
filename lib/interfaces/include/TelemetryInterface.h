#ifndef __TELEMETRY_INTERFACE_H__
#define __TELEMETRY_INTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

#include "AnalogSensor.h"
#include "UpperSteeringSensor.h"

class TelemetryInterface
{
public:
    TelemetryInterface(AnalogMultiSensor *adc, UpperSteeringSensor *digital_steering):
        adc_(adc),
        digital_steering_(digital_steering) {};

    void send_CAN_mcu_pedal_readings(CAN_message_t &msg);
    void send_CAN_mcu_load_cells(CAN_message_t &msg);
    void send_CAN_mcu_front_potentiometers(CAN_message_t &msg);
    void send_CAN_mcu_rear_potentiometers(CAN_message_t &msg);
    void send_CAN_mcu_analog_readings(CAN_message_t &msg);

private:
    /* Utility helper functions */
    update_pedal_readings_CAN_msg();
    update_load_cells_CAN_msg();
    update_front_pots_CAN_msg();
    update_rear_pots_CAN_msg();
    update_analog_readings_CAN_msg();

    /* Outbound telemetry CAN messages */
    MCU_pedal_readings          mcu_pedal_readings_;
    MCU_load_cells              mcu_load_cells_;
    MCU_front_potentiometers    mcu_front_potentiometers_;
    MCU_rear_potentiometers     mcu_rear_potentiometers_;
    MCU_analog_readings         mcu_analog_readings_;    

    /* Associated interfaces */
    AnalogMultiSensor *adc_;
    UpperSteeringSensor *digital_steering_;
};





#endif /* __TELEMETRY_INTERFACE_H__ */
