//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: NORMAL_FORCE_TV.h
//
// Code generated for Simulink model 'NORMAL_FORCE_TV'.
//
// Model version                  : 1.30
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Sat Apr 20 04:12:24 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_NORMAL_FORCE_TV_h_
#define RTW_HEADER_NORMAL_FORCE_TV_h_
#include "rtwtypes.h"
#include "NORMAL_FORCE_TV_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "rtGetNaN.h"
#include "rtw_modelmap.h"
#include <cstring>

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  NORMAL_FORCE_TV_GetCAPIStaticMap(void);

// Class declaration for model NORMAL_FORCE_TV
class NORMAL_FORCE_TV final
{
  // public data and function members
 public:
  // Real-time Model Data Structure
  struct RT_MODEL_NORMAL_FORCE_TV_T {
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
  NORMAL_FORCE_TV(NORMAL_FORCE_TV const&) = delete;

  // Assignment Operator
  NORMAL_FORCE_TV& operator= (NORMAL_FORCE_TV const&) & = delete;

  // Move Constructor
  NORMAL_FORCE_TV(NORMAL_FORCE_TV &&) = delete;

  // Move Assignment Operator
  NORMAL_FORCE_TV& operator= (NORMAL_FORCE_TV &&) = delete;

  // Real-Time Model get method
  NORMAL_FORCE_TV::RT_MODEL_NORMAL_FORCE_TV_T * getRTM();

  // member function to set up the C-API information
  void setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T
                     *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx);

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // model step function
  void step(const boolean_T *rtu_useNormalForce, const real_T *rtu_FZ_FL, const
            real_T *rtu_FZ_FR, const real_T *rtu_FZ_RL, const real_T *rtu_FZ_RR,
            const real_T *rtu_TORQUE_IN_FL, const real_T *rtu_TORQUE_IN_FR,
            const real_T *rtu_TORQUE_IN_RL, const real_T *rtu_TORQUE_IN_RR,
            const boolean_T *rtu_usePIDTV, const real_T *rtu_TorqueLimit, real_T
            *rty_FL_torque_out, real_T *rty_FR_torque_out, real_T
            *rty_RL_torque_out, real_T *rty_RR_torque_out, real_T
            *rty_Normal_Percent_FL, real_T *rty_Normal_Percent_FR, real_T
            *rty_Normal_Percent_RL, real_T *rty_Normal_Percent_RR);

  // Constructor
  NORMAL_FORCE_TV();

  // Destructor
  ~NORMAL_FORCE_TV();

  // private data and function members
 private:
  // Real-Time Model
  RT_MODEL_NORMAL_FORCE_TV_T NORMAL_FORCE_TV_M;
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
//  '<Root>' : 'NORMAL_FORCE_TV'
//  '<S1>'   : 'NORMAL_FORCE_TV/MATLAB Function2'

#endif                                 // RTW_HEADER_NORMAL_FORCE_TV_h_

//
// File trailer for generated code.
//
// [EOF]
//
