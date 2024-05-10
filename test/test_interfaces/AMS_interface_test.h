#include <Arduino.h>
#include <unity.h>
#include "AMSInterface.h"
#include "SysClock.h"
#include "CAN_testing_utilities.h"

/* Circular buffer for a CAN line to write to/read from. */
Circular_Buffer<uint8_t, (uint32_t)32, sizeof(CAN_message_t)>
    CAN3_txBuffer;
    
void test_AMS_unpacking_BMS_status_message()
{
    /*
    Need clarification on what these states are.
    Why is nothing else in the message read by AMSInterface
    */
    BMS_status bms_status{};
    bms_status.set_state(5);

}

void test_AMS_unpacking_BMS_temperatures_message()
{

}

/**
 * Tests the AMSInterface's "retrieve_current_shunt_CAN()" function.
*/
void test_current_shunt_CAN_message()
{

    // Declaring & instantiating new AMSInterface (to read from CAN message)
    AMSInterface interface(8, &CAN3_txBuffer);


    
    // Creating a new CAN message, feeding it into the interface, and then retrieving it
    CAN_message_t acu_can_msg = generate_can_msg_from_uint_16s(0x0001U, 0x0002U, 0x0003U, 0x0000U, true);

    interface.retrieve_current_shunt_CAN(acu_can_msg); // Reads CAN message into the acu_shunt_measurements_ member variable
    ACU_SHUNT_MEASUREMENTS_t received_shunt_measurements = interface.get_acu_shunt_measurements();



    // Tests to ensure that the values read off of the CAN line are as expected (ideally should never fail)
    TEST_ASSERT_EQUAL(0x0001U, received_shunt_measurements.current_shunt_read_ro);
    TEST_ASSERT_EQUAL(0x0002U, received_shunt_measurements.pack_filtered_read_ro);
    TEST_ASSERT_EQUAL(0x0003U, received_shunt_measurements.ts_out_filtered_read_ro);

}

void test_bms_voltages_CAN_message()
{

    // Declaring & instantiating new AMSInterface (to read from CAN message)
    AMSInterface interface(8, &CAN3_txBuffer);


    // ----------- CONSTANTS (FOR TESTING PURPOSES) ----------- //
    // 4.0 volts with a 0.0001 scale factor is 40000. 40000 in hex is 9C40 // Cell should never go above 3.972
    // 3.9 volts with a 0.0001 scale factor is 39000. 39000 in hex is 9858
    // 3.8 volts with a 0.0001 scale factor is 38000. 38000 in hex is 9470
    // 3.7 volts with a 0.0001 scale factor is 37000. 37000 in hex is 9088
    // 3.6 volts with a 0.0001 scale factor is 36000. 36000 in hex is 8CA0
    // 3.5 volts with a 0.0001 scale factor is 35000. 35000 in hex is 88B8
    // 3.4 volts with a 0.0001 scale factor is 34000. 34000 in hex is 84D0
    // 3.3 volts with a 0.0001 scale factor is 33000. 33000 in hex is 80E8
    // 3.2 volts with a 0.0001 scale factor is 32000. 32000 in hex is 7D00
    // 3.1 volts with a 0.0001 scale factor is 31000. 31000 in hex is 7918
    // 3.0 volts with a 0.0001 scale factor is 30000. 30000 in hex is 7530
    // 2.9 volts with a 0.0001 scale factor is 29000. 29000 in hex is 7148 // Cell should never go below 3.0

    // BMS_VOLTAGES_t has avg, low, high, and total voltage for each cell. BMS_VOLTAGES_t reads off the CAN line as big-endian.
    //                                                                  3.7 avg  3.5 low  3.9 high
    CAN_message_t bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9088U, 0x88B8U, 0x9858U, 0xFFFFU, false);

    interface.retrieve_voltage_CAN(bms_voltages_can_msg); // Reads CAN message into the acu_shunt_measurements_ member variable
    BMS_VOLTAGES_t received_voltages = interface.get_bms_voltages();



    // Tests to ensure that the values read off of the CAN line are as expected (ideally should never fail)
    TEST_ASSERT_EQUAL(0x9088U, received_voltages.average_voltage_ro);
    TEST_ASSERT_EQUAL(0x88B8U, received_voltages.low_voltage_ro);
    TEST_ASSERT_EQUAL(0x9858U, received_voltages.high_voltage_ro);
    TEST_ASSERT_EQUAL(0xFFFFU, received_voltages.total_voltage_ro);

}

void test_em_measurements_CAN_message()
{

    // Declaring & instantiating new AMSInterface (to read from CAN message)
    AMSInterface interface(8, &CAN3_txBuffer);

    CAN_message_t em_measurements_can = generate_can_msg_from_uint_32s(HYTECH_em_current_ro_toS(23.9f), HYTECH_em_voltage_ro_toS(530.5f), true);

    interface.retrieve_em_measurement_CAN(em_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable
    EM_MEASUREMENT_t received_em_measurement = interface.get_em_measurements();

    // Tests to ensure that the values read off of the CAN line are as expected (ideally should never fail)
    TEST_ASSERT_EQUAL(23.9f, HYTECH_em_current_ro_fromS(received_em_measurement.em_current_ro));
    TEST_ASSERT_EQUAL(530.5f, HYTECH_em_voltage_ro_fromS(received_em_measurement.em_voltage_ro));

}

void test_AMS_charge_critical_threshold()
{

}

void test_AMS_filtered_readings()
{

}

void test_AMS_heartbeat()
{   
    //setting arbitrary pin 20
    AMSInterface ams_interface(20, &CAN3_txBuffer);

    unsigned long starting_millis = millis();
    SysTick_s starting_tick;
    starting_tick.millis = starting_millis;

    ams_interface.init(starting_tick);
    ams_interface.set_start_state();
    TEST_ASSERT_EQUAL(true, ams_interface.heartbeat_received(starting_millis + 1000));
    TEST_ASSERT_EQUAL(false, ams_interface.heartbeat_received(starting_millis + 2000));

    starting_millis = millis();
    ams_interface.set_heartbeat(starting_millis);
    TEST_ASSERT_EQUAL(true, ams_interface.heartbeat_received(starting_millis + 100));
    TEST_ASSERT_EQUAL(true, ams_interface.heartbeat_received(starting_millis + 1000));
    TEST_ASSERT_EQUAL(true, ams_interface.heartbeat_received(starting_millis + 1999));
    TEST_ASSERT_EQUAL(false, ams_interface.heartbeat_received(starting_millis + 2000));
    TEST_ASSERT_EQUAL(false, ams_interface.heartbeat_received(starting_millis + 2010));
    
}