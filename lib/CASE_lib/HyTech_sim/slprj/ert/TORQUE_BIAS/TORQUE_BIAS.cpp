//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TORQUE_BIAS.cpp
//
// Code generated for Simulink model 'TORQUE_BIAS'.
//
// Model version                  : 1.4
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr 26 00:58:12 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "TORQUE_BIAS.h"
#include "rtwtypes.h"
#include <cmath>
#include "TORQUE_BIAS_capi.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "TORQUE_BIAS_private.h"

// Output and update for referenced model: 'TORQUE_BIAS'
void TORQUE_BIAS::step(const boolean_T *rtu_useTorqueBias, const real_T
  *rtu_ModeConstrainedTorqueReq, const real_T *rtu_DriveTorquePercentFront,
  const real_T *rtu_BrakeTorquePercentFront, const real_T
  *rtu_AbsoluteTorqueLimit, real_T *rty_BiasConstrainedTorqueAvgFro, real_T
  *rty_BiasConstrainedTorqueAvgRea)
{
  // If: '<Root>/If'
  if (*rtu_useTorqueBias) {
    real_T c_Bias_Constrained_Torque_Avg_F;
    real_T rtb_ModeConstrainedTorqueReq;
    real_T u;

    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // MATLAB Function: '<S2>/MATLAB Function'
    if (*rtu_ModeConstrainedTorqueReq < 0.0) {
      c_Bias_Constrained_Torque_Avg_F = *rtu_ModeConstrainedTorqueReq * 4.0 *
        *rtu_BrakeTorquePercentFront / 2.0;
      rtb_ModeConstrainedTorqueReq = *rtu_ModeConstrainedTorqueReq * 4.0 * (1.0
        - *rtu_BrakeTorquePercentFront) / 2.0;
    } else if (*rtu_ModeConstrainedTorqueReq > 0.0) {
      c_Bias_Constrained_Torque_Avg_F = *rtu_ModeConstrainedTorqueReq * 4.0 *
        *rtu_DriveTorquePercentFront / 2.0;
      rtb_ModeConstrainedTorqueReq = *rtu_ModeConstrainedTorqueReq * 4.0 * (1.0
        - *rtu_DriveTorquePercentFront) / 2.0;
    } else {
      c_Bias_Constrained_Torque_Avg_F = 0.0;
      rtb_ModeConstrainedTorqueReq = 0.0;
    }

    if (std::abs(c_Bias_Constrained_Torque_Avg_F) > *rtu_AbsoluteTorqueLimit) {
      u = *rtu_ModeConstrainedTorqueReq;
      if (std::isnan(u)) {
        u = (rtNaN);
      } else if (u < 0.0) {
        u = -1.0;
      } else {
        u = (u > 0.0);
      }

      c_Bias_Constrained_Torque_Avg_F = *rtu_AbsoluteTorqueLimit * u;
    }

    if (std::abs(rtb_ModeConstrainedTorqueReq) > *rtu_AbsoluteTorqueLimit) {
      u = *rtu_ModeConstrainedTorqueReq;
      if (std::isnan(u)) {
        u = (rtNaN);
      } else if (u < 0.0) {
        u = -1.0;
      } else {
        u = (u > 0.0);
      }

      rtb_ModeConstrainedTorqueReq = *rtu_AbsoluteTorqueLimit * u;
    }

    // SignalConversion generated from: '<S2>/Bias Constrained Torque Avg Front' incorporates:
    //   MATLAB Function: '<S2>/MATLAB Function'

    *rty_BiasConstrainedTorqueAvgFro = c_Bias_Constrained_Torque_Avg_F;

    // SignalConversion generated from: '<S2>/Bias Constrained Torque Avg Rear' incorporates:
    //   MATLAB Function: '<S2>/MATLAB Function'

    *rty_BiasConstrainedTorqueAvgRea = rtb_ModeConstrainedTorqueReq;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem1'
  } else {
    real_T rtb_ModeConstrainedTorqueReq;

    // Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
    //   ActionPort: '<S1>/Action Port'

    // SignalConversion generated from: '<S1>/Mode Constrained Torque Req'
    rtb_ModeConstrainedTorqueReq = *rtu_ModeConstrainedTorqueReq;

    // SignalConversion generated from: '<S1>/Bias Constrained Torque Avg Front' 
    *rty_BiasConstrainedTorqueAvgFro = rtb_ModeConstrainedTorqueReq;

    // SignalConversion generated from: '<S1>/Bias Constrained Torque Avg Rear'
    *rty_BiasConstrainedTorqueAvgRea = rtb_ModeConstrainedTorqueReq;

    // End of Outputs for SubSystem: '<Root>/If Action Subsystem'
  }

  // End of If: '<Root>/If'
}

// Model initialize function
void TORQUE_BIAS::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // Initialize DataMapInfo substructure containing ModelMap for C API
  TORQUE_BIAS_InitializeDataMapInfo((&TORQUE_BIAS_M));
}

// Constructor
TORQUE_BIAS::TORQUE_BIAS() :
  TORQUE_BIAS_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
TORQUE_BIAS::~TORQUE_BIAS() = default;

// Real-Time Model get method
TORQUE_BIAS::RT_MODEL_TORQUE_BIAS_T * TORQUE_BIAS::getRTM()
{
  return (&TORQUE_BIAS_M);
}

// member function to set up the C-API information
void TORQUE_BIAS::setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const
  char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  // Initialize Parent model MMI
  if ((rt_ParentMMI != (nullptr)) && (rt_ChildPath != (nullptr))) {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &((&TORQUE_BIAS_M)
      ->DataMapInfo.mmi));
    rtwCAPI_SetPath((&TORQUE_BIAS_M)->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex((&TORQUE_BIAS_M)->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

// member function to setup error status pointer
void TORQUE_BIAS::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&TORQUE_BIAS_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
