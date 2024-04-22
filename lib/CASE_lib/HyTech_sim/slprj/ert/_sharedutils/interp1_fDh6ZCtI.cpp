//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: interp1_fDh6ZCtI.cpp
//
// Code generated for Simulink model 'BasicVehicleMath'.
//
// Model version                  : 1.21
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Sun Apr 21 22:12:16 2024
//
#include "rtwtypes.h"
#include "interp1_fDh6ZCtI.h"
#include <cmath>

extern "C"
{

#include "rt_nonfinite.h"

}

// Function for MATLAB Function: '<S20>/MATLAB Function'
real_T interp1_fDh6ZCtI(const real_T varargin_1[2], const real_T varargin_2[2],
  real_T varargin_3)
{
  real_T Vq;
  real_T r;
  real_T x_idx_1;
  real_T y_idx_0;
  real_T y_idx_1;
  int32_T k;
  y_idx_0 = varargin_2[0];
  r = varargin_1[0];
  y_idx_1 = varargin_2[1];
  x_idx_1 = varargin_1[1];
  Vq = (rtNaN);
  k = 0;
  int32_T exitg1;
  do {
    exitg1 = 0;
    if (k < 2) {
      if (std::isnan(varargin_1[k])) {
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      if (varargin_1[1] < varargin_1[0]) {
        r = varargin_1[1];
        x_idx_1 = varargin_1[0];
        y_idx_0 = varargin_2[1];
        y_idx_1 = varargin_2[0];
      }

      if ((!std::isnan(varargin_3)) && (!(varargin_3 > x_idx_1)) &&
          (!(varargin_3 < r))) {
        r = (varargin_3 - r) / (x_idx_1 - r);
        if (r == 0.0) {
          Vq = y_idx_0;
        } else if (r == 1.0) {
          Vq = y_idx_1;
        } else if (y_idx_0 == y_idx_1) {
          Vq = y_idx_0;
        } else {
          Vq = (1.0 - r) * y_idx_0 + r * y_idx_1;
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Vq;
}

//
// File trailer for generated code.
//
// [EOF]
//
