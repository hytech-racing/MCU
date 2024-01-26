#include <unity.h>
#include "MCUStateMachine.h"
#include "PedalsSystem.h"
class DrivetrainMock
{
public:


    bool drivetrain_ready_;
    bool drivetrain_ready() {};
    /// @param curr_time current system tick time (millis()) that sets the init phase start time
    void enable_drivetrain_hv(unsigned long curr_time){};

    // startup phase 2
    bool check_drivetrain_quit_dc_on() {};

    // on entry logic
    void request_enable() {};
    void command_drivetrain_no_torque() {};

    // final check for drivetrain initialization to check if quit inverter on
    bool drivetrain_enabled(){};

    // check to see if init time limit has passed
    bool inverter_init_timeout(unsigned long curr_time) {};

    bool hv_over_threshold_on_drivetrain() {};
    void disable() {};
    bool drivetrain_error_occured() {};

    void command_drivetrain(const DrivetrainCommand &data) {};
};


BuzzerController buzzer(500);



DrivetrainMock drivetrain;

DashboardInterface dash_interface;

MCUStateMachine<DrivetrainMock> state_machine(&buzzer, &drivetrain, &dash_interface);

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
    //   STR_TO_TEST = "";
}

void test_state_machine_init_tick(void)
{
    unsigned long sys_time = 1000;
    TEST_ASSERT_TRUE(state_machine.get_state() == CAR_STATE::STARTUP);
    state_machine.tick_state_machine(sys_time);
    TEST_ASSERT_TRUE(state_machine.get_state() == CAR_STATE::TRACTIVE_SYSTEM_NOT_ACTIVE);
}

int main()
{
    //   delay(2000); // service delay
    UNITY_BEGIN();

    RUN_TEST(test_state_machine_init_tick);
    

    UNITY_END(); // stop unit testing
}
