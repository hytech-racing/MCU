#ifndef __FAKE_CONTROLLER_TYPE_H__
#define __FAKE_CONTROLLER_TYPE_H__
#include "BaseController.h"
struct dummy_queue
{
};

class TestControllerType : public virtual Controller
{

public:
    TorqueControllerOutput_s output;
    TorqueControllerOutput_s evaluate(const SharedCarState_s &state) override { return output; }
};
#endif // __FAKE_CONTROLLER_TYPE_H__