#ifndef DASH_INTERFACE_TEST
#define DASH_INTERFACE_TEST

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// #include "FlexCAN_T4.h"
// #include "HytechCANInterface.h"
#include "hytech.h"

#include "DashboardInterface.h"

Circular_Buffer <uint8_t, (uint32_t)16, sizeof(CAN_message_t)> CAN_buffer;

DashboardInterface dash_interface(&CAN_buffer);

TEST(DashInterfaceTesting, test_unpacking_message)
{

    DASHBOARD_STATE_t dash_state{};
    dash_state.start_button = true;
    dash_state.mark_button = true;
    dash_state.mode_button = false;
    dash_state.motor_controller_cycle_button = true;
    dash_state.launch_ctrl_button = false;
    dash_state.torque_mode_button = false;
    dash_state.led_dimmer_button = false;
    dash_state.left_shifter_button = true;
    dash_state.right_shifter_button = false;
    dash_state.shutdown_h_above_threshold = false;
    
    CAN_message_t msg;
    msg.id= Pack_DASHBOARD_STATE_hytech(&dash_state, msg.buf, &msg.len, msg.flags.extended);

    dash_interface.read(msg);



}

#endif