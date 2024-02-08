#ifndef DRIVETRAIN_SYSTEM_TEST
#define DRIVETRAIN_SYSTEM_TEST
#include "DrivetrainSystem.h"

// TODO @ben
// TODO handle startup sequence stuff

class InverterMock
{
public:
    int request_enable_hv_count_, request_enable_inverter_count_;

    InverterMock()
    {
        int request_enable_hv_count_ = 0;
        int request_enable_inverter_count_ = 0;
        error_ = false;
        system_ready_ = false;
        dc_quit_on_ = false;
        quit_inverter_on_ = false;
    };

    bool error_, system_ready_, dc_quit_on_, quit_inverter_on_;
    uint16_t voltage_;

    // want to ensure that we are only sending requests once at a time
    // stage 1
    void request_enable_hv()
    {
        request_enable_hv_count_++;
        dc_quit_on_ = true;
    };
    // stage 2
    void request_enable_inverter()
    {
        request_enable_inverter_count_++;
        quit_inverter_on_ = true;
    };

    void command_no_torque(){};
    bool error() { return error_; };
    bool inverter_system_ready() { return system_ready_; };
    void command_reset() { error_ = false; };
    uint16_t dc_bus_voltage() { return voltage_; };
    bool dc_quit_on() { return dc_quit_on_; }
    bool quit_inverter_on() { return quit_inverter_on_; }
};

// TODO
TEST(DrivetrainSystemTesting, test_drivetrain_startup)
{
    InverterMock inv_fl, inv_fr, inv_rl, inv_rr;
    DrivetrainSystem<InverterMock> dt({&inv_fl, &inv_fr, &inv_rl, &inv_rr}, 1000);
}
// TODO test startup timeout

// TODO test commanding of drivetrain to ensure that the data is getting accross correctly
#endif /* DRIVETRAIN_SYSTEM_TEST */
