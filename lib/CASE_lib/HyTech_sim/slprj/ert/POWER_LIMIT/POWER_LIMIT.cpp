//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: POWER_LIMIT.cpp
//
// Code generated for Simulink model 'POWER_LIMIT'.
//
// Model version                  : 1.45
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr 26 01:31:06 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "POWER_LIMIT.h"
#include "rtwtypes.h"
#include <cmath>
#include "POWER_LIMIT_capi.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "POWER_LIMIT_private.h"

//
// Output and update for atomic system:
//    '<S5>/MATLAB Function'
//    '<S2>/MATLAB Function'
//
void POWER_LIMIT::POWER_LIMIT_MATLABFunction(real_T rtu_Torque_FL, real_T
  rtu_Torque_FR, real_T rtu_Torque_RL, real_T rtu_Torque_RR, real_T
  rtu_Motor_Omega_FL, real_T rtu_Motor_Omega_FR, real_T rtu_Motor_Omega_RL,
  real_T rtu_Motor_Omega_RR, real_T *rty_cornerPower_FL, real_T
  *rty_cornerPower_FR, real_T *rty_cornerPower_RL, real_T *rty_cornerPower_RR)
{
  real_T powerPerCorner_kW_idx_0;
  real_T powerPerCorner_kW_idx_1;
  real_T powerPerCorner_kW_idx_2;
  real_T powerPerCorner_kW_idx_3;
  powerPerCorner_kW_idx_0 = rtu_Motor_Omega_FL;
  powerPerCorner_kW_idx_1 = rtu_Motor_Omega_FR;
  powerPerCorner_kW_idx_2 = rtu_Motor_Omega_RL;
  powerPerCorner_kW_idx_3 = rtu_Motor_Omega_RR;
  powerPerCorner_kW_idx_0 = rtu_Torque_FL * std::abs(powerPerCorner_kW_idx_0) /
    1000.0;
  powerPerCorner_kW_idx_1 = rtu_Torque_FR * std::abs(powerPerCorner_kW_idx_1) /
    1000.0;
  powerPerCorner_kW_idx_2 = rtu_Torque_RL * std::abs(powerPerCorner_kW_idx_2) /
    1000.0;
  powerPerCorner_kW_idx_3 = rtu_Torque_RR * std::abs(powerPerCorner_kW_idx_3) /
    1000.0;
  *rty_cornerPower_FL = powerPerCorner_kW_idx_0;
  *rty_cornerPower_FR = powerPerCorner_kW_idx_1;
  *rty_cornerPower_RL = powerPerCorner_kW_idx_2;
  *rty_cornerPower_RR = powerPerCorner_kW_idx_3;
}

