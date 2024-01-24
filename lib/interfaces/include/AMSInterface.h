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
    AMSInterface(MCUInterface *mcu): 
        mcu_(mcu),
        last_heartbeat_time(time),
        filtered_max_cell_temp(40.0),
        filtered_min_cell_voltage(3.5),
        cell_temp_alpha(0.8),
        cell_voltage_alpha(0.8) {};

    void init();

    void set_start_state();
    void set_state_ok_high(bool ok_high);

    void set_software_is_ok(bool is_ok);
    bool software_is_ok();
    
    bool ok_high();
    bool heartbeat_received(unsigned long curr_time);
    bool is_below_pack_charge_critical_low_thresh();
    bool is_below_pack_charge_critical_total_thresh();
    bool pack_charge_is_critical();

    void set_pack_charge_critical(bool is_critical);
    static void set_heartbeat(unsigned long curr_time);

    float get_filtered_max_cell_temp();
    float get_filtered_min_cell_voltage();

    void retrieve_coulomb_count_CAN(BMS_coulomb_counts bms_coulomb_counts);
    void retrieve_status_CAN(BMS_status bms_status);
    void retrieve_temp_CAN(BMS_temperatures bms_temperatures);
    void retrieve_voltage_CAN(BMS_voltages bms_voltages);

    void send_CAN_bms_coulomb_counts(CAN_message_t &msg);

private:
    /* Private utility functions */
    update_CAN_msg();

    /* AMS CAN messages */
    BMS_coulomb_counts  bms_coulomb_counts_;
    BMS_status          bms_status_;
    BMS_temperatures    bms_temperatures_;
    BMS_voltages        bms_voltages_;
    /* Software OK status */
    bool software_is_ok;

    /* AMS heartbeat check */
    static unsigned long last_heartbeat_time;
    /* Power limiting data */
    float bms_high_temp;
    float bms_low_voltage;
    float filtered_max_cell_temp;
    float filtered_min_cell_voltage;
    float cell_temp_alpha;
    float cell_voltage_alpha;
};

#endif /* __AMS_INTERFACE_H__ */
