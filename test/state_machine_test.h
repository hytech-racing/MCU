#ifndef STATE_MACHINE_TEST
#define STATE_MACHINE_TEST
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MCUStateMachine.h"




class DrivetrainMock
{
public:
    bool drivetrain_ready_;
    bool hv_thresh_;
    bool drivetrain_ready(){};
    /// @param curr_time current system tick time (millis()) that sets the init phase start time
    void enable_drivetrain_hv(unsigned long curr_time){};

    // startup phase 2
    bool check_drivetrain_quit_dc_on(){};

    // on entry logic
    void request_enable(){};
    void command_drivetrain_no_torque(){};

    // final check for drivetrain initialization to check if quit inverter on
    bool drivetrain_enabled(){};

    // check to see if init time limit has passed
    bool inverter_init_timeout(unsigned long curr_time){};

    bool hv_over_threshold_on_drivetrain() { return hv_thresh_; };
    void disable(){};
    bool drivetrain_error_occured(){};

    void command_drivetrain(const DrivetrainCommand &data){};
};

BuzzerController buzzer(500);

DrivetrainMock drivetrain;


PedalsParams params_for_test = {1, 1, 10, 10, 1, 1, 9, 9};
PedalsSystem pedals(params_for_test, params_for_test);

DashboardInterface dash_interface;

MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals);

TEST(MCUStateMachineTesting, test_state_machine_init_tick)
{
    unsigned long sys_time = 1000;
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::STARTUP);
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);
}



TEST(MCUStateMachineTesting, test_state_machine_tractive_system_activation)
{
    unsigned long sys_time = 1000;

    // ticking without hv over threshold testing and ensuring the tractive system not active still 
    state_machine.tick_state_machine(sys_time);
    sys_time += 1;
    drivetrain.hv_thresh_ = false;
    state_machine.tick_state_machine(sys_time);
    sys_time += 1;
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);

    // hv going over threshold -> tractive system
    drivetrain.hv_thresh_ = true;
    sys_time +=1;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_ACTIVE);


    // hv going under thresh -> tractive system not active
    drivetrain.hv_thresh_ =false; 
    sys_time +=1;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);
}

TEST(MCUStateMachineTesting, test_state_machine_tractive_system_enabling)
{
    unsigned long sys_time = 1000;

    // ticking without hv over threshold testing and ensuring the tractive system not active still 
    state_machine.tick_state_machine(sys_time);
    sys_time += 1;
    drivetrain.hv_thresh_ = false;
    state_machine.tick_state_machine(sys_time);
    sys_time += 1;
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);

    // hv going over threshold -> tractive system
    drivetrain.hv_thresh_ = true;
    sys_time +=1;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_ACTIVE);


    sys_time +=1;
    dash_interface.start_button_status_ = true;
    auto pedals_brake_active_res = pedals.evaluate_pedals({0,0,3,3}, sys_time);
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::ENABLING_INVERTERS);

    
}


#endif /* STATE_MACHINE_TEST */
