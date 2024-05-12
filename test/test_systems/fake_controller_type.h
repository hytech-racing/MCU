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
    TorqueControllerOutput_s evaluate(const car_state &state) override { return output; }
    // void update_input_state(const car_state &state) override { }
};
#endif // __FAKE_CONTROLLER_TYPE_H__