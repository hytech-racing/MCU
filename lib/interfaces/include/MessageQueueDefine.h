#ifndef MESAGE_QUEUE_DEFINE_H
#define MESAGE_QUEUE_DEFINE_H

#include "FlexCAN_T4.h"

constexpr std::size_t CANBufferSize = 16;
using CANBufferType = CircularBuffer<uint8_t, CANBufferSize>;

#endif