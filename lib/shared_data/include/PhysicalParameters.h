#ifndef __PHYSICALPARAMETERS_H__
#define __PHYSICALPARAMETERS_H__

namespace PhysicalParameters
{
    const float AMK_MAX_RPM = 20000;
    const float AMK_MAX_TORQUE = 21.42; 
    const float MAX_REGEN_TORQUE = 10.0;

}
constexpr const float GEARBOX_RATIO               = 11.86;
constexpr const float WHEEL_DIAMETER              = 0.4064; // meters
constexpr const float RPM_TO_METERS_PER_SECOND    = WHEEL_DIAMETER * 3.1415 / GEARBOX_RATIO / 60.0;
constexpr const float RPM_TO_KILOMETERS_PER_HOUR  = RPM_TO_METERS_PER_SECOND * 3600.0 / 1000.0;
constexpr const float METERS_PER_SECOND_TO_RPM    = 1.0 / RPM_TO_METERS_PER_SECOND;

const float RPM_TO_RAD_PER_SECOND = 2 * 3.1415 / 60.0;
const float RAD_PER_SECOND_TO_RPM = 1 / RPM_TO_RAD_PER_SECOND;

#endif /* __PHYSICALPARAMETERS_H__ */