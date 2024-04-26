//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TORQUE_BIAS.h
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
#ifndef RTW_HEADER_TORQUE_BIAS_h_
#define RTW_HEADER_TORQUE_BIAS_h_
#include "rtwtypes.h"
#include "TORQUE_BIAS_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "rtGetNaN.h"
#include "rtw_modelmap.h"
#include <cstring>

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  TORQUE_BIAS_GetCAPIStaticMap(void);

// Class declaration for model TORQUE_BIAS
class TORQUE_BIAS final
{
  // public data and function members
 public:
  // Real-time Model Data Structure
  struct RT_MODEL_TORQUE_BIAS_T {
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
  TORQUE_BIAS(TORQUE_BIAS const&) = delete;

  // Assignment Operator
  TORQUE_BIAS& operator= (TORQUE_BIAS const&) & = delete;

  // Move Constructor
  TORQUE_BIAS(TORQUE_BIAS &&) = delete;

  // Move Assignment Operator
  TORQUE_BIAS& operator= (TORQUE_BIAS &&) = delete;

  // Real-Time Model get method
  TORQUE_BIAS::RT_MODEL_TORQUE_BIAS_T * getRTM();

  // member function to set up the C-API information
  void setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T
                     *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx);

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // model step function
  void step(const boolean_T *rtu_useTorqueBias, const real_T
            *rtu_ModeConstrainedTorqueReq, const real_T
            *rtu_DriveTorquePercentFront, const real_T
            *rtu_BrakeTorquePercentFront, const real_T *rtu_AbsoluteTorqueLimit,
            real_T *rty_BiasConstrainedTorqueAvgFro, real_T
            *rty_BiasConstrainedTorqueAvgRea);

  // Constructor
  TORQUE_BIAS();

  // Destructor
  ~TORQUE_BIAS();

  // private data and function members
 private:
  // Real-Time Model
  RT_MODEL_TORQUE_BIAS_T TORQUE_BIAS_M;
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
//  '<Root>' : 'TORQUE_BIAS'
//  '<S1>'   : 'TORQUE_BIAS/If Action Subsystem'
//  '<S2>'   : 'TORQUE_BIAS/If Action Subsystem1'
//  '<S3>'   : 'TORQUE_BIAS/If Action Subsystem1/MATLAB Function'

#endif                                 // RTW_HEADER_TORQUE_BIAS_h_

//
// File trailer for generated code.
//
// [EOF]
//
