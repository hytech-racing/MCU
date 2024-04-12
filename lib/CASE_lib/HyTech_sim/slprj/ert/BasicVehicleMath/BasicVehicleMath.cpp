//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: BasicVehicleMath.cpp
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
#include "BasicVehicleMath.h"
#include "rtwtypes.h"
#include <cmath>
#include "rt_atan2d_snf.h"
#include "BasicVehicleMath_capi.h"
#include "look1_binlxpw.h"
#include "BasicVehicleMath_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

//
// Output and update for action system:
//    '<S17>/Accel. Calc'
//    '<S18>/Accel. Calc'
//    '<S19>/Accel. Calc'
//    '<S20>/Accel. Calc'
//
void BasicVehicleMath::BasicVehicleMath_AccelCalc(real_T rtu_CornerSpeed, real_T
  rtu_WheelOmega1, real_T *rty_SL)
{
  real_T rtb_Switch3;
  real_T tmp;

  // Product: '<S21>/Product' incorporates:
  //   Constant: '<S21>/Constant'

  rtb_Switch3 = rtu_WheelOmega1 * 0.2;

  // Switch: '<S21>/Switch' incorporates:
  //   Constant: '<S21>/Constant1'

  if (rtb_Switch3 != 0.0) {
    tmp = rtb_Switch3;
  } else {
    tmp = (rtInf);
  }

  // Product: '<S21>/Divide' incorporates:
  //   Sum: '<S21>/Subtract'
  //   Switch: '<S21>/Switch'

  rtb_Switch3 = (rtb_Switch3 - rtu_CornerSpeed) / tmp;

  // Switch: '<S21>/Switch3' incorporates:
  //   Constant: '<S21>/Constant3'

  if (!(rtb_Switch3 > 0.0)) {
    rtb_Switch3 = 0.0;
  }

  // End of Switch: '<S21>/Switch3'

  // Switch: '<S21>/Switch1' incorporates:
  //   Constant: '<S21>/Constant2'

  if (rtb_Switch3 > 1.0) {
    *rty_SL = 1.0;
  } else {
    *rty_SL = rtb_Switch3;
  }

  // End of Switch: '<S21>/Switch1'
}

//
// Output and update for action system:
//    '<S17>/Brake Calc'
//    '<S18>/Brake Calc'
//    '<S19>/Brake Calc'
//    '<S20>/Brake Calc'
//
void BasicVehicleMath::BasicVehicleMath_BrakeCalc(real_T rtu_WheelOmega, real_T
  rtu_CornerSpeed, real_T *rty_SL)
{
  real_T rtb_LongitudinalSlipSL;

  // Product: '<S22>/Divide' incorporates:
  //   Constant: '<S22>/Constant'
  //   Product: '<S22>/Product'
  //   Sum: '<S22>/Subtract'

  rtb_LongitudinalSlipSL = (rtu_WheelOmega * 0.2 - rtu_CornerSpeed) /
    rtu_CornerSpeed;

  // Switch: '<S22>/Switch' incorporates:
  //   Abs: '<S22>/Abs'
  //   Constant: '<S22>/Constant1'

  if (std::abs(rtb_LongitudinalSlipSL) > 1.0) {
    rtb_LongitudinalSlipSL = -1.0;
  }

  // Gain: '<S22>/Gain' incorporates:
  //   Abs: '<S22>/Abs1'
  //   Switch: '<S22>/Switch'

  *rty_SL = -std::abs(rtb_LongitudinalSlipSL);
}

