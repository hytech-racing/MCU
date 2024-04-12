//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: LAUNCH_CONTROL.cpp
//
// Code generated for Simulink model 'LAUNCH_CONTROL'.
//
// Model version                  : 1.8
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Wed Apr 10 20:16:07 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "LAUNCH_CONTROL.h"
#include "rtwtypes.h"
#include "LAUNCH_CONTROL_capi.h"
#include "LAUNCH_CONTROL_private.h"

// Output and update for referenced model: 'LAUNCH_CONTROL'
void LAUNCH_CONTROL::step(const real_T *rtu_SLFL, const real_T *rtu_SLFR, const
  real_T *rtu_SLRL, const real_T *rtu_SLRR, real_T *rty_LaunchTorqueFL, real_T
  *rty_LaunchTorqueFR, real_T *rty_LaunchTorqueRL, real_T *rty_LaunchTorqueRR)
{
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_b;
  real_T rtb_FilterCoefficient_j;
  real_T rtb_FilterCoefficient_k;
  real_T rtb_Integrator_bw;
  real_T rtb_Integrator_n;
  real_T rtb_Integrator_o;
  real_T rtb_Subtract;
  real_T rtb_Sum;

  // Sum: '<Root>/Subtract' incorporates:
  //   Constant: '<Root>/Constant'

  rtb_Subtract = 0.2 - *rtu_SLFL;

  // Gain: '<S39>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S31>/Filter'
  //   Gain: '<S30>/Derivative Gain'
  //   Sum: '<S31>/SumD'

  rtb_FilterCoefficient = (2.0 * rtb_Subtract - LAUNCH_CONTROL_DW.Filter_DSTATE)
    * 100.0;

  // Sum: '<S45>/Sum' incorporates:
  //   DiscreteIntegrator: '<S36>/Integrator'
  //   Gain: '<S41>/Proportional Gain'

  rtb_Integrator_n = (10.0 * rtb_Subtract + LAUNCH_CONTROL_DW.Integrator_DSTATE)
    + rtb_FilterCoefficient;

  // Switch: '<Root>/Switch3' incorporates:
  //   Constant: '<Root>/Constant1'

  if (rtb_Integrator_n > 0.0) {
    *rty_LaunchTorqueFL = rtb_Integrator_n;
  } else {
    *rty_LaunchTorqueFL = 0.0;
  }

  // End of Switch: '<Root>/Switch3'

  // Sum: '<Root>/Subtract3' incorporates:
  //   Constant: '<Root>/Constant'

  rtb_Integrator_n = 0.2 - *rtu_SLRR;

  // Gain: '<S183>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S175>/Filter'
  //   Gain: '<S174>/Derivative Gain'
  //   Sum: '<S175>/SumD'

  rtb_FilterCoefficient_b = (2.0 * rtb_Integrator_n -
    LAUNCH_CONTROL_DW.Filter_DSTATE_m) * 100.0;

  // Sum: '<S189>/Sum' incorporates:
  //   DiscreteIntegrator: '<S180>/Integrator'
  //   Gain: '<S185>/Proportional Gain'

  rtb_Integrator_o = (10.0 * rtb_Integrator_n +
                      LAUNCH_CONTROL_DW.Integrator_DSTATE_l) +
    rtb_FilterCoefficient_b;

  // Switch: '<Root>/Switch' incorporates:
  //   Constant: '<Root>/Constant1'

  if (rtb_Integrator_o > 0.0) {
    *rty_LaunchTorqueRR = rtb_Integrator_o;
  } else {
    *rty_LaunchTorqueRR = 0.0;
  }

  // End of Switch: '<Root>/Switch'

  // Gain: '<S177>/Integral Gain'
  rtb_Integrator_o = 10.0 * rtb_Integrator_n;

  // Sum: '<Root>/Subtract2' incorporates:
  //   Constant: '<Root>/Constant'

  rtb_Integrator_n = 0.2 - *rtu_SLRL;

  // Gain: '<S135>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S127>/Filter'
  //   Gain: '<S126>/Derivative Gain'
  //   Sum: '<S127>/SumD'

  rtb_FilterCoefficient_j = (2.0 * rtb_Integrator_n -
    LAUNCH_CONTROL_DW.Filter_DSTATE_i) * 100.0;

  // Sum: '<S141>/Sum' incorporates:
  //   DiscreteIntegrator: '<S132>/Integrator'
  //   Gain: '<S137>/Proportional Gain'

  rtb_Integrator_bw = (10.0 * rtb_Integrator_n +
                       LAUNCH_CONTROL_DW.Integrator_DSTATE_f) +
    rtb_FilterCoefficient_j;

  // Switch: '<Root>/Switch1' incorporates:
  //   Constant: '<Root>/Constant1'

  if (rtb_Integrator_bw > 0.0) {
    *rty_LaunchTorqueRL = rtb_Integrator_bw;
  } else {
    *rty_LaunchTorqueRL = 0.0;
  }

  // End of Switch: '<Root>/Switch1'

  // Gain: '<S129>/Integral Gain'
  rtb_Integrator_bw = 10.0 * rtb_Integrator_n;

  // Sum: '<Root>/Subtract1' incorporates:
  //   Constant: '<Root>/Constant'

  rtb_Integrator_n = 0.2 - *rtu_SLFR;

  // Gain: '<S87>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S79>/Filter'
  //   Gain: '<S78>/Derivative Gain'
  //   Sum: '<S79>/SumD'

  rtb_FilterCoefficient_k = (2.0 * rtb_Integrator_n -
    LAUNCH_CONTROL_DW.Filter_DSTATE_h) * 100.0;

  // Sum: '<S93>/Sum' incorporates:
  //   DiscreteIntegrator: '<S84>/Integrator'
  //   Gain: '<S89>/Proportional Gain'

  rtb_Sum = (10.0 * rtb_Integrator_n + LAUNCH_CONTROL_DW.Integrator_DSTATE_d) +
    rtb_FilterCoefficient_k;

  // Switch: '<Root>/Switch2' incorporates:
  //   Constant: '<Root>/Constant1'

  if (rtb_Sum > 0.0) {
    *rty_LaunchTorqueFR = rtb_Sum;
  } else {
    *rty_LaunchTorqueFR = 0.0;
  }

  // End of Switch: '<Root>/Switch2'

  // Update for DiscreteIntegrator: '<S31>/Filter'
  LAUNCH_CONTROL_DW.Filter_DSTATE += 0.001 * rtb_FilterCoefficient;

  // Update for DiscreteIntegrator: '<S36>/Integrator' incorporates:
  //   Gain: '<S33>/Integral Gain'

  LAUNCH_CONTROL_DW.Integrator_DSTATE += 10.0 * rtb_Subtract * 0.001;

  // Update for DiscreteIntegrator: '<S180>/Integrator'
  LAUNCH_CONTROL_DW.Integrator_DSTATE_l += 0.001 * rtb_Integrator_o;

  // Update for DiscreteIntegrator: '<S175>/Filter'
  LAUNCH_CONTROL_DW.Filter_DSTATE_m += 0.001 * rtb_FilterCoefficient_b;

  // Update for DiscreteIntegrator: '<S132>/Integrator'
  LAUNCH_CONTROL_DW.Integrator_DSTATE_f += 0.001 * rtb_Integrator_bw;

  // Update for DiscreteIntegrator: '<S127>/Filter'
  LAUNCH_CONTROL_DW.Filter_DSTATE_i += 0.001 * rtb_FilterCoefficient_j;

  // Update for DiscreteIntegrator: '<S84>/Integrator' incorporates:
  //   Gain: '<S81>/Integral Gain'

  LAUNCH_CONTROL_DW.Integrator_DSTATE_d += 10.0 * rtb_Integrator_n * 0.001;

  // Update for DiscreteIntegrator: '<S79>/Filter'
  LAUNCH_CONTROL_DW.Filter_DSTATE_h += 0.001 * rtb_FilterCoefficient_k;
}

