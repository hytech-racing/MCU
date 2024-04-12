//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: BasicVehicleMath_private.h
//
// Code generated for Simulink model 'BasicVehicleMath'.
//
// Model version                  : 1.9
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Apr 11 22:49:11 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_BasicVehicleMath_private_h_
#define RTW_HEADER_BasicVehicleMath_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "BasicVehicleMath_types.h"

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

extern const real_T rtCP_pooled_ACWA9Kl3HBxo[201];
extern const real_T rtCP_pooled_q9XPNtLBKvWU[201];

#define rtCP_uDLookupTable_tableData   rtCP_pooled_ACWA9Kl3HBxo  // Expression: wheelSteerKin
                                                                 //  Referenced by: '<Root>/1-D Lookup Table'

#define rtCP_uDLookupTable_bp01Data    rtCP_pooled_q9XPNtLBKvWU  // Expression: abs(driverSteerKin)
                                                                 //  Referenced by: '<Root>/1-D Lookup Table'

#endif                                // RTW_HEADER_BasicVehicleMath_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
