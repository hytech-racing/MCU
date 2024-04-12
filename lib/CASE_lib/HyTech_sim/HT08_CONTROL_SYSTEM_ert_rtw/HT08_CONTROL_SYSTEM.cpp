//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: HT08_CONTROL_SYSTEM.cpp
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
#include "HT08_CONTROL_SYSTEM.h"
#include "rtwtypes.h"
#include "HT08_CONTROL_SYSTEM_capi.h"
#include "HT08_CONTROL_SYSTEM_private.h"
#include "LAUNCH_CONTROL.h"
#include "POWER_LIMIT.h"
#include "BasicVehicleMath.h"
#include "NORMAL_FORCE_TV.h"
#include "PID_TV.h"

// Model step function
void HT08_CONTROL_SYSTEM::step()
{
  real_T rtb_Merge;
  real_T rtb_Merge1;
  real_T rtb_Merge2;
  real_T rtb_Merge3;
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
  //   Outport generated from: '<Root>/Out Bus Element2'

  // S-Function (scanpack): '<S1>/CAN Pack'
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.ID = 2028U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[7] = 0;

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
        uint32_T result = (uint32_T) (HT08_CONTROL_SYSTEM_U.useLaunch);

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] |
              (uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U));
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
        uint32_T result = (uint32_T) (HT08_CONTROL_SYSTEM_U.usePIDTV);

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] |
              (uint8_T)((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 2));
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
        uint32_T result = (uint32_T) (HT08_CONTROL_SYSTEM_U.useNormalForce);

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] |
              (uint8_T)((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 3));
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
        uint32_T result = (uint32_T) (HT08_CONTROL_SYSTEM_U.usePowerLimit);

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] |
              (uint8_T)((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 1));
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
        uint32_T result = (uint32_T) (HT08_CONTROL_SYSTEM_U.usePIDPowerLimit);

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_boolea.Data[0] |
              (uint8_T)((uint8_T)((uint8_T)(packedValue & (uint8_T)0x1U) << 4));
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
  //   Inport generated from: '<Root>/Yaw Rate [rad//s]'

  Vehicle_MathMDLOBJ3.step(&HT08_CONTROL_SYSTEM_U.Vx_B,
    &HT08_CONTROL_SYSTEM_U.Vy_B, &HT08_CONTROL_SYSTEM_U.YawRaterads,
    &HT08_CONTROL_SYSTEM_U.MotorOmegaFLrpm,
    &HT08_CONTROL_SYSTEM_U.MotorOmegaFRrpm,
    &HT08_CONTROL_SYSTEM_U.MotorOmegaRLrpm,
    &HT08_CONTROL_SYSTEM_U.MotorOmegaRRrpm,
    &HT08_CONTROL_SYSTEM_U.SteeringWheelAngleDeg, &HT08_CONTROL_SYSTEM_B.BetaDeg,
    &HT08_CONTROL_SYSTEM_B.AlphaFLDeg, &HT08_CONTROL_SYSTEM_B.AlphaFRDeg,
    &HT08_CONTROL_SYSTEM_B.AlphaRLDeg, &HT08_CONTROL_SYSTEM_B.AlphaRRDeg,
    &HT08_CONTROL_SYSTEM_B.LongCornerVelFL,
    &HT08_CONTROL_SYSTEM_B.LongCornerVelFR,
    &HT08_CONTROL_SYSTEM_B.LongCornerVelRL,
    &HT08_CONTROL_SYSTEM_B.LongCornerVelRR,
    &HT08_CONTROL_SYSTEM_B.DesiredYawRaterads, &HT08_CONTROL_SYSTEM_B.SLFL,
    &HT08_CONTROL_SYSTEM_B.SLFR, &HT08_CONTROL_SYSTEM_B.SLRL,
    &HT08_CONTROL_SYSTEM_B.SLRR, &HT08_CONTROL_SYSTEM_B.WheelSteerAvgDeg,
    &rtb_VehicleMath_o16, &rtb_VehicleMath_o17, &rtb_VehicleMath_o18,
    &rtb_VehicleMath_o19);

  // If: '<Root>/If1' incorporates:
  //   Inport generated from: '<Root>/useLaunch'

  if (HT08_CONTROL_SYSTEM_U.useLaunch) {
    // Outputs for IfAction SubSystem: '<Root>/Launch Control' incorporates:
    //   ActionPort: '<S2>/Action Port'

    // ModelReference: '<S2>/Model3'
    Model3MDLOBJ1.step(&HT08_CONTROL_SYSTEM_B.SLFL, &HT08_CONTROL_SYSTEM_B.SLFR,
                       &HT08_CONTROL_SYSTEM_B.SLRL, &HT08_CONTROL_SYSTEM_B.SLRR,
                       &rtb_Merge, &rtb_Merge1, &rtb_Merge2, &rtb_Merge3);

    // End of Outputs for SubSystem: '<Root>/Launch Control'
  } else {
    // Outputs for IfAction SubSystem: '<Root>/Yaw and Normal Force TV' incorporates:
    //   ActionPort: '<S5>/Action Port'

    // ModelReference: '<S5>/PID_TV' incorporates:
    //   Constant: '<S5>/Constant2'
    //   Constant: '<S5>/Constant3'
    //   Constant: '<S5>/Constant4'
    //   Constant: '<S5>/Constant5'
    //   Inport generated from: '<Root>/Torque Average [Nm]'
    //   Inport generated from: '<Root>/Yaw Rate [rad//s]'
    //   Inport generated from: '<Root>/usePIDTV'

    PID_TVMDLOBJ5.step(&HT08_CONTROL_SYSTEM_U.YawRaterads, &rtCP_Constant3_Value,
                       &rtCP_Constant4_Value, &rtCP_Constant5_Value,
                       &rtCP_Constant2_Value,
                       &HT08_CONTROL_SYSTEM_U.TorqueAverageNm,
                       &HT08_CONTROL_SYSTEM_U.TorqueAverageNm,
                       &HT08_CONTROL_SYSTEM_U.TorqueAverageNm,
                       &HT08_CONTROL_SYSTEM_U.TorqueAverageNm,
                       &HT08_CONTROL_SYSTEM_U.usePIDTV,
                       &HT08_CONTROL_SYSTEM_B.FRTORQUEPID,
                       &HT08_CONTROL_SYSTEM_B.RRTORQUEPID,
                       &HT08_CONTROL_SYSTEM_B.FLTORQUEPID,
                       &HT08_CONTROL_SYSTEM_B.RLTORQUEPID,
                       &HT08_CONTROL_SYSTEM_B.YawErrorrads,
                       &HT08_CONTROL_SYSTEM_B.PID_TV_o6);

    // ModelReference: '<S5>/Model' incorporates:
    //   Inport generated from: '<Root>/FZ FL'
    //   Inport generated from: '<Root>/FZ FR'
    //   Inport generated from: '<Root>/FZ RL'
    //   Inport generated from: '<Root>/FZ RR'
    //   Inport generated from: '<Root>/useNormalForce'
    //   Inport generated from: '<Root>/usePIDTV'

    ModelMDLOBJ4.step(&HT08_CONTROL_SYSTEM_U.useNormalForce,
                      &HT08_CONTROL_SYSTEM_U.FZFL, &HT08_CONTROL_SYSTEM_U.FZFR,
                      &HT08_CONTROL_SYSTEM_U.FZRL, &HT08_CONTROL_SYSTEM_U.FZRR,
                      &HT08_CONTROL_SYSTEM_B.FLTORQUEPID,
                      &HT08_CONTROL_SYSTEM_B.FRTORQUEPID,
                      &HT08_CONTROL_SYSTEM_B.RLTORQUEPID,
                      &HT08_CONTROL_SYSTEM_B.RRTORQUEPID,
                      &HT08_CONTROL_SYSTEM_U.usePIDTV,
                      &HT08_CONTROL_SYSTEM_B.TorqueNormalFL,
                      &HT08_CONTROL_SYSTEM_B.TorqueNormalFR,
                      &HT08_CONTROL_SYSTEM_B.TorqueNormalRL,
                      &HT08_CONTROL_SYSTEM_B.TorqueNormalRR,
                      &HT08_CONTROL_SYSTEM_B.Normal_Percent_FL,
                      &HT08_CONTROL_SYSTEM_B.Normal_Percent_FR,
                      &HT08_CONTROL_SYSTEM_B.Normal_Percent_RL,
                      &HT08_CONTROL_SYSTEM_B.Normal_Percent_RR);

    // Merge: '<S3>/Merge' incorporates:
    //   SignalConversion: '<S5>/Signal Conversion'

    rtb_Merge = HT08_CONTROL_SYSTEM_B.TorqueNormalFL;

    // Merge: '<S3>/Merge1' incorporates:
    //   SignalConversion: '<S5>/Signal Conversion1'

    rtb_Merge1 = HT08_CONTROL_SYSTEM_B.TorqueNormalFR;

    // Merge: '<S3>/Merge2' incorporates:
    //   SignalConversion: '<S5>/Signal Conversion2'

    rtb_Merge2 = HT08_CONTROL_SYSTEM_B.TorqueNormalRL;

    // Merge: '<S3>/Merge3' incorporates:
    //   SignalConversion: '<S5>/Signal Conversion3'

    rtb_Merge3 = HT08_CONTROL_SYSTEM_B.TorqueNormalRR;

    // End of Outputs for SubSystem: '<Root>/Yaw and Normal Force TV'
  }

  // End of If: '<Root>/If1'

  // S-Function (scanpack): '<S1>/CAN Pack1' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element3'

  // S-Function (scanpack): '<S1>/CAN Pack1'
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.ID = 2011U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.Normal_Percent_FL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.Normal_Percent_FR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[2] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.Normal_Percent_RL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[4] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[5] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.Normal_Percent_RR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[6] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[6] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[7] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_normal.Data[7] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack2' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element4'

  // S-Function (scanpack): '<S1>/CAN Pack2'
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.ID = 2012U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.TorqueNormalFL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.TorqueNormalFR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[2] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.TorqueNormalRL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[4] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[5] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.TorqueNormalRR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[6] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[6] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[7] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_norm_p.Data[7] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack3' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element5'

  // S-Function (scanpack): '<S1>/CAN Pack3'
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.ID = 1997U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.PID_TV_o6;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[4] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[5] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.YawErrorrads;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[2] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.DesiredYawRaterads;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid_ya.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack4' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element6'

  // S-Function (scanpack): '<S1>/CAN Pack4'
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.ID = 2010U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.FLTORQUEPID;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.FRTORQUEPID;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[2] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.RLTORQUEPID;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[4] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[5] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.RRTORQUEPID;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[6] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[6] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[7] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pid__p.Data[7] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
  //   Outport generated from: '<Root>/Power Lim Status'

  Power_LimitMDLOBJ2.step(&HT08_CONTROL_SYSTEM_U.CurrentPowerkW, &rtb_Merge,
    &rtb_Merge1, &rtb_Merge2, &rtb_Merge3, &rtb_VehicleMath_o16,
    &rtb_VehicleMath_o17, &rtb_VehicleMath_o18, &rtb_VehicleMath_o19,
    &HT08_CONTROL_SYSTEM_U.usePowerLimit,
    &HT08_CONTROL_SYSTEM_U.usePIDPowerLimit,
    &HT08_CONTROL_SYSTEM_Y.FinalTorqueFL, &HT08_CONTROL_SYSTEM_Y.FinalTorqueFR,
    &HT08_CONTROL_SYSTEM_Y.FinalTorqueRL, &HT08_CONTROL_SYSTEM_Y.FinalTorqueRR,
    &HT08_CONTROL_SYSTEM_Y.PowerLimStatus, &HT08_CONTROL_SYSTEM_B.PowerLimit_o6,
    &HT08_CONTROL_SYSTEM_B.TorqueAdjustment,
    &HT08_CONTROL_SYSTEM_B.PowerLimit_o8, &HT08_CONTROL_SYSTEM_B.PowerLimit_o9,
    &HT08_CONTROL_SYSTEM_B.PowerLimit_o10, &HT08_CONTROL_SYSTEM_B.PowerLimit_o11);

  // S-Function (scanpack): '<S1>/CAN Pack5' incorporates:
  //   Outport generated from: '<Root>/Power Lim Status'
  //   Outport generated from: '<Root>/Out Bus Element7'

  // S-Function (scanpack): '<S1>/CAN Pack5'
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.ID = 2014U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.PowerLimit_o6;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[0] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFU) << 4));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF0U) >> 4));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[2] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xF000U) >>
              12));
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
        real_T result = HT08_CONTROL_SYSTEM_Y.PowerLimStatus;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[0] |
              (uint8_T)((uint8_T)(packedValue & (uint8_T)0xFU));
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
        real_T result = HT08_CONTROL_SYSTEM_B.TorqueAdjustment;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[2] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFU) << 4));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF0U) >> 4));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_power_.Data[4] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xF000U) >>
              12));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack6' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element8'

  // S-Function (scanpack): '<S1>/CAN Pack6'
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.ID = 2026U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.PowerLimit_o8;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.PowerLimit_o9;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[2] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.PowerLimit_o10;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[4] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[5] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.PowerLimit_o11;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[6] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[6] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[7] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_powe_p.Data[7] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.ID = 2027U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_Y.FinalTorqueFL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_Y.FinalTorqueFR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[2] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_Y.FinalTorqueRL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[4] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[5] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_Y.FinalTorqueRR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[6] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[6] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[7] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_pow_pn.Data[7] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S1>/CAN Pack8' incorporates:
  //   Inport generated from: '<Root>/Torque Average [Nm]'
  //   Outport generated from: '<Root>/Out Bus Element10'

  // S-Function (scanpack): '<S1>/CAN Pack8'
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.ID = 2042U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_U.TorqueAverageNm;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_controller_initia.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S4>/CAN Pack2' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element1'

  // S-Function (scanpack): '<S4>/CAN Pack2'
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.ID = 2031U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.BetaDeg;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_beta_deg.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S4>/CAN Pack' incorporates:
  //   Outport generated from: '<Root>/Out Bus Element'

  // S-Function (scanpack): '<S4>/CAN Pack'
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.ID = 2047U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.AlphaFLDeg;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.AlphaFRDeg;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[2] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.AlphaRLDeg;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[4] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[5] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.AlphaRRDeg;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[6] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[6] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[7] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_alpha_deg.Data[7] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S4>/CAN Pack1' incorporates:
  //   Outport generated from: '<Root>/BusElementOut'

  // S-Function (scanpack): '<S4>/CAN Pack1'
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.ID = 1999U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.SLFL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[0] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[1] | (uint8_T)
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
        real_T result = HT08_CONTROL_SYSTEM_B.SLFR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[2] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[3] | (uint8_T)
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
        real_T result = HT08_CONTROL_SYSTEM_B.SLRL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[4] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[5] | (uint8_T)
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
        real_T result = HT08_CONTROL_SYSTEM_B.SLRR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[6] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[6] | (uint8_T)
              ((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[7] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_sl.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S4>/CAN Pack3' incorporates:
  //   Outport generated from: '<Root>/Bus Element Out'

  // S-Function (scanpack): '<S4>/CAN Pack3'
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.ID = 1998U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.LongCornerVelFL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.LongCornerVelFR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[2] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[2] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[3] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[3] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.LongCornerVelRL;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[4] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[4] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[5] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[5] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
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
        real_T result = HT08_CONTROL_SYSTEM_B.LongCornerVelRR;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[6] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[6] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[7] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_long_corner_.Data[7] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S4>/CAN Pack4' incorporates:
  //   Outport generated from: '<Root>/Bus Element Out1'

  // S-Function (scanpack): '<S4>/CAN Pack4'
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.ID = 1994U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.WheelSteerAvgDeg;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_wheel_steer_.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }

  // S-Function (scanpack): '<S4>/CAN Pack5' incorporates:
  //   Outport generated from: '<Root>/Bus Element Out2'

  // S-Function (scanpack): '<S4>/CAN Pack5'
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.ID = 1995U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Length = 8U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Extended = 0U;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Remote = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[0] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[1] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[2] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[3] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[4] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[5] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[6] = 0;
  HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[7] = 0;

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
        real_T result = HT08_CONTROL_SYSTEM_B.DesiredYawRaterads;

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
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[0] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[0] |
              (uint8_T)((uint16_T)(tempValue & (uint16_T)0xFFU));
            HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[1] =
              HT08_CONTROL_SYSTEM_Y.controllerBus_vehm_kin_desired_.Data[1] |
              (uint8_T)((uint16_T)((uint16_T)(tempValue & (uint16_T)0xFF00U) >>
              8));
          }
        }
      }
    }
  }
}

