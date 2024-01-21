#ifndef __TELEMETRY_INTERFACE_H__
#define __TELEMETRY_INTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

class TelemetryInterface
{
public:
    TelemetryInterface() = default;

    void send_CAN_mcu_pedal_readings(CAN_message_t &msg);
    void send_CAN_mcu_load_cells(CAN_message_t &msg);
    void send_CAN_mcu_front_potentiometers(CAN_message_t &msg);
    void send_CAN_mcu_rear_potentiometers(CAN_message_t &msg);
    void send_CAN_mcu_analog_readings(CAN_message_t &msg);

private:
    MCU_pedal_readings          *mcu_pedal_readings_;
    MCU_load_cells              *mcu_load_cells_;
    MCU_front_potentiometers    *mcu_front_potentiometers_;
    MCU_rear_potentiometers     *mcu_rear_potentiometers_;
    MCU_analog_readings         *mcu_analog_readings_;    

};





#endif /* __TELEMETRY_INTERFACE_H__ */
