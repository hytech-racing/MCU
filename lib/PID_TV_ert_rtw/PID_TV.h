//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PID_TV.h
//
// Code generated for Simulink model 'PID_TV'.
//
// Model version                  : 1.14
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Tue Mar 26 00:06:56 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_PID_TV_h_
#define RTW_HEADER_PID_TV_h_
#include "rtwtypes.h"
#include "PID_TV_types.h"
#include "rtw_modelmap.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  PID_TV_GetCAPIStaticMap(void);

// Class declaration for model PID_TV
class PID_TV final
{
  // public data and function members
 public:

  float shit_in;
  float shit_out;
  // Block states (default storage) for system '<Root>'
  struct DW_PID_TV_T {
    real_T Integrator_DSTATE;          // '<S35>/Integrator'
    real_T Filter_DSTATE;              // '<S30>/Filter'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_PID_TV_T {
    real_T Vx_B;                       // '<Root>/Vx_B'
    real_T WheelDeltarad;              // '<Root>/Wheel Delta [rad]'
    real_T YawRaterads;                // '<Root>/Yaw Rate [rad//s]'
    real_T PID_I;                      // '<Root>/PID_I'
    real_T PID_D;                      // '<Root>/PID_D'
    real_T PID_N;                      // '<Root>/PID_N'
    real_T PID_P;                      // '<Root>/PID_P'
    real_T FR_in;                      // '<Root>/FR_in'
    real_T RR_in;                      // '<Root>/RR_in'
    real_T FL_in;                      // '<Root>/FL_in'
    real_T RL_in;                      // '<Root>/RL_in'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_PID_TV_T {
    real_T FR_out;                     // '<Root>/FR_out'
    real_T RR_out;                     // '<Root>/RR_out'
    real_T FL_out;                     // '<Root>/FL_out'
    real_T RL_out;                     // '<Root>/RL_out'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_PID_TV_T {
    const char_T * volatile errorStatus;

    //
    //  DataMapInfo:
    //  The following substructure contains information regarding
    //  structures generated in the model's C API.

    struct {
      rtwCAPI_ModelMappingInfo mmi;
    } DataMapInfo;
  };

  // Copy Constructor
  PID_TV(PID_TV const&) = delete;

  // Assignment Operator
  PID_TV& operator= (PID_TV const&) & = delete;

  // Move Constructor
  PID_TV(PID_TV &&) = delete;

  // Move Assignment Operator
  PID_TV& operator= (PID_TV &&) = delete;

