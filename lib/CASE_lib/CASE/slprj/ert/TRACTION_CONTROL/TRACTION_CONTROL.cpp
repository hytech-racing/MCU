//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TRACTION_CONTROL.cpp
//
// Code generated for Simulink model 'TRACTION_CONTROL'.
//
// Model version                  : 1.11
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Mon Apr 15 17:38:58 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "TRACTION_CONTROL.h"
#include "rtwtypes.h"
#include "TRACTION_CONTROL_capi.h"
#include "TRACTION_CONTROL_private.h"

// System initialize for referenced model: 'TRACTION_CONTROL'
void TRACTION_CONTROL::init(real_T rty_TCSPIDData[8]) const
{
  // SystemInitialize for SignalConversion generated from: '<Root>/TCS PID Data' 
  rty_TCSPIDData[0] = TRACTION_CONTROL_B.Switch;
  rty_TCSPIDData[1] = TRACTION_CONTROL_B.Switch4;
  rty_TCSPIDData[2] = TRACTION_CONTROL_B.Switch1;
  rty_TCSPIDData[3] = TRACTION_CONTROL_B.Switch2;
  rty_TCSPIDData[4] = TRACTION_CONTROL_B.Switch3;
  rty_TCSPIDData[5] = TRACTION_CONTROL_B.Switch5;
  rty_TCSPIDData[6] = TRACTION_CONTROL_B.Switch6;
  rty_TCSPIDData[7] = TRACTION_CONTROL_B.Switch7;
}

