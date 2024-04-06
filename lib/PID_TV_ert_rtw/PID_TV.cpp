//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PID_TV.cpp
//
// Code generated for Simulink model 'PID_TV'.
//
// Model version                  : 1.14
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Tue Mar 26 00:06:56 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "PID_TV.h"
#include <cmath>
#include "rtwtypes.h"
#include "PID_TV_capi.h"

// Model step function
void PID_TV::step()
{
  real_T rtb_Gain;
  real_T rtb_NProdOut;
  real_T rtb_YawErrorrads;

  // Outputs for Atomic SubSystem: '<Root>/PID_TV'
  // Sum: '<S3>/Subtract' incorporates:
  //   Abs: '<S3>/Abs'
  //   Constant: '<S3>/wb'
  //   Inport: '<Root>/Vx_B'
  //   Inport: '<Root>/Wheel Delta [rad]'
  //   Inport: '<Root>/Yaw Rate [rad//s]'
  //   Product: '<S3>/Divide'
  //   Trigonometry: '<S3>/Tan'

  rtb_YawErrorrads = std::abs(PID_TV_U.Vx_B) * std::tan(PID_TV_U.WheelDeltarad) /
    1.535 - PID_TV_U.YawRaterads;
  shit_in = rtb_YawErrorrads;
  // Product: '<S38>/NProd Out' incorporates:
  //   DiscreteIntegrator: '<S30>/Filter'
  //   Inport: '<Root>/PID_D'
  //   Inport: '<Root>/PID_N'
  //   Product: '<S29>/DProd Out'
  //   Sum: '<S30>/SumD'

  rtb_NProdOut = (rtb_YawErrorrads * PID_TV_U.PID_D - PID_TV_DW.Filter_DSTATE) *
    PID_TV_U.PID_N;

  // Gain: '<S1>/Gain' incorporates:
  //   DiscreteIntegrator: '<S35>/Integrator'
  //   Inport: '<Root>/PID_P'
  //   Product: '<S40>/PProd Out'
  //   Sum: '<S44>/Sum'

  rtb_Gain = -((rtb_YawErrorrads * PID_TV_U.PID_P + PID_TV_DW.Integrator_DSTATE)
               + rtb_NProdOut);
  shit_out = rtb_Gain;
  // Update for DiscreteIntegrator: '<S35>/Integrator' incorporates:
  //   Inport: '<Root>/PID_I'
  //   Product: '<S32>/IProd Out'

  PID_TV_DW.Integrator_DSTATE += rtb_YawErrorrads * PID_TV_U.PID_I * 0.2;

  // Update for DiscreteIntegrator: '<S30>/Filter'
  PID_TV_DW.Filter_DSTATE += 0.2 * rtb_NProdOut;

  // Outport: '<Root>/FR_out' incorporates:
  //   Inport: '<Root>/FR_in'
  //   Sum: '<S1>/Sum'

  PID_TV_Y.FR_out = rtb_Gain + PID_TV_U.FR_in;

  // Outport: '<Root>/RR_out' incorporates:
  //   Inport: '<Root>/RR_in'
  //   Sum: '<S1>/Sum1'

  PID_TV_Y.RR_out = rtb_Gain + PID_TV_U.RR_in;

  // Outport: '<Root>/FL_out' incorporates:
  //   Inport: '<Root>/FL_in'
  //   Sum: '<S1>/Sum2'

  PID_TV_Y.FL_out = PID_TV_U.FL_in - rtb_Gain;

  // Outport: '<Root>/RL_out' incorporates:
  //   Inport: '<Root>/RL_in'
  //   Sum: '<S1>/Sum3'

  PID_TV_Y.RL_out = PID_TV_U.RL_in - rtb_Gain;

  // End of Outputs for SubSystem: '<Root>/PID_TV'
}

// Model initialize function
void PID_TV::initialize()
{
  // Registration code

  // Initialize DataMapInfo substructure containing ModelMap for C API
  PID_TV_InitializeDataMapInfo((&PID_TV_M));
}

// Model terminate function
void PID_TV::terminate()
{
  // (no terminate code required)
}

// Constructor
PID_TV::PID_TV() :
  PID_TV_U(),
  PID_TV_Y(),
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

//
// File trailer for generated code.
//
// [EOF]
//
