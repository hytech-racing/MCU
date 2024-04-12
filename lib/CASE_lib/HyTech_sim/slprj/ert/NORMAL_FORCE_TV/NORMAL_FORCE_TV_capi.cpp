//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: NORMAL_FORCE_TV_capi.cpp
//
// Code generated for Simulink model 'NORMAL_FORCE_TV'.
//
// Model version                  : 1.20
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Apr 11 22:49:21 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "NORMAL_FORCE_TV_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  // HOST_CAPI_BUILD
#include "builtin_typeid_types.h"
#include "NORMAL_FORCE_TV.h"
#include "NORMAL_FORCE_TV_capi.h"
#include "NORMAL_FORCE_TV_private.h"
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

// Data Type Map - use dataTypeMapIndex to access this structure
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[]{
  // cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
  //  isComplex, isPointer, enumStorageType
  {
    "", "", 0, 0, 0, 0, 0, 0, 0
  }
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
  {
    rtwCAPI_SCALAR, 0, 0, 0
  }
};

// Dimension Array- use dimArrayIndex to access elements of this array
static uint_T rtDimensionArray[]{ 0 };

// Fixed Point Map
static rtwCAPI_FixPtMap rtFixPtMap[]{
  // fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned
  { (nullptr), (nullptr), rtwCAPI_FIX_RESERVED, 0, 0, (boolean_T)0 },
};

// Sample Time Map - use sTimeIndex to access elements of ths structure
static rtwCAPI_SampleTimeMap rtSampleTimeMap[]{
  // samplePeriodPtr, sampleOffsetPtr, tid, samplingMode
  {
    (nullptr), (nullptr), 0, 0
  }
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

  { rtBlockSignals, 0,
    (nullptr), 0,
    (nullptr), 0 },

  { rtBlockParameters, 0,
    rtModelParameters, 0 },

  { (nullptr), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 936193240U,
    3622517184U,
    1158259804U,
    1573811821U },
  (nullptr), 0,
  (boolean_T)0
};

// Function to get C API Model Mapping Static Info
const rtwCAPI_ModelMappingStaticInfo*
  NORMAL_FORCE_TV_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

// Cache pointers into DataMapInfo substructure of RTModel
#ifndef HOST_CAPI_BUILD

void NORMAL_FORCE_TV_InitializeDataMapInfo(NORMAL_FORCE_TV::
  RT_MODEL_NORMAL_FORCE_TV_T *const NORMAL_FORCE_TV_M)
{
  // Set C-API version
  rtwCAPI_SetVersion(NORMAL_FORCE_TV_M->DataMapInfo.mmi, 1);

  // Cache static C-API data into the Real-time Model Data structure
  rtwCAPI_SetStaticMap(NORMAL_FORCE_TV_M->DataMapInfo.mmi, &mmiStatic);

  // Cache static C-API logging data into the Real-time Model Data structure
  rtwCAPI_SetLoggingStaticMap(NORMAL_FORCE_TV_M->DataMapInfo.mmi, (nullptr));

  // Set Instance specific path
  rtwCAPI_SetPath(NORMAL_FORCE_TV_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetFullPath(NORMAL_FORCE_TV_M->DataMapInfo.mmi, (nullptr));

  // Cache the instance C-API logging pointer
  rtwCAPI_SetInstanceLoggingInfo(NORMAL_FORCE_TV_M->DataMapInfo.mmi, (nullptr));

  // Set reference to submodels
  rtwCAPI_SetChildMMIArray(NORMAL_FORCE_TV_M->DataMapInfo.mmi, (nullptr));
  rtwCAPI_SetChildMMIArrayLen(NORMAL_FORCE_TV_M->DataMapInfo.mmi, 0);
}

#else                                  // HOST_CAPI_BUILD
#ifdef __cplusplus

extern "C"
{

#endif

  void NORMAL_FORCE_TV_host_InitializeDataMapInfo
    (NORMAL_FORCE_TV_host_DataMapInfo_T *dataMap, const char *path)
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
