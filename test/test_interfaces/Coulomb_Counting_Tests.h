#include <Arduino.h>
#include <unity.h>
#include <iostream>
#include "AMSInterface.h"
#include "SysClock.h"

void test_initialize_charge()
{

    // Declaring & instantiating new AMSInterface (to read from CAN message)
    AMSInterface interface(8);



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

void test_get_SoC_em()
{
    // Declaring & instantiating a new AMSInterface (to read from CAN messages and perform the SoC calculations)
    AMSInterface interface(8);

    CAN_message_t em_measurements_can, bms_voltages_can;

    // Declaring CAN frames and feeding them into the AMSInterface.
    // Initializes BMS_VOLTAGES to have a min (of 3.7 volts, which is 0x9088U).
    bms_voltages_can = generate_can_msg_from_uint_16s(0x9088U, 37000U, 0x9858U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can);

    em_measurements_can = generate_can_msg_from_uint_32s(HYTECH_em_current_ro_toS(25.0f), HYTECH_em_voltage_ro_toS(530.5f), true);
    interface.retrieve_em_measurement_CAN(em_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable



    // Declaring initial conditions
    unsigned long starting_millis = millis();
    unsigned long starting_micros = micros();
    SysTick_s starting_tick;
    starting_tick.millis = starting_millis;
    starting_tick.micros = starting_micros;



    // call init() to set heartbeat
    interface.init(starting_tick);
    // call initialize_charge() to set starting SoC
    interface.initialize_charge();
    // assert initial SoC is correct
    TEST_ASSERT_EQUAL_FLOAT(75.0, interface.get_SoC());


    // Running actual test cases

    // TEST CASE ONE - 10ms - 25amps
    SysTick_s tick_one;
    tick_one.millis = starting_millis + 10;
    tick_one.micros = starting_micros + 10000;

    // 25 amps of current * 0.01sec = 0.25 coulombs of charge.
    // Starting charge = 75%, so 36450 coulombs. After this,
    // charge should be at 36449.75, or 74.94855%
    interface.tick50(tick_one);
    TEST_ASSERT_EQUAL_FLOAT(74.9994855, interface.get_SoC());



    // TEST CASE TWO - 20ms - 50amps
    SysTick_s tick_two;
    tick_two.millis = starting_millis + 10 + 20;
    tick_two.micros = starting_micros + 10000 + 20000;

    em_measurements_can = generate_can_msg_from_uint_32s(HYTECH_em_current_ro_toS(50.0f), HYTECH_em_voltage_ro_toS(530.5f), true);
    interface.retrieve_em_measurement_CAN(em_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable

    // 50 amps of current * 0.02sec = 1 coulomb of charge.
    // Starting charge = 36449.75 coulombs. After this,
    // charge should be at 36448.75, or 74.94855%
    interface.tick50(tick_two);
    TEST_ASSERT_EQUAL_FLOAT(74.9974279f, interface.get_SoC());



    // TEST CASE THREE - 10 full seconds, in 20ms intervals, at 50 amps

    em_measurements_can = generate_can_msg_from_uint_32s(HYTECH_em_current_ro_toS(50.0f), HYTECH_em_voltage_ro_toS(530.5f), true);
    interface.retrieve_em_measurement_CAN(em_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable

    for (int i = 0; i <= 10000000; i += 10000) {
        SysTick_s curr_tick;
        curr_tick.millis = starting_millis + 10 + 20 + i/1000;
        curr_tick.micros = starting_micros + 10000 + 20000 + i;
        interface.tick50(curr_tick);
    }

    // 50 amps of current * 10sec = 500 coulombs of charge
    // Starting charge = 36448.75 coulombs. After this, charge
    // should be 35948.75 coulombs, which is 73.9686%
    TEST_ASSERT_EQUAL_FLOAT(73.9686f, interface.get_SoC());

}
