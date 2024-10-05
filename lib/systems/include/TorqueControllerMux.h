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
// - [x] make the controllers inherit from the base controller class
//      - [x] port TorqueControllerSimple
//      - [x] port TorqueControllerLoadCellVectoring
//      - [x] port BaseLaunchController
//      - [x] port TorqueControllerSimpleLaunch
//      - [x] port slip launch
//      - [x] port TorqueControllerLookupLaunch
//      - [x] port CASE 
// - [x] add the torque limit evaluation logic into dashboard interface
// - [x] integrate into state machine
//   - [x] pass through the car state
//   - [x] get dial and torque mode from the dashboard
// - [x] create car_state in main and pass into state machine
// - [x] add 3 bit status to a telemetry message for the TC mux status to HT_CAN 
// - [x] pass state of tc mux into telem interface and add the CAN signal
// - [x] remove the old tc mux
// - [ ] add back checking of the ready flag of the controllers and if the controller isnt ready it defaults
//        - [ ] add test for this
// - [ ] make folder for the controllers
// - [ ] write integration tests for the real controllers
//      - [x] test construction with real controllers
//      - [ ] ensure that sane outputs occur on first tick of each controller
// - [x] update the state machine unit test with integration test of new tc mux

// ON CAR testing
// - [ ] test the change of the torque mode from the dashboard interface
//      - [ ] write testing code for this in separate environment


/// @brief Contains a max speed for mode changes(5 m/s), a max torque delta for mode change(.5 nm) and a max power limit(63000 W).
///        These values are used in the event that no value is provided for them in the constructor. 
namespace TC_MUX_DEFAULT_PARAMS
{
    constexpr const float MAX_SPEED_FOR_MODE_CHANGE = 5.0;        // m/s
    constexpr const float MAX_TORQUE_DELTA_FOR_MODE_CHANGE = 0.5; // Nm
    constexpr const float MAX_POWER_LIMIT = 63000.0; // watts of mechanical power
};

template <std::size_t num_controllers>
class TorqueControllerMux
{
    static_assert(num_controllers > 0, "Must create TC mux with at least 1 controller");

    

private:
    std::array<Controller *, num_controllers> controller_pointers_;

    std::array<bool, num_controllers> mux_bypass_limits_;

    std::unordered_map<TorqueLimit_e, float> torque_limit_map_ = {
        {TorqueLimit_e::TCMUX_FULL_TORQUE, PhysicalParameters::AMK_MAX_TORQUE},
        {TorqueLimit_e::TCMUX_MID_TORQUE, 15.0f},
        {TorqueLimit_e::TCMUX_LOW_TORQUE, 10.0f}};
    float max_change_speed_, max_torque_pos_change_delta_, max_power_limit_;
    DrivetrainCommand_s prev_command_ = {};
    TorqueControllerMuxStatus active_status_ = {};
    TorqueControllerMuxError can_switch_controller_(DrivetrainDynamicReport_s active_drivetrain_data,
                                                    DrivetrainCommand_s previous_controller_command,
                                                    DrivetrainCommand_s desired_controller_out);

    /// @brief Clamps negative rpms to 0f
    /// @param const DrivetrainCommand_s &command provides the rpm info as a DrivetrainCommand_s
    /// @return DrivetrainCommand_s to update the drivetrain command in the getDrivetrainCommand method
    DrivetrainCommand_s apply_positive_speed_limit_(const DrivetrainCommand_s &command);

    /// @brief Ensure torque is at most at the specified limit. If exceeding, then limit it in the returned DrivetrainCommand_s
    /// @param const DrivetrainCommand_s &command is a DrivetrainCommand_s, which provides torque info
    /// @param float max_torque this is the maximum average torque the wheels are allowed to experience before it is limited.
    /// @return DrivetrainCommand_s to update the drivetrain command in the getDrivetrainCommand method
    DrivetrainCommand_s apply_torque_limit_(const DrivetrainCommand_s &command, float max_torque);
    
    /// @brief Apply power limit (watts) such that the mechanical power of all wheels never exceeds the preset mechanical power limit. Scales all wheels down to preserve functionality of torque controllers
    /// @param const DrivetrainCommand_s &command provides torque info, which is used to calculate mechanical power
    /// @param const DrivetrainDynamicReport_s &drivetrain provides RPMS, which are used to calculate radians / s
    /// @param float max_torque is used to indirectly specifiy the max power
    /// @return DrivetrainCommand_s to update the drivetrain command in the getDrivetrainCommand method
    DrivetrainCommand_s apply_power_limit_(const DrivetrainCommand_s &command, const DrivetrainDynamicReport_s &drivetrain, float power_limit, float max_torque);

    /// @brief begin limiting regen at noRegenLimitKPH (hardcoded in func) and completely limit regen at fullRegenLimitKPH (hardcoded in func)
    /// @param const DrivetrainCommand_s &command 
    /// @param const DrivetrainDynamicReport_s &drivetrain_data provides RPMs
    /// @return DrivetrainCommand_s to update the drivetrain command in the getDrivetrainCommand method
    DrivetrainCommand_s apply_regen_limit_(const DrivetrainCommand_s &command, const DrivetrainDynamicReport_s &drivetrain_data);
    
public:
    
    TorqueControllerMux() = delete;
    /// @brief constructor for the TC mux
    /// @param controller_pointers the array of pointers to the controllers being muxed between
    /// @param mux_bypass_limits the array of aligned bools for determining if the limits should be applied to the controller outputs defaults to TC_MUX_DEFAULT_PARAMS::MAX_SPEED_FOR_MODE_CHANGE
    /// @param max_change_speed the max speed difference between the requested controller output and the actual speed of each wheel that if the controller has a diff larger than the mux will not switch to the requested controller
    /// @param max_torque_pos_change_delta same as speed but evaluated between the controller commanded torques defaults to TC_MUX_DEFAULT_PARAMS::MAX_TORQUE_DELTA_FOR_MODE_CHANGE
    /// @param max_power_limit the max power limit defaults to TC_MUX_DEFAULT_PARAMS::MAX_POWER_LIMIT
    /// @note TC Mux must be created with at least 1 controller.
    explicit TorqueControllerMux(std::array<Controller *, num_controllers> controller_pointers,
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
    
    const TorqueControllerMuxStatus &get_tc_mux_status() { return active_status_; }

    /// @brief function that evaluates the mux, controllers and gets the active command
    /// @param requested_controller_type the requested controller type from the dial state
    /// @param controller_command_torque_limit the torque limit state enum set by dashboard
    /// @param input_state the active state of the car
    /// @return the active DrivetrainCommand_s to be sent to the drivetrain to command increases and decreases in torque
    DrivetrainCommand_s getDrivetrainCommand(ControllerMode_e requested_controller_type,
                                             TorqueLimit_e controller_command_torque_limit,
                                             const SharedCarState_s &input_state);
};
// }

const int number_of_controllers = 5;
using TCMuxType = TorqueControllerMux<number_of_controllers>;

#include "TorqueControllerMux.tpp"
#endif // __TorqueControllerMux_H__
