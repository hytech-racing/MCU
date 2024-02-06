#ifndef STATE_MACHINE_TEST
#define STATE_MACHINE_TEST
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MCUStateMachine.h"


// TODO @ben

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

    void command_drivetrain(const DrivetrainCommand_s &data){};
};

BuzzerController buzzer(500);

DrivetrainMock drivetrain;

PedalsSystem pedals;
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

    AnalogConversion_s pedals1_data;
    pedals1_data.raw = 0;
    pedals1_data.conversion = 0;
    pedals1_data.status = AnalogSensorStatus_e::ANALOG_SENSOR_GOOD;
    auto pedals2_data = pedals1_data;

    AnalogConversion_s pedals3_data;
    pedals3_data.raw = 3000;
    pedals3_data.conversion= 1.0;
    pedals3_data.status = pedals1_data.status;
    auto pedals4_data = pedals3_data;
    pedals.tick(SysTick_s{}, pedals1_data, pedals2_data, pedals3_data, pedals4_data);
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::ENABLING_INVERTERS);
    
}

TEST(MCUStateMachineTesting, test_state_machine_drivetrain_quit_test)
{

}

TEST(MCUStateMachineTesting, test_state_machine_drivetrain_enable)
{

}

TEST(MCUStateMachineTesting, test_state_machine_rtd_sound)
{

}

TEST(MCUStateMachineTesting, test_state_machine_rtd_state_transitions)
{

}

#endif /* STATE_MACHINE_TEST */
