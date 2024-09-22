#ifndef __LOADCELLINTERFACE_H__
#define __LOADCELLINTERFACE_H__

/* System Includes */
#include "Utility.h"

/* Library Includes */
#include "SysClock.h"

/* Interface */
#include "AnalogSensorsInterface.h"



/**
 * Struct holding conversions for each wheel's load cell data. 
 * AnalogConversion_s struct holds raw and converted values and whether the result was clamped.
 * Load cell data is converted from raw -> lbs 
 */
struct LoadCellInterfaceTick_s
{
    const AnalogConversion_s &FLConversion;
    const AnalogConversion_s &FRConversion;
    const AnalogConversion_s &RLConversion;
    const AnalogConversion_s &RRConversion;
};

/**
 * A struct that the LoadCellInterface will output, including the forces themselves, the analog conversions,
 * a boolean representing whether or not the FIR filter is saturated.
 */
struct LoadCellInterfaceOutput_s
{
    veh_vec<float> loadCellForcesFiltered;
    veh_vec<AnalogConversion_s> loadCellConversions;
    bool FIRSaturated;
};


/**
 * The LoadCellInterface filters load cell signals to be used in the TorqueControllers system.
 * Applies FIR filter and determines if signal is saturated
 */
class LoadCellInterface
{
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

    /**
     * Index of the latest sample in the raw buffer. Since this is a circular buffer, this indicates
     * the last index where a new value was written.
     */
    int FIRCircBufferHead = 0;

    /**
     * A "vehicle vector" containing all of the newest load cell analog conversions.
     */
    veh_vec<AnalogConversion_s> loadCellConversions_;

    /**
     * A "vehicle vector" containing the last five load cell readings on each wheel.
     */
    veh_vec<float[numFIRTaps_]> loadCellForcesUnfiltered_;

    /**
     * The filtered output of the FIR filter.
     */
    veh_vec<float> loadCellForcesFiltered_;

    /**
     * Flag containing whether or not the FIR filter is saturated.
     */
    bool FIRSaturated_ = false;



public:

    /**
     * Generic constructor to create a new LoadCellInterface.
     */
    LoadCellInterface() {}

    /**
     * Exteral tick() function to pass in a new LoadCellInterfaceTick struct into the LoadCellInterface.
     * When this tick() function completes, the loadCellConversions_, loadCellForcesUnfiltered_,
     * loadCellForcesFiltered_, and FIRSaturated_ fields will be updated.
     */
    void tick(const LoadCellInterfaceTick_s &intake);

    /**
     * Returns a new LoadCellinterfaceOutput struct that contains the current state of this LoadCellInterface.
     */
    LoadCellInterfaceOutput_s getLoadCellForces();

};

#endif