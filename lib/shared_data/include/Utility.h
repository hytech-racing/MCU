#ifndef __UTILITY_H__
#define __UTILITY_H__
#include "PhysicalParameters.h"
// Defines
const int FL =          0;
const int FR =          1;
const int RL =          2;
const int RR =          3;
const int NUM_MOTORS =  4;

const int DEBOUNCE_MILLIS = 10; // milliseconds before registering another button press

/// @brief generic data vector type that can be used with tire and / or anything to do with 4 corners of the car.
template <typename T>
struct veh_vec
{
    T FL;
    T FR;
    T RL;
    T RR;
};

template <typename T>
struct xyz_vec
{
    T x;
    T y;
    T z;
};

template <typename T>
struct xy_vec
{
    T x;
    T y;
};

#endif /* __UTILITY_H__ */