#ifndef __AMS_INTERFACE_H__
#define __AMS_INTERFACE_H__

#include "MCUInterface.h"
#include "HyTech_CAN.h"

#define HEARTBEAT_INTERVAL                      20   // milliseconds
#define PACK_CHARGE_CRIT_TOTAL_THRESHOLD        420
#define PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD  35000

#define SOFTWARE_OK     28

class AMSInterface
{
public:
    AMSInterface(float init_temp=40.0, float init_volt=3.5, float temp_alpha=0.8, float volt_alpha=0.8):        
        filtered_max_cell_temp(init_temp),
        filtered_min_cell_voltage(init_volt),
        cell_temp_alpha(temp_alpha),
        cell_voltage_alpha(volt_alpha) 
    {
        last_heartbeat_time = millis();
    }

    /* Initialize interface pin mode */
    void init();

    /* Write to Main ECU */
    // Initialize output value
    void set_start_state();
    // Set output value
    void set_state_ok_high(bool ok_high);
    
    /* Monitor AMS state */
    void set_heartbeat(unsigned long curr_time);
    bool heartbeat_received(unsigned long curr_time);
    bool is_below_pack_charge_critical_low_thresh();
    bool is_below_pack_charge_critical_total_thresh();
    bool pack_charge_is_critical();    

    /* IIR filtered AMS readings */
    float get_filtered_max_cell_temp();
    float get_filtered_min_cell_voltage();

    /* Retrieve CAN */
    void retrieve_coulomb_count_CAN(CAN_message_t &recvd_msg);
    void retrieve_status_CAN(CAN_message_t &recvd_msg);
    void retrieve_temp_CAN(CAN_message_t &recvd_msg);
    void retrieve_voltage_CAN(CAN_message_t &recvd_msg);

    /* Send CAN */
    void send_CAN_bms_coulomb_counts(CAN_message_t &msg);

private:
    /* Private utility functions */
    update_CAN_msg();

    /* AMS CAN messages */
    // Inbound and outbound (not sure why, need to double check with Liwei)
    BMS_coulomb_counts  bms_coulomb_counts_;
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
};

#endif /* __AMS_INTERFACE_H__ */
