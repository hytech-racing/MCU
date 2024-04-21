#ifndef __AMSINTERFACE_H__
#define __AMSINTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "hytech.h"

/* Heartbeat Interval is the allowable amount of time between BMS status messages before car delatches */
const unsigned long HEARTBEAT_INTERVAL                      = 2000;   // milliseconds
/* The total pcc threshold is the lowest allowable voltage of the entire pack (in Volts)*/
const unsigned long PACK_CHARGE_CRIT_TOTAL_THRESHOLD        = 420;
/* The lowest pcc threshold is the lowest allowable single cell voltage (in 100 microvolts)*/
const unsigned long PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD  = 35000; //equivalent to 3.5V

const float DEFAULT_INIT_TEMP       = 40.0;
const float DEFAULT_INIT_VOLTAGE    = 3.5;
const float DEFAULT_TEMP_ALPHA      = 0.8;
const float DEFAULT_VOLTAGE_ALPHA   = 0.8;
const uint16_t MAX_PACK_CHARGE      = 48600;


/// @brief this class is for interfacing with the AMS (accumulator management system) 
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
        cell_voltage_alpha(volt_alpha) {};

    /* Overloaded constructor that only takes in software OK pin and uses default voltages and temp*/
    AMSInterface(int sw_ok_pin):
        AMSInterface(sw_ok_pin, DEFAULT_INIT_TEMP, DEFAULT_INIT_VOLTAGE, DEFAULT_TEMP_ALPHA, DEFAULT_VOLTAGE_ALPHA) {};

    /* Initialize the heartbeat timer */
    void init(unsigned long curr_millis);

    /* Init software OK pin by setting high*/
    void set_start_state();

    /* Check if the last heartbeat arrived within allowable interval */
    bool heartbeat_received(unsigned long curr_millis);

    /* Check if either lowest cell or total pack is below threshold*/
    bool pack_charge_is_critical(); 

    void coulomb_counter();

    //SETTERS//    
    /* set software OK pin */
    void set_state_ok_high(bool ok_high);    
    /* set the last heartbeat to the current millis time */
    void set_heartbeat(unsigned long curr_millis);

    //GETTERS//
    /* IIR filter and return filtered max cell temperature */
    float get_filtered_max_cell_temp();
    /* IIR filter and return filtered min cell voltage */
    float get_filtered_min_cell_voltage();

    float initialize_charge();
    float get_SoC_em();
    float get_SoC_acu();
    void tick50();

    //RETRIEVE CAN MESSAGES//
    /* read BMS status messages */
    void retrieve_status_CAN(unsigned long curr_millis, CAN_message_t &recvd_msg);
    /* read BMS temperature messages */
    void retrieve_temp_CAN(CAN_message_t &recvd_msg);
    /* read BMS voltage messages */
    void retrieve_voltage_CAN(CAN_message_t &recvd_msg);
    /* read ACU current shunt messages */
    void read_current_shunt_CAN(const CAN_message_t &can_msg);

private:
    /* Private functions */
    // Check if lowest cell temperature is below threshold
    bool is_below_pack_charge_critical_low_thresh();
    // Check if total pack charge is above threshold
    bool is_below_pack_charge_critical_total_thresh();

    /* AMS CAN messages */
    BMS_status          bms_status_;
    BMS_temperatures    bms_temperatures_;
    BMS_voltages        bms_voltages_;
    ACU_SHUNT_MEASUREMENTS_t         acu_shunt_measurements_;
    EM_MEASUREMENT_t                 em_measurements_;
    BMS_VOLTAGES_t                   low_voltage_ro;

    /* AMS last heartbeat time */
    unsigned long last_heartbeat_time;

    /* software OK pin */
    int pin_software_ok_;

    /* IIR filter parameters */
    float bms_high_temp;
    float bms_low_voltage;
    float filtered_max_cell_temp;
    float filtered_min_cell_voltage;
    float cell_temp_alpha;
    float cell_voltage_alpha;
    float calc_current;
    float shunt_voltage;
    float current;
    float charge;
    float SoC;
    float voltage_lookup_table[101] = {3.972, 3.945, 3.918, 3.891, 3.885, 3.874, 3.864, 3.858, 3.847, 3.836, 3.82, 3.815, 3.815, 3.798, 3.788,
    3.782, 3.771, 3.755, 3.744, 3.744, 3.733, 3.728, 3.723, 3.712, 3,701, 3.695, 3.69, 3.679, 3.679, 3.668, 3.663, 3.657, 3.647,
    3.647, 3.636, 3.625, 3.625, 3.625, 3.614, 3.609, 3.603, 3.603, 3.592, 3.592, 3.592, 3.581, 3.581, 3.571, 3.571, 3.571, 3.56,
    3.56, 3.56, 3.549, 3.549, 3.549, 3.549, 3.538, 3.538, 3.551, 3.546, 3.535, 3.535, 3.535, 3.53, 3.524, 3.524, 3.524, 3.513,
    3.513, 3.513, 3.503, 3.503, 3.492, 3.492, 3.492, 3.487, 3.481, 3.481, 3.476, 3.471, 3.46, 3.46, 3.449, 3.444, 3.428, 3.428,
    3.417, 3.401, 3.39, 3.379, 3.363, 3.331, 3.299, 3.267, 3.213, 3.149, 3.041, 3, 0};
    elapsedMicros CC_integrator_timer = 0;
};

#endif /* __AMSINTERFACE_H__ */