// Model initialize function
void LAUNCH_CONTROL::initialize()
{
  // Registration code

  // Initialize DataMapInfo substructure containing ModelMap for C API
  LAUNCH_CONTROL_InitializeDataMapInfo((&LAUNCH_CONTROL_M));
}

// Constructor
LAUNCH_CONTROL::LAUNCH_CONTROL() :
  LAUNCH_CONTROL_DW(),
  LAUNCH_CONTROL_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
LAUNCH_CONTROL::~LAUNCH_CONTROL() = default;

// Real-Time Model get method
LAUNCH_CONTROL::RT_MODEL_LAUNCH_CONTROL_T * LAUNCH_CONTROL::getRTM()
{
  return (&LAUNCH_CONTROL_M);
}

// member function to set up the C-API information
void LAUNCH_CONTROL::setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const
  char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  // Initialize Parent model MMI
  if ((rt_ParentMMI != (nullptr)) && (rt_ChildPath != (nullptr))) {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &((&LAUNCH_CONTROL_M)
      ->DataMapInfo.mmi));
    rtwCAPI_SetPath((&LAUNCH_CONTROL_M)->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex((&LAUNCH_CONTROL_M)->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

// member function to setup error status pointer
void LAUNCH_CONTROL::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&LAUNCH_CONTROL_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
