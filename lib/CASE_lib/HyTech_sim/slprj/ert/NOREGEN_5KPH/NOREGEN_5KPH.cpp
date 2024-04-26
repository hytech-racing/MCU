//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: NOREGEN_5KPH.cpp
//
// Code generated for Simulink model 'NOREGEN_5KPH'.
//
// Model version                  : 1.6
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr 26 00:57:52 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "NOREGEN_5KPH.h"
#include "rtwtypes.h"
#include "NOREGEN_5KPH_capi.h"
#include "NOREGEN_5KPH_private.h"

// Output and update for referenced model: 'NOREGEN_5KPH'
void NOREGEN_5KPH::step(const real_T *rtu_PowerLimTorqueFL, const real_T
  *rtu_PowerLimTorqueFR, const real_T *rtu_PowerLimTorqueRL, const real_T
  *rtu_PowerLimTorqueRR, const boolean_T *rtu_useNoRegen5kph, const real_T
  *rtu_WheelLinearVelFLms, const real_T *rtu_WheelLinearVelFRms, const real_T
  *rtu_WheelLinearVelRLms, const real_T *rtu_WheelLinearVelRRms, const real_T
  *rtu_ModeConstrainedTorqueReq, real_T *rty_Regen5KPHTorqueFL, real_T
  *rty_Regen5KPHTorqueFR, real_T *rty_Regen5KPHTorqueRL, real_T
  *rty_Regen5KPHTorqueRR, real_T *rty_Regen5KPHStatusFL, real_T
  *rty_Regen5KPHStatusFR, real_T *rty_Regen5KPHStatusRL, real_T
  *rty_Regen5KPHStatusRR)
{
  real_T rtb_Gain;
  real_T rtb_Regen_5KPH_Torque_FL;
  real_T rtb_Regen_5KPH_Torque_FR;
  real_T rtb_Regen_5KPH_Torque_RR;
  real_T x_idx_4;

  // MATLAB Function: '<Root>/MATLAB Function'
  rtb_Regen_5KPH_Torque_RR = *rtu_WheelLinearVelFLms;
  rtb_Regen_5KPH_Torque_FR = *rtu_WheelLinearVelFRms;
  rtb_Regen_5KPH_Torque_FL = *rtu_WheelLinearVelRLms;
  x_idx_4 = *rtu_WheelLinearVelRRms;
  rtb_Gain = 0.0;
  if (rtb_Regen_5KPH_Torque_RR > 0.0) {
    rtb_Gain = rtb_Regen_5KPH_Torque_RR;
  }

  if (rtb_Gain < rtb_Regen_5KPH_Torque_FR) {
    rtb_Gain = rtb_Regen_5KPH_Torque_FR;
  }

  if (rtb_Gain < rtb_Regen_5KPH_Torque_FL) {
    rtb_Gain = rtb_Regen_5KPH_Torque_FL;
  }

  if (rtb_Gain < x_idx_4) {
    rtb_Gain = x_idx_4;
  }

  // Gain: '<Root>/Gain' incorporates:
  //   MATLAB Function: '<Root>/MATLAB Function'

  rtb_Gain *= 3.6;

  // If: '<Root>/If'
  if (*rtu_useNoRegen5kph) {
    int32_T rtb_Regen_5KPH_Status_FL;

    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // MATLAB Function: '<S2>/MATLAB Function'
    if (rtb_Gain < 10.0) {
      if (rtb_Gain < 5.0) {
        if (*rtu_ModeConstrainedTorqueReq < 0.0) {
          rtb_Regen_5KPH_Torque_FL = 0.0;
          rtb_Regen_5KPH_Torque_FR = 0.0;
          rtb_Gain = 0.0;
          rtb_Regen_5KPH_Torque_RR = 0.0;
          rtb_Regen_5KPH_Status_FL = 1;
        } else {
          rtb_Regen_5KPH_Torque_FL = *rtu_PowerLimTorqueFL;
          rtb_Regen_5KPH_Torque_FR = *rtu_PowerLimTorqueFR;
          rtb_Gain = *rtu_PowerLimTorqueRL;
          rtb_Regen_5KPH_Torque_RR = *rtu_PowerLimTorqueRR;
          rtb_Regen_5KPH_Status_FL = 0;
        }
      } else if (*rtu_ModeConstrainedTorqueReq < 0.0) {
        rtb_Regen_5KPH_Torque_RR = (rtb_Gain - 5.0) / 5.0;
        if (rtb_Regen_5KPH_Torque_RR == 0.0) {
          rtb_Regen_5KPH_Torque_RR = 0.0;
        }

        rtb_Regen_5KPH_Torque_FL = *rtu_PowerLimTorqueFL *
          rtb_Regen_5KPH_Torque_RR;
        rtb_Regen_5KPH_Torque_FR = *rtu_PowerLimTorqueFR *
          rtb_Regen_5KPH_Torque_RR;
        rtb_Gain = *rtu_PowerLimTorqueRL * rtb_Regen_5KPH_Torque_RR;
        rtb_Regen_5KPH_Torque_RR *= *rtu_PowerLimTorqueRR;
        rtb_Regen_5KPH_Status_FL = 1;
      } else {
        rtb_Regen_5KPH_Torque_FL = *rtu_PowerLimTorqueFL;
        rtb_Regen_5KPH_Torque_FR = *rtu_PowerLimTorqueFR;
        rtb_Gain = *rtu_PowerLimTorqueRL;
        rtb_Regen_5KPH_Torque_RR = *rtu_PowerLimTorqueRR;
        rtb_Regen_5KPH_Status_FL = 0;
      }
    } else {
      rtb_Regen_5KPH_Torque_FL = *rtu_PowerLimTorqueFL;
      rtb_Regen_5KPH_Torque_FR = *rtu_PowerLimTorqueFR;
      rtb_Gain = *rtu_PowerLimTorqueRL;
      rtb_Regen_5KPH_Torque_RR = *rtu_PowerLimTorqueRR;
      rtb_Regen_5KPH_Status_FL = 0;
    }

    // End of MATLAB Function: '<S2>/MATLAB Function'

    // SignalConversion generated from: '<S2>/Regen 5KPH Status FL'
    *rty_Regen5KPHStatusFL = rtb_Regen_5KPH_Status_FL;

    // SignalConversion generated from: '<S2>/Regen 5KPH Status FR' incorporates:
    //   SignalConversion generated from: '<S2>/Regen 5KPH Status FL'

    *rty_Regen5KPHStatusFR = rtb_Regen_5KPH_Status_FL;

    // SignalConversion generated from: '<S2>/Regen 5KPH Status RL' incorporates:
    //   SignalConversion generated from: '<S2>/Regen 5KPH Status FL'

    *rty_Regen5KPHStatusRL = rtb_Regen_5KPH_Status_FL;

    // SignalConversion generated from: '<S2>/Regen 5KPH Status RR' incorporates:
    //   SignalConversion generated from: '<S2>/Regen 5KPH Status FL'

    *rty_Regen5KPHStatusRR = rtb_Regen_5KPH_Status_FL;

    // SignalConversion generated from: '<S2>/Regen 5KPH Torque FL'
    *rty_Regen5KPHTorqueFL = rtb_Regen_5KPH_Torque_FL;

    // SignalConversion generated from: '<S2>/Regen 5KPH Torque FR'
    *rty_Regen5KPHTorqueFR = rtb_Regen_5KPH_Torque_FR;

    // SignalConversion generated from: '<S2>/Regen 5KPH Torque RL'
    *rty_Regen5KPHTorqueRL = rtb_Gain;

    // SignalConversion generated from: '<S2>/Regen 5KPH Torque RR'
    *rty_Regen5KPHTorqueRR = rtb_Regen_5KPH_Torque_RR;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem1'
  } else {
    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
    //   ActionPort: '<S1>/Action Port'

    // SignalConversion generated from: '<S1>/Regen 5KPH Status FL' incorporates:
    //   Constant: '<S1>/Constant'

    *rty_Regen5KPHStatusFL = 0.0;

    // SignalConversion generated from: '<S1>/Regen 5KPH Status FR' incorporates:
    //   Constant: '<S1>/Constant1'

    *rty_Regen5KPHStatusFR = 0.0;

    // SignalConversion generated from: '<S1>/Regen 5KPH Status RL' incorporates:
    //   Constant: '<S1>/Constant2'

    *rty_Regen5KPHStatusRL = 0.0;

    // SignalConversion generated from: '<S1>/Regen 5KPH Status RR' incorporates:
    //   Constant: '<S1>/Constant3'

    *rty_Regen5KPHStatusRR = 0.0;

    // SignalConversion generated from: '<S1>/Power Lim Torque FL'
    *rty_Regen5KPHTorqueFL = *rtu_PowerLimTorqueFL;

    // SignalConversion generated from: '<S1>/Power Lim Torque FR'
    *rty_Regen5KPHTorqueFR = *rtu_PowerLimTorqueFR;

    // SignalConversion generated from: '<S1>/Power Lim Torque RL'
    *rty_Regen5KPHTorqueRL = *rtu_PowerLimTorqueRL;

    // SignalConversion generated from: '<S1>/Power Lim Torque RR'
    *rty_Regen5KPHTorqueRR = *rtu_PowerLimTorqueRR;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem'
  }

  // End of If: '<Root>/If'
}

// Model initialize function
void NOREGEN_5KPH::initialize()
{
  // Registration code

  // Initialize DataMapInfo substructure containing ModelMap for C API
  NOREGEN_5KPH_InitializeDataMapInfo((&NOREGEN_5KPH_M));
}

// Constructor
NOREGEN_5KPH::NOREGEN_5KPH() :
  NOREGEN_5KPH_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
NOREGEN_5KPH::~NOREGEN_5KPH() = default;

// Real-Time Model get method
NOREGEN_5KPH::RT_MODEL_NOREGEN_5KPH_T * NOREGEN_5KPH::getRTM()
{
  return (&NOREGEN_5KPH_M);
}

// member function to set up the C-API information
void NOREGEN_5KPH::setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const
  char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  // Initialize Parent model MMI
  if ((rt_ParentMMI != (nullptr)) && (rt_ChildPath != (nullptr))) {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &((&NOREGEN_5KPH_M)
      ->DataMapInfo.mmi));
    rtwCAPI_SetPath((&NOREGEN_5KPH_M)->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex((&NOREGEN_5KPH_M)->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

// member function to setup error status pointer
void NOREGEN_5KPH::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&NOREGEN_5KPH_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
