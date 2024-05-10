#ifndef __CASECONTROLLERWRAPPER_H__
#define __CASECONTROLLERWRAPPER_H__
#include "BaseController.h"

#include "CASESystem.h"

class TorqueControllerCASEWrapper : 
{
public:
    
    TorqueControllerCASEWrapper(const CASESystem& case_instance) :  case_instance_(case_instance)
    {
    }
    TorqueControllerOutput_s evaluate(const car_state &state) override;
private:
    const CASESystem& case_instance_;
};

#endif // __CASECONTROLLERWRAPPER_H__