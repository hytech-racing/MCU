//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PID_TV.cpp
//
// Code generated for Simulink model 'PID_TV'.
//
// Model version                  : 1.54
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Sat Apr 20 04:12:30 2024
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

extern "C"
{

#include "rt_nonfinite.h"

}

#include "PID_TV_private.h"

// System initialize for referenced model: 'PID_TV'
void PID_TV::init(void)
{
  // SystemInitialize for Atomic SubSystem: '<Root>/PID_TV'
  // InitializeConditions for DiscreteIntegrator: '<S40>/Integrator'
  PID_TV_DW.Integrator_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S35>/Filter'
  PID_TV_DW.Filter_PrevResetState = 2;

  // End of SystemInitialize for SubSystem: '<Root>/PID_TV'
}

// Output and update for referenced model: 'PID_TV'
void PID_TV::step(const real_T *rtu_YawRaterads, const real_T *rtu_PID_I, const
                  real_T *rtu_PID_D, const real_T *rtu_PID_N, const real_T
                  *rtu_PID_P, const real_T *rtu_FR_in, const real_T *rtu_RR_in,
                  const real_T *rtu_FL_in, const real_T *rtu_RL_in, const
                  boolean_T *rtu_usePIDTV, const real_T
                  *rtu_KinematicDesiredYawRaterad, const real_T *rtu_Vx_B, const
                  real_T *rtu_TorqueLimit, const real_T
                  *rtu_InitialTorqueAvgRequest, const real_T
                  *rtu_YawPIDErrorThreshold, const real_T
                  *rtu_YawPIDCoastThreshold, const real_T
                  *rtu_YawPIDVelThreshold, const real_T *rtu_useTCSLimitedYawPID,
                  const real_T *rtu_TCSStatusFL, const real_T *rtu_TCSStatusFR,
                  const real_T *rtu_TCSStatusRL, const real_T *rtu_TCSStatusRR,
                  const real_T *rtu_YawPIDMaxDifferential, real_T *rty_FR_out,
                  real_T *rty_RR_out, real_T *rty_FL_out, real_T *rty_RL_out,
                  real_T *rty_YawRateErrorrads, real_T *rty_YawPIDOutput)
{
  real_T Torque_Output_FL;
  real_T Torque_Output_RL;
  real_T Torque_Output_RR;
  real_T rtb_Abs;
  real_T rtb_Integrator;
  real_T rtb_Switch2;
  real_T rtb_YawErrorrads;
  int32_T rtb_Switch7;
  int8_T rtb_Switch1_p;
  int8_T tmp;
  boolean_T rtb_LowerRelop1;

  // Outputs for Atomic SubSystem: '<Root>/PID_TV'
  // Sum: '<S5>/Subtract'
  rtb_YawErrorrads = *rtu_KinematicDesiredYawRaterad - *rtu_YawRaterads;

  // Sum: '<S1>/Subtract1' incorporates:
  //   Abs: '<S1>/Abs4'

  rtb_Integrator = std::abs(rtb_YawErrorrads) - *rtu_YawPIDErrorThreshold;

  // Switch: '<S1>/Switch6' incorporates:
  //   Constant: '<S1>/Constant1'

  if (rtb_Integrator > 0.0) {
    // Abs: '<S1>/Abs'
    rtb_Abs = std::abs(*rtu_Vx_B);

    // Sum: '<S1>/Subtract'
    rtb_Abs -= *rtu_YawPIDVelThreshold;

    // Switch: '<S1>/Switch1' incorporates:
    //   Constant: '<S1>/Constant1'

    if (rtb_Abs > 0.0) {
      *rty_YawRateErrorrads = rtb_YawErrorrads;
    } else {
      *rty_YawRateErrorrads = 0.0;
    }

    // End of Switch: '<S1>/Switch1'
  } else {
    *rty_YawRateErrorrads = 0.0;
  }

  // End of Switch: '<S1>/Switch6'

  // Product: '<S45>/PProd Out'
  rtb_YawErrorrads = *rty_YawRateErrorrads * *rtu_PID_P;

  // Switch: '<S1>/Switch7'
  rtb_Switch7 = !(rtb_Integrator > 0.0);

  // DiscreteIntegrator: '<S40>/Integrator'
  if ((rtb_Switch7 > 0) && (PID_TV_DW.Integrator_PrevResetState <= 0)) {
    PID_TV_DW.Integrator_DSTATE = 0.0;
  }

  // Product: '<S34>/DProd Out'
  rtb_Integrator = *rty_YawRateErrorrads * *rtu_PID_D;

  // DiscreteIntegrator: '<S35>/Filter'
  if ((rtb_Switch7 > 0) && (PID_TV_DW.Filter_PrevResetState <= 0)) {
    PID_TV_DW.Filter_DSTATE = 0.0;
  }

  // Product: '<S43>/NProd Out' incorporates:
  //   DiscreteIntegrator: '<S35>/Filter'
  //   Sum: '<S35>/SumD'

  rtb_Integrator = (rtb_Integrator - PID_TV_DW.Filter_DSTATE) * *rtu_PID_N;

  // Sum: '<S50>/Sum' incorporates:
  //   DiscreteIntegrator: '<S40>/Integrator'

  rtb_YawErrorrads = (rtb_YawErrorrads + PID_TV_DW.Integrator_DSTATE) +
    rtb_Integrator;

  // Gain: '<S1>/Gain1'
  rtb_Abs = -*rtu_YawPIDMaxDifferential;

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant'
  //   Gain: '<S1>/Gain'

  if (*rtu_usePIDTV) {
    // RelationalOperator: '<S48>/LowerRelop1'
    rtb_LowerRelop1 = (rtb_YawErrorrads > *rtu_YawPIDMaxDifferential);

    // Switch: '<S48>/Switch2' incorporates:
    //   RelationalOperator: '<S48>/UpperRelop'
    //   Switch: '<S48>/Switch'

    if (rtb_LowerRelop1) {
      rtb_Switch2 = *rtu_YawPIDMaxDifferential;
    } else if (rtb_YawErrorrads < rtb_Abs) {
      // Switch: '<S48>/Switch'
      rtb_Switch2 = rtb_Abs;
    } else {
      rtb_Switch2 = rtb_YawErrorrads;
    }

    // End of Switch: '<S48>/Switch2'
    *rty_YawPIDOutput = -rtb_Switch2;
  } else {
    *rty_YawPIDOutput = 0.0;
  }

  // End of Switch: '<S1>/Switch'

  // MATLAB Function: '<S1>/MATLAB Function'
  if (*rtu_InitialTorqueAvgRequest > 0.0) {
    Torque_Output_FL = *rtu_FL_in - *rty_YawPIDOutput;
    rtb_Switch2 = *rtu_FR_in + *rty_YawPIDOutput;
    Torque_Output_RL = *rtu_RL_in - *rty_YawPIDOutput;
    Torque_Output_RR = *rtu_RR_in + *rty_YawPIDOutput;
  } else if (*rtu_InitialTorqueAvgRequest == 0.0) {
    if (std::abs(*rtu_Vx_B) > *rtu_YawPIDCoastThreshold) {
      Torque_Output_FL = *rtu_FL_in - *rty_YawPIDOutput;
      rtb_Switch2 = *rtu_FR_in + *rty_YawPIDOutput;
      Torque_Output_RL = *rtu_RL_in - *rty_YawPIDOutput;
      Torque_Output_RR = *rtu_RR_in + *rty_YawPIDOutput;
    } else {
      Torque_Output_FL = 0.0;
      rtb_Switch2 = 0.0;
      Torque_Output_RL = 0.0;
      Torque_Output_RR = 0.0;
    }
  } else {
    if (*rty_YawPIDOutput < 0.0) {
      Torque_Output_FL = *rtu_FL_in;
      rtb_Switch2 = *rtu_FR_in + *rty_YawPIDOutput;
      Torque_Output_RL = *rtu_RL_in;
      Torque_Output_RR = *rtu_RR_in + *rty_YawPIDOutput;
    } else if (*rty_YawPIDOutput > 0.0) {
      Torque_Output_FL = *rtu_FL_in - *rty_YawPIDOutput;
      rtb_Switch2 = *rtu_FR_in;
      Torque_Output_RL = *rtu_RL_in - *rty_YawPIDOutput;
      Torque_Output_RR = *rtu_RR_in;
    } else {
      Torque_Output_FL = *rtu_FL_in;
      rtb_Switch2 = *rtu_FR_in;
      Torque_Output_RL = *rtu_RL_in;
      Torque_Output_RR = *rtu_RR_in;
    }

    if (Torque_Output_FL > 0.0) {
      Torque_Output_FL = 0.0;
    }

    if (rtb_Switch2 > 0.0) {
      rtb_Switch2 = 0.0;
    }

    if (Torque_Output_RL > 0.0) {
      Torque_Output_RL = 0.0;
    }

    if (Torque_Output_RR > 0.0) {
      Torque_Output_RR = 0.0;
    }
  }

  if (*rtu_useTCSLimitedYawPID != 0.0) {
    if ((*rtu_TCSStatusFL == 1.0) && (Torque_Output_FL > *rtu_FL_in)) {
      Torque_Output_FL = *rtu_FL_in;
    }

    if ((*rtu_TCSStatusFR == 1.0) && (rtb_Switch2 > *rtu_FR_in)) {
      rtb_Switch2 = *rtu_FR_in;
    }

    if ((*rtu_TCSStatusRL == 1.0) && (Torque_Output_RL > *rtu_RL_in)) {
      Torque_Output_RL = *rtu_RL_in;
    }

    if ((*rtu_TCSStatusRR == 1.0) && (Torque_Output_RR > *rtu_RR_in)) {
      Torque_Output_RR = *rtu_RR_in;
    }
  }

  // MATLAB Function: '<S1>/PID Torque Overflow Check2' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function'

  *rty_FL_out = Torque_Output_FL;
  *rty_FR_out = rtb_Switch2;
  *rty_RL_out = Torque_Output_RL;
  *rty_RR_out = Torque_Output_RR;
  if (std::abs(Torque_Output_FL) > *rtu_TorqueLimit) {
    if (std::isnan(Torque_Output_FL)) {
      Torque_Output_FL = (rtNaN);
    } else if (Torque_Output_FL < 0.0) {
      Torque_Output_FL = -1.0;
    } else {
      Torque_Output_FL = (Torque_Output_FL > 0.0);
    }

    *rty_FL_out = *rtu_TorqueLimit * Torque_Output_FL;
  }

  if (std::abs(rtb_Switch2) > *rtu_TorqueLimit) {
    if (std::isnan(rtb_Switch2)) {
      Torque_Output_FL = (rtNaN);
    } else if (rtb_Switch2 < 0.0) {
      Torque_Output_FL = -1.0;
    } else {
      Torque_Output_FL = (rtb_Switch2 > 0.0);
    }

    *rty_FR_out = *rtu_TorqueLimit * Torque_Output_FL;
  }

  if (std::abs(Torque_Output_RL) > *rtu_TorqueLimit) {
    if (std::isnan(Torque_Output_RL)) {
      Torque_Output_FL = (rtNaN);
    } else if (Torque_Output_RL < 0.0) {
      Torque_Output_FL = -1.0;
    } else {
      Torque_Output_FL = (Torque_Output_RL > 0.0);
    }

    *rty_RL_out = *rtu_TorqueLimit * Torque_Output_FL;
  }

  if (std::abs(Torque_Output_RR) > *rtu_TorqueLimit) {
    if (std::isnan(Torque_Output_RR)) {
      Torque_Output_FL = (rtNaN);
    } else if (Torque_Output_RR < 0.0) {
      Torque_Output_FL = -1.0;
    } else {
      Torque_Output_FL = (Torque_Output_RR > 0.0);
    }

    *rty_RR_out = *rtu_TorqueLimit * Torque_Output_FL;
  }

  // End of MATLAB Function: '<S1>/PID Torque Overflow Check2'

  // RelationalOperator: '<S33>/u_GTE_up'
  rtb_LowerRelop1 = (rtb_YawErrorrads >= *rtu_YawPIDMaxDifferential);

  // Switch: '<S33>/Switch' incorporates:
  //   RelationalOperator: '<S33>/u_GT_lo'
  //   Switch: '<S33>/Switch1'

  if (rtb_LowerRelop1) {
    rtb_Abs = *rtu_YawPIDMaxDifferential;
  } else if (rtb_YawErrorrads > rtb_Abs) {
    // Switch: '<S33>/Switch1'
    rtb_Abs = rtb_YawErrorrads;
  }

  // End of Switch: '<S33>/Switch'

  // Sum: '<S33>/Diff'
  rtb_Abs = rtb_YawErrorrads - rtb_Abs;

  // RelationalOperator: '<S30>/Relational Operator' incorporates:
  //   Constant: '<S30>/Clamping_zero'

  rtb_LowerRelop1 = (rtb_Abs != 0.0);

  // Switch: '<S30>/Switch1' incorporates:
  //   Constant: '<S30>/Clamping_zero'
  //   Constant: '<S30>/Constant'
  //   Constant: '<S30>/Constant2'
  //   RelationalOperator: '<S30>/fix for DT propagation issue'

  if (rtb_Abs > 0.0) {
    rtb_Switch1_p = 1;
  } else {
    rtb_Switch1_p = -1;
  }

  // End of Switch: '<S30>/Switch1'

  // Product: '<S37>/IProd Out'
  rtb_Abs = *rty_YawRateErrorrads * *rtu_PID_I;

  // Switch: '<S30>/Switch2' incorporates:
  //   Constant: '<S30>/Clamping_zero'
  //   Constant: '<S30>/Constant3'
  //   Constant: '<S30>/Constant4'
  //   RelationalOperator: '<S30>/fix for DT propagation issue1'

  if (rtb_Abs > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S30>/Switch' incorporates:
  //   Constant: '<S30>/Constant1'
  //   Logic: '<S30>/AND3'
  //   RelationalOperator: '<S30>/Equal1'
  //   Switch: '<S30>/Switch2'

  if (rtb_LowerRelop1 && (rtb_Switch1_p == tmp)) {
    rtb_Abs = 0.0;
  }

  // Update for DiscreteIntegrator: '<S40>/Integrator' incorporates:
  //   DiscreteIntegrator: '<S35>/Filter'
  //   Switch: '<S30>/Switch'

  PID_TV_DW.Integrator_DSTATE += 0.001 * rtb_Abs;
  if (PID_TV_DW.Integrator_DSTATE > 1.5) {
    PID_TV_DW.Integrator_DSTATE = 1.5;
  } else if (PID_TV_DW.Integrator_DSTATE < -1.5) {
    PID_TV_DW.Integrator_DSTATE = -1.5;
  }

  if (rtb_Switch7 > 0) {
    PID_TV_DW.Integrator_PrevResetState = 1;
    PID_TV_DW.Filter_PrevResetState = 1;
  } else {
    PID_TV_DW.Integrator_PrevResetState = 0;
    PID_TV_DW.Filter_PrevResetState = 0;
  }

  // End of Update for DiscreteIntegrator: '<S40>/Integrator'

  // Update for DiscreteIntegrator: '<S35>/Filter'
  PID_TV_DW.Filter_DSTATE += 0.001 * rtb_Integrator;

  // End of Outputs for SubSystem: '<Root>/PID_TV'
}

// Model initialize function
void PID_TV::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

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
