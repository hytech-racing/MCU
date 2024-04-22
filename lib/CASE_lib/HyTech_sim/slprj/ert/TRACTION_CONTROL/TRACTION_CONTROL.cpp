//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TRACTION_CONTROL.cpp
//
// Code generated for Simulink model 'TRACTION_CONTROL'.
//
// Model version                  : 1.26
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Sun Apr 21 22:13:39 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "TRACTION_CONTROL.h"
#include "rtwtypes.h"
#include <cmath>
#include "TRACTION_CONTROL_capi.h"
#include "TRACTION_CONTROL_private.h"

//
// Output and update for atomic system:
//    '<S1>/MATLAB Function'
//    '<S1>/MATLAB Function1'
//    '<S1>/MATLAB Function2'
//    '<S1>/MATLAB Function3'
//
void TRACTION_CONTROL::TRACTION_CONTROL_MATLABFunction(real_T rtu_TCS_PID_Output,
  real_T rtu_torqueReference, real_T *rty_adjusted_TCS_PID_Output)
{
  *rty_adjusted_TCS_PID_Output = rtu_TCS_PID_Output;
  if ((rtu_TCS_PID_Output > rtu_torqueReference) && (rtu_torqueReference > 0.0))
  {
    *rty_adjusted_TCS_PID_Output = rtu_torqueReference;
  }

  if (rtu_torqueReference <= 0.0) {
    *rty_adjusted_TCS_PID_Output = 0.0;
  }
}

// System initialize for referenced model: 'TRACTION_CONTROL'
void TRACTION_CONTROL::init(real_T rty_TCSPIDData[8]) const
{
  // SystemInitialize for SignalConversion generated from: '<Root>/TCS PID Data' 
  rty_TCSPIDData[0] = TRACTION_CONTROL_B.Switch;
  rty_TCSPIDData[1] = TRACTION_CONTROL_B.adjusted_TCS_PID_Output_e;
  rty_TCSPIDData[2] = TRACTION_CONTROL_B.Switch1;
  rty_TCSPIDData[3] = TRACTION_CONTROL_B.adjusted_TCS_PID_Output_l;
  rty_TCSPIDData[4] = TRACTION_CONTROL_B.Switch3;
  rty_TCSPIDData[5] = TRACTION_CONTROL_B.adjusted_TCS_PID_Output_c;
  rty_TCSPIDData[6] = TRACTION_CONTROL_B.Switch6;
  rty_TCSPIDData[7] = TRACTION_CONTROL_B.adjusted_TCS_PID_Output;
}

