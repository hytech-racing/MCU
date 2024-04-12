//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: HT08_CONTROL_SYSTEM.h
//
// Code generated for Simulink model 'HT08_CONTROL_SYSTEM'.
//
// Model version                  : 1.36
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Apr 11 22:49:42 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_HT08_CONTROL_SYSTEM_h_
#define RTW_HEADER_HT08_CONTROL_SYSTEM_h_
#include <math.h>
#include "rtwtypes.h"
#include "HT08_CONTROL_SYSTEM_types.h"
#include "BasicVehicleMath.h"
#include "POWER_LIMIT.h"
#include "PID_TV.h"
#include "NORMAL_FORCE_TV.h"
#include "LAUNCH_CONTROL.h"
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

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  HT08_CONTROL_SYSTEM_GetCAPIStaticMap(void);

// Class declaration for model HT08_CONTROL_SYSTEM
class HT08_CONTROL_SYSTEM final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_HT08_CONTROL_SYSTEM_T {
    real_T BetaDeg;                    // '<Root>/Vehicle Math'
    real_T AlphaFLDeg;                 // '<Root>/Vehicle Math'
    real_T AlphaFRDeg;                 // '<Root>/Vehicle Math'
    real_T AlphaRLDeg;                 // '<Root>/Vehicle Math'
    real_T AlphaRRDeg;                 // '<Root>/Vehicle Math'
    real_T LongCornerVelFL;            // '<Root>/Vehicle Math'
    real_T LongCornerVelFR;            // '<Root>/Vehicle Math'
    real_T LongCornerVelRL;            // '<Root>/Vehicle Math'
    real_T LongCornerVelRR;            // '<Root>/Vehicle Math'
    real_T DesiredYawRaterads;         // '<Root>/Vehicle Math'
    real_T SLFL;                       // '<Root>/Vehicle Math'
    real_T SLFR;                       // '<Root>/Vehicle Math'
    real_T SLRL;                       // '<Root>/Vehicle Math'
    real_T SLRR;                       // '<Root>/Vehicle Math'
    real_T WheelSteerAvgDeg;           // '<Root>/Vehicle Math'
    real_T PowerLimit_o6;              // '<Root>/Power Limit'
    real_T TorqueAdjustment;           // '<Root>/Power Limit'
    real_T PowerLimit_o8;              // '<Root>/Power Limit'
    real_T PowerLimit_o9;              // '<Root>/Power Limit'
    real_T PowerLimit_o10;             // '<Root>/Power Limit'
    real_T PowerLimit_o11;             // '<Root>/Power Limit'
    real_T FRTORQUEPID;                // '<S5>/PID_TV'
    real_T RRTORQUEPID;                // '<S5>/PID_TV'
    real_T FLTORQUEPID;                // '<S5>/PID_TV'
    real_T RLTORQUEPID;                // '<S5>/PID_TV'
    real_T YawErrorrads;               // '<S5>/PID_TV'
    real_T PID_TV_o6;                  // '<S5>/PID_TV'
    real_T TorqueNormalFL;             // '<S5>/Model'
    real_T TorqueNormalFR;             // '<S5>/Model'
    real_T TorqueNormalRL;             // '<S5>/Model'
    real_T TorqueNormalRR;             // '<S5>/Model'
    real_T Normal_Percent_FL;          // '<S5>/Model'
    real_T Normal_Percent_FR;          // '<S5>/Model'
    real_T Normal_Percent_RL;          // '<S5>/Model'
    real_T Normal_Percent_RR;          // '<S5>/Model'
    real_T PID_TV_o7;                  // '<S5>/PID_TV'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_HT08_CONTROL_SYSTEM_T {
    int_T CANPack_ModeSignalID;        // '<S1>/CAN Pack'
    int_T CANPack1_ModeSignalID;       // '<S1>/CAN Pack1'
    int_T CANPack2_ModeSignalID;       // '<S1>/CAN Pack2'
    int_T CANPack3_ModeSignalID;       // '<S1>/CAN Pack3'
    int_T CANPack4_ModeSignalID;       // '<S1>/CAN Pack4'
    int_T CANPack5_ModeSignalID;       // '<S1>/CAN Pack5'
    int_T CANPack6_ModeSignalID;       // '<S1>/CAN Pack6'
    int_T CANPack7_ModeSignalID;       // '<S1>/CAN Pack7'
    int_T CANPack8_ModeSignalID;       // '<S1>/CAN Pack8'
    int_T CANPack2_ModeSignalID_k;     // '<S4>/CAN Pack2'
    int_T CANPack_ModeSignalID_a;      // '<S4>/CAN Pack'
    int_T CANPack1_ModeSignalID_m;     // '<S4>/CAN Pack1'
    int_T CANPack3_ModeSignalID_m;     // '<S4>/CAN Pack3'
    int_T CANPack4_ModeSignalID_b;     // '<S4>/CAN Pack4'
    int_T CANPack5_ModeSignalID_p;     // '<S4>/CAN Pack5'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_HT08_CONTROL_SYSTEM_T {
    real_T SteeringWheelAngleDeg;      // '<Root>/Steering Wheel Angle [Deg]'
    real_T TorqueAverageNm;            // '<Root>/Torque Average [Nm]'
    real_T YawRaterads;                // '<Root>/Yaw Rate [rad//s]'
    real_T Vx_B;                       // '<Root>/Vx_B'
    real_T FZFL;                       // '<Root>/FZ FL'
    real_T FZFR;                       // '<Root>/FZ FR'
    real_T FZRL;                       // '<Root>/FZ RL'
    real_T FZRR;                       // '<Root>/FZ RR'
    real_T CurrentPowerkW;             // '<Root>/Current Power [kW]'
    real_T MotorOmegaFLrpm;            // '<Root>/Motor Omega FL [rpm]'
    real_T MotorOmegaFRrpm;            // '<Root>/Motor Omega FR [rpm]'
    real_T MotorOmegaRLrpm;            // '<Root>/Motor Omega RL [rpm]'
    real_T MotorOmegaRRrpm;            // '<Root>/Motor Omega RR [rpm]'
    boolean_T usePIDTV;                // '<Root>/usePIDTV'
    boolean_T useNormalForce;          // '<Root>/useNormalForce'
    boolean_T usePowerLimit;           // '<Root>/usePowerLimit'
    boolean_T usePIDPowerLimit;        // '<Root>/usePIDPowerLimit'
    boolean_T useLaunch;               // '<Root>/useLaunch'
    real_T Vy_B;                       // '<Root>/Vy_B'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_HT08_CONTROL_SYSTEM_T {
    real_T FinalTorqueFL;              // '<Root>/Final Torque FL'
    real_T FinalTorqueFR;              // '<Root>/Final Torque FR'
    real_T FinalTorqueRL;              // '<Root>/Final Torque RL'
    real_T FinalTorqueRR;              // '<Root>/Final Torque RR'
    real_T PowerLimStatus;             // '<Root>/Power Lim Status'
    CAN_MESSAGE_BUS controllerBus_vehm_alpha_deg;// '<Root>/controllerBus_vehm_alpha_deg' 
    CAN_MESSAGE_BUS controllerBus_vehm_sl;// '<Root>/controllerBus_vehm_sl'
    CAN_MESSAGE_BUS controllerBus_vehm_long_corner_;
                                 // '<Root>/controllerBus_vehm_long_corner_vel'
    CAN_MESSAGE_BUS controllerBus_vehm_wheel_steer_;
                             // '<Root>/controllerBus_vehm_wheel_steer_avg_deg'
    CAN_MESSAGE_BUS controllerBus_vehm_kin_desired_;
                      // '<Root>/controllerBus_vehm_kin_desired_yaw_rate_rad_s'
    CAN_MESSAGE_BUS controllerBus_vehm_beta_deg;// '<Root>/controllerBus_vehm_beta_deg' 
    CAN_MESSAGE_BUS controllerBus_controller_boolea;
                                   // '<Root>/controllerBus_controller_boolean'
    CAN_MESSAGE_BUS controllerBus_controller_normal;
                               // '<Root>/controllerBus_controller_normal_dist'
    CAN_MESSAGE_BUS controllerBus_controller_norm_p;
                             // '<Root>/controllerBus_controller_normal_torque'
    CAN_MESSAGE_BUS controllerBus_controller_pid_ya;
                                   // '<Root>/controllerBus_controller_pid_yaw'
    CAN_MESSAGE_BUS controllerBus_controller_pid__p;
                            // '<Root>/controllerBus_controller_pid_yaw_torque'
    CAN_MESSAGE_BUS controllerBus_controller_power_;
                                 // '<Root>/controllerBus_controller_power_lim'
    CAN_MESSAGE_BUS controllerBus_controller_powe_p;
                      // '<Root>/controllerBus_controller_power_lim_corner_pow'
    CAN_MESSAGE_BUS controllerBus_controller_pow_pn;
                          // '<Root>/controllerBus_controller_power_lim_torque'
    CAN_MESSAGE_BUS controllerBus_controller_initia;
                        // '<Root>/controllerBus_controller_initial_torque_req'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_HT08_CONTROL_SYSTEM_T {
    const char_T *errorStatus;

