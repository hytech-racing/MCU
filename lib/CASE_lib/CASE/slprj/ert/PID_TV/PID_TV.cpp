//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PID_TV.cpp
//
// Code generated for Simulink model 'PID_TV'.
//
// Model version                  : 1.35
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr 12 08:19:45 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "PID_TV.h"
#include "rtwtypes.h"
#include "PID_TV_capi.h"
#include "PID_TV_private.h"

// Output and update for referenced model: 'PID_TV'
void PID_TV::step(const real_T *rtu_YawRaterads, const real_T *rtu_PID_I, const
                  real_T *rtu_PID_D, const real_T *rtu_PID_N, const real_T
                  *rtu_PID_P, const real_T *rtu_FR_in, const real_T *rtu_RR_in,
                  const real_T *rtu_FL_in, const real_T *rtu_RL_in, const
                  boolean_T *rtu_usePIDTV, const real_T
                  *rtu_KinematicDesiredYawRaterad, const real_T *rtu_Inport,
                  real_T *rty_FR_out, real_T *rty_RR_out, real_T *rty_FL_out,
                  real_T *rty_RL_out, real_T *rty_YawRateErrorrads, real_T
                  *rty_YawPIDOutput)
{
  real_T rtb_DProdOut;
  real_T rtb_IProdOut;
  real_T rtb_PProdOut;
  real_T rtb_Switch_m;
  int8_T tmp;
  int8_T tmp_0;

  // Outputs for Atomic SubSystem: '<Root>/PID_TV'
  // Sum: '<S3>/Subtract'
  *rty_YawRateErrorrads = *rtu_KinematicDesiredYawRaterad - *rtu_YawRaterads;

  // Switch: '<S1>/Switch1' incorporates:
  //   Constant: '<S1>/Constant1'

  if (*rtu_Inport > 1.0) {
    rtb_IProdOut = *rty_YawRateErrorrads;
  } else {
    rtb_IProdOut = 0.0;
  }

  // End of Switch: '<S1>/Switch1'

  // Product: '<S42>/PProd Out'
  rtb_PProdOut = rtb_IProdOut * *rtu_PID_P;

  // Product: '<S31>/DProd Out'
  rtb_DProdOut = rtb_IProdOut * *rtu_PID_D;

  // Product: '<S40>/NProd Out' incorporates:
  //   DiscreteIntegrator: '<S32>/Filter'
  //   Sum: '<S32>/SumD'

  rtb_DProdOut = (rtb_DProdOut - PID_TV_DW.Filter_DSTATE) * *rtu_PID_N;

  // Sum: '<S46>/Sum' incorporates:
  //   DiscreteIntegrator: '<S37>/Integrator'

  rtb_PProdOut = (rtb_PProdOut + PID_TV_DW.Integrator_DSTATE) + rtb_DProdOut;

  // Saturate: '<S44>/Saturation'
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

  // End of Saturate: '<S44>/Saturation'

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant'

  if (*rtu_usePIDTV) {
    rtb_Switch_m = *rty_YawPIDOutput;
  } else {
    rtb_Switch_m = 0.0;
  }

  // End of Switch: '<S1>/Switch'

  // Sum: '<S1>/Sum'
  *rty_FR_out = rtb_Switch_m + *rtu_FR_in;

  // Sum: '<S1>/Sum1'
  *rty_RR_out = rtb_Switch_m + *rtu_RR_in;

  // Sum: '<S1>/Sum2'
  *rty_FL_out = *rtu_FL_in - rtb_Switch_m;

  // Sum: '<S1>/Sum3'
  *rty_RL_out = *rtu_RL_in - rtb_Switch_m;

  // DeadZone: '<S30>/DeadZone'
  if (rtb_PProdOut > 5.0) {
    rtb_PProdOut -= 5.0;
  } else if (rtb_PProdOut >= -5.0) {
    rtb_PProdOut = 0.0;
  } else {
    rtb_PProdOut -= -5.0;
  }

  // End of DeadZone: '<S30>/DeadZone'

  // Product: '<S34>/IProd Out'
  rtb_IProdOut *= *rtu_PID_I;

  // Switch: '<S28>/Switch1' incorporates:
  //   Constant: '<S28>/Clamping_zero'
  //   Constant: '<S28>/Constant'
  //   Constant: '<S28>/Constant2'
  //   RelationalOperator: '<S28>/fix for DT propagation issue'

  if (rtb_PProdOut > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S28>/Switch2' incorporates:
  //   Constant: '<S28>/Clamping_zero'
  //   Constant: '<S28>/Constant3'
  //   Constant: '<S28>/Constant4'
  //   RelationalOperator: '<S28>/fix for DT propagation issue1'

  if (rtb_IProdOut > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S28>/Switch' incorporates:
  //   Constant: '<S28>/Clamping_zero'
  //   Constant: '<S28>/Constant1'
  //   Logic: '<S28>/AND3'
  //   RelationalOperator: '<S28>/Equal1'
  //   RelationalOperator: '<S28>/Relational Operator'
  //   Switch: '<S28>/Switch1'
  //   Switch: '<S28>/Switch2'

  if ((rtb_PProdOut != 0.0) && (tmp == tmp_0)) {
    rtb_IProdOut = 0.0;
  }

  // Update for DiscreteIntegrator: '<S37>/Integrator' incorporates:
  //   Switch: '<S28>/Switch'

  PID_TV_DW.Integrator_DSTATE += 0.001 * rtb_IProdOut;
  if (PID_TV_DW.Integrator_DSTATE > 1.5) {
    PID_TV_DW.Integrator_DSTATE = 1.5;
  } else if (PID_TV_DW.Integrator_DSTATE < -1.5) {
    PID_TV_DW.Integrator_DSTATE = -1.5;
  }

  // End of Update for DiscreteIntegrator: '<S37>/Integrator'

  // Update for DiscreteIntegrator: '<S32>/Filter'
  PID_TV_DW.Filter_DSTATE += 0.001 * rtb_DProdOut;

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
