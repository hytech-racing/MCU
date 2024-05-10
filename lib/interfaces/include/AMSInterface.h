#ifndef __AMSINTERFACE_H__
#define __AMSINTERFACE_H__

#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "SysClock.h"
#include "hytech.h"
#include "MessageQueueDefine.h"

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
    AMSInterface(CANBufferType *msg_output_queue, int sw_ok_pin, float init_temp, float init_volt, float temp_alpha, float volt_alpha):        
        msg_queue_(msg_output_queue),
        pin_software_ok_(sw_ok_pin),
        filtered_max_cell_temp(init_temp),
        filtered_min_cell_voltage(init_volt),
        cell_temp_alpha(temp_alpha),
        cell_voltage_alpha(volt_alpha),
        use_em_for_soc_(true),
        charge_(0.0f),
        SoC_(0.0f),
        has_initialized_charge_(false) {};

    /* Overloaded constructor that only takes in software OK pin and uses default voltages and temp*/
    AMSInterface(CANBufferType *msg_output_queue, int sw_ok_pin):
        AMSInterface(msg_output_queue, sw_ok_pin, DEFAULT_INIT_TEMP, DEFAULT_INIT_VOLTAGE, DEFAULT_TEMP_ALPHA, DEFAULT_VOLTAGE_ALPHA) {};

    /* Initialize the heartbeat timer */
    void init(SysTick_s &initial_tick);

    /* Init software OK pin by setting high*/
    void set_start_state();

    /* Check if the last heartbeat arrived within allowable interval */
    bool heartbeat_received(unsigned long curr_millis);

    /* Check if either lowest cell or total pack is below threshold*/
    bool pack_charge_is_critical(); 

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

    /**
     * Initializes the charge member variable from the voltage of the minimum cell using the VOLTAGE_LOOKUP_TABLE.
     * 
     * @pre The bms_voltages_ member variable MUST be initialized before this function can be called.
     * @return The charge, in coulombs, that the charge member variable is initialized to.
    */
    float initialize_charge();

    /**
     * Calculates SoC based on the energy meter CAN message. Calling calculate_SoC_em()
     * will update the SoC_ and charge_ member variables.
     * 
     * @param The current tick that the calculate_SoC_em function should use for integration.
     * 
     * @pre The last_tick_ member variable must be updated correctly.
     * @post The charge_ field has the updated charge, and the SoC field contains an updated percentage.
    */
    void calculate_SoC_em(const SysTick_s &tick);

    /**
     * Calculates SoC based on the ACU_SHUNT_MEASUREMENTS CAN message. Calling calculate_SoC_acu()
     * will update the SoC_ and charge_ member variables.
     * 
     * @param The current tick that the calculate_SoC_em function should use for integration.
     * 
     * @pre The last_tick_ member variable must be updated correctly.
     * @post The charge_ field has the updated charge, and the SoC field contains an updated percentage.
    */
    void calculate_SoC_acu(const SysTick_s &tick);

    /**
     * Retrieves the value of the SoC member variable. This function does NOT recalculate
     * the SoC_ variable, it only returns the value that is stored.
     * 
     * @return the current value stored in the SoC_ member variable.
    */
    float get_SoC() {return SoC_;}

    /**
     * This is AMSInterface's tick() function. It behaves correctly regardless of the
     * since the functions calculate the elapsed time between the given tick and the stored last_tick_.
     * 
     * @param tick The current system tick.
    */
    void tick(const SysTick_s &tick);

    //RETRIEVE CAN MESSAGES//
    
    /**
     * Reads this CAN message into the bms_status_ member variable. This function uses the OLD CAN library.
     */
    void retrieve_status_CAN(unsigned long curr_millis, CAN_message_t &recvd_msg);
    
    /**
     * Reads this CAN message into the bms_temperatures_ member variable. This function uses the OLD CAN library.
     */
    void retrieve_temp_CAN(CAN_message_t &recvd_msg);
    
    /**
     * Reads this CAN message into the bms_voltages_ member variable. This function
     * does NOT apply the fromS() functions on the data. This function uses the NEW CAN library.
     */
    void retrieve_voltage_CAN(CAN_message_t &recvd_msg);
    
    /**
     * Reads this CAN message into the em_measurements_ member variable. This function
     * does NOT apply the fromS() functions on the data. This function uses the NEW CAN library.
     */
    void retrieve_em_measurement_CAN(CAN_message_t &can_msg);

    /**
     * Reads this CAN message into the acu_shunt_measurements_ member variable. This function
     * does NOT apply the fromS() functions on the data. This function uses the NEW CAN library.
     */
    void retrieve_current_shunt_CAN(const CAN_message_t &can_msg);

    /**
     * Retrieves the current state of the use_em_for_soc member variable.
     * @return True if using EM, false if using ACU shunt measurements.
     */
    bool is_using_em_for_soc() {return use_em_for_soc_;}

    /**
     * Setter function for the use_em_for_soc_ member variable.
     * @param new_use_em_for_soc The new value for the variable.
     */
    void set_use_em_for_soc(bool new_use_em_for_soc) {
        use_em_for_soc_ = new_use_em_for_soc;
    }

    /**
     * Puts the current value of SoC_ and charge_ onto msg_queue_.
    */
    void enqueue_state_of_charge_CAN();

    /** Helper function to enqueue CAN messages using the new CAN library*/
    template <typename U>
    void enqueue_new_CAN(U *structure, uint32_t (*pack_function)(U *, uint8_t *, uint8_t *, uint8_t *));

    // Getters (for testing purposes)
    BMS_VOLTAGES_t get_bms_voltages() {return bms_voltages_;}
    EM_MEASUREMENT_t get_em_measurements() {return em_measurements_;}
    ACU_SHUNT_MEASUREMENTS_t get_acu_shunt_measurements() {return acu_shunt_measurements_;}
    

