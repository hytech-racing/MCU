//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: NORMAL_FORCE_TV.cpp
//
// Code generated for Simulink model 'NORMAL_FORCE_TV'.
//
// Model version                  : 1.22
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Mon Apr 15 17:36:44 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "NORMAL_FORCE_TV.h"
#include "rtwtypes.h"
#include <cmath>
#include "NORMAL_FORCE_TV_capi.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "NORMAL_FORCE_TV_private.h"

// Output and update for referenced model: 'NORMAL_FORCE_TV'
void NORMAL_FORCE_TV::step(const boolean_T *rtu_useNormalForce, const real_T
  *rtu_FZ_FL, const real_T *rtu_FZ_FR, const real_T *rtu_FZ_RL, const real_T
  *rtu_FZ_RR, const real_T *rtu_TORQUE_IN_FL, const real_T *rtu_TORQUE_IN_FR,
  const real_T *rtu_TORQUE_IN_RL, const real_T *rtu_TORQUE_IN_RR, const
  boolean_T *rtu_usePIDTVBool, real_T *rty_FL_torque_out, real_T
  *rty_FR_torque_out, real_T *rty_RL_torque_out, real_T *rty_RR_torque_out,
  real_T *rty_Normal_Percent_FL, real_T *rty_Normal_Percent_FR, real_T
  *rty_Normal_Percent_RL, real_T *rty_Normal_Percent_RR)
{
  real_T rtb_Abs;
  real_T rtb_Abs1;
  real_T rtb_Abs2;
  real_T rtb_Abs3;

  // Abs: '<Root>/Abs'
  rtb_Abs = std::abs(*rtu_FZ_RL);

  // Abs: '<Root>/Abs1'
  rtb_Abs1 = std::abs(*rtu_FZ_FL);

  // Abs: '<Root>/Abs2'
  rtb_Abs2 = std::abs(*rtu_FZ_FR);

  // Abs: '<Root>/Abs3'
  rtb_Abs3 = std::abs(*rtu_FZ_RR);

  // MATLAB Function: '<Root>/MATLAB Function'
  if (*rtu_useNormalForce) {
    if (*rtu_usePIDTVBool) {
      real_T F_NET;
      real_T F_NET_LEFT;
      real_T F_NET_RIGHT;
      real_T T_NET_MAG;
      F_NET_LEFT = rtb_Abs1 + rtb_Abs;
      F_NET_RIGHT = rtb_Abs2 + rtb_Abs3;
      F_NET = std::abs(*rtu_TORQUE_IN_FL) + std::abs(*rtu_TORQUE_IN_RL);
      T_NET_MAG = std::abs(*rtu_TORQUE_IN_FR) + std::abs(*rtu_TORQUE_IN_RR);
      if (rtb_Abs1 > 0.0) {
        rtb_Abs1 /= F_NET_LEFT;
      } else {
        rtb_Abs1 = 0.0;
      }

      if (rtb_Abs2 > 0.0) {
        rtb_Abs2 /= F_NET_RIGHT;
      } else {
        rtb_Abs2 = 0.0;
      }

      if (rtb_Abs > 0.0) {
        rtb_Abs /= F_NET_LEFT;
      } else {
        rtb_Abs = 0.0;
      }

      if (rtb_Abs3 > 0.0) {
        rtb_Abs3 /= F_NET_RIGHT;
      } else {
        rtb_Abs3 = 0.0;
      }

      F_NET_RIGHT = *rtu_TORQUE_IN_FL;
      if (std::isnan(F_NET_RIGHT)) {
        F_NET_RIGHT = (rtNaN);
      } else if (F_NET_RIGHT < 0.0) {
        F_NET_RIGHT = -1.0;
      } else {
        F_NET_RIGHT = (F_NET_RIGHT > 0.0);
      }

      *rty_FL_torque_out = rtb_Abs1 * F_NET * F_NET_RIGHT;
      F_NET_RIGHT = *rtu_TORQUE_IN_FR;
      if (std::isnan(F_NET_RIGHT)) {
        F_NET_RIGHT = (rtNaN);
      } else if (F_NET_RIGHT < 0.0) {
        F_NET_RIGHT = -1.0;
      } else {
        F_NET_RIGHT = (F_NET_RIGHT > 0.0);
      }

      *rty_FR_torque_out = rtb_Abs2 * T_NET_MAG * F_NET_RIGHT;
      F_NET_RIGHT = *rtu_TORQUE_IN_RL;
      if (std::isnan(F_NET_RIGHT)) {
        F_NET_RIGHT = (rtNaN);
      } else if (F_NET_RIGHT < 0.0) {
        F_NET_RIGHT = -1.0;
      } else {
        F_NET_RIGHT = (F_NET_RIGHT > 0.0);
      }

      *rty_RL_torque_out = rtb_Abs * F_NET * F_NET_RIGHT;
      F_NET_RIGHT = *rtu_TORQUE_IN_RR;
      if (std::isnan(F_NET_RIGHT)) {
        F_NET_RIGHT = (rtNaN);
      } else if (F_NET_RIGHT < 0.0) {
        F_NET_RIGHT = -1.0;
      } else {
        F_NET_RIGHT = (F_NET_RIGHT > 0.0);
      }

      *rty_RR_torque_out = rtb_Abs3 * T_NET_MAG * F_NET_RIGHT;
    } else {
      real_T F_NET;
      real_T F_NET_RIGHT;
      real_T T_NET_MAG;
      F_NET = ((rtb_Abs1 + rtb_Abs2) + rtb_Abs) + rtb_Abs3;
      T_NET_MAG = ((std::abs(*rtu_TORQUE_IN_FL) + std::abs(*rtu_TORQUE_IN_FR)) +
                   std::abs(*rtu_TORQUE_IN_RL)) + std::abs(*rtu_TORQUE_IN_RR);
      if (rtb_Abs1 > 0.0) {
        rtb_Abs1 /= F_NET;
      } else {
        rtb_Abs1 = 0.0;
      }

      if (rtb_Abs2 > 0.0) {
        rtb_Abs2 /= F_NET;
      } else {
        rtb_Abs2 = 0.0;
      }

      if (rtb_Abs > 0.0) {
        rtb_Abs /= F_NET;
      } else {
        rtb_Abs = 0.0;
      }

      if (rtb_Abs3 > 0.0) {
        rtb_Abs3 /= F_NET;
      } else {
        rtb_Abs3 = 0.0;
      }

      F_NET_RIGHT = *rtu_TORQUE_IN_FL;
      if (std::isnan(F_NET_RIGHT)) {
        F_NET_RIGHT = (rtNaN);
      } else if (F_NET_RIGHT < 0.0) {
        F_NET_RIGHT = -1.0;
      } else {
        F_NET_RIGHT = (F_NET_RIGHT > 0.0);
      }

      *rty_FL_torque_out = rtb_Abs1 * T_NET_MAG * F_NET_RIGHT;
      F_NET_RIGHT = *rtu_TORQUE_IN_FR;
      if (std::isnan(F_NET_RIGHT)) {
        F_NET_RIGHT = (rtNaN);
      } else if (F_NET_RIGHT < 0.0) {
        F_NET_RIGHT = -1.0;
      } else {
        F_NET_RIGHT = (F_NET_RIGHT > 0.0);
      }

      *rty_FR_torque_out = rtb_Abs2 * T_NET_MAG * F_NET_RIGHT;
      F_NET_RIGHT = *rtu_TORQUE_IN_RL;
      if (std::isnan(F_NET_RIGHT)) {
        F_NET_RIGHT = (rtNaN);
      } else if (F_NET_RIGHT < 0.0) {
        F_NET_RIGHT = -1.0;
      } else {
        F_NET_RIGHT = (F_NET_RIGHT > 0.0);
      }

      *rty_RL_torque_out = rtb_Abs * T_NET_MAG * F_NET_RIGHT;
      F_NET_RIGHT = *rtu_TORQUE_IN_RR;
      if (std::isnan(F_NET_RIGHT)) {
        F_NET_RIGHT = (rtNaN);
      } else if (F_NET_RIGHT < 0.0) {
        F_NET_RIGHT = -1.0;
      } else {
        F_NET_RIGHT = (F_NET_RIGHT > 0.0);
      }

      *rty_RR_torque_out = rtb_Abs3 * T_NET_MAG * F_NET_RIGHT;
    }
  } else {
    rtb_Abs1 = 1.0;
    rtb_Abs2 = 1.0;
    rtb_Abs = 1.0;
    rtb_Abs3 = 1.0;
    *rty_FL_torque_out = *rtu_TORQUE_IN_FL;
    *rty_FR_torque_out = *rtu_TORQUE_IN_FR;
    *rty_RL_torque_out = *rtu_TORQUE_IN_RL;
    *rty_RR_torque_out = *rtu_TORQUE_IN_RR;
  }

  *rty_Normal_Percent_FL = rtb_Abs1;
  *rty_Normal_Percent_FR = rtb_Abs2;
  *rty_Normal_Percent_RL = rtb_Abs;
  *rty_Normal_Percent_RR = rtb_Abs3;

  // End of MATLAB Function: '<Root>/MATLAB Function'
}

