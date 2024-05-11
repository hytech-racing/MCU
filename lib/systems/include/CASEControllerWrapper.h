#ifndef __CASECONTROLLERWRAPPER_H__
#define __CASECONTROLLERWRAPPER_H__
#include "BaseController.h"

#include "CASESystem.h"

template <typename message_queue>
class TorqueControllerCASEWrapper : public virtual Controller
{
public:
    TorqueControllerCASEWrapper() = delete;
    
    TorqueControllerCASEWrapper(CASESystem<message_queue> *case_instance) : case_instance_(case_instance)
    {
    }
    TorqueControllerOutput_s evaluate(const car_state &state) override
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