// Output and update for referenced model: 'BasicVehicleMath'
void BasicVehicleMath::step(const real_T *rtu_Vx_Bms, const real_T *rtu_Vy_Bms,
  const real_T *rtu_YawRaterads, const real_T *rtu_MotorOmegaFLrpm, const real_T
  *rtu_MotorOmegaFRrpm, const real_T *rtu_MotorOmegaRLrpm, const real_T
  *rtu_MotorOmegaRRrpm, const real_T *rtu_SteeringWheelAngleDeg, real_T
  *rty_BetaDeg, real_T *rty_AlphaFLDeg, real_T *rty_AlphaFRDeg, real_T
  *rty_AlphaRLDeg, real_T *rty_AlphaRRDeg, real_T *rty_LongitudinalCornerVelWFLm,
  real_T *rty_LongitudinalCornerVelWFRm, real_T *rty_LongitudinalCornerVelWRLm,
  real_T *rty_LongitudinalCornerVelWRRm, real_T *rty_KinematicDesiredYawRaterad,
  real_T *rty_SLFL, real_T *rty_SLFR, real_T *rty_SLRL, real_T *rty_SLRR, real_T
  *rty_WheelSteerAvgDeg, real_T *rty_WheelOmegaFLrads, real_T
  *rty_WheelOmegaFRrads, real_T *rty_WheelOmegaRLrads, real_T
  *rty_WheelOmegaRRrads)
{
  real_T Alpha_FL;
  real_T Alpha_FR;
  real_T den;
  real_T den_tmp;
  real_T rtb_Abs;
  real_T rtb_Abs1;
  real_T rtb_Alpha_RL;
  real_T rtb_Divide2;
  real_T rtb_Gain1_e_tmp;
  real_T rtb_Gain2_e;
  real_T rtb_Gain3_m;
  real_T rtb_LongCornerVel_FL_B;
  real_T rtb_LongCornerVel_FR_B;
  real_T rtb_SL;

  // Abs: '<Root>/Abs'
  rtb_Abs1 = std::abs(*rtu_SteeringWheelAngleDeg);

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant2'

  if (*rtu_Vx_Bms > 0.0) {
    rtb_Abs = *rtu_Vx_Bms;
  } else {
    rtb_Abs = (rtInf);
  }

  // End of Switch: '<S1>/Switch'

  // Product: '<S1>/Divide2'
  rtb_Divide2 = *rtu_Vy_Bms / rtb_Abs;

  // Signum: '<Root>/Sign'
  rtb_Abs = *rtu_SteeringWheelAngleDeg;
  if (std::isnan(rtb_Abs)) {
    rtb_Gain1_e_tmp = (rtNaN);
  } else if (rtb_Abs < 0.0) {
    rtb_Gain1_e_tmp = -1.0;
  } else {
    rtb_Gain1_e_tmp = (rtb_Abs > 0.0);
  }

  // Product: '<Root>/Product' incorporates:
  //   Abs: '<S8>/Abs1'
  //   Lookup_n-D: '<Root>/1-D Lookup Table'
  //   Signum: '<Root>/Sign'

  *rty_WheelSteerAvgDeg = look1_binlxpw(rtb_Abs1, rtCP_uDLookupTable_bp01Data,
    rtCP_uDLookupTable_tableData, 200U) * rtb_Gain1_e_tmp;

  // Gain: '<S2>/Gain1' incorporates:
  //   Gain: '<S3>/Gain1'
  //   Gain: '<S4>/Gain1'
  //   Gain: '<S5>/Gain1'
  //   Gain: '<S6>/Gain1'

  rtb_Gain1_e_tmp = 0.017453292519943295 * *rty_WheelSteerAvgDeg;

  // Gain: '<Root>/Gain'
  rtb_Abs1 = 0.10471975511965977 * *rtu_MotorOmegaRRrpm;

  // Gain: '<Root>/Gain1'
  rtb_Abs = 0.10471975511965977 * *rtu_MotorOmegaRLrpm;

  // Gain: '<Root>/Gain2'
  rtb_Gain2_e = 0.10471975511965977 * *rtu_MotorOmegaFRrpm;

  // Gain: '<Root>/Gain3'
  rtb_Gain3_m = 0.10471975511965977 * *rtu_MotorOmegaFLrpm;

  // Abs: '<S7>/Abs'
  rtb_SL = std::abs(*rtu_Vx_Bms);

  // Product: '<S7>/Divide' incorporates:
  //   Constant: '<S7>/wb'
  //   Trigonometry: '<S7>/Tan'

  *rty_KinematicDesiredYawRaterad = rtb_SL * std::tan(rtb_Gain1_e_tmp) / 1.535;

  // MATLAB Function: '<S14>/MATLAB Function' incorporates:
  //   Constant: '<S14>/Constant'
  //   Constant: '<S14>/Constant2'
  //   Constant: '<S14>/Constant3'
  //   Constant: '<S14>/Constant4'
  //   Constant: '<S14>/Constant6'
  //   Constant: '<S14>/Constant7'
  //   Gain: '<S2>/Gain1'

  den_tmp = *rtu_YawRaterads * 0.96437803790837118 * 0.62216265449318331;
  den = den_tmp + *rtu_Vx_Bms;
  rtb_SL = *rtu_YawRaterads * 0.96437803790837118 * 0.78288800690392224 +
    *rtu_Vy_Bms;
  Alpha_FL = -(rtb_Gain1_e_tmp - rt_atan2d_snf(rtb_SL, den));
  if (std::isnan(Alpha_FL)) {
    if (rtb_Gain1_e_tmp != 0.0) {
      Alpha_FL = -rtb_Gain1_e_tmp;
    } else {
      Alpha_FL = 0.0;
    }
  }

  rtb_LongCornerVel_FL_B = den;
  den = *rtu_Vx_Bms - den_tmp;
  Alpha_FR = -(rtb_Gain1_e_tmp - rt_atan2d_snf(rtb_SL, den));
  if (std::isnan(Alpha_FR)) {
    if (rtb_Gain1_e_tmp != 0.0) {
      Alpha_FR = -rtb_Gain1_e_tmp;
    } else {
      Alpha_FR = 0.0;
    }
  }

  rtb_LongCornerVel_FR_B = den;
  den_tmp = *rtu_YawRaterads * 0.98407316801140354 * 0.60971076084969233;
  den = den_tmp + *rtu_Vx_Bms;
  rtb_SL = rt_atan2d_snf(*rtu_Vy_Bms - *rtu_YawRaterads * 0.98407316801140354 *
    0.79262398910460008, den);
  rtb_Alpha_RL = rtb_SL;
  if (std::isnan(rtb_SL)) {
    rtb_Alpha_RL = 0.0;
  }

  *rty_LongitudinalCornerVelWRLm = den;
  den = *rtu_Vx_Bms - den_tmp;
  rtb_SL = rt_atan2d_snf(*rtu_Vy_Bms - *rtu_YawRaterads * 0.98407316801140354 *
    0.79262398910460019, den);
  if (std::isnan(rtb_SL)) {
    rtb_SL = 0.0;
  }

  *rty_LongitudinalCornerVelWRRm = den;

  // Trigonometry: '<S8>/Cos' incorporates:
  //   Abs: '<S8>/Abs'
  //   Trigonometry: '<S8>/Cos1'

  rtb_Gain1_e_tmp = std::cos(std::abs(rtb_Gain1_e_tmp));

  // Product: '<S8>/Product' incorporates:
  //   Trigonometry: '<S8>/Cos'

  *rty_LongitudinalCornerVelWFLm = rtb_LongCornerVel_FL_B * rtb_Gain1_e_tmp;

  // Product: '<S8>/Product1'
  *rty_LongitudinalCornerVelWFRm = rtb_LongCornerVel_FR_B * rtb_Gain1_e_tmp;

  // Gain: '<S9>/Gain' incorporates:
  //   MATLAB Function: '<S14>/MATLAB Function'

  *rty_AlphaFLDeg = 57.295779513082323 * Alpha_FL;

  // Gain: '<S10>/Gain' incorporates:
  //   MATLAB Function: '<S14>/MATLAB Function'

  *rty_AlphaFRDeg = 57.295779513082323 * Alpha_FR;

  // Gain: '<S11>/Gain'
  *rty_AlphaRLDeg = 57.295779513082323 * rtb_Alpha_RL;

  // Gain: '<S12>/Gain'
  *rty_AlphaRRDeg = 57.295779513082323 * rtb_SL;

  // Gain: '<S13>/Gain' incorporates:
  //   Trigonometry: '<S1>/Atan'

  *rty_BetaDeg = 57.295779513082323 * std::atan(rtb_Divide2);

  // Gain: '<S15>/Gain'
  *rty_WheelOmegaFLrads = 0.084317032040472181 * rtb_Gain3_m;

  // Product: '<S17>/Product1' incorporates:
  //   Constant: '<S17>/Constant2'

  rtb_Divide2 = *rty_WheelOmegaFLrads * 0.2;

  // Sum: '<S17>/Subtract1'
  rtb_Divide2 -= *rty_LongitudinalCornerVelWFLm;

  // If: '<S17>/If2'
  if (rtb_Divide2 > 0.0) {
    // Outputs for IfAction SubSystem: '<S17>/Accel. Calc' incorporates:
    //   ActionPort: '<S21>/Action Port'

    BasicVehicleMath_AccelCalc(*rty_LongitudinalCornerVelWFLm,
      *rty_WheelOmegaFLrads, &rtb_SL);

    // End of Outputs for SubSystem: '<S17>/Accel. Calc'
  } else if (rtb_Divide2 < 0.0) {
    // Outputs for IfAction SubSystem: '<S17>/Brake Calc' incorporates:
    //   ActionPort: '<S22>/Action Port'

    BasicVehicleMath_BrakeCalc(*rty_WheelOmegaFLrads,
      *rty_LongitudinalCornerVelWFLm, &rtb_SL);

    // End of Outputs for SubSystem: '<S17>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S17>/If Action Subsystem' incorporates:
    //   ActionPort: '<S23>/Action Port'

    // SignalConversion generated from: '<S23>/in' incorporates:
    //   Constant: '<S17>/Constant1'

    rtb_SL = 0.0;

    // End of Outputs for SubSystem: '<S17>/If Action Subsystem'
  }

  // End of If: '<S17>/If2'

  // Switch: '<S15>/Switch'
  *rty_SLFL = rtb_SL;

  // Gain: '<S15>/Gain1'
  *rty_WheelOmegaFRrads = 0.084317032040472181 * rtb_Gain2_e;

  // Product: '<S18>/Product1' incorporates:
  //   Constant: '<S18>/Constant2'

  rtb_Gain2_e = *rty_WheelOmegaFRrads * 0.2;

  // Sum: '<S18>/Subtract1'
  rtb_Gain2_e -= *rty_LongitudinalCornerVelWFRm;

  // If: '<S18>/If2'
  if (rtb_Gain2_e > 0.0) {
    // Outputs for IfAction SubSystem: '<S18>/Accel. Calc' incorporates:
    //   ActionPort: '<S24>/Action Port'

    BasicVehicleMath_AccelCalc(*rty_LongitudinalCornerVelWFRm,
      *rty_WheelOmegaFRrads, &rtb_SL);

    // End of Outputs for SubSystem: '<S18>/Accel. Calc'
  } else if (rtb_Gain2_e < 0.0) {
    // Outputs for IfAction SubSystem: '<S18>/Brake Calc' incorporates:
    //   ActionPort: '<S25>/Action Port'

    BasicVehicleMath_BrakeCalc(*rty_WheelOmegaFRrads,
      *rty_LongitudinalCornerVelWFRm, &rtb_SL);

    // End of Outputs for SubSystem: '<S18>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S18>/If Action Subsystem' incorporates:
    //   ActionPort: '<S26>/Action Port'

    // SignalConversion generated from: '<S26>/in' incorporates:
    //   Constant: '<S18>/Constant1'

    rtb_SL = 0.0;

    // End of Outputs for SubSystem: '<S18>/If Action Subsystem'
  }

  // End of If: '<S18>/If2'

  // Switch: '<S15>/Switch1'
  *rty_SLFR = rtb_SL;

  // Gain: '<S15>/Gain2'
  *rty_WheelOmegaRLrads = 0.084317032040472181 * rtb_Abs;

  // Product: '<S19>/Product1' incorporates:
  //   Constant: '<S19>/Constant2'

  rtb_Abs = *rty_WheelOmegaRLrads * 0.2;

  // Sum: '<S19>/Subtract1'
  rtb_Abs -= *rty_LongitudinalCornerVelWRLm;

  // If: '<S19>/If2'
  if (rtb_Abs > 0.0) {
    // Outputs for IfAction SubSystem: '<S19>/Accel. Calc' incorporates:
    //   ActionPort: '<S27>/Action Port'

    BasicVehicleMath_AccelCalc(*rty_LongitudinalCornerVelWRLm,
      *rty_WheelOmegaRLrads, &rtb_SL);

    // End of Outputs for SubSystem: '<S19>/Accel. Calc'
  } else if (rtb_Abs < 0.0) {
    // Outputs for IfAction SubSystem: '<S19>/Brake Calc' incorporates:
    //   ActionPort: '<S28>/Action Port'

    BasicVehicleMath_BrakeCalc(*rty_WheelOmegaRLrads,
      *rty_LongitudinalCornerVelWRLm, &rtb_SL);

    // End of Outputs for SubSystem: '<S19>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S19>/If Action Subsystem' incorporates:
    //   ActionPort: '<S29>/Action Port'

    // SignalConversion generated from: '<S29>/in' incorporates:
    //   Constant: '<S19>/Constant1'

    rtb_SL = 0.0;

    // End of Outputs for SubSystem: '<S19>/If Action Subsystem'
  }

  // End of If: '<S19>/If2'

  // Switch: '<S15>/Switch2'
  *rty_SLRL = rtb_SL;

  // Gain: '<S15>/Gain3'
  *rty_WheelOmegaRRrads = 0.084317032040472181 * rtb_Abs1;

  // Product: '<S20>/Product1' incorporates:
  //   Constant: '<S20>/Constant2'

  rtb_Abs1 = *rty_WheelOmegaRRrads * 0.2;

  // Sum: '<S20>/Subtract1'
  rtb_Abs1 -= *rty_LongitudinalCornerVelWRRm;

  // If: '<S20>/If2'
  if (rtb_Abs1 > 0.0) {
    // Outputs for IfAction SubSystem: '<S20>/Accel. Calc' incorporates:
    //   ActionPort: '<S30>/Action Port'

    BasicVehicleMath_AccelCalc(*rty_LongitudinalCornerVelWRRm,
      *rty_WheelOmegaRRrads, &rtb_SL);

    // End of Outputs for SubSystem: '<S20>/Accel. Calc'
  } else if (rtb_Abs1 < 0.0) {
    // Outputs for IfAction SubSystem: '<S20>/Brake Calc' incorporates:
    //   ActionPort: '<S31>/Action Port'

    BasicVehicleMath_BrakeCalc(*rty_WheelOmegaRRrads,
      *rty_LongitudinalCornerVelWRRm, &rtb_SL);

    // End of Outputs for SubSystem: '<S20>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S20>/If Action Subsystem' incorporates:
    //   ActionPort: '<S32>/Action Port'

    // SignalConversion generated from: '<S32>/in' incorporates:
    //   Constant: '<S20>/Constant1'

    rtb_SL = 0.0;

    // End of Outputs for SubSystem: '<S20>/If Action Subsystem'
  }

  // End of If: '<S20>/If2'

  // Switch: '<S15>/Switch3'
  *rty_SLRR = rtb_SL;
}

// Model initialize function
void BasicVehicleMath::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // Initialize DataMapInfo substructure containing ModelMap for C API
  BasicVehicleMath_InitializeDataMapInfo((&BasicVehicleMath_M));
}

// Constructor
BasicVehicleMath::BasicVehicleMath() :
  BasicVehicleMath_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
BasicVehicleMath::~BasicVehicleMath() = default;

// Real-Time Model get method
BasicVehicleMath::RT_MODEL_BasicVehicleMath_T * BasicVehicleMath::getRTM()
{
  return (&BasicVehicleMath_M);
}

// member function to set up the C-API information
void BasicVehicleMath::setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI,
  const char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  // Initialize Parent model MMI
  if ((rt_ParentMMI != (nullptr)) && (rt_ChildPath != (nullptr))) {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &((&BasicVehicleMath_M)
      ->DataMapInfo.mmi));
    rtwCAPI_SetPath((&BasicVehicleMath_M)->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex((&BasicVehicleMath_M)->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

// member function to setup error status pointer
void BasicVehicleMath::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&BasicVehicleMath_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
