//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: NOREGEN_5KPH.h
//
// Code generated for Simulink model 'NOREGEN_5KPH'.
//
// Model version                  : 1.6
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr 26 00:57:52 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_NOREGEN_5KPH_h_
#define RTW_HEADER_NOREGEN_5KPH_h_
#include "rtwtypes.h"
#include "NOREGEN_5KPH_types.h"
#include "rtw_modelmap.h"
#include <cstring>

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  NOREGEN_5KPH_GetCAPIStaticMap(void);

// Class declaration for model NOREGEN_5KPH
class NOREGEN_5KPH final
{
  // public data and function members
 public:
  // Real-time Model Data Structure
  struct RT_MODEL_NOREGEN_5KPH_T {
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
  NOREGEN_5KPH(NOREGEN_5KPH const&) = delete;

  // Assignment Operator
  NOREGEN_5KPH& operator= (NOREGEN_5KPH const&) & = delete;

  // Move Constructor
  NOREGEN_5KPH(NOREGEN_5KPH &&) = delete;

  // Move Assignment Operator
  NOREGEN_5KPH& operator= (NOREGEN_5KPH &&) = delete;

  // Real-Time Model get method
  NOREGEN_5KPH::RT_MODEL_NOREGEN_5KPH_T * getRTM();

  // member function to set up the C-API information
  void setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T
                     *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx);

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // model step function
  void step(const real_T *rtu_PowerLimTorqueFL, const real_T
            *rtu_PowerLimTorqueFR, const real_T *rtu_PowerLimTorqueRL, const
            real_T *rtu_PowerLimTorqueRR, const boolean_T *rtu_useNoRegen5kph,
            const real_T *rtu_WheelLinearVelFLms, const real_T
            *rtu_WheelLinearVelFRms, const real_T *rtu_WheelLinearVelRLms, const
            real_T *rtu_WheelLinearVelRRms, const real_T
            *rtu_ModeConstrainedTorqueReq, real_T *rty_Regen5KPHTorqueFL, real_T
            *rty_Regen5KPHTorqueFR, real_T *rty_Regen5KPHTorqueRL, real_T
            *rty_Regen5KPHTorqueRR, real_T *rty_Regen5KPHStatusFL, real_T
            *rty_Regen5KPHStatusFR, real_T *rty_Regen5KPHStatusRL, real_T
            *rty_Regen5KPHStatusRR);

  // Constructor
  NOREGEN_5KPH();

  // Destructor
  ~NOREGEN_5KPH();

  // private data and function members
 private:
  // Real-Time Model
  RT_MODEL_NOREGEN_5KPH_T NOREGEN_5KPH_M;
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
//  '<Root>' : 'NOREGEN_5KPH'
//  '<S1>'   : 'NOREGEN_5KPH/If Action Subsystem'
//  '<S2>'   : 'NOREGEN_5KPH/If Action Subsystem1'
//  '<S3>'   : 'NOREGEN_5KPH/MATLAB Function'
//  '<S4>'   : 'NOREGEN_5KPH/If Action Subsystem1/MATLAB Function'

#endif                                 // RTW_HEADER_NOREGEN_5KPH_h_

//
// File trailer for generated code.
//
// [EOF]
//
