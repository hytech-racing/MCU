//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: POWER_LIMIT.h
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
#ifndef RTW_HEADER_POWER_LIMIT_h_
#define RTW_HEADER_POWER_LIMIT_h_
#include "rtwtypes.h"
#include "POWER_LIMIT_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "rtGetNaN.h"
#include "rtw_modelmap.h"
#include <cstring>

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  POWER_LIMIT_GetCAPIStaticMap(void);

// Class declaration for model POWER_LIMIT
class POWER_LIMIT final
{
  // public data and function members
 public:
  // Block signals for model 'POWER_LIMIT'
  struct B_POWER_LIMIT_T {
    real_T cornerPower_FL;             // '<S5>/MATLAB Function'
    real_T cornerPower_FR;             // '<S5>/MATLAB Function'
    real_T cornerPower_RL;             // '<S5>/MATLAB Function'
    real_T cornerPower_RR;             // '<S5>/MATLAB Function'
  };

  // Block states (default storage) for model 'POWER_LIMIT'
  struct DW_POWER_LIMIT_T {
    real_T Integrator_DSTATE;          // '<S42>/Integrator'
    real_T Filter_DSTATE;              // '<S37>/Filter'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_POWER_LIMIT_T {
    const char_T **errorStatus;

    //
    //  DataMapInfo:
    //  The following substructure contains information regarding
    //  structures generated in the model's C API.

    struct {
      rtwCAPI_ModelMappingInfo mmi;
      void* dataAddress[8];
      int32_T* vardimsAddress[8];
      RTWLoggingFcnPtr loggingPtrs[8];
    } DataMapInfo;
  };

  // model initialize function
  void initialize();

  // Copy Constructor
  POWER_LIMIT(POWER_LIMIT const&) = delete;

  // Assignment Operator
  POWER_LIMIT& operator= (POWER_LIMIT const&) & = delete;

  // Move Constructor
  POWER_LIMIT(POWER_LIMIT &&) = delete;

  // Move Assignment Operator
  POWER_LIMIT& operator= (POWER_LIMIT &&) = delete;

  // Real-Time Model get method
  POWER_LIMIT::RT_MODEL_POWER_LIMIT_T * getRTM();

  // member function to set up the C-API information
  void setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T
                     *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx);

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // model step function
  void step(const real_T *rtu_CurrentElectricalPowerkW, const real_T
            *rtu_TorqueInputFL, const real_T *rtu_TorqueInputFR, const real_T
            *rtu_TorqueInputRL, const real_T *rtu_TorqueInputRR, const real_T
            *rtu_WheelOmegaFLrads, const real_T *rtu_WheelOmegaFRrads, const
            real_T *rtu_WheelOmegaRLrads, const real_T *rtu_WheelOmegaRRrads,
            const boolean_T *rtu_usePowerLimit, const boolean_T
            *rtu_usePIDPowerLimit, const real_T *rtu_AbsoluteTorqueLimit, const
            real_T *rtu_MechPowerMaxkW, real_T *rty_PLTorqueFL, real_T
            *rty_PLTorqueFR, real_T *rty_PLTorqueRL, real_T *rty_PLTorqueRR,
            real_T *rty_PowerLimStatus, real_T *rty_PowerLimErrorkW, real_T
            *rty_PowerLimTorqueAdjustment, real_T *rty_CornerPowerFLkW, real_T
            *rty_CornerPowerFRkW, real_T *rty_CornerPowerRLkW, real_T
            *rty_CornerPowerRRkW);

  // Constructor
  POWER_LIMIT();

  // Destructor
  ~POWER_LIMIT();

  // private data and function members
 private:
  // Block signals
  B_POWER_LIMIT_T POWER_LIMIT_B;

  // Block states
  DW_POWER_LIMIT_T POWER_LIMIT_DW;

  // private member function(s) for subsystem '<S5>/MATLAB Function'
  static void POWER_LIMIT_MATLABFunction(real_T rtu_Torque_FL, real_T
    rtu_Torque_FR, real_T rtu_Torque_RL, real_T rtu_Torque_RR, real_T
    rtu_Motor_Omega_FL, real_T rtu_Motor_Omega_FR, real_T rtu_Motor_Omega_RL,
    real_T rtu_Motor_Omega_RR, real_T *rty_cornerPower_FL, real_T
    *rty_cornerPower_FR, real_T *rty_cornerPower_RL, real_T *rty_cornerPower_RR);

  // Real-Time Model
  RT_MODEL_POWER_LIMIT_T POWER_LIMIT_M;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'POWER_LIMIT'
//  '<S1>'   : 'POWER_LIMIT/If Action Subsystem'
//  '<S2>'   : 'POWER_LIMIT/If Action Subsystem1'
//  '<S3>'   : 'POWER_LIMIT/MATLAB Function'
//  '<S4>'   : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem'
//  '<S5>'   : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem1'
//  '<S6>'   : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT'
//  '<S7>'   : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/If Action Subsystem1'
//  '<S8>'   : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT'
//  '<S9>'   : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT/MATLAB Function'
//  '<S10>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller'
//  '<S11>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Anti-windup'
//  '<S12>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/D Gain'
//  '<S13>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Filter'
//  '<S14>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Filter ICs'
//  '<S15>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/I Gain'
//  '<S16>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Ideal P Gain'
//  '<S17>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Ideal P Gain Fdbk'
//  '<S18>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Integrator'
//  '<S19>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Integrator ICs'
//  '<S20>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/N Copy'
//  '<S21>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/N Gain'
//  '<S22>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/P Copy'
//  '<S23>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Parallel P Gain'
//  '<S24>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Reset Signal'
//  '<S25>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Saturation'
//  '<S26>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Saturation Fdbk'
//  '<S27>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Sum'
//  '<S28>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Sum Fdbk'
//  '<S29>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Tracking Mode'
//  '<S30>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Tracking Mode Sum'
//  '<S31>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Tsamp - Integral'
//  '<S32>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Tsamp - Ngain'
//  '<S33>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/postSat Signal'
//  '<S34>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/preSat Signal'
//  '<S35>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Anti-windup/Passthrough'
//  '<S36>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/D Gain/Internal Parameters'
//  '<S37>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S38>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S39>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/I Gain/Internal Parameters'
//  '<S40>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Ideal P Gain/Passthrough'
//  '<S41>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S42>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Integrator/Discrete'
//  '<S43>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Integrator ICs/Internal IC'
//  '<S44>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/N Copy/Disabled'
//  '<S45>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/N Gain/Internal Parameters'
//  '<S46>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/P Copy/Disabled'
//  '<S47>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S48>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Reset Signal/Disabled'
//  '<S49>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Saturation/Passthrough'
//  '<S50>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Saturation Fdbk/Disabled'
//  '<S51>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Sum/Sum_PID'
//  '<S52>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Sum Fdbk/Disabled'
//  '<S53>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Tracking Mode/Disabled'
//  '<S54>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S55>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S56>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S57>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/postSat Signal/Forward_Path'
//  '<S58>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem/PID POWER LIMIT/PID Controller/preSat Signal/Forward_Path'
//  '<S59>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT'
//  '<S60>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem1/If Action Subsystem1'
//  '<S61>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem1/MATLAB Function'
//  '<S62>'  : 'POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT/MATLAB Function'
//  '<S63>'  : 'POWER_LIMIT/If Action Subsystem1/MATLAB Function'

#endif                                 // RTW_HEADER_POWER_LIMIT_h_

//
// File trailer for generated code.
//
// [EOF]
//
