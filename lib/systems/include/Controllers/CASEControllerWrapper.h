#ifndef __CASECONTROLLERWRAPPER_H__
#define __CASECONTROLLERWRAPPER_H__
#include "BaseController.h"

#include "CASESystem.h"

template <typename message_queue>
class TorqueControllerCASEWrapper : public virtual Controller
{
public:
    TorqueControllerCASEWrapper() = delete;
    /// @brief makes CASE system apart of Controller hierarchy for use in TC Mux
    /// @param case_instance 
    TorqueControllerCASEWrapper(CASESystem<message_queue> *case_instance) : case_instance_(case_instance)
    {
    }
    /// @brief packages CASE system command into Torque Controller Output
    /// @param SharedCarState_s &state
    /// @return TorqueControllerOutput_s
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