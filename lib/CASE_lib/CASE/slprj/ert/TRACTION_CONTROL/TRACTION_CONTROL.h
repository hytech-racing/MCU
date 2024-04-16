//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TRACTION_CONTROL.h
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
#ifndef RTW_HEADER_TRACTION_CONTROL_h_
#define RTW_HEADER_TRACTION_CONTROL_h_
#include "rtwtypes.h"
#include "TRACTION_CONTROL_types.h"
#include "rtw_modelmap.h"
#include <cstring>

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  TRACTION_CONTROL_GetCAPIStaticMap(void);

// Class declaration for model TRACTION_CONTROL
class TRACTION_CONTROL final
{
  // public data and function members
 public:
  // Block signals for model 'TRACTION_CONTROL'
  struct B_TRACTION_CONTROL_T {
    real_T Switch;                     // '<S1>/Switch'
    real_T Switch4;                    // '<S1>/Switch4'
    real_T Switch1;                    // '<S1>/Switch1'
    real_T Switch2;                    // '<S1>/Switch2'
    real_T Switch3;                    // '<S1>/Switch3'
    real_T Switch5;                    // '<S1>/Switch5'
    real_T Switch6;                    // '<S1>/Switch6'
    real_T Switch7;                    // '<S1>/Switch7'
  };

  // Block states (default storage) for model 'TRACTION_CONTROL'
  struct DW_TRACTION_CONTROL_T {
    real_T Integrator_DSTATE;          // '<S41>/Integrator'
    real_T Filter_DSTATE;              // '<S36>/Filter'
    real_T Integrator_DSTATE_i;        // '<S92>/Integrator'
    real_T Filter_DSTATE_a;            // '<S87>/Filter'
    real_T Integrator_DSTATE_ir;       // '<S143>/Integrator'
    real_T Filter_DSTATE_b;            // '<S138>/Filter'
    real_T Integrator_DSTATE_p;        // '<S194>/Integrator'
    real_T Filter_DSTATE_m;            // '<S189>/Filter'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_TRACTION_CONTROL_T {
    const char_T **errorStatus;

    //
    //  DataMapInfo:
    //  The following substructure contains information regarding
    //  structures generated in the model's C API.

    struct {
      rtwCAPI_ModelMappingInfo mmi;
      void* dataAddress[16];
      int32_T* vardimsAddress[16];
      RTWLoggingFcnPtr loggingPtrs[16];
    } DataMapInfo;
  };

  // model initialize function
  void initialize();

  // Initial conditions function
  void init(real_T rty_TCSPIDData[8]) const;

  // Copy Constructor
  TRACTION_CONTROL(TRACTION_CONTROL const&) = delete;

  // Assignment Operator
  TRACTION_CONTROL& operator= (TRACTION_CONTROL const&) & = delete;

  // Move Constructor
  TRACTION_CONTROL(TRACTION_CONTROL &&) = delete;

  // Move Assignment Operator
  TRACTION_CONTROL& operator= (TRACTION_CONTROL &&) = delete;

  // Real-Time Model get method
  TRACTION_CONTROL::RT_MODEL_TRACTION_CONTROL_T * getRTM();

