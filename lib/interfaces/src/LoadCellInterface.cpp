#include "LoadCellInterface.h"

void LoadCellInterface::tick(const LoadCellInterfaceTick_s &intake)
{
    // filter runs at 100hz
    loadCellConversions_.FL = intake.FLConversion;
    loadCellConversions_.FR = intake.FRConversion;
    loadCellConversions_.RL = intake.RLConversion;
    loadCellConversions_.RR = intake.RRConversion;

    loadCellForcesUnfiltered_.FL[FIRCircBufferHead] = intake.FLConversion.conversion;
    loadCellForcesUnfiltered_.FR[FIRCircBufferHead] = intake.FRConversion.conversion;
    loadCellForcesUnfiltered_.RL[FIRCircBufferHead] = intake.RLConversion.conversion;
    loadCellForcesUnfiltered_.RR[FIRCircBufferHead] = intake.RRConversion.conversion;

    loadCellForcesFiltered_.FL = 0.0f;
    loadCellForcesFiltered_.FR = 0.0f;
    loadCellForcesFiltered_.RL = 0.0f;
    loadCellForcesFiltered_.RR = 0.0f;

    for (int FIROffset = 0; FIROffset < numFIRTaps_; FIROffset++)
    {
        int index = (FIRCircBufferHead + FIROffset) % numFIRTaps_;
        loadCellForcesFiltered_.FL += loadCellForcesUnfiltered_.FL[index] * FIRTaps_[FIROffset];
        loadCellForcesFiltered_.FR += loadCellForcesUnfiltered_.FR[index] * FIRTaps_[FIROffset];
        loadCellForcesFiltered_.RL += loadCellForcesUnfiltered_.RL[index] * FIRTaps_[FIROffset];
        loadCellForcesFiltered_.RR += loadCellForcesUnfiltered_.RR[index] * FIRTaps_[FIROffset];
    }

    FIRCircBufferHead = (FIRCircBufferHead + 1) % numFIRTaps_;
    if (FIRCircBufferHead == numFIRTaps_ - 1)
        FIRSaturated_ = true;
}

LoadCellInterfaceOutput_s LoadCellInterface::getLoadCellForces()
{
    return (LoadCellInterfaceOutput_s){
        .loadCellForcesFiltered = loadCellForcesFiltered_,
        .loadCellConversions = loadCellConversions_,
        .FIRSaturated = FIRSaturated_};
}

// this is a hack, i know, i just want all the data.
void LoadCellInterface::update_raw_data(const LoadCellInterfaceTick_s &intake)
{
    _raw_data.raw_load_cell_data = {intake.FLConversion.raw, intake.FRConversion.raw, intake.RLConversion.raw, intake.RRConversion.raw};
}