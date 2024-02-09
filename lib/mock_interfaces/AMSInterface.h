#ifndef __AMS_INTERFACE_H__
#define __AMS_INTERFACE_H__

#include "SysClock.h"

const unsigned long HEARTBEAT_INTERVAL                      = 20;   // milliseconds
const unsigned long PACK_CHARGE_CRIT_TOTAL_THRESHOLD        = 420;
const unsigned long PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD  = 35000;

const float DEFAULT_INIT_TEMP       = 40.0;
const float DEFAULT_INIT_VOLTAGE    = 3.5;
const float DEFAULT_TEMP_ALPHA      = 0.8;
const float DEFAULT_VOLTAGE_ALPHA   = 0.8;

class AMSInterface
{
public:
    AMSInterface(int sw_ok_pin, float init_temp, float init_volt, float temp_alpha, float volt_alpha){
        // Set pin mode
    };
        /* Initialize interface pin mode */
    void init();

    /* Write to Main ECU */
    // Initialize output value
    void set_start_state();
    // Set output value
    void set_state_ok_high(bool ok_high);
    
    /* Monitor AMS state */
    void set_heartbeat();
    bool heartbeat_received();
    bool is_below_pack_charge_critical_low_thresh();
    bool is_below_pack_charge_critical_total_thresh();
    bool pack_charge_is_critical();    

    /* IIR filtered AMS readings */
    float get_filtered_max_cell_temp();
    float get_filtered_min_cell_voltage();

    /* Retrieve CAN */
private:
    /* AMS CAN messages */
    // Outbound
};

#endif /* __AMS_INTERFACE_H__ */
