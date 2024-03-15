#ifndef __SABINTERFACE_H__
#define __SABINTERFACE_H__

#include "hytech.h"
#include "FlexCAN_T4.h"
#include "AnalogSensorsInterface.h"

class SABInterface
{
private:
public:
    AnalogChannel rlLoadCell;
    AnalogChannel rrLoadCell;
    AnalogChannel pot3;
    AnalogChannel pot4;

    SABInterface(
        float rlLoadCellScale,
        float rlLoadCellOffset,
        float rrLoadCellScale,
        float rrLoadCellOffset,
        float pot3Scale,
        float pot3Offset,
        float pot4Scale,
        float pot4Offset
    )
    {
        rlLoadCell.scale = rlLoadCellScale;
        rlLoadCell.offset = rlLoadCellOffset;

        rrLoadCell.scale = rrLoadCellScale;
        rrLoadCell.offset = rrLoadCellOffset;

        pot3.scale = pot3Scale;
        pot3.offset = pot3Offset;

        pot4.scale = pot4Scale;
        pot4.offset = pot4Offset;
    };

    SABInterface(
        float rlLoadCellScale,
        float rlLoadCellOffset,
        float rrLoadCellScale,
        float rrLoadCellOffset
    ) : SABInterface (rlLoadCellScale, rlLoadCellOffset, rrLoadCellScale, rrLoadCellOffset, 1.0, 0.0, 1.0, 0.0) {};

    void retrieve_pots_and_load_cells_CAN(CAN_message_t &recvd_msg);
};

#endif /* __SABINTERFACE_H__ */
