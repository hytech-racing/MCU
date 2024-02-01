#ifndef __UTILITY_H__
#define __UTILITY_H__

// Defines
#define FL          (0)
#define FR          (1)
#define RL          (2)
#define RR          (3)
#define NUM_MOTORS  (4)

#define PI                          (3.14159265)
#define GEARBOX_RATIO               (11.86)
#define WHEEL_DIAMETER              (0.4064) // meters
#define RPM_TO_METERS_PER_SECOND    (WHEEL_DIAMETER * PI / GEARBOX_RATIO / 60.0)

#endif /* __UTILITY_H__ */