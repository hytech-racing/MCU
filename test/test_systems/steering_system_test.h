/**
 * @file steering_system_test.h
 * @author Akshat Jain and..
 * @brief just some basic test cases for steering systems 
 * @version 0.1
 * @date 2024-04-10 
 */
#ifndef STEERING_SYSTEM_TEST
#define STEERING_SYSTEM_TEST
#include <gtest/gtest.h>
#include <string>
#include "C:\Users\aksha\OneDrive\MCU\lib\systems\include\SteeringSystem.h"
#include <array>
#include <iostream>
using namespace std;

// check if interpolation using the steerign angle map and the normaliztion work properly)
TEST(SteeringSystemTesting, test_steering_angle_map_and_normalization)
{    // 
    const int testLength = 10;
    double wheelAnglesRandom[testLength] = {-23.0, -22.9, 11.1, 12.5, 0.0, -1.0, 1.0, 6.0, 22.0, 8.0};
    double rawDataRandom[testLength] = {-130.0, 12.4, 0.0, -2.9, 100.0, 114.0, 112.0, -5.0, -18.0, -20.0};
    double convertedValues[testLength];
    double expectedValues[testLength] = {-1.0000, 0.0954, 0, -0.0223, 0.7692, 0.8769, 0.8615, -0.0385, -0.1385, -0.1538}; // expected values calculated on matlab
    double tempAngle = 0.0;
    int steeringDataMap[2] = {-130, 130}; // max and min range of converted steering data (change depending on data)
    int wheelSteerRange[2] = {23, -23}; // max and min of final wheel steering (correct if actual limits of car are different)
    for (int i = 0; i < testLength; ++i) {
        tempAngle = interpolateSteering(rawDataRandom[i], steeringDataMap[0], steeringDataMap[1], wheelSteerRange[0], wheelSteerRange[1]);
        // cout << "Interpolated value of wheel angle : " << tempAngle << ", raw input value is " << rawDataRandom[i] << "\n";
        tempAngle = normalizeSteering(tempAngle, wheelSteerRange[0], wheelSteerRange[1]);
        // cout << "Normalized value : " << tempAngle;
        convertedValues[i] = tempAngle;
        EXPECT_TRUE(convertedValues[i] == expectedValues[i]);
    }
}
#endif