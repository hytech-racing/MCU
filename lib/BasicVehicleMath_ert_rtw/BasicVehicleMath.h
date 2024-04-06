//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: BasicVehicleMath.h
//
// Code generated for Simulink model 'BasicVehicleMath'.
//
// Model version                  : 1.2
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr  5 20:57:25 2024
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

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Class declaration for model BasicVehicleMath
class BasicVehicleMath final
{
  // public data and function members
 public:
  // External inputs (root inport signals with default storage)
  struct ExtU_BasicVehicleMath_T {
    real_T Vx_Bms;                     // '<Root>/Vx_B [m//s]'
    real_T Vy_Bms;                     // '<Root>/Vy_B [m//s]'
    real_T YawRaterads;                // '<Root>/Yaw Rate [rad//s]'
    real_T DeltaLeftrad;               // '<Root>/Delta Left [rad]'
    real_T DeltaRightrad;              // '<Root>/Delta Right [rad]'
    real_T DeltaAvgrad;                // '<Root>/Delta Avg [rad]'
    real_T WheelOmegaFLrads;           // '<Root>/Wheel Omega FL [rad//s]'
    real_T WheelOmegaFRrads;           // '<Root>/Wheel Omega FR [rad//s]'
    real_T WheelOmegaRLrads;           // '<Root>/Wheel Omega RL [rad//s]'
    real_T WheelOmegaRRrads;           // '<Root>/Wheel Omega RR [rad//s]'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_BasicVehicleMath_T {
    real_T Betarad;                    // '<Root>/Beta [rad]'
    real_T AlphaFLrad;                 // '<Root>/Alpha FL [rad]'
    real_T AlphaFRrad;                 // '<Root>/Alpha FR [rad]'
    real_T AlphaRLrad;                 // '<Root>/Alpha RL [rad]'
    real_T AlphaRRrad;                 // '<Root>/Alpha RR [rad]'
    real_T LongitudinalCornerVelWFLms;
                                // '<Root>/Longitudinal Corner Vel W FL [m//s]'
    real_T LongitudinalCornerVelWFRms;
                                // '<Root>/Longitudinal Corner Vel W FR [m//s]'
    real_T LongitudinalCornerVelWRLms;
                                // '<Root>/Longitudinal Corner Vel W RL [m//s]'
    real_T LongitudinalCornerVelWRRms;
                                // '<Root>/Longitudinal Corner Vel W RR [m//s]'
    real_T KinematicDesiredYawRaterads;
                                // '<Root>/Kinematic Desired Yaw Rate [rad//s]'
    real_T SLFL;                       // '<Root>/SL FL'
    real_T SLFR;                       // '<Root>/SL FR'
    real_T SLRL;                       // '<Root>/SL RL'
    real_T SLRR;                       // '<Root>/SL RR'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_BasicVehicleMath_T {
    const char_T * volatile errorStatus;
  };

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

  // Root inports set method
  void setExternalInputs(const ExtU_BasicVehicleMath_T *pExtU_BasicVehicleMath_T)
  {
    BasicVehicleMath_U = *pExtU_BasicVehicleMath_T;
  }

  // Root outports get method
  const ExtY_BasicVehicleMath_T &getExternalOutputs() const
  {
    return BasicVehicleMath_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  BasicVehicleMath();

  // Destructor
  ~BasicVehicleMath();

  // private data and function members
 private:
  // External inputs
  ExtU_BasicVehicleMath_T BasicVehicleMath_U;

  // External outputs
  ExtY_BasicVehicleMath_T BasicVehicleMath_Y;

  // private member function(s) for subsystem '<S7>/Accel. Calc'
  static void BasicVehicleMath_AccelCalc(real_T rtu_CornerSpeed, real_T
    rtu_WheelOmega1, real_T *rty_SL);

  // private member function(s) for subsystem '<S7>/Brake Calc'
  static void BasicVehicleMath_BrakeCalc(real_T rtu_WheelOmega, real_T
    rtu_CornerSpeed, real_T *rty_SL);

  // Real-Time Model
  RT_MODEL_BasicVehicleMath_T BasicVehicleMath_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S7>/Scope' : Unused code path elimination
//  Block '<S8>/Scope' : Unused code path elimination
//  Block '<S9>/Scope' : Unused code path elimination
//  Block '<S10>/Scope' : Unused code path elimination
//  Block '<S5>/Constant' : Unused code path elimination
//  Block '<S5>/Constant1' : Unused code path elimination
//  Block '<S5>/Constant2' : Unused code path elimination
//  Block '<S5>/Constant3' : Unused code path elimination
//  Block '<S5>/Constant4' : Unused code path elimination
//  Block '<S5>/Constant5' : Unused code path elimination
//  Block '<S5>/Constant6' : Unused code path elimination
//  Block '<S5>/Constant7' : Unused code path elimination


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
//  '<S2>'   : 'BasicVehicleMath/Kinematic Yaw Rate'
//  '<S3>'   : 'BasicVehicleMath/Longitudinal Corner Vel B --> W Transformation'
//  '<S4>'   : 'BasicVehicleMath/Slip Angle and Corner Velocity'
//  '<S5>'   : 'BasicVehicleMath/Subsystem'
//  '<S6>'   : 'BasicVehicleMath/Slip Angle and Corner Velocity/MATLAB Function'
//  '<S7>'   : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FL'
//  '<S8>'   : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FR'
//  '<S9>'   : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RL'
//  '<S10>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RR'
//  '<S11>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FL/Accel. Calc'
//  '<S12>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FL/Brake Calc'
//  '<S13>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FL/If Action Subsystem'
//  '<S14>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FR/Accel. Calc'
//  '<S15>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FR/Brake Calc'
//  '<S16>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc FR/If Action Subsystem'
//  '<S17>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RL/Accel. Calc'
//  '<S18>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RL/Brake Calc'
//  '<S19>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RL/If Action Subsystem'
//  '<S20>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RR/Accel. Calc'
//  '<S21>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RR/Brake Calc'
//  '<S22>'  : 'BasicVehicleMath/Subsystem/Longitudinal Slip Calc RR/If Action Subsystem'

#endif                                 // RTW_HEADER_BasicVehicleMath_h_

//
// File trailer for generated code.
//
// [EOF]
//
