#ifndef STATE_MACHINE_TEST
#define STATE_MACHINE_TEST
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MCUStateMachine.h"

// TODO @ben

class DrivetrainMock
{
public:
    bool drivetrain_inited_;
    bool hv_thresh_;
    bool drivetrain_error_;
    /// @param curr_time current system tick time (millis()) that sets the init phase start time

    void command_drivetrain_no_torque(){};

    bool handle_inverter_startup(unsigned long cm) { return drivetrain_inited_; };
    // check to see if init time limit has passed
    bool inverter_init_timeout(unsigned long curr_time){};

    bool hv_over_threshold_on_drivetrain() { return hv_thresh_; };
    void disable(){};
    bool drivetrain_error_occured() { return drivetrain_error_; };

    void command_drivetrain(const DrivetrainCommand_s &data){};
};

void handle_startup(MCUStateMachine<DrivetrainMock> &state_machine, unsigned long sys_time, DrivetrainMock &drivetrain, PedalsSystem &pedals, DashboardInterface &dash_interface)
{
    // ticking without hv over threshold testing and ensuring the tractive system not active still
    auto sys_time2 = sys_time;

    drivetrain.hv_thresh_ = true;

    state_machine.tick_state_machine(sys_time);
    // hv going over threshold -> tractive system active
    drivetrain.hv_thresh_ = true;
    sys_time2 += 1;
    state_machine.tick_state_machine(sys_time);
    sys_time2 += 1;
    dash_interface.start_button_status_ = true;
    AnalogConversion_s pedals1_data;
    pedals1_data.raw = 0;
    pedals1_data.conversion = 0;
    pedals1_data.status = AnalogSensorStatus_e::ANALOG_SENSOR_GOOD;
    auto pedals2_data = pedals1_data;

    AnalogConversion_s pedals3_data;
    pedals3_data.raw = 3000;
    pedals3_data.conversion = 1.0;
    pedals3_data.status = pedals1_data.status;
    auto pedals4_data = pedals3_data;
    pedals.tick(SysTick_s{}, pedals1_data, pedals2_data, pedals3_data, pedals4_data);
    // get to enabling inverters
    state_machine.tick_state_machine(sys_time);
}

TEST(MCUStateMachineTesting, test_state_machine_init_tick)
{
    
    AMSInterface ams(0,0,0,0,0);
    BuzzerController buzzer(50);
    DrivetrainMock drivetrain;
    PedalsSystem pedals({},{});
    DashboardInterface dash_interface;
    TorqueControllerMux tc_mux;
    SafetySystem ss(&ams, 0);
    MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals, &tc_mux, &ss);
    unsigned long sys_time = 1000;
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::STARTUP);
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);
}

TEST(MCUStateMachineTesting, test_state_machine_tractive_system_activation)
{
    AMSInterface ams(0,0,0,0,0);
    BuzzerController buzzer(50);
    DrivetrainMock drivetrain;
    PedalsSystem pedals({},{});
    DashboardInterface dash_interface;
    TorqueControllerMux tc_mux;
    SafetySystem ss(&ams, 0);
    MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals, &tc_mux, &ss);
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
    sys_time += 1;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_ACTIVE);

    // hv going under thresh -> tractive system not active
    drivetrain.hv_thresh_ = false;
    sys_time += 1;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);
}

TEST(MCUStateMachineTesting, test_state_machine_tractive_system_enabling)
{
    unsigned long sys_time = 1000;

    AMSInterface ams(0,0,0,0,0);
    BuzzerController buzzer(50);
    DrivetrainMock drivetrain;
    PedalsSystem pedals({},{});
    DashboardInterface dash_interface;
    TorqueControllerMux tc_mux;

    SafetySystem ss(&ams, 0);
    MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals, &tc_mux, &ss);

    // ticking without hv over threshold testing and ensuring the tractive system not active still
    state_machine.tick_state_machine(sys_time);
    sys_time += 1;
    drivetrain.hv_thresh_ = false;
    state_machine.tick_state_machine(sys_time);
    sys_time += 1;
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);

    // hv going over threshold -> tractive system
    drivetrain.hv_thresh_ = true;
    sys_time += 1;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_ACTIVE);

    sys_time += 1;
    dash_interface.start_button_status_ = true;

    AnalogConversion_s pedals1_data;
    pedals1_data.raw = 0;
    pedals1_data.conversion = 0;
    pedals1_data.status = AnalogSensorStatus_e::ANALOG_SENSOR_GOOD;
    auto pedals2_data = pedals1_data;

    AnalogConversion_s pedals3_data;
    pedals3_data.raw = 3000;
    pedals3_data.conversion = 1.0;
    pedals3_data.status = pedals1_data.status;
    auto pedals4_data = pedals3_data;
    pedals.tick(SysTick_s{}, pedals1_data, pedals2_data, pedals3_data, pedals4_data);
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::ENABLING_INVERTERS);
}

