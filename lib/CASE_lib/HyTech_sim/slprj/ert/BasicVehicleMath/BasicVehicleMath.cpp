//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: BasicVehicleMath.cpp
//
// Code generated for Simulink model 'BasicVehicleMath'.
//
// Model version                  : 1.22
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr 26 00:57:44 2024
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
#include "interp1_fDh6ZCtI.h"
#include "BasicVehicleMath_capi.h"
#include "look1_binlxpw.h"
#include "BasicVehicleMath_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

//
// Output and update for action system:
//    '<S22>/Accel. Calc'
//    '<S23>/Accel. Calc'
//    '<S24>/Accel. Calc'
//    '<S25>/Accel. Calc'
//
void BasicVehicleMath::BasicVehicleMath_AccelCalc(real_T rtu_CornerSpeed, real_T
  rtu_WheelOmega1, real_T *rty_SL)
{
  real_T rtb_Switch3;
  real_T tmp;

  // Product: '<S26>/Product' incorporates:
  //   Constant: '<S26>/Constant'

  rtb_Switch3 = rtu_WheelOmega1 * 0.2;

  // Switch: '<S26>/Switch' incorporates:
  //   Constant: '<S26>/Constant1'

  if (rtb_Switch3 != 0.0) {
    tmp = rtb_Switch3;
  } else {
    tmp = (rtInf);
  }

  // Product: '<S26>/Divide' incorporates:
  //   Sum: '<S26>/Subtract'
  //   Switch: '<S26>/Switch'

  rtb_Switch3 = (rtb_Switch3 - rtu_CornerSpeed) / tmp;

  // Switch: '<S26>/Switch3' incorporates:
  //   Constant: '<S26>/Constant3'

  if (!(rtb_Switch3 > 0.0)) {
    rtb_Switch3 = 0.0;
  }

  // End of Switch: '<S26>/Switch3'

  // Switch: '<S26>/Switch1' incorporates:
  //   Constant: '<S26>/Constant2'

  if (rtb_Switch3 > 1.0) {
    *rty_SL = 1.0;
  } else {
    *rty_SL = rtb_Switch3;
  }

  // End of Switch: '<S26>/Switch1'
}

//
// Output and update for action system:
//    '<S22>/Brake Calc'
//    '<S23>/Brake Calc'
//    '<S24>/Brake Calc'
//    '<S25>/Brake Calc'
//
void BasicVehicleMath::BasicVehicleMath_BrakeCalc(real_T rtu_WheelOmega, real_T
  rtu_CornerSpeed, real_T *rty_SL)
{
  real_T rtb_LongitudinalSlipSL;

  // Product: '<S27>/Divide' incorporates:
  //   Constant: '<S27>/Constant'
  //   Product: '<S27>/Product'
  //   Sum: '<S27>/Subtract'

  rtb_LongitudinalSlipSL = (rtu_WheelOmega * 0.2 - rtu_CornerSpeed) /
    rtu_CornerSpeed;

  // Switch: '<S27>/Switch' incorporates:
  //   Abs: '<S27>/Abs'
  //   Constant: '<S27>/Constant1'

  if (std::abs(rtb_LongitudinalSlipSL) > 1.0) {
    rtb_LongitudinalSlipSL = -1.0;
  }

  // Gain: '<S27>/Gain' incorporates:
  //   Abs: '<S27>/Abs1'
  //   Switch: '<S27>/Switch'

  *rty_SL = -std::abs(rtb_LongitudinalSlipSL);
}

