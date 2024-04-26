#ifndef RTW_HEADER_NOREGEN_5KPH_cap_host_h__
#define RTW_HEADER_NOREGEN_5KPH_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

struct NOREGEN_5KPH_host_DataMapInfo_T {
  rtwCAPI_ModelMappingInfo mmi;
};

#ifdef __cplusplus

extern "C"
{

#endif

  void NOREGEN_5KPH_host_InitializeDataMapInfo(NOREGEN_5KPH_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 // HOST_CAPI_BUILD
#endif                                 // RTW_HEADER_NOREGEN_5KPH_cap_host_h__

// EOF: NOREGEN_5KPH_capi_host.h
