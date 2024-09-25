#ifndef __CASECONTROLLERWRAPPER_H__
#define __CASECONTROLLERWRAPPER_H__
#include "BaseController.h"

#include "CASESystem.h"

template <typename message_queue>
/// @brief makes CASE system a part of Controller hierarchy for use in TC Mux
class TorqueControllerCASEWrapper : public virtual Controller
{
public:
    TorqueControllerCASEWrapper() = delete;
    /// @param case_instance requires current state estimator instance to give access of the CASE instance to this specific controller so that it can update/control it.
    /// @note This also ensures there are not duplicates of this system for safety.
    TorqueControllerCASEWrapper(CASESystem<message_queue> *case_instance) : case_instance_(case_instance)
    {
    }
    /// @brief packages CASE system command into Torque Controller Output
    /// @param state this state is updated by the CASE system in main repeatedly
    TorqueControllerOutput_s evaluate(const SharedCarState_s &state) override
    {
        DrivetrainCommand_s curr_cmd = case_instance_->get_current_drive_command();
        TorqueControllerOutput_s out;
        out.ready = true;
        out.command = curr_cmd;
        return out;
    }

private:
    CASESystem<message_queue> *case_instance_;

};

#endif // __CASECONTROLLERWRAPPER_H__