#include <Arduino.h>
#include <unity.h>
#include <iostream>
#include "AMSInterface.h"
#include "SysClock.h"
#include "MessageQueueDefine.h"

CANBufferType CAN_BUFFER_CC_TESTS;

void test_initialize_charge()
{

    // Declaring & instantiating new AMSInterface (to read from CAN message)
    AMSInterface interface(&CAN_BUFFER_CC_TESTS, 8);



    // -------------------------- Initializes bms_voltages CAN message -------------------------- //
    CAN_message_t bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9088U, 0x88B8U, 0x9858U, 0xFFFFU, false);

    interface.retrieve_voltage_CAN(bms_voltages_can_msg); // Reads CAN message into the acu_shunt_measurements_ member variable
    BMS_VOLTAGES_t received_voltages = interface.get_bms_voltages();



    // -------------------------- Tests the initialize_charge function -------------------------- //

    //                                                    3.7 avg  3.5 low  3.9 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9088U, 0x88B8U, 0x9858U, 0xFFFFU, false); // Regular use case
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(13122.0f, interface.initialize_charge());

    //                                                    3.7 avg  3.3 low  3.9 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9088U, 0x80E8U, 0x9858U, 0xFFFFU, false); // Regular use case
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(3402.0f, interface.initialize_charge());

    //                                                    3.8 avg  3.7 low  3.9 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9470U, 0x9088U, 0x9858U, 0xFFFFU, false); // Regular use case
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(36450.0f, interface.initialize_charge());

    //                                                    4.0 avg  4.0 low  4.0 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9C40U, 0x9C40U, 0x9C40U, 0xFFFFU, false); // Maximum voltage (100% charge)
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(48600.0f, interface.initialize_charge());

    //                                                    3.3 avg  2.9 low  3.7 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x80E8U, 0x7148U, 0x9088U, 0xFFFFU, false); // Minimum voltage (0% charge)
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, interface.initialize_charge());

}

