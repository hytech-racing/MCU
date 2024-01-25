#ifndef __TELEMETRY_INTERFACE_H__
#define __TELEMETRY_INTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

class TelemetryInterface
{
public:
    TelemetryInterface() = default;

    /* Update CAN messages (main loop) */
    // Interfaces
    void update_pedal_readings_CAN_msg();
    void update_load_cells_CAN_msg();
    void update_potentiometers_CAN_msg();
    void update_analog_readings_CAN_msg();

    /* Send outbound telemetry CAN messages */    
    void send_CAN_mcu_pedal_readings(CAN_message_t &msg);
    void send_CAN_mcu_load_cells(CAN_message_t &msg);
    void send_CAN_mcu_front_potentiometers(CAN_message_t &msg);
    void send_CAN_mcu_rear_potentiometers(CAN_message_t &msg);
    void send_CAN_mcu_analog_readings(CAN_message_t &msg);

private:
    /* Outbound telemetry CAN messages */
    MCU_pedal_readings          mcu_pedal_readings_;
    MCU_load_cells              mcu_load_cells_;
    MCU_front_potentiometers    mcu_front_potentiometers_;
    MCU_rear_potentiometers     mcu_rear_potentiometers_;
    MCU_analog_readings         mcu_analog_readings_;    
};

#endif /* __TELEMETRY_INTERFACE_H__ */
