//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PID_TV.cpp
//
// Code generated for Simulink model 'PID_TV'.
//
// Model version                  : 1.59
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Sun Apr 21 22:57:07 2024
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
  // InitializeConditions for DiscreteIntegrator: '<S41>/Integrator'
  PID_TV_DW.Integrator_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S36>/Filter'
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
                  real_T *rtu_AbsoluteTorqueLimit, const real_T
                  *rtu_InitialTorqueAvgRequest, const real_T
                  *rtu_YawPIDErrorThreshold, const real_T
                  *rtu_YawPIDCoastThreshold, const real_T
                  *rtu_YawPIDVelThreshold, const boolean_T
                  *rtu_useTCSLimitedYawPID, const real_T *rtu_TCSStatusFL, const
                  real_T *rtu_TCSStatusFR, const real_T *rtu_TCSStatusRL, const
                  real_T *rtu_TCSStatusRR, const real_T
                  *rtu_YawPIDMaxDifferential, const real_T *rtu_Brakes_P, const
                  real_T *rtu_Brakes_I, const real_T *rtu_Brakes_D, const
                  boolean_T *rtu_useDecoupledYawBrakes, const boolean_T
                  *rtu_useDiscontinuousYawPIDBrake, const real_T
                  *rtu_decoupledYawPIDBrakesMaxDIf, const real_T
                  *rtu_discontinuousBrakesPercentT, const real_T *rtu_RegenLimit,
                  real_T *rty_FR_out, real_T *rty_RR_out, real_T *rty_FL_out,
                  real_T *rty_RL_out, real_T *rty_YawRateErrorrads, real_T
                  *rty_YawPIDOutput)
{
  real_T Torque_Output_FL;
  real_T Torque_Output_RL;
  real_T Torque_Output_RR;
  real_T rtb_Abs;
  real_T rtb_D;
  real_T rtb_Integrator;
  real_T rtb_PIDMaxDifferential;
  real_T rtb_YawErrorrads;
  int32_T rtb_Switch7;
  int8_T rtb_Switch1_p;
  int8_T tmp;
  boolean_T rtb_RelationalOperator;

  // Outputs for Atomic SubSystem: '<Root>/PID_TV'
  // Sum: '<S6>/Subtract'
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

  // MATLAB Function: '<S1>/MATLAB Function1'
  if (*rtu_InitialTorqueAvgRequest >= 0.0) {
    rtb_Abs = *rtu_PID_P;
    rtb_YawErrorrads = *rtu_PID_I;
    rtb_D = *rtu_PID_D;
    rtb_PIDMaxDifferential = *rtu_YawPIDMaxDifferential;
  } else if (*rtu_useDecoupledYawBrakes) {
    rtb_Abs = *rtu_Brakes_P;
    rtb_YawErrorrads = *rtu_Brakes_I;
    rtb_D = *rtu_Brakes_D;
    rtb_PIDMaxDifferential = *rtu_decoupledYawPIDBrakesMaxDIf;
  } else {
    rtb_Abs = *rtu_PID_P;
    rtb_YawErrorrads = *rtu_PID_I;
    rtb_D = *rtu_PID_D;
    rtb_PIDMaxDifferential = *rtu_YawPIDMaxDifferential;
  }

  // End of MATLAB Function: '<S1>/MATLAB Function1'

  // Product: '<S46>/PProd Out'
  rtb_Abs *= *rty_YawRateErrorrads;

  // Switch: '<S1>/Switch7'
  rtb_Switch7 = !(rtb_Integrator > 0.0);

  // DiscreteIntegrator: '<S41>/Integrator'
  if ((rtb_Switch7 > 0) && (PID_TV_DW.Integrator_PrevResetState <= 0)) {
    PID_TV_DW.Integrator_DSTATE = 0.0;
  }

  // Product: '<S35>/DProd Out'
  rtb_Integrator = *rty_YawRateErrorrads * rtb_D;

  // DiscreteIntegrator: '<S36>/Filter'
  if ((rtb_Switch7 > 0) && (PID_TV_DW.Filter_PrevResetState <= 0)) {
    PID_TV_DW.Filter_DSTATE = 0.0;
  }

  // Product: '<S44>/NProd Out' incorporates:
  //   DiscreteIntegrator: '<S36>/Filter'
  //   Sum: '<S36>/SumD'

  rtb_Integrator = (rtb_Integrator - PID_TV_DW.Filter_DSTATE) * *rtu_PID_N;

  // Sum: '<S51>/Sum' incorporates:
  //   DiscreteIntegrator: '<S41>/Integrator'

  rtb_Abs = (rtb_Abs + PID_TV_DW.Integrator_DSTATE) + rtb_Integrator;

  // Gain: '<S1>/Gain2'
  rtb_PIDMaxDifferential *= 0.5;

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant'
  //   Switch: '<S49>/Switch2'

  if (*rtu_usePIDTV) {
    // Switch: '<S49>/Switch2' incorporates:
    //   Gain: '<S1>/Gain'
    //   Gain: '<S1>/Gain1'
    //   RelationalOperator: '<S49>/LowerRelop1'
    //   RelationalOperator: '<S49>/UpperRelop'
    //   Switch: '<S49>/Switch'

    if (rtb_Abs > rtb_PIDMaxDifferential) {
      *rty_YawPIDOutput = -rtb_PIDMaxDifferential;
    } else if (rtb_Abs < -rtb_PIDMaxDifferential) {
      // Switch: '<S49>/Switch' incorporates:
      //   Gain: '<S1>/Gain1'

      *rty_YawPIDOutput = rtb_PIDMaxDifferential;
    } else {
      *rty_YawPIDOutput = -rtb_Abs;
    }
  } else {
    *rty_YawPIDOutput = 0.0;
  }

  // End of Switch: '<S1>/Switch'

  // MATLAB Function: '<S1>/MATLAB Function'
  if (*rtu_InitialTorqueAvgRequest > 0.0) {
    Torque_Output_FL = *rtu_FL_in - *rty_YawPIDOutput;
    rtb_D = *rtu_FR_in + *rty_YawPIDOutput;
    Torque_Output_RL = *rtu_RL_in - *rty_YawPIDOutput;
    Torque_Output_RR = *rtu_RR_in + *rty_YawPIDOutput;
  } else if (*rtu_InitialTorqueAvgRequest == 0.0) {
    if (std::abs(*rtu_Vx_B) > *rtu_YawPIDCoastThreshold) {
      Torque_Output_FL = *rtu_FL_in - *rty_YawPIDOutput;
      rtb_D = *rtu_FR_in + *rty_YawPIDOutput;
      Torque_Output_RL = *rtu_RL_in - *rty_YawPIDOutput;
      Torque_Output_RR = *rtu_RR_in + *rty_YawPIDOutput;
    } else {
      Torque_Output_FL = 0.0;
      rtb_D = 0.0;
      Torque_Output_RL = 0.0;
      Torque_Output_RR = 0.0;
    }
  } else {
    if (*rty_YawPIDOutput < 0.0) {
      Torque_Output_FL = *rtu_FL_in;
      rtb_D = *rtu_FR_in + *rty_YawPIDOutput;
      Torque_Output_RL = *rtu_RL_in;
      Torque_Output_RR = *rtu_RR_in + *rty_YawPIDOutput;
    } else if (*rty_YawPIDOutput > 0.0) {
      Torque_Output_FL = *rtu_FL_in - *rty_YawPIDOutput;
      rtb_D = *rtu_FR_in;
      Torque_Output_RL = *rtu_RL_in - *rty_YawPIDOutput;
      Torque_Output_RR = *rtu_RR_in;
    } else {
      Torque_Output_FL = *rtu_FL_in;
      rtb_D = *rtu_FR_in;
      Torque_Output_RL = *rtu_RL_in;
      Torque_Output_RR = *rtu_RR_in;
    }

    if ((*rtu_useDiscontinuousYawPIDBrake) && (std::abs
         (*rtu_InitialTorqueAvgRequest) / std::abs(*rtu_RegenLimit) >=
         *rtu_discontinuousBrakesPercentT)) {
      Torque_Output_FL = *rtu_FL_in;
      rtb_D = *rtu_FR_in;
      Torque_Output_RL = *rtu_RL_in;
      Torque_Output_RR = *rtu_RR_in;
    }

    if (Torque_Output_FL > 0.0) {
      Torque_Output_FL = 0.0;
    }

    if (rtb_D > 0.0) {
      rtb_D = 0.0;
    }

    if (Torque_Output_RL > 0.0) {
      Torque_Output_RL = 0.0;
    }

    if (Torque_Output_RR > 0.0) {
      Torque_Output_RR = 0.0;
    }
  }

  if (*rtu_useTCSLimitedYawPID) {
    if ((*rtu_TCSStatusFL == 1.0) && (Torque_Output_FL > *rtu_FL_in)) {
      Torque_Output_FL = *rtu_FL_in;
    }

    if ((*rtu_TCSStatusFR == 1.0) && (rtb_D > *rtu_FR_in)) {
      rtb_D = *rtu_FR_in;
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
  *rty_FR_out = rtb_D;
  *rty_RL_out = Torque_Output_RL;
  *rty_RR_out = Torque_Output_RR;
  if (std::abs(Torque_Output_FL) > *rtu_AbsoluteTorqueLimit) {
    if (std::isnan(Torque_Output_FL)) {
      Torque_Output_FL = (rtNaN);
    } else if (Torque_Output_FL < 0.0) {
      Torque_Output_FL = -1.0;
    } else {
      Torque_Output_FL = (Torque_Output_FL > 0.0);
    }

    *rty_FL_out = *rtu_AbsoluteTorqueLimit * Torque_Output_FL;
  }

  if (std::abs(rtb_D) > *rtu_AbsoluteTorqueLimit) {
    if (std::isnan(rtb_D)) {
      Torque_Output_FL = (rtNaN);
    } else if (rtb_D < 0.0) {
      Torque_Output_FL = -1.0;
    } else {
      Torque_Output_FL = (rtb_D > 0.0);
    }

    *rty_FR_out = *rtu_AbsoluteTorqueLimit * Torque_Output_FL;
  }

  if (std::abs(Torque_Output_RL) > *rtu_AbsoluteTorqueLimit) {
    if (std::isnan(Torque_Output_RL)) {
      Torque_Output_FL = (rtNaN);
    } else if (Torque_Output_RL < 0.0) {
      Torque_Output_FL = -1.0;
    } else {
      Torque_Output_FL = (Torque_Output_RL > 0.0);
    }

    *rty_RL_out = *rtu_AbsoluteTorqueLimit * Torque_Output_FL;
  }

  if (std::abs(Torque_Output_RR) > *rtu_AbsoluteTorqueLimit) {
    if (std::isnan(Torque_Output_RR)) {
      Torque_Output_FL = (rtNaN);
    } else if (Torque_Output_RR < 0.0) {
      Torque_Output_FL = -1.0;
    } else {
      Torque_Output_FL = (Torque_Output_RR > 0.0);
    }

    *rty_RR_out = *rtu_AbsoluteTorqueLimit * Torque_Output_FL;
  }

  // End of MATLAB Function: '<S1>/PID Torque Overflow Check2'

  // Switch: '<S34>/Switch' incorporates:
  //   RelationalOperator: '<S34>/u_GTE_up'

  if (!(rtb_Abs >= rtb_PIDMaxDifferential)) {
    // Switch: '<S34>/Switch1' incorporates:
    //   Gain: '<S1>/Gain1'
    //   RelationalOperator: '<S34>/u_GT_lo'

    if (rtb_Abs > -rtb_PIDMaxDifferential) {
      rtb_PIDMaxDifferential = rtb_Abs;
    } else {
      rtb_PIDMaxDifferential = -rtb_PIDMaxDifferential;
    }

    // End of Switch: '<S34>/Switch1'
  }

  // Sum: '<S34>/Diff' incorporates:
  //   Switch: '<S34>/Switch'

  rtb_Abs -= rtb_PIDMaxDifferential;

  // RelationalOperator: '<S31>/Relational Operator' incorporates:
  //   Constant: '<S31>/Clamping_zero'

  rtb_RelationalOperator = (rtb_Abs != 0.0);

  // Switch: '<S31>/Switch1' incorporates:
  //   Constant: '<S31>/Clamping_zero'
  //   Constant: '<S31>/Constant'
  //   Constant: '<S31>/Constant2'
  //   RelationalOperator: '<S31>/fix for DT propagation issue'

  if (rtb_Abs > 0.0) {
    rtb_Switch1_p = 1;
  } else {
    rtb_Switch1_p = -1;
  }

  // End of Switch: '<S31>/Switch1'

  // Product: '<S38>/IProd Out'
  rtb_Abs = *rty_YawRateErrorrads * rtb_YawErrorrads;

  // Switch: '<S31>/Switch2' incorporates:
  //   Constant: '<S31>/Clamping_zero'
  //   Constant: '<S31>/Constant3'
  //   Constant: '<S31>/Constant4'
  //   RelationalOperator: '<S31>/fix for DT propagation issue1'

  if (rtb_Abs > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S31>/Switch' incorporates:
  //   Constant: '<S31>/Constant1'
  //   Logic: '<S31>/AND3'
  //   RelationalOperator: '<S31>/Equal1'
  //   Switch: '<S31>/Switch2'

  if (rtb_RelationalOperator && (rtb_Switch1_p == tmp)) {
    rtb_Abs = 0.0;
  }

  // Update for DiscreteIntegrator: '<S41>/Integrator' incorporates:
  //   DiscreteIntegrator: '<S36>/Filter'
  //   Switch: '<S31>/Switch'

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

  // End of Update for DiscreteIntegrator: '<S41>/Integrator'

  // Update for DiscreteIntegrator: '<S36>/Filter'
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
