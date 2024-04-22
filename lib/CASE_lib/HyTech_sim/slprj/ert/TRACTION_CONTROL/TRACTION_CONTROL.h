//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TRACTION_CONTROL.h
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
    real_T Switch1;                    // '<S1>/Switch1'
    real_T Switch3;                    // '<S1>/Switch3'
    real_T Switch6;                    // '<S1>/Switch6'
    real_T adjusted_TCS_PID_Output;    // '<S1>/MATLAB Function3'
    real_T adjusted_TCS_PID_Output_c;  // '<S1>/MATLAB Function2'
    real_T adjusted_TCS_PID_Output_l;  // '<S1>/MATLAB Function1'
    real_T adjusted_TCS_PID_Output_e;  // '<S1>/MATLAB Function'
  };

  // Block states (default storage) for model 'TRACTION_CONTROL'
  struct DW_TRACTION_CONTROL_T {
    real_T Integrator_DSTATE;          // '<S53>/Integrator'
    real_T Filter_DSTATE;              // '<S48>/Filter'
    real_T Integrator_DSTATE_n;        // '<S104>/Integrator'
    real_T Filter_DSTATE_k;            // '<S99>/Filter'
    real_T Integrator_DSTATE_h;        // '<S155>/Integrator'
    real_T Filter_DSTATE_a;            // '<S150>/Filter'
    real_T Integrator_DSTATE_e;        // '<S206>/Integrator'
    real_T Filter_DSTATE_i;            // '<S201>/Filter'
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
            *rtu_useTractionControl, const real_T *rtu_TCS_SLThreshold, const
            real_T *rtu_TorqueInputFL, const real_T *rtu_TorqueInputFR, const
            real_T *rtu_TorqueInputRL, const real_T *rtu_TorqueInputRR, const
            real_T *rtu_SLFL, const real_T *rtu_SLFR, const real_T *rtu_SLRL,
            const real_T *rtu_SLRR, const boolean_T *rtu_useLaunch, const real_T
            *rtu_launchSL, const real_T *rtu_launchDeadZone, const real_T
            rtu_TCSPIDConfig[3], const real_T *rtu_Vx_B, const real_T
            *rtu_LaunchVelThreshold, const real_T *rtu_TCSVelThreshold, real_T
            *rty_TCSTorqueFL, real_T *rty_TCSTorqueFR, real_T *rty_TCSTorqueRL,
            real_T *rty_TCSTorqueRR, real_T *rty_TCSStatusFL, real_T
            *rty_TCSStatusFR, real_T *rty_TCSStatusRL, real_T *rty_TCSStatusRR,
            real_T rty_TCSPIDData[8]);

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

  // private member function(s) for subsystem '<S1>/MATLAB Function'
  static void TRACTION_CONTROL_MATLABFunction(real_T rtu_TCS_PID_Output, real_T
    rtu_torqueReference, real_T *rty_adjusted_TCS_PID_Output);

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
//  '<S7>'   : 'TRACTION_CONTROL/If Action Subsystem/MATLAB Function'
//  '<S8>'   : 'TRACTION_CONTROL/If Action Subsystem/MATLAB Function1'
//  '<S9>'   : 'TRACTION_CONTROL/If Action Subsystem/MATLAB Function2'
//  '<S10>'  : 'TRACTION_CONTROL/If Action Subsystem/MATLAB Function3'
//  '<S11>'  : 'TRACTION_CONTROL/If Action Subsystem/Torque Dead Zone Check'
//  '<S12>'  : 'TRACTION_CONTROL/If Action Subsystem/Torque Dead Zone Check1'
//  '<S13>'  : 'TRACTION_CONTROL/If Action Subsystem/Torque Dead Zone Check2'
//  '<S14>'  : 'TRACTION_CONTROL/If Action Subsystem/Torque Dead Zone Check3'
//  '<S15>'  : 'TRACTION_CONTROL/If Action Subsystem/Vel Threshold Check'
//  '<S16>'  : 'TRACTION_CONTROL/If Action Subsystem/Vel Threshold Check1'
//  '<S17>'  : 'TRACTION_CONTROL/If Action Subsystem/Vel Threshold Check2'
//  '<S18>'  : 'TRACTION_CONTROL/If Action Subsystem/Vel Threshold Check3'
//  '<S19>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller'
//  '<S20>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Anti-windup'
//  '<S21>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/D Gain'
//  '<S22>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Filter'
//  '<S23>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Filter ICs'
//  '<S24>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/I Gain'
//  '<S25>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Ideal P Gain'
//  '<S26>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Ideal P Gain Fdbk'
//  '<S27>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Integrator'
//  '<S28>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Integrator ICs'
//  '<S29>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/N Copy'
//  '<S30>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/N Gain'
//  '<S31>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/P Copy'
//  '<S32>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Parallel P Gain'
//  '<S33>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Reset Signal'
//  '<S34>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Saturation'
//  '<S35>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Saturation Fdbk'
//  '<S36>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Sum'
//  '<S37>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Sum Fdbk'
//  '<S38>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tracking Mode'
//  '<S39>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tracking Mode Sum'
//  '<S40>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tsamp - Integral'
//  '<S41>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tsamp - Ngain'
//  '<S42>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/postSat Signal'
//  '<S43>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/preSat Signal'
//  '<S44>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S45>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S46>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S47>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/D Gain/External Parameters'
//  '<S48>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S49>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S50>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/I Gain/External Parameters'
//  '<S51>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Ideal P Gain/Passthrough'
//  '<S52>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S53>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Integrator/Discrete'
//  '<S54>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Integrator ICs/Internal IC'
//  '<S55>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/N Copy/Disabled'
//  '<S56>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/N Gain/External Parameters'
//  '<S57>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/P Copy/Disabled'
//  '<S58>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Parallel P Gain/External Parameters'
//  '<S59>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Reset Signal/Disabled'
//  '<S60>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Saturation/Enabled'
//  '<S61>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Saturation Fdbk/Disabled'
//  '<S62>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Sum/Sum_PID'
//  '<S63>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Sum Fdbk/Disabled'
//  '<S64>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tracking Mode/Disabled'
//  '<S65>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S66>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S67>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S68>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/postSat Signal/Forward_Path'
//  '<S69>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID/PID Controller/preSat Signal/Forward_Path'
//  '<S70>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller'
//  '<S71>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Anti-windup'
//  '<S72>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/D Gain'
//  '<S73>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Filter'
//  '<S74>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Filter ICs'
//  '<S75>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/I Gain'
//  '<S76>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Ideal P Gain'
//  '<S77>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Ideal P Gain Fdbk'
//  '<S78>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Integrator'
//  '<S79>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Integrator ICs'
//  '<S80>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/N Copy'
//  '<S81>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/N Gain'
//  '<S82>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/P Copy'
//  '<S83>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Parallel P Gain'
//  '<S84>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Reset Signal'
//  '<S85>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Saturation'
//  '<S86>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Saturation Fdbk'
//  '<S87>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Sum'
//  '<S88>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Sum Fdbk'
//  '<S89>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tracking Mode'
//  '<S90>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tracking Mode Sum'
//  '<S91>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tsamp - Integral'
//  '<S92>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tsamp - Ngain'
//  '<S93>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/postSat Signal'
//  '<S94>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/preSat Signal'
//  '<S95>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S96>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S97>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S98>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/D Gain/External Parameters'
//  '<S99>'  : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S100>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S101>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/I Gain/External Parameters'
//  '<S102>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Ideal P Gain/Passthrough'
//  '<S103>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S104>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Integrator/Discrete'
//  '<S105>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Integrator ICs/Internal IC'
//  '<S106>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/N Copy/Disabled'
//  '<S107>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/N Gain/External Parameters'
//  '<S108>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/P Copy/Disabled'
//  '<S109>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Parallel P Gain/External Parameters'
//  '<S110>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Reset Signal/Disabled'
//  '<S111>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Saturation/Enabled'
//  '<S112>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Saturation Fdbk/Disabled'
//  '<S113>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Sum/Sum_PID'
//  '<S114>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Sum Fdbk/Disabled'
//  '<S115>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tracking Mode/Disabled'
//  '<S116>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S117>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S118>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S119>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/postSat Signal/Forward_Path'
//  '<S120>' : 'TRACTION_CONTROL/If Action Subsystem/External PID1/PID Controller/preSat Signal/Forward_Path'
//  '<S121>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller'
//  '<S122>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Anti-windup'
//  '<S123>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/D Gain'
//  '<S124>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Filter'
//  '<S125>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Filter ICs'
//  '<S126>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/I Gain'
//  '<S127>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Ideal P Gain'
//  '<S128>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Ideal P Gain Fdbk'
//  '<S129>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Integrator'
//  '<S130>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Integrator ICs'
//  '<S131>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/N Copy'
//  '<S132>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/N Gain'
//  '<S133>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/P Copy'
//  '<S134>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Parallel P Gain'
//  '<S135>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Reset Signal'
//  '<S136>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Saturation'
//  '<S137>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Saturation Fdbk'
//  '<S138>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Sum'
//  '<S139>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Sum Fdbk'
//  '<S140>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tracking Mode'
//  '<S141>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tracking Mode Sum'
//  '<S142>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tsamp - Integral'
//  '<S143>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tsamp - Ngain'
//  '<S144>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/postSat Signal'
//  '<S145>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/preSat Signal'
//  '<S146>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S147>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S148>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S149>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/D Gain/External Parameters'
//  '<S150>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S151>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S152>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/I Gain/External Parameters'
//  '<S153>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Ideal P Gain/Passthrough'
//  '<S154>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S155>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Integrator/Discrete'
//  '<S156>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Integrator ICs/Internal IC'
//  '<S157>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/N Copy/Disabled'
//  '<S158>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/N Gain/External Parameters'
//  '<S159>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/P Copy/Disabled'
//  '<S160>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Parallel P Gain/External Parameters'
//  '<S161>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Reset Signal/Disabled'
//  '<S162>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Saturation/Enabled'
//  '<S163>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Saturation Fdbk/Disabled'
//  '<S164>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Sum/Sum_PID'
//  '<S165>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Sum Fdbk/Disabled'
//  '<S166>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tracking Mode/Disabled'
//  '<S167>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S168>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S169>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S170>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/postSat Signal/Forward_Path'
//  '<S171>' : 'TRACTION_CONTROL/If Action Subsystem/External PID2/PID Controller/preSat Signal/Forward_Path'
//  '<S172>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller'
//  '<S173>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Anti-windup'
//  '<S174>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/D Gain'
//  '<S175>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Filter'
//  '<S176>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Filter ICs'
//  '<S177>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/I Gain'
//  '<S178>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Ideal P Gain'
//  '<S179>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Ideal P Gain Fdbk'
//  '<S180>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Integrator'
//  '<S181>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Integrator ICs'
//  '<S182>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/N Copy'
//  '<S183>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/N Gain'
//  '<S184>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/P Copy'
//  '<S185>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Parallel P Gain'
//  '<S186>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Reset Signal'
//  '<S187>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Saturation'
//  '<S188>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Saturation Fdbk'
//  '<S189>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Sum'
//  '<S190>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Sum Fdbk'
//  '<S191>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tracking Mode'
//  '<S192>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tracking Mode Sum'
//  '<S193>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tsamp - Integral'
//  '<S194>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tsamp - Ngain'
//  '<S195>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/postSat Signal'
//  '<S196>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/preSat Signal'
//  '<S197>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S198>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S199>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S200>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/D Gain/External Parameters'
//  '<S201>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S202>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S203>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/I Gain/External Parameters'
//  '<S204>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Ideal P Gain/Passthrough'
//  '<S205>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S206>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Integrator/Discrete'
//  '<S207>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Integrator ICs/Internal IC'
//  '<S208>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/N Copy/Disabled'
//  '<S209>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/N Gain/External Parameters'
//  '<S210>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/P Copy/Disabled'
//  '<S211>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Parallel P Gain/External Parameters'
//  '<S212>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Reset Signal/Disabled'
//  '<S213>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Saturation/Enabled'
//  '<S214>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Saturation Fdbk/Disabled'
//  '<S215>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Sum/Sum_PID'
//  '<S216>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Sum Fdbk/Disabled'
//  '<S217>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tracking Mode/Disabled'
//  '<S218>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S219>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S220>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S221>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/postSat Signal/Forward_Path'
//  '<S222>' : 'TRACTION_CONTROL/If Action Subsystem/External PID3/PID Controller/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_TRACTION_CONTROL_h_

//
// File trailer for generated code.
//
// [EOF]
//
