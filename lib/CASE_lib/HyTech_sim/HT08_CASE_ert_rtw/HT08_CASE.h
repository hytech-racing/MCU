//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: HT08_CASE.h
//
// Code generated for Simulink model 'HT08_CASE'.
//
// Model version                  : 1.70
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Apr 26 01:22:02 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_HT08_CASE_h_
#define RTW_HEADER_HT08_CASE_h_
#include <math.h>
#include "rtwtypes.h"
#include "HT08_CASE_types.h"
#include "BasicVehicleMath.h"
#include "TORQUE_BIAS.h"
#include "TRACTION_CONTROL.h"
#include "PID_TV.h"
#include "NORMAL_FORCE_TV.h"
#include "POWER_LIMIT.h"
#include "NOREGEN_5KPH.h"
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
  HT08_CASE_GetCAPIStaticMap(void);

// Class declaration for model HT08_CASE
class HT08_CASE final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_HT08_CASE_T {
    real_T BetaDeg;                    // '<Root>/Vehicle Math'
    real_T AlphaFLDeg;                 // '<Root>/Vehicle Math'
    real_T AlphaFRDeg;                 // '<Root>/Vehicle Math'
    real_T AlphaRLDeg;                 // '<Root>/Vehicle Math'
    real_T AlphaRRDeg;                 // '<Root>/Vehicle Math'
    real_T LongCornerVelFL;            // '<Root>/Vehicle Math'
    real_T LongCornerVelFR;            // '<Root>/Vehicle Math'
    real_T LongCornerVelRL;            // '<Root>/Vehicle Math'
    real_T LongCornerVelRR;            // '<Root>/Vehicle Math'
    real_T VehicleMath_o10;            // '<Root>/Vehicle Math'
    real_T SLFL;                       // '<Root>/Vehicle Math'
    real_T SLFR;                       // '<Root>/Vehicle Math'
    real_T SLRL;                       // '<Root>/Vehicle Math'
    real_T SLRR;                       // '<Root>/Vehicle Math'
    real_T WheelSteerAvgDeg;           // '<Root>/Vehicle Math'
    real_T modeConstrainedTorqueRequest;// '<Root>/Vehicle Math'
    real_T VehicleMath_o21;            // '<Root>/Vehicle Math'
    real_T VehicleMath_o22;            // '<Root>/Vehicle Math'
    real_T VehicleMath_o23;            // '<Root>/Vehicle Math'
    real_T VehicleMath_o24;            // '<Root>/Vehicle Math'
    real_T Model1_o1;                  // '<Root>/Model1'
    real_T Model1_o2;                  // '<Root>/Model1'
    real_T TCS_o1;                     // '<Root>/TCS'
    real_T TCS_o2;                     // '<Root>/TCS'
    real_T TCS_o3;                     // '<Root>/TCS'
    real_T TCS_o4;                     // '<Root>/TCS'
    real_T TCS_o5;                     // '<Root>/TCS'
    real_T TCS_o6;                     // '<Root>/TCS'
    real_T TCS_o7;                     // '<Root>/TCS'
    real_T TCS_o8;                     // '<Root>/TCS'
    real_T TCS_o9[8];                  // '<Root>/TCS'
    real_T FRTORQUEPID;                // '<S4>/PID_TV'
    real_T RRTORQUEPID;                // '<S4>/PID_TV'
    real_T FLTORQUEPID;                // '<S4>/PID_TV'
    real_T RLTORQUEPID;                // '<S4>/PID_TV'
    real_T PID_TV_o5;                  // '<S4>/PID_TV'
    real_T PID_TV_o6;                  // '<S4>/PID_TV'
    real_T TorqueNormalFL;             // '<S4>/Model'
    real_T TorqueNormalFR;             // '<S4>/Model'
    real_T TorqueNormalRL;             // '<S4>/Model'
    real_T TorqueNormalRR;             // '<S4>/Model'
    real_T Normal_Percent_FL;          // '<S4>/Model'
    real_T Normal_Percent_FR;          // '<S4>/Model'
    real_T Normal_Percent_RL;          // '<S4>/Model'
    real_T Normal_Percent_RR;          // '<S4>/Model'
    real_T PowerLimTorqueFL;           // '<Root>/Power Limit'
    real_T PowerLimTorqueFR;           // '<Root>/Power Limit'
    real_T PowerLimTorqueRL;           // '<Root>/Power Limit'
    real_T PowerLimTorqueRR;           // '<Root>/Power Limit'
    real_T PowerLimit_o5;              // '<Root>/Power Limit'
    real_T PowerLimit_o6;              // '<Root>/Power Limit'
    real_T TorqueAdjustment;           // '<Root>/Power Limit'
    real_T PowerLimit_o8;              // '<Root>/Power Limit'
    real_T PowerLimit_o9;              // '<Root>/Power Limit'
    real_T PowerLimit_o10;             // '<Root>/Power Limit'
    real_T PowerLimit_o11;             // '<Root>/Power Limit'
    real_T Model_o5;                   // '<Root>/Model'
    real_T Model_o6;                   // '<Root>/Model'
    real_T Model_o7;                   // '<Root>/Model'
    real_T Model_o8;                   // '<Root>/Model'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_HT08_CASE_T {
    int_T CANPack_ModeSignalID;        // '<S1>/CAN Pack'
    int_T CANPack1_ModeSignalID;       // '<S1>/CAN Pack1'
    int_T CANPack2_ModeSignalID;       // '<S1>/CAN Pack2'
    int_T CANPack3_ModeSignalID;       // '<S1>/CAN Pack3'
    int_T CANPack4_ModeSignalID;       // '<S1>/CAN Pack4'
    int_T CANPack5_ModeSignalID;       // '<S1>/CAN Pack5'
    int_T CANPack6_ModeSignalID;       // '<S1>/CAN Pack6'
    int_T CANPack7_ModeSignalID;       // '<S1>/CAN Pack7'
    int_T CANPack8_ModeSignalID;       // '<S1>/CAN Pack8'
    int_T CANPack9_ModeSignalID;       // '<S1>/CAN Pack9'
    int_T CANPack10_ModeSignalID;      // '<S1>/CAN Pack10'
    int_T CANPack11_ModeSignalID;      // '<S1>/CAN Pack11'
    int_T CANPack12_ModeSignalID;      // '<S1>/CAN Pack12'
    int_T CANPack13_ModeSignalID;      // '<S1>/CAN Pack13'
    int_T CANPack14_ModeSignalID;      // '<S1>/CAN Pack14'
    int_T CANPack15_ModeSignalID;      // '<S1>/CAN Pack15'
    int_T CANPack16_ModeSignalID;      // '<S1>/CAN Pack16'
    int_T CANPack2_ModeSignalID_k;     // '<S3>/CAN Pack2'
    int_T CANPack_ModeSignalID_a;      // '<S3>/CAN Pack'
    int_T CANPack1_ModeSignalID_m;     // '<S3>/CAN Pack1'
    int_T CANPack3_ModeSignalID_m;     // '<S3>/CAN Pack3'
    int_T CANPack4_ModeSignalID_b;     // '<S3>/CAN Pack4'
    int_T CANPack5_ModeSignalID_p;     // '<S3>/CAN Pack5'
    int_T CANPack6_ModeSignalID_h;     // '<S3>/CAN Pack6'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_HT08_CASE_T {
    real_T SteeringWheelAngleDeg;      // '<Root>/Steering Wheel Angle [Deg]'
    real_T TorqueAverageNm;            // '<Root>/Torque Average [Nm]'
    real_T YawRaterads;                // '<Root>/Yaw Rate [rad//s]'
    real_T Vx_B;                       // '<Root>/Vx_B'
    real_T FZFL;                       // '<Root>/FZ FL'
    real_T FZFR;                       // '<Root>/FZ FR'
    real_T FZRL;                       // '<Root>/FZ RL'
    real_T FZRR;                       // '<Root>/FZ RR'
    real_T CurrentElectricalPowerkW;  // '<Root>/Current Electrical Power [kW]'
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
    real_T YawPIDConfig[3];            // '<Root>/Yaw PID Config'
    real_T AbsoluteTorqueLimit;        // '<Root>/Absolute Torque Limit'
    boolean_T useTractionControl;      // '<Root>/useTractionControl'
    real_T TCS_SLThreshold;            // '<Root>/TCS_SLThreshold'
    real_T LaunchSL;                   // '<Root>/Launch SL'
    real_T LaunchDeadZone;             // '<Root>/Launch Dead Zone'
    real_T TCSPIDConfig[3];            // '<Root>/TCS PID Config'
    real_T LaunchVelThreshold;         // '<Root>/Launch Vel Threshold'
    real_T TCSVelThreshold;            // '<Root>/TCS Vel Threshold'
    real_T YawPIDErrorThreshold;       // '<Root>/Yaw PID Error Threshold'
    real_T YawPIDVelThreshold;         // '<Root>/Yaw PID Vel Threshold'
    real_T YawPIDCoastThreshold;       // '<Root>/Yaw PID Coast Threshold'
    boolean_T useTCSLimitedYawPID;     // '<Root>/useTCSLimitedYawPID'
    real_T YawPIDMaxDifferential;      // '<Root>/Yaw PID Max Differential'
    boolean_T useDecoupledYawBrakes;   // '<Root>/useDecoupledYawBrakes'
    real_T YawPIDBrakesConfig[3];      // '<Root>/Yaw PID Brakes Config'
    real_T decoupledYawPIDBrakesMaxDIffere;
                               // '<Root>/decoupledYawPIDBrakesMaxDIfferential'
    boolean_T useDiscontinuousYawPIDBrakes;// '<Root>/useDiscontinuousYawPIDBrakes' 
    real_T discontinuousBrakesPercentThres;
                                // '<Root>/discontinuousBrakesPercentThreshold'
    real_T TorqueMode;                 // '<Root>/Torque Mode'
    real_T RegenLimit;                 // '<Root>/Regen Limit'
    boolean_T useNoRegen5kph;          // '<Root>/useNoRegen5kph'
    boolean_T useTorqueBias;           // '<Root>/useTorqueBias'
    real_T DriveTorquePercentFront;    // '<Root>/Drive Torque Percent Front'
    real_T BrakeTorquePercentFront;    // '<Root>/Brake Torque Percent Front'
    real_T MechPowerMaxkW;             // '<Root>/Mech Power Max [kW]'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_HT08_CASE_T {
    real_T FinalTorqueFL;              // '<Root>/Final Torque FL'
    real_T FinalTorqueFR;              // '<Root>/Final Torque FR'
    real_T FinalTorqueRL;              // '<Root>/Final Torque RL'
    real_T FinalTorqueRR;              // '<Root>/Final Torque RR'
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
    CAN_MESSAGE_BUS controllerBus_controller_tcs_co;
                                // '<Root>/controllerBus_controller_tcs_config'
    CAN_MESSAGE_BUS controllerBus_controller_tcs_st;
                                // '<Root>/controllerBus_controller_tcs_status'
    CAN_MESSAGE_BUS controllerBus_controller_tcs_pi;
                             // '<Root>/controllerBus_controller_tcs_pid_input'
    CAN_MESSAGE_BUS controllerBus_controller_tcs__p;
                            // '<Root>/controllerBus_controller_tcs_pid_output'
    CAN_MESSAGE_BUS controllerBus_controller_tcs_to;
                                // '<Root>/controllerBus_controller_tcs_torque'
    CAN_MESSAGE_BUS controllerBus_controller_regen_;
                         // '<Root>/controllerBus_controller_regen_5kph_torque'
    CAN_MESSAGE_BUS controllerBus_controller_rege_p;
                         // '<Root>/controllerBus_controller_regen_5kph_status'
    CAN_MESSAGE_BUS controllerBus_controller_torque;
                               // '<Root>/controllerBus_controller_torque_bias'
    CAN_MESSAGE_BUS controllerBus_vehm_wheel_lin_ve;
                                   // '<Root>/controllerBus_vehm_wheel_lin_vel'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_HT08_CASE_T {
    const char_T *errorStatus;

