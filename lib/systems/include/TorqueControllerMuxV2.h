#ifndef TORQUECONTROLLERMUX
#define TORQUECONTROLLERMUX

#include <array>
// #include "TorqueControllers.h"
#include "SharedDataTypes.h"

// notes:
// 21 torque limit should be first

// tc mux needs to handle these things:
// 1 swapping between controller outputs
// 2 turning on and off running of controllers
// 3 application of safeties and limits to controller outputs
// 4 torque limit changing (torque mode) -->
// TODO the torque limit value changing should be handled in the dashboard interface

namespace TC_MUX_DEFAULT_PARAMS
{
    const float MAX_SPEED_FOR_MODE_CHANGE = 5.0;        // m/s
    const float MAX_TORQUE_DELTA_FOR_MODE_CHANGE = 0.5; // Nm
}

class Controller
{
private:
    // common function for calculation of the limited torque request that goes into controllers
    float get_torque_request_(float torque_limit_nm, const PedalsSystemData_s &pedals_data) { return 0; };

public:
    virtual TorqueControllerOutput_s evaluate(const car_state &state) = 0;
};

// namespace TC_MUX
// {
template <std::size_t num_controllers>
class TorqueControllerMuxv2
{
    static_assert(num_controllers >= 1, "Must create TC mux with at least 1 controller");

private:
    std::array<Controller *, num_controllers> controller_pointers_;
    std::array<bool, num_controllers> mux_bypass_limits_;

    std::unordered_map<TorqueLimit_e, float> torque_limit_map_ = {
        {TorqueLimit_e::TCMUX_LOW_TORQUE, AMK_MAX_TORQUE},
        {TorqueLimit_e::TCMUX_MID_TORQUE, 15.0},
        {TorqueLimit_e::TCMUX_FULL_TORQUE, 10.0}};
    float max_change_speed_, max_torque_pos_change_delta_;
    DrivetrainCommand_s prev_command_ = {};
    TorqueControllerMuxStatus current_status_ = {};
    TorqueControllerMuxError can_switch_controller_(DrivetrainDynamicReport_s current_drivetrain_data,
                                                    DrivetrainCommand_s previous_controller_command,
                                                    DrivetrainCommand_s desired_controller_out);
    DrivetrainCommand_s apply_positive_speed_limit_(const DrivetrainCommand_s &command);
    DrivetrainCommand_s apply_torque_limit_(const DrivetrainCommand_s &command, float max_torque);
    DrivetrainCommand_s apply_power_limit_(const DrivetrainCommand_s &command, const DrivetrainDynamicReport_s &drivetrain, float power_limit, float max_torque);
    DrivetrainCommand_s apply_regen_limit_(const DrivetrainCommand_s &command, const DrivetrainDynamicReport_s &drivetrain_data);
public:
    TorqueControllerMuxv2(std::array<Controller *, num_controllers> controller_pointers,
                          std::array<bool, num_controllers> mux_bypass_limits,
                          float max_change_speed = TC_MUX_DEFAULT_PARAMS::MAX_SPEED_FOR_MODE_CHANGE,
                          float max_torque_pos_change_delta = TC_MUX_DEFAULT_PARAMS::MAX_TORQUE_DELTA_FOR_MODE_CHANGE) : controller_pointers_(controller_pointers),
                                                                                                                         mux_bypass_limits_(mux_bypass_limits),
                                                                                                                         max_change_speed_(max_change_speed),
                                                                                                                         max_torque_pos_change_delta_(max_torque_pos_change_delta_)

    {
    }

    const TorqueControllerMuxStatus &get_tc_mux_status() { return current_status_; }

    DrivetrainCommand_s getDrivetrainCommand(ControllerMode_e requested_controller_type,
                                             TorqueLimit_e controller_command_torque_limit,
                                             const car_state &input_state);
};
// }
#include "TorqueControllerMuxV2.tpp"
#endif // __TORQUECONTROLLERMUXV2_H__