// Output and update for referenced model: 'TRACTION_CONTROL'
void TRACTION_CONTROL::step(const real_T *rtu_DriverTorqueAvg, const boolean_T
  *rtu_useTractionControl, const real_T *rtu_TCS_SLThreshold, const real_T
  *rtu_TorqueInputFL, const real_T *rtu_TorqueInputFR, const real_T
  *rtu_TorqueInputRL, const real_T *rtu_TorqueInputRR, const real_T *rtu_SLFL,
  const real_T *rtu_SLFR, const real_T *rtu_SLRL, const real_T *rtu_SLRR, const
  boolean_T *rtu_useLaunch, const real_T *rtu_launchSL, const real_T
  *rtu_launchDeadZone, const real_T rtu_TCSPIDConfig[3], const real_T *rtu_Vx_B,
  const real_T *rtu_LaunchVelThreshold, const real_T *rtu_TCSVelThreshold,
  real_T *rty_TCSTorqueFL, real_T *rty_TCSTorqueFR, real_T *rty_TCSTorqueRL,
  real_T *rty_TCSTorqueRR, real_T *rty_TCSStatusFL, real_T *rty_TCSStatusFR,
  real_T *rty_TCSStatusRL, real_T *rty_TCSStatusRR, real_T rty_TCSPIDData[8])
{
  real_T rtb_DeadZone_g;
  real_T rtb_IProdOut;
  real_T rtb_Integrator_g;
  real_T rtb_Integrator_k;
  real_T rtb_Integrator_l;
  real_T rtb_Subtract5_l;
  real_T rtb_Subtract8;
  real_T rtb_Switch12;
  real_T rtb_Switch12_d;
  real_T rtb_Switch22;
  real_T rtb_Switch8;
  real_T tmp;
  int8_T tmp_0;
  int8_T tmp_1;

  // If: '<Root>/If1'
  if (*rtu_useTractionControl) {
    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
    //   ActionPort: '<S1>/Action Port'

    // Switch: '<S11>/Switch12' incorporates:
    //   Switch: '<S15>/Switch28'
    //   Switch: '<S1>/Switch8'

    if (*rtu_useLaunch) {
      // Sum: '<S11>/Subtract5'
      rtb_Subtract5_l = *rtu_DriverTorqueAvg - *rtu_launchDeadZone;

      // Switch: '<S11>/Switch11' incorporates:
      //   Switch: '<S11>/Switch17'

      if (rtb_Subtract5_l > 0.0) {
        rtb_Switch12 = *rtu_TorqueInputFL;
      } else if (*rtu_TorqueInputFL > 0.0) {
        // Switch: '<S11>/Switch17' incorporates:
        //   Constant: '<S11>/Constant9'

        rtb_Switch12 = 0.0;
      } else {
        // Switch: '<S11>/Switch17'
        rtb_Switch12 = *rtu_TorqueInputFL;
      }

      // End of Switch: '<S11>/Switch11'
      rtb_Switch8 = *rtu_launchSL;
      rtb_Subtract5_l = *rtu_LaunchVelThreshold;
    } else {
      rtb_Switch12 = *rtu_TorqueInputFL;
      rtb_Switch8 = *rtu_TCS_SLThreshold;
      rtb_Subtract5_l = *rtu_TCSVelThreshold;
    }

    // End of Switch: '<S11>/Switch12'

    // Abs: '<S15>/Abs' incorporates:
    //   Abs: '<S16>/Abs'
    //   Abs: '<S17>/Abs'
    //   Abs: '<S18>/Abs'

    rtb_IProdOut = std::abs(*rtu_Vx_B);

    // Switch: '<S15>/Switch29' incorporates:
    //   Abs: '<S15>/Abs'
    //   Constant: '<S15>/Constant23'
    //   Sum: '<S15>/Subtract9'

    if (rtb_IProdOut - rtb_Subtract5_l > 0.0) {
      // Sum: '<S1>/Subtract'
      rtb_Subtract5_l = *rtu_SLFL - rtb_Switch8;
    } else {
      rtb_Subtract5_l = 0.0;
    }

    // End of Switch: '<S15>/Switch29'

    // Switch: '<S1>/Switch'
    if (rtb_Subtract5_l > 0.0) {
      // Switch: '<S1>/Switch'
      TRACTION_CONTROL_B.Switch = rtb_Subtract5_l;
    } else {
      // Switch: '<S1>/Switch' incorporates:
      //   Constant: '<S1>/Constant'

      TRACTION_CONTROL_B.Switch = 0.0;
    }

    // End of Switch: '<S1>/Switch'

    // Product: '<S58>/PProd Out'
    rtb_Subtract5_l = TRACTION_CONTROL_B.Switch * rtu_TCSPIDConfig[0];

    // Product: '<S47>/DProd Out'
    rtb_Integrator_l = TRACTION_CONTROL_B.Switch * rtu_TCSPIDConfig[2];

    // Product: '<S56>/NProd Out' incorporates:
    //   Constant: '<S3>/Constant'
    //   DiscreteIntegrator: '<S48>/Filter'
    //   Sum: '<S48>/SumD'

    rtb_Integrator_l = (rtb_Integrator_l - TRACTION_CONTROL_DW.Filter_DSTATE) *
      100.0;

    // Sum: '<S62>/Sum' incorporates:
    //   DiscreteIntegrator: '<S53>/Integrator'

    rtb_Subtract5_l = (rtb_Subtract5_l + TRACTION_CONTROL_DW.Integrator_DSTATE)
      + rtb_Integrator_l;

    // Switch: '<S1>/Switch22'
    if (*rtu_useLaunch) {
      // Sum: '<S1>/Subtract8'
      rtb_Subtract8 = *rtu_DriverTorqueAvg - *rtu_launchDeadZone;

      // Switch: '<S1>/Switch21' incorporates:
      //   Switch: '<S1>/Switch23'

      if (rtb_Subtract8 > 0.0) {
        rtb_Switch22 = *rtu_DriverTorqueAvg;
      } else if (*rtu_DriverTorqueAvg > 0.0) {
        // Switch: '<S1>/Switch23' incorporates:
        //   Constant: '<S1>/Constant12'

        rtb_Switch22 = 0.0;
      } else {
        // Switch: '<S1>/Switch23'
        rtb_Switch22 = *rtu_DriverTorqueAvg;
      }

      // End of Switch: '<S1>/Switch21'
    } else {
      rtb_Switch22 = *rtu_DriverTorqueAvg;
    }

    // End of Switch: '<S1>/Switch22'

    // Switch: '<S1>/Switch4' incorporates:
    //   Constant: '<S1>/Constant4'
    //   Saturate: '<S60>/Saturation'

    if (rtb_Switch22 > 0.0) {
      // Saturate: '<S60>/Saturation'
      if (rtb_Subtract5_l > 20.0) {
        tmp = 20.0;
      } else if (rtb_Subtract5_l < 0.0) {
        tmp = 0.0;
      } else {
        tmp = rtb_Subtract5_l;
      }
    } else {
      tmp = 0.0;
    }

    // MATLAB Function: '<S1>/MATLAB Function' incorporates:
    //   Switch: '<S1>/Switch4'

    TRACTION_CONTROL_MATLABFunction(tmp, rtb_Switch12,
      &TRACTION_CONTROL_B.adjusted_TCS_PID_Output_e);

    // Sum: '<S1>/Add'
    *rty_TCSTorqueFL = rtb_Switch12 -
      TRACTION_CONTROL_B.adjusted_TCS_PID_Output_e;

    // Switch: '<S1>/Switch24'
    *rty_TCSStatusFL = (TRACTION_CONTROL_B.adjusted_TCS_PID_Output_e > 0.0);

    // Switch: '<S16>/Switch28'
    if (*rtu_useLaunch) {
      rtb_Integrator_g = *rtu_LaunchVelThreshold;
    } else {
      rtb_Integrator_g = *rtu_TCSVelThreshold;
    }

    // End of Switch: '<S16>/Switch28'

    // Switch: '<S16>/Switch29' incorporates:
    //   Constant: '<S16>/Constant23'
    //   Sum: '<S16>/Subtract9'

    if (rtb_IProdOut - rtb_Integrator_g > 0.0) {
      // Sum: '<S1>/Subtract1'
      rtb_Integrator_g = *rtu_SLFR - rtb_Switch8;
    } else {
      rtb_Integrator_g = 0.0;
    }

    // End of Switch: '<S16>/Switch29'

    // Switch: '<S1>/Switch1'
    if (rtb_Integrator_g > 0.0) {
      // Switch: '<S1>/Switch1'
      TRACTION_CONTROL_B.Switch1 = rtb_Integrator_g;
    } else {
      // Switch: '<S1>/Switch1' incorporates:
      //   Constant: '<S1>/Constant1'

      TRACTION_CONTROL_B.Switch1 = 0.0;
    }

    // End of Switch: '<S1>/Switch1'

    // Product: '<S109>/PProd Out'
    rtb_Integrator_g = TRACTION_CONTROL_B.Switch1 * rtu_TCSPIDConfig[0];

    // Product: '<S98>/DProd Out'
    rtb_Integrator_k = TRACTION_CONTROL_B.Switch1 * rtu_TCSPIDConfig[2];

    // Product: '<S107>/NProd Out' incorporates:
    //   Constant: '<S4>/Constant'
    //   DiscreteIntegrator: '<S99>/Filter'
    //   Sum: '<S99>/SumD'

    rtb_Switch12 = (rtb_Integrator_k - TRACTION_CONTROL_DW.Filter_DSTATE_k) *
      100.0;

    // Sum: '<S113>/Sum' incorporates:
    //   DiscreteIntegrator: '<S104>/Integrator'

    rtb_Integrator_g = (rtb_Integrator_g +
                        TRACTION_CONTROL_DW.Integrator_DSTATE_n) + rtb_Switch12;

    // Switch: '<S12>/Switch12'
    if (*rtu_useLaunch) {
      // Sum: '<S12>/Subtract5'
      rtb_Subtract8 = *rtu_DriverTorqueAvg - *rtu_launchDeadZone;

      // Switch: '<S12>/Switch11' incorporates:
      //   Switch: '<S12>/Switch17'

      if (rtb_Subtract8 > 0.0) {
        rtb_Subtract8 = *rtu_TorqueInputFR;
      } else if (*rtu_TorqueInputFR > 0.0) {
        // Switch: '<S12>/Switch17' incorporates:
        //   Constant: '<S12>/Constant9'

        rtb_Subtract8 = 0.0;
      } else {
        // Switch: '<S12>/Switch17'
        rtb_Subtract8 = *rtu_TorqueInputFR;
      }

      // End of Switch: '<S12>/Switch11'
    } else {
      rtb_Subtract8 = *rtu_TorqueInputFR;
    }

    // End of Switch: '<S12>/Switch12'

    // Switch: '<S1>/Switch2' incorporates:
    //   Constant: '<S1>/Constant2'
    //   Saturate: '<S111>/Saturation'

    if (rtb_Switch22 > 0.0) {
      // Saturate: '<S111>/Saturation'
      if (rtb_Integrator_g > 20.0) {
        tmp = 20.0;
      } else if (rtb_Integrator_g < 0.0) {
        tmp = 0.0;
      } else {
        tmp = rtb_Integrator_g;
      }
    } else {
      tmp = 0.0;
    }

    // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
    //   Switch: '<S1>/Switch2'

    TRACTION_CONTROL_MATLABFunction(tmp, rtb_Subtract8,
      &TRACTION_CONTROL_B.adjusted_TCS_PID_Output_l);

    // Sum: '<S1>/Add1'
    *rty_TCSTorqueFR = rtb_Subtract8 -
      TRACTION_CONTROL_B.adjusted_TCS_PID_Output_l;

    // Switch: '<S1>/Switch25'
    *rty_TCSStatusFR = (TRACTION_CONTROL_B.adjusted_TCS_PID_Output_l > 0.0);

    // DeadZone: '<S97>/DeadZone'
    if (rtb_Integrator_g > 20.0) {
      rtb_Integrator_g -= 20.0;
    } else if (rtb_Integrator_g >= 0.0) {
      rtb_Integrator_g = 0.0;
    }

    // End of DeadZone: '<S97>/DeadZone'

    // Product: '<S101>/IProd Out'
    rtb_Integrator_k = TRACTION_CONTROL_B.Switch1 * rtu_TCSPIDConfig[1];

    // Switch: '<S95>/Switch1' incorporates:
    //   Constant: '<S95>/Clamping_zero'
    //   Constant: '<S95>/Constant'
    //   Constant: '<S95>/Constant2'
    //   RelationalOperator: '<S95>/fix for DT propagation issue'

    if (rtb_Integrator_g > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    // Switch: '<S95>/Switch2' incorporates:
    //   Constant: '<S95>/Clamping_zero'
    //   Constant: '<S95>/Constant3'
    //   Constant: '<S95>/Constant4'
    //   RelationalOperator: '<S95>/fix for DT propagation issue1'

    if (rtb_Integrator_k > 0.0) {
      tmp_1 = 1;
    } else {
      tmp_1 = -1;
    }

    // Switch: '<S95>/Switch' incorporates:
    //   Constant: '<S95>/Clamping_zero'
    //   Constant: '<S95>/Constant1'
    //   Logic: '<S95>/AND3'
    //   RelationalOperator: '<S95>/Equal1'
    //   RelationalOperator: '<S95>/Relational Operator'
    //   Switch: '<S95>/Switch1'
    //   Switch: '<S95>/Switch2'

    if ((rtb_Integrator_g != 0.0) && (tmp_0 == tmp_1)) {
      rtb_Subtract8 = 0.0;
    } else {
      rtb_Subtract8 = rtb_Integrator_k;
    }

    // End of Switch: '<S95>/Switch'

    // Switch: '<S17>/Switch28'
    if (*rtu_useLaunch) {
      rtb_Integrator_g = *rtu_LaunchVelThreshold;
    } else {
      rtb_Integrator_g = *rtu_TCSVelThreshold;
    }

    // End of Switch: '<S17>/Switch28'

    // Switch: '<S17>/Switch29' incorporates:
    //   Constant: '<S17>/Constant23'
    //   Sum: '<S17>/Subtract9'

    if (rtb_IProdOut - rtb_Integrator_g > 0.0) {
      // Sum: '<S1>/Subtract2'
      rtb_Integrator_k = *rtu_SLRL - rtb_Switch8;
    } else {
      rtb_Integrator_k = 0.0;
    }

    // End of Switch: '<S17>/Switch29'

    // Switch: '<S1>/Switch3'
    if (rtb_Integrator_k > 0.0) {
      // Switch: '<S1>/Switch3'
      TRACTION_CONTROL_B.Switch3 = rtb_Integrator_k;
    } else {
      // Switch: '<S1>/Switch3' incorporates:
      //   Constant: '<S1>/Constant3'

      TRACTION_CONTROL_B.Switch3 = 0.0;
    }

    // End of Switch: '<S1>/Switch3'

    // Product: '<S160>/PProd Out'
    rtb_Integrator_k = TRACTION_CONTROL_B.Switch3 * rtu_TCSPIDConfig[0];

    // Product: '<S149>/DProd Out'
    rtb_DeadZone_g = TRACTION_CONTROL_B.Switch3 * rtu_TCSPIDConfig[2];

    // Product: '<S158>/NProd Out' incorporates:
    //   Constant: '<S5>/Constant'
    //   DiscreteIntegrator: '<S150>/Filter'
    //   Sum: '<S150>/SumD'

    rtb_Integrator_g = (rtb_DeadZone_g - TRACTION_CONTROL_DW.Filter_DSTATE_a) *
      100.0;

    // Sum: '<S164>/Sum' incorporates:
    //   DiscreteIntegrator: '<S155>/Integrator'

    rtb_Integrator_k = (rtb_Integrator_k +
                        TRACTION_CONTROL_DW.Integrator_DSTATE_h) +
      rtb_Integrator_g;

    // Switch: '<S13>/Switch12'
    if (*rtu_useLaunch) {
      // Sum: '<S13>/Subtract5'
      rtb_Switch12_d = *rtu_DriverTorqueAvg - *rtu_launchDeadZone;

      // Switch: '<S13>/Switch11' incorporates:
      //   Switch: '<S13>/Switch17'

      if (rtb_Switch12_d > 0.0) {
        rtb_Switch12_d = *rtu_TorqueInputRL;
      } else if (*rtu_TorqueInputRL > 0.0) {
        // Switch: '<S13>/Switch17' incorporates:
        //   Constant: '<S13>/Constant9'

        rtb_Switch12_d = 0.0;
      } else {
        // Switch: '<S13>/Switch17'
        rtb_Switch12_d = *rtu_TorqueInputRL;
      }

      // End of Switch: '<S13>/Switch11'
    } else {
      rtb_Switch12_d = *rtu_TorqueInputRL;
    }

    // End of Switch: '<S13>/Switch12'

    // Switch: '<S1>/Switch5' incorporates:
    //   Constant: '<S1>/Constant5'
    //   Saturate: '<S162>/Saturation'

    if (rtb_Switch22 > 0.0) {
      // Saturate: '<S162>/Saturation'
      if (rtb_Integrator_k > 20.0) {
        tmp = 20.0;
      } else if (rtb_Integrator_k < 0.0) {
        tmp = 0.0;
      } else {
        tmp = rtb_Integrator_k;
      }
    } else {
      tmp = 0.0;
    }

    // MATLAB Function: '<S1>/MATLAB Function2' incorporates:
    //   Switch: '<S1>/Switch5'

    TRACTION_CONTROL_MATLABFunction(tmp, rtb_Switch12_d,
      &TRACTION_CONTROL_B.adjusted_TCS_PID_Output_c);

    // Sum: '<S1>/Add2'
    *rty_TCSTorqueRL = rtb_Switch12_d -
      TRACTION_CONTROL_B.adjusted_TCS_PID_Output_c;

    // Switch: '<S1>/Switch26'
    *rty_TCSStatusRL = (TRACTION_CONTROL_B.adjusted_TCS_PID_Output_c > 0.0);

    // DeadZone: '<S148>/DeadZone'
    if (rtb_Integrator_k > 20.0) {
      rtb_Integrator_k -= 20.0;
    } else if (rtb_Integrator_k >= 0.0) {
      rtb_Integrator_k = 0.0;
    }

    // End of DeadZone: '<S148>/DeadZone'

    // Product: '<S152>/IProd Out'
    rtb_DeadZone_g = TRACTION_CONTROL_B.Switch3 * rtu_TCSPIDConfig[1];

    // Switch: '<S146>/Switch1' incorporates:
    //   Constant: '<S146>/Clamping_zero'
    //   Constant: '<S146>/Constant'
    //   Constant: '<S146>/Constant2'
    //   RelationalOperator: '<S146>/fix for DT propagation issue'

    if (rtb_Integrator_k > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    // Switch: '<S146>/Switch2' incorporates:
    //   Constant: '<S146>/Clamping_zero'
    //   Constant: '<S146>/Constant3'
    //   Constant: '<S146>/Constant4'
    //   RelationalOperator: '<S146>/fix for DT propagation issue1'

    if (rtb_DeadZone_g > 0.0) {
      tmp_1 = 1;
    } else {
      tmp_1 = -1;
    }

    // Switch: '<S146>/Switch' incorporates:
    //   Constant: '<S146>/Clamping_zero'
    //   Constant: '<S146>/Constant1'
    //   Logic: '<S146>/AND3'
    //   RelationalOperator: '<S146>/Equal1'
    //   RelationalOperator: '<S146>/Relational Operator'
    //   Switch: '<S146>/Switch1'
    //   Switch: '<S146>/Switch2'

    if ((rtb_Integrator_k != 0.0) && (tmp_0 == tmp_1)) {
      rtb_Switch12_d = 0.0;
    } else {
      rtb_Switch12_d = rtb_DeadZone_g;
    }

    // End of Switch: '<S146>/Switch'

    // Switch: '<S18>/Switch28'
    if (*rtu_useLaunch) {
      rtb_Integrator_k = *rtu_LaunchVelThreshold;
    } else {
      rtb_Integrator_k = *rtu_TCSVelThreshold;
    }

    // End of Switch: '<S18>/Switch28'

    // Switch: '<S18>/Switch29' incorporates:
    //   Constant: '<S18>/Constant23'
    //   Sum: '<S18>/Subtract9'

    if (rtb_IProdOut - rtb_Integrator_k > 0.0) {
      // Sum: '<S1>/Subtract3'
      rtb_DeadZone_g = *rtu_SLRR - rtb_Switch8;
    } else {
      rtb_DeadZone_g = 0.0;
    }

    // End of Switch: '<S18>/Switch29'

    // Switch: '<S1>/Switch6'
    if (rtb_DeadZone_g > 0.0) {
      // Switch: '<S1>/Switch6'
      TRACTION_CONTROL_B.Switch6 = rtb_DeadZone_g;
    } else {
      // Switch: '<S1>/Switch6' incorporates:
      //   Constant: '<S1>/Constant6'

      TRACTION_CONTROL_B.Switch6 = 0.0;
    }

    // End of Switch: '<S1>/Switch6'

    // Product: '<S211>/PProd Out'
    rtb_DeadZone_g = TRACTION_CONTROL_B.Switch6 * rtu_TCSPIDConfig[0];

    // Product: '<S200>/DProd Out'
    rtb_IProdOut = TRACTION_CONTROL_B.Switch6 * rtu_TCSPIDConfig[2];

    // Product: '<S209>/NProd Out' incorporates:
    //   Constant: '<S6>/Constant'
    //   DiscreteIntegrator: '<S201>/Filter'
    //   Sum: '<S201>/SumD'

    rtb_Switch8 = (rtb_IProdOut - TRACTION_CONTROL_DW.Filter_DSTATE_i) * 100.0;

    // Sum: '<S215>/Sum' incorporates:
    //   DiscreteIntegrator: '<S206>/Integrator'

    rtb_DeadZone_g = (rtb_DeadZone_g + TRACTION_CONTROL_DW.Integrator_DSTATE_e)
      + rtb_Switch8;

    // Switch: '<S14>/Switch12'
    if (*rtu_useLaunch) {
      // Sum: '<S14>/Subtract5'
      rtb_IProdOut = *rtu_DriverTorqueAvg - *rtu_launchDeadZone;

      // Switch: '<S14>/Switch11' incorporates:
      //   Switch: '<S14>/Switch17'

      if (rtb_IProdOut > 0.0) {
        rtb_IProdOut = *rtu_TorqueInputRR;
      } else if (*rtu_TorqueInputRR > 0.0) {
        // Switch: '<S14>/Switch17' incorporates:
        //   Constant: '<S14>/Constant9'

        rtb_IProdOut = 0.0;
      } else {
        // Switch: '<S14>/Switch17'
        rtb_IProdOut = *rtu_TorqueInputRR;
      }

      // End of Switch: '<S14>/Switch11'
    } else {
      rtb_IProdOut = *rtu_TorqueInputRR;
    }

    // End of Switch: '<S14>/Switch12'

    // Switch: '<S1>/Switch7' incorporates:
    //   Constant: '<S1>/Constant7'
    //   Saturate: '<S213>/Saturation'

    if (rtb_Switch22 > 0.0) {
      // Saturate: '<S213>/Saturation'
      if (rtb_DeadZone_g > 20.0) {
        tmp = 20.0;
      } else if (rtb_DeadZone_g < 0.0) {
        tmp = 0.0;
      } else {
        tmp = rtb_DeadZone_g;
      }
    } else {
      tmp = 0.0;
    }

    // MATLAB Function: '<S1>/MATLAB Function3' incorporates:
    //   Switch: '<S1>/Switch7'

    TRACTION_CONTROL_MATLABFunction(tmp, rtb_IProdOut,
      &TRACTION_CONTROL_B.adjusted_TCS_PID_Output);

    // Sum: '<S1>/Add3'
    *rty_TCSTorqueRR = rtb_IProdOut - TRACTION_CONTROL_B.adjusted_TCS_PID_Output;

    // Switch: '<S1>/Switch27'
    *rty_TCSStatusRR = (TRACTION_CONTROL_B.adjusted_TCS_PID_Output > 0.0);

    // DeadZone: '<S199>/DeadZone'
    if (rtb_DeadZone_g > 20.0) {
      rtb_DeadZone_g -= 20.0;
    } else if (rtb_DeadZone_g >= 0.0) {
      rtb_DeadZone_g = 0.0;
    }

    // End of DeadZone: '<S199>/DeadZone'

    // Product: '<S203>/IProd Out'
    rtb_IProdOut = TRACTION_CONTROL_B.Switch6 * rtu_TCSPIDConfig[1];

    // Switch: '<S197>/Switch1' incorporates:
    //   Constant: '<S197>/Clamping_zero'
    //   Constant: '<S197>/Constant'
    //   Constant: '<S197>/Constant2'
    //   RelationalOperator: '<S197>/fix for DT propagation issue'

    if (rtb_DeadZone_g > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    // Switch: '<S197>/Switch2' incorporates:
    //   Constant: '<S197>/Clamping_zero'
    //   Constant: '<S197>/Constant3'
    //   Constant: '<S197>/Constant4'
    //   RelationalOperator: '<S197>/fix for DT propagation issue1'

    if (rtb_IProdOut > 0.0) {
      tmp_1 = 1;
    } else {
      tmp_1 = -1;
    }

    // Switch: '<S197>/Switch' incorporates:
    //   Constant: '<S197>/Clamping_zero'
    //   Constant: '<S197>/Constant1'
    //   Logic: '<S197>/AND3'
    //   RelationalOperator: '<S197>/Equal1'
    //   RelationalOperator: '<S197>/Relational Operator'
    //   Switch: '<S197>/Switch1'
    //   Switch: '<S197>/Switch2'

    if ((rtb_DeadZone_g != 0.0) && (tmp_0 == tmp_1)) {
      rtb_Switch22 = 0.0;
    } else {
      rtb_Switch22 = rtb_IProdOut;
    }

    // End of Switch: '<S197>/Switch'

    // DeadZone: '<S46>/DeadZone'
    if (rtb_Subtract5_l > 20.0) {
      rtb_Subtract5_l -= 20.0;
    } else if (rtb_Subtract5_l >= 0.0) {
      rtb_Subtract5_l = 0.0;
    }

    // End of DeadZone: '<S46>/DeadZone'

    // Product: '<S50>/IProd Out'
    rtb_IProdOut = TRACTION_CONTROL_B.Switch * rtu_TCSPIDConfig[1];

    // Switch: '<S44>/Switch1' incorporates:
    //   Constant: '<S44>/Clamping_zero'
    //   Constant: '<S44>/Constant'
    //   Constant: '<S44>/Constant2'
    //   RelationalOperator: '<S44>/fix for DT propagation issue'

    if (rtb_Subtract5_l > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    // Switch: '<S44>/Switch2' incorporates:
    //   Constant: '<S44>/Clamping_zero'
    //   Constant: '<S44>/Constant3'
    //   Constant: '<S44>/Constant4'
    //   RelationalOperator: '<S44>/fix for DT propagation issue1'

    if (rtb_IProdOut > 0.0) {
      tmp_1 = 1;
    } else {
      tmp_1 = -1;
    }

    // Switch: '<S44>/Switch' incorporates:
    //   Constant: '<S44>/Clamping_zero'
    //   Constant: '<S44>/Constant1'
    //   Logic: '<S44>/AND3'
    //   RelationalOperator: '<S44>/Equal1'
    //   RelationalOperator: '<S44>/Relational Operator'
    //   Switch: '<S44>/Switch1'
    //   Switch: '<S44>/Switch2'

    if ((rtb_Subtract5_l != 0.0) && (tmp_0 == tmp_1)) {
      rtb_IProdOut = 0.0;
    }

    // Update for DiscreteIntegrator: '<S53>/Integrator' incorporates:
    //   Switch: '<S44>/Switch'

    TRACTION_CONTROL_DW.Integrator_DSTATE += 0.001 * rtb_IProdOut;
    if (TRACTION_CONTROL_DW.Integrator_DSTATE > 5.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE = 5.0;
    } else if (TRACTION_CONTROL_DW.Integrator_DSTATE < 0.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE = 0.0;
    }

    // End of Update for DiscreteIntegrator: '<S53>/Integrator'

    // Update for DiscreteIntegrator: '<S48>/Filter'
    TRACTION_CONTROL_DW.Filter_DSTATE += 0.001 * rtb_Integrator_l;

    // Update for DiscreteIntegrator: '<S104>/Integrator'
    TRACTION_CONTROL_DW.Integrator_DSTATE_n += 0.001 * rtb_Subtract8;
    if (TRACTION_CONTROL_DW.Integrator_DSTATE_n > 5.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_n = 5.0;
    } else if (TRACTION_CONTROL_DW.Integrator_DSTATE_n < 0.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_n = 0.0;
    }

    // End of Update for DiscreteIntegrator: '<S104>/Integrator'

    // Update for DiscreteIntegrator: '<S99>/Filter'
    TRACTION_CONTROL_DW.Filter_DSTATE_k += 0.001 * rtb_Switch12;

    // Update for DiscreteIntegrator: '<S155>/Integrator'
    TRACTION_CONTROL_DW.Integrator_DSTATE_h += 0.001 * rtb_Switch12_d;
    if (TRACTION_CONTROL_DW.Integrator_DSTATE_h > 5.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_h = 5.0;
    } else if (TRACTION_CONTROL_DW.Integrator_DSTATE_h < 0.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_h = 0.0;
    }

    // End of Update for DiscreteIntegrator: '<S155>/Integrator'

    // Update for DiscreteIntegrator: '<S150>/Filter'
    TRACTION_CONTROL_DW.Filter_DSTATE_a += 0.001 * rtb_Integrator_g;

    // Update for DiscreteIntegrator: '<S206>/Integrator'
    TRACTION_CONTROL_DW.Integrator_DSTATE_e += 0.001 * rtb_Switch22;
    if (TRACTION_CONTROL_DW.Integrator_DSTATE_e > 5.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_e = 5.0;
    } else if (TRACTION_CONTROL_DW.Integrator_DSTATE_e < 0.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_e = 0.0;
    }

    // End of Update for DiscreteIntegrator: '<S206>/Integrator'

    // Update for DiscreteIntegrator: '<S201>/Filter'
    TRACTION_CONTROL_DW.Filter_DSTATE_i += 0.001 * rtb_Switch8;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // SignalConversion generated from: '<S2>/TCS Status FL' incorporates:
    //   Constant: '<S2>/Constant'

    *rty_TCSStatusFL = 0.0;

    // SignalConversion generated from: '<S2>/TCS Status FR' incorporates:
    //   Constant: '<S2>/Constant1'

    *rty_TCSStatusFR = 0.0;

    // SignalConversion generated from: '<S2>/TCS Status RL' incorporates:
    //   Constant: '<S2>/Constant2'

    *rty_TCSStatusRL = 0.0;

    // SignalConversion generated from: '<S2>/TCS Status RR' incorporates:
    //   Constant: '<S2>/Constant3'

    *rty_TCSStatusRR = 0.0;

    // SignalConversion generated from: '<S2>/Torque Input FL'
    *rty_TCSTorqueFL = *rtu_TorqueInputFL;

    // SignalConversion generated from: '<S2>/Torque Input FR'
    *rty_TCSTorqueFR = *rtu_TorqueInputFR;

    // SignalConversion generated from: '<S2>/Torque Input RL'
    *rty_TCSTorqueRL = *rtu_TorqueInputRL;

    // SignalConversion generated from: '<S2>/Torque Input RR'
    *rty_TCSTorqueRR = *rtu_TorqueInputRR;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem1'
  }

  // End of If: '<Root>/If1'

  // SignalConversion generated from: '<Root>/TCS PID Data'
  rty_TCSPIDData[0] = TRACTION_CONTROL_B.Switch;
  rty_TCSPIDData[1] = TRACTION_CONTROL_B.adjusted_TCS_PID_Output_e;
  rty_TCSPIDData[2] = TRACTION_CONTROL_B.Switch1;
  rty_TCSPIDData[3] = TRACTION_CONTROL_B.adjusted_TCS_PID_Output_l;
  rty_TCSPIDData[4] = TRACTION_CONTROL_B.Switch3;
  rty_TCSPIDData[5] = TRACTION_CONTROL_B.adjusted_TCS_PID_Output_c;
  rty_TCSPIDData[6] = TRACTION_CONTROL_B.Switch6;
  rty_TCSPIDData[7] = TRACTION_CONTROL_B.adjusted_TCS_PID_Output;
}

// Model initialize function
void TRACTION_CONTROL::initialize()
{
  // Registration code

  // Initialize DataMapInfo substructure containing ModelMap for C API
  TRACTION_CONTROL_InitializeDataMapInfo((&TRACTION_CONTROL_M),
    &TRACTION_CONTROL_B);
}

// Constructor
TRACTION_CONTROL::TRACTION_CONTROL() :
  TRACTION_CONTROL_B(),
  TRACTION_CONTROL_DW(),
  TRACTION_CONTROL_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
TRACTION_CONTROL::~TRACTION_CONTROL() = default;

// Real-Time Model get method
TRACTION_CONTROL::RT_MODEL_TRACTION_CONTROL_T * TRACTION_CONTROL::getRTM()
{
  return (&TRACTION_CONTROL_M);
}

// member function to set up the C-API information
void TRACTION_CONTROL::setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI,
  const char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  // Initialize Parent model MMI
  if ((rt_ParentMMI != (nullptr)) && (rt_ChildPath != (nullptr))) {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &((&TRACTION_CONTROL_M)
      ->DataMapInfo.mmi));
    rtwCAPI_SetPath((&TRACTION_CONTROL_M)->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex((&TRACTION_CONTROL_M)->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

// member function to setup error status pointer
void TRACTION_CONTROL::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&TRACTION_CONTROL_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
