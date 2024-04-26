#include <Arduino.h>
#include <unity.h>
#include <iostream>
#include "AMSInterface.h"

/* CAN_message_t typedef from FlexCAN_T4.h (line 55)
typedef struct CAN_message_t {
  uint32_t id = 0;          // can identifier
  uint16_t timestamp = 0;   // FlexCAN time when message arrived
  uint8_t idhit = 0; // filter that id came from
  struct {
    bool extended = 0; // identifier is extended (29-bit)
    bool remote = 0;  // remote transmission request packet type
    bool overrun = 0; // message overrun
    bool reserved = 0;
  } flags;
  uint8_t len = 8;      // length of data
  uint8_t buf[8] = { 0 };       // data
  int8_t mb = 0;       // used to identify mailbox reception
  uint8_t bus = 0;      // used to identify where the message came from when events() is used.
  bool seq = 0;         // sequential frames
} CAN_message_t;
*/

/**
 * Generates a CAN message containing the given data. This handles the byte-swapping (because of big-endian) automatically.
 * 
 * @param first The leftmost 16 bits of this CAN message's 64 bits.
 * @param second The second-leftmost 16 bits of this CAN message's 64 bits.
 * @param third The second-rightmost 16 bits of this CAN message's 64 bits.
 * @param fourth The rightmost 16 bits of this CAN message's 64 bits.
 * @param invert_bits True if the bytes will be READ OFF OF THE CAN LINE using little-endian. If the unpack function expects the number
 *                    0013 to be on the CAN line as 00 13, then set this to true. If the unpack function expects the number 0013 to
 *                    be on the CAN line as 13 00, then set this to false.
 * 
 * @return A CAN_message_t with ONLY its data set (not the ID or any other bits)
*/
inline CAN_message_t generate_can_msg_from_uint_16s(uint16_t first, uint16_t second, uint16_t third, uint16_t fourth, bool use_little_endian)
{

    CAN_message_t can_msg;

    uint16_t actual_first = first, actual_second = second, actual_third = third, actual_fourth = fourth;

    // Expected values in CAN message. These are BIG-ENDIAN, by BYTE. The number 19 in hex
    // is 0013, but we must declare it as 0x1300U with the least-sig byte and most-sig byte switched.
    if (use_little_endian) {
        actual_first = (uint16_t) ( (0x00FFU & first) << 8U | (0xFF00U & first) >> 8U );
        actual_second = (uint16_t) ( (0x00FFU & second) << 8U | (0xFF00U & second) >> 8U );
        actual_third = (uint16_t) ( (0x00FFU & third) << 8U | (0xFF00U & third) >> 8U );
        actual_fourth = (uint16_t) ( (0x00FFU & fourth) << 8U | (0xFF00U & fourth) >> 8U );
    }

    // Places expected values into buffer
    memcpy(&can_msg.buf, &actual_first, sizeof(uint16_t));
    memcpy(&can_msg.buf[2], &actual_second, sizeof(uint16_t));
    memcpy(&can_msg.buf[4], &actual_third, sizeof(uint16_t));
    memcpy(&can_msg.buf[6], &actual_fourth, sizeof(uint16_t));

    return can_msg;

}

void test_get_SoC_em()
{

    // Declaring & instantiating new AMSInterface (to read from CAN message)
    AMSInterface interface(0, 0.0f, 0.0f, 0.0f, 0.0f);



    // -------------------------- INITIALIZING ACU_SHUNT_MEASUREMENTS -------------------------- //

    CAN_message_t acu_can_msg = generate_can_msg_from_uint_16s(0x0001U, 0x0002U, 0x0003U, 0x0000U, true);

    interface.read_current_shunt_CAN(acu_can_msg); // Reads CAN message into the acu_shunt_measurements_ member variable
    ACU_SHUNT_MEASUREMENTS_t received_shunt_measurements = interface.get_acu_shunt_measurements();

    // Tests to ensure that the values read off of the CAN line are as expected (ideally should never fail)
    TEST_ASSERT_EQUAL(0x0001U, received_shunt_measurements.current_shunt_read_ro);
    TEST_ASSERT_EQUAL(0x0002U, received_shunt_measurements.pack_filtered_read_ro);
    TEST_ASSERT_EQUAL(0x0003U, received_shunt_measurements.ts_out_filtered_read_ro);



    // -------------------------- INITIALIZING BMS_VOLTAGES -------------------------- //

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



    // -------------------------- Tests the initialize_charge function -------------------------- //

    //                                                    3.7 avg  3.5 low  3.9 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9088U, 0x88B8U, 0x9858U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(13122.0f, interface.initialize_charge());

    //                                                    3.7 avg  3.3 low  3.9 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9088U, 0x80E8U, 0x9858U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(3402.0f, interface.initialize_charge());

    //                                                    3.8 avg  3.7 low  3.9 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9470U, 0x9088U, 0x9858U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(36450.0f, interface.initialize_charge());

    //                                                    4.0 avg  4.0 low  4.0 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x9C40U, 0x9C40U, 0x9C40U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(48600.0f, interface.initialize_charge());

    //                                                    3.3 avg  2.9 low  3.7 high
    bms_voltages_can_msg = generate_can_msg_from_uint_16s(0x80E8U, 0x7148U, 0x9088U, 0xFFFFU, false);
    interface.retrieve_voltage_CAN(bms_voltages_can_msg);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, interface.initialize_charge());

}

void test_get_SoC_acu()
{

}
