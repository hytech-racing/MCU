//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: HT08_CASE_capi.cpp
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
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "HT08_CASE_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  // HOST_CAPI_BUILD
#include "builtin_typeid_types.h"
#include "HT08_CASE.h"
#include "HT08_CASE_capi.h"
#include "HT08_CASE_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((nullptr))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 // HOST_CAPI_BUILD

// Block output signal information
static rtwCAPI_Signals rtBlockSignals[]{
  // addrMapIndex, sysNum, blockPath,
  //  signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex

  { 0, 1, TARGET_STRING("HT08_CASE/Power Limit"),
    TARGET_STRING(""), 4, 0, 0, 0, 0 },

  { 1, 1, TARGET_STRING("HT08_CASE/Power Limit"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  { 2, 1, TARGET_STRING("HT08_CASE/Power Limit"),
    TARGET_STRING(""), 6, 0, 0, 0, 0 },

  { 3, 1, TARGET_STRING("HT08_CASE/Power Limit"),
    TARGET_STRING(""), 7, 0, 0, 0, 0 },

  { 4, 1, TARGET_STRING("HT08_CASE/Power Limit"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 5, 1, TARGET_STRING("HT08_CASE/Power Limit"),
    TARGET_STRING(""), 9, 0, 0, 0, 0 },

  { 6, 1, TARGET_STRING("HT08_CASE/Power Limit"),
    TARGET_STRING(""), 10, 0, 0, 0, 0 },

  { 7, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 8, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 1, 0, 0, 0, 0 },

  { 9, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 2, 0, 0, 0, 0 },

  { 10, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 3, 0, 0, 0, 0 },

  { 11, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 4, 0, 0, 0, 0 },

  { 12, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  { 13, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 6, 0, 0, 0, 0 },

  { 14, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 7, 0, 0, 0, 0 },

  { 15, 1, TARGET_STRING("HT08_CASE/TCS"),
    TARGET_STRING(""), 8, 0, 1, 0, 0 },

  { 16, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Beta [Deg]"), 0, 0, 0, 0, 0 },

  { 17, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Alpha FL [Deg]"), 1, 0, 0, 0, 0 },

  { 18, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Alpha FR [Deg]"), 2, 0, 0, 0, 0 },

  { 19, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Alpha RL [Deg]"), 3, 0, 0, 0, 0 },

  { 20, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Alpha RR [Deg]"), 4, 0, 0, 0, 0 },

  { 21, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Long Corner Vel FL"), 5, 0, 0, 0, 0 },

  { 22, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Long Corner Vel FR"), 6, 0, 0, 0, 0 },

  { 23, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Long Corner Vel RL"), 7, 0, 0, 0, 0 },

  { 24, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Long Corner Vel RR"), 8, 0, 0, 0, 0 },

  { 25, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING(""), 9, 0, 0, 0, 0 },

  { 26, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING(""), 10, 0, 0, 0, 0 },

  { 27, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING(""), 11, 0, 0, 0, 0 },

  { 28, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING(""), 12, 0, 0, 0, 0 },

  { 29, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING(""), 13, 0, 0, 0, 0 },

  { 30, 1, TARGET_STRING("HT08_CASE/Vehicle Math"),
    TARGET_STRING("Wheel Steer Avg [Deg]"), 14, 0, 0, 0, 0 },

  { 31, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/Model"),
    TARGET_STRING("Torque Normal FL"), 0, 0, 0, 0, 0 },

  { 32, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/Model"),
    TARGET_STRING("Torque Normal FR"), 1, 0, 0, 0, 0 },

  { 33, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/Model"),
    TARGET_STRING("Torque Normal RL"), 2, 0, 0, 0, 0 },

  { 34, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/Model"),
    TARGET_STRING("Torque Normal RR"), 3, 0, 0, 0, 0 },

  { 35, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/Model"),
    TARGET_STRING(""), 4, 0, 0, 0, 0 },

  { 36, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/Model"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  { 37, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/Model"),
    TARGET_STRING(""), 6, 0, 0, 0, 0 },

  { 38, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/Model"),
    TARGET_STRING(""), 7, 0, 0, 0, 0 },

  { 39, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/PID_TV"),
    TARGET_STRING("FR TORQUE PID"), 0, 0, 0, 0, 0 },

  { 40, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/PID_TV"),
    TARGET_STRING("RR TORQUE PID"), 1, 0, 0, 0, 0 },

  { 41, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/PID_TV"),
    TARGET_STRING("FL TORQUE PID"), 2, 0, 0, 0, 0 },

  { 42, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/PID_TV"),
    TARGET_STRING("RL TORQUE PID"), 3, 0, 0, 0, 0 },

  { 43, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/PID_TV"),
    TARGET_STRING(""), 4, 0, 0, 0, 0 },

  { 44, 1, TARGET_STRING("HT08_CASE/Yaw and Normal Force TV/PID_TV"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  {
    0, 0, (nullptr), (nullptr), 0, 0, 0, 0, 0
  }
};

// Individual block tuning is not valid when inline parameters is *
//  selected. An empty map is produced to provide a consistent     *
//  interface independent  of inlining parameters.                 *

static rtwCAPI_BlockParameters rtBlockParameters[]{
  // addrMapIndex, blockPath,
  //  paramName, dataTypeIndex, dimIndex, fixPtIdx

  {
    0, (nullptr), (nullptr), 0, 0, 0
  }
};

// Tunable variable parameters
static rtwCAPI_ModelParameters rtModelParameters[]{
  // addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex
  { 0, (nullptr), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

// Initialize Data Address
static void HT08_CASE_InitializeDataAddr(void* dataAddr[], HT08_CASE::
  B_HT08_CASE_T *HT08_CASE_B)
{
  dataAddr[0] = (void*) (&HT08_CASE_B->PowerLimit_o5);
  dataAddr[1] = (void*) (&HT08_CASE_B->PowerLimit_o6);
  dataAddr[2] = (void*) (&HT08_CASE_B->TorqueAdjustment);
  dataAddr[3] = (void*) (&HT08_CASE_B->PowerLimit_o8);
  dataAddr[4] = (void*) (&HT08_CASE_B->PowerLimit_o9);
  dataAddr[5] = (void*) (&HT08_CASE_B->PowerLimit_o10);
  dataAddr[6] = (void*) (&HT08_CASE_B->PowerLimit_o11);
  dataAddr[7] = (void*) (&HT08_CASE_B->TCS_o1);
  dataAddr[8] = (void*) (&HT08_CASE_B->TCS_o2);
  dataAddr[9] = (void*) (&HT08_CASE_B->TCS_o3);
  dataAddr[10] = (void*) (&HT08_CASE_B->TCS_o4);
  dataAddr[11] = (void*) (&HT08_CASE_B->TCS_o5);
  dataAddr[12] = (void*) (&HT08_CASE_B->TCS_o6);
  dataAddr[13] = (void*) (&HT08_CASE_B->TCS_o7);
  dataAddr[14] = (void*) (&HT08_CASE_B->TCS_o8);
  dataAddr[15] = (void*) (&HT08_CASE_B->TCS_o9[0]);
  dataAddr[16] = (void*) (&HT08_CASE_B->BetaDeg);
  dataAddr[17] = (void*) (&HT08_CASE_B->AlphaFLDeg);
  dataAddr[18] = (void*) (&HT08_CASE_B->AlphaFRDeg);
  dataAddr[19] = (void*) (&HT08_CASE_B->AlphaRLDeg);
  dataAddr[20] = (void*) (&HT08_CASE_B->AlphaRRDeg);
  dataAddr[21] = (void*) (&HT08_CASE_B->LongCornerVelFL);
  dataAddr[22] = (void*) (&HT08_CASE_B->LongCornerVelFR);
  dataAddr[23] = (void*) (&HT08_CASE_B->LongCornerVelRL);
  dataAddr[24] = (void*) (&HT08_CASE_B->LongCornerVelRR);
  dataAddr[25] = (void*) (&HT08_CASE_B->VehicleMath_o10);
  dataAddr[26] = (void*) (&HT08_CASE_B->SLFL);
  dataAddr[27] = (void*) (&HT08_CASE_B->SLFR);
  dataAddr[28] = (void*) (&HT08_CASE_B->SLRL);
  dataAddr[29] = (void*) (&HT08_CASE_B->SLRR);
  dataAddr[30] = (void*) (&HT08_CASE_B->WheelSteerAvgDeg);
  dataAddr[31] = (void*) (&HT08_CASE_B->TorqueNormalFL);
  dataAddr[32] = (void*) (&HT08_CASE_B->TorqueNormalFR);
  dataAddr[33] = (void*) (&HT08_CASE_B->TorqueNormalRL);
  dataAddr[34] = (void*) (&HT08_CASE_B->TorqueNormalRR);
  dataAddr[35] = (void*) (&HT08_CASE_B->Normal_Percent_FL);
  dataAddr[36] = (void*) (&HT08_CASE_B->Normal_Percent_FR);
  dataAddr[37] = (void*) (&HT08_CASE_B->Normal_Percent_RL);
  dataAddr[38] = (void*) (&HT08_CASE_B->Normal_Percent_RR);
  dataAddr[39] = (void*) (&HT08_CASE_B->FRTORQUEPID);
  dataAddr[40] = (void*) (&HT08_CASE_B->RRTORQUEPID);
  dataAddr[41] = (void*) (&HT08_CASE_B->FLTORQUEPID);
  dataAddr[42] = (void*) (&HT08_CASE_B->RLTORQUEPID);
  dataAddr[43] = (void*) (&HT08_CASE_B->PID_TV_o5);
  dataAddr[44] = (void*) (&HT08_CASE_B->PID_TV_o6);
}

#endif

// Initialize Data Run-Time Dimension Buffer Address
#ifndef HOST_CAPI_BUILD

static void HT08_CASE_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (nullptr);
}

#endif

#ifndef HOST_CAPI_BUILD

// Initialize logging function pointers
static void HT08_CASE_InitializeLoggingFunctions(RTWLoggingFcnPtr loggingPtrs[])
{
  loggingPtrs[0] = (nullptr);
  loggingPtrs[1] = (nullptr);
  loggingPtrs[2] = (nullptr);
  loggingPtrs[3] = (nullptr);
  loggingPtrs[4] = (nullptr);
  loggingPtrs[5] = (nullptr);
  loggingPtrs[6] = (nullptr);
  loggingPtrs[7] = (nullptr);
  loggingPtrs[8] = (nullptr);
  loggingPtrs[9] = (nullptr);
  loggingPtrs[10] = (nullptr);
  loggingPtrs[11] = (nullptr);
  loggingPtrs[12] = (nullptr);
  loggingPtrs[13] = (nullptr);
  loggingPtrs[14] = (nullptr);
  loggingPtrs[15] = (nullptr);
  loggingPtrs[16] = (nullptr);
  loggingPtrs[17] = (nullptr);
  loggingPtrs[18] = (nullptr);
  loggingPtrs[19] = (nullptr);
  loggingPtrs[20] = (nullptr);
  loggingPtrs[21] = (nullptr);
  loggingPtrs[22] = (nullptr);
  loggingPtrs[23] = (nullptr);
  loggingPtrs[24] = (nullptr);
  loggingPtrs[25] = (nullptr);
  loggingPtrs[26] = (nullptr);
  loggingPtrs[27] = (nullptr);
  loggingPtrs[28] = (nullptr);
  loggingPtrs[29] = (nullptr);
  loggingPtrs[30] = (nullptr);
  loggingPtrs[31] = (nullptr);
  loggingPtrs[32] = (nullptr);
  loggingPtrs[33] = (nullptr);
  loggingPtrs[34] = (nullptr);
  loggingPtrs[35] = (nullptr);
  loggingPtrs[36] = (nullptr);
  loggingPtrs[37] = (nullptr);
  loggingPtrs[38] = (nullptr);
  loggingPtrs[39] = (nullptr);
  loggingPtrs[40] = (nullptr);
  loggingPtrs[41] = (nullptr);
  loggingPtrs[42] = (nullptr);
  loggingPtrs[43] = (nullptr);
  loggingPtrs[44] = (nullptr);
}

#endif

// Data Type Map - use dataTypeMapIndex to access this structure
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[]{
  // cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
  //  isComplex, isPointer, enumStorageType
  { "double", "real_T", 0, 0, sizeof(real_T), (uint8_T)SS_DOUBLE, 0, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

// Structure Element Map - use elemMapIndex to access this structure
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[]{
  // elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex
  { (nullptr), 0, 0, 0, 0 },
};

// Dimension Map - use dimensionMapIndex to access elements of ths structure
static rtwCAPI_DimensionMap rtDimensionMap[]{
  // dataOrientation, dimArrayIndex, numDims, vardimsIndex
  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 }
};

// Dimension Array- use dimArrayIndex to access elements of this array
static uint_T rtDimensionArray[]{
  1,                                   // 0
  1,                                   // 1
  8,                                   // 2
  1                                    // 3
};

// C-API stores floating point values in an array. The elements of this  *
//  are unique. This ensures that values which are shared across the model*
//  are stored in the most efficient way. These values are referenced by  *
//            - rtwCAPI_FixPtMap.fracSlopePtr,                            *
//            - rtwCAPI_FixPtMap.biasPtr,                                 *
//            - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
//            - rtwCAPI_SampleTimeMap.sampleOffsetPtr
static const real_T rtcapiStoredFloats[]{
  0.001, 0.0
};

// Fixed Point Map
static rtwCAPI_FixPtMap rtFixPtMap[]{
  // fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned
  { (nullptr), (nullptr), rtwCAPI_FIX_RESERVED, 0, 0, (boolean_T)0 },
};

// Sample Time Map - use sTimeIndex to access elements of ths structure
static rtwCAPI_SampleTimeMap rtSampleTimeMap[]{
  // samplePeriodPtr, sampleOffsetPtr, tid, samplingMode
  { static_cast<const void *>(&rtcapiStoredFloats[0]), static_cast<const void *>
    (&rtcapiStoredFloats[1]), static_cast<int8_T>(0), static_cast<uint8_T>(0) }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic{
  // Signals:{signals, numSignals,
  //            rootInputs, numRootInputs,
  //            rootOutputs, numRootOutputs},
  //  Params: {blockParameters, numBlockParameters,
  //           modelParameters, numModelParameters},
  //  States: {states, numStates},
  //  Maps:   {dataTypeMap, dimensionMap, fixPtMap,
  //           elementMap, sampleTimeMap, dimensionArray},
  //  TargetType: targetType

  { rtBlockSignals, 45,
    (nullptr), 0,
    (nullptr), 0 },

  { rtBlockParameters, 0,
    rtModelParameters, 0 },

  { (nullptr), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 3889057229U,
    1836662284U,
    863743702U,
    1558041043U },
  (nullptr), 0,
  (boolean_T)0
};

// Function to get C API Model Mapping Static Info
const rtwCAPI_ModelMappingStaticInfo*
  HT08_CASE_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

// Cache pointers into DataMapInfo substructure of RTModel
#ifndef HOST_CAPI_BUILD

void HT08_CASE_InitializeDataMapInfo(HT08_CASE::RT_MODEL_HT08_CASE_T *const
  HT08_CASE_M, HT08_CASE::B_HT08_CASE_T *HT08_CASE_B)
{
  // Set C-API version
  rtwCAPI_SetVersion(HT08_CASE_M->DataMapInfo.mmi, 1);

  // Cache static C-API data into the Real-time Model Data structure
  rtwCAPI_SetStaticMap(HT08_CASE_M->DataMapInfo.mmi, &mmiStatic);

  // Cache static C-API logging data into the Real-time Model Data structure
  rtwCAPI_SetLoggingStaticMap(HT08_CASE_M->DataMapInfo.mmi, (nullptr));

  // Cache C-API Data Addresses into the Real-Time Model Data structure
  HT08_CASE_InitializeDataAddr(HT08_CASE_M->DataMapInfo.dataAddress, HT08_CASE_B);
  rtwCAPI_SetDataAddressMap(HT08_CASE_M->DataMapInfo.mmi,
    HT08_CASE_M->DataMapInfo.dataAddress);

  // Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure 
  HT08_CASE_InitializeVarDimsAddr(HT08_CASE_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(HT08_CASE_M->DataMapInfo.mmi,
    HT08_CASE_M->DataMapInfo.vardimsAddress);

  // Set Instance specific path
  rtwCAPI_SetPath(HT08_CASE_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetFullPath(HT08_CASE_M->DataMapInfo.mmi, (nullptr));

  // Cache C-API logging function pointers into the Real-Time Model Data structure 
  HT08_CASE_InitializeLoggingFunctions(HT08_CASE_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(HT08_CASE_M->DataMapInfo.mmi,
    HT08_CASE_M->DataMapInfo.loggingPtrs);

  // Cache the instance C-API logging pointer
  rtwCAPI_SetInstanceLoggingInfo(HT08_CASE_M->DataMapInfo.mmi, (nullptr));

  // Set reference to submodels
  rtwCAPI_SetChildMMIArray(HT08_CASE_M->DataMapInfo.mmi,
    HT08_CASE_M->DataMapInfo.childMMI);
  rtwCAPI_SetChildMMIArrayLen(HT08_CASE_M->DataMapInfo.mmi, 5);
}

#else                                  // HOST_CAPI_BUILD
#ifdef __cplusplus

extern "C"
{

#endif

  void HT08_CASE_host_InitializeDataMapInfo(HT08_CASE_host_DataMapInfo_T
    *dataMap, const char *path)
  {
    // Set C-API version
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    // Cache static C-API data into the Real-time Model Data structure
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    // host data address map is NULL
    rtwCAPI_SetDataAddressMap(dataMap->mmi, (nullptr));

    // host vardims address map is NULL
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, (nullptr));

    // Set Instance specific path
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, (nullptr));

    // Set reference to submodels
    dataMap->childMMI[0] = &(dataMap->child0.mmi);
    POWER_LIMIT_host_InitializeDataMapInfo(&(dataMap->child0),
      "HT08_CASE/Power Limit");
    dataMap->childMMI[1] = &(dataMap->child1.mmi);
    TRACTION_CONTROL_host_InitializeDataMapInfo(&(dataMap->child1),
      "HT08_CASE/TCS");
    dataMap->childMMI[2] = &(dataMap->child2.mmi);
    BasicVehicleMath_host_InitializeDataMapInfo(&(dataMap->child2),
      "HT08_CASE/Vehicle Math");
    dataMap->childMMI[3] = &(dataMap->child3.mmi);
    NORMAL_FORCE_TV_host_InitializeDataMapInfo(&(dataMap->child3),
      "HT08_CASE/Yaw and Normal Force TV/Model");
    dataMap->childMMI[4] = &(dataMap->child4.mmi);
    PID_TV_host_InitializeDataMapInfo(&(dataMap->child4),
      "HT08_CASE/Yaw and Normal Force TV/PID_TV");
    rtwCAPI_SetChildMMIArray(dataMap->mmi, dataMap->childMMI);
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 5);
  }

#ifdef __cplusplus

}

#endif
#endif                                 // HOST_CAPI_BUILD

//
// File trailer for generated code.
//
// [EOF]
//
