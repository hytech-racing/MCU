#include "Drivetrain.h"

DRIVETRAIN_STATE DrivetrainComponent::handle_state_machine(unsigned long curr_time)
{
  switch (state_)
  {
  case DRIVETRAIN_STATE::WAIT_SYSTEM_READY:
    if (drivetrain_ready())
    {
      enable_drivetrain_hv(curr_time);
      set_state_(DRIVETRAIN_STATE::WAIT_QUIT_DC_ON);
    }
    break;

  case DRIVETRAIN_STATE::WAIT_QUIT_DC_ON:
    if (check_drivetrain_quit_dc_on_())
    {
      command_drivetrain_no_torque();
      set_drivetrain_driver_enable_(true);
      set_drivetrain_enable_inverters_(true);
      set_state_(DRIVETRAIN_STATE::WAIT_QUIT_INVERTER_ON);
    }
    break;

  case DRIVETRAIN_STATE::WAIT_QUIT_INVERTER_ON:
    if (check_drivetrain_quit_dc_on_())
    {
      set_state_(DRIVETRAIN_STATE::RTD);
    }
    break;
  case DRIVETRAIN_STATE::RTD:
    break;
  }
  return state_;
}