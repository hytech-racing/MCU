//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PID_TV.cpp
//
// Code generated for Simulink model 'PID_TV'.
//
// Model version                  : 1.30
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Apr 11 22:49:27 2024
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
                  boolean_T *rtu_usePIDTV, real_T *rty_FR_out, real_T
                  *rty_RR_out, real_T *rty_FL_out, real_T *rty_RL_out, real_T
                  *rty_YawRateErrorrads, real_T *rty_YawPIDOutput)
{
  real_T rtb_DProdOut;
  real_T rtb_PProdOut;

  // Outputs for Atomic SubSystem: '<Root>/PID_TV'
  // Sum: '<S3>/Subtract'
  *rty_YawRateErrorrads = 0.0 - *rtu_YawRaterads;

  // Product: '<S40>/PProd Out'
  rtb_PProdOut = *rty_YawRateErrorrads * *rtu_PID_P;

  // Product: '<S29>/DProd Out'
  rtb_DProdOut = *rty_YawRateErrorrads * *rtu_PID_D;

  // Product: '<S38>/NProd Out' incorporates:
  //   DiscreteIntegrator: '<S30>/Filter'
  //   Sum: '<S30>/SumD'

  rtb_DProdOut = (rtb_DProdOut - PID_TV_DW.Filter_DSTATE) * *rtu_PID_N;

  // Gain: '<S1>/Gain' incorporates:
  //   DiscreteIntegrator: '<S35>/Integrator'
  //   Sum: '<S44>/Sum'

  *rty_YawPIDOutput = -((rtb_PProdOut + PID_TV_DW.Integrator_DSTATE) +
                        rtb_DProdOut);

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant'

  if (*rtu_usePIDTV) {
    rtb_PProdOut = *rty_YawPIDOutput;
  } else {
    rtb_PProdOut = 0.0;
  }

  // End of Switch: '<S1>/Switch'

  // Sum: '<S1>/Sum'
  *rty_FR_out = rtb_PProdOut + *rtu_FR_in;

  // Sum: '<S1>/Sum1'
  *rty_RR_out = rtb_PProdOut + *rtu_RR_in;

  // Sum: '<S1>/Sum2'
  *rty_FL_out = *rtu_FL_in - rtb_PProdOut;

  // Sum: '<S1>/Sum3'
  *rty_RL_out = *rtu_RL_in - rtb_PProdOut;

  // Product: '<S32>/IProd Out'
  rtb_PProdOut = *rty_YawRateErrorrads * *rtu_PID_I;

  // Update for DiscreteIntegrator: '<S35>/Integrator'
  PID_TV_DW.Integrator_DSTATE += 0.001 * rtb_PProdOut;

  // Update for DiscreteIntegrator: '<S30>/Filter'
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
