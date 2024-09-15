#ifndef AMS_SYSTEM_TEST
#define AMS_SYSTEM_TEST

#include <gtest/gtest.h>
#include "AMSSystem.h"

// Test initialization of charge based on BMS low voltage
TEST(AMSSystemTest, test_initialize_charge) {
    AMSSystem system;

    system.bms_voltages_.low_voltage_ro = 38000;  // Test with valid low voltage
    float charge = system.initialize_charge();
    ASSERT_EQ(system.SoC_, 87);  // Expected SoC after initialization

    system.bms_voltages_.low_voltage_ro = 0;  // Test with invalid low voltage
    charge = system.initialize_charge();
    ASSERT_EQ(system.SoC_, 0);  // Expected SoC for zero voltage
}

// Test the filtered maximum cell temperature calculation
TEST(AMSSystemTest, test_get_filtered_max_cell_temp) {
    AMSSystem system;

    system.bms_temperatures_.high_temperature = 5000;  // Test with a high temperature value (50.00°C)
    system.cell_temp_alpha = 0.8;
    system.filtered_max_cell_temp = 40.0;  // Initialize with a base value

    float temp = system.get_filtered_max_cell_temp();
    ASSERT_NEAR(temp, 42.0, 0.1);  // Check the temperature filtering with alpha factor
}

// Test the filtered minimum cell voltage calculation
TEST(AMSSystemTest, test_get_filtered_min_cell_voltage) {
    AMSSystem system;

    system.bms_voltages_.low_voltage_ro = 35000;  // Example low voltage (3.5V)
    system.cell_voltage_alpha = 0.9;
    system.filtered_min_cell_voltage = 3.6;  // Initialize with a base value

    float voltage = system.get_filtered_min_cell_voltage();
    ASSERT_NEAR(voltage, 3.59, 0.01);  // Check the voltage filtering with alpha factor
}

// Test acceleration derating factor calculation
TEST(AMSSystemTest, test_calculate_acc_derate_factor) {
    AMSSystem system;

    system.cell_temp_alpha = 0.9;
    system.cell_voltage_alpha = 0.9;
    system.bms_voltages_.low_voltage_ro = 33000;  // Test with voltage (3.3V)
    system.bms_temperatures_.high_temperature = 5500;  // Test with temperature (55.0°C)

    system.filtered_max_cell_temp = system.get_filtered_max_cell_temp();
    system.filtered_min_cell_voltage = system.get_filtered_min_cell_voltage();
    system.calculate_acc_derate_factor();

    ASSERT_NEAR(system.get_acc_derate_factor(), 1.0, 0.1); 
}


TEST(AMSSystemTest, test_tick_function_initialization) {
    AMSSystem system;

    system.timestamp_start_ = 0;
    system.bms_voltages_.low_voltage_ro = 38000;  
    system.has_initialized_charge_ = false;

    SysTick_s tick = {6000, 0}; 

    system.tick(tick);

    ASSERT_TRUE(system.has_initialized_charge_); 
    ASSERT_EQ(system.SoC_, 87); 
}

TEST(AMSSystemTest, test_tick_function_SoC_update_em) {
    AMSSystem system;

    system.has_initialized_charge_ = true;
    system.use_em_for_soc_ = true;
    system.charge_ = 100;  
    system.em_measurements_.em_current_ro = 10000;  
    system.last_tick_ = {0, 0};  

    SysTick_s tick = {0, 1000000};  

    system.tick(tick);

    ASSERT_NEAR(system.SoC_, 0.21, 0.1); 
}

TEST(AMSSystemTest, test_tick_function_SoC_update_acu) {
    AMSSystem system;

    system.has_initialized_charge_ = true;
    system.use_em_for_soc_ = false;
    system.charge_ = 100; 
    system.acu_shunt_measurements_.current_shunt_read_ro = 4000; 
    system.last_tick_ = {0, 0}; 

    SysTick_s tick = {0, 1000000}; 

    system.tick(tick);

    ASSERT_NEAR(system.SoC_, -0.8, 0.1); 
}


#endif
