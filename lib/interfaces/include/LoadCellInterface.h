#ifndef __LOADCELLINTERFACE_H__
#define __LOADCELLINTERFACE_H__

#include "Utility.h"
#include "SysClock.h"
#include "AnalogSensorsInterface.h"
#include "SharedDataTypes.h"

/* Structs */

struct LoadCellInterfaceTick_s
{
    const AnalogConversion_s &FLConversion;
    const AnalogConversion_s &FRConversion;
    const AnalogConversion_s &RLConversion;
    const AnalogConversion_s &RRConversion;
};


class LoadCellInterface
{
public:
    LoadCellInterface() {
        loadCellConversions_ = veh_vec<AnalogConversion_s>();
        loadCellForcesUnfiltered_ = veh_vec<float[numFIRTaps_]>();
        loadCellForcesFiltered_ = veh_vec<float>();
    }
    void tick(const LoadCellInterfaceTick_s &intake);
    LoadCellInterfaceOutput_s getLoadCellForces();
private:
    /*
    FIR filter designed with
    http://t-filter.appspot.com

    sampling frequency: 100 Hz

    * 0 Hz - 10 Hz
    gain = 1
    desired ripple = 5 dB
    actual ripple = 1.7659949026015025 dB

    * 40 Hz - 50 Hz
    gain = 0
    desired attenuation = -40 dB
    actual attenuation = -47.34009380570117 dB
    */
   const static int numFIRTaps_ = 5;
    float FIRTaps_[numFIRTaps_] = 
    {
        0.07022690881526232,
        0.27638313122745306,
        0.408090001549378,
        0.27638313122745306,
        0.07022690881526232
    };
    int FIRCircBufferHead = 0; // index of the latest sample in the raw buffer
    veh_vec<AnalogConversion_s> loadCellConversions_;
    veh_vec<float[numFIRTaps_]> loadCellForcesUnfiltered_;
    veh_vec<float> loadCellForcesFiltered_;
    bool FIRSaturated_ = false;

};

#endif