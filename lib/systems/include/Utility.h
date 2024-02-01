#ifndef __UTILITY_H__
#define __UTILITY_H__

// Defines
const int FL =          0;
const int FR =          1;
const int RL =          2;
const int RR =          3;
const int NUM_MOTORS =  4;

const float PI =                        3.14159265;
const float GEARBOX_RATIO =             11.86;
const float WHEEL_DIAMETER =            0.4064; // meters
const float RPM_TO_METERS_PER_SECOND =  WHEEL_DIAMETER * PI / GEARBOX_RATIO / 60.0;

const int DEBOUNCE_MILLIS = 20; // milliseconds before registering another button press

#endif /* __UTILITY_H__ */