// Model initialize function
void HT08_CONTROL_SYSTEM::initialize()
{
  // Registration code

  // block I/O
  {
    HT08_CONTROL_SYSTEM_B.PID_TV_o7 = 0.001;
  }

  // Initialize DataMapInfo substructure containing ModelMap for C API
  HT08_CONTROL_SYSTEM_InitializeDataMapInfo((&HT08_CONTROL_SYSTEM_M),
    &HT08_CONTROL_SYSTEM_B);

  // Model Initialize function for ModelReference Block: '<S2>/Model3'

  // Set error status pointer for ModelReference Block: '<S2>/Model3'
  Model3MDLOBJ1.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&HT08_CONTROL_SYSTEM_M)));
  Model3MDLOBJ1.initialize();
  Model3MDLOBJ1.setupCAPIInfo(&((&HT08_CONTROL_SYSTEM_M)->DataMapInfo.mmi),
    "HT08_CONTROL_SYSTEM/Launch Control/Model3",0,-1);

  // Model Initialize function for ModelReference Block: '<Root>/Power Limit'

  // Set error status pointer for ModelReference Block: '<Root>/Power Limit'
  Power_LimitMDLOBJ2.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&HT08_CONTROL_SYSTEM_M)));
  Power_LimitMDLOBJ2.initialize();
  Power_LimitMDLOBJ2.setupCAPIInfo(&((&HT08_CONTROL_SYSTEM_M)->DataMapInfo.mmi),
    "HT08_CONTROL_SYSTEM/Power Limit",1,-1);

  // Model Initialize function for ModelReference Block: '<Root>/Vehicle Math'

  // Set error status pointer for ModelReference Block: '<Root>/Vehicle Math'
  Vehicle_MathMDLOBJ3.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&HT08_CONTROL_SYSTEM_M)));
  Vehicle_MathMDLOBJ3.initialize();
  Vehicle_MathMDLOBJ3.setupCAPIInfo(&((&HT08_CONTROL_SYSTEM_M)->DataMapInfo.mmi),
    "HT08_CONTROL_SYSTEM/Vehicle Math",2,-1);

  // Model Initialize function for ModelReference Block: '<S5>/Model'

  // Set error status pointer for ModelReference Block: '<S5>/Model'
  ModelMDLOBJ4.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&HT08_CONTROL_SYSTEM_M)));
  ModelMDLOBJ4.initialize();
  ModelMDLOBJ4.setupCAPIInfo(&((&HT08_CONTROL_SYSTEM_M)->DataMapInfo.mmi),
    "HT08_CONTROL_SYSTEM/Yaw and Normal Force TV/Model",3,-1);

  // Model Initialize function for ModelReference Block: '<S5>/PID_TV'

  // Set error status pointer for ModelReference Block: '<S5>/PID_TV'
  PID_TVMDLOBJ5.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&HT08_CONTROL_SYSTEM_M)));
  PID_TVMDLOBJ5.initialize();
  PID_TVMDLOBJ5.setupCAPIInfo(&((&HT08_CONTROL_SYSTEM_M)->DataMapInfo.mmi),
    "HT08_CONTROL_SYSTEM/Yaw and Normal Force TV/PID_TV",4,-1);
}

// Model terminate function
void HT08_CONTROL_SYSTEM::terminate()
{
  // (no terminate code required)
}

// Constructor
HT08_CONTROL_SYSTEM::HT08_CONTROL_SYSTEM() :
  HT08_CONTROL_SYSTEM_U(),
  HT08_CONTROL_SYSTEM_Y(),
  HT08_CONTROL_SYSTEM_B(),
  HT08_CONTROL_SYSTEM_DW(),
  HT08_CONTROL_SYSTEM_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
HT08_CONTROL_SYSTEM::~HT08_CONTROL_SYSTEM() = default;

// Real-Time Model get method
HT08_CONTROL_SYSTEM::RT_MODEL_HT08_CONTROL_SYSTEM_T * HT08_CONTROL_SYSTEM::
  getRTM()
{
  return (&HT08_CONTROL_SYSTEM_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