    //
    //  DataMapInfo:
    //  The following substructure contains information regarding
    //  structures generated in the model's C API.

    struct {
      rtwCAPI_ModelMappingInfo mmi;
      void* dataAddress[50];
      int32_T* vardimsAddress[50];
      RTWLoggingFcnPtr loggingPtrs[50];
      rtwCAPI_ModelMappingInfo* childMMI[5];
    } DataMapInfo;
  };

  // Copy Constructor
  HT08_CONTROL_SYSTEM(HT08_CONTROL_SYSTEM const&) = delete;

  // Assignment Operator
  HT08_CONTROL_SYSTEM& operator= (HT08_CONTROL_SYSTEM const&) & = delete;

  // Move Constructor
  HT08_CONTROL_SYSTEM(HT08_CONTROL_SYSTEM &&) = delete;

  // Move Assignment Operator
  HT08_CONTROL_SYSTEM& operator= (HT08_CONTROL_SYSTEM &&) = delete;

  // Real-Time Model get method
  HT08_CONTROL_SYSTEM::RT_MODEL_HT08_CONTROL_SYSTEM_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_HT08_CONTROL_SYSTEM_T
    *pExtU_HT08_CONTROL_SYSTEM_T)
  {
    HT08_CONTROL_SYSTEM_U = *pExtU_HT08_CONTROL_SYSTEM_T;
  }

  // Root outports get method
  const ExtY_HT08_CONTROL_SYSTEM_T &getExternalOutputs() const
  {
    return HT08_CONTROL_SYSTEM_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  HT08_CONTROL_SYSTEM();

  // Destructor
  ~HT08_CONTROL_SYSTEM();

  // private data and function members
 private:
  // External inputs
  ExtU_HT08_CONTROL_SYSTEM_T HT08_CONTROL_SYSTEM_U;

  // External outputs
  ExtY_HT08_CONTROL_SYSTEM_T HT08_CONTROL_SYSTEM_Y;

  // Block signals
  B_HT08_CONTROL_SYSTEM_T HT08_CONTROL_SYSTEM_B;

  // Block states
  DW_HT08_CONTROL_SYSTEM_T HT08_CONTROL_SYSTEM_DW;

  // model instance variable for '<S2>/Model3'
  LAUNCH_CONTROL Model3MDLOBJ1;

  // model instance variable for '<Root>/Power Limit'
  POWER_LIMIT Power_LimitMDLOBJ2;

  // model instance variable for '<Root>/Vehicle Math'
  BasicVehicleMath Vehicle_MathMDLOBJ3;

  // model instance variable for '<S5>/Model'
  NORMAL_FORCE_TV ModelMDLOBJ4;

  // model instance variable for '<S5>/PID_TV'
  PID_TV PID_TVMDLOBJ5;

  // Real-Time Model
  RT_MODEL_HT08_CONTROL_SYSTEM_T HT08_CONTROL_SYSTEM_M;
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
//  '<Root>' : 'HT08_CONTROL_SYSTEM'
//  '<S1>'   : 'HT08_CONTROL_SYSTEM/Control System CAN Msg'
//  '<S2>'   : 'HT08_CONTROL_SYSTEM/Launch Control'
//  '<S3>'   : 'HT08_CONTROL_SYSTEM/Merge Torque'
//  '<S4>'   : 'HT08_CONTROL_SYSTEM/VEHM CAN Msg'
//  '<S5>'   : 'HT08_CONTROL_SYSTEM/Yaw and Normal Force TV'

#endif                                 // RTW_HEADER_HT08_CONTROL_SYSTEM_h_

//
// File trailer for generated code.
//
// [EOF]
//
