#ifndef __PHYSICALPARAMETERS_H__
#define __PHYSICALPARAMETERS_H__

const float GEARBOX_RATIO =             11.86;
const float WHEEL_DIAMETER =            0.4064; // meters
const float RPM_TO_METERS_PER_SECOND =  WHEEL_DIAMETER * 3.1415 / GEARBOX_RATIO / 60.0;
const float METERS_PER_SECOND_TO_RPM = 1.0 / RPM_TO_METERS_PER_SECOND;

#endif /* __PHYSICALPARAMETERS_H__ */