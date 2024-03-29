#ifndef DRIVETRAIN_SYSTEM_TEST
#define DRIVETRAIN_SYSTEM_TEST
#include "DrivetrainSystem.h"

// TODO @ben
// TODO handle startup sequence stuff
struct InverterCommand
{
    float torque_setpoint_nm;
    float speed_setpoint_rpm;
};
class InverterMock
{
public:
    int request_enable_hv_count_ = 0;
    int request_enable_inverter_count_ = 0;
    float torque_setpoint_nm_ = 0;
    float speed_setpoint_rpm_ = 0;

    int cmd_no_t_count_ = 0;
    int cmd_reset_count_ = 0;
    int cmd_general_count_ = 0;
    int cmd_disable_count_ = 0;

    InverterMock()
    {

        request_enable_hv_count_ = 0;
        request_enable_inverter_count_ = 0;
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

    // periodic commands
    void command_no_torque(){cmd_no_t_count_++;};
    void command_reset() { 
        cmd_reset_count_++;
        error_ = false; };
    void handle_command(const InverterCommand &cmd)
    {
        cmd_general_count_++;
        torque_setpoint_nm_ = cmd.torque_setpoint_nm;
        speed_setpoint_rpm_ = cmd.speed_setpoint_rpm;
    };
    void disable() {
        cmd_disable_count_++;
    }

    bool error() { return error_; };
    bool inverter_system_ready() { return system_ready_; };

    uint16_t dc_bus_voltage() { return voltage_; };
    bool dc_quit_on() { return dc_quit_on_; }
    bool get_quit_dc_on() { return dc_quit_on_; }
    bool get_quit_inverter_on() { return quit_inverter_on_; }
};

TEST(DrivetrainSystemTesting, test_drivetrain_startup)
{
    
    InverterMock inv_fl, inv_fr, inv_rl, inv_rr;
    MCUInterface mcu;
    DrivetrainSystem<InverterMock> dt({&inv_fl, &inv_fr, &inv_rl, &inv_rr}, &mcu, 1000);
    unsigned long sys_time = 1000;
    // inverters are not ready so an inverter startup call shouldnt send any requests to the inverter
    // to start the initialization process
    EXPECT_FALSE(dt.handle_inverter_startup(sys_time));
    EXPECT_EQ(inv_fl.request_enable_hv_count_, 0);
    EXPECT_EQ(inv_fr.request_enable_hv_count_, 0);
    EXPECT_EQ(inv_rl.request_enable_hv_count_, 0);
    EXPECT_EQ(inv_rr.request_enable_hv_count_, 0);

    inv_fl.system_ready_ = true;
    inv_fr.system_ready_ = true;
    inv_rl.system_ready_ = true;
    inv_rr.system_ready_ = true;

    // this should enable the drivetrain hv
    EXPECT_FALSE(dt.handle_inverter_startup(sys_time));

    EXPECT_TRUE(inv_fl.dc_quit_on_);
    EXPECT_TRUE(inv_fr.dc_quit_on_);
    EXPECT_TRUE(inv_rl.dc_quit_on_);
    EXPECT_TRUE(inv_rr.dc_quit_on_);

    // im just gonna test one from now on for this type of stuff
    EXPECT_EQ(inv_rr.request_enable_hv_count_, 1);
    EXPECT_EQ(inv_rr.request_enable_inverter_count_, 0); // this should enable the inverters
    EXPECT_FALSE(dt.handle_inverter_startup(sys_time));

    EXPECT_EQ(inv_rr.request_enable_hv_count_, 1);
    EXPECT_EQ(inv_rr.request_enable_inverter_count_, 1);

    EXPECT_TRUE(dt.handle_inverter_startup(sys_time));
}

TEST(DrivetrainSystemTesting, test_drivetrain_init_timeout)
{
    InverterMock inv_fl, inv_fr, inv_rl, inv_rr;
    MCUInterface mcu;
    DrivetrainSystem<InverterMock> dt({&inv_fl, &inv_fr, &inv_rl, &inv_rr}, &mcu, 1000);
    unsigned long sys_time = 1000;
    // test and make sure that normally the drivetrain doesnt timeout when changing the time
    EXPECT_FALSE(dt.handle_inverter_startup(sys_time));
    inv_fl.system_ready_ = true;
    inv_fr.system_ready_ = true;
    inv_rl.system_ready_ = true;
    inv_rr.system_ready_ = true;
    sys_time += 10;
    // tick to request hv enable
    EXPECT_FALSE(dt.handle_inverter_startup(sys_time));

    sys_time += 10;
    // tick to request enable inverters
    EXPECT_FALSE(dt.handle_inverter_startup(sys_time));

    sys_time += 10;
    // tick to check inverters status
    EXPECT_TRUE(dt.handle_inverter_startup(sys_time));
    EXPECT_FALSE(dt.inverter_init_timeout(sys_time));

    // test timeout
    InverterMock inv_fl2, inv_fr2, inv_rl2, inv_rr2;
    DrivetrainSystem<InverterMock> dt2({&inv_fl2, &inv_fr2, &inv_rl2, &inv_rr2}, &mcu,1000);
    unsigned long sys_time2 = 1000;

    EXPECT_FALSE(dt2.handle_inverter_startup(sys_time2));
    // inv_fl.system_ready_ = true;
    inv_fr2.system_ready_ = true;
    inv_rl2.system_ready_ = true;
    inv_rr2.system_ready_ = true;
    sys_time2 += 1050;
    EXPECT_TRUE(dt.inverter_init_timeout(sys_time2));
}

TEST(DrivetrainSystemTesting, test_drivetrain_inverter_comms)
{

    InverterMock inv_fl, inv_fr, inv_rl, inv_rr;
    MCUInterface mcu;
    DrivetrainSystem<InverterMock> dt({&inv_fl, &inv_fr, &inv_rl, &inv_rr}, &mcu, 1000);
    dt.command_drivetrain({{1000.0, 1001.0, 1002.0, 1003.0}, {2000.0, 2001.0, 2002.0, 2003.0}});

    //  torque_setpoint_nm_
    //  speed_setpoint_rpm_
    // ensure that without ticking the inverters dont get the data
    // as of 3/13/24 this isnt being handled by the drivetrain rn
    // EXPECT_EQ(inv_fl.speed_setpoint_rpm_, 0.0);
    // EXPECT_EQ(inv_fl.torque_setpoint_nm_, 0);

    // EXPECT_EQ(inv_fr.torque_setpoint_nm_, 0);
    // EXPECT_EQ(inv_fr.speed_setpoint_rpm_, 0);

    // EXPECT_EQ(inv_rl.torque_setpoint_nm_, 0);
    // EXPECT_EQ(inv_rl.speed_setpoint_rpm_, 0);

    // EXPECT_EQ(inv_rr.torque_setpoint_nm_, 0);
    // EXPECT_EQ(inv_rr.speed_setpoint_rpm_, 0);
    SysClock clock;
    auto micros = 1000000;
    dt.tick(clock.tick(micros));
    dt.command_drivetrain({{1000.0, 1001.0, 1002.0, 1003.0}, {2000.0, 2001.0, 2002.0, 2003.0}});
    EXPECT_EQ(inv_fl.speed_setpoint_rpm_, 1000.0);
    EXPECT_EQ(inv_fl.torque_setpoint_nm_, 2000.0);

    EXPECT_EQ(inv_fr.torque_setpoint_nm_, 2001.0);
    EXPECT_EQ(inv_fr.speed_setpoint_rpm_, 1001.0);

    EXPECT_EQ(inv_rl.torque_setpoint_nm_, 2002.0);
    EXPECT_EQ(inv_rl.speed_setpoint_rpm_, 1002.0);

    EXPECT_EQ(inv_rr.torque_setpoint_nm_, 2003.0);
    EXPECT_EQ(inv_rr.speed_setpoint_rpm_, 1003.0);

    // testing to ensure that these extra general commands dont get through the period filter
    // as of 3/13/24, the inverter sending rate is being handled at the inverter interface
    // TODO decide if we want to add this back into the drivetrain
    // micros += (20 * 1000);
    // dt.tick(clock.tick(micros));
    // dt.command_drivetrain({{1000.0, 1001.0, 1002.0, 1003.0}, {2000.0, 2001.0, 2002.0, 2003.0}});
    // dt.command_drivetrain({{1000.0, 1001.0, 1002.0, 1003.0}, {2000.0, 2001.0, 2002.0, 2003.0}});
    // dt.command_drivetrain({{1000.0, 1001.0, 1002.0, 1003.0}, {2000.0, 2001.0, 2002.0, 2003.0}});
    // EXPECT_EQ(inv_rl.cmd_general_count_, 1);
    // micros += (20 * 1000);
    // dt.tick(clock.tick(micros));
    // dt.command_drivetrain({{1000.0, 1001.0, 1002.0, 1003.0}, {2000.0, 2001.0, 2002.0, 2003.0}});
    // EXPECT_EQ(inv_rl.cmd_general_count_, 2);
}
// TODO test commanding of drivetrain to ensure that the data is getting accross correctly
#endif /* DRIVETRAIN_SYSTEM_TEST */
