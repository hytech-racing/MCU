//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: HT08_CASE.cpp
//
// Code generated for Simulink model 'HT08_CASE'.
//
// Model version                  : 1.61
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Sat Apr 20 04:12:55 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "HT08_CASE.h"
#include "rtwtypes.h"
#include "HT08_CASE_capi.h"
#include "HT08_CASE_private.h"
#include "POWER_LIMIT.h"
#include "TRACTION_CONTROL.h"
#include "BasicVehicleMath.h"
#include "NORMAL_FORCE_TV.h"
#include "PID_TV.h"

// Model step function
void HT08_CASE::step()
{
  real_T rtb_VehicleMath_o16;
  real_T rtb_VehicleMath_o17;
  real_T rtb_VehicleMath_o18;
  real_T rtb_VehicleMath_o19;

  // S-Function (scanpack): '<S1>/CAN Pack' incorporates:
  //   Inport generated from: '<Root>/useLaunch'
  //   Inport generated from: '<Root>/useNormalForce'
  //   Inport generated from: '<Root>/usePIDPowerLimit'
  //   Inport generated from: '<Root>/usePIDTV'
  //   Inport generated from: '<Root>/usePowerLimit'
  //   Inport generated from: '<Root>/useTractionControl'
  //   Outport generated from: '<Root>/Out Bus Element2'

  // S-Function (scanpack): '<S1>/CAN Pack'
  HT08_CASE_Y.controllerBus_controller_boolea.ID = 2028U;
  HT08_CASE_Y.controllerBus_controller_boolea.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_boolea.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_boolea.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_boolea.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_boolea.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_boolea.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_boolea.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_boolea.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_boolea.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_boolea.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_boolea.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 1
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (HT08_CASE_U.useLaunch);

        // no scaling required
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (boolean_T)(1)) {
          packedValue = (uint8_T) 1;
        } else if (packingValue < (boolean_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CASE_Y.controllerBus_controller_boolea.Data[0] | (uint8_T)
              ((uint8_T)(packedValue & (uint8_T)0x1U));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 2
    //   length                  = 1
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (HT08_CASE_U.useNormalForce);

        // no scaling required
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (boolean_T)(1)) {
          packedValue = (uint8_T) 1;
        } else if (packingValue < (boolean_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CASE_Y.controllerBus_controller_boolea.Data[0] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 2));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 3
    //   length                  = 1
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (HT08_CASE_U.usePIDPowerLimit);

        // no scaling required
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (boolean_T)(1)) {
          packedValue = (uint8_T) 1;
        } else if (packingValue < (boolean_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CASE_Y.controllerBus_controller_boolea.Data[0] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 3));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 1
    //   length                  = 1
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (HT08_CASE_U.usePIDTV);

        // no scaling required
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (boolean_T)(1)) {
          packedValue = (uint8_T) 1;
        } else if (packingValue < (boolean_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CASE_Y.controllerBus_controller_boolea.Data[0] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 1));
          }
        }
      }
    }

    // --------------- START Packing signal 4 ------------------
    //   startBit                = 4
    //   length                  = 1
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (HT08_CASE_U.usePowerLimit);

        // no scaling required
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (boolean_T)(1)) {
          packedValue = (uint8_T) 1;
        } else if (packingValue < (boolean_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CASE_Y.controllerBus_controller_boolea.Data[0] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 4));
          }
        }
      }
    }

    // --------------- START Packing signal 5 ------------------
    //   startBit                = 5
    //   length                  = 1
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (HT08_CASE_U.useTractionControl);

        // no scaling required
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (boolean_T)(1)) {
          packedValue = (uint8_T) 1;
        } else if (packingValue < (boolean_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CASE_Y.controllerBus_controller_boolea.Data[0] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 5));
          }
        }
      }
    }
  }

  // ModelReference: '<Root>/Vehicle Math' incorporates:
  //   Inport generated from: '<Root>/Motor Omega FL [rpm]'
  //   Inport generated from: '<Root>/Motor Omega FR [rpm]'
  //   Inport generated from: '<Root>/Motor Omega RL [rpm]'
  //   Inport generated from: '<Root>/Motor Omega RR [rpm]'
  //   Inport generated from: '<Root>/Steering Wheel Angle [Deg]'
  //   Inport generated from: '<Root>/Vx_B'
  //   Inport generated from: '<Root>/Vy_B'
  //   Inport generated from: '<Root>/Yaw PID Vel Threshold'
  //   Inport generated from: '<Root>/Yaw Rate [rad//s]'

  Vehicle_MathMDLOBJ3.step(&HT08_CASE_U.Vx_B, &HT08_CASE_U.Vy_B,
    &HT08_CASE_U.YawRaterads, &HT08_CASE_U.MotorOmegaFLrpm,
    &HT08_CASE_U.MotorOmegaFRrpm, &HT08_CASE_U.MotorOmegaRLrpm,
    &HT08_CASE_U.MotorOmegaRRrpm, &HT08_CASE_U.SteeringWheelAngleDeg,
    &HT08_CASE_U.YawPIDVelThreshold, &HT08_CASE_B.BetaDeg,
    &HT08_CASE_B.AlphaFLDeg, &HT08_CASE_B.AlphaFRDeg, &HT08_CASE_B.AlphaRLDeg,
    &HT08_CASE_B.AlphaRRDeg, &HT08_CASE_B.LongCornerVelFL,
    &HT08_CASE_B.LongCornerVelFR, &HT08_CASE_B.LongCornerVelRL,
    &HT08_CASE_B.LongCornerVelRR, &HT08_CASE_B.VehicleMath_o10,
    &HT08_CASE_B.SLFL, &HT08_CASE_B.SLFR, &HT08_CASE_B.SLRL, &HT08_CASE_B.SLRR,
    &HT08_CASE_B.WheelSteerAvgDeg, &rtb_VehicleMath_o16, &rtb_VehicleMath_o17,
    &rtb_VehicleMath_o18, &rtb_VehicleMath_o19);

  // ModelReference: '<Root>/TCS' incorporates:
  //   Inport generated from: '<Root>/Launch Dead Zone'
  //   Inport generated from: '<Root>/Launch SL'
  //   Inport generated from: '<Root>/Launch Vel Threshold'
  //   Inport generated from: '<Root>/TCS PID Config'
  //   Inport generated from: '<Root>/TCS Vel Threshold'
  //   Inport generated from: '<Root>/TCS_SLThreshold'
  //   Inport generated from: '<Root>/Torque Average [Nm]'
  //   Inport generated from: '<Root>/Vx_B'
  //   Inport generated from: '<Root>/useLaunch'
  //   Inport generated from: '<Root>/useTractionControl'

  TCSMDLOBJ2.step(&HT08_CASE_U.TorqueAverageNm, &HT08_CASE_U.useTractionControl,
                  &HT08_CASE_U.TCS_SLThreshold, &HT08_CASE_U.TorqueAverageNm,
                  &HT08_CASE_U.TorqueAverageNm, &HT08_CASE_U.TorqueAverageNm,
                  &HT08_CASE_U.TorqueAverageNm, &HT08_CASE_B.SLFL,
                  &HT08_CASE_B.SLFR, &HT08_CASE_B.SLRL, &HT08_CASE_B.SLRR,
                  &HT08_CASE_U.useLaunch, &HT08_CASE_U.LaunchSL,
                  &HT08_CASE_U.LaunchDeadZone, &HT08_CASE_U.TCSPIDConfig[0],
                  &HT08_CASE_U.Vx_B, &HT08_CASE_U.LaunchVelThreshold,
                  &HT08_CASE_U.TCSVelThreshold, &HT08_CASE_B.TCS_o1,
                  &HT08_CASE_B.TCS_o2, &HT08_CASE_B.TCS_o3, &HT08_CASE_B.TCS_o4,
                  &HT08_CASE_B.TCS_o5, &HT08_CASE_B.TCS_o6, &HT08_CASE_B.TCS_o7,
                  &HT08_CASE_B.TCS_o8, &HT08_CASE_B.TCS_o9[0]);

  // ModelReference: '<S4>/PID_TV' incorporates:
  //   Constant: '<S4>/Constant5'
  //   Inport generated from: '<Root>/Torque Average [Nm]'
  //   Inport generated from: '<Root>/Torque Limit'
  //   Inport generated from: '<Root>/Vx_B'
  //   Inport generated from: '<Root>/Yaw PID Coast Threshold'
  //   Inport generated from: '<Root>/Yaw PID Config'
  //   Inport generated from: '<Root>/Yaw PID Error Threshold'
  //   Inport generated from: '<Root>/Yaw PID Max Differential'
  //   Inport generated from: '<Root>/Yaw PID Vel Threshold'
  //   Inport generated from: '<Root>/Yaw Rate [rad//s]'
  //   Inport generated from: '<Root>/usePIDTV'
  //   Inport generated from: '<Root>/useTCSLimitedYawPID'

  PID_TVMDLOBJ5.step(&HT08_CASE_U.YawRaterads, &HT08_CASE_U.YawPIDConfig[1],
                     &HT08_CASE_U.YawPIDConfig[2], &rtCP_Constant5_Value,
                     &HT08_CASE_U.YawPIDConfig[0], &HT08_CASE_B.TCS_o2,
                     &HT08_CASE_B.TCS_o4, &HT08_CASE_B.TCS_o1,
                     &HT08_CASE_B.TCS_o3, &HT08_CASE_U.usePIDTV,
                     &HT08_CASE_B.VehicleMath_o10, &HT08_CASE_U.Vx_B,
                     &HT08_CASE_U.TorqueLimit, &HT08_CASE_U.TorqueAverageNm,
                     &HT08_CASE_U.YawPIDErrorThreshold,
                     &HT08_CASE_U.YawPIDCoastThreshold,
                     &HT08_CASE_U.YawPIDVelThreshold,
                     &HT08_CASE_U.useTCSLimitedYawPID, &HT08_CASE_B.TCS_o5,
                     &HT08_CASE_B.TCS_o6, &HT08_CASE_B.TCS_o7,
                     &HT08_CASE_B.TCS_o8, &HT08_CASE_U.YawPIDMaxDifferential,
                     &HT08_CASE_B.FRTORQUEPID, &HT08_CASE_B.RRTORQUEPID,
                     &HT08_CASE_B.FLTORQUEPID, &HT08_CASE_B.RLTORQUEPID,
                     &HT08_CASE_B.PID_TV_o5, &HT08_CASE_B.PID_TV_o6);

  // ModelReference: '<S4>/Model' incorporates:
  //   Inport generated from: '<Root>/FZ FL'
  //   Inport generated from: '<Root>/FZ FR'
  //   Inport generated from: '<Root>/FZ RL'
  //   Inport generated from: '<Root>/FZ RR'
  //   Inport generated from: '<Root>/Torque Limit'
  //   Inport generated from: '<Root>/useNormalForce'
  //   Inport generated from: '<Root>/usePIDTV'

  ModelMDLOBJ4.step(&HT08_CASE_U.useNormalForce, &HT08_CASE_U.FZFL,
                    &HT08_CASE_U.FZFR, &HT08_CASE_U.FZRL, &HT08_CASE_U.FZRR,
                    &HT08_CASE_B.FLTORQUEPID, &HT08_CASE_B.FRTORQUEPID,
                    &HT08_CASE_B.RLTORQUEPID, &HT08_CASE_B.RRTORQUEPID,
                    &HT08_CASE_U.usePIDTV, &HT08_CASE_U.TorqueLimit,
                    &HT08_CASE_B.TorqueNormalFL, &HT08_CASE_B.TorqueNormalFR,
                    &HT08_CASE_B.TorqueNormalRL, &HT08_CASE_B.TorqueNormalRR,
                    &HT08_CASE_B.Normal_Percent_FL,
                    &HT08_CASE_B.Normal_Percent_FR,
                    &HT08_CASE_B.Normal_Percent_RL,
                    &HT08_CASE_B.Normal_Percent_RR);

  // S-Function (scanpack): '<S1>/CAN Pack1' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element3'

  // S-Function (scanpack): '<S1>/CAN Pack1'
  HT08_CASE_Y.controllerBus_controller_normal.ID = 2011U;
  HT08_CASE_Y.controllerBus_controller_normal.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_normal.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_normal.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_normal.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_normal.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_normal.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_normal.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_normal.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_normal.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_normal.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_normal.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.Normal_Percent_FL;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_normal.Data[0] =
              HT08_CASE_Y.controllerBus_controller_normal.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_normal.Data[1] =
              HT08_CASE_Y.controllerBus_controller_normal.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.Normal_Percent_FR;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_normal.Data[2] =
              HT08_CASE_Y.controllerBus_controller_normal.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_normal.Data[3] =
              HT08_CASE_Y.controllerBus_controller_normal.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.Normal_Percent_RL;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_normal.Data[4] =
              HT08_CASE_Y.controllerBus_controller_normal.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_normal.Data[5] =
              HT08_CASE_Y.controllerBus_controller_normal.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.Normal_Percent_RR;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_normal.Data[6] =
              HT08_CASE_Y.controllerBus_controller_normal.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_normal.Data[7] =
              HT08_CASE_Y.controllerBus_controller_normal.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack2' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element4'

  // S-Function (scanpack): '<S1>/CAN Pack2'
  HT08_CASE_Y.controllerBus_controller_norm_p.ID = 2012U;
  HT08_CASE_Y.controllerBus_controller_norm_p.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_norm_p.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_norm_p.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_norm_p.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_norm_p.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_norm_p.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_norm_p.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_norm_p.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_norm_p.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_norm_p.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_norm_p.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TorqueNormalFL;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_norm_p.Data[0] =
              HT08_CASE_Y.controllerBus_controller_norm_p.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_norm_p.Data[1] =
              HT08_CASE_Y.controllerBus_controller_norm_p.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TorqueNormalFR;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_norm_p.Data[2] =
              HT08_CASE_Y.controllerBus_controller_norm_p.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_norm_p.Data[3] =
              HT08_CASE_Y.controllerBus_controller_norm_p.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TorqueNormalRL;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_norm_p.Data[4] =
              HT08_CASE_Y.controllerBus_controller_norm_p.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_norm_p.Data[5] =
              HT08_CASE_Y.controllerBus_controller_norm_p.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TorqueNormalRR;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_norm_p.Data[6] =
              HT08_CASE_Y.controllerBus_controller_norm_p.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_norm_p.Data[7] =
              HT08_CASE_Y.controllerBus_controller_norm_p.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack3' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element5'

  // S-Function (scanpack): '<S1>/CAN Pack3'
  HT08_CASE_Y.controllerBus_controller_pid_ya.ID = 1997U;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_pid_ya.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.PID_TV_o6;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pid_ya.Data[4] =
              HT08_CASE_Y.controllerBus_controller_pid_ya.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pid_ya.Data[5] =
              HT08_CASE_Y.controllerBus_controller_pid_ya.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.PID_TV_o5;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pid_ya.Data[2] =
              HT08_CASE_Y.controllerBus_controller_pid_ya.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pid_ya.Data[3] =
              HT08_CASE_Y.controllerBus_controller_pid_ya.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.VehicleMath_o10;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pid_ya.Data[0] =
              HT08_CASE_Y.controllerBus_controller_pid_ya.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pid_ya.Data[1] =
              HT08_CASE_Y.controllerBus_controller_pid_ya.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack4' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element6'

  // S-Function (scanpack): '<S1>/CAN Pack4'
  HT08_CASE_Y.controllerBus_controller_pid__p.ID = 2010U;
  HT08_CASE_Y.controllerBus_controller_pid__p.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_pid__p.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_pid__p.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_pid__p.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_pid__p.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_pid__p.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_pid__p.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_pid__p.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_pid__p.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_pid__p.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_pid__p.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.FLTORQUEPID;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pid__p.Data[0] =
              HT08_CASE_Y.controllerBus_controller_pid__p.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pid__p.Data[1] =
              HT08_CASE_Y.controllerBus_controller_pid__p.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.FRTORQUEPID;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pid__p.Data[2] =
              HT08_CASE_Y.controllerBus_controller_pid__p.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pid__p.Data[3] =
              HT08_CASE_Y.controllerBus_controller_pid__p.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.RLTORQUEPID;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pid__p.Data[4] =
              HT08_CASE_Y.controllerBus_controller_pid__p.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pid__p.Data[5] =
              HT08_CASE_Y.controllerBus_controller_pid__p.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.RRTORQUEPID;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pid__p.Data[6] =
              HT08_CASE_Y.controllerBus_controller_pid__p.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pid__p.Data[7] =
              HT08_CASE_Y.controllerBus_controller_pid__p.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // ModelReference: '<Root>/Power Limit' incorporates:
  //   Inport generated from: '<Root>/Current Power [kW]'
  //   Inport generated from: '<Root>/usePIDPowerLimit'
  //   Inport generated from: '<Root>/usePowerLimit'
  //   Outport generated from: '<Root>/Final Torque FL'
  //   Outport generated from: '<Root>/Final Torque FR'
  //   Outport generated from: '<Root>/Final Torque RL'
  //   Outport generated from: '<Root>/Final Torque RR'

  Power_LimitMDLOBJ1.step(&HT08_CASE_U.CurrentPowerkW,
    &HT08_CASE_B.TorqueNormalFL, &HT08_CASE_B.TorqueNormalFR,
    &HT08_CASE_B.TorqueNormalRL, &HT08_CASE_B.TorqueNormalRR,
    &rtb_VehicleMath_o16, &rtb_VehicleMath_o17, &rtb_VehicleMath_o18,
    &rtb_VehicleMath_o19, &HT08_CASE_U.usePowerLimit,
    &HT08_CASE_U.usePIDPowerLimit, &HT08_CASE_Y.FinalTorqueFL,
    &HT08_CASE_Y.FinalTorqueFR, &HT08_CASE_Y.FinalTorqueRL,
    &HT08_CASE_Y.FinalTorqueRR, &HT08_CASE_B.PowerLimit_o5,
    &HT08_CASE_B.PowerLimit_o6, &HT08_CASE_B.TorqueAdjustment,
    &HT08_CASE_B.PowerLimit_o8, &HT08_CASE_B.PowerLimit_o9,
    &HT08_CASE_B.PowerLimit_o10, &HT08_CASE_B.PowerLimit_o11);

  // S-Function (scanpack): '<S1>/CAN Pack5' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element7'

  // S-Function (scanpack): '<S1>/CAN Pack5'
  HT08_CASE_Y.controllerBus_controller_power_.ID = 2014U;
  HT08_CASE_Y.controllerBus_controller_power_.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_power_.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_power_.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_power_.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_power_.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_power_.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_power_.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_power_.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_power_.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_power_.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_power_.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 4
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.PowerLimit_o6;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_power_.Data[0] =
              HT08_CASE_Y.controllerBus_controller_power_.Data[0] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFU) << 4));
            HT08_CASE_Y.controllerBus_controller_power_.Data[1] =
              HT08_CASE_Y.controllerBus_controller_power_.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF0U) >> 4));
            HT08_CASE_Y.controllerBus_controller_power_.Data[2] =
              HT08_CASE_Y.controllerBus_controller_power_.Data[2] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xF000U) >> 12));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 0
    //   length                  = 4
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.PowerLimit_o5;

        // no scaling required
        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real_T)(15)) {
          packedValue = (uint8_T) 15;
        } else if (outValue < (real_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_power_.Data[0] =
              HT08_CASE_Y.controllerBus_controller_power_.Data[0] | (uint8_T)
              ((uint8_T)(packedValue & (uint8_T)0xFU));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 20
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TorqueAdjustment;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_power_.Data[2] =
              HT08_CASE_Y.controllerBus_controller_power_.Data[2] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFU) << 4));
            HT08_CASE_Y.controllerBus_controller_power_.Data[3] =
              HT08_CASE_Y.controllerBus_controller_power_.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF0U) >> 4));
            HT08_CASE_Y.controllerBus_controller_power_.Data[4] =
              HT08_CASE_Y.controllerBus_controller_power_.Data[4] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xF000U) >> 12));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack6' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element8'

  // S-Function (scanpack): '<S1>/CAN Pack6'
  HT08_CASE_Y.controllerBus_controller_powe_p.ID = 2026U;
  HT08_CASE_Y.controllerBus_controller_powe_p.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_powe_p.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_powe_p.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_powe_p.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_powe_p.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_powe_p.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_powe_p.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_powe_p.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_powe_p.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_powe_p.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_powe_p.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.PowerLimit_o8;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_powe_p.Data[0] =
              HT08_CASE_Y.controllerBus_controller_powe_p.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_powe_p.Data[1] =
              HT08_CASE_Y.controllerBus_controller_powe_p.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.PowerLimit_o9;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_powe_p.Data[2] =
              HT08_CASE_Y.controllerBus_controller_powe_p.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_powe_p.Data[3] =
              HT08_CASE_Y.controllerBus_controller_powe_p.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.PowerLimit_o10;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_powe_p.Data[4] =
              HT08_CASE_Y.controllerBus_controller_powe_p.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_powe_p.Data[5] =
              HT08_CASE_Y.controllerBus_controller_powe_p.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.PowerLimit_o11;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_powe_p.Data[6] =
              HT08_CASE_Y.controllerBus_controller_powe_p.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_powe_p.Data[7] =
              HT08_CASE_Y.controllerBus_controller_powe_p.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack7' incorporates:
  //   Outport generated from: '<Root>/Final Torque FL'
  //   Outport generated from: '<Root>/Final Torque FR'
  //   Outport generated from: '<Root>/Final Torque RL'
  //   Outport generated from: '<Root>/Final Torque RR'
  //   Outport generated from: '<Root>/Out Bus Element9'

  // S-Function (scanpack): '<S1>/CAN Pack7'
  HT08_CASE_Y.controllerBus_controller_pow_pn.ID = 2027U;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_pow_pn.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_Y.FinalTorqueFL;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pow_pn.Data[0] =
              HT08_CASE_Y.controllerBus_controller_pow_pn.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pow_pn.Data[1] =
              HT08_CASE_Y.controllerBus_controller_pow_pn.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_Y.FinalTorqueFR;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pow_pn.Data[2] =
              HT08_CASE_Y.controllerBus_controller_pow_pn.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pow_pn.Data[3] =
              HT08_CASE_Y.controllerBus_controller_pow_pn.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_Y.FinalTorqueRL;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pow_pn.Data[4] =
              HT08_CASE_Y.controllerBus_controller_pow_pn.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pow_pn.Data[5] =
              HT08_CASE_Y.controllerBus_controller_pow_pn.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_Y.FinalTorqueRR;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_pow_pn.Data[6] =
              HT08_CASE_Y.controllerBus_controller_pow_pn.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_pow_pn.Data[7] =
              HT08_CASE_Y.controllerBus_controller_pow_pn.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack8' incorporates:
  //   Inport generated from: '<Root>/Torque Average [Nm]'
  //   Outport generated from: '<Root>/Out Bus Element10'

  // S-Function (scanpack): '<S1>/CAN Pack8'
  HT08_CASE_Y.controllerBus_controller_initia.ID = 2042U;
  HT08_CASE_Y.controllerBus_controller_initia.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_initia.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_initia.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_initia.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_initia.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_initia.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_initia.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_initia.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_initia.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_initia.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_initia.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_U.TorqueAverageNm;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_initia.Data[0] =
              HT08_CASE_Y.controllerBus_controller_initia.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_initia.Data[1] =
              HT08_CASE_Y.controllerBus_controller_initia.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack9' incorporates:
  //   Inport generated from: '<Root>/Launch Dead Zone'
  //   Inport generated from: '<Root>/Launch SL'
  //   Inport generated from: '<Root>/TCS_SLThreshold'
  //   Outport generated from: '<Root>/Out Bus Element11'

  // S-Function (scanpack): '<S1>/CAN Pack9'
  HT08_CASE_Y.controllerBus_controller_tcs_co.ID = 2043U;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_co.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 16
    //   length                  = 12
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_U.LaunchDeadZone;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        uint16_T packedValue;
        if (outValue > (real_T)(4095)) {
          packedValue = (uint16_T) 4095;
        } else if (outValue < (real_T)(0)) {
          packedValue = (uint16_T) 0;
        } else {
          packedValue = (uint16_T) (outValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_tcs_co.Data[2] =
              HT08_CASE_Y.controllerBus_controller_tcs_co.Data[2] | (uint8_T)
              ((uint16_T)(packedValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_co.Data[3] =
              HT08_CASE_Y.controllerBus_controller_tcs_co.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(packedValue & (uint16_T)0xF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 8
    //   length                  = 8
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_U.LaunchSL;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real_T)(255)) {
          packedValue = (uint8_T) 255;
        } else if (outValue < (real_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_tcs_co.Data[1] =
              HT08_CASE_Y.controllerBus_controller_tcs_co.Data[1] | (uint8_T)
              (packedValue);
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 0
    //   length                  = 8
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_U.TCS_SLThreshold;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real_T)(255)) {
          packedValue = (uint8_T) 255;
        } else if (outValue < (real_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_tcs_co.Data[0] =
              HT08_CASE_Y.controllerBus_controller_tcs_co.Data[0] | (uint8_T)
              (packedValue);
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack10' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element12'

  // S-Function (scanpack): '<S1>/CAN Pack10'
  HT08_CASE_Y.controllerBus_controller_tcs_st.ID = 2045U;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_st.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 2
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o5;

        // no scaling required
        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real_T)(3)) {
          packedValue = (uint8_T) 3;
        } else if (outValue < (real_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] =
              HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] | (uint8_T)
              ((uint8_T)(packedValue & (uint8_T)0x3U));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 2
    //   length                  = 2
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o6;

        // no scaling required
        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real_T)(3)) {
          packedValue = (uint8_T) 3;
        } else if (outValue < (real_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] =
              HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x3U) << 2));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 4
    //   length                  = 2
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o7;

        // no scaling required
        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real_T)(3)) {
          packedValue = (uint8_T) 3;
        } else if (outValue < (real_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] =
              HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x3U) << 4));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 6
    //   length                  = 2
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = UNSIGNED
    //   factor                  = 1.0
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o8;

        // no scaling required
        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real_T)(3)) {
          packedValue = (uint8_T) 3;
        } else if (outValue < (real_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] =
              HT08_CASE_Y.controllerBus_controller_tcs_st.Data[0] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x3U) << 6));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack11' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element13'

  // S-Function (scanpack): '<S1>/CAN Pack11'
  HT08_CASE_Y.controllerBus_controller_tcs_pi.ID = 2046U;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o9[0];

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[0] =
              HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[1] =
              HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o9[2];

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[2] =
              HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[3] =
              HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o9[4];

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[4] =
              HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[5] =
              HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o9[6];

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[6] =
              HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[7] =
              HT08_CASE_Y.controllerBus_controller_tcs_pi.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack12' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element14'

  // S-Function (scanpack): '<S1>/CAN Pack12'
  HT08_CASE_Y.controllerBus_controller_tcs__p.ID = 1962U;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs__p.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o9[1];

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs__p.Data[0] =
              HT08_CASE_Y.controllerBus_controller_tcs__p.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs__p.Data[1] =
              HT08_CASE_Y.controllerBus_controller_tcs__p.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o9[3];

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs__p.Data[2] =
              HT08_CASE_Y.controllerBus_controller_tcs__p.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs__p.Data[3] =
              HT08_CASE_Y.controllerBus_controller_tcs__p.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o9[5];

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs__p.Data[4] =
              HT08_CASE_Y.controllerBus_controller_tcs__p.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs__p.Data[5] =
              HT08_CASE_Y.controllerBus_controller_tcs__p.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o9[7];

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs__p.Data[6] =
              HT08_CASE_Y.controllerBus_controller_tcs__p.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs__p.Data[7] =
              HT08_CASE_Y.controllerBus_controller_tcs__p.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack13' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element15'

  // S-Function (scanpack): '<S1>/CAN Pack13'
  HT08_CASE_Y.controllerBus_controller_tcs_to.ID = 2044U;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Length = 8U;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Extended = 0U;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Remote = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Data[0] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Data[1] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Data[2] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Data[3] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Data[4] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Data[5] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Data[6] = 0;
  HT08_CASE_Y.controllerBus_controller_tcs_to.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o1;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs_to.Data[0] =
              HT08_CASE_Y.controllerBus_controller_tcs_to.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_to.Data[1] =
              HT08_CASE_Y.controllerBus_controller_tcs_to.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o2;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs_to.Data[2] =
              HT08_CASE_Y.controllerBus_controller_tcs_to.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_to.Data[3] =
              HT08_CASE_Y.controllerBus_controller_tcs_to.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o3;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs_to.Data[4] =
              HT08_CASE_Y.controllerBus_controller_tcs_to.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_to.Data[5] =
              HT08_CASE_Y.controllerBus_controller_tcs_to.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.TCS_o4;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_controller_tcs_to.Data[6] =
              HT08_CASE_Y.controllerBus_controller_tcs_to.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_controller_tcs_to.Data[7] =
              HT08_CASE_Y.controllerBus_controller_tcs_to.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S3>/CAN Pack2' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element1'

  // S-Function (scanpack): '<S3>/CAN Pack2'
  HT08_CASE_Y.controllerBus_vehm_beta_deg.ID = 2031U;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Length = 8U;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Extended = 0U;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Remote = 0;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[0] = 0;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[1] = 0;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[2] = 0;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[3] = 0;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[4] = 0;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[5] = 0;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[6] = 0;
  HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.BetaDeg;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[0] =
              HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[1] =
              HT08_CASE_Y.controllerBus_vehm_beta_deg.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S3>/CAN Pack' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element'

  // S-Function (scanpack): '<S3>/CAN Pack'
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.ID = 2047U;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Length = 8U;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Extended = 0U;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Remote = 0;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[0] = 0;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[1] = 0;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[2] = 0;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[3] = 0;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[4] = 0;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[5] = 0;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[6] = 0;
  HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.AlphaFLDeg;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[0] =
              HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[1] =
              HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.AlphaFRDeg;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[2] =
              HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[3] =
              HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.AlphaRLDeg;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[4] =
              HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[5] =
              HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.AlphaRRDeg;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[6] =
              HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[7] =
              HT08_CASE_Y.controllerBus_vehm_alpha_deg.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S3>/CAN Pack1' incorporates:
  //   Outport generated from: '<Root>/BusElementOut'

  // S-Function (scanpack): '<S3>/CAN Pack1'
  HT08_CASE_Y.controllerBus_vehm_sl.ID = 1999U;
  HT08_CASE_Y.controllerBus_vehm_sl.Length = 8U;
  HT08_CASE_Y.controllerBus_vehm_sl.Extended = 0U;
  HT08_CASE_Y.controllerBus_vehm_sl.Remote = 0;
  HT08_CASE_Y.controllerBus_vehm_sl.Data[0] = 0;
  HT08_CASE_Y.controllerBus_vehm_sl.Data[1] = 0;
  HT08_CASE_Y.controllerBus_vehm_sl.Data[2] = 0;
  HT08_CASE_Y.controllerBus_vehm_sl.Data[3] = 0;
  HT08_CASE_Y.controllerBus_vehm_sl.Data[4] = 0;
  HT08_CASE_Y.controllerBus_vehm_sl.Data[5] = 0;
  HT08_CASE_Y.controllerBus_vehm_sl.Data[6] = 0;
  HT08_CASE_Y.controllerBus_vehm_sl.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.SLFL;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_sl.Data[0] =
              HT08_CASE_Y.controllerBus_vehm_sl.Data[0] | (uint8_T)((uint16_T)
              (tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_sl.Data[1] =
              HT08_CASE_Y.controllerBus_vehm_sl.Data[1] | (uint8_T)((uint16_T)
              ((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.SLFR;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_sl.Data[2] =
              HT08_CASE_Y.controllerBus_vehm_sl.Data[2] | (uint8_T)((uint16_T)
              (tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_sl.Data[3] =
              HT08_CASE_Y.controllerBus_vehm_sl.Data[3] | (uint8_T)((uint16_T)
              ((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.SLRL;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_sl.Data[4] =
              HT08_CASE_Y.controllerBus_vehm_sl.Data[4] | (uint8_T)((uint16_T)
              (tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_sl.Data[5] =
              HT08_CASE_Y.controllerBus_vehm_sl.Data[5] | (uint8_T)((uint16_T)
              ((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.SLRR;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_sl.Data[6] =
              HT08_CASE_Y.controllerBus_vehm_sl.Data[6] | (uint8_T)((uint16_T)
              (tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_sl.Data[7] =
              HT08_CASE_Y.controllerBus_vehm_sl.Data[7] | (uint8_T)((uint16_T)
              ((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S3>/CAN Pack3' incorporates:
  //   Outport generated from: '<Root>/Bus Element Out'

  // S-Function (scanpack): '<S3>/CAN Pack3'
  HT08_CASE_Y.controllerBus_vehm_long_corner_.ID = 1998U;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Length = 8U;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Extended = 0U;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Remote = 0;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[0] = 0;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[1] = 0;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[2] = 0;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[3] = 0;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[4] = 0;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[5] = 0;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[6] = 0;
  HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.LongCornerVelFL;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[0] =
              HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[1] =
              HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 1 ------------------
    //   startBit                = 16
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.LongCornerVelFR;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[2] =
              HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[3] =
              HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 2 ------------------
    //   startBit                = 32
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.LongCornerVelRL;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[4] =
              HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[5] =
              HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    // --------------- START Packing signal 3 ------------------
    //   startBit                = 48
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.01
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.LongCornerVelRR;

        // no offset to apply
        result = result * (1 / 0.01);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[6] =
              HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[7] =
              HT08_CASE_Y.controllerBus_vehm_long_corner_.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S3>/CAN Pack4' incorporates:
  //   Outport generated from: '<Root>/Bus Element Out1'

  // S-Function (scanpack): '<S3>/CAN Pack4'
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.ID = 1994U;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Length = 8U;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Extended = 0U;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Remote = 0;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[0] = 0;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[1] = 0;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[2] = 0;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[3] = 0;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[4] = 0;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[5] = 0;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[6] = 0;
  HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.WheelSteerAvgDeg;

        // no offset to apply
        result = result * (1 / 0.001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[0] =
              HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[1] =
              HT08_CASE_Y.controllerBus_vehm_wheel_steer_.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S3>/CAN Pack5' incorporates:
  //   Outport generated from: '<Root>/Bus Element Out2'

  // S-Function (scanpack): '<S3>/CAN Pack5'
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.ID = 1995U;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Length = 8U;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Extended = 0U;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Remote = 0;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[0] = 0;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[1] = 0;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[2] = 0;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[3] = 0;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[4] = 0;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[5] = 0;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[6] = 0;
  HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[7] = 0;

  {
    // --------------- START Packing signal 0 ------------------
    //   startBit                = 0
    //   length                  = 16
    //   desiredSignalByteLayout = LITTLEENDIAN
    //   dataType                = SIGNED
    //   factor                  = 0.0001
    //   offset                  = 0.0
    //   minimum                 = 0.0
    //   maximum                 = 0.0
    //  -----------------------------------------------------------------------
    {
      real_T outValue = 0;

      {
        real_T result = HT08_CASE_B.VehicleMath_o10;

        // no offset to apply
        result = result * (1 / 0.0001);

        // round to closest integer value for integer CAN signal
        outValue = round(result);
      }

      {
        int16_T packedValue;
        int32_T scaledValue;
        if (outValue > 2147483647.0) {
          scaledValue = 2147483647;
        } else if (outValue < -2147483648.0) {
          scaledValue = -2147483647 - 1;
        } else {
          scaledValue = (int32_T) outValue;
        }

        if (scaledValue > (int32_T) (32767)) {
          packedValue = 32767;
        } else if (scaledValue < (int32_T)((-(32767)-1))) {
          packedValue = (-(32767)-1);
        } else {
          packedValue = (int16_T) (scaledValue);
        }

        {
          uint16_T* tempValuePtr = (uint16_T*)&packedValue;
          uint16_T tempValue = *tempValuePtr;

          {
            HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[0] =
              HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[1] =
              HT08_CASE_Y.controllerBus_vehm_kin_desired_.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }
}

// Model initialize function
void HT08_CASE::initialize()
{
  // Registration code

  // Initialize DataMapInfo substructure containing ModelMap for C API
  HT08_CASE_InitializeDataMapInfo((&HT08_CASE_M), &HT08_CASE_B);

  // Model Initialize function for ModelReference Block: '<Root>/Power Limit'

  // Set error status pointer for ModelReference Block: '<Root>/Power Limit'
  Power_LimitMDLOBJ1.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&HT08_CASE_M)));
  Power_LimitMDLOBJ1.initialize();
  Power_LimitMDLOBJ1.setupCAPIInfo(&((&HT08_CASE_M)->DataMapInfo.mmi),
    "HT08_CASE/Power Limit",0,-1);

  // Model Initialize function for ModelReference Block: '<Root>/TCS'

  // Set error status pointer for ModelReference Block: '<Root>/TCS'
  TCSMDLOBJ2.setErrorStatusPointer(rtmGetErrorStatusPointer((&HT08_CASE_M)));
  TCSMDLOBJ2.initialize();
  TCSMDLOBJ2.setupCAPIInfo(&((&HT08_CASE_M)->DataMapInfo.mmi),"HT08_CASE/TCS",1,
    -1);

  // Model Initialize function for ModelReference Block: '<Root>/Vehicle Math'

  // Set error status pointer for ModelReference Block: '<Root>/Vehicle Math'
  Vehicle_MathMDLOBJ3.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&HT08_CASE_M)));
  Vehicle_MathMDLOBJ3.initialize();
  Vehicle_MathMDLOBJ3.setupCAPIInfo(&((&HT08_CASE_M)->DataMapInfo.mmi),
    "HT08_CASE/Vehicle Math",2,-1);

  // Model Initialize function for ModelReference Block: '<S4>/Model'

  // Set error status pointer for ModelReference Block: '<S4>/Model'
  ModelMDLOBJ4.setErrorStatusPointer(rtmGetErrorStatusPointer((&HT08_CASE_M)));
  ModelMDLOBJ4.initialize();
  ModelMDLOBJ4.setupCAPIInfo(&((&HT08_CASE_M)->DataMapInfo.mmi),
    "HT08_CASE/Yaw and Normal Force TV/Model",3,-1);

  // Model Initialize function for ModelReference Block: '<S4>/PID_TV'

  // Set error status pointer for ModelReference Block: '<S4>/PID_TV'
  PID_TVMDLOBJ5.setErrorStatusPointer(rtmGetErrorStatusPointer((&HT08_CASE_M)));
  PID_TVMDLOBJ5.initialize();
  PID_TVMDLOBJ5.setupCAPIInfo(&((&HT08_CASE_M)->DataMapInfo.mmi),
    "HT08_CASE/Yaw and Normal Force TV/PID_TV",4,-1);

  // SystemInitialize for ModelReference: '<Root>/TCS'
  TCSMDLOBJ2.init(&HT08_CASE_B.TCS_o9[0]);

  // SystemInitialize for ModelReference: '<S4>/PID_TV'
  PID_TVMDLOBJ5.init();
}

// Model terminate function
void HT08_CASE::terminate()
{
  // (no terminate code required)
}

// Constructor
HT08_CASE::HT08_CASE() :
  HT08_CASE_U(),
  HT08_CASE_Y(),
  HT08_CASE_B(),
  HT08_CASE_DW(),
  HT08_CASE_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
HT08_CASE::~HT08_CASE() = default;

// Real-Time Model get method
HT08_CASE::RT_MODEL_HT08_CASE_T * HT08_CASE::getRTM()
{
  return (&HT08_CASE_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
