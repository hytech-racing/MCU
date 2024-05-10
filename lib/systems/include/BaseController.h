#ifndef BASECONTROLLER
#define BASECONTROLLER
#include "SharedDataTypes.h"

class Controller
{
private:
    // common function for calculation of the limited torque request that goes into controllers
    float get_torque_request_(float torque_limit_nm, const PedalsSystemData_s &pedals_data) { return 0; };

public:
    virtual TorqueControllerOutput_s evaluate(const car_state &state) = 0;
};

#endif