// test getting into and out of the waiting RTD and ensuring it stays within the state when we want it to
TEST(MCUStateMachineTesting, test_state_machine_ready_to_drive_alert)
{
    AMSInterface ams(0,0,0,0,0);
    BuzzerController buzzer(50);
    DrivetrainMock drivetrain;
    PedalsSystem pedals({},{});
    DashboardInterface dash_interface;
    TorqueControllerMux tc_mux;

    SafetySystem ss(&ams, 0);
    MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals, &tc_mux, &ss);

    unsigned long sys_time = 1000;
    handle_startup(state_machine, sys_time, drivetrain, pedals, dash_interface);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::ENABLING_INVERTERS);

    drivetrain.hv_thresh_ = true;
    drivetrain.drivetrain_inited_ = true;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::WAITING_READY_TO_DRIVE_SOUND);
    sys_time += 20;

    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::WAITING_READY_TO_DRIVE_SOUND);
    sys_time += 35;

    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::READY_TO_DRIVE);
}

TEST(MCUStateMachineTesting, test_state_machine_ready_to_drive_alert_leaving)
{
    AMSInterface ams(0,0,0,0,0);
    BuzzerController buzzer(50);
    DrivetrainMock drivetrain;
    PedalsSystem pedals({},{});
    DashboardInterface dash_interface;
    TorqueControllerMux tc_mux;

    SafetySystem ss(&ams, 0);
    MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals, &tc_mux, &ss);

    unsigned long sys_time = 1000;

    drivetrain.hv_thresh_ = true;
    handle_startup(state_machine, sys_time, drivetrain, pedals, dash_interface);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::ENABLING_INVERTERS);

    drivetrain.drivetrain_inited_ = true;
    state_machine.tick_state_machine(sys_time);

    buzzer.activate_buzzer(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::WAITING_READY_TO_DRIVE_SOUND);
    sys_time += 20;

    drivetrain.hv_thresh_ = false;
    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);
}

// state transitions out of RTD state
TEST(MCUStateMachineTesting, test_state_machine_rtd_state_transitions_to_ts_active)
{

    AMSInterface ams(0,0,0,0,0);
    BuzzerController buzzer(50);
    DrivetrainMock drivetrain;
    drivetrain.drivetrain_error_ = false;
    PedalsSystem pedals({},{});
    DashboardInterface dash_interface;
    TorqueControllerMux tc_mux;

    SafetySystem ss(&ams, 0);
    MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals, &tc_mux, &ss);



    unsigned long sys_time = 1000;

    handle_startup(state_machine, sys_time, drivetrain, pedals, dash_interface);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::ENABLING_INVERTERS);

    sys_time += 70;
    drivetrain.drivetrain_inited_ = true;
    drivetrain.hv_thresh_ = true;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::WAITING_READY_TO_DRIVE_SOUND);
    sys_time += 70;
    drivetrain.hv_thresh_ = true;

    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::READY_TO_DRIVE);

    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::READY_TO_DRIVE);

    drivetrain.drivetrain_error_ = true;

    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_ACTIVE);
}

TEST(MCUStateMachineTesting, test_state_machine_rtd_state_transitions_to_ts_not_active)
{

    AMSInterface ams(0,0,0,0,0);
    BuzzerController buzzer(50);
    DrivetrainMock drivetrain;
    drivetrain.drivetrain_error_ = false;
    PedalsSystem pedals({},{});
    DashboardInterface dash_interface;

    TorqueControllerMux tc_mux;

    SafetySystem ss(&ams, 0);
    MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface, &pedals, &tc_mux, &ss);
   
   
   
    unsigned long sys_time = 1000;

    handle_startup(state_machine, sys_time, drivetrain, pedals, dash_interface);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::ENABLING_INVERTERS);

    sys_time += 70;
    drivetrain.drivetrain_inited_ = true;
    drivetrain.hv_thresh_ = true;
    state_machine.tick_state_machine(sys_time);
    EXPECT_EQ(state_machine.get_state(), CAR_STATE::WAITING_READY_TO_DRIVE_SOUND);
    sys_time += 70;
    drivetrain.hv_thresh_ = true;

    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::READY_TO_DRIVE);

    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::READY_TO_DRIVE);

    // drivetrain.drivetrain_error_ = true;

    drivetrain.hv_thresh_ = false;
    state_machine.tick_state_machine(sys_time);

    EXPECT_EQ(state_machine.get_state(), CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);
}

#endif /* STATE_MACHINE_TEST */
