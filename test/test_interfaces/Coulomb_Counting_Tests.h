#include <Arduino.h>
#include <unity.h>
#include <iostream>
#include "AMSInterface.h"

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

    // Declaring CAN frames and feeding them into the AMSInterface
    bms_voltages_can = generate_can_msg_from_uint_16s(0x9088U, 0x88B8U, 0x9858U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can);

    em_measurements_can = generate_can_msg_from_uint_32s(HYTECH_em_current_ro_toS(23.9f), HYTECH_em_voltage_ro_toS(530.5f), true);
    interface.retrieve_em_measurement_CAN(em_measurements_can); // Reads CAN message into the acu_shunt_measurements_ member variable


}
