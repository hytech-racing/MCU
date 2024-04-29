#ifndef MESAGE_QUEUE_DEFINE_H
#define MESAGE_QUEUE_DEFINE_H

#include "FlexCAN_T4.h"

// does this need to be 3 params like our original definitions of the buffers?
using CANBufferType = Circular_Buffer<uint8_t, (uint32_t)128, sizeof(CAN_message_t)>;

#endif