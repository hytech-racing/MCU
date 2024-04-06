//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: BasicVehicleMath.cpp
//
// Code generated for Simulink model 'BasicVehicleMath'.
//
// Model version                  : 1.2
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr  5 20:57:25 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "BasicVehicleMath.h"
#include "rtwtypes.h"
#include <cmath>
#include "BasicVehicleMath_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "rt_defines.h"

//
// Output and update for action system:
//    '<S7>/Accel. Calc'
//    '<S8>/Accel. Calc'
//    '<S9>/Accel. Calc'
//    '<S10>/Accel. Calc'
//
void BasicVehicleMath::BasicVehicleMath_AccelCalc(real_T rtu_CornerSpeed, real_T
  rtu_WheelOmega1, real_T *rty_SL)
{
  real_T rtb_Switch3;
  real_T tmp;

  // Product: '<S11>/Product' incorporates:
  //   Constant: '<S11>/Constant'

  rtb_Switch3 = rtu_WheelOmega1 * 0.2;

  // Switch: '<S11>/Switch' incorporates:
  //   Constant: '<S11>/Constant1'

  if (rtb_Switch3 != 0.0) {
    tmp = rtb_Switch3;
  } else {
    tmp = (rtInf);
  }

  // Product: '<S11>/Divide' incorporates:
  //   Sum: '<S11>/Subtract'
  //   Switch: '<S11>/Switch'

  rtb_Switch3 = (rtb_Switch3 - rtu_CornerSpeed) / tmp;

  // Switch: '<S11>/Switch3' incorporates:
  //   Constant: '<S11>/Constant3'

  if (!(rtb_Switch3 > 0.0)) {
    rtb_Switch3 = 0.0;
  }

  // End of Switch: '<S11>/Switch3'

  // Switch: '<S11>/Switch1' incorporates:
  //   Constant: '<S11>/Constant2'

  if (rtb_Switch3 > 1.0) {
    *rty_SL = 1.0;
  } else {
    *rty_SL = rtb_Switch3;
  }

  // End of Switch: '<S11>/Switch1'
}

