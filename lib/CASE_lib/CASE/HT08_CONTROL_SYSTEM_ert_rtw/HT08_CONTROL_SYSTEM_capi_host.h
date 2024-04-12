#ifndef RTW_HEADER_HT08_CONTROL_SYSTEM_cap_host_h__
#define RTW_HEADER_HT08_CONTROL_SYSTEM_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"
#include "LAUNCH_CONTROL_capi_host.h"
#include "POWER_LIMIT_capi_host.h"
#include "BasicVehicleMath_capi_host.h"
#include "NORMAL_FORCE_TV_capi_host.h"
#include "PID_TV_capi_host.h"

struct HT08_CONTROL_SYSTEM_host_DataMapInfo_T {
  rtwCAPI_ModelMappingInfo mmi;
  rtwCAPI_ModelMappingInfo *childMMI[5];
  LAUNCH_CONTROL_host_DataMapInfo_T child0;
  POWER_LIMIT_host_DataMapInfo_T child1;
  BasicVehicleMath_host_DataMapInfo_T child2;
  NORMAL_FORCE_TV_host_DataMapInfo_T child3;
  PID_TV_host_DataMapInfo_T child4;
};

#ifdef __cplusplus

extern "C"
{

#endif

  void HT08_CONTROL_SYSTEM_host_InitializeDataMapInfo
    (HT08_CONTROL_SYSTEM_host_DataMapInfo_T *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 // HOST_CAPI_BUILD
#endif                           // RTW_HEADER_HT08_CONTROL_SYSTEM_cap_host_h__

// EOF: HT08_CONTROL_SYSTEM_capi_host.h
