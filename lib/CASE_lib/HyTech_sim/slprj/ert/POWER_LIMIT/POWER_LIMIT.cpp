//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: POWER_LIMIT.cpp
//
// Code generated for Simulink model 'POWER_LIMIT'.
//
// Model version                  : 1.34
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Apr 11 22:49:33 2024
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
#include "POWER_LIMIT_private.h"

// Output and update for referenced model: 'POWER_LIMIT'
void POWER_LIMIT::step(const real_T *rtu_CurrentPowerkW, const real_T
  *rtu_TorqueFL, const real_T *rtu_TorqueFR, const real_T *rtu_TorqueRL, const
  real_T *rtu_TorqueRR, const real_T *rtu_WheelOmegaFLrads, const real_T
  *rtu_WheelOmegaFRrads, const real_T *rtu_WheelOmegaRLrads, const real_T
  *rtu_WheelOmegaRRrads, const boolean_T *rtu_usePowerLimit, const boolean_T
  *rtu_usePIDPowerLimit, real_T *rty_PLTorqueFL, real_T *rty_PLTorqueFR, real_T *
  rty_PLTorqueRL, real_T *rty_PLTorqueRR, real_T *rty_PowerLimStatus, real_T
  *rty_PowerLimErrorkW, real_T *rty_PowerLimTorqueAdjustment, real_T
  *rty_CornerPowerFLkW, real_T *rty_CornerPowerFRkW, real_T *rty_CornerPowerRLkW,
  real_T *rty_CornerPowerRRkW)
{
  // If: '<Root>/If1'
  if (*rtu_usePowerLimit) {
    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
    //   ActionPort: '<S1>/Action Port'

    // If: '<S1>/If'
    if (*rtu_usePIDPowerLimit) {
      real_T rtb_Gain;
      real_T rtb_Gain1;
      real_T rtb_Gain2;
      real_T rtb_Gain3;

      // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem' incorporates:
      //   ActionPort: '<S3>/Action Port'

      // Gain: '<S3>/Gain'
      rtb_Gain = 11.86 * *rtu_WheelOmegaFLrads;

      // Gain: '<S3>/Gain1'
      rtb_Gain1 = 11.86 * *rtu_WheelOmegaFRrads;

      // Gain: '<S3>/Gain2'
      rtb_Gain2 = 11.86 * *rtu_WheelOmegaRLrads;

      // Gain: '<S3>/Gain3'
      rtb_Gain3 = 11.86 * *rtu_WheelOmegaRRrads;

      // If: '<S3>/If'
      if (*rtu_CurrentPowerkW >= 80.0) {
        real_T powerPerCorner_kW_idx_0;
        real_T powerPerCorner_kW_idx_1;
        real_T powerPerCorner_kW_idx_2;
        real_T torqueNet_Mag;

        // Outputs for IfAction SubSystem: '<S3>/HT07 POWER LIMIT' incorporates:
        //   ActionPort: '<S5>/Action Port'

        // MATLAB Function: '<S5>/MATLAB Function' incorporates:
        //   Constant: '<S5>/Constant'

        torqueNet_Mag = ((std::abs(*rtu_TorqueFL) + std::abs(*rtu_TorqueFR)) +
                         std::abs(*rtu_TorqueRL)) + std::abs(*rtu_TorqueRR);
        powerPerCorner_kW_idx_0 = *rtu_TorqueFL / torqueNet_Mag * 80.0 * 1000.0;
        powerPerCorner_kW_idx_1 = *rtu_TorqueFR / torqueNet_Mag * 80.0 * 1000.0;
        powerPerCorner_kW_idx_2 = *rtu_TorqueRL / torqueNet_Mag * 80.0 * 1000.0;
        torqueNet_Mag = *rtu_TorqueRR / torqueNet_Mag * 80.0 * 1000.0;
        POWER_LIMIT_B.cornerPower_FL_i = powerPerCorner_kW_idx_0;
        POWER_LIMIT_B.cornerPower_FR_k = powerPerCorner_kW_idx_0;
        POWER_LIMIT_B.cornerPower_RL_b = powerPerCorner_kW_idx_0;
        POWER_LIMIT_B.cornerPower_RR_b = powerPerCorner_kW_idx_0;

        // SignalConversion generated from: '<S5>/PLTorque_FL' incorporates:
        //   MATLAB Function: '<S5>/MATLAB Function'

        *rty_PLTorqueFL = powerPerCorner_kW_idx_0 / rtb_Gain;

        // SignalConversion generated from: '<S5>/PLTorque_FR' incorporates:
        //   MATLAB Function: '<S5>/MATLAB Function'

        *rty_PLTorqueFR = powerPerCorner_kW_idx_1 / rtb_Gain1;

        // SignalConversion generated from: '<S5>/PLTorque_RL' incorporates:
        //   MATLAB Function: '<S5>/MATLAB Function'

        *rty_PLTorqueRL = powerPerCorner_kW_idx_2 / rtb_Gain2;

        // SignalConversion generated from: '<S5>/PLTorque_RR' incorporates:
        //   MATLAB Function: '<S5>/MATLAB Function'

        *rty_PLTorqueRR = torqueNet_Mag / rtb_Gain3;

        // SignalConversion generated from: '<S5>/Power Lim Status' incorporates:
        //   Constant: '<S5>/Constant1'

        *rty_PowerLimStatus = 2.0;

        // End of Outputs for SubSystem: '<S3>/HT07 POWER LIMIT'
      } else if (*rtu_CurrentPowerkW >= 75.0) {
        real_T powerPerCorner_kW_idx_1;
        real_T powerPerCorner_kW_idx_2;
        real_T torqueNet_Mag;

        // Outputs for IfAction SubSystem: '<S3>/PID POWER LIMIT' incorporates:
        //   ActionPort: '<S7>/Action Port'

        // Sum: '<S7>/Subtract' incorporates:
        //   Constant: '<S7>/Constant'

        *rty_PowerLimErrorkW = 75.0 - *rtu_CurrentPowerkW;

        // Gain: '<S46>/Proportional Gain'
        torqueNet_Mag = 1.5 * *rty_PowerLimErrorkW;

        // Gain: '<S35>/Derivative Gain' incorporates:
        //   Gain: '<S38>/Integral Gain'

        powerPerCorner_kW_idx_2 = 0.0 * *rty_PowerLimErrorkW;

        // Gain: '<S44>/Filter Coefficient' incorporates:
        //   DiscreteIntegrator: '<S36>/Filter'
        //   Gain: '<S35>/Derivative Gain'
        //   Sum: '<S36>/SumD'

        powerPerCorner_kW_idx_1 = (powerPerCorner_kW_idx_2 -
          POWER_LIMIT_DW.Filter_DSTATE) * 100.0;

        // Sum: '<S50>/Sum' incorporates:
        //   DiscreteIntegrator: '<S41>/Integrator'

        torqueNet_Mag = (torqueNet_Mag + POWER_LIMIT_DW.Integrator_DSTATE) +
          powerPerCorner_kW_idx_1;

        // Switch: '<S7>/Switch' incorporates:
        //   Constant: '<S7>/Constant2'

        if (torqueNet_Mag > 0.0) {
          *rty_PowerLimTorqueAdjustment = 0.0;
        } else {
          *rty_PowerLimTorqueAdjustment = torqueNet_Mag;
        }

        // End of Switch: '<S7>/Switch'

        // Sum: '<S7>/Add'
        *rty_PLTorqueFL = *rty_PowerLimTorqueAdjustment + *rtu_TorqueFL;

        // Sum: '<S7>/Add1'
        *rty_PLTorqueFR = *rty_PowerLimTorqueAdjustment + *rtu_TorqueFR;

        // Sum: '<S7>/Add2'
        *rty_PLTorqueRL = *rty_PowerLimTorqueAdjustment + *rtu_TorqueRL;

        // Sum: '<S7>/Add3'
        *rty_PLTorqueRR = *rty_PowerLimTorqueAdjustment + *rtu_TorqueRR;

        // SignalConversion generated from: '<S7>/Power Lim Status' incorporates:
        //   Constant: '<S7>/Constant1'

        *rty_PowerLimStatus = 1.0;

        // Update for DiscreteIntegrator: '<S41>/Integrator'
        POWER_LIMIT_DW.Integrator_DSTATE += 0.001 * powerPerCorner_kW_idx_2;

        // Update for DiscreteIntegrator: '<S36>/Filter'
        POWER_LIMIT_DW.Filter_DSTATE += 0.001 * powerPerCorner_kW_idx_1;

        // End of Outputs for SubSystem: '<S3>/PID POWER LIMIT'
      } else {
        // Outputs for IfAction SubSystem: '<S3>/If Action Subsystem1' incorporates:
        //   ActionPort: '<S6>/Action Port'

        // SignalConversion generated from: '<S6>/Power Lim Status' incorporates:
        //   Constant: '<S6>/Constant'

        *rty_PowerLimStatus = 0.0;

        // SignalConversion generated from: '<S6>/Torque FL'
        *rty_PLTorqueFL = *rtu_TorqueFL;

        // SignalConversion generated from: '<S6>/Torque FR'
        *rty_PLTorqueFR = *rtu_TorqueFR;

        // SignalConversion generated from: '<S6>/Torque RL'
        *rty_PLTorqueRL = *rtu_TorqueRL;

        // SignalConversion generated from: '<S6>/Torque RR'
        *rty_PLTorqueRR = *rtu_TorqueRR;

        // End of Outputs for SubSystem: '<S3>/If Action Subsystem1'
      }

      // End of If: '<S3>/If'

      // SignalConversion generated from: '<S3>/cornerPower_FL'
      *rty_CornerPowerFLkW = POWER_LIMIT_B.cornerPower_FL_i;

      // SignalConversion generated from: '<S3>/cornerPower_FR'
      *rty_CornerPowerFRkW = POWER_LIMIT_B.cornerPower_FR_k;

      // SignalConversion generated from: '<S3>/cornerPower_RL'
      *rty_CornerPowerRLkW = POWER_LIMIT_B.cornerPower_RL_b;

      // SignalConversion generated from: '<S3>/cornerPower_RR'
      *rty_CornerPowerRRkW = POWER_LIMIT_B.cornerPower_RR_b;

      // End of Outputs for SubSystem: '<S1>/If Action Subsystem'
    } else {
      real_T rtb_Gain;
      real_T rtb_Gain1;
      real_T rtb_Gain2;
      real_T rtb_Gain3;

      // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem1' incorporates:
      //   ActionPort: '<S4>/Action Port'

      // Gain: '<S4>/Gain'
      rtb_Gain = 11.86 * *rtu_WheelOmegaFLrads;

      // Gain: '<S4>/Gain1'
      rtb_Gain1 = 11.86 * *rtu_WheelOmegaFRrads;

      // Gain: '<S4>/Gain2'
      rtb_Gain2 = 11.86 * *rtu_WheelOmegaRLrads;

      // Gain: '<S4>/Gain3'
      rtb_Gain3 = 11.86 * *rtu_WheelOmegaRRrads;

      // If: '<S4>/If'
      if (*rtu_CurrentPowerkW >= 75.0) {
        real_T powerPerCorner_kW_idx_0;
        real_T powerPerCorner_kW_idx_1;
        real_T powerPerCorner_kW_idx_2;
        real_T torqueNet_Mag;

        // Outputs for IfAction SubSystem: '<S4>/HT07 POWER LIMIT' incorporates:
        //   ActionPort: '<S58>/Action Port'

        // MATLAB Function: '<S58>/MATLAB Function' incorporates:
        //   Constant: '<S58>/Constant'

        torqueNet_Mag = ((std::abs(*rtu_TorqueFL) + std::abs(*rtu_TorqueFR)) +
                         std::abs(*rtu_TorqueRL)) + std::abs(*rtu_TorqueRR);
        powerPerCorner_kW_idx_0 = *rtu_TorqueFL / torqueNet_Mag * 80.0 * 1000.0;
        powerPerCorner_kW_idx_1 = *rtu_TorqueFR / torqueNet_Mag * 80.0 * 1000.0;
        powerPerCorner_kW_idx_2 = *rtu_TorqueRL / torqueNet_Mag * 80.0 * 1000.0;
        torqueNet_Mag = *rtu_TorqueRR / torqueNet_Mag * 80.0 * 1000.0;
        POWER_LIMIT_B.cornerPower_FL = powerPerCorner_kW_idx_0;
        POWER_LIMIT_B.cornerPower_FR = powerPerCorner_kW_idx_0;
        POWER_LIMIT_B.cornerPower_RL = powerPerCorner_kW_idx_0;
        POWER_LIMIT_B.cornerPower_RR = powerPerCorner_kW_idx_0;

        // SignalConversion generated from: '<S58>/PLTorque_FL' incorporates:
        //   MATLAB Function: '<S58>/MATLAB Function'

        *rty_PLTorqueFL = powerPerCorner_kW_idx_0 / rtb_Gain;

        // SignalConversion generated from: '<S58>/PLTorque_FR' incorporates:
        //   MATLAB Function: '<S58>/MATLAB Function'

        *rty_PLTorqueFR = powerPerCorner_kW_idx_1 / rtb_Gain1;

        // SignalConversion generated from: '<S58>/PLTorque_RL' incorporates:
        //   MATLAB Function: '<S58>/MATLAB Function'

        *rty_PLTorqueRL = powerPerCorner_kW_idx_2 / rtb_Gain2;

        // SignalConversion generated from: '<S58>/PLTorque_RR' incorporates:
        //   MATLAB Function: '<S58>/MATLAB Function'

        *rty_PLTorqueRR = torqueNet_Mag / rtb_Gain3;

        // SignalConversion generated from: '<S58>/Power Lim Status' incorporates:
        //   Constant: '<S58>/Constant1'

        *rty_PowerLimStatus = 2.0;

        // End of Outputs for SubSystem: '<S4>/HT07 POWER LIMIT'
      } else {
        // Outputs for IfAction SubSystem: '<S4>/If Action Subsystem1' incorporates:
        //   ActionPort: '<S59>/Action Port'

        // SignalConversion generated from: '<S59>/Power Lim Status' incorporates:
        //   Constant: '<S59>/Constant1'

        *rty_PowerLimStatus = 0.0;

        // SignalConversion generated from: '<S59>/Torque FL'
        *rty_PLTorqueFL = *rtu_TorqueFL;

        // SignalConversion generated from: '<S59>/Torque FR'
        *rty_PLTorqueFR = *rtu_TorqueFR;

        // SignalConversion generated from: '<S59>/Torque RL'
        *rty_PLTorqueRL = *rtu_TorqueRL;

        // SignalConversion generated from: '<S59>/Torque RR'
        *rty_PLTorqueRR = *rtu_TorqueRR;

        // End of Outputs for SubSystem: '<S4>/If Action Subsystem1'
      }

      // End of If: '<S4>/If'

      // SignalConversion generated from: '<S4>/cornerPower_FL'
      *rty_CornerPowerFLkW = POWER_LIMIT_B.cornerPower_FL;

      // SignalConversion generated from: '<S4>/cornerPower_FR'
      *rty_CornerPowerFRkW = POWER_LIMIT_B.cornerPower_FR;

      // SignalConversion generated from: '<S4>/cornerPower_RL'
      *rty_CornerPowerRLkW = POWER_LIMIT_B.cornerPower_RL;

      // SignalConversion generated from: '<S4>/cornerPower_RR'
      *rty_CornerPowerRRkW = POWER_LIMIT_B.cornerPower_RR;

      // End of Outputs for SubSystem: '<S1>/If Action Subsystem1'
    }

    // End of If: '<S1>/If'
    // End of Outputs for SubSystem: '<Root>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // SignalConversion generated from: '<S2>/Power Lim Status' incorporates:
    //   Constant: '<S2>/Constant'

    *rty_PowerLimStatus = 0.0;

    // SignalConversion generated from: '<S2>/Corner Power FL' incorporates:
    //   Constant: '<S2>/Constant1'

    *rty_CornerPowerFLkW = 0.0;

    // SignalConversion generated from: '<S2>/Corner Power FR' incorporates:
    //   Constant: '<S2>/Constant2'

    *rty_CornerPowerFRkW = 0.0;

    // SignalConversion generated from: '<S2>/Corner Power RL' incorporates:
    //   Constant: '<S2>/Constant3'

    *rty_CornerPowerRLkW = 0.0;

    // SignalConversion generated from: '<S2>/Corner Power RR' incorporates:
    //   Constant: '<S2>/Constant4'

    *rty_CornerPowerRRkW = 0.0;

    // SignalConversion generated from: '<S2>/Torque FL'
    *rty_PLTorqueFL = *rtu_TorqueFL;

    // SignalConversion generated from: '<S2>/Torque FR'
    *rty_PLTorqueFR = *rtu_TorqueFR;

    // SignalConversion generated from: '<S2>/Torque RL'
    *rty_PLTorqueRL = *rtu_TorqueRL;

    // SignalConversion generated from: '<S2>/Torque RR'
    *rty_PLTorqueRR = *rtu_TorqueRR;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem1'
  }

  // End of If: '<Root>/If1'
}

// Model initialize function
void POWER_LIMIT::initialize()
{
  // Registration code

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
