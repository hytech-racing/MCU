#ifndef __UTILITY_H__
#define __UTILITY_H__
#include "PhysicalParameters.h"
#include <array>
// Defines
const int FL = 0;
const int FR = 1;
const int RL = 2;
const int RR = 3;
const int NUM_MOTORS = 4;

const int DEBOUNCE_MILLIS = 10; // milliseconds before registering another button press

/// @brief generic data vector type that can be used with tire and / or anything to do with 4 corners of the car.
template <typename T>
struct veh_vec
{
public:
    T FL;
    T FR;
    T RL;
    T RR;

public:
    veh_vec() = default;
    veh_vec(T _FL, T _FR, T _RL, T _RR)
    {
        FL = _FL;
        FR = _FR;
        RL = _RL;
        RR = _RR;
    }

    /// @brief copy values to array in FL, FR, RL, RR order
    void copy_to_arr(T (&arr_out)[4])
    {
        arr_out[0] = FL;
        arr_out[1] = FR;
        arr_out[2] = RL;
        arr_out[3] = RR;
    }
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