//
// Output and update for action system:
//    '<S7>/Brake Calc'
//    '<S8>/Brake Calc'
//    '<S9>/Brake Calc'
//    '<S10>/Brake Calc'
//
void BasicVehicleMath::BasicVehicleMath_BrakeCalc(real_T rtu_WheelOmega, real_T
  rtu_CornerSpeed, real_T *rty_SL)
{
  real_T rtb_LongitudinalSlipSL;

  // Product: '<S12>/Divide' incorporates:
  //   Constant: '<S12>/Constant'
  //   Product: '<S12>/Product'
  //   Sum: '<S12>/Subtract'

  rtb_LongitudinalSlipSL = (rtu_WheelOmega * 0.2 - rtu_CornerSpeed) /
    rtu_CornerSpeed;

  // Switch: '<S12>/Switch' incorporates:
  //   Abs: '<S12>/Abs'
  //   Constant: '<S12>/Constant1'

  if (std::abs(rtb_LongitudinalSlipSL) > 1.0) {
    rtb_LongitudinalSlipSL = -1.0;
  }

  // Gain: '<S12>/Gain' incorporates:
  //   Abs: '<S12>/Abs1'
  //   Switch: '<S12>/Switch'

  *rty_SL = -std::abs(rtb_LongitudinalSlipSL);
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = std::atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

// Model step function
void BasicVehicleMath::step()
{
  real_T rtb_LongCornerVel_FL_B;
  real_T rtb_LongCornerVel_FR_B;
  real_T rtb_Subtract1;

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant2'
  //   Inport: '<Root>/Vx_B [m//s]'

  if (BasicVehicleMath_U.Vx_Bms > 0.0) {
    rtb_Subtract1 = BasicVehicleMath_U.Vx_Bms;
  } else {
    rtb_Subtract1 = (rtInf);
  }

  // Outport: '<Root>/Beta [rad]' incorporates:
  //   Inport: '<Root>/Vy_B [m//s]'
  //   Product: '<S1>/Divide2'
  //   Switch: '<S1>/Switch'
  //   Trigonometry: '<S1>/Atan'

  BasicVehicleMath_Y.Betarad = std::atan(BasicVehicleMath_U.Vy_Bms /
    rtb_Subtract1);

  // MATLAB Function: '<S4>/MATLAB Function' incorporates:
  //   Constant: '<S4>/Constant'
  //   Constant: '<S4>/Constant2'
  //   Constant: '<S4>/Constant4'
  //   Constant: '<S4>/Constant6'
  //   Inport: '<Root>/Delta Left [rad]'
  //   Inport: '<Root>/Delta Right [rad]'
  //   Inport: '<Root>/Vx_B [m//s]'
  //   Inport: '<Root>/Vy_B [m//s]'
  //   Inport: '<Root>/Yaw Rate [rad//s]'

  rtb_Subtract1 = BasicVehicleMath_U.YawRaterads * 0.96437803790837118 *
    0.62216265449318331;
  BasicVehicleMath_Y.LongitudinalCornerVelWRRms = rtb_Subtract1 +
    BasicVehicleMath_U.Vx_Bms;
  rtb_LongCornerVel_FR_B = BasicVehicleMath_U.YawRaterads * 0.96437803790837118 *
    0.78288800690392224 + BasicVehicleMath_U.Vy_Bms;
  BasicVehicleMath_Y.AlphaFLrad = -(BasicVehicleMath_U.DeltaLeftrad -
    rt_atan2d_snf(rtb_LongCornerVel_FR_B,
                  BasicVehicleMath_Y.LongitudinalCornerVelWRRms));
  if (std::isnan(BasicVehicleMath_Y.AlphaFLrad)) {
    if (BasicVehicleMath_U.DeltaLeftrad != 0.0) {
      BasicVehicleMath_Y.AlphaFLrad = -BasicVehicleMath_U.DeltaLeftrad;
    } else {
      BasicVehicleMath_Y.AlphaFLrad = 0.0;
    }
  }

  rtb_LongCornerVel_FL_B = BasicVehicleMath_Y.LongitudinalCornerVelWRRms;
  BasicVehicleMath_Y.LongitudinalCornerVelWRRms = BasicVehicleMath_U.Vx_Bms -
    rtb_Subtract1;
  BasicVehicleMath_Y.AlphaFRrad = -(BasicVehicleMath_U.DeltaRightrad -
    rt_atan2d_snf(rtb_LongCornerVel_FR_B,
                  BasicVehicleMath_Y.LongitudinalCornerVelWRRms));
  if (std::isnan(BasicVehicleMath_Y.AlphaFRrad)) {
    if (BasicVehicleMath_U.DeltaRightrad != 0.0) {
      BasicVehicleMath_Y.AlphaFRrad = -BasicVehicleMath_U.DeltaRightrad;
    } else {
      BasicVehicleMath_Y.AlphaFRrad = 0.0;
    }
  }

  rtb_LongCornerVel_FR_B = BasicVehicleMath_Y.LongitudinalCornerVelWRRms;
  rtb_Subtract1 = BasicVehicleMath_U.YawRaterads * 0.98407316801140354 *
    0.60971076084969233;
  BasicVehicleMath_Y.LongitudinalCornerVelWRRms = rtb_Subtract1 +
    BasicVehicleMath_U.Vx_Bms;
  BasicVehicleMath_Y.AlphaRRrad = rt_atan2d_snf(BasicVehicleMath_U.Vy_Bms -
    BasicVehicleMath_U.YawRaterads * 0.98407316801140354 * 0.79262398910460008,
    BasicVehicleMath_Y.LongitudinalCornerVelWRRms);

  // Outport: '<Root>/Alpha RL [rad]' incorporates:
  //   MATLAB Function: '<S4>/MATLAB Function'

  BasicVehicleMath_Y.AlphaRLrad = BasicVehicleMath_Y.AlphaRRrad;

  // MATLAB Function: '<S4>/MATLAB Function' incorporates:
  //   Constant: '<S4>/Constant3'
  //   Constant: '<S4>/Constant7'
  //   Inport: '<Root>/Vx_B [m//s]'
  //   Inport: '<Root>/Vy_B [m//s]'
  //   Inport: '<Root>/Yaw Rate [rad//s]'

  if (std::isnan(BasicVehicleMath_Y.AlphaRRrad)) {
    // Outport: '<Root>/Alpha RL [rad]'
    BasicVehicleMath_Y.AlphaRLrad = 0.0;
  }

  BasicVehicleMath_Y.LongitudinalCornerVelWRLms =
    BasicVehicleMath_Y.LongitudinalCornerVelWRRms;
  BasicVehicleMath_Y.LongitudinalCornerVelWRRms = BasicVehicleMath_U.Vx_Bms -
    rtb_Subtract1;
  BasicVehicleMath_Y.AlphaRRrad = rt_atan2d_snf(BasicVehicleMath_U.Vy_Bms -
    BasicVehicleMath_U.YawRaterads * 0.98407316801140354 * 0.79262398910460019,
    BasicVehicleMath_Y.LongitudinalCornerVelWRRms);
  if (std::isnan(BasicVehicleMath_Y.AlphaRRrad)) {
    // Outport: '<Root>/Alpha RR [rad]'
    BasicVehicleMath_Y.AlphaRRrad = 0.0;
  }

  // Product: '<S3>/Product' incorporates:
  //   Abs: '<S3>/Abs'
  //   Inport: '<Root>/Delta Left [rad]'
  //   Trigonometry: '<S3>/Cos'

  BasicVehicleMath_Y.LongitudinalCornerVelWFLms = rtb_LongCornerVel_FL_B * std::
    cos(std::abs(BasicVehicleMath_U.DeltaLeftrad));

  // Product: '<S3>/Product1' incorporates:
  //   Abs: '<S3>/Abs1'
  //   Inport: '<Root>/Delta Right [rad]'
  //   Trigonometry: '<S3>/Cos1'

  BasicVehicleMath_Y.LongitudinalCornerVelWFRms = rtb_LongCornerVel_FR_B * std::
    cos(std::abs(BasicVehicleMath_U.DeltaRightrad));

  // Merge: '<S10>/Merge' incorporates:
  //   Abs: '<S2>/Abs'
  //   Inport: '<Root>/Vx_B [m//s]'

  BasicVehicleMath_Y.SLRR = std::abs(BasicVehicleMath_U.Vx_Bms);

  // Outport: '<Root>/Kinematic Desired Yaw Rate [rad//s]' incorporates:
  //   Constant: '<S2>/wb'
  //   Inport: '<Root>/Delta Avg [rad]'
  //   Product: '<S2>/Divide'
  //   Trigonometry: '<S2>/Tan'

  BasicVehicleMath_Y.KinematicDesiredYawRaterads = BasicVehicleMath_Y.SLRR * std::
    tan(BasicVehicleMath_U.DeltaAvgrad) / 1.535;

  // Sum: '<S7>/Subtract1' incorporates:
  //   Constant: '<S7>/Constant2'
  //   Inport: '<Root>/Wheel Omega FL [rad//s]'
  //   Product: '<S7>/Product1'

  rtb_Subtract1 = BasicVehicleMath_U.WheelOmegaFLrads * 0.2 -
    BasicVehicleMath_Y.LongitudinalCornerVelWFLms;

  // If: '<S7>/If2' incorporates:
  //   Inport: '<Root>/Wheel Omega FL [rad//s]'

  if (rtb_Subtract1 > 0.0) {
    // Outputs for IfAction SubSystem: '<S7>/Accel. Calc' incorporates:
    //   ActionPort: '<S11>/Action Port'

    BasicVehicleMath_AccelCalc(BasicVehicleMath_Y.LongitudinalCornerVelWFLms,
      BasicVehicleMath_U.WheelOmegaFLrads, &BasicVehicleMath_Y.SLRR);

    // End of Outputs for SubSystem: '<S7>/Accel. Calc'
  } else if (rtb_Subtract1 < 0.0) {
    // Outputs for IfAction SubSystem: '<S7>/Brake Calc' incorporates:
    //   ActionPort: '<S12>/Action Port'

    BasicVehicleMath_BrakeCalc(BasicVehicleMath_U.WheelOmegaFLrads,
      BasicVehicleMath_Y.LongitudinalCornerVelWFLms, &BasicVehicleMath_Y.SLRR);

    // End of Outputs for SubSystem: '<S7>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S7>/If Action Subsystem' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // Merge: '<S10>/Merge' incorporates:
    //   Constant: '<S7>/Constant1'
    //   SignalConversion generated from: '<S13>/in'

    BasicVehicleMath_Y.SLRR = 0.0;

    // End of Outputs for SubSystem: '<S7>/If Action Subsystem'
  }

  // End of If: '<S7>/If2'

  // Outport: '<Root>/SL FL' incorporates:
  //   Switch: '<S5>/Switch'

  BasicVehicleMath_Y.SLFL = BasicVehicleMath_Y.SLRR;

  // Sum: '<S8>/Subtract1' incorporates:
  //   Constant: '<S8>/Constant2'
  //   Inport: '<Root>/Wheel Omega FR [rad//s]'
  //   Product: '<S8>/Product1'

  rtb_Subtract1 = BasicVehicleMath_U.WheelOmegaFRrads * 0.2 -
    BasicVehicleMath_Y.LongitudinalCornerVelWFRms;

  // If: '<S8>/If2' incorporates:
  //   Inport: '<Root>/Wheel Omega FR [rad//s]'

  if (rtb_Subtract1 > 0.0) {
    // Outputs for IfAction SubSystem: '<S8>/Accel. Calc' incorporates:
    //   ActionPort: '<S14>/Action Port'

    BasicVehicleMath_AccelCalc(BasicVehicleMath_Y.LongitudinalCornerVelWFRms,
      BasicVehicleMath_U.WheelOmegaFRrads, &BasicVehicleMath_Y.SLRR);

    // End of Outputs for SubSystem: '<S8>/Accel. Calc'
  } else if (rtb_Subtract1 < 0.0) {
    // Outputs for IfAction SubSystem: '<S8>/Brake Calc' incorporates:
    //   ActionPort: '<S15>/Action Port'

    BasicVehicleMath_BrakeCalc(BasicVehicleMath_U.WheelOmegaFRrads,
      BasicVehicleMath_Y.LongitudinalCornerVelWFRms, &BasicVehicleMath_Y.SLRR);

    // End of Outputs for SubSystem: '<S8>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S8>/If Action Subsystem' incorporates:
    //   ActionPort: '<S16>/Action Port'

    // Merge: '<S10>/Merge' incorporates:
    //   Constant: '<S8>/Constant1'
    //   SignalConversion generated from: '<S16>/in'

    BasicVehicleMath_Y.SLRR = 0.0;

    // End of Outputs for SubSystem: '<S8>/If Action Subsystem'
  }

  // End of If: '<S8>/If2'

  // Outport: '<Root>/SL FR' incorporates:
  //   Switch: '<S5>/Switch1'

  BasicVehicleMath_Y.SLFR = BasicVehicleMath_Y.SLRR;

  // Sum: '<S9>/Subtract1' incorporates:
  //   Constant: '<S9>/Constant2'
  //   Inport: '<Root>/Wheel Omega RL [rad//s]'
  //   Product: '<S9>/Product1'

  rtb_Subtract1 = BasicVehicleMath_U.WheelOmegaRLrads * 0.2 -
    BasicVehicleMath_Y.LongitudinalCornerVelWRLms;

  // If: '<S9>/If2' incorporates:
  //   Inport: '<Root>/Wheel Omega RL [rad//s]'

  if (rtb_Subtract1 > 0.0) {
    // Outputs for IfAction SubSystem: '<S9>/Accel. Calc' incorporates:
    //   ActionPort: '<S17>/Action Port'

    BasicVehicleMath_AccelCalc(BasicVehicleMath_Y.LongitudinalCornerVelWRLms,
      BasicVehicleMath_U.WheelOmegaRLrads, &BasicVehicleMath_Y.SLRR);

    // End of Outputs for SubSystem: '<S9>/Accel. Calc'
  } else if (rtb_Subtract1 < 0.0) {
    // Outputs for IfAction SubSystem: '<S9>/Brake Calc' incorporates:
    //   ActionPort: '<S18>/Action Port'

    BasicVehicleMath_BrakeCalc(BasicVehicleMath_U.WheelOmegaRLrads,
      BasicVehicleMath_Y.LongitudinalCornerVelWRLms, &BasicVehicleMath_Y.SLRR);

    // End of Outputs for SubSystem: '<S9>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S9>/If Action Subsystem' incorporates:
    //   ActionPort: '<S19>/Action Port'

    // Merge: '<S10>/Merge' incorporates:
    //   Constant: '<S9>/Constant1'
    //   SignalConversion generated from: '<S19>/in'

    BasicVehicleMath_Y.SLRR = 0.0;

    // End of Outputs for SubSystem: '<S9>/If Action Subsystem'
  }

  // End of If: '<S9>/If2'

  // Outport: '<Root>/SL RL' incorporates:
  //   Switch: '<S5>/Switch2'

  BasicVehicleMath_Y.SLRL = BasicVehicleMath_Y.SLRR;

  // Sum: '<S10>/Subtract1' incorporates:
  //   Constant: '<S10>/Constant2'
  //   Inport: '<Root>/Wheel Omega RR [rad//s]'
  //   MATLAB Function: '<S4>/MATLAB Function'
  //   Product: '<S10>/Product1'

  rtb_Subtract1 = BasicVehicleMath_U.WheelOmegaRRrads * 0.2 -
    BasicVehicleMath_Y.LongitudinalCornerVelWRRms;

  // If: '<S10>/If2' incorporates:
  //   Inport: '<Root>/Wheel Omega RR [rad//s]'
  //   MATLAB Function: '<S4>/MATLAB Function'

  if (rtb_Subtract1 > 0.0) {
    // Outputs for IfAction SubSystem: '<S10>/Accel. Calc' incorporates:
    //   ActionPort: '<S20>/Action Port'

    BasicVehicleMath_AccelCalc(BasicVehicleMath_Y.LongitudinalCornerVelWRRms,
      BasicVehicleMath_U.WheelOmegaRRrads, &BasicVehicleMath_Y.SLRR);

    // End of Outputs for SubSystem: '<S10>/Accel. Calc'
  } else if (rtb_Subtract1 < 0.0) {
    // Outputs for IfAction SubSystem: '<S10>/Brake Calc' incorporates:
    //   ActionPort: '<S21>/Action Port'

    BasicVehicleMath_BrakeCalc(BasicVehicleMath_U.WheelOmegaRRrads,
      BasicVehicleMath_Y.LongitudinalCornerVelWRRms, &BasicVehicleMath_Y.SLRR);

    // End of Outputs for SubSystem: '<S10>/Brake Calc'
  } else {
    // Outputs for IfAction SubSystem: '<S10>/If Action Subsystem' incorporates:
    //   ActionPort: '<S22>/Action Port'

    // Merge: '<S10>/Merge' incorporates:
    //   Constant: '<S10>/Constant1'
    //   SignalConversion generated from: '<S22>/in'

    BasicVehicleMath_Y.SLRR = 0.0;

    // End of Outputs for SubSystem: '<S10>/If Action Subsystem'
  }

  // End of If: '<S10>/If2'
}

// Model initialize function
void BasicVehicleMath::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

// Model terminate function
void BasicVehicleMath::terminate()
{
  // (no terminate code required)
}

// Constructor
BasicVehicleMath::BasicVehicleMath() :
  BasicVehicleMath_U(),
  BasicVehicleMath_Y(),
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

//
// File trailer for generated code.
//
// [EOF]
//
