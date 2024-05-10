#ifndef __LOADCELLINTERFACE_H__
#define __LOADCELLINTERFACE_H__

#include "Utility.h"
#include "AnalogSensorsInterface.h"

/* Structs */

struct LoadCellInterfaceOutput_s
{
    veh_vec<float> loadCellForcesFiltered;
    veh_vec<AnalogConversion_s> loadCellConversions;
    bool FIRSaturated;
};

#endif