    //
    //  DataMapInfo:
    //  The following substructure contains information regarding
    //  structures generated in the model's C API.

    struct {
      rtwCAPI_ModelMappingInfo mmi;
      void* dataAddress[60];
      int32_T* vardimsAddress[60];
      RTWLoggingFcnPtr loggingPtrs[60];
      rtwCAPI_ModelMappingInfo* childMMI[7];
    } DataMapInfo;
  };

  // Copy Constructor
  HT08_CASE(HT08_CASE const&) = delete;

  // Assignment Operator
  HT08_CASE& operator= (HT08_CASE const&) & = delete;

  // Move Constructor
  HT08_CASE(HT08_CASE &&) = delete;

  // Move Assignment Operator
  HT08_CASE& operator= (HT08_CASE &&) = delete;

  // Real-Time Model get method
  HT08_CASE::RT_MODEL_HT08_CASE_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_HT08_CASE_T *pExtU_HT08_CASE_T)
  {
    HT08_CASE_U = *pExtU_HT08_CASE_T;
  }

  // Root outports get method
  const ExtY_HT08_CASE_T &getExternalOutputs() const
  {
    return HT08_CASE_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  HT08_CASE();

  // Destructor
  ~HT08_CASE();

  // private data and function members
 private:
  // External inputs
  ExtU_HT08_CASE_T HT08_CASE_U;

  // External outputs
  ExtY_HT08_CASE_T HT08_CASE_Y;

  // Block signals
  B_HT08_CASE_T HT08_CASE_B;

  // Block states
  DW_HT08_CASE_T HT08_CASE_DW;

  // model instance variable for '<Root>/Model'
  NOREGEN_5KPH ModelMDLOBJ1;

  // model instance variable for '<Root>/Model1'
  TORQUE_BIAS Model1MDLOBJ2;

  // model instance variable for '<Root>/Power Limit'
  POWER_LIMIT Power_LimitMDLOBJ3;

  // model instance variable for '<Root>/TCS'
  TRACTION_CONTROL TCSMDLOBJ4;

  // model instance variable for '<Root>/Vehicle Math'
  BasicVehicleMath Vehicle_MathMDLOBJ5;

  // model instance variable for '<S4>/Model'
  NORMAL_FORCE_TV ModelMDLOBJ6;

  // model instance variable for '<S4>/PID_TV'
  PID_TV PID_TVMDLOBJ7;

  // Real-Time Model
  RT_MODEL_HT08_CASE_T HT08_CASE_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/Add' : Unused code path elimination
//  Block '<S2>/Fcn' : Unused code path elimination


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
//  '<Root>' : 'HT08_CASE'
//  '<S1>'   : 'HT08_CASE/Control System CAN Msg'
//  '<S2>'   : 'HT08_CASE/Final Attempted Torque Average'
//  '<S3>'   : 'HT08_CASE/VEHM CAN Msg'
//  '<S4>'   : 'HT08_CASE/Yaw and Nor mal Force TV'

#endif                                 // RTW_HEADER_HT08_CASE_h_

//
// File trailer for generated code.
//
// [EOF]
//
