#include "AMSSystem.h"
#include "SysClock.h"

float currentfromS(float x){
    return (x * 0.000015259) + 0.0f;
}

float currentshuntfromS(float x){
    return (x * 0.291373985) + (-666.0f);
}

float lowvoltagefromS(float x) {
    return (x * 0.0001f) + 0.0f;
} 

AMSSystem::AMSSystem() {
    // Initialize BMS voltages to an invalid state
    bms_voltages_.low_voltage_ro = 0xFFFFU;
    charge_ = 0;
    SoC_ = 0;
    has_initialized_charge_ = false;
    last_tick_ = {0, 0};  // Initialize the last tick time
    use_em_for_soc_ = true;  // Example: assuming EM measurements are used for SoC
}

// Initialize the charge based on the BMS low voltage
float AMSSystem::initialize_charge() {
    // Step 1: Retrieve the lowest voltage from the Battery Management System (BMS)
    float min_voltage = static_cast<float>(bms_voltages_.low_voltage_ro) * 0.0001f;  // Convert to float using factor

    // Step 2: Use the lowest voltage with the VOLTAGE_LOOKUP_TABLE to determine the percentage charge
    int percentage_charge = 0;
    for (int i = 0; i < 101; ++i) {
        if (min_voltage >= VOLTAGE_LOOKUP_TABLE[i]) {
            percentage_charge = 100 - i;
            break;
        }
    }

    // Step 3: Initialize the charge_ and SoC_ member variables
    charge_ = static_cast<float>(percentage_charge) / 100.0f;
    SoC_ = percentage_charge;

    // Step 4: Return the current charge
    return charge_;
}

// Tick function to handle SoC updates based on time and conditions
void AMSSystem::tick(const SysTick_s &tick) {
    // Only calculate the updated SoC if charge has been properly initialized.
    if (has_initialized_charge_) {
        if (use_em_for_soc_) {
            calculate_SoC_em(tick);  // Use em measurements to calculate SoC
        } else {
            calculate_SoC_acu(tick);  // Use ACU measurements to calculate SoC
        }
    }

    // Initialize charge if it hasn't been initialized yet and sufficient time has passed since start
    if (!has_initialized_charge_ && ((tick.millis - timestamp_start_) >= DEFAULT_INITIALIZATION_WAIT_INTERVAL)) {
        // Initialize charge based on the BMS voltage data
        initialize_charge();
        has_initialized_charge_ = true;
    }

    last_tick_ = tick;  // Update the last tick time
}

// Calculate the SoC based on the em measurements
void AMSSystem::calculate_SoC_em(const SysTick_s &tick) {
    unsigned long delta_time_micros = tick.micros - last_tick_.micros;
    float current = currentfromS(em_measurements_.em_current_ro);  // Current in amps
    charge_ -= (current * delta_time_micros) / 1000000;  // Coulombs = amps * microseconds / 1e6
    SoC_ = (charge_ / MAX_PACK_CHARGE) * 100;  // Update SoC percentage
}

// Calculate the SoC based on the ACU measurements
void AMSSystem::calculate_SoC_acu(const SysTick_s &tick) {
    unsigned long delta_time_micros = tick.micros - last_tick_.micros;
    charge_ -= (currentshuntfromS(acu_shunt_measurements_.current_shunt_read_ro) * delta_time_micros) / 1000000;
    SoC_ = (charge_ / MAX_PACK_CHARGE) * 100;  // Update SoC percentage
}

// Perform calculations for derating factor based on temperature and voltage limits
void AMSSystem::calculate_acc_derate_factor() {
    float voltage_lim_factor = map_range(get_filtered_min_cell_voltage(), 3.5, 3.2, 1.0, 0.2);
    float temp_lim_factor = map_range(get_filtered_max_cell_temp(), 50, 58, 1.0, 0.2);

    acc_derate_factor = std::min(temp_lim_factor, voltage_lim_factor);
}

// Return the derate factor after calculation
float AMSSystem::get_acc_derate_factor() {
    calculate_acc_derate_factor();
    return acc_derate_factor;
}

// Helper function to map values from one range to another
float AMSSystem::map_range(float value, float in_min, float in_max, float out_min, float out_max) {
    return std::max(std::min((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min, out_max), out_min);
}

// Getter for filtered maximum cell temperature
float AMSSystem::get_filtered_max_cell_temp() {
    bms_high_temp = bms_temperatures_.high_temperature / 100.0;
    filtered_max_cell_temp = filtered_max_cell_temp * cell_temp_alpha + (1.0 - cell_temp_alpha) * bms_high_temp;
    return filtered_max_cell_temp;
}

// Getter for filtered minimum cell voltage
float AMSSystem::get_filtered_min_cell_voltage() {
    bms_low_voltage = lowvoltagefromS(bms_voltages_.low_voltage_ro);
    filtered_min_cell_voltage = filtered_min_cell_voltage * cell_voltage_alpha + (1.0 - cell_voltage_alpha) * bms_low_voltage;
    return filtered_min_cell_voltage;
}
