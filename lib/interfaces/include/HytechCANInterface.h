#ifndef HYTECHCANINTERFACE
#define HYTECHCANINTERFACE

#include <tuple>
#include "FlexCAN_T4.h"

#include "HyTech_CAN.h"

// the goal with the can interface is that there exists a receive call that appends to a circular buffer
// the processing of the receive queue happens on every iteration of the loop
// in the processing of the receive call, all of the messages received get de-serialized and passed to their interfaces

extern Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>
    CAN1_rxBuffer;
extern Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>
    CAN2_rxBuffer;

extern Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>
    CAN3_rxBuffer;

extern Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>
    CAN1_txBuffer;
extern Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>
    CAN2_txBuffer;

extern Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>
    CAN3_txBuffer;

void on_can1_receive(const CAN_message_t &msg);
void on_can2_receive(const CAN_message_t &msg);
void on_can3_receive(const CAN_message_t &msg);

// reads from receive buffer updating the current message frame from a specific receive buffer
template <typename BufferType>
void process_ring_buffer(AllMsgs &current_message_frame, BufferType &rx_buffer, InverterInterface * front_left_inv)
{

    while (rx_buffer.available())
    {
        CAN_message_t recvd_msg;
        uint8_t buf[sizeof(CAN_message_t)];
        rx_buffer.pop_front(buf, sizeof(CAN_message_t));
        memmove(&recvd_msg, buf, sizeof(recvd_msg));
        switch (recvd_msg.id)
        {
        case ID_MC1_STATUS:
            front_left_inv->receive_status_msg(recvd_msg); 
            break;
        case ID_MC2_STATUS:
            std::get<0>(current_message_frame.mc_2_status) = true;
            std::get<1>(current_message_frame.mc_2_status).load(recvd_msg.buf);
            break;
        case ID_MC1_TEMPS:
            std::get<0>(current_message_frame.mc_1_temps) = true;
            std::get<1>(current_message_frame.mc_1_temps).load(recvd_msg.buf);
            break;
        case ID_MC2_TEMPS:
            std::get<0>(current_message_frame.mc_2_temps) = true;
            std::get<1>(current_message_frame.mc_2_temps).load(recvd_msg.buf);
            break;
        case ID_MC1_ENERGY:
            std::get<0>(current_message_frame.mc_1_energy) = true;
            std::get<1>(current_message_frame.mc_1_energy).load(recvd_msg.buf);
            break;
        case ID_MC2_ENERGY:
            std::get<0>(current_message_frame.mc_2_energy) = true;
            std::get<1>(current_message_frame.mc_2_energy).load(recvd_msg.buf);
            break;
        }
    }
}

template <typename bufferType>
void send_all_CAN_msgs(bufferType& buffer, FlexCAN_T4_Base * can_interface)
{
    CAN_message_t msg;
    while(buffer.available())
    {
        CAN_message_t msg;
        uint8_t buf[sizeof(CAN_message_t)];
        buffer.pop_front(buf, sizeof(CAN_message_t));
        memmove(&msg, buf, sizeof(msg));
        can_interface->write(msg);

    }
}

#endif /* HYTECHCANINTERFACE */
