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

struct AllMsgs
{
    std::tuple<bool, MC_status> mc_1_status = {false, MC_status()};
    std::tuple<bool, MC_status> mc_2_status = {false, MC_status()};
    std::tuple<bool, MC_status> mc_3_status = {false, MC_status()};
    std::tuple<bool, MC_status> mc_4_status = {false, MC_status()};

    std::tuple<bool, MC_temps> mc_1_temps = {false, MC_temps()};
    std::tuple<bool, MC_temps> mc_2_temps = {false, MC_temps()};
    std::tuple<bool, MC_temps> mc_3_temps = {false, MC_temps()};
    std::tuple<bool, MC_temps> mc_4_temps = {false, MC_temps()};

    std::tuple<bool, MC_energy> mc_1_energy = {false, MC_energy()};
    std::tuple<bool, MC_energy> mc_2_energy = {false, MC_energy()};
    std::tuple<bool, MC_energy> mc_3_energy = {false, MC_energy()};
    std::tuple<bool, MC_energy> mc_4_energy = {false, MC_energy()};

    std::tuple<bool, BMS_coulomb_counts> bms_coulomb_counts = {false, BMS_coulomb_counts()};
    std::tuple<bool, BMS_status> bms_status = {false, BMS_status()};
    std::tuple<bool, BMS_temperatures> bms_temperatures = {false, BMS_temperatures()};
    std::tuple<bool, BMS_voltages> bms_voltages = {false, BMS_voltages()};
    std::tuple<bool, Dashboard_status> dashboard_status = {false, Dashboard_status()};
};

// 
void on_can1_receive(const CAN_message_t &msg);
void on_can2_receive(const CAN_message_t &msg);
void on_can3_receive(const CAN_message_t &msg);

// reads from receive buffer updating the current message frame from a specific receive buffer
template <typename BufferType>
void process_ring_buffer(AllMsgs &current_message_frame, BufferType &rx_buffer)
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
            std::get<0>(current_message_frame.mc_1_status) = true;
            std::get<1>(current_message_frame.mc_1_status).load(recvd_msg.buf);
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

#endif /* HYTECHCANINTERFACE */
