#ifndef RTW_HEADER_TORQUE_BIAS_cap_host_h__
#define RTW_HEADER_TORQUE_BIAS_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

struct TORQUE_BIAS_host_DataMapInfo_T {
  rtwCAPI_ModelMappingInfo mmi;
};

#ifdef __cplusplus

extern "C"
{

#endif

  void TORQUE_BIAS_host_InitializeDataMapInfo(TORQUE_BIAS_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 // HOST_CAPI_BUILD
#endif                                 // RTW_HEADER_TORQUE_BIAS_cap_host_h__

// EOF: TORQUE_BIAS_capi_host.h