  // Real-Time Model get method
  PID_TV::RT_MODEL_PID_TV_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_PID_TV_T *pExtU_PID_TV_T)
  {
    PID_TV_U = *pExtU_PID_TV_T;
  }

  // Root outports get method
  const ExtY_PID_TV_T &getExternalOutputs() const
  {
    return PID_TV_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  PID_TV();

  // Destructor
  ~PID_TV();

  // private data and function members
 private:
  // External inputs
  ExtU_PID_TV_T PID_TV_U;

  // External outputs
  ExtY_PID_TV_T PID_TV_Y;

  // Block states
  DW_PID_TV_T PID_TV_DW;

  // Real-Time Model
  RT_MODEL_PID_TV_T PID_TV_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Constant' : Unused code path elimination


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
//  '<Root>' : 'PID_TV'
//  '<S1>'   : 'PID_TV/PID_TV'
//  '<S2>'   : 'PID_TV/PID_TV/PID Controller'
//  '<S3>'   : 'PID_TV/PID_TV/Subsystem3'
//  '<S4>'   : 'PID_TV/PID_TV/PID Controller/Anti-windup'
//  '<S5>'   : 'PID_TV/PID_TV/PID Controller/D Gain'
//  '<S6>'   : 'PID_TV/PID_TV/PID Controller/Filter'
//  '<S7>'   : 'PID_TV/PID_TV/PID Controller/Filter ICs'
//  '<S8>'   : 'PID_TV/PID_TV/PID Controller/I Gain'
//  '<S9>'   : 'PID_TV/PID_TV/PID Controller/Ideal P Gain'
//  '<S10>'  : 'PID_TV/PID_TV/PID Controller/Ideal P Gain Fdbk'
//  '<S11>'  : 'PID_TV/PID_TV/PID Controller/Integrator'
//  '<S12>'  : 'PID_TV/PID_TV/PID Controller/Integrator ICs'
//  '<S13>'  : 'PID_TV/PID_TV/PID Controller/N Copy'
//  '<S14>'  : 'PID_TV/PID_TV/PID Controller/N Gain'
//  '<S15>'  : 'PID_TV/PID_TV/PID Controller/P Copy'
//  '<S16>'  : 'PID_TV/PID_TV/PID Controller/Parallel P Gain'
//  '<S17>'  : 'PID_TV/PID_TV/PID Controller/Reset Signal'
//  '<S18>'  : 'PID_TV/PID_TV/PID Controller/Saturation'
//  '<S19>'  : 'PID_TV/PID_TV/PID Controller/Saturation Fdbk'
//  '<S20>'  : 'PID_TV/PID_TV/PID Controller/Sum'
//  '<S21>'  : 'PID_TV/PID_TV/PID Controller/Sum Fdbk'
//  '<S22>'  : 'PID_TV/PID_TV/PID Controller/Tracking Mode'
//  '<S23>'  : 'PID_TV/PID_TV/PID Controller/Tracking Mode Sum'
//  '<S24>'  : 'PID_TV/PID_TV/PID Controller/Tsamp - Integral'
//  '<S25>'  : 'PID_TV/PID_TV/PID Controller/Tsamp - Ngain'
//  '<S26>'  : 'PID_TV/PID_TV/PID Controller/postSat Signal'
//  '<S27>'  : 'PID_TV/PID_TV/PID Controller/preSat Signal'
//  '<S28>'  : 'PID_TV/PID_TV/PID Controller/Anti-windup/Passthrough'
//  '<S29>'  : 'PID_TV/PID_TV/PID Controller/D Gain/External Parameters'
//  '<S30>'  : 'PID_TV/PID_TV/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S31>'  : 'PID_TV/PID_TV/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S32>'  : 'PID_TV/PID_TV/PID Controller/I Gain/External Parameters'
//  '<S33>'  : 'PID_TV/PID_TV/PID Controller/Ideal P Gain/Passthrough'
//  '<S34>'  : 'PID_TV/PID_TV/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S35>'  : 'PID_TV/PID_TV/PID Controller/Integrator/Discrete'
//  '<S36>'  : 'PID_TV/PID_TV/PID Controller/Integrator ICs/Internal IC'
//  '<S37>'  : 'PID_TV/PID_TV/PID Controller/N Copy/Disabled'
//  '<S38>'  : 'PID_TV/PID_TV/PID Controller/N Gain/External Parameters'
//  '<S39>'  : 'PID_TV/PID_TV/PID Controller/P Copy/Disabled'
//  '<S40>'  : 'PID_TV/PID_TV/PID Controller/Parallel P Gain/External Parameters'
//  '<S41>'  : 'PID_TV/PID_TV/PID Controller/Reset Signal/Disabled'
//  '<S42>'  : 'PID_TV/PID_TV/PID Controller/Saturation/Passthrough'
//  '<S43>'  : 'PID_TV/PID_TV/PID Controller/Saturation Fdbk/Disabled'
//  '<S44>'  : 'PID_TV/PID_TV/PID Controller/Sum/Sum_PID'
//  '<S45>'  : 'PID_TV/PID_TV/PID Controller/Sum Fdbk/Disabled'
//  '<S46>'  : 'PID_TV/PID_TV/PID Controller/Tracking Mode/Disabled'
//  '<S47>'  : 'PID_TV/PID_TV/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S48>'  : 'PID_TV/PID_TV/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S49>'  : 'PID_TV/PID_TV/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S50>'  : 'PID_TV/PID_TV/PID Controller/postSat Signal/Forward_Path'
//  '<S51>'  : 'PID_TV/PID_TV/PID Controller/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_PID_TV_h_

//
// File trailer for generated code.
//
// [EOF]
//
