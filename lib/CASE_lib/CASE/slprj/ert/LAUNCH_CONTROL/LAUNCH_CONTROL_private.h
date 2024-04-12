//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: LAUNCH_CONTROL_private.h
//
// Code generated for Simulink model 'LAUNCH_CONTROL'.
//
// Model version                  : 1.8
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Wed Apr 10 19:33:49 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_LAUNCH_CONTROL_private_h_
#define RTW_HEADER_LAUNCH_CONTROL_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "LAUNCH_CONTROL_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
#define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif
#endif                                 // RTW_HEADER_LAUNCH_CONTROL_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
