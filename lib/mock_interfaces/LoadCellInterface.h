#ifndef __LOADCELLINTERFACE_H__
#define __LOADCELLINTERFACE_H__

/* System Includes */
#include "Utility.h"

/* Library Includes */
#include "SysClock.h"
#include "AnalogSensorsInterface.h"



/* Structs */
struct LoadCellInterfaceTick_s
{
    const AnalogConversion_s &FLConversion;
    const AnalogConversion_s &FRConversion;
    const AnalogConversion_s &RLConversion;
    const AnalogConversion_s &RRConversion;
};

struct LoadCellInterfaceOutput_s
{
    veh_vec<float> loadCellForcesFiltered;
    veh_vec<AnalogConversion_s> loadCellConversions;
    bool FIRSaturated;
};

/**
 * Mock interface for testing purposes. Please see the real LoadCellInterface for proper documentation.
*/
class LoadCellInterface
{
private:
    const static int numFIRTaps_ = 5;
    float FIRTaps_[numFIRTaps_] = 
    {
        0.07022690881526232,
        0.27638313122745306,
        0.408090001549378,
        0.27638313122745306,
        0.07022690881526232
    };

    int FIRCircBufferHead = 0;
    veh_vec<AnalogConversion_s> loadCellConversions_;
    veh_vec<float[numFIRTaps_]> loadCellForcesUnfiltered_;
    veh_vec<float> loadCellForcesFiltered_;
    bool FIRSaturated_ = false;



public:
    LoadCellInterface() {}
    void tick(const LoadCellInterfaceTick_s &intake);
    LoadCellInterfaceOutput_s getLoadCellForces();

};

#endif