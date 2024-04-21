#ifndef RTW_HEADER_BasicVehicleMath_cap_host_h__
#define RTW_HEADER_BasicVehicleMath_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

struct BasicVehicleMath_host_DataMapInfo_T {
  rtwCAPI_ModelMappingInfo mmi;
};

#ifdef __cplusplus

extern "C"
{

#endif

  void BasicVehicleMath_host_InitializeDataMapInfo
    (BasicVehicleMath_host_DataMapInfo_T *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 // HOST_CAPI_BUILD
#endif                              // RTW_HEADER_BasicVehicleMath_cap_host_h__

// EOF: BasicVehicleMath_capi_host.h
