//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: BasicVehicleMath.h
//
// Code generated for Simulink model 'BasicVehicleMath'.
//
// Model version                  : 1.13
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Sat Apr 13 09:39:36 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_BasicVehicleMath_h_
#define RTW_HEADER_BasicVehicleMath_h_
#include "rtwtypes.h"
#include "BasicVehicleMath_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rtw_modelmap.h"
#include <cstring>

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  BasicVehicleMath_GetCAPIStaticMap(void);

// Class declaration for model BasicVehicleMath
class BasicVehicleMath final
{
  // public data and function members
 public:
  // Real-time Model Data Structure
  struct RT_MODEL_BasicVehicleMath_T {
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
  BasicVehicleMath(BasicVehicleMath const&) = delete;

  // Assignment Operator
  BasicVehicleMath& operator= (BasicVehicleMath const&) & = delete;

  // Move Constructor
  BasicVehicleMath(BasicVehicleMath &&) = delete;

  // Move Assignment Operator
  BasicVehicleMath& operator= (BasicVehicleMath &&) = delete;

  // Real-Time Model get method
  BasicVehicleMath::RT_MODEL_BasicVehicleMath_T * getRTM();

  // member function to set up the C-API information
  void setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI, const char_T
                     *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx);

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // model step function
  void step(const real_T *rtu_Vx_Bms, const real_T *rtu_Vy_Bms, const real_T
            *rtu_YawRaterads, const real_T *rtu_MotorOmegaFLrpm, const real_T
            *rtu_MotorOmegaFRrpm, const real_T *rtu_MotorOmegaRLrpm, const
            real_T *rtu_MotorOmegaRRrpm, const real_T *rtu_SteeringWheelAngleDeg,
            real_T *rty_BetaDeg, real_T *rty_AlphaFLDeg, real_T *rty_AlphaFRDeg,
            real_T *rty_AlphaRLDeg, real_T *rty_AlphaRRDeg, real_T
            *rty_LongitudinalCornerVelWFLm, real_T
            *rty_LongitudinalCornerVelWFRm, real_T
            *rty_LongitudinalCornerVelWRLm, real_T
            *rty_LongitudinalCornerVelWRRm, real_T
            *rty_KinematicDesiredYawRaterad, real_T *rty_SLFL, real_T *rty_SLFR,
            real_T *rty_SLRL, real_T *rty_SLRR, real_T *rty_WheelSteerAvgDeg,
            real_T *rty_WheelOmegaFLrads, real_T *rty_WheelOmegaFRrads, real_T
            *rty_WheelOmegaRLrads, real_T *rty_WheelOmegaRRrads);

  // Constructor
  BasicVehicleMath();

  // Destructor
  ~BasicVehicleMath();

  // private data and function members
 private:
  // private member function(s) for subsystem '<S17>/Accel. Calc'
  static void BasicVehicleMath_AccelCalc(real_T rtu_CornerSpeed, real_T
    rtu_WheelOmega1, real_T *rty_SL);

  // private member function(s) for subsystem '<S17>/Brake Calc'
  static void BasicVehicleMath_BrakeCalc(real_T rtu_WheelOmega, real_T
    rtu_CornerSpeed, real_T *rty_SL);

  // Real-Time Model
  RT_MODEL_BasicVehicleMath_T BasicVehicleMath_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S17>/Scope' : Unused code path elimination
//  Block '<S18>/Scope' : Unused code path elimination
//  Block '<S19>/Scope' : Unused code path elimination
//  Block '<S20>/Scope' : Unused code path elimination
//  Block '<S15>/Constant' : Unused code path elimination
//  Block '<S15>/Constant1' : Unused code path elimination
//  Block '<S15>/Constant2' : Unused code path elimination
//  Block '<S15>/Constant3' : Unused code path elimination
//  Block '<S15>/Constant4' : Unused code path elimination
//  Block '<S15>/Constant5' : Unused code path elimination
//  Block '<S15>/Constant6' : Unused code path elimination
//  Block '<S15>/Constant7' : Unused code path elimination


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
//  '<Root>' : 'BasicVehicleMath'
//  '<S1>'   : 'BasicVehicleMath/Body Slip'
//  '<S2>'   : 'BasicVehicleMath/Degrees to Radians'
//  '<S3>'   : 'BasicVehicleMath/Degrees to Radians1'
//  '<S4>'   : 'BasicVehicleMath/Degrees to Radians2'
//  '<S5>'   : 'BasicVehicleMath/Degrees to Radians3'
//  '<S6>'   : 'BasicVehicleMath/Degrees to Radians4'
//  '<S7>'   : 'BasicVehicleMath/Kinematic Yaw Rate'
//  '<S8>'   : 'BasicVehicleMath/Longitudinal Corner Vel B --> W Transformation'
//  '<S9>'   : 'BasicVehicleMath/Radians to Degrees'
//  '<S10>'  : 'BasicVehicleMath/Radians to Degrees1'
//  '<S11>'  : 'BasicVehicleMath/Radians to Degrees2'
//  '<S12>'  : 'BasicVehicleMath/Radians to Degrees3'
//  '<S13>'  : 'BasicVehicleMath/Radians to Degrees4'
//  '<S14>'  : 'BasicVehicleMath/Slip Angle and Corner Velocity'
//  '<S15>'  : 'BasicVehicleMath/Subsystem'
//  '<S16>'  : 'BasicVehicleMath/Slip Angle and Corner Velocity/MATLAB Function'
//  '<S17>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FL'
//  '<S18>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FR'
//  '<S19>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RL'
//  '<S20>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RR'
//  '<S21>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FL/Accel. Calc'
//  '<S22>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FL/Brake Calc'
//  '<S23>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FL/If Action Subsystem'
//  '<S24>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FR/Accel. Calc'
//  '<S25>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FR/Brake Calc'
//  '<S26>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FR/If Action Subsystem'
//  '<S27>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RL/Accel. Calc'
//  '<S28>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RL/Brake Calc'
//  '<S29>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RL/If Action Subsystem'
//  '<S30>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RR/Accel. Calc'
//  '<S31>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RR/Brake Calc'
//  '<S32>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RR/If Action Subsystem'

#endif                                 // RTW_HEADER_BasicVehicleMath_h_

//
// File trailer for generated code.
//
// [EOF]
//
