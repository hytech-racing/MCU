#ifndef __AMS_INTERFACE_H__
#define __AMS_INTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "SysClock.h"

#define HEARTBEAT_INTERVAL                      20   // milliseconds
#define PACK_CHARGE_CRIT_TOTAL_THRESHOLD        420
#define PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD  35000

#define DEFAULT_INIT_TEMP       40.0
#define DEFAULT_INIT_VOLTAGE    3.5
#define DEFAULT_TEMP_ALPHA      0.8
#define DEFAULT_VOLTAGE_ALPHA   0.8

#define DEFAULT_SOFTWARE_OK 28

class AMSInterface
{
public:
    AMSInterface(int sw_ok_pin, float init_temp, float init_volt, float temp_alpha, float volt_alpha):        
        pin_software_ok_(sw_ok_pin),
        filtered_max_cell_temp(init_temp),
        filtered_min_cell_voltage(init_volt),
        cell_temp_alpha(temp_alpha),
        cell_voltage_alpha(volt_alpha) {};
    AMSInterface(int sw_ok_pin):
        AMSInterface(sw_ok_pin, DEFAULT_INIT_TEMP, DEFAULT_INIT_VOLTAGE, DEFAULT_TEMP_ALPHA, DEFAULT_VOLTAGE_ALPHA) {};
    AMSInterface():
        AMSInterface(DEFAULT_SOFTWARE_OK) {};

    /* Initialize interface pin mode */
    void init(const SysTick_s &tick);

    /* Write to Main ECU */
    // Initialize output value
    void set_start_state();
    // Set output value
    void set_state_ok_high(bool ok_high);
    
    /* Monitor AMS state */
    void set_heartbeat(const SysTick_s &tick);
    bool heartbeat_received(const SysTick_s &tick);
    bool is_below_pack_charge_critical_low_thresh();
    bool is_below_pack_charge_critical_total_thresh();
    bool pack_charge_is_critical();    

    /* IIR filtered AMS readings */
    float get_filtered_max_cell_temp();
    float get_filtered_min_cell_voltage();

    /* Retrieve CAN */
    void retrieve_coulomb_count_CAN(CAN_message_t &recvd_msg);
    void retrieve_status_CAN(CAN_message_t &recvd_msg, const SysTick_s &tick);
    void retrieve_temp_CAN(CAN_message_t &recvd_msg);
    void retrieve_voltage_CAN(CAN_message_t &recvd_msg);

private:
    /* AMS CAN messages */
    // Outbound
    BMS_status          bms_status_;
    BMS_temperatures    bms_temperatures_;
    BMS_voltages        bms_voltages_;

    /* AMS heartbeat check */
    unsigned long last_heartbeat_time;

    /* IIR filter parameters */
    float bms_high_temp;
    float bms_low_voltage;
    float filtered_max_cell_temp;
    float filtered_min_cell_voltage;
    float cell_temp_alpha;
    float cell_voltage_alpha;

    /* Hardware interface pins */
    int pin_software_ok_;
};

#endif /* __AMS_INTERFACE_H__ */
