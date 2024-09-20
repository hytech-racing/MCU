#ifndef __AMSINTERFACE_H__
#define __AMSINTERFACE_H__

#include "SysClock.h"

#define CANBufferType_mock int
#define CAN_message_t_mock int


/**
 * Mock interface for testing purposes. Please see the real AMSInterface for proper documentation.
*/

const unsigned long HEARTBEAT_INTERVAL                      = 2000;   // milliseconds
const unsigned long PACK_CHARGE_CRIT_TOTAL_THRESHOLD        = 420;
const unsigned long PACK_CHARGE_CRIT_LOWEST_CELL_THRESHOLD  = 35000; //equivalent to 3.5V

const float DEFAULT_INIT_TEMP       = 40.0;
const float DEFAULT_INIT_VOLTAGE    = 3.5;
const float DEFAULT_TEMP_ALPHA      = 0.8;
const float DEFAULT_VOLTAGE_ALPHA   = 0.8;
const unsigned short MAX_PACK_CHARGE      = 48600;
const unsigned long DEFAULT_INITIALIZATION_WAIT_INTERVAL = 5000;

class AMSInterface
{
public:

    AMSInterface(CANBufferType_mock *msg_output_queue, int sw_ok_pin, float init_temp, float init_volt, float temp_alpha, float volt_alpha):        
        msg_queue_(msg_output_queue),
        pin_software_ok_(sw_ok_pin),
        filtered_max_cell_temp(init_temp),
        filtered_min_cell_voltage(init_volt),
        cell_temp_alpha(temp_alpha),
        cell_voltage_alpha(volt_alpha),
        use_em_for_soc_(true),
        charge_(0.0f),
        SoC_(0.0f),
        has_initialized_charge_(false),
        has_received_bms_voltage_(false) {};

    AMSInterface(CANBufferType_mock *msg_output_queue, int sw_ok_pin):
        AMSInterface(msg_output_queue, sw_ok_pin, DEFAULT_INIT_TEMP, DEFAULT_INIT_VOLTAGE, DEFAULT_TEMP_ALPHA, DEFAULT_VOLTAGE_ALPHA) {};


    void init(SysTick_s &initial_tick) {};
    void set_start_state() {};
    bool heartbeat_received(unsigned long curr_millis) {return ((curr_millis - last_heartbeat_time_) < HEARTBEAT_INTERVAL);};
    bool pack_charge_is_critical() {};

    //SETTERS//    
    void set_state_ok_high(bool ok_high) {};
    void set_heartbeat(unsigned long curr_millis) {last_heartbeat_time_ = curr_millis;};

    //GETTERS//
    float get_filtered_max_cell_temp() {};
    float get_filtered_min_cell_voltage() {};
    float get_acc_derate_factor() {};

    float initialize_charge() {};
    void calculate_SoC_em(const SysTick_s &tick) {};
    void calculate_SoC_acu(const SysTick_s &tick) {};
    float get_SoC() {return SoC_;}
    void tick(const SysTick_s &tick) {};

    void retrieve_status_CAN(unsigned long curr_millis, CAN_message_t_mock &recvd_msg) {};
    void retrieve_temp_CAN(CAN_message_t_mock &recvd_msg) {};
    void retrieve_voltage_CAN(CAN_message_t_mock &recvd_msg) {};
    void calculate_acc_derate_factor() {};

    void retrieve_em_measurement_CAN(CAN_message_t_mock &can_msg) {};
    void retrieve_current_shunt_CAN(const CAN_message_t_mock &can_msg) {};
    bool is_using_em_for_soc() {return use_em_for_soc_;}
    void set_use_em_for_soc(bool new_use_em_for_soc) {
        use_em_for_soc_ = new_use_em_for_soc;
    }
    void enqueue_state_of_charge_CAN() {};

    /** Helper function to enqueue CAN messages using the new CAN library*/
    //template <typename U>
    //void enqueue_new_CAN(U *structure, uint32_t (*pack_function)(U *, uint8_t *, uint8_t *, uint8_t *));

    // Getters (for testing purposes)
    //BMS_VOLTAGES_t get_bms_voltages() {return bms_voltages_;}
    //EM_MEASUREMENT_t get_em_measurements() {return em_measurements_;}
    //ACU_SHUNT_MEASUREMENTS_t get_acu_shunt_measurements() {return acu_shunt_measurements_;}
    

private:

    const float VOLTAGE_LOOKUP_TABLE[101] = {3.972, 3.945, 3.918, 3.891, 3.885, 3.874, 3.864, 3.858, 3.847, 3.836, 3.82, 3.815, 3.815, 3.798, 3.788,
    3.782, 3.771, 3.755, 3.744, 3.744, 3.733, 3.728, 3.723, 3.712, 3.701, 3.695, 3.69, 3.679, 3.679, 3.668, 3.663, 3.657, 3.647,
    3.647, 3.636, 3.625, 3.625, 3.625, 3.614, 3.609, 3.603, 3.603, 3.592, 3.592, 3.592, 3.581, 3.581, 3.571, 3.571, 3.571, 3.56,
    3.56, 3.56, 3.549, 3.549, 3.549, 3.549, 3.538, 3.538, 3.551, 3.546, 3.535, 3.535, 3.535, 3.53, 3.524, 3.524, 3.524, 3.513,
    3.513, 3.513, 3.503, 3.503, 3.492, 3.492, 3.492, 3.487, 3.481, 3.481, 3.476, 3.471, 3.46, 3.46, 3.449, 3.444, 3.428, 3.428,
    3.417, 3.401, 3.39, 3.379, 3.363, 3.331, 3.299, 3.267, 3.213, 3.149, 3.041, 3, 3, 0};

    CANBufferType_mock *msg_queue_;

    /* software OK pin */
    int pin_software_ok_;

    /* AMS CAN messages */
    //BMS_status          bms_status_;
    //BMS_temperatures    bms_temperatures_;
    //ACU_SHUNT_MEASUREMENTS_t         acu_shunt_measurements_;
    //EM_MEASUREMENT_t                 em_measurements_;
    //BMS_VOLTAGES_t                   bms_voltages_;

    /* AMS last heartbeat time */
    unsigned long last_heartbeat_time_;

    /* IIR filter parameters */
    float bms_high_temp;
    float bms_low_voltage;
    float filtered_max_cell_temp;
    float filtered_min_cell_voltage;
    float cell_temp_alpha;
    float cell_voltage_alpha;
    
    float acc_derate_factor;
    bool use_em_for_soc_ = true;
    float charge_;
    float SoC_;
    SysTick_s last_tick_;
    bool has_initialized_charge_;
    bool has_received_bms_voltage_;
    unsigned long timestamp_start_;

    bool is_below_pack_charge_critical_low_thresh();
    bool is_below_pack_charge_critical_total_thresh();

};

#endif /* __AMSINTERFACE_H__ */