#ifndef RTW_HEADER_NORMAL_FORCE_TV_cap_host_h__
#define RTW_HEADER_NORMAL_FORCE_TV_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

struct NORMAL_FORCE_TV_host_DataMapInfo_T {
  rtwCAPI_ModelMappingInfo mmi;
};

#ifdef __cplusplus

extern "C"
{

#endif

  void NORMAL_FORCE_TV_host_InitializeDataMapInfo
    (NORMAL_FORCE_TV_host_DataMapInfo_T *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 // HOST_CAPI_BUILD
#endif                               // RTW_HEADER_NORMAL_FORCE_TV_cap_host_h__

// EOF: NORMAL_FORCE_TV_capi_host.h
