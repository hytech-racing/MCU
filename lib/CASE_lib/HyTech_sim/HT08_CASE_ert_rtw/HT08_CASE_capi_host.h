#ifndef RTW_HEADER_HT08_CASE_cap_host_h__
#define RTW_HEADER_HT08_CASE_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"
#include "NOREGEN_5KPH_capi_host.h"
#include "TORQUE_BIAS_capi_host.h"
#include "POWER_LIMIT_capi_host.h"
#include "TRACTION_CONTROL_capi_host.h"
#include "BasicVehicleMath_capi_host.h"
#include "NORMAL_FORCE_TV_capi_host.h"
#include "PID_TV_capi_host.h"

struct HT08_CASE_host_DataMapInfo_T {
  rtwCAPI_ModelMappingInfo mmi;
  rtwCAPI_ModelMappingInfo *childMMI[7];
  NOREGEN_5KPH_host_DataMapInfo_T child0;
  TORQUE_BIAS_host_DataMapInfo_T child1;
  POWER_LIMIT_host_DataMapInfo_T child2;
  TRACTION_CONTROL_host_DataMapInfo_T child3;
  BasicVehicleMath_host_DataMapInfo_T child4;
  NORMAL_FORCE_TV_host_DataMapInfo_T child5;
  PID_TV_host_DataMapInfo_T child6;
};

#ifdef __cplusplus

extern "C"
{

#endif

  void HT08_CASE_host_InitializeDataMapInfo(HT08_CASE_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 // HOST_CAPI_BUILD
#endif                                 // RTW_HEADER_HT08_CASE_cap_host_h__

// EOF: HT08_CASE_capi_host.h
