//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: HT08_CASE_types.h
//
// Code generated for Simulink model 'HT08_CASE'.
//
// Model version                  : 1.50
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Mon Apr 15 17:39:16 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_HT08_CASE_types_h_
#define RTW_HEADER_HT08_CASE_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_
#define DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_

struct CAN_MESSAGE_BUS
{
  uint8_T Extended;
  uint8_T Length;
  uint8_T Remote;
  uint8_T Error;
  uint32_T ID;
  real_T Timestamp;
  uint8_T Data[8];
};

#endif
#endif                                 // RTW_HEADER_HT08_CASE_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