void test_calculate_SoC_em()
{

    // Declaring initial conditions
    unsigned long starting_millis = millis();
    unsigned long starting_micros = micros();
    SysTick_s starting_tick;
    starting_tick.millis = starting_millis;
    starting_tick.micros = starting_micros;

    // Declaring & instantiating a new AMSInterface (to read from CAN messages and perform the SoC calculations)
    AMSInterface interface(&CAN_BUFFER_CC_TESTS, 8);
    interface.init(starting_tick); // Sets heartbeat and puts "uninitialized" value into bms_voltages_

    interface.set_use_em_for_soc(true);

    CAN_message_t em_measurements_can, bms_voltages_can;

    // Declaring CAN frames and feeding them into the AMSInterface.
    // Initializes BMS_VOLTAGES to have a min (of 3.7 volts, which is 0x9088U).
    bms_voltages_can = generate_can_msg_from_uint_16s(0x9088U, 37000U, 0x9858U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can);

    em_measurements_can = generate_can_msg_from_uint_32s(HYTECH_em_current_ro_toS(25.0f), HYTECH_em_voltage_ro_toS(530.5f), true);
    interface.retrieve_em_measurement_CAN(em_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable


    // TEST CASE ZERO - 5000ms to allow initialization to happen
    SysTick_s tick_zero;
    tick_zero.millis = starting_millis + 5000;
    tick_zero.micros = starting_micros + 1000000;

    // Call tick() once (with no delta t) so that initialize_charge() will be called
    interface.tick(tick_zero);

    // assert initial SoC is correct
    TEST_ASSERT_EQUAL_FLOAT(75.0, interface.get_SoC());


    // Running actual test cases

    // TEST CASE ONE - 10ms - 25amps
    SysTick_s tick_one;
    tick_one.millis = tick_zero.millis + 10;
    tick_one.micros = tick_zero.micros + 10000;

    // 25 amps of current * 0.01sec = 0.25 coulombs of charge.
    // Starting charge = 75%, so 36450 coulombs. After this,
    // charge should be at 36449.75, or 74.9994%
    interface.tick(tick_one);
    TEST_ASSERT_EQUAL_FLOAT(74.9994855, interface.get_SoC());



    // TEST CASE TWO - 20ms - 50amps
    SysTick_s tick_two;
    tick_two.millis = tick_zero.millis + 10 + 20;
    tick_two.micros = tick_zero.micros + 10000 + 20000;

    em_measurements_can = generate_can_msg_from_uint_32s(HYTECH_em_current_ro_toS(50.0f), HYTECH_em_voltage_ro_toS(530.5f), true);
    interface.retrieve_em_measurement_CAN(em_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable

    // 50 amps of current * 0.02sec = 1 coulomb of charge.
    // Starting charge = 36449.75 coulombs. After this,
    // charge should be at 36448.75, or 74.9974279%
    interface.tick(tick_two);
    TEST_ASSERT_EQUAL_FLOAT(74.9974279f, interface.get_SoC());



    // TEST CASE THREE - 10 full seconds, in 20ms intervals, at 50 amps

    em_measurements_can = generate_can_msg_from_uint_32s(HYTECH_em_current_ro_toS(50.0f), HYTECH_em_voltage_ro_toS(530.5f), true);
    interface.retrieve_em_measurement_CAN(em_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable

    for (int i = 0; i <= 10000000; i += 20000) {
        SysTick_s curr_tick;
        curr_tick.millis = tick_zero.millis + 10 + 20 + i/1000;
        curr_tick.micros = tick_zero.micros + 10000 + 20000 + i;
        interface.tick(curr_tick);
    }

    // 50 amps of current * 10sec = 500 coulombs of charge
    // Starting charge = 36448.75 coulombs. After this, charge
    // should be 35948.75 coulombs, which is 73.9686%
    TEST_ASSERT_EQUAL_FLOAT(73.9686f, interface.get_SoC());

}

void test_calculate_SoC_acu()
{
   // Declaring initial conditions
    unsigned long starting_millis = millis();
    unsigned long starting_micros = micros();
    SysTick_s starting_tick;
    starting_tick.millis = starting_millis;
    starting_tick.micros = starting_micros;

    // Declaring & instantiating a new AMSInterface (to read from CAN messages and perform the SoC calculations)
    AMSInterface interface(&CAN_BUFFER_CC_TESTS, 8);
    interface.init(starting_tick); // Sets heartbeat and puts "uninitialized" value into bms_voltages_

    interface.set_use_em_for_soc(false);

    CAN_message_t acu_measurements_can, bms_voltages_can;

    // Declaring CAN frames and feeding them into the AMSInterface.
    // Initializes BMS_VOLTAGES to have a min (of 3.7 volts, which is 0x9088U).
    bms_voltages_can = generate_can_msg_from_uint_16s(0x9088U, 37000U, 0x9858U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can);

    // 2372 analog value corresponds to 25A
    acu_measurements_can = generate_can_msg_from_uint_16s(2372, HYTECH_pack_filtered_read_ro_toS(0.0), HYTECH_ts_out_filtered_read_ro_toS(0.0), 0, false);
    interface.retrieve_current_shunt_CAN(acu_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable



    // TEST CASE ZERO - 5000ms to allow initialization to happen
    SysTick_s tick_zero;
    tick_zero.millis = starting_millis + 5000;
    tick_zero.micros = starting_micros + 1000000;

    // Call tick() once (with no delta t) so that initialize_charge() will be called
    interface.tick(tick_zero);
    // assert initial SoC is correct
    TEST_ASSERT_EQUAL_FLOAT(75.0, interface.get_SoC());


    // Running actual test cases

    // TEST CASE ONE - 10ms - 25amps
    SysTick_s tick_one;
    tick_one.millis = tick_zero.millis + 10;
    tick_one.micros = tick_zero.micros + 10000;

    // 25 amps of current * 0.01sec = 0.25 coulombs of charge.
    // Starting charge = 75%, so 36450 coulombs. After this,
    // charge should be at 36449.75, or 74.9994855%
    interface.tick(tick_one);
    TEST_ASSERT_EQUAL_FLOAT(74.9994855, interface.get_SoC());



    // TEST CASE TWO - 20ms - 50amps
    SysTick_s tick_two;
    tick_two.millis = tick_zero.millis + 10 + 20;
    tick_two.micros = tick_zero.micros + 10000 + 20000;

    acu_measurements_can = generate_can_msg_from_uint_16s(2458, HYTECH_pack_filtered_read_ro_toS(0.0), HYTECH_ts_out_filtered_read_ro_toS(0.0), 0, false);
    interface.retrieve_current_shunt_CAN(acu_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable

    // 50 amps of current * 0.02sec = 1 coulomb of charge.
    // Starting charge = 36449.75 coulombs. After this,
    // charge should be at 36448.75, or 74.9974279f%
    interface.tick(tick_two);
    TEST_ASSERT_EQUAL_FLOAT(74.9974279f, interface.get_SoC());



    // TEST CASE THREE - 10 full seconds, in 20ms intervals, at 50 amps

    acu_measurements_can = generate_can_msg_from_uint_16s(2457, HYTECH_pack_filtered_read_ro_toS(0.0), HYTECH_ts_out_filtered_read_ro_toS(0.0), 0, false);
    interface.retrieve_current_shunt_CAN(acu_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable

    for (int i = 0; i <= 10000000; i += 20000) {
        SysTick_s curr_tick;
        curr_tick.millis = tick_zero.millis + 10 + 20 + i/1000;
        curr_tick.micros = tick_zero.micros + 10000 + 20000 + i;
        interface.tick(curr_tick);
    }

    // 50 amps of current * 10sec = 500 coulombs of charge
    // Starting charge = 36448.75 coulombs. After this, charge
    // should be 35948.75 coulombs, which is 73.9686%
    TEST_ASSERT_EQUAL_FLOAT(73.9686f, interface.get_SoC());

}