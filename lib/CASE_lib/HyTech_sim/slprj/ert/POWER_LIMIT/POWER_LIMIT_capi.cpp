//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: POWER_LIMIT_capi.cpp
//
// Code generated for Simulink model 'POWER_LIMIT'.
//
// Model version                  : 1.34
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Apr 11 22:49:33 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "POWER_LIMIT_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  // HOST_CAPI_BUILD
#include "builtin_typeid_types.h"
#include "POWER_LIMIT.h"
#include "POWER_LIMIT_capi.h"
#include "POWER_LIMIT_private.h"
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

  { 0, 1, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  { 1, 1, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT"),
    TARGET_STRING(""), 6, 0, 0, 0, 0 },

  { 2, 1, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT"),
    TARGET_STRING(""), 7, 0, 0, 0, 0 },

  { 3, 1, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 4, 6, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  { 5, 6, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT"),
    TARGET_STRING(""), 6, 0, 0, 0, 0 },

  { 6, 6, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT"),
    TARGET_STRING(""), 7, 0, 0, 0, 0 },

  { 7, 6, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 8, 1, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT/MATLAB Function"),
    TARGET_STRING(""), 4, 0, 0, 0, 0 },

  { 9, 1, TARGET_STRING("POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT/MATLAB Function"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  { 10, 1, TARGET_STRING(
    "POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT/MATLAB Function"),
    TARGET_STRING(""), 6, 0, 0, 0, 0 },

  { 11, 1, TARGET_STRING(
    "POWER_LIMIT/If Action Subsystem/If Action Subsystem/HT07 POWER LIMIT/MATLAB Function"),
    TARGET_STRING(""), 7, 0, 0, 0, 0 },

  { 12, 6, TARGET_STRING(
    "POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT/MATLAB Function"),
    TARGET_STRING(""), 4, 0, 0, 0, 0 },

  { 13, 6, TARGET_STRING(
    "POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT/MATLAB Function"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  { 14, 6, TARGET_STRING(
    "POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT/MATLAB Function"),
    TARGET_STRING(""), 6, 0, 0, 0, 0 },

  { 15, 6, TARGET_STRING(
    "POWER_LIMIT/If Action Subsystem/If Action Subsystem1/HT07 POWER LIMIT/MATLAB Function"),
    TARGET_STRING(""), 7, 0, 0, 0, 0 },

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
static void POWER_LIMIT_InitializeDataAddr(void* dataAddr[], POWER_LIMIT::
  B_POWER_LIMIT_T *POWER_LIMIT_B)
{
  dataAddr[0] = (void*) (&POWER_LIMIT_B->cornerPower_FL_i);
  dataAddr[1] = (void*) (&POWER_LIMIT_B->cornerPower_FR_k);
  dataAddr[2] = (void*) (&POWER_LIMIT_B->cornerPower_RL_b);
  dataAddr[3] = (void*) (&POWER_LIMIT_B->cornerPower_RR_b);
  dataAddr[4] = (void*) (&POWER_LIMIT_B->cornerPower_FL);
  dataAddr[5] = (void*) (&POWER_LIMIT_B->cornerPower_FR);
  dataAddr[6] = (void*) (&POWER_LIMIT_B->cornerPower_RL);
  dataAddr[7] = (void*) (&POWER_LIMIT_B->cornerPower_RR);
  dataAddr[8] = (void*) (&POWER_LIMIT_B->cornerPower_FL_i);
  dataAddr[9] = (void*) (&POWER_LIMIT_B->cornerPower_FR_k);
  dataAddr[10] = (void*) (&POWER_LIMIT_B->cornerPower_RL_b);
  dataAddr[11] = (void*) (&POWER_LIMIT_B->cornerPower_RR_b);
  dataAddr[12] = (void*) (&POWER_LIMIT_B->cornerPower_FL);
  dataAddr[13] = (void*) (&POWER_LIMIT_B->cornerPower_FR);
  dataAddr[14] = (void*) (&POWER_LIMIT_B->cornerPower_RL);
  dataAddr[15] = (void*) (&POWER_LIMIT_B->cornerPower_RR);
}

#endif

// Initialize Data Run-Time Dimension Buffer Address
#ifndef HOST_CAPI_BUILD

static void POWER_LIMIT_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (nullptr);
}

#endif

#ifndef HOST_CAPI_BUILD

// Initialize logging function pointers
static void POWER_LIMIT_InitializeLoggingFunctions(RTWLoggingFcnPtr loggingPtrs[])
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
  { rtwCAPI_SCALAR, 0, 2, 0 }
};

// Dimension Array- use dimArrayIndex to access elements of this array
static uint_T rtDimensionArray[]{
  1,                                   // 0
  1                                    // 1
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

  { rtBlockSignals, 16,
    (nullptr), 0,
    (nullptr), 0 },

  { rtBlockParameters, 0,
    rtModelParameters, 0 },

  { (nullptr), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 555444912U,
    3008848702U,
    2513927759U,
    307553862U },
  (nullptr), 0,
  (boolean_T)0
};

// Function to get C API Model Mapping Static Info
const rtwCAPI_ModelMappingStaticInfo*
  POWER_LIMIT_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

// Cache pointers into DataMapInfo substructure of RTModel
#ifndef HOST_CAPI_BUILD

void POWER_LIMIT_InitializeDataMapInfo(POWER_LIMIT::RT_MODEL_POWER_LIMIT_T *
  const POWER_LIMIT_M, POWER_LIMIT::B_POWER_LIMIT_T *POWER_LIMIT_B)
{
  // Set C-API version
  rtwCAPI_SetVersion(POWER_LIMIT_M->DataMapInfo.mmi, 1);

  // Cache static C-API data into the Real-time Model Data structure
  rtwCAPI_SetStaticMap(POWER_LIMIT_M->DataMapInfo.mmi, &mmiStatic);

  // Cache static C-API logging data into the Real-time Model Data structure
  rtwCAPI_SetLoggingStaticMap(POWER_LIMIT_M->DataMapInfo.mmi, (nullptr));

  // Cache C-API Data Addresses into the Real-Time Model Data structure
  POWER_LIMIT_InitializeDataAddr(POWER_LIMIT_M->DataMapInfo.dataAddress,
    POWER_LIMIT_B);
  rtwCAPI_SetDataAddressMap(POWER_LIMIT_M->DataMapInfo.mmi,
    POWER_LIMIT_M->DataMapInfo.dataAddress);

  // Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure 
  POWER_LIMIT_InitializeVarDimsAddr(POWER_LIMIT_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(POWER_LIMIT_M->DataMapInfo.mmi,
    POWER_LIMIT_M->DataMapInfo.vardimsAddress);

  // Set Instance specific path
  rtwCAPI_SetPath(POWER_LIMIT_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetFullPath(POWER_LIMIT_M->DataMapInfo.mmi, (nullptr));

  // Cache C-API logging function pointers into the Real-Time Model Data structure 
  POWER_LIMIT_InitializeLoggingFunctions(POWER_LIMIT_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(POWER_LIMIT_M->DataMapInfo.mmi,
    POWER_LIMIT_M->DataMapInfo.loggingPtrs);

  // Cache the instance C-API logging pointer
  rtwCAPI_SetInstanceLoggingInfo(POWER_LIMIT_M->DataMapInfo.mmi, (nullptr));

  // Set reference to submodels
  rtwCAPI_SetChildMMIArray(POWER_LIMIT_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetChildMMIArrayLen(POWER_LIMIT_M->DataMapInfo.mmi, 0);
}

#else                                  // HOST_CAPI_BUILD
#ifdef __cplusplus

extern "C"
{

#endif

  void POWER_LIMIT_host_InitializeDataMapInfo(POWER_LIMIT_host_DataMapInfo_T
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
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (nullptr));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
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
