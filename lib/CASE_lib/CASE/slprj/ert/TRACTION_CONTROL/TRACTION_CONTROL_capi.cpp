//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TRACTION_CONTROL_capi.cpp
//
// Code generated for Simulink model 'TRACTION_CONTROL'.
//
// Model version                  : 1.11
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Mon Apr 15 17:38:58 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "TRACTION_CONTROL_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  // HOST_CAPI_BUILD
#include "builtin_typeid_types.h"
#include "TRACTION_CONTROL.h"
#include "TRACTION_CONTROL_capi.h"
#include "TRACTION_CONTROL_private.h"
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

  { 0, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 1, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 2, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 3, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 4, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 5, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 6, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 7, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem"),
    TARGET_STRING(""), 8, 0, 0, 0, 0 },

  { 8, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem/Switch"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 9, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem/Switch1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 10, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem/Switch2"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 11, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem/Switch3"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 12, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem/Switch4"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 13, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem/Switch5"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 14, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem/Switch6"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 15, 11, TARGET_STRING("TRACTION_CONTROL/If Action Subsystem/Switch7"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

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
static void TRACTION_CONTROL_InitializeDataAddr(void* dataAddr[],
  TRACTION_CONTROL::B_TRACTION_CONTROL_T *TRACTION_CONTROL_B)
{
  dataAddr[0] = (void*) (&TRACTION_CONTROL_B->Switch);
  dataAddr[1] = (void*) (&TRACTION_CONTROL_B->Switch4);
  dataAddr[2] = (void*) (&TRACTION_CONTROL_B->Switch1);
  dataAddr[3] = (void*) (&TRACTION_CONTROL_B->Switch2);
  dataAddr[4] = (void*) (&TRACTION_CONTROL_B->Switch3);
  dataAddr[5] = (void*) (&TRACTION_CONTROL_B->Switch5);
  dataAddr[6] = (void*) (&TRACTION_CONTROL_B->Switch6);
  dataAddr[7] = (void*) (&TRACTION_CONTROL_B->Switch7);
  dataAddr[8] = (void*) (&TRACTION_CONTROL_B->Switch);
  dataAddr[9] = (void*) (&TRACTION_CONTROL_B->Switch1);
  dataAddr[10] = (void*) (&TRACTION_CONTROL_B->Switch2);
  dataAddr[11] = (void*) (&TRACTION_CONTROL_B->Switch3);
  dataAddr[12] = (void*) (&TRACTION_CONTROL_B->Switch4);
  dataAddr[13] = (void*) (&TRACTION_CONTROL_B->Switch5);
  dataAddr[14] = (void*) (&TRACTION_CONTROL_B->Switch6);
  dataAddr[15] = (void*) (&TRACTION_CONTROL_B->Switch7);
}

#endif

// Initialize Data Run-Time Dimension Buffer Address
#ifndef HOST_CAPI_BUILD

static void TRACTION_CONTROL_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (nullptr);
}

#endif

#ifndef HOST_CAPI_BUILD

// Initialize logging function pointers
static void TRACTION_CONTROL_InitializeLoggingFunctions(RTWLoggingFcnPtr
  loggingPtrs[])
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

  { 221063980U,
    4026814401U,
    92965693U,
    4169696004U },
  (nullptr), 0,
  (boolean_T)0
};

// Function to get C API Model Mapping Static Info
const rtwCAPI_ModelMappingStaticInfo*
  TRACTION_CONTROL_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

// Cache pointers into DataMapInfo substructure of RTModel
#ifndef HOST_CAPI_BUILD

void TRACTION_CONTROL_InitializeDataMapInfo(TRACTION_CONTROL::
  RT_MODEL_TRACTION_CONTROL_T *const TRACTION_CONTROL_M, TRACTION_CONTROL::
  B_TRACTION_CONTROL_T *TRACTION_CONTROL_B)
{
  // Set C-API version
  rtwCAPI_SetVersion(TRACTION_CONTROL_M->DataMapInfo.mmi, 1);

  // Cache static C-API data into the Real-time Model Data structure
  rtwCAPI_SetStaticMap(TRACTION_CONTROL_M->DataMapInfo.mmi, &mmiStatic);

  // Cache static C-API logging data into the Real-time Model Data structure
  rtwCAPI_SetLoggingStaticMap(TRACTION_CONTROL_M->DataMapInfo.mmi, (nullptr));

  // Cache C-API Data Addresses into the Real-Time Model Data structure
  TRACTION_CONTROL_InitializeDataAddr
    (TRACTION_CONTROL_M->DataMapInfo.dataAddress, TRACTION_CONTROL_B);
  rtwCAPI_SetDataAddressMap(TRACTION_CONTROL_M->DataMapInfo.mmi,
    TRACTION_CONTROL_M->DataMapInfo.dataAddress);

  // Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure 
  TRACTION_CONTROL_InitializeVarDimsAddr
    (TRACTION_CONTROL_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(TRACTION_CONTROL_M->DataMapInfo.mmi,
    TRACTION_CONTROL_M->DataMapInfo.vardimsAddress);

  // Set Instance specific path
  rtwCAPI_SetPath(TRACTION_CONTROL_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetFullPath(TRACTION_CONTROL_M->DataMapInfo.mmi, (nullptr));

  // Cache C-API logging function pointers into the Real-Time Model Data structure 
  TRACTION_CONTROL_InitializeLoggingFunctions
    (TRACTION_CONTROL_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(TRACTION_CONTROL_M->DataMapInfo.mmi,
    TRACTION_CONTROL_M->DataMapInfo.loggingPtrs);

  // Cache the instance C-API logging pointer
  rtwCAPI_SetInstanceLoggingInfo(TRACTION_CONTROL_M->DataMapInfo.mmi, (nullptr));

  // Set reference to submodels
  rtwCAPI_SetChildMMIArray(TRACTION_CONTROL_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetChildMMIArrayLen(TRACTION_CONTROL_M->DataMapInfo.mmi, 0);
}

#else                                  // HOST_CAPI_BUILD
#ifdef __cplusplus

extern "C"
{

#endif

  void TRACTION_CONTROL_host_InitializeDataMapInfo
    (TRACTION_CONTROL_host_DataMapInfo_T *dataMap, const char *path)
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
