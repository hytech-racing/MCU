#ifndef TORQUECONTROLLERMUX
#define TORQUECONTROLLERMUX

#include <array>
#include "SharedDataTypes.h"
#include "BaseController.h"

// notes:
// 21 torque limit should be first

// tc mux needs to handle these things:
// 1 swapping between controller outputs
// 2 turning on and off running of controllers
// 3 application of safeties and limits to controller outputs
// 4 torque limit changing (torque mode) -->
// TODO the torque limit value changing should be handled in the dashboard interface


// TODOs
// - [-] make the controllers inherit from the base controller class
//      - [x] port TorqueControllerSimple
//      - [x] port TorqueControllerLoadCellVectoring
//      - [x] port BaseLaunchController
//      - [x] port TorqueControllerSimpleLaunch
//      - [x] port slip launch
//      - [x] port TorqueControllerLookupLaunch
//      - [ ] port CASE 
// - [ ] integrate into state machine
//   - [ ] set the car_state from all sources
//   - [ ] get dial and torque mode from the dashboard
// - [ ] write integration test for the real controllers
// - [ ] update the state machine unit test with integration test of new tc mux



namespace TC_MUX_DEFAULT_PARAMS
{
    const float MAX_SPEED_FOR_MODE_CHANGE = 5.0;        // m/s
    const float MAX_TORQUE_DELTA_FOR_MODE_CHANGE = 0.5; // Nm
    const float MAX_POWER_LIMIT = 630000.0;
};


// namespace TC_MUX
// {


template <std::size_t num_controllers>
class TorqueControllerMuxv2
{
    static_assert(num_controllers > 0, "Must create TC mux with at least 1 controller");

    

private:
    std::array<Controller *, num_controllers> controller_pointers_;

    std::array<bool, num_controllers> mux_bypass_limits_;

    std::unordered_map<TorqueLimit_e, float> torque_limit_map_ = {
        {TorqueLimit_e::TCMUX_LOW_TORQUE, AMK_MAX_TORQUE},
        {TorqueLimit_e::TCMUX_MID_TORQUE, 15.0},
        {TorqueLimit_e::TCMUX_FULL_TORQUE, 10.0}};
    float max_change_speed_, max_torque_pos_change_delta_, max_power_limit_;
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
    
    TorqueControllerMuxv2() = delete;
    /// @brief constructor for the TC mux
    /// @param controller_pointers the array of pointers to the controllers being muxed between
    /// @param mux_bypass_limits the array of aligned bools for determining if the limits should be applied to the controller outputs defaults to TC_MUX_DEFAULT_PARAMS::MAX_SPEED_FOR_MODE_CHANGE
    /// @param max_change_speed the max speed difference between the requested controller output and the actual speed of each wheel that if the controller has a diff larger than the mux will not switch to the requested controller
    /// @param max_torque_pos_change_delta same as speed but evaluated between the controller commanded torques defaults to TC_MUX_DEFAULT_PARAMS::MAX_TORQUE_DELTA_FOR_MODE_CHANGE
    /// @param max_power_limit the max power limit defaults to TC_MUX_DEFAULT_PARAMS::MAX_POWER_LIMIT
    explicit TorqueControllerMuxv2(std::array<Controller *, num_controllers> controller_pointers,
                          std::array<bool, num_controllers> mux_bypass_limits,
                          float max_change_speed = TC_MUX_DEFAULT_PARAMS::MAX_SPEED_FOR_MODE_CHANGE,
                          float max_torque_pos_change_delta = TC_MUX_DEFAULT_PARAMS::MAX_TORQUE_DELTA_FOR_MODE_CHANGE,
                          float max_power_limit = TC_MUX_DEFAULT_PARAMS::MAX_POWER_LIMIT) : controller_pointers_(controller_pointers),
                                                                                            mux_bypass_limits_(mux_bypass_limits),
                                                                                            max_change_speed_(max_change_speed),
                                                                                            max_torque_pos_change_delta_(max_torque_pos_change_delta),
                                                                                            max_power_limit_(max_power_limit)


    {
        static_assert(num_controllers > 0, "Must create TC mux with at least 1 controller");

    }

    const TorqueControllerMuxStatus &get_tc_mux_status() { return current_status_; }

    /// @brief function that evaluates the mux, controllers and gets the current command
    /// @param requested_controller_type the requested controller type from the dial state
    /// @param controller_command_torque_limit the torque limit state enum set by dashboard
    /// @param input_state the current state of the car
    /// @return the current drivetrain command to be sent to the drivetrain
    DrivetrainCommand_s getDrivetrainCommand(ControllerMode_e requested_controller_type,
                                             TorqueLimit_e controller_command_torque_limit,
                                             const car_state &input_state);
};
// }
#include "TorqueControllerMuxV2.tpp"
#endif // __TORQUECONTROLLERMUXV2_H__