  // member function to set up the C-API information
  void setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T
                     *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx);

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // model step function
  void step(const real_T *rtu_DriverTorqueAvg, const boolean_T
            *rtu_useTractionControl, const real_T *rtu_TCSThreshold, const
            real_T *rtu_TorqueTVFL, const real_T *rtu_TorqueTVFR, const real_T
            *rtu_TorqueTVRL, const real_T *rtu_TorqueTVRR, const real_T
            *rtu_SLFL, const real_T *rtu_SLFR, const real_T *rtu_SLRL, const
            real_T *rtu_SLRR, const boolean_T *rtu_useLaunch, const real_T
            *rtu_launchSL, const real_T *rtu_launchDeadZone, const real_T
            rtu_TCSPIDConfig[3], real_T *rty_TCSTorqueFL, real_T
            *rty_TCSTorqueFR, real_T *rty_TCSTorqueRL, real_T *rty_TCSTorqueRR,
            real_T *rty_TCSStatusFL, real_T *rty_TCSStatusFR, real_T
            *rty_TCSStatusRL, real_T *rty_TCSStatusRR, real_T rty_TCSPIDData[8]);

  // Constructor
  TRACTION_CONTROL();

  // Destructor
  ~TRACTION_CONTROL();

  // private data and function members
 private:
  // Block signals
  B_TRACTION_CONTROL_T TRACTION_CONTROL_B;

  // Block states
  DW_TRACTION_CONTROL_T TRACTION_CONTROL_DW;

  // Real-Time Model
  RT_MODEL_TRACTION_CONTROL_T TRACTION_CONTROL_M;
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
//  '<Root>' : 'TRACTION_CONTROL'
//  '<S1>'   : 'TRACTION_CONTROL/If Action Subsystem'
//  '<S2>'   : 'TRACTION_CONTROL/If Action Subsystem1'
//  '<S3>'   : 'TRACTION_CONTROL/If Action Subsystem/External PID'
//  '<S4>'   : 'TRACTION_CONTROL/If Action Subsystem/External PID1'
//  '<S5>'   : 'TRACTION_CONTROL/If Action Subsystem/External PID2'
//  '<S6>'   : 'TRACTION_CONTROL/If Action Subsystem/External PID3'
//  '<S7>'   : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller'
//  '<S8>'   : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Anti-windup'
//  '<S9>'   : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/D Gain'
//  '<S10>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Filter'
//  '<S11>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Filter ICs'
//  '<S12>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/I Gain'
//  '<S13>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Ideal P Gain'
//  '<S14>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Ideal P Gain Fdbk'
//  '<S15>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Integrator'
//  '<S16>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Integrator ICs'
//  '<S17>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/N Copy'
//  '<S18>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/N Gain'
//  '<S19>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/P Copy'
//  '<S20>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Parallel P Gain'
//  '<S21>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Reset Signal'
//  '<S22>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Saturation'
//  '<S23>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Saturation Fdbk'
//  '<S24>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Sum'
//  '<S25>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Sum Fdbk'
//  '<S26>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tracking Mode'
//  '<S27>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tracking Mode Sum'
//  '<S28>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tsamp - Integral'
//  '<S29>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tsamp - Ngain'
//  '<S30>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/postSat Signal'
//  '<S31>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/preSat Signal'
//  '<S32>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S33>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S34>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S35>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/D Gain/External Parameters'
//  '<S36>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S37>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S38>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/I Gain/External Parameters'
//  '<S39>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Ideal P Gain/Passthrough'
//  '<S40>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S41>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Integrator/Discrete'
//  '<S42>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Integrator ICs/Internal IC'
//  '<S43>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/N Copy/Disabled'
//  '<S44>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/N Gain/External Parameters'
//  '<S45>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/P Copy/Disabled'
//  '<S46>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Parallel P Gain/External Parameters'
//  '<S47>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Reset Signal/Disabled'
//  '<S48>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Saturation/Enabled'
//  '<S49>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Saturation Fdbk/Disabled'
//  '<S50>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Sum/Sum_PID'
//  '<S51>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Sum Fdbk/Disabled'
//  '<S52>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tracking Mode/Disabled'
//  '<S53>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S54>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S55>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S56>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/postSat Signal/Forward_Path'
//  '<S57>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/preSat Signal/Forward_Path'
//  '<S58>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller'
//  '<S59>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Anti-windup'
//  '<S60>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/D Gain'
//  '<S61>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Filter'
//  '<S62>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Filter ICs'
//  '<S63>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/I Gain'
//  '<S64>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Ideal P Gain'
//  '<S65>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Ideal P Gain Fdbk'
//  '<S66>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Integrator'
//  '<S67>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Integrator ICs'
//  '<S68>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/N Copy'
//  '<S69>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/N Gain'
//  '<S70>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/P Copy'
//  '<S71>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Parallel P Gain'
//  '<S72>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Reset Signal'
//  '<S73>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Saturation'
//  '<S74>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Saturation Fdbk'
//  '<S75>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Sum'
//  '<S76>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Sum Fdbk'
//  '<S77>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tracking Mode'
//  '<S78>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tracking Mode Sum'
//  '<S79>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tsamp - Integral'
//  '<S80>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tsamp - Ngain'
//  '<S81>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/postSat Signal'
//  '<S82>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/preSat Signal'
//  '<S83>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S84>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S85>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S86>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/D Gain/External Parameters'
//  '<S87>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S88>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S89>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/I Gain/External Parameters'
//  '<S90>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Ideal P Gain/Passthrough'
//  '<S91>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S92>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Integrator/Discrete'
//  '<S93>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Integrator ICs/Internal IC'
//  '<S94>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/N Copy/Disabled'
//  '<S95>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/N Gain/External Parameters'
//  '<S96>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/P Copy/Disabled'
//  '<S97>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Parallel P Gain/External Parameters'
//  '<S98>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Reset Signal/Disabled'
//  '<S99>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Saturation/Enabled'
//  '<S100>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Saturation Fdbk/Disabled'
//  '<S101>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Sum/Sum_PID'
//  '<S102>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Sum Fdbk/Disabled'
//  '<S103>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tracking Mode/Disabled'
//  '<S104>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S105>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S106>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S107>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/postSat Signal/Forward_Path'
//  '<S108>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/preSat Signal/Forward_Path'
//  '<S109>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller'
//  '<S110>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Anti-windup'
//  '<S111>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/D Gain'
//  '<S112>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Filter'
//  '<S113>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Filter ICs'
//  '<S114>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/I Gain'
//  '<S115>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Ideal P Gain'
//  '<S116>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Ideal P Gain Fdbk'
//  '<S117>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Integrator'
//  '<S118>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Integrator ICs'
//  '<S119>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/N Copy'
//  '<S120>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/N Gain'
//  '<S121>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/P Copy'
//  '<S122>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Parallel P Gain'
//  '<S123>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Reset Signal'
//  '<S124>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Saturation'
//  '<S125>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Saturation Fdbk'
//  '<S126>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Sum'
//  '<S127>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Sum Fdbk'
//  '<S128>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tracking Mode'
//  '<S129>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tracking Mode Sum'
//  '<S130>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tsamp - Integral'
//  '<S131>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tsamp - Ngain'
//  '<S132>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/postSat Signal'
//  '<S133>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/preSat Signal'
//  '<S134>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S135>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S136>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S137>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/D Gain/External Parameters'
//  '<S138>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S139>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S140>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/I Gain/External Parameters'
//  '<S141>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Ideal P Gain/Passthrough'
//  '<S142>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S143>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Integrator/Discrete'
//  '<S144>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Integrator ICs/Internal IC'
//  '<S145>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/N Copy/Disabled'
//  '<S146>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/N Gain/External Parameters'
//  '<S147>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/P Copy/Disabled'
//  '<S148>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Parallel P Gain/External Parameters'
//  '<S149>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Reset Signal/Disabled'
//  '<S150>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Saturation/Enabled'
//  '<S151>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Saturation Fdbk/Disabled'
//  '<S152>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Sum/Sum_PID'
//  '<S153>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Sum Fdbk/Disabled'
//  '<S154>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tracking Mode/Disabled'
//  '<S155>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S156>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S157>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S158>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/postSat Signal/Forward_Path'
//  '<S159>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/preSat Signal/Forward_Path'
//  '<S160>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller'
//  '<S161>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Anti-windup'
//  '<S162>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/D Gain'
//  '<S163>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Filter'
//  '<S164>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Filter ICs'
//  '<S165>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/I Gain'
//  '<S166>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Ideal P Gain'
//  '<S167>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Ideal P Gain Fdbk'
//  '<S168>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Integrator'
//  '<S169>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Integrator ICs'
//  '<S170>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/N Copy'
//  '<S171>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/N Gain'
//  '<S172>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/P Copy'
//  '<S173>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Parallel P Gain'
//  '<S174>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Reset Signal'
//  '<S175>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Saturation'
//  '<S176>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Saturation Fdbk'
//  '<S177>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Sum'
//  '<S178>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Sum Fdbk'
//  '<S179>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tracking Mode'
//  '<S180>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tracking Mode Sum'
//  '<S181>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tsamp - Integral'
//  '<S182>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tsamp - Ngain'
//  '<S183>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/postSat Signal'
//  '<S184>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/preSat Signal'
//  '<S185>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S186>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S187>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S188>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/D Gain/External Parameters'
//  '<S189>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S190>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S191>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/I Gain/External Parameters'
//  '<S192>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Ideal P Gain/Passthrough'
//  '<S193>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S194>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Integrator/Discrete'
//  '<S195>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Integrator ICs/Internal IC'
//  '<S196>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/N Copy/Disabled'
//  '<S197>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/N Gain/External Parameters'
//  '<S198>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/P Copy/Disabled'
//  '<S199>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Parallel P Gain/External Parameters'
//  '<S200>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Reset Signal/Disabled'
//  '<S201>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Saturation/Enabled'
//  '<S202>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Saturation Fdbk/Disabled'
//  '<S203>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Sum/Sum_PID'
//  '<S204>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Sum Fdbk/Disabled'
//  '<S205>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tracking Mode/Disabled'
//  '<S206>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S207>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S208>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S209>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/postSat Signal/Forward_Path'
//  '<S210>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_TRACTION_CONTROL_h_

//
// File trailer for generated code.
//
// [EOF]
//
