#include <Arduino.h>

/**
 * Generates a CAN message containing the given data. This handles the byte-swapping (because of big-endian) automatically.
 * 
 * @param first The leftmost 16 bits of this CAN message's 64 bits.
 * @param second The second-leftmost 16 bits of this CAN message's 64 bits.
 * @param third The second-rightmost 16 bits of this CAN message's 64 bits.
 * @param fourth The rightmost 16 bits of this CAN message's 64 bits.
 * @param use_little_endian True if the bytes will be READ OFF OF THE CAN LINE using little-endian. If the unpack function expects the number
 *                          0013 to be on the CAN line as 00 13, then set this to true. If the unpack function expects the number 0013 to
 *                          be on the CAN line as 13 00, then set this to false.
 * 
 * @return A CAN_message_t with ONLY its data set (not the ID or any other bits)
*/
inline CAN_message_t generate_can_msg_from_uint_16s(uint16_t first, uint16_t second, uint16_t third, uint16_t fourth, bool use_little_endian)
{

    CAN_message_t can_msg;

    uint16_t actual_first = first, actual_second = second, actual_third = third, actual_fourth = fourth;

    // By default, uint16s are saved in memory using big-endian, by byte. This means that if you say "uint16_t x = 0x0013", this will be saved
    // in memory as 1300. If the bits SHOULD be on the CAN line using big-endian, then this is fine. However, if the bits SHOULD be on the CAN
    // line as little-endian, then we need to invert the bytes before copying the memory into the CAN buffer.
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

/**
 * Generates a CAN message containing the given data. This handles the byte-swapping (because of big-endian) automatically.
 * 
 * @param first The leftmost 32 bits of this CAN message's 64 bits.
 * @param second The second-leftmost 32 bits of this CAN message's 64 bits.
 * @param use_little_endian True if the bytes will be READ OFF OF THE CAN LINE using little-endian. If the unpack function expects the number
 *                          00000013 (hex) to be on the CAN line as 00 00 00 13, then set this to true. If the unpack function expects the
 *                          number 00000013 to be on the CAN line as 13 00 00 00, then set this to false.
 * 
 * @return A CAN_message_t with ONLY its data set (not the ID or any other bits)
*/
inline CAN_message_t generate_can_msg_from_uint_32s(uint32_t first, uint32_t second, bool use_little_endian)
{

    CAN_message_t can_msg;

    uint32_t actual_first = first, actual_second = second;

    // Expected values in CAN message. These are BIG-ENDIAN, by BYTE. The number 19 in hex
    // is 0013, but we must declare it as 0x1300U with the least-sig byte and most-sig byte switched.
    if (use_little_endian) {
        actual_first = (uint32_t) ( (0x000000FFU & first) << 24U | (0x0000FF00U & first) << 8U | (0x00FF0000U & first) >> 8U | (0xFF000000U & first) >> 24U);
        actual_second = (uint32_t) ( (0x000000FFU & second) << 24U | (0x0000FF00U & second) << 8U | (0x00FF0000U & second) >> 8U | (0xFF000000U & second) >> 24U);
    }

    // Places expected values into buffer
    memcpy(&can_msg.buf, &actual_first, sizeof(uint32_t));
    memcpy(&can_msg.buf[4], &actual_second, sizeof(uint32_t));

    return can_msg;

}