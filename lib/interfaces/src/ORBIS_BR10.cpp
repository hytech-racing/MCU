// #include "UpperSteeringSensor.h"
// #include <Arduino.h>

// // Definitions
// #define ORBIS_BR10_DEFAULT_SERIAL_SPEED             115200
// #define ORBIS_BR10_SCALE                            0.0219726562 // 360 degrees per 14 bits
// #define ORBIS_BR10_BITMASK_GENERAL_WARNING          (0b1 << 0)
// #define ORBIS_BR10_BITMASK_GENERAL_ERROR            (0b1 << 1)
// #define ORBIS_BR10_BITMASK_GENERAL                  (ORBIS_BR10_BITMASK_GENERAL_WARNING | ORBIS_BR10_BITMASK_GENERAL_ERROR)
// #define ORBIS_BR10_BITMASK_DETAILED_COUNTER_ERROR   (0b1 << 3)
// #define ORBIS_BR10_BITMASK_DETAILED_SPEED_HIGH      (0b1 << 4)
// #define ORBIS_BR10_BITMASK_DETAILED_TEMP_RANGE      (0b1 << 5)
// #define ORBIS_BR10_BITMASK_DETAILED_DIST_FAR        (0b1 << 6)
// #define ORBIS_BR10_BITMASK_DETAILED_DIST_NEAR       (0b1 << 7)
// #define ORBIS_BR10_BITMASK_DETAILED                 (ORBIS_BR10_BITMASK_DETAILED_COUNTER_ERROR | ORBIS_BR10_BITMASK_DETAILED_SPEED_HIGH | ORBIS_BR10_BITMASK_DETAILED_TEMP_RANGE | ORBIS_BR10_BITMASK_DETAILED_DIST_FAR | ORBIS_BR10_BITMASK_DETAILED_DIST_NEAR)

// class orbisBR10 : UpperSteeringSensor
// {
// private:
// // Data
//     HardwareSerial* serial;
//     int serialSpeed;
//     AnalogChannel channel;
//     int data;
//     char status;
// public:
// // Constructors
//     orbisBR10(HardwareSerial* serial_, int serialSpeed_)
//     : serial(serial_)
//     , serialSpeed(serialSpeed_)
//     {
//         channel = AnalogChannel(ORBIS_BR10_SCALE, 0.0);
//         data = 0;
//         // Initialize with all errors/warnings set
//         status = ORBIS_BR10_BITMASK_GENERAL | ORBIS_BR10_BITMASK_DETAILED;

//         serial->begin(serialSpeed);
//     }
//     orbisBR10(HardwareSerial* serial_)
//     : orbisBR10(serial_, ORBIS_BR10_DEFAULT_SERIAL_SPEED) {}

// // Functions
//     void sample()
//     {
//         uint8_t readByte[3] = {0};

//         serial->write(0x64);
//         if (serial->available() >= 4 && serial->read() == 0x64) {
//             readByte[0] = serial->read(); //lower half of steering
//             readByte[1] = serial->read(); //upper half of steering
//             readByte[2] = serial->read(); //error stream 
//             data = (readByte[0] << 6) | (readByte[1] >> 2);
//             status = readByte[1] & ORBIS_BR10_BITMASK_GENERAL;
//             status |= readByte[2] & ORBIS_BR10_BITMASK_DETAILED;
//         }
//         else
//         {
//             // set the error flag
//             status = ORBIS_BR10_BITMASK_GENERAL_ERROR;
//         }
//     }

//     std::tuple<float, upperSteeringStatus_s> getAngleAndStatus()
//     {
//         // TODO @mikhail fix return
//         // std::tuple<float, bool> conversion = channel.convert();
//         upperSteeringStatus_s returnStatus;
//         if (status & (ORBIS_BR10_BITMASK_GENERAL_ERROR | ORBIS_BR10_BITMASK_DETAILED_COUNTER_ERROR))
//         {
//             returnStatus = UPPER_STEERING_ERROR;
//         }
//         else if (status == 0 || std::get<1>(conversion))
//         {
//             returnStatus = UPPER_STEERING_NOMINAL;
//         }
//         else
//         {
//             returnStatus = UPPER_STEERING_MARGINAL;
//         }
//         return {std::get<0>(conversion), returnStatus};
//     }

//     void setOffset(float newOffset)
//     {
//         channel.offset = newOffset;
//     }
// };