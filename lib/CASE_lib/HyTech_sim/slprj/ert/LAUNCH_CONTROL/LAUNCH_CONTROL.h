//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: LAUNCH_CONTROL.h
//
// Code generated for Simulink model 'LAUNCH_CONTROL'.
//
// Model version                  : 1.8
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Wed Apr 10 20:16:07 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_LAUNCH_CONTROL_h_
#define RTW_HEADER_LAUNCH_CONTROL_h_
#include "rtwtypes.h"
#include "LAUNCH_CONTROL_types.h"
#include "rtw_modelmap.h"
#include <cstring>

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  LAUNCH_CONTROL_GetCAPIStaticMap(void);

// Class declaration for model LAUNCH_CONTROL
class LAUNCH_CONTROL final
{
  // public data and function members
 public:
  // Block states (default storage) for model 'LAUNCH_CONTROL'
  struct DW_LAUNCH_CONTROL_T {
    real_T Filter_DSTATE;              // '<S31>/Filter'
    real_T Integrator_DSTATE;          // '<S36>/Integrator'
    real_T Integrator_DSTATE_l;        // '<S180>/Integrator'
    real_T Filter_DSTATE_m;            // '<S175>/Filter'
    real_T Integrator_DSTATE_f;        // '<S132>/Integrator'
    real_T Filter_DSTATE_i;            // '<S127>/Filter'
    real_T Integrator_DSTATE_d;        // '<S84>/Integrator'
    real_T Filter_DSTATE_h;            // '<S79>/Filter'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_LAUNCH_CONTROL_T {
    const char_T **errorStatus;

    //
    //  DataMapInfo:
    //  The following substructure contains information regarding
    //  structures generated in the model's C API.

    struct {
      rtwCAPI_ModelMappingInfo mmi;
    } DataMapInfo;
  };

  // model initialize function
  void initialize();

  // Copy Constructor
  LAUNCH_CONTROL(LAUNCH_CONTROL const&) = delete;

  // Assignment Operator
  LAUNCH_CONTROL& operator= (LAUNCH_CONTROL const&) & = delete;

  // Move Constructor
  LAUNCH_CONTROL(LAUNCH_CONTROL &&) = delete;

  // Move Assignment Operator
  LAUNCH_CONTROL& operator= (LAUNCH_CONTROL &&) = delete;

  // Real-Time Model get method
  LAUNCH_CONTROL::RT_MODEL_LAUNCH_CONTROL_T * getRTM();