// Output and update for referenced model: 'TRACTION_CONTROL'
void TRACTION_CONTROL::step(const real_T *rtu_DriverTorqueAvg, const boolean_T
  *rtu_useTractionControl, const real_T *rtu_TCSThreshold, const real_T
  *rtu_TorqueTVFL, const real_T *rtu_TorqueTVFR, const real_T *rtu_TorqueTVRL,
  const real_T *rtu_TorqueTVRR, const real_T *rtu_SLFL, const real_T *rtu_SLFR,
  const real_T *rtu_SLRL, const real_T *rtu_SLRR, const boolean_T *rtu_useLaunch,
  const real_T *rtu_launchSL, const real_T *rtu_launchDeadZone, const real_T
  rtu_TCSPIDConfig[3], real_T *rty_TCSTorqueFL, real_T *rty_TCSTorqueFR, real_T *
  rty_TCSTorqueRL, real_T *rty_TCSTorqueRR, real_T *rty_TCSStatusFL, real_T
  *rty_TCSStatusFR, real_T *rty_TCSStatusRL, real_T *rty_TCSStatusRR, real_T
  rty_TCSPIDData[8])
{
  // If: '<Root>/If1'
  if (*rtu_useTractionControl) {
    real_T rtb_IProdOut;
    real_T rtb_Integrator_j;
    real_T rtb_Integrator_lj;
    real_T rtb_Integrator_o;
    real_T rtb_NProdOut;
    real_T rtb_Saturation;
    real_T rtb_Subtract4;
    real_T rtb_Subtract5;
    real_T rtb_Switch16;
    int8_T tmp;
    int8_T tmp_0;
    boolean_T rtb_RelationalOperator_g;
    boolean_T rtb_fixforDTpropagationissue_j;

    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
    //   ActionPort: '<S1>/Action Port'

    // Switch: '<S1>/Switch12' incorporates:
    //   Switch: '<S1>/Switch8'

    if (*rtu_useLaunch) {
      // Sum: '<S1>/Subtract5'
      rtb_Subtract5 = *rtu_TorqueTVFL - *rtu_launchDeadZone;

      // Switch: '<S1>/Switch11' incorporates:
      //   Switch: '<S1>/Switch17'

      if (rtb_Subtract5 > 0.0) {
        rtb_Integrator_o = *rtu_TorqueTVFL;
      } else if (*rtu_TorqueTVFL > 0.0) {
        // Switch: '<S1>/Switch17' incorporates:
        //   Constant: '<S1>/Constant9'

        rtb_Integrator_o = 0.0;
      } else {
        // Switch: '<S1>/Switch17'
        rtb_Integrator_o = *rtu_TorqueTVFL;
      }

      // End of Switch: '<S1>/Switch11'
      rtb_Saturation = *rtu_launchSL;
    } else {
      rtb_Integrator_o = *rtu_TorqueTVFL;
      rtb_Saturation = *rtu_TCSThreshold;
    }

    // End of Switch: '<S1>/Switch12'

    // Sum: '<S1>/Subtract'
    rtb_Subtract5 = *rtu_SLFL - rtb_Saturation;

    // Switch: '<S1>/Switch'
    if (rtb_Subtract5 > 0.0) {
      // Switch: '<S1>/Switch'
      TRACTION_CONTROL_B.Switch = rtb_Subtract5;
    } else {
      // Switch: '<S1>/Switch' incorporates:
      //   Constant: '<S1>/Constant'

      TRACTION_CONTROL_B.Switch = 0.0;
    }

    // End of Switch: '<S1>/Switch'

    // Product: '<S46>/PProd Out'
    rtb_Subtract5 = TRACTION_CONTROL_B.Switch * rtu_TCSPIDConfig[0];

    // Product: '<S35>/DProd Out'
    rtb_Integrator_lj = TRACTION_CONTROL_B.Switch * rtu_TCSPIDConfig[2];

    // Product: '<S44>/NProd Out' incorporates:
    //   Constant: '<S3>/Constant'
    //   DiscreteIntegrator: '<S36>/Filter'
    //   Sum: '<S36>/SumD'

    rtb_NProdOut = (rtb_Integrator_lj - TRACTION_CONTROL_DW.Filter_DSTATE) *
      100.0;

    // Sum: '<S50>/Sum' incorporates:
    //   DiscreteIntegrator: '<S41>/Integrator'

    rtb_Subtract5 = (rtb_Subtract5 + TRACTION_CONTROL_DW.Integrator_DSTATE) +
      rtb_NProdOut;

    // Switch: '<S1>/Switch22'
    if (*rtu_useLaunch) {
      // Sum: '<S1>/Subtract8'
      rtb_Integrator_lj = *rtu_DriverTorqueAvg - *rtu_launchDeadZone;

      // Switch: '<S1>/Switch21' incorporates:
      //   Switch: '<S1>/Switch23'

      if (rtb_Integrator_lj > 0.0) {
        rtb_Switch16 = *rtu_DriverTorqueAvg;
      } else if (*rtu_DriverTorqueAvg > 0.0) {
        // Switch: '<S1>/Switch23' incorporates:
        //   Constant: '<S1>/Constant12'

        rtb_Switch16 = 0.0;
      } else {
        // Switch: '<S1>/Switch23'
        rtb_Switch16 = *rtu_DriverTorqueAvg;
      }

      // End of Switch: '<S1>/Switch21'
    } else {
      rtb_Switch16 = *rtu_DriverTorqueAvg;
    }

    // End of Switch: '<S1>/Switch22'

    // Switch: '<S1>/Switch4'
    if (rtb_Switch16 > 0.0) {
      // Saturate: '<S48>/Saturation'
      if (rtb_Subtract5 > 15.0) {
        // Switch: '<S1>/Switch4'
        TRACTION_CONTROL_B.Switch4 = 15.0;
      } else if (rtb_Subtract5 < 0.0) {
        // Switch: '<S1>/Switch4'
        TRACTION_CONTROL_B.Switch4 = 0.0;
      } else {
        // Switch: '<S1>/Switch4'
        TRACTION_CONTROL_B.Switch4 = rtb_Subtract5;
      }
    } else {
      // Switch: '<S1>/Switch4' incorporates:
      //   Constant: '<S1>/Constant4'
      //   Saturate: '<S48>/Saturation'

      TRACTION_CONTROL_B.Switch4 = 0.0;
    }

    // End of Switch: '<S1>/Switch4'

    // Sum: '<S1>/Add'
    *rty_TCSTorqueFL = rtb_Integrator_o - TRACTION_CONTROL_B.Switch4;

    // Switch: '<S1>/Switch24'
    *rty_TCSStatusFL = (TRACTION_CONTROL_B.Switch4 > 0.0);

    // Sum: '<S1>/Subtract1'
    rtb_Integrator_lj = *rtu_SLFR - rtb_Saturation;

    // Switch: '<S1>/Switch1'
    if (rtb_Integrator_lj > 0.0) {
      // Switch: '<S1>/Switch1'
      TRACTION_CONTROL_B.Switch1 = rtb_Integrator_lj;
    } else {
      // Switch: '<S1>/Switch1' incorporates:
      //   Constant: '<S1>/Constant1'

      TRACTION_CONTROL_B.Switch1 = 0.0;
    }

    // End of Switch: '<S1>/Switch1'

    // Product: '<S97>/PProd Out'
    rtb_Integrator_lj = TRACTION_CONTROL_B.Switch1 * rtu_TCSPIDConfig[0];

    // Product: '<S86>/DProd Out'
    rtb_Integrator_j = TRACTION_CONTROL_B.Switch1 * rtu_TCSPIDConfig[2];

    // Product: '<S95>/NProd Out' incorporates:
    //   Constant: '<S4>/Constant'
    //   DiscreteIntegrator: '<S87>/Filter'
    //   Sum: '<S87>/SumD'

    rtb_Integrator_o = (rtb_Integrator_j - TRACTION_CONTROL_DW.Filter_DSTATE_a) *
      100.0;

    // Sum: '<S101>/Sum' incorporates:
    //   DiscreteIntegrator: '<S92>/Integrator'

    rtb_Integrator_lj = (rtb_Integrator_lj +
                         TRACTION_CONTROL_DW.Integrator_DSTATE_i) +
      rtb_Integrator_o;

    // Switch: '<S1>/Switch2'
    if (rtb_Switch16 > 0.0) {
      // Saturate: '<S99>/Saturation'
      if (rtb_Integrator_lj > 15.0) {
        // Switch: '<S1>/Switch2'
        TRACTION_CONTROL_B.Switch2 = 15.0;
      } else if (rtb_Integrator_lj < 0.0) {
        // Switch: '<S1>/Switch2'
        TRACTION_CONTROL_B.Switch2 = 0.0;
      } else {
        // Switch: '<S1>/Switch2'
        TRACTION_CONTROL_B.Switch2 = rtb_Integrator_lj;
      }
    } else {
      // Switch: '<S1>/Switch2' incorporates:
      //   Constant: '<S1>/Constant2'
      //   Saturate: '<S99>/Saturation'

      TRACTION_CONTROL_B.Switch2 = 0.0;
    }

    // End of Switch: '<S1>/Switch2'

    // Switch: '<S1>/Switch10'
    if (*rtu_useLaunch) {
      // Sum: '<S1>/Subtract4'
      rtb_Subtract4 = *rtu_TorqueTVFR - *rtu_launchDeadZone;

      // Switch: '<S1>/Switch9' incorporates:
      //   Switch: '<S1>/Switch18'

      if (rtb_Subtract4 > 0.0) {
        rtb_Integrator_j = *rtu_TorqueTVFR;
      } else if (*rtu_TorqueTVFR > 0.0) {
        // Switch: '<S1>/Switch18' incorporates:
        //   Constant: '<S1>/Constant8'

        rtb_Integrator_j = 0.0;
      } else {
        // Switch: '<S1>/Switch18'
        rtb_Integrator_j = *rtu_TorqueTVFR;
      }

      // End of Switch: '<S1>/Switch9'
    } else {
      rtb_Integrator_j = *rtu_TorqueTVFR;
    }

    // End of Switch: '<S1>/Switch10'

    // Sum: '<S1>/Add1'
    *rty_TCSTorqueFR = rtb_Integrator_j - TRACTION_CONTROL_B.Switch2;

    // Switch: '<S1>/Switch25'
    *rty_TCSStatusFR = (TRACTION_CONTROL_B.Switch2 > 0.0);

    // DeadZone: '<S85>/DeadZone'
    if (rtb_Integrator_lj > 15.0) {
      rtb_Integrator_lj -= 15.0;
    } else if (rtb_Integrator_lj >= 0.0) {
      rtb_Integrator_lj = 0.0;
    }

    // End of DeadZone: '<S85>/DeadZone'

    // Product: '<S89>/IProd Out'
    rtb_Integrator_j = TRACTION_CONTROL_B.Switch1 * rtu_TCSPIDConfig[1];

    // Switch: '<S83>/Switch1' incorporates:
    //   Constant: '<S83>/Clamping_zero'
    //   Constant: '<S83>/Constant'
    //   Constant: '<S83>/Constant2'
    //   RelationalOperator: '<S83>/fix for DT propagation issue'

    if (rtb_Integrator_lj > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    // Switch: '<S83>/Switch2' incorporates:
    //   Constant: '<S83>/Clamping_zero'
    //   Constant: '<S83>/Constant3'
    //   Constant: '<S83>/Constant4'
    //   RelationalOperator: '<S83>/fix for DT propagation issue1'

    if (rtb_Integrator_j > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    // Switch: '<S83>/Switch' incorporates:
    //   Constant: '<S83>/Clamping_zero'
    //   Constant: '<S83>/Constant1'
    //   Logic: '<S83>/AND3'
    //   RelationalOperator: '<S83>/Equal1'
    //   RelationalOperator: '<S83>/Relational Operator'
    //   Switch: '<S83>/Switch1'
    //   Switch: '<S83>/Switch2'

    if ((rtb_Integrator_lj != 0.0) && (tmp == tmp_0)) {
      rtb_Integrator_lj = 0.0;
    } else {
      rtb_Integrator_lj = rtb_Integrator_j;
    }

    // End of Switch: '<S83>/Switch'

    // Sum: '<S1>/Subtract2'
    rtb_Integrator_j = *rtu_SLRL - rtb_Saturation;

    // Switch: '<S1>/Switch3'
    if (rtb_Integrator_j > 0.0) {
      // Switch: '<S1>/Switch3'
      TRACTION_CONTROL_B.Switch3 = rtb_Integrator_j;
    } else {
      // Switch: '<S1>/Switch3' incorporates:
      //   Constant: '<S1>/Constant3'

      TRACTION_CONTROL_B.Switch3 = 0.0;
    }

    // End of Switch: '<S1>/Switch3'

    // Product: '<S148>/PProd Out'
    rtb_Integrator_j = TRACTION_CONTROL_B.Switch3 * rtu_TCSPIDConfig[0];

    // Product: '<S137>/DProd Out'
    rtb_IProdOut = TRACTION_CONTROL_B.Switch3 * rtu_TCSPIDConfig[2];

    // Product: '<S146>/NProd Out' incorporates:
    //   Constant: '<S5>/Constant'
    //   DiscreteIntegrator: '<S138>/Filter'
    //   Sum: '<S138>/SumD'

    rtb_Subtract4 = (rtb_IProdOut - TRACTION_CONTROL_DW.Filter_DSTATE_b) * 100.0;

    // Sum: '<S152>/Sum' incorporates:
    //   DiscreteIntegrator: '<S143>/Integrator'

    rtb_Integrator_j = (rtb_Integrator_j +
                        TRACTION_CONTROL_DW.Integrator_DSTATE_ir) +
      rtb_Subtract4;

    // Switch: '<S1>/Switch5'
    if (rtb_Switch16 > 0.0) {
      // Saturate: '<S150>/Saturation'
      if (rtb_Integrator_j > 15.0) {
        // Switch: '<S1>/Switch5'
        TRACTION_CONTROL_B.Switch5 = 15.0;
      } else if (rtb_Integrator_j < 0.0) {
        // Switch: '<S1>/Switch5'
        TRACTION_CONTROL_B.Switch5 = 0.0;
      } else {
        // Switch: '<S1>/Switch5'
        TRACTION_CONTROL_B.Switch5 = rtb_Integrator_j;
      }
    } else {
      // Switch: '<S1>/Switch5' incorporates:
      //   Constant: '<S1>/Constant5'
      //   Saturate: '<S150>/Saturation'

      TRACTION_CONTROL_B.Switch5 = 0.0;
    }

    // End of Switch: '<S1>/Switch5'

    // Switch: '<S1>/Switch14'
    if (*rtu_useLaunch) {
      // Sum: '<S1>/Subtract6'
      rtb_IProdOut = *rtu_TorqueTVRL - *rtu_launchDeadZone;

      // Switch: '<S1>/Switch13' incorporates:
      //   Switch: '<S1>/Switch19'

      if (rtb_IProdOut > 0.0) {
        rtb_IProdOut = *rtu_TorqueTVRL;
      } else if (*rtu_TorqueTVRL > 0.0) {
        // Switch: '<S1>/Switch19' incorporates:
        //   Constant: '<S1>/Constant10'

        rtb_IProdOut = 0.0;
      } else {
        // Switch: '<S1>/Switch19'
        rtb_IProdOut = *rtu_TorqueTVRL;
      }

      // End of Switch: '<S1>/Switch13'
    } else {
      rtb_IProdOut = *rtu_TorqueTVRL;
    }

    // End of Switch: '<S1>/Switch14'

    // Sum: '<S1>/Add2'
    *rty_TCSTorqueRL = rtb_IProdOut - TRACTION_CONTROL_B.Switch5;

    // Switch: '<S1>/Switch26'
    *rty_TCSStatusRL = (TRACTION_CONTROL_B.Switch5 > 0.0);

    // DeadZone: '<S136>/DeadZone'
    if (rtb_Integrator_j > 15.0) {
      rtb_Integrator_j -= 15.0;
    } else if (rtb_Integrator_j >= 0.0) {
      rtb_Integrator_j = 0.0;
    }

    // End of DeadZone: '<S136>/DeadZone'

    // Product: '<S140>/IProd Out'
    rtb_IProdOut = TRACTION_CONTROL_B.Switch3 * rtu_TCSPIDConfig[1];

    // Switch: '<S134>/Switch1' incorporates:
    //   Constant: '<S134>/Clamping_zero'
    //   Constant: '<S134>/Constant'
    //   Constant: '<S134>/Constant2'
    //   RelationalOperator: '<S134>/fix for DT propagation issue'

    if (rtb_Integrator_j > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    // Switch: '<S134>/Switch2' incorporates:
    //   Constant: '<S134>/Clamping_zero'
    //   Constant: '<S134>/Constant3'
    //   Constant: '<S134>/Constant4'
    //   RelationalOperator: '<S134>/fix for DT propagation issue1'

    if (rtb_IProdOut > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    // Switch: '<S134>/Switch' incorporates:
    //   Constant: '<S134>/Clamping_zero'
    //   Constant: '<S134>/Constant1'
    //   Logic: '<S134>/AND3'
    //   RelationalOperator: '<S134>/Equal1'
    //   RelationalOperator: '<S134>/Relational Operator'
    //   Switch: '<S134>/Switch1'
    //   Switch: '<S134>/Switch2'

    if ((rtb_Integrator_j != 0.0) && (tmp == tmp_0)) {
      rtb_Integrator_j = 0.0;
    } else {
      rtb_Integrator_j = rtb_IProdOut;
    }

    // End of Switch: '<S134>/Switch'

    // Sum: '<S1>/Subtract3'
    rtb_Saturation = *rtu_SLRR - rtb_Saturation;

    // Switch: '<S1>/Switch6'
    if (rtb_Saturation > 0.0) {
      // Switch: '<S1>/Switch6'
      TRACTION_CONTROL_B.Switch6 = rtb_Saturation;
    } else {
      // Switch: '<S1>/Switch6' incorporates:
      //   Constant: '<S1>/Constant6'

      TRACTION_CONTROL_B.Switch6 = 0.0;
    }

    // End of Switch: '<S1>/Switch6'

    // Product: '<S199>/PProd Out'
    rtb_IProdOut = TRACTION_CONTROL_B.Switch6 * rtu_TCSPIDConfig[0];

    // Product: '<S188>/DProd Out'
    rtb_Saturation = TRACTION_CONTROL_B.Switch6 * rtu_TCSPIDConfig[2];

    // Product: '<S197>/NProd Out' incorporates:
    //   Constant: '<S6>/Constant'
    //   DiscreteIntegrator: '<S189>/Filter'
    //   Sum: '<S189>/SumD'

    rtb_Saturation = (rtb_Saturation - TRACTION_CONTROL_DW.Filter_DSTATE_m) *
      100.0;

    // Sum: '<S203>/Sum' incorporates:
    //   DiscreteIntegrator: '<S194>/Integrator'

    rtb_IProdOut = (rtb_IProdOut + TRACTION_CONTROL_DW.Integrator_DSTATE_p) +
      rtb_Saturation;

    // Switch: '<S1>/Switch7'
    if (rtb_Switch16 > 0.0) {
      // Saturate: '<S201>/Saturation'
      if (rtb_IProdOut > 15.0) {
        // Switch: '<S1>/Switch7'
        TRACTION_CONTROL_B.Switch7 = 15.0;
      } else if (rtb_IProdOut < 0.0) {
        // Switch: '<S1>/Switch7'
        TRACTION_CONTROL_B.Switch7 = 0.0;
      } else {
        // Switch: '<S1>/Switch7'
        TRACTION_CONTROL_B.Switch7 = rtb_IProdOut;
      }
    } else {
      // Switch: '<S1>/Switch7' incorporates:
      //   Constant: '<S1>/Constant7'
      //   Saturate: '<S201>/Saturation'

      TRACTION_CONTROL_B.Switch7 = 0.0;
    }

    // End of Switch: '<S1>/Switch7'

    // Switch: '<S1>/Switch16'
    if (*rtu_useLaunch) {
      // Sum: '<S1>/Subtract7'
      rtb_Switch16 = *rtu_TorqueTVRR - *rtu_launchDeadZone;

      // Switch: '<S1>/Switch15' incorporates:
      //   Switch: '<S1>/Switch20'

      if (rtb_Switch16 > 0.0) {
        rtb_Switch16 = *rtu_TorqueTVRR;
      } else if (*rtu_TorqueTVRR > 0.0) {
        // Switch: '<S1>/Switch20' incorporates:
        //   Constant: '<S1>/Constant11'

        rtb_Switch16 = 0.0;
      } else {
        // Switch: '<S1>/Switch20'
        rtb_Switch16 = *rtu_TorqueTVRR;
      }

      // End of Switch: '<S1>/Switch15'
    } else {
      rtb_Switch16 = *rtu_TorqueTVRR;
    }

    // End of Switch: '<S1>/Switch16'

    // Sum: '<S1>/Add3'
    *rty_TCSTorqueRR = rtb_Switch16 - TRACTION_CONTROL_B.Switch7;

    // Switch: '<S1>/Switch27'
    *rty_TCSStatusRR = (TRACTION_CONTROL_B.Switch7 > 0.0);

    // DeadZone: '<S187>/DeadZone'
    if (rtb_IProdOut > 15.0) {
      rtb_IProdOut -= 15.0;
    } else if (rtb_IProdOut >= 0.0) {
      rtb_IProdOut = 0.0;
    }

    // End of DeadZone: '<S187>/DeadZone'

    // RelationalOperator: '<S185>/Relational Operator' incorporates:
    //   Constant: '<S185>/Clamping_zero'

    rtb_RelationalOperator_g = (rtb_IProdOut != 0.0);

    // RelationalOperator: '<S185>/fix for DT propagation issue' incorporates:
    //   Constant: '<S185>/Clamping_zero'

    rtb_fixforDTpropagationissue_j = (rtb_IProdOut > 0.0);

    // Product: '<S191>/IProd Out'
    rtb_IProdOut = TRACTION_CONTROL_B.Switch6 * rtu_TCSPIDConfig[1];

    // Switch: '<S185>/Switch1' incorporates:
    //   Constant: '<S185>/Constant'
    //   Constant: '<S185>/Constant2'

    if (rtb_fixforDTpropagationissue_j) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    // Switch: '<S185>/Switch2' incorporates:
    //   Constant: '<S185>/Clamping_zero'
    //   Constant: '<S185>/Constant3'
    //   Constant: '<S185>/Constant4'
    //   RelationalOperator: '<S185>/fix for DT propagation issue1'

    if (rtb_IProdOut > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    // Switch: '<S185>/Switch' incorporates:
    //   Constant: '<S185>/Constant1'
    //   Logic: '<S185>/AND3'
    //   RelationalOperator: '<S185>/Equal1'
    //   Switch: '<S185>/Switch1'
    //   Switch: '<S185>/Switch2'

    if (rtb_RelationalOperator_g && (tmp == tmp_0)) {
      rtb_Switch16 = 0.0;
    } else {
      rtb_Switch16 = rtb_IProdOut;
    }

    // End of Switch: '<S185>/Switch'

    // DeadZone: '<S34>/DeadZone'
    if (rtb_Subtract5 > 15.0) {
      rtb_Subtract5 -= 15.0;
    } else if (rtb_Subtract5 >= 0.0) {
      rtb_Subtract5 = 0.0;
    }

    // End of DeadZone: '<S34>/DeadZone'

    // Product: '<S38>/IProd Out'
    rtb_IProdOut = TRACTION_CONTROL_B.Switch * rtu_TCSPIDConfig[1];

    // Switch: '<S32>/Switch1' incorporates:
    //   Constant: '<S32>/Clamping_zero'
    //   Constant: '<S32>/Constant'
    //   Constant: '<S32>/Constant2'
    //   RelationalOperator: '<S32>/fix for DT propagation issue'

    if (rtb_Subtract5 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    // Switch: '<S32>/Switch2' incorporates:
    //   Constant: '<S32>/Clamping_zero'
    //   Constant: '<S32>/Constant3'
    //   Constant: '<S32>/Constant4'
    //   RelationalOperator: '<S32>/fix for DT propagation issue1'

    if (rtb_IProdOut > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    // Switch: '<S32>/Switch' incorporates:
    //   Constant: '<S32>/Clamping_zero'
    //   Constant: '<S32>/Constant1'
    //   Logic: '<S32>/AND3'
    //   RelationalOperator: '<S32>/Equal1'
    //   RelationalOperator: '<S32>/Relational Operator'
    //   Switch: '<S32>/Switch1'
    //   Switch: '<S32>/Switch2'

    if ((rtb_Subtract5 != 0.0) && (tmp == tmp_0)) {
      rtb_IProdOut = 0.0;
    }

    // Update for DiscreteIntegrator: '<S41>/Integrator' incorporates:
    //   Switch: '<S32>/Switch'

    TRACTION_CONTROL_DW.Integrator_DSTATE += 0.001 * rtb_IProdOut;
    if (TRACTION_CONTROL_DW.Integrator_DSTATE > 5.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE = 5.0;
    } else if (TRACTION_CONTROL_DW.Integrator_DSTATE < 0.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE = 0.0;
    }

    // End of Update for DiscreteIntegrator: '<S41>/Integrator'

    // Update for DiscreteIntegrator: '<S36>/Filter'
    TRACTION_CONTROL_DW.Filter_DSTATE += 0.001 * rtb_NProdOut;

    // Update for DiscreteIntegrator: '<S92>/Integrator'
    TRACTION_CONTROL_DW.Integrator_DSTATE_i += 0.001 * rtb_Integrator_lj;
    if (TRACTION_CONTROL_DW.Integrator_DSTATE_i > 5.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_i = 5.0;
    } else if (TRACTION_CONTROL_DW.Integrator_DSTATE_i < 0.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_i = 0.0;
    }

    // End of Update for DiscreteIntegrator: '<S92>/Integrator'

    // Update for DiscreteIntegrator: '<S87>/Filter'
    TRACTION_CONTROL_DW.Filter_DSTATE_a += 0.001 * rtb_Integrator_o;

    // Update for DiscreteIntegrator: '<S143>/Integrator'
    TRACTION_CONTROL_DW.Integrator_DSTATE_ir += 0.001 * rtb_Integrator_j;
    if (TRACTION_CONTROL_DW.Integrator_DSTATE_ir > 5.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_ir = 5.0;
    } else if (TRACTION_CONTROL_DW.Integrator_DSTATE_ir < 0.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_ir = 0.0;
    }

    // End of Update for DiscreteIntegrator: '<S143>/Integrator'

    // Update for DiscreteIntegrator: '<S138>/Filter'
    TRACTION_CONTROL_DW.Filter_DSTATE_b += 0.001 * rtb_Subtract4;

    // Update for DiscreteIntegrator: '<S194>/Integrator'
    TRACTION_CONTROL_DW.Integrator_DSTATE_p += 0.001 * rtb_Switch16;
    if (TRACTION_CONTROL_DW.Integrator_DSTATE_p > 5.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_p = 5.0;
    } else if (TRACTION_CONTROL_DW.Integrator_DSTATE_p < 0.0) {
      TRACTION_CONTROL_DW.Integrator_DSTATE_p = 0.0;
    }

    // End of Update for DiscreteIntegrator: '<S194>/Integrator'

    // Update for DiscreteIntegrator: '<S189>/Filter'
    TRACTION_CONTROL_DW.Filter_DSTATE_m += 0.001 * rtb_Saturation;

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

    // SignalConversion generated from: '<S2>/Torque TV FL'
    *rty_TCSTorqueFL = *rtu_TorqueTVFL;

    // SignalConversion generated from: '<S2>/Torque TV FR'
    *rty_TCSTorqueFR = *rtu_TorqueTVFR;

    // SignalConversion generated from: '<S2>/Torque TV RL'
    *rty_TCSTorqueRL = *rtu_TorqueTVRL;

    // SignalConversion generated from: '<S2>/Torque TV RR'
    *rty_TCSTorqueRR = *rtu_TorqueTVRR;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem1'
  }

  // End of If: '<Root>/If1'

  // SignalConversion generated from: '<Root>/TCS PID Data'
  rty_TCSPIDData[0] = TRACTION_CONTROL_B.Switch;
  rty_TCSPIDData[1] = TRACTION_CONTROL_B.Switch4;
  rty_TCSPIDData[2] = TRACTION_CONTROL_B.Switch1;
  rty_TCSPIDData[3] = TRACTION_CONTROL_B.Switch2;
  rty_TCSPIDData[4] = TRACTION_CONTROL_B.Switch3;
  rty_TCSPIDData[5] = TRACTION_CONTROL_B.Switch5;
  rty_TCSPIDData[6] = TRACTION_CONTROL_B.Switch6;
  rty_TCSPIDData[7] = TRACTION_CONTROL_B.Switch7;
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