// Model initialize function
void NORMAL_FORCE_TV::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // Initialize DataMapInfo substructure containing ModelMap for C API
  NORMAL_FORCE_TV_InitializeDataMapInfo((&NORMAL_FORCE_TV_M));
}

// Constructor
NORMAL_FORCE_TV::NORMAL_FORCE_TV() :
  NORMAL_FORCE_TV_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
NORMAL_FORCE_TV::~NORMAL_FORCE_TV() = default;

// Real-Time Model get method
NORMAL_FORCE_TV::RT_MODEL_NORMAL_FORCE_TV_T * NORMAL_FORCE_TV::getRTM()
{
  return (&NORMAL_FORCE_TV_M);
}

// member function to set up the C-API information
void NORMAL_FORCE_TV::setupCAPIInfo(rtwCAPI_ModelMappingInfo *rt_ParentMMI,
  const char_T *rt_ChildPath, int_T rt_ChildMMIIdx, int_T rt_CSTATEIdx)
{
  // Initialize Parent model MMI
  if ((rt_ParentMMI != (nullptr)) && (rt_ChildPath != (nullptr))) {
    rtwCAPI_SetChildMMI(*rt_ParentMMI, rt_ChildMMIIdx, &((&NORMAL_FORCE_TV_M)
      ->DataMapInfo.mmi));
    rtwCAPI_SetPath((&NORMAL_FORCE_TV_M)->DataMapInfo.mmi, rt_ChildPath);
    rtwCAPI_MMISetContStateStartIndex((&NORMAL_FORCE_TV_M)->DataMapInfo.mmi,
      rt_CSTATEIdx);
  }
}

// member function to setup error status pointer
void NORMAL_FORCE_TV::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&NORMAL_FORCE_TV_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