// Output and update for referenced model: 'POWER_LIMIT'
void POWER_LIMIT::step(const real_T *rtu_CurrentElectricalPowerkW, const real_T *
  rtu_TorqueInputFL, const real_T *rtu_TorqueInputFR, const real_T
  *rtu_TorqueInputRL, const real_T *rtu_TorqueInputRR, const real_T
  *rtu_WheelOmegaFLrads, const real_T *rtu_WheelOmegaFRrads, const real_T
  *rtu_WheelOmegaRLrads, const real_T *rtu_WheelOmegaRRrads, const boolean_T
  *rtu_usePowerLimit, const boolean_T *rtu_usePIDPowerLimit, const real_T
  *rtu_AbsoluteTorqueLimit, const real_T *rtu_MechPowerMaxkW, real_T
  *rty_PLTorqueFL, real_T *rty_PLTorqueFR, real_T *rty_PLTorqueRL, real_T
  *rty_PLTorqueRR, real_T *rty_PowerLimStatus, real_T *rty_PowerLimErrorkW,
  real_T *rty_PowerLimTorqueAdjustment, real_T *rty_CornerPowerFLkW, real_T
  *rty_CornerPowerFRkW, real_T *rty_CornerPowerRLkW, real_T *rty_CornerPowerRRkW)
{
  real_T motorOmegaABSVec_idx_0;
  real_T motorOmegaABSVec_idx_3;
  real_T powerLimitedTorque_idx_0;
  real_T powerLimitedTorque_idx_1;
  real_T powerLimitedTorque_idx_2;
  real_T powerLimitedTorque_idx_3;
  real_T rtb_FilterCoefficient;
  real_T rtb_ProportionalGain;
  real_T rtb_TorqueRR;
  real_T rtb_cornerPower_FL;
  real_T rtb_cornerPower_FR;
  real_T rtb_cornerPower_RL;

  // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
  //   ActionPort: '<S1>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem1' incorporates:
  //   ActionPort: '<S5>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem' incorporates:
  //   ActionPort: '<S4>/Action Port'

  // If: '<S1>/If' incorporates:
  //   Gain: '<Root>/Gain'
  //   Gain: '<Root>/Gain1'
  //   Gain: '<Root>/Gain2'
  //   Gain: '<Root>/Gain3'
  //   Gain: '<Root>/Gain4'
  //   Gain: '<Root>/Gain5'
  //   Gain: '<Root>/Gain6'
  //   Gain: '<Root>/Gain7'
  //   Gain: '<S4>/Gain'
  //   Gain: '<S4>/Gain1'
  //   Gain: '<S4>/Gain2'
  //   Gain: '<S4>/Gain3'
  //   Gain: '<S5>/Gain'
  //   Gain: '<S5>/Gain1'
  //   Gain: '<S5>/Gain2'
  //   Gain: '<S5>/Gain3'
  //   If: '<Root>/If1'
  //   If: '<S4>/If'
  //   If: '<S5>/If'
  //   MATLAB Function: '<Root>/MATLAB Function'
  //   MATLAB Function: '<S59>/MATLAB Function'
  //   MATLAB Function: '<S6>/MATLAB Function'

  motorOmegaABSVec_idx_0 = 11.86 * *rtu_WheelOmegaFLrads;
  rtb_FilterCoefficient = 11.86 * *rtu_WheelOmegaFRrads;
  rtb_ProportionalGain = 11.86 * *rtu_WheelOmegaRLrads;
  motorOmegaABSVec_idx_3 = 11.86 * *rtu_WheelOmegaRRrads;

  // Outputs for IfAction SubSystem: '<S5>/HT07 POWER LIMIT' incorporates:
  //   ActionPort: '<S59>/Action Port'

  // Outputs for IfAction SubSystem: '<S4>/HT07 POWER LIMIT' incorporates:
  //   ActionPort: '<S6>/Action Port'

  rtb_cornerPower_FL = std::abs(motorOmegaABSVec_idx_0);

  // End of Outputs for SubSystem: '<S4>/HT07 POWER LIMIT'
  // End of Outputs for SubSystem: '<S5>/HT07 POWER LIMIT'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem1'
  // End of Outputs for SubSystem: '<Root>/If Action Subsystem'

  // MATLAB Function: '<Root>/MATLAB Function'
  powerLimitedTorque_idx_0 = *rtu_TorqueInputFL * rtb_cornerPower_FL / 1000.0;

  // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
  //   ActionPort: '<S1>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem1' incorporates:
  //   ActionPort: '<S5>/Action Port'

  // Outputs for IfAction SubSystem: '<S5>/HT07 POWER LIMIT' incorporates:
  //   ActionPort: '<S59>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem' incorporates:
  //   ActionPort: '<S4>/Action Port'

  // Outputs for IfAction SubSystem: '<S4>/HT07 POWER LIMIT' incorporates:
  //   ActionPort: '<S6>/Action Port'

  // If: '<S1>/If' incorporates:
  //   If: '<Root>/If1'
  //   If: '<S4>/If'
  //   If: '<S5>/If'
  //   MATLAB Function: '<Root>/MATLAB Function'
  //   MATLAB Function: '<S59>/MATLAB Function'
  //   MATLAB Function: '<S6>/MATLAB Function'

  rtb_cornerPower_FR = std::abs(rtb_FilterCoefficient);

  // End of Outputs for SubSystem: '<S4>/HT07 POWER LIMIT'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem'
  // End of Outputs for SubSystem: '<S5>/HT07 POWER LIMIT'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem1'
  // End of Outputs for SubSystem: '<Root>/If Action Subsystem'

  // MATLAB Function: '<Root>/MATLAB Function'
  powerLimitedTorque_idx_1 = *rtu_TorqueInputFR * rtb_cornerPower_FR / 1000.0;

  // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
  //   ActionPort: '<S1>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem1' incorporates:
  //   ActionPort: '<S5>/Action Port'

  // Outputs for IfAction SubSystem: '<S5>/HT07 POWER LIMIT' incorporates:
  //   ActionPort: '<S59>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem' incorporates:
  //   ActionPort: '<S4>/Action Port'

  // Outputs for IfAction SubSystem: '<S4>/HT07 POWER LIMIT' incorporates:
  //   ActionPort: '<S6>/Action Port'

  // If: '<S1>/If' incorporates:
  //   If: '<Root>/If1'
  //   If: '<S4>/If'
  //   If: '<S5>/If'
  //   MATLAB Function: '<Root>/MATLAB Function'
  //   MATLAB Function: '<S59>/MATLAB Function'
  //   MATLAB Function: '<S6>/MATLAB Function'

  rtb_cornerPower_RL = std::abs(rtb_ProportionalGain);

  // End of Outputs for SubSystem: '<S4>/HT07 POWER LIMIT'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem'
  // End of Outputs for SubSystem: '<S5>/HT07 POWER LIMIT'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem1'
  // End of Outputs for SubSystem: '<Root>/If Action Subsystem'

  // MATLAB Function: '<Root>/MATLAB Function'
  powerLimitedTorque_idx_2 = *rtu_TorqueInputRL * rtb_cornerPower_RL / 1000.0;

  // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
  //   ActionPort: '<S1>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem1' incorporates:
  //   ActionPort: '<S5>/Action Port'

  // Outputs for IfAction SubSystem: '<S5>/HT07 POWER LIMIT' incorporates:
  //   ActionPort: '<S59>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem' incorporates:
  //   ActionPort: '<S4>/Action Port'

  // Outputs for IfAction SubSystem: '<S4>/HT07 POWER LIMIT' incorporates:
  //   ActionPort: '<S6>/Action Port'

  // If: '<S1>/If' incorporates:
  //   If: '<Root>/If1'
  //   If: '<S4>/If'
  //   If: '<S5>/If'
  //   MATLAB Function: '<Root>/MATLAB Function'
  //   MATLAB Function: '<S59>/MATLAB Function'
  //   MATLAB Function: '<S6>/MATLAB Function'

  rtb_TorqueRR = std::abs(motorOmegaABSVec_idx_3);

  // End of Outputs for SubSystem: '<S4>/HT07 POWER LIMIT'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem'
  // End of Outputs for SubSystem: '<S5>/HT07 POWER LIMIT'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem1'
  // End of Outputs for SubSystem: '<Root>/If Action Subsystem'

  // MATLAB Function: '<Root>/MATLAB Function'
  powerLimitedTorque_idx_3 = *rtu_TorqueInputRR * rtb_TorqueRR / 1000.0;

  // If: '<Root>/If1'
  if (*rtu_usePowerLimit) {
    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
    //   ActionPort: '<S1>/Action Port'

    // If: '<S1>/If'
    if (*rtu_usePIDPowerLimit) {
      // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem' incorporates:
      //   ActionPort: '<S4>/Action Port'

      // If: '<S4>/If'
      if (*rtu_CurrentElectricalPowerkW >= 80.0) {
        // Outputs for IfAction SubSystem: '<S4>/HT07 POWER LIMIT' incorporates:
        //   ActionPort: '<S6>/Action Port'

        // MATLAB Function: '<S6>/MATLAB Function' incorporates:
        //   Constant: '<S6>/Constant'

        powerLimitedTorque_idx_3 = ((std::abs(*rtu_TorqueInputFL) + std::abs
          (*rtu_TorqueInputFR)) + std::abs(*rtu_TorqueInputRL)) + std::abs
          (*rtu_TorqueInputRR);
        powerLimitedTorque_idx_0 = *rtu_TorqueInputFL / powerLimitedTorque_idx_3
          * 80.0;
        powerLimitedTorque_idx_1 = *rtu_TorqueInputFR / powerLimitedTorque_idx_3
          * 80.0;
        powerLimitedTorque_idx_2 = *rtu_TorqueInputRL / powerLimitedTorque_idx_3
          * 80.0;
        powerLimitedTorque_idx_3 = *rtu_TorqueInputRR / powerLimitedTorque_idx_3
          * 80.0;
        motorOmegaABSVec_idx_0 = powerLimitedTorque_idx_0 * 1000.0 /
          rtb_cornerPower_FL;
        rtb_FilterCoefficient = powerLimitedTorque_idx_1 * 1000.0 /
          rtb_cornerPower_FR;
        rtb_ProportionalGain = powerLimitedTorque_idx_2 * 1000.0 /
          rtb_cornerPower_RL;
        motorOmegaABSVec_idx_3 = powerLimitedTorque_idx_3 * 1000.0 /
          rtb_TorqueRR;
        if (std::abs(motorOmegaABSVec_idx_0) > *rtu_AbsoluteTorqueLimit) {
          if (std::isnan(motorOmegaABSVec_idx_0)) {
            rtb_TorqueRR = (rtNaN);
          } else if (motorOmegaABSVec_idx_0 < 0.0) {
            rtb_TorqueRR = -1.0;
          } else {
            rtb_TorqueRR = (motorOmegaABSVec_idx_0 > 0.0);
          }

          motorOmegaABSVec_idx_0 = *rtu_AbsoluteTorqueLimit * rtb_TorqueRR;
        }

        if (std::abs(rtb_FilterCoefficient) > *rtu_AbsoluteTorqueLimit) {
          if (std::isnan(rtb_FilterCoefficient)) {
            rtb_TorqueRR = (rtNaN);
          } else if (rtb_FilterCoefficient < 0.0) {
            rtb_TorqueRR = -1.0;
          } else {
            rtb_TorqueRR = (rtb_FilterCoefficient > 0.0);
          }

          rtb_FilterCoefficient = *rtu_AbsoluteTorqueLimit * rtb_TorqueRR;
        }

        if (std::abs(rtb_ProportionalGain) > *rtu_AbsoluteTorqueLimit) {
          if (std::isnan(rtb_ProportionalGain)) {
            rtb_TorqueRR = (rtNaN);
          } else if (rtb_ProportionalGain < 0.0) {
            rtb_TorqueRR = -1.0;
          } else {
            rtb_TorqueRR = (rtb_ProportionalGain > 0.0);
          }

          rtb_ProportionalGain = *rtu_AbsoluteTorqueLimit * rtb_TorqueRR;
        }

        if (std::abs(motorOmegaABSVec_idx_3) > *rtu_AbsoluteTorqueLimit) {
          if (std::isnan(motorOmegaABSVec_idx_3)) {
            rtb_TorqueRR = (rtNaN);
          } else if (motorOmegaABSVec_idx_3 < 0.0) {
            rtb_TorqueRR = -1.0;
          } else {
            rtb_TorqueRR = (motorOmegaABSVec_idx_3 > 0.0);
          }

          motorOmegaABSVec_idx_3 = *rtu_AbsoluteTorqueLimit * rtb_TorqueRR;
        }

        // SignalConversion generated from: '<S6>/PLTorque_FL' incorporates:
        //   MATLAB Function: '<S6>/MATLAB Function'

        *rty_PLTorqueFL = motorOmegaABSVec_idx_0;

        // SignalConversion generated from: '<S6>/PLTorque_FR' incorporates:
        //   MATLAB Function: '<S6>/MATLAB Function'

        *rty_PLTorqueFR = rtb_FilterCoefficient;

        // SignalConversion generated from: '<S6>/PLTorque_RL' incorporates:
        //   MATLAB Function: '<S6>/MATLAB Function'

        *rty_PLTorqueRL = rtb_ProportionalGain;

        // SignalConversion generated from: '<S6>/PLTorque_RR' incorporates:
        //   MATLAB Function: '<S6>/MATLAB Function'

        *rty_PLTorqueRR = motorOmegaABSVec_idx_3;

        // SignalConversion generated from: '<S6>/Power Lim Status' incorporates:
        //   Constant: '<S6>/Constant1'

        *rty_PowerLimStatus = 2.0;

        // End of Outputs for SubSystem: '<S4>/HT07 POWER LIMIT'
      } else if (*rtu_CurrentElectricalPowerkW >= 75.0) {
        // Outputs for IfAction SubSystem: '<S4>/PID POWER LIMIT' incorporates:
        //   ActionPort: '<S8>/Action Port'

        // Sum: '<S8>/Subtract' incorporates:
        //   Constant: '<S8>/Constant'

        *rty_PowerLimErrorkW = 75.0 - *rtu_CurrentElectricalPowerkW;

        // Gain: '<S47>/Proportional Gain'
        rtb_ProportionalGain = 1.5 * *rty_PowerLimErrorkW;

        // Gain: '<S36>/Derivative Gain' incorporates:
        //   Gain: '<S39>/Integral Gain'

        motorOmegaABSVec_idx_0 = 0.0 * *rty_PowerLimErrorkW;

        // Gain: '<S45>/Filter Coefficient' incorporates:
        //   DiscreteIntegrator: '<S37>/Filter'
        //   Gain: '<S36>/Derivative Gain'
        //   Sum: '<S37>/SumD'

        rtb_FilterCoefficient = (motorOmegaABSVec_idx_0 -
          POWER_LIMIT_DW.Filter_DSTATE) * 100.0;

        // Sum: '<S51>/Sum' incorporates:
        //   DiscreteIntegrator: '<S42>/Integrator'

        rtb_ProportionalGain = (rtb_ProportionalGain +
          POWER_LIMIT_DW.Integrator_DSTATE) + rtb_FilterCoefficient;

        // Switch: '<S8>/Switch' incorporates:
        //   Constant: '<S8>/Constant2'

        if (rtb_ProportionalGain > 0.0) {
          *rty_PowerLimTorqueAdjustment = 0.0;
        } else {
          *rty_PowerLimTorqueAdjustment = rtb_ProportionalGain;
        }

        // End of Switch: '<S8>/Switch'

        // Sum: '<S8>/Add'
        *rty_PLTorqueFL = *rty_PowerLimTorqueAdjustment + *rtu_TorqueInputFL;

        // Sum: '<S8>/Add1'
        *rty_PLTorqueFR = *rty_PowerLimTorqueAdjustment + *rtu_TorqueInputFR;

        // Sum: '<S8>/Add2'
        *rty_PLTorqueRL = *rty_PowerLimTorqueAdjustment + *rtu_TorqueInputRL;

        // Sum: '<S8>/Add3'
        *rty_PLTorqueRR = *rty_PowerLimTorqueAdjustment + *rtu_TorqueInputRR;

        // SignalConversion generated from: '<S8>/Power Lim Status' incorporates:
        //   Constant: '<S8>/Constant1'

        *rty_PowerLimStatus = 1.0;

        // Update for DiscreteIntegrator: '<S42>/Integrator'
        POWER_LIMIT_DW.Integrator_DSTATE += 0.001 * motorOmegaABSVec_idx_0;

        // Update for DiscreteIntegrator: '<S37>/Filter'
        POWER_LIMIT_DW.Filter_DSTATE += 0.001 * rtb_FilterCoefficient;

        // End of Outputs for SubSystem: '<S4>/PID POWER LIMIT'
      } else {
        // Outputs for IfAction SubSystem: '<S4>/If Action Subsystem1' incorporates:
        //   ActionPort: '<S7>/Action Port'

        // SignalConversion generated from: '<S7>/Power Lim Status' incorporates:
        //   Constant: '<S7>/Constant'

        *rty_PowerLimStatus = 0.0;

        // SignalConversion generated from: '<S7>/Torque FL'
        *rty_PLTorqueFL = *rtu_TorqueInputFL;

        // SignalConversion generated from: '<S7>/Torque FR'
        *rty_PLTorqueFR = *rtu_TorqueInputFR;

        // SignalConversion generated from: '<S7>/Torque RL'
        *rty_PLTorqueRL = *rtu_TorqueInputRL;

        // SignalConversion generated from: '<S7>/Torque RR'
        *rty_PLTorqueRR = *rtu_TorqueInputRR;

        // End of Outputs for SubSystem: '<S4>/If Action Subsystem1'
      }

      // End of Outputs for SubSystem: '<S1>/If Action Subsystem'
    } else {
      // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem1' incorporates:
      //   ActionPort: '<S5>/Action Port'

      // Sum: '<S5>/Subtract' incorporates:
      //   Abs: '<S5>/Abs'
      //   MATLAB Function: '<Root>/MATLAB Function'

      powerLimitedTorque_idx_0 = std::abs(((powerLimitedTorque_idx_0 +
        powerLimitedTorque_idx_1) + powerLimitedTorque_idx_2) +
        powerLimitedTorque_idx_3) - *rtu_MechPowerMaxkW;

      // If: '<S5>/If'
      if (powerLimitedTorque_idx_0 >= 0.0) {
        // Outputs for IfAction SubSystem: '<S5>/HT07 POWER LIMIT' incorporates:
        //   ActionPort: '<S59>/Action Port'

        // MATLAB Function: '<S59>/MATLAB Function'
        powerLimitedTorque_idx_3 = ((std::abs(*rtu_TorqueInputFL) + std::abs
          (*rtu_TorqueInputFR)) + std::abs(*rtu_TorqueInputRL)) + std::abs
          (*rtu_TorqueInputRR);
        powerLimitedTorque_idx_0 = *rtu_TorqueInputFL / powerLimitedTorque_idx_3
          * *rtu_MechPowerMaxkW * 1000.0 / rtb_cornerPower_FL;
        powerLimitedTorque_idx_1 = *rtu_TorqueInputFR / powerLimitedTorque_idx_3
          * *rtu_MechPowerMaxkW * 1000.0 / rtb_cornerPower_FR;
        powerLimitedTorque_idx_2 = *rtu_TorqueInputRL / powerLimitedTorque_idx_3
          * *rtu_MechPowerMaxkW * 1000.0 / rtb_cornerPower_RL;
        powerLimitedTorque_idx_3 = *rtu_TorqueInputRR / powerLimitedTorque_idx_3
          * *rtu_MechPowerMaxkW * 1000.0 / rtb_TorqueRR;
        if (std::abs(powerLimitedTorque_idx_0) > *rtu_AbsoluteTorqueLimit) {
          if (std::isnan(powerLimitedTorque_idx_0)) {
            rtb_TorqueRR = (rtNaN);
          } else if (powerLimitedTorque_idx_0 < 0.0) {
            rtb_TorqueRR = -1.0;
          } else {
            rtb_TorqueRR = (powerLimitedTorque_idx_0 > 0.0);
          }

          // Merge: '<S5>/Merge'
          powerLimitedTorque_idx_0 = *rtu_AbsoluteTorqueLimit * rtb_TorqueRR;
        }

        if (std::abs(powerLimitedTorque_idx_1) > *rtu_AbsoluteTorqueLimit) {
          if (std::isnan(powerLimitedTorque_idx_1)) {
            rtb_TorqueRR = (rtNaN);
          } else if (powerLimitedTorque_idx_1 < 0.0) {
            rtb_TorqueRR = -1.0;
          } else {
            rtb_TorqueRR = (powerLimitedTorque_idx_1 > 0.0);
          }

          // Merge: '<S5>/Merge1'
          powerLimitedTorque_idx_1 = *rtu_AbsoluteTorqueLimit * rtb_TorqueRR;
        }

        if (std::abs(powerLimitedTorque_idx_2) > *rtu_AbsoluteTorqueLimit) {
          if (std::isnan(powerLimitedTorque_idx_2)) {
            rtb_TorqueRR = (rtNaN);
          } else if (powerLimitedTorque_idx_2 < 0.0) {
            rtb_TorqueRR = -1.0;
          } else {
            rtb_TorqueRR = (powerLimitedTorque_idx_2 > 0.0);
          }

          // Merge: '<S5>/Merge2'
          powerLimitedTorque_idx_2 = *rtu_AbsoluteTorqueLimit * rtb_TorqueRR;
        }

        if (std::abs(powerLimitedTorque_idx_3) > *rtu_AbsoluteTorqueLimit) {
          if (std::isnan(powerLimitedTorque_idx_3)) {
            rtb_TorqueRR = (rtNaN);
          } else if (powerLimitedTorque_idx_3 < 0.0) {
            rtb_TorqueRR = -1.0;
          } else {
            rtb_TorqueRR = (powerLimitedTorque_idx_3 > 0.0);
          }

          // Merge: '<S5>/Merge3'
          powerLimitedTorque_idx_3 = *rtu_AbsoluteTorqueLimit * rtb_TorqueRR;
        }

        // SignalConversion generated from: '<S59>/Power Lim Status' incorporates:
        //   Constant: '<S59>/Constant1'

        *rty_PowerLimStatus = 2.0;

        // End of Outputs for SubSystem: '<S5>/HT07 POWER LIMIT'
      } else {
        // Outputs for IfAction SubSystem: '<S5>/If Action Subsystem1' incorporates:
        //   ActionPort: '<S60>/Action Port'

        // SignalConversion generated from: '<S60>/Power Lim Status' incorporates:
        //   Constant: '<S60>/Constant1'

        *rty_PowerLimStatus = 0.0;

        // Merge: '<S5>/Merge' incorporates:
        //   SignalConversion generated from: '<S60>/Torque FL'

        powerLimitedTorque_idx_0 = *rtu_TorqueInputFL;

        // Merge: '<S5>/Merge1' incorporates:
        //   SignalConversion generated from: '<S60>/Torque FR'

        powerLimitedTorque_idx_1 = *rtu_TorqueInputFR;

        // Merge: '<S5>/Merge2' incorporates:
        //   SignalConversion generated from: '<S60>/Torque RL'

        powerLimitedTorque_idx_2 = *rtu_TorqueInputRL;

        // Merge: '<S5>/Merge3' incorporates:
        //   SignalConversion generated from: '<S60>/Torque RR'

        powerLimitedTorque_idx_3 = *rtu_TorqueInputRR;

        // End of Outputs for SubSystem: '<S5>/If Action Subsystem1'
      }

      // MATLAB Function: '<S5>/MATLAB Function'
      POWER_LIMIT_MATLABFunction(powerLimitedTorque_idx_0,
        powerLimitedTorque_idx_1, powerLimitedTorque_idx_2,
        powerLimitedTorque_idx_3, motorOmegaABSVec_idx_0, rtb_FilterCoefficient,
        rtb_ProportionalGain, motorOmegaABSVec_idx_3,
        &POWER_LIMIT_B.cornerPower_FL, &POWER_LIMIT_B.cornerPower_FR,
        &POWER_LIMIT_B.cornerPower_RL, &POWER_LIMIT_B.cornerPower_RR);

      // SignalConversion generated from: '<S5>/PLTorque RR'
      *rty_PLTorqueRR = powerLimitedTorque_idx_3;

      // SignalConversion generated from: '<S5>/PLTorque RL'
      *rty_PLTorqueRL = powerLimitedTorque_idx_2;

      // SignalConversion generated from: '<S5>/PLTorque FR'
      *rty_PLTorqueFR = powerLimitedTorque_idx_1;

      // SignalConversion generated from: '<S5>/PLTorque FL'
      *rty_PLTorqueFL = powerLimitedTorque_idx_0;

      // End of Outputs for SubSystem: '<S1>/If Action Subsystem1'
    }

    // SignalConversion generated from: '<S1>/cornerPower_FL'
    *rty_CornerPowerFLkW = POWER_LIMIT_B.cornerPower_FL;

    // SignalConversion generated from: '<S1>/cornerPower_FR'
    *rty_CornerPowerFRkW = POWER_LIMIT_B.cornerPower_FR;

    // SignalConversion generated from: '<S1>/cornerPower_RL'
    *rty_CornerPowerRLkW = POWER_LIMIT_B.cornerPower_RL;

    // SignalConversion generated from: '<S1>/cornerPower_RR'
    *rty_CornerPowerRRkW = POWER_LIMIT_B.cornerPower_RR;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // SignalConversion generated from: '<S2>/Torque FL'
    powerLimitedTorque_idx_0 = *rtu_TorqueInputFL;

    // SignalConversion generated from: '<S2>/Torque FR'
    powerLimitedTorque_idx_1 = *rtu_TorqueInputFR;

    // SignalConversion generated from: '<S2>/Torque RL'
    powerLimitedTorque_idx_2 = *rtu_TorqueInputRL;

    // SignalConversion generated from: '<S2>/Torque RR'
    rtb_TorqueRR = *rtu_TorqueInputRR;

    // MATLAB Function: '<S2>/MATLAB Function' incorporates:
    //   Gain: '<Root>/Gain'
    //   Gain: '<Root>/Gain1'
    //   Gain: '<Root>/Gain2'
    //   Gain: '<Root>/Gain3'

    POWER_LIMIT_MATLABFunction(powerLimitedTorque_idx_0,
      powerLimitedTorque_idx_1, powerLimitedTorque_idx_2, rtb_TorqueRR,
      motorOmegaABSVec_idx_0, rtb_FilterCoefficient, rtb_ProportionalGain,
      motorOmegaABSVec_idx_3, &rtb_cornerPower_FL, &rtb_cornerPower_FR,
      &rtb_cornerPower_RL, &powerLimitedTorque_idx_3);

    // SignalConversion generated from: '<S2>/cornerPower_FL'
    *rty_CornerPowerFLkW = rtb_cornerPower_FL;

    // SignalConversion generated from: '<S2>/cornerPower_FR'
    *rty_CornerPowerFRkW = rtb_cornerPower_FR;

    // SignalConversion generated from: '<S2>/cornerPower_RL'
    *rty_CornerPowerRLkW = rtb_cornerPower_RL;

    // SignalConversion generated from: '<S2>/cornerPower_RR'
    *rty_CornerPowerRRkW = powerLimitedTorque_idx_3;

    // SignalConversion generated from: '<S2>/NonPL Torque RR'
    *rty_PLTorqueRR = rtb_TorqueRR;

    // SignalConversion generated from: '<S2>/NonPL Torque RL'
    *rty_PLTorqueRL = powerLimitedTorque_idx_2;

    // SignalConversion generated from: '<S2>/NonPL Torque FR'
    *rty_PLTorqueFR = powerLimitedTorque_idx_1;

    // SignalConversion generated from: '<S2>/NonPL Torque FL'
    *rty_PLTorqueFL = powerLimitedTorque_idx_0;

    // SignalConversion generated from: '<S2>/Power Lim Status' incorporates:
    //   Constant: '<S2>/Constant'

    *rty_PowerLimStatus = 0.0;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem1'
  }
}

// Model initialize function
void POWER_LIMIT::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // Initialize DataMapInfo substructure containing ModelMap for C API
  POWER_LIMIT_InitializeDataMapInfo((&POWER_LIMIT_M), &POWER_LIMIT_B);
}

// Constructor
POWER_LIMIT::POWER_LIMIT() :
  POWER_LIMIT_B(),
  POWER_LIMIT_DW(),
  POWER_LIMIT_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
POWER_LIMIT::~POWER_LIMIT() = default;

// Real-Time Model get method
POWER_LIMIT::RT_MODEL_POWER_LIMIT_T * POWER_LIMIT::getRTM()
{
  return (&POWER_LIMIT_M);
}

// member function to set up the C-API information
void POWER_LIMIT::setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const
  char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  // Initialize Parent model MMI
  if ((rt_ParentMMI != (nullptr)) && (rt_ChildPath != (nullptr))) {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &((&POWER_LIMIT_M)
      ->DataMapInfo.mmi));
    rtwCAPI_SetPath((&POWER_LIMIT_M)->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex((&POWER_LIMIT_M)->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

// member function to setup error status pointer
void POWER_LIMIT::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&POWER_LIMIT_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
