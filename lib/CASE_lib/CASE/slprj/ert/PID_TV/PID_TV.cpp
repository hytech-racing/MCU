//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PID_TV.cpp
//
// Code generated for Simulink model 'PID_TV'.
//
// Model version                  : 1.38
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Mon Apr 15 17:36:51 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "PID_TV.h"
#include "rtwtypes.h"
#include <cmath>
#include "PID_TV_capi.h"
#include "PID_TV_private.h"

// Output and update for referenced model: 'PID_TV'
void PID_TV::step(const real_T *rtu_YawRaterads, const real_T *rtu_PID_I, const
                  real_T *rtu_PID_D, const real_T *rtu_PID_N, const real_T
                  *rtu_PID_P, const real_T *rtu_FR_in, const real_T *rtu_RR_in,
                  const real_T *rtu_FL_in, const real_T *rtu_RL_in, const
                  boolean_T *rtu_usePIDTV, const real_T
                  *rtu_KinematicDesiredYawRaterad, const real_T *rtu_Inport,
                  const real_T *rtu_TorqueLimit, real_T *rty_FR_out, real_T
                  *rty_RR_out, real_T *rty_FL_out, real_T *rty_RL_out, real_T
                  *rty_YawRateErrorrads, real_T *rty_YawPIDOutput)
{
  real_T rtb_Abs;
  real_T rtb_IProdOut;
  real_T rtb_PProdOut;
  real_T rtb_Switch;
  real_T rtb_Switch2;
  real_T rtb_Switch3;
  real_T rtb_Switch5;
  real_T rtb_YawErrorrads;
  real_T torqueOverFlow_idx_2;
  real_T torqueOverFlow_idx_3;
  int8_T tmp;
  int8_T tmp_0;

  // Outputs for Atomic SubSystem: '<Root>/PID_TV'
  // Abs: '<S1>/Abs'
  rtb_Abs = std::abs(*rtu_FR_in);

  // Switch: '<S1>/Switch1' incorporates:
  //   Constant: '<S1>/Constant1'

  if (*rtu_Inport > 1.0) {
    // Sum: '<S4>/Subtract'
    rtb_YawErrorrads = *rtu_KinematicDesiredYawRaterad - *rtu_YawRaterads;
    *rty_YawRateErrorrads = rtb_YawErrorrads;
  } else {
    *rty_YawRateErrorrads = 0.0;
  }

  // End of Switch: '<S1>/Switch1'

  // Product: '<S43>/PProd Out'
  rtb_PProdOut = *rty_YawRateErrorrads * *rtu_PID_P;

  // Product: '<S32>/DProd Out'
  rtb_YawErrorrads = *rty_YawRateErrorrads * *rtu_PID_D;

  // Product: '<S41>/NProd Out' incorporates:
  //   DiscreteIntegrator: '<S33>/Filter'
  //   Sum: '<S33>/SumD'

  rtb_YawErrorrads = (rtb_YawErrorrads - PID_TV_DW.Filter_DSTATE) * *rtu_PID_N;

  // Sum: '<S47>/Sum' incorporates:
  //   DiscreteIntegrator: '<S38>/Integrator'

  rtb_PProdOut = (rtb_PProdOut + PID_TV_DW.Integrator_DSTATE) + rtb_YawErrorrads;

  // Saturate: '<S45>/Saturation'
  if (rtb_PProdOut > 5.0) {
    // Gain: '<S1>/Gain'
    *rty_YawPIDOutput = -5.0;
  } else if (rtb_PProdOut < -5.0) {
    // Gain: '<S1>/Gain'
    *rty_YawPIDOutput = 5.0;
  } else {
    // Gain: '<S1>/Gain'
    *rty_YawPIDOutput = -rtb_PProdOut;
  }

  // End of Saturate: '<S45>/Saturation'

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant'

  if (*rtu_usePIDTV) {
    rtb_Switch = *rty_YawPIDOutput;
  } else {
    rtb_Switch = 0.0;
  }

  // End of Switch: '<S1>/Switch'

  // Switch: '<S1>/Switch2' incorporates:
  //   Constant: '<S1>/Constant2'

  if (rtb_Abs > 0.0) {
    // Sum: '<S1>/Sum'
    rtb_Switch2 = rtb_Switch + *rtu_FR_in;
  } else {
    rtb_Switch2 = 0.0;
  }

  // End of Switch: '<S1>/Switch2'

  // Abs: '<S1>/Abs2'
  rtb_IProdOut = std::abs(*rtu_FL_in);

  // Switch: '<S1>/Switch4' incorporates:
  //   Constant: '<S1>/Constant4'

  if (rtb_IProdOut > 0.0) {
    // Sum: '<S1>/Sum2'
    rtb_Abs = *rtu_FL_in - rtb_Switch;
  } else {
    rtb_Abs = 0.0;
  }

  // End of Switch: '<S1>/Switch4'

  // Abs: '<S1>/Abs3'
  rtb_IProdOut = std::abs(*rtu_RL_in);

  // Switch: '<S1>/Switch5' incorporates:
  //   Constant: '<S1>/Constant5'

  if (rtb_IProdOut > 0.0) {
    // Sum: '<S1>/Sum3'
    rtb_Switch5 = *rtu_RL_in - rtb_Switch;
  } else {
    rtb_Switch5 = 0.0;
  }

  // End of Switch: '<S1>/Switch5'

  // Abs: '<S1>/Abs1'
  rtb_IProdOut = std::abs(*rtu_RR_in);

  // Switch: '<S1>/Switch3' incorporates:
  //   Constant: '<S1>/Constant3'

  if (rtb_IProdOut > 0.0) {
    // Sum: '<S1>/Sum1'
    rtb_Switch3 = rtb_Switch + *rtu_RR_in;
  } else {
    rtb_Switch3 = 0.0;
  }

  // End of Switch: '<S1>/Switch3'

  // MATLAB Function: '<S1>/PID Torque Overflow Check'
  rtb_IProdOut = rtb_Abs - *rtu_TorqueLimit;
  rtb_Switch = rtb_Switch2 - *rtu_TorqueLimit;
  torqueOverFlow_idx_2 = rtb_Switch5 - *rtu_TorqueLimit;
  torqueOverFlow_idx_3 = rtb_Switch3 - *rtu_TorqueLimit;
  *rty_FL_out = rtb_Abs;
  *rty_FR_out = rtb_Switch2;
  *rty_RL_out = rtb_Switch5;
  *rty_RR_out = rtb_Switch3;
  if (rtb_IProdOut > 0.0) {
    *rty_FL_out = *rtu_TorqueLimit;
    *rty_FR_out = rtb_Switch2 + rtb_IProdOut;
  }

  if (rtb_Switch > 0.0) {
    *rty_FR_out = *rtu_TorqueLimit;
    *rty_FL_out = rtb_Abs + rtb_Switch;
  }

  if (torqueOverFlow_idx_2 > 0.0) {
    *rty_RL_out = *rtu_TorqueLimit;
    *rty_RR_out = rtb_Switch3 + torqueOverFlow_idx_2;
  }

  if (torqueOverFlow_idx_3 > 0.0) {
    *rty_RR_out = *rtu_TorqueLimit;
    *rty_RL_out = rtb_Switch5 + torqueOverFlow_idx_3;
  }

  // End of MATLAB Function: '<S1>/PID Torque Overflow Check'

  // DeadZone: '<S31>/DeadZone'
  if (rtb_PProdOut > 5.0) {
    rtb_PProdOut -= 5.0;
  } else if (rtb_PProdOut >= -5.0) {
    rtb_PProdOut = 0.0;
  } else {
    rtb_PProdOut -= -5.0;
  }

  // End of DeadZone: '<S31>/DeadZone'

  // Product: '<S35>/IProd Out'
  rtb_IProdOut = *rty_YawRateErrorrads * *rtu_PID_I;

  // Switch: '<S29>/Switch1' incorporates:
  //   Constant: '<S29>/Clamping_zero'
  //   Constant: '<S29>/Constant'
  //   Constant: '<S29>/Constant2'
  //   RelationalOperator: '<S29>/fix for DT propagation issue'

  if (rtb_PProdOut > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S29>/Switch2' incorporates:
  //   Constant: '<S29>/Clamping_zero'
  //   Constant: '<S29>/Constant3'
  //   Constant: '<S29>/Constant4'
  //   RelationalOperator: '<S29>/fix for DT propagation issue1'

  if (rtb_IProdOut > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S29>/Switch' incorporates:
  //   Constant: '<S29>/Clamping_zero'
  //   Constant: '<S29>/Constant1'
  //   Logic: '<S29>/AND3'
  //   RelationalOperator: '<S29>/Equal1'
  //   RelationalOperator: '<S29>/Relational Operator'
  //   Switch: '<S29>/Switch1'
  //   Switch: '<S29>/Switch2'

  if ((rtb_PProdOut != 0.0) && (tmp == tmp_0)) {
    rtb_IProdOut = 0.0;
  }

  // Update for DiscreteIntegrator: '<S38>/Integrator' incorporates:
  //   Switch: '<S29>/Switch'

  PID_TV_DW.Integrator_DSTATE += 0.001 * rtb_IProdOut;
  if (PID_TV_DW.Integrator_DSTATE > 1.5) {
    PID_TV_DW.Integrator_DSTATE = 1.5;
  } else if (PID_TV_DW.Integrator_DSTATE < -1.5) {
    PID_TV_DW.Integrator_DSTATE = -1.5;
  }

  // End of Update for DiscreteIntegrator: '<S38>/Integrator'

  // Update for DiscreteIntegrator: '<S33>/Filter'
  PID_TV_DW.Filter_DSTATE += 0.001 * rtb_YawErrorrads;

  // End of Outputs for SubSystem: '<Root>/PID_TV'
}

// Model initialize function
void PID_TV::initialize()
{
  // Registration code

  // Initialize DataMapInfo substructure containing ModelMap for C API
  PID_TV_InitializeDataMapInfo((&PID_TV_M));
}

// Constructor
PID_TV::PID_TV() :
  PID_TV_DW(),
  PID_TV_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
PID_TV::~PID_TV() = default;

// Real-Time Model get method
PID_TV::RT_MODEL_PID_TV_T * PID_TV::getRTM()
{
  return (&PID_TV_M);
}

// member function to set up the C-API information
void PID_TV::setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T *
  rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  // Initialize Parent model MMI
  if ((rt_ParentMMI != (nullptr)) && (rt_ChildPath != (nullptr))) {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &((&PID_TV_M)
      ->DataMapInfo.mmi));
    rtwCAPI_SetPath((&PID_TV_M)->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex((&PID_TV_M)->DataMapInfo.mmi, rt_CSTATEIdx);
  }
}

// member function to setup error status pointer
void PID_TV::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&PID_TV_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