  // member function to set up the C-API information
  void setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T
                     *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx);

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // model step function
  void step(const real_T *rtu_SLFL, const real_T *rtu_SLFR, const real_T
            *rtu_SLRL, const real_T *rtu_SLRR, real_T *rty_LaunchTorqueFL,
            real_T *rty_LaunchTorqueFR, real_T *rty_LaunchTorqueRL, real_T
            *rty_LaunchTorqueRR);

  // Constructor
  LAUNCH_CONTROL();

  // Destructor
  ~LAUNCH_CONTROL();

  // private data and function members
 private:
  // Block states
  DW_LAUNCH_CONTROL_T LAUNCH_CONTROL_DW;

  // Real-Time Model
  RT_MODEL_LAUNCH_CONTROL_T LAUNCH_CONTROL_M;
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
//  '<Root>' : 'LAUNCH_CONTROL'
//  '<S1>'   : 'LAUNCH_CONTROL/PID Controller'
//  '<S2>'   : 'LAUNCH_CONTROL/PID Controller1'
//  '<S3>'   : 'LAUNCH_CONTROL/PID Controller2'
//  '<S4>'   : 'LAUNCH_CONTROL/PID Controller3'
//  '<S5>'   : 'LAUNCH_CONTROL/PID Controller/Anti-windup'
//  '<S6>'   : 'LAUNCH_CONTROL/PID Controller/D Gain'
//  '<S7>'   : 'LAUNCH_CONTROL/PID Controller/Filter'
//  '<S8>'   : 'LAUNCH_CONTROL/PID Controller/Filter ICs'
//  '<S9>'   : 'LAUNCH_CONTROL/PID Controller/I Gain'
//  '<S10>'  : 'LAUNCH_CONTROL/PID Controller/Ideal P Gain'
//  '<S11>'  : 'LAUNCH_CONTROL/PID Controller/Ideal P Gain Fdbk'
//  '<S12>'  : 'LAUNCH_CONTROL/PID Controller/Integrator'
//  '<S13>'  : 'LAUNCH_CONTROL/PID Controller/Integrator ICs'
//  '<S14>'  : 'LAUNCH_CONTROL/PID Controller/N Copy'
//  '<S15>'  : 'LAUNCH_CONTROL/PID Controller/N Gain'
//  '<S16>'  : 'LAUNCH_CONTROL/PID Controller/P Copy'
//  '<S17>'  : 'LAUNCH_CONTROL/PID Controller/Parallel P Gain'
//  '<S18>'  : 'LAUNCH_CONTROL/PID Controller/Reset Signal'
//  '<S19>'  : 'LAUNCH_CONTROL/PID Controller/Saturation'
//  '<S20>'  : 'LAUNCH_CONTROL/PID Controller/Saturation Fdbk'
//  '<S21>'  : 'LAUNCH_CONTROL/PID Controller/Sum'
//  '<S22>'  : 'LAUNCH_CONTROL/PID Controller/Sum Fdbk'
//  '<S23>'  : 'LAUNCH_CONTROL/PID Controller/Tracking Mode'
//  '<S24>'  : 'LAUNCH_CONTROL/PID Controller/Tracking Mode Sum'
//  '<S25>'  : 'LAUNCH_CONTROL/PID Controller/Tsamp - Integral'
//  '<S26>'  : 'LAUNCH_CONTROL/PID Controller/Tsamp - Ngain'
//  '<S27>'  : 'LAUNCH_CONTROL/PID Controller/postSat Signal'
//  '<S28>'  : 'LAUNCH_CONTROL/PID Controller/preSat Signal'
//  '<S29>'  : 'LAUNCH_CONTROL/PID Controller/Anti-windup/Passthrough'
//  '<S30>'  : 'LAUNCH_CONTROL/PID Controller/D Gain/Internal Parameters'
//  '<S31>'  : 'LAUNCH_CONTROL/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S32>'  : 'LAUNCH_CONTROL/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S33>'  : 'LAUNCH_CONTROL/PID Controller/I Gain/Internal Parameters'
//  '<S34>'  : 'LAUNCH_CONTROL/PID Controller/Ideal P Gain/Passthrough'
//  '<S35>'  : 'LAUNCH_CONTROL/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S36>'  : 'LAUNCH_CONTROL/PID Controller/Integrator/Discrete'
//  '<S37>'  : 'LAUNCH_CONTROL/PID Controller/Integrator ICs/Internal IC'
//  '<S38>'  : 'LAUNCH_CONTROL/PID Controller/N Copy/Disabled'
//  '<S39>'  : 'LAUNCH_CONTROL/PID Controller/N Gain/Internal Parameters'
//  '<S40>'  : 'LAUNCH_CONTROL/PID Controller/P Copy/Disabled'
//  '<S41>'  : 'LAUNCH_CONTROL/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S42>'  : 'LAUNCH_CONTROL/PID Controller/Reset Signal/Disabled'
//  '<S43>'  : 'LAUNCH_CONTROL/PID Controller/Saturation/Passthrough'
//  '<S44>'  : 'LAUNCH_CONTROL/PID Controller/Saturation Fdbk/Disabled'
//  '<S45>'  : 'LAUNCH_CONTROL/PID Controller/Sum/Sum_PID'
//  '<S46>'  : 'LAUNCH_CONTROL/PID Controller/Sum Fdbk/Disabled'
//  '<S47>'  : 'LAUNCH_CONTROL/PID Controller/Tracking Mode/Disabled'
//  '<S48>'  : 'LAUNCH_CONTROL/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S49>'  : 'LAUNCH_CONTROL/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S50>'  : 'LAUNCH_CONTROL/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S51>'  : 'LAUNCH_CONTROL/PID Controller/postSat Signal/Forward_Path'
//  '<S52>'  : 'LAUNCH_CONTROL/PID Controller/preSat Signal/Forward_Path'
//  '<S53>'  : 'LAUNCH_CONTROL/PID Controller1/Anti-windup'
//  '<S54>'  : 'LAUNCH_CONTROL/PID Controller1/D Gain'
//  '<S55>'  : 'LAUNCH_CONTROL/PID Controller1/Filter'
//  '<S56>'  : 'LAUNCH_CONTROL/PID Controller1/Filter ICs'
//  '<S57>'  : 'LAUNCH_CONTROL/PID Controller1/I Gain'
//  '<S58>'  : 'LAUNCH_CONTROL/PID Controller1/Ideal P Gain'
//  '<S59>'  : 'LAUNCH_CONTROL/PID Controller1/Ideal P Gain Fdbk'
//  '<S60>'  : 'LAUNCH_CONTROL/PID Controller1/Integrator'
//  '<S61>'  : 'LAUNCH_CONTROL/PID Controller1/Integrator ICs'
//  '<S62>'  : 'LAUNCH_CONTROL/PID Controller1/N Copy'
//  '<S63>'  : 'LAUNCH_CONTROL/PID Controller1/N Gain'
//  '<S64>'  : 'LAUNCH_CONTROL/PID Controller1/P Copy'
//  '<S65>'  : 'LAUNCH_CONTROL/PID Controller1/Parallel P Gain'
//  '<S66>'  : 'LAUNCH_CONTROL/PID Controller1/Reset Signal'
//  '<S67>'  : 'LAUNCH_CONTROL/PID Controller1/Saturation'
//  '<S68>'  : 'LAUNCH_CONTROL/PID Controller1/Saturation Fdbk'
//  '<S69>'  : 'LAUNCH_CONTROL/PID Controller1/Sum'
//  '<S70>'  : 'LAUNCH_CONTROL/PID Controller1/Sum Fdbk'
//  '<S71>'  : 'LAUNCH_CONTROL/PID Controller1/Tracking Mode'
//  '<S72>'  : 'LAUNCH_CONTROL/PID Controller1/Tracking Mode Sum'
//  '<S73>'  : 'LAUNCH_CONTROL/PID Controller1/Tsamp - Integral'
//  '<S74>'  : 'LAUNCH_CONTROL/PID Controller1/Tsamp - Ngain'
//  '<S75>'  : 'LAUNCH_CONTROL/PID Controller1/postSat Signal'
//  '<S76>'  : 'LAUNCH_CONTROL/PID Controller1/preSat Signal'
//  '<S77>'  : 'LAUNCH_CONTROL/PID Controller1/Anti-windup/Passthrough'
//  '<S78>'  : 'LAUNCH_CONTROL/PID Controller1/D Gain/Internal Parameters'
//  '<S79>'  : 'LAUNCH_CONTROL/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S80>'  : 'LAUNCH_CONTROL/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S81>'  : 'LAUNCH_CONTROL/PID Controller1/I Gain/Internal Parameters'
//  '<S82>'  : 'LAUNCH_CONTROL/PID Controller1/Ideal P Gain/Passthrough'
//  '<S83>'  : 'LAUNCH_CONTROL/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S84>'  : 'LAUNCH_CONTROL/PID Controller1/Integrator/Discrete'
//  '<S85>'  : 'LAUNCH_CONTROL/PID Controller1/Integrator ICs/Internal IC'
//  '<S86>'  : 'LAUNCH_CONTROL/PID Controller1/N Copy/Disabled'
//  '<S87>'  : 'LAUNCH_CONTROL/PID Controller1/N Gain/Internal Parameters'
//  '<S88>'  : 'LAUNCH_CONTROL/PID Controller1/P Copy/Disabled'
//  '<S89>'  : 'LAUNCH_CONTROL/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S90>'  : 'LAUNCH_CONTROL/PID Controller1/Reset Signal/Disabled'
//  '<S91>'  : 'LAUNCH_CONTROL/PID Controller1/Saturation/Passthrough'
//  '<S92>'  : 'LAUNCH_CONTROL/PID Controller1/Saturation Fdbk/Disabled'
//  '<S93>'  : 'LAUNCH_CONTROL/PID Controller1/Sum/Sum_PID'
//  '<S94>'  : 'LAUNCH_CONTROL/PID Controller1/Sum Fdbk/Disabled'
//  '<S95>'  : 'LAUNCH_CONTROL/PID Controller1/Tracking Mode/Disabled'
//  '<S96>'  : 'LAUNCH_CONTROL/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S97>'  : 'LAUNCH_CONTROL/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S98>'  : 'LAUNCH_CONTROL/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S99>'  : 'LAUNCH_CONTROL/PID Controller1/postSat Signal/Forward_Path'
//  '<S100>' : 'LAUNCH_CONTROL/PID Controller1/preSat Signal/Forward_Path'
//  '<S101>' : 'LAUNCH_CONTROL/PID Controller2/Anti-windup'
//  '<S102>' : 'LAUNCH_CONTROL/PID Controller2/D Gain'
//  '<S103>' : 'LAUNCH_CONTROL/PID Controller2/Filter'
//  '<S104>' : 'LAUNCH_CONTROL/PID Controller2/Filter ICs'
//  '<S105>' : 'LAUNCH_CONTROL/PID Controller2/I Gain'
//  '<S106>' : 'LAUNCH_CONTROL/PID Controller2/Ideal P Gain'
//  '<S107>' : 'LAUNCH_CONTROL/PID Controller2/Ideal P Gain Fdbk'
//  '<S108>' : 'LAUNCH_CONTROL/PID Controller2/Integrator'
//  '<S109>' : 'LAUNCH_CONTROL/PID Controller2/Integrator ICs'
//  '<S110>' : 'LAUNCH_CONTROL/PID Controller2/N Copy'
//  '<S111>' : 'LAUNCH_CONTROL/PID Controller2/N Gain'
//  '<S112>' : 'LAUNCH_CONTROL/PID Controller2/P Copy'
//  '<S113>' : 'LAUNCH_CONTROL/PID Controller2/Parallel P Gain'
//  '<S114>' : 'LAUNCH_CONTROL/PID Controller2/Reset Signal'
//  '<S115>' : 'LAUNCH_CONTROL/PID Controller2/Saturation'
//  '<S116>' : 'LAUNCH_CONTROL/PID Controller2/Saturation Fdbk'
//  '<S117>' : 'LAUNCH_CONTROL/PID Controller2/Sum'
//  '<S118>' : 'LAUNCH_CONTROL/PID Controller2/Sum Fdbk'
//  '<S119>' : 'LAUNCH_CONTROL/PID Controller2/Tracking Mode'
//  '<S120>' : 'LAUNCH_CONTROL/PID Controller2/Tracking Mode Sum'
//  '<S121>' : 'LAUNCH_CONTROL/PID Controller2/Tsamp - Integral'
//  '<S122>' : 'LAUNCH_CONTROL/PID Controller2/Tsamp - Ngain'
//  '<S123>' : 'LAUNCH_CONTROL/PID Controller2/postSat Signal'
//  '<S124>' : 'LAUNCH_CONTROL/PID Controller2/preSat Signal'
//  '<S125>' : 'LAUNCH_CONTROL/PID Controller2/Anti-windup/Passthrough'
//  '<S126>' : 'LAUNCH_CONTROL/PID Controller2/D Gain/Internal Parameters'
//  '<S127>' : 'LAUNCH_CONTROL/PID Controller2/Filter/Disc. Forward Euler Filter'
//  '<S128>' : 'LAUNCH_CONTROL/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S129>' : 'LAUNCH_CONTROL/PID Controller2/I Gain/Internal Parameters'
//  '<S130>' : 'LAUNCH_CONTROL/PID Controller2/Ideal P Gain/Passthrough'
//  '<S131>' : 'LAUNCH_CONTROL/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S132>' : 'LAUNCH_CONTROL/PID Controller2/Integrator/Discrete'
//  '<S133>' : 'LAUNCH_CONTROL/PID Controller2/Integrator ICs/Internal IC'
//  '<S134>' : 'LAUNCH_CONTROL/PID Controller2/N Copy/Disabled'
//  '<S135>' : 'LAUNCH_CONTROL/PID Controller2/N Gain/Internal Parameters'
//  '<S136>' : 'LAUNCH_CONTROL/PID Controller2/P Copy/Disabled'
//  '<S137>' : 'LAUNCH_CONTROL/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S138>' : 'LAUNCH_CONTROL/PID Controller2/Reset Signal/Disabled'
//  '<S139>' : 'LAUNCH_CONTROL/PID Controller2/Saturation/Passthrough'
//  '<S140>' : 'LAUNCH_CONTROL/PID Controller2/Saturation Fdbk/Disabled'
//  '<S141>' : 'LAUNCH_CONTROL/PID Controller2/Sum/Sum_PID'
//  '<S142>' : 'LAUNCH_CONTROL/PID Controller2/Sum Fdbk/Disabled'
//  '<S143>' : 'LAUNCH_CONTROL/PID Controller2/Tracking Mode/Disabled'
//  '<S144>' : 'LAUNCH_CONTROL/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S145>' : 'LAUNCH_CONTROL/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S146>' : 'LAUNCH_CONTROL/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S147>' : 'LAUNCH_CONTROL/PID Controller2/postSat Signal/Forward_Path'
//  '<S148>' : 'LAUNCH_CONTROL/PID Controller2/preSat Signal/Forward_Path'
//  '<S149>' : 'LAUNCH_CONTROL/PID Controller3/Anti-windup'
//  '<S150>' : 'LAUNCH_CONTROL/PID Controller3/D Gain'
//  '<S151>' : 'LAUNCH_CONTROL/PID Controller3/Filter'
//  '<S152>' : 'LAUNCH_CONTROL/PID Controller3/Filter ICs'
//  '<S153>' : 'LAUNCH_CONTROL/PID Controller3/I Gain'
//  '<S154>' : 'LAUNCH_CONTROL/PID Controller3/Ideal P Gain'
//  '<S155>' : 'LAUNCH_CONTROL/PID Controller3/Ideal P Gain Fdbk'
//  '<S156>' : 'LAUNCH_CONTROL/PID Controller3/Integrator'
//  '<S157>' : 'LAUNCH_CONTROL/PID Controller3/Integrator ICs'
//  '<S158>' : 'LAUNCH_CONTROL/PID Controller3/N Copy'
//  '<S159>' : 'LAUNCH_CONTROL/PID Controller3/N Gain'
//  '<S160>' : 'LAUNCH_CONTROL/PID Controller3/P Copy'
//  '<S161>' : 'LAUNCH_CONTROL/PID Controller3/Parallel P Gain'
//  '<S162>' : 'LAUNCH_CONTROL/PID Controller3/Reset Signal'
//  '<S163>' : 'LAUNCH_CONTROL/PID Controller3/Saturation'
//  '<S164>' : 'LAUNCH_CONTROL/PID Controller3/Saturation Fdbk'
//  '<S165>' : 'LAUNCH_CONTROL/PID Controller3/Sum'
//  '<S166>' : 'LAUNCH_CONTROL/PID Controller3/Sum Fdbk'
//  '<S167>' : 'LAUNCH_CONTROL/PID Controller3/Tracking Mode'
//  '<S168>' : 'LAUNCH_CONTROL/PID Controller3/Tracking Mode Sum'
//  '<S169>' : 'LAUNCH_CONTROL/PID Controller3/Tsamp - Integral'
//  '<S170>' : 'LAUNCH_CONTROL/PID Controller3/Tsamp - Ngain'
//  '<S171>' : 'LAUNCH_CONTROL/PID Controller3/postSat Signal'
//  '<S172>' : 'LAUNCH_CONTROL/PID Controller3/preSat Signal'
//  '<S173>' : 'LAUNCH_CONTROL/PID Controller3/Anti-windup/Passthrough'
//  '<S174>' : 'LAUNCH_CONTROL/PID Controller3/D Gain/Internal Parameters'
//  '<S175>' : 'LAUNCH_CONTROL/PID Controller3/Filter/Disc. Forward Euler Filter'
//  '<S176>' : 'LAUNCH_CONTROL/PID Controller3/Filter ICs/Internal IC - Filter'
//  '<S177>' : 'LAUNCH_CONTROL/PID Controller3/I Gain/Internal Parameters'
//  '<S178>' : 'LAUNCH_CONTROL/PID Controller3/Ideal P Gain/Passthrough'
//  '<S179>' : 'LAUNCH_CONTROL/PID Controller3/Ideal P Gain Fdbk/Disabled'
//  '<S180>' : 'LAUNCH_CONTROL/PID Controller3/Integrator/Discrete'
//  '<S181>' : 'LAUNCH_CONTROL/PID Controller3/Integrator ICs/Internal IC'
//  '<S182>' : 'LAUNCH_CONTROL/PID Controller3/N Copy/Disabled'
//  '<S183>' : 'LAUNCH_CONTROL/PID Controller3/N Gain/Internal Parameters'
//  '<S184>' : 'LAUNCH_CONTROL/PID Controller3/P Copy/Disabled'
//  '<S185>' : 'LAUNCH_CONTROL/PID Controller3/Parallel P Gain/Internal Parameters'
//  '<S186>' : 'LAUNCH_CONTROL/PID Controller3/Reset Signal/Disabled'
//  '<S187>' : 'LAUNCH_CONTROL/PID Controller3/Saturation/Passthrough'
//  '<S188>' : 'LAUNCH_CONTROL/PID Controller3/Saturation Fdbk/Disabled'
//  '<S189>' : 'LAUNCH_CONTROL/PID Controller3/Sum/Sum_PID'
//  '<S190>' : 'LAUNCH_CONTROL/PID Controller3/Sum Fdbk/Disabled'
//  '<S191>' : 'LAUNCH_CONTROL/PID Controller3/Tracking Mode/Disabled'
//  '<S192>' : 'LAUNCH_CONTROL/PID Controller3/Tracking Mode Sum/Passthrough'
//  '<S193>' : 'LAUNCH_CONTROL/PID Controller3/Tsamp - Integral/TsSignalSpecification'
//  '<S194>' : 'LAUNCH_CONTROL/PID Controller3/Tsamp - Ngain/Passthrough'
//  '<S195>' : 'LAUNCH_CONTROL/PID Controller3/postSat Signal/Forward_Path'
//  '<S196>' : 'LAUNCH_CONTROL/PID Controller3/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_LAUNCH_CONTROL_h_

//
// File trailer for generated code.
//
// [EOF]
//
