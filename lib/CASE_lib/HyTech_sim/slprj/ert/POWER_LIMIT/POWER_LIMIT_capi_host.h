#ifndef RTW_HEADER_POWER_LIMIT_cap_host_h__
#define RTW_HEADER_POWER_LIMIT_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

struct POWER_LIMIT_host_DataMapInfo_T {
  rtwCAPI_ModelMappingInfo mmi;
};

#ifdef __cplusplus

extern "C"
{

#endif

  void POWER_LIMIT_host_InitializeDataMapInfo(POWER_LIMIT_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 // HOST_CAPI_BUILD
#endif                                 // RTW_HEADER_POWER_LIMIT_cap_host_h__

// EOF: POWER_LIMIT_capi_host.h
