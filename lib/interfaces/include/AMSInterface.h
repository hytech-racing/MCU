#ifndef AMSINTERFACE
#define AMSINTERFACE

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"

/* Heartbeat Interval is the allowable amount of time between BMS status messages before car delatches */
const unsigned long HEARTBEAT_INTERVAL                      = 20;   // milliseconds
/* The total pcc threshold is the lowest allowable voltage of the entire pack (in Volts)*/
const unsigned long PACK_CHARGE_CRIT_TOTAL_THRESHOLD        = 420;
/* The lowest pcc threshold is the lowest allowable single cell voltage (in 100 microvolts)*/
const unsigned long PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD  = 35000; //equivalent to 3.5V

const float DEFAULT_INIT_TEMP       = 40.0;
const float DEFAULT_INIT_VOLTAGE    = 3.5;
const float DEFAULT_TEMP_ALPHA      = 0.8;
const float DEFAULT_VOLTAGE_ALPHA   = 0.8;

class AMSInterface
{
public:
    /*!
        Constructor for the AMS Interface
        @param sw_ok_pin The software ok pin number.
        This pin is connected to the shutdown line and will go low if the AMS times out
    */
    AMSInterface(int sw_ok_pin, float init_temp, float init_volt, float temp_alpha, float volt_alpha):        
        pin_software_ok_(sw_ok_pin),
        filtered_max_cell_temp(init_temp),
        filtered_min_cell_voltage(init_volt),
        cell_temp_alpha(temp_alpha),
        cell_voltage_alpha(volt_alpha)
    {
        // Set pin mode
        pinMode(pin_software_ok_, OUTPUT);
    }

    /* Overloaded constructor that only takes in software OK pin, and uses default voltages and temp*/
    AMSInterface(int sw_ok_pin):
        AMSInterface(sw_ok_pin, DEFAULT_INIT_TEMP, DEFAULT_INIT_VOLTAGE, DEFAULT_TEMP_ALPHA, DEFAULT_VOLTAGE_ALPHA) {};

    /* Initialize the heartbeat timer */
    void init(unsigned long curr_millis);

    /* Write to Main ECU */

    /* Init software OK pin by setting high*/
    void set_start_state();

    /* set software OK pin */
    void set_state_ok_high(bool ok_high);
    
    /* Monitor AMS state */
    void set_heartbeat(unsigned long curr_millis);
    bool heartbeat_received(unsigned long curr_millis);
    bool is_below_pack_charge_critical_low_thresh();
    bool is_below_pack_charge_critical_total_thresh();
    bool pack_charge_is_critical();    

    /* IIR filtered AMS readings */
    float get_filtered_max_cell_temp();
    float get_filtered_min_cell_voltage();

    /* Retrieve CAN */
    void retrieve_status_CAN(unsigned long millis, CAN_message_t &recvd_msg);
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

#endif /* AMSINTERFACE */