// Output and update for referenced model: 'BasicVehicleMath'
void BasicVehicleMath::step(const real_T *rtu_Vx_Bms, const real_T *rtu_Vy_Bms,
  const real_T *rtu_YawRaterads, const real_T *rtu_MotorOmegaFLrpm, const real_T
  *rtu_MotorOmegaFRrpm, const real_T *rtu_MotorOmegaRLrpm, const real_T
  *rtu_MotorOmegaRRrpm, const real_T *rtu_SteeringWheelAngleDeg, const real_T
  *rtu_YawPIDVelThreshold, const real_T *rtu_InitialTorqueRequest, const real_T *
  rtu_TorqueMode, const real_T *rtu_AbsoluteTorqueLimit, const real_T
  *rtu_RegenLimit, real_T *rty_BetaDeg, real_T *rty_AlphaFLDeg, real_T
  *rty_AlphaFRDeg, real_T *rty_AlphaRLDeg, real_T *rty_AlphaRRDeg, real_T
  *rty_LongitudinalCornerVelWFLm, real_T *rty_LongitudinalCornerVelWFRm, real_T *
  rty_LongitudinalCornerVelWRLm, real_T *rty_LongitudinalCornerVelWRRm, real_T
  *rty_KinematicDesiredYawRaterad, real_T *rty_SLFL, real_T *rty_SLFR, real_T
  *rty_SLRL, real_T *rty_SLRR, real_T *rty_WheelSteerAvgDeg, real_T
  *rty_WheelOmegaFLrads, real_T *rty_WheelOmegaFRrads, real_T
  *rty_WheelOmegaRLrads, real_T *rty_WheelOmegaRRrads, real_T
  *rty_ModeConstrainedTorqueReques, real_T *rty_WheelLinearSpeedFLms, real_T
  *rty_WheelLinearSpeedFRms, real_T *rty_WheelLinearSpeedRLms, real_T
  *rty_WheelLinearSpeedRRms)
{
  real_T tmp[2];
  real_T tmp_0[2];
  real_T Alpha_FL;
  real_T Alpha_FR;
  real_T den;
  real_T den_tmp;
  real_T rtb_Abs_l;
  real_T rtb_Abs_tmp;
  real_T rtb_Alpha_RL;
  real_T rtb_Gain1_e_tmp;
  real_T rtb_LongCornerVel_FL_B;
  real_T rtb_LongCornerVel_FR_B;
  real_T rtb_Subtract;
  real_T rtb_Subtract_b;
  real_T rtb_Switch1;
  real_T rtb_Switch1_tmp;
  real_T rtb_Switch_a;
  real_T rtb_Switch_j;

  // Abs: '<Root>/Abs'
  rtb_Abs_l = std::abs(*rtu_SteeringWheelAngleDeg);

  // Lookup_n-D: '<Root>/1-D Lookup Table' incorporates:
  //   Abs: '<S9>/Abs'

  rtb_Abs_l = look1_binlxpw(rtb_Abs_l, rtCP_uDLookupTable_bp01Data,
    rtCP_uDLookupTable_tableData, 200U);

  // Gain: '<Root>/Gain'
  rtb_Switch_j = 0.10471975511965977 * *rtu_MotorOmegaRRrpm;

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant'

  if (!(rtb_Switch_j > 50.0)) {
    rtb_Switch_j = 0.0;
  }

  // End of Switch: '<S1>/Switch'

  // Abs: '<S2>/Abs' incorporates:
  //   MATLAB Function: '<S15>/MATLAB Function'

  rtb_Switch1_tmp = std::abs(*rtu_Vy_Bms);

  // Sum: '<S2>/Subtract' incorporates:
  //   Abs: '<S2>/Abs'

  rtb_Subtract = rtb_Switch1_tmp - *rtu_YawPIDVelThreshold;

  // Switch: '<S2>/Switch1' incorporates:
  //   Constant: '<S2>/Constant'
  //   Trigonometry: '<S2>/Atan'

  if (rtb_Subtract > 0.0) {
    // Abs: '<S2>/Abs1'
    rtb_Subtract = std::abs(*rtu_Vx_Bms);

    // Switch: '<S2>/Switch' incorporates:
    //   Constant: '<S2>/Constant2'

    if (rtb_Subtract > 0.0) {
      rtb_Subtract = *rtu_Vx_Bms;
    } else {
      rtb_Subtract = (rtInf);
    }

    // End of Switch: '<S2>/Switch'

    // Product: '<S2>/Divide2'
    rtb_Subtract = *rtu_Vy_Bms / rtb_Subtract;
    rtb_Switch1 = std::atan(rtb_Subtract);
  } else {
    rtb_Switch1 = 0.0;
  }

  // End of Switch: '<S2>/Switch1'

  // Signum: '<Root>/Sign'
  rtb_Subtract = *rtu_SteeringWheelAngleDeg;
  if (std::isnan(rtb_Subtract)) {
    rtb_Gain1_e_tmp = (rtNaN);
  } else if (rtb_Subtract < 0.0) {
    rtb_Gain1_e_tmp = -1.0;
  } else {
    rtb_Gain1_e_tmp = (rtb_Subtract > 0.0);
  }

  // Product: '<Root>/Product' incorporates:
  //   Signum: '<Root>/Sign'

  *rty_WheelSteerAvgDeg = rtb_Abs_l * rtb_Gain1_e_tmp;

  // Gain: '<S3>/Gain1' incorporates:
  //   Gain: '<S4>/Gain1'
  //   Gain: '<S5>/Gain1'
  //   Gain: '<S6>/Gain1'
  //   Gain: '<S7>/Gain1'
  //   Switch: '<S8>/Switch'

  rtb_Gain1_e_tmp = 0.017453292519943295 * *rty_WheelSteerAvgDeg;

  // Gain: '<Root>/Gain1'
  rtb_Subtract = 0.10471975511965977 * *rtu_MotorOmegaRLrpm;

  // Gain: '<Root>/Gain2'
  rtb_Switch_a = 0.10471975511965977 * *rtu_MotorOmegaFRrpm;

  // Gain: '<Root>/Gain3'
  rtb_Abs_l = 0.10471975511965977 * *rtu_MotorOmegaFLrpm;

  // Abs: '<S8>/Abs' incorporates:
  //   MATLAB Function: '<S15>/MATLAB Function'

  rtb_Abs_tmp = std::abs(*rtu_Vx_Bms);

  // Sum: '<S8>/Subtract' incorporates:
  //   Abs: '<S8>/Abs'

  rtb_Subtract_b = rtb_Abs_tmp - *rtu_YawPIDVelThreshold;

  // Switch: '<S8>/Switch' incorporates:
  //   Abs: '<S8>/Abs'
  //   Constant: '<S8>/Constant'
  //   Constant: '<S8>/wb'
  //   Product: '<S8>/Divide'
  //   Trigonometry: '<S8>/Tan'

  if (rtb_Subtract_b > 0.0) {
    *rty_KinematicDesiredYawRaterad = rtb_Abs_tmp * std::tan(rtb_Gain1_e_tmp) /
      1.535;
  } else {
    *rty_KinematicDesiredYawRaterad = 0.0;
  }

  // MATLAB Function: '<S15>/MATLAB Function' incorporates:
  //   Constant: '<S15>/Constant'
  //   Constant: '<S15>/Constant2'
  //   Constant: '<S15>/Constant3'
  //   Constant: '<S15>/Constant4'
  //   Constant: '<S15>/Constant6'
  //   Constant: '<S15>/Constant7'
  //   Gain: '<S3>/Gain1'

  den_tmp = *rtu_YawRaterads * 0.96437803790837118 * 0.62216265449318331;
  den = den_tmp + *rtu_Vx_Bms;
  rtb_Subtract_b = *rtu_YawRaterads * 0.96437803790837118 * 0.78288800690392224
    + *rtu_Vy_Bms;
  Alpha_FL = -(rtb_Gain1_e_tmp - rt_atan2d_snf(rtb_Subtract_b, den));
  if (std::isnan(Alpha_FL)) {
    if (rtb_Gain1_e_tmp != 0.0) {
      Alpha_FL = -rtb_Gain1_e_tmp;
    } else {
      Alpha_FL = 0.0;
    }
  }

  rtb_LongCornerVel_FL_B = den;
  den = *rtu_Vx_Bms - den_tmp;
  Alpha_FR = -(rtb_Gain1_e_tmp - rt_atan2d_snf(rtb_Subtract_b, den));
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
  rtb_Subtract_b = rt_atan2d_snf(*rtu_Vy_Bms - *rtu_YawRaterads *
    0.98407316801140354 * 0.79262398910460008, den);
  rtb_Alpha_RL = rtb_Subtract_b;
  if (std::isnan(rtb_Subtract_b)) {
    rtb_Alpha_RL = 0.0;
  }

  *rty_LongitudinalCornerVelWRLm = den;
  den = *rtu_Vx_Bms - den_tmp;
  rtb_Subtract_b = rt_atan2d_snf(*rtu_Vy_Bms - *rtu_YawRaterads *
    0.98407316801140354 * 0.79262398910460019, den);
  if (std::isnan(rtb_Subtract_b)) {
    rtb_Subtract_b = 0.0;
  }

  *rty_LongitudinalCornerVelWRRm = den;
  if ((rtb_Abs_tmp < *rtu_YawPIDVelThreshold) || (rtb_Switch1_tmp < 0.25)) {
    Alpha_FL = 0.0;
    Alpha_FR = 0.0;
    rtb_Alpha_RL = 0.0;
    rtb_Subtract_b = 0.0;
  }

  if (rtb_Abs_tmp < 1.0) {
    rtb_LongCornerVel_FL_B = 0.0;
    rtb_LongCornerVel_FR_B = 0.0;
    *rty_LongitudinalCornerVelWRLm = 0.0;
    *rty_LongitudinalCornerVelWRRm = 0.0;
  }

  // Trigonometry: '<S9>/Cos' incorporates:
  //   Abs: '<S9>/Abs'
  //   Trigonometry: '<S9>/Cos1'

  rtb_Gain1_e_tmp = std::cos(std::abs(rtb_Gain1_e_tmp));

  // Product: '<S9>/Product' incorporates:
  //   Trigonometry: '<S9>/Cos'

  *rty_LongitudinalCornerVelWFLm = rtb_LongCornerVel_FL_B * rtb_Gain1_e_tmp;

  // Product: '<S9>/Product1'
  *rty_LongitudinalCornerVelWFRm = rtb_LongCornerVel_FR_B * rtb_Gain1_e_tmp;

  // Gain: '<S10>/Gain' incorporates:
  //   MATLAB Function: '<S15>/MATLAB Function'

  *rty_AlphaFLDeg = 57.295779513082323 * Alpha_FL;

  // Gain: '<S11>/Gain' incorporates:
  //   MATLAB Function: '<S15>/MATLAB Function'

  *rty_AlphaFRDeg = 57.295779513082323 * Alpha_FR;

  // Gain: '<S12>/Gain'
  *rty_AlphaRLDeg = 57.295779513082323 * rtb_Alpha_RL;

  // Gain: '<S13>/Gain'
  *rty_AlphaRRDeg = 57.295779513082323 * rtb_Subtract_b;

  // Gain: '<S14>/Gain'
  *rty_BetaDeg = 57.295779513082323 * rtb_Switch1;

  // Switch: '<S17>/Switch' incorporates:
  //   Constant: '<S17>/Constant'

  if (!(rtb_Abs_l > 50.0)) {
    rtb_Abs_l = 0.0;
  }

  // End of Switch: '<S17>/Switch'

  // Gain: '<S16>/Gain'
  *rty_WheelOmegaFLrads = 0.084317032040472181 * rtb_Abs_l;

  // Gain: '<S16>/Gain4'
  *rty_WheelLinearSpeedFLms = 0.2 * *rty_WheelOmegaFLrads;

  // Product: '<S22>/Product1' incorporates:
  //   Constant: '<S22>/Constant2'

  rtb_Abs_l = *rty_WheelOmegaFLrads * 0.2;

  // Sum: '<S22>/Subtract1'
  rtb_Abs_l -= *rty_LongitudinalCornerVelWFLm;

  // If: '<S22>/If2'
  if (rtb_Abs_l > 0.0) {
    // Outputs for IfAction SubSystem: '<S22>/Accel. Calc' incorporates:
    //   ActionPort: '<S26>/Action Port'

    BasicVehicleMath_AccelCalc(*rty_LongitudinalCornerVelWFLm,
      *rty_WheelOmegaFLrads, &rtb_Abs_l);

    // End of Outputs for SubSystem: '<S22>/Accel. Calc'
  } else if (rtb_Abs_l < 0.0) {
    // Outputs for IfAction SubSystem: '<S22>/Brake Calc' incorporates:
    //   ActionPort: '<S27>/Action Port'

    BasicVehicleMath_BrakeCalc(*rty_WheelOmegaFLrads,
      *rty_LongitudinalCornerVelWFLm, &rtb_Abs_l);

    // End of Outputs for SubSystem: '<S22>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S22>/If Action Subsystem' incorporates:
    //   ActionPort: '<S28>/Action Port'

    // SignalConversion generated from: '<S28>/in' incorporates:
    //   Constant: '<S22>/Constant1'

    rtb_Abs_l = 0.0;

    // End of Outputs for SubSystem: '<S22>/If Action Subsystem'
  }

  // End of If: '<S22>/If2'

  // Switch: '<S16>/Switch'
  *rty_SLFL = rtb_Abs_l;

  // Switch: '<S18>/Switch' incorporates:
  //   Constant: '<S18>/Constant'

  if (!(rtb_Switch_a > 50.0)) {
    rtb_Switch_a = 0.0;
  }

  // Gain: '<S16>/Gain1' incorporates:
  //   Switch: '<S18>/Switch'

  *rty_WheelOmegaFRrads = 0.084317032040472181 * rtb_Switch_a;

  // Gain: '<S16>/Gain5'
  *rty_WheelLinearSpeedFRms = 0.2 * *rty_WheelOmegaFRrads;

  // Product: '<S23>/Product1' incorporates:
  //   Constant: '<S23>/Constant2'

  rtb_Abs_l = *rty_WheelOmegaFRrads * 0.2;

  // Sum: '<S23>/Subtract1'
  rtb_Abs_l -= *rty_LongitudinalCornerVelWFRm;

  // If: '<S23>/If2'
  if (rtb_Abs_l > 0.0) {
    // Outputs for IfAction SubSystem: '<S23>/Accel. Calc' incorporates:
    //   ActionPort: '<S29>/Action Port'

    BasicVehicleMath_AccelCalc(*rty_LongitudinalCornerVelWFRm,
      *rty_WheelOmegaFRrads, &rtb_Abs_l);

    // End of Outputs for SubSystem: '<S23>/Accel. Calc'
  } else if (rtb_Abs_l < 0.0) {
    // Outputs for IfAction SubSystem: '<S23>/Brake Calc' incorporates:
    //   ActionPort: '<S30>/Action Port'

    BasicVehicleMath_BrakeCalc(*rty_WheelOmegaFRrads,
      *rty_LongitudinalCornerVelWFRm, &rtb_Abs_l);

    // End of Outputs for SubSystem: '<S23>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S23>/If Action Subsystem' incorporates:
    //   ActionPort: '<S31>/Action Port'

    // SignalConversion generated from: '<S31>/in' incorporates:
    //   Constant: '<S23>/Constant1'

    rtb_Abs_l = 0.0;

    // End of Outputs for SubSystem: '<S23>/If Action Subsystem'
  }

  // End of If: '<S23>/If2'

  // Switch: '<S16>/Switch1'
  *rty_SLFR = rtb_Abs_l;

  // Switch: '<S19>/Switch' incorporates:
  //   Constant: '<S19>/Constant'

  if (!(rtb_Subtract > 50.0)) {
    rtb_Subtract = 0.0;
  }

  // Gain: '<S16>/Gain2' incorporates:
  //   Switch: '<S19>/Switch'

  *rty_WheelOmegaRLrads = 0.084317032040472181 * rtb_Subtract;

  // Gain: '<S16>/Gain6'
  *rty_WheelLinearSpeedRLms = 0.2 * *rty_WheelOmegaRLrads;

  // Product: '<S24>/Product1' incorporates:
  //   Constant: '<S24>/Constant2'

  rtb_Abs_l = *rty_WheelOmegaRLrads * 0.2;

  // Sum: '<S24>/Subtract1'
  rtb_Abs_l -= *rty_LongitudinalCornerVelWRLm;

  // If: '<S24>/If2'
  if (rtb_Abs_l > 0.0) {
    // Outputs for IfAction SubSystem: '<S24>/Accel. Calc' incorporates:
    //   ActionPort: '<S32>/Action Port'

    BasicVehicleMath_AccelCalc(*rty_LongitudinalCornerVelWRLm,
      *rty_WheelOmegaRLrads, &rtb_Abs_l);

    // End of Outputs for SubSystem: '<S24>/Accel. Calc'
  } else if (rtb_Abs_l < 0.0) {
    // Outputs for IfAction SubSystem: '<S24>/Brake Calc' incorporates:
    //   ActionPort: '<S33>/Action Port'

    BasicVehicleMath_BrakeCalc(*rty_WheelOmegaRLrads,
      *rty_LongitudinalCornerVelWRLm, &rtb_Abs_l);

    // End of Outputs for SubSystem: '<S24>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S24>/If Action Subsystem' incorporates:
    //   ActionPort: '<S34>/Action Port'

    // SignalConversion generated from: '<S34>/in' incorporates:
    //   Constant: '<S24>/Constant1'

    rtb_Abs_l = 0.0;

    // End of Outputs for SubSystem: '<S24>/If Action Subsystem'
  }

  // End of If: '<S24>/If2'

  // Switch: '<S16>/Switch2'
  *rty_SLRL = rtb_Abs_l;

  // Gain: '<S16>/Gain3'
  *rty_WheelOmegaRRrads = 0.084317032040472181 * rtb_Switch_j;

  // Gain: '<S16>/Gain7'
  *rty_WheelLinearSpeedRRms = 0.2 * *rty_WheelOmegaRRrads;

  // Product: '<S25>/Product1' incorporates:
  //   Constant: '<S25>/Constant2'

  rtb_Switch_j = *rty_WheelOmegaRRrads * 0.2;

  // Sum: '<S25>/Subtract1'
  rtb_Switch_j -= *rty_LongitudinalCornerVelWRRm;

  // If: '<S25>/If2'
  if (rtb_Switch_j > 0.0) {
    // Outputs for IfAction SubSystem: '<S25>/Accel. Calc' incorporates:
    //   ActionPort: '<S35>/Action Port'

    BasicVehicleMath_AccelCalc(*rty_LongitudinalCornerVelWRRm,
      *rty_WheelOmegaRRrads, &rtb_Abs_l);

    // End of Outputs for SubSystem: '<S25>/Accel. Calc'
  } else if (rtb_Switch_j < 0.0) {
    // Outputs for IfAction SubSystem: '<S25>/Brake Calc' incorporates:
    //   ActionPort: '<S36>/Action Port'

    BasicVehicleMath_BrakeCalc(*rty_WheelOmegaRRrads,
      *rty_LongitudinalCornerVelWRRm, &rtb_Abs_l);

    // End of Outputs for SubSystem: '<S25>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S25>/If Action Subsystem' incorporates:
    //   ActionPort: '<S37>/Action Port'

    // SignalConversion generated from: '<S37>/in' incorporates:
    //   Constant: '<S25>/Constant1'

    rtb_Abs_l = 0.0;

    // End of Outputs for SubSystem: '<S25>/If Action Subsystem'
  }

  // End of If: '<S25>/If2'

  // Switch: '<S16>/Switch3'
  *rty_SLRR = rtb_Abs_l;

  // MATLAB Function: '<S20>/MATLAB Function'
  if (*rtu_InitialTorqueRequest > 0.0) {
    tmp[0] = 0.0;
    tmp[1] = *rtu_AbsoluteTorqueLimit;
    tmp_0[0] = 0.0;
    tmp_0[1] = *rtu_TorqueMode;
    *rty_ModeConstrainedTorqueReques = interp1_fDh6ZCtI(tmp, tmp_0,
      *rtu_InitialTorqueRequest);
  } else if (*rtu_InitialTorqueRequest < 0.0) {
    tmp[0] = 0.0;
    tmp[1] = -*rtu_AbsoluteTorqueLimit;
    tmp_0[0] = 0.0;
    tmp_0[1] = *rtu_RegenLimit;
    *rty_ModeConstrainedTorqueReques = interp1_fDh6ZCtI(tmp, tmp_0,
      *rtu_InitialTorqueRequest);
  } else {
    *rty_ModeConstrainedTorqueReques = 0.0;
  }

  // End of MATLAB Function: '<S20>/MATLAB Function'
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
