#ifndef DRIVEBRAIN_CONTROLLER_TEST
#define DRIVEBRAIN_CONTROLLER_TEST
#include <DrivebrainController.h>
#include <DrivebrainData.h>
#include <gtest/gtest.h>

auto runTick(DrivebrainController *controller,
             float last_DB_receive_time_millis, float last_receive_time_millis,
             ControllerMode_e current_control_mode,
             unsigned long systick_millis, float brakePercent,
             float accelPercent) {
  DrivebrainData_s data;
  data.last_receive_time_millis = last_receive_time_millis;
  data.DB_prev_MCU_recv_millis = last_DB_receive_time_millis;
  data.torque_limits_nm = {1, 1, 1, 1};
  data.speed_setpoints_rpm = {1, 1, 1, 1};

  SysTick_s systick;
  systick.millis = systick_millis;
  systick.micros = 1000;

  TorqueControllerMuxStatus status = {};
  status.current_controller_mode_ = current_control_mode;
  PedalsSystemData_s pedals_data = {};
  pedals_data.regenPercent = brakePercent;
  pedals_data.accelPercent = accelPercent;
  SharedCarState_s state(systick, {/*steering data*/}, {/*drivetrain_data*/},
                         {/*loadcell_data*/}, {/*raw_loadcell_data*/},
                         pedals_data, {}, data, status);
  return controller->evaluate(state);
}

TEST(DrivebrainControllerTesting, signals_sent_within_range) {
  DrivebrainController controller(10);
  auto torque_controller_output_s =
      runTick(&controller, 998, 1001, ControllerMode_e::MODE_4, 1002, 0.0f, 0.0f);
  EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

TEST(DrivebrainControllerTesting, setpoint_too_latent_still_in_control) {
  DrivebrainController controller(5);
  auto torque_controller_output_s = runTick(
      &controller, 800, 1006, ControllerMode_e::MODE_4, 1012, 1.0f, 0.0f);
  EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
  EXPECT_FLOAT_EQ(torque_controller_output_s.command.torqueSetpoints[0], PhysicalParameters::MAX_REGEN_TORQUE);
}

TEST(DrivebrainControllerTesting, failing_stay_failing) {
  DrivebrainController controller(10);
  auto torque_controller_output_s = runTick(
      &controller, 200, 1011, ControllerMode_e::MODE_4, 1032, 0.01f, 0.0f);
  EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

  torque_controller_output_s = runTick(
      &controller, 200, 1033, ControllerMode_e::MODE_4, 1033, 0.01f, 0.0f);
  EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

  torque_controller_output_s = runTick(
      &controller, 400, 1034, ControllerMode_e::MODE_4, 1034, 0.01f, 0.0f);
  EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);
}

TEST(DrivebrainControllerTesting, failing_reset_success) {
  DrivebrainController controller(10);
  auto torque_controller_output_s =
      runTick(&controller, 300, 1011, ControllerMode_e::MODE_4, 1022, 0.01f, 0.0f);
  EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 0);

  torque_controller_output_s =
      runTick(&controller, 1020, 1021, ControllerMode_e::MODE_3, 1023, 0.01f, 0);
  torque_controller_output_s =
      runTick(&controller, 1022, 1022, ControllerMode_e::MODE_4, 1024, 0.01f, 0);
  EXPECT_FLOAT_EQ(torque_controller_output_s.command.speeds_rpm[0], 1);
}

#endif