private:

    const float VOLTAGE_LOOKUP_TABLE[101] = {3.972, 3.945, 3.918, 3.891, 3.885, 3.874, 3.864, 3.858, 3.847, 3.836, 3.82, 3.815, 3.815, 3.798, 3.788,
    3.782, 3.771, 3.755, 3.744, 3.744, 3.733, 3.728, 3.723, 3.712, 3.701, 3.695, 3.69, 3.679, 3.679, 3.668, 3.663, 3.657, 3.647,
    3.647, 3.636, 3.625, 3.625, 3.625, 3.614, 3.609, 3.603, 3.603, 3.592, 3.592, 3.592, 3.581, 3.581, 3.571, 3.571, 3.571, 3.56,
    3.56, 3.56, 3.549, 3.549, 3.549, 3.549, 3.538, 3.538, 3.551, 3.546, 3.535, 3.535, 3.535, 3.53, 3.524, 3.524, 3.524, 3.513,
    3.513, 3.513, 3.503, 3.503, 3.492, 3.492, 3.492, 3.487, 3.481, 3.481, 3.476, 3.471, 3.46, 3.46, 3.449, 3.444, 3.428, 3.428,
    3.417, 3.401, 3.39, 3.379, 3.363, 3.331, 3.299, 3.267, 3.213, 3.149, 3.041, 3, 3, 0};

    /**
     * CAN line that this AMSInterface should write to. This should be the Telemetry CAN line.
    */
    CANBufferType *msg_queue_;

    /* software OK pin */
    int pin_software_ok_;

    /* AMS CAN messages */
    BMS_status          bms_status_;
    BMS_temperatures    bms_temperatures_;
    ACU_SHUNT_MEASUREMENTS_t         acu_shunt_measurements_;
    EM_MEASUREMENT_t                 em_measurements_;
    BMS_VOLTAGES_t                   bms_voltages_;

    /* AMS last heartbeat time */
    unsigned long last_heartbeat_time_;

    /* IIR filter parameters */
    float bms_high_temp;
    float bms_low_voltage;
    float filtered_max_cell_temp;
    float filtered_min_cell_voltage;
    float cell_temp_alpha;
    float cell_voltage_alpha;

    /**
     * If set to TRUE, then SoC will use EM.
     * If set to FALSE, then SoC will use ACU SHUNT.
     * Set to TRUE in constructor by default.
     */
    bool use_em_for_soc_ = true;

    /**
     * The charge stored on the accumulator. Stored in coulombs, ranging from
     * zero to MAX_PACK_CHARGE.
    */
    float charge_;

    /**
     * Stores the current state of charge of the accumulator. SoC is stored as a
     * percentage of MAX_PACK_CHARGE. In every location, this is calculated as
     * SoC = (charge / MAX_PACK_CHARGE) * 100;
    */
    float SoC_;
    
    /**
     * Stores the last Sys_Tick_s struct from the last time the tick() function is called.
    */
    SysTick_s last_tick_;

    /**
     * Stores whether or not this AMSInterface has initialized SoC_ or not.
    */
   bool has_initialized_charge_;


    // Check if lowest cell temperature is below threshold
    bool is_below_pack_charge_critical_low_thresh();
    // Check if total pack charge is above threshold
    bool is_below_pack_charge_critical_total_thresh();

};

#endif /* __AMSINTERFACE_H__ */
