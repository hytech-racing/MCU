#ifndef __SABINTERFACE_H__
#define __SABINTERFACE_H__

/* Library */
#include "hytech.h"
#include "FlexCAN_T4.h"

/* Interface */
#include "AnalogSensorsInterface.h"

/**
 * The SAB Interface receieves CAN messages containing load cell and potentionmeter readings.
 * Through this interface values are parsed, updated, and converted to real units.
 */
class SABInterface
{
private:
public:
    /* Rear load cell output */
    AnalogChannel rlLoadCell;
    AnalogChannel rrLoadCell;

    /* Rear potentiometer output */
    AnalogChannel pot3;
    AnalogChannel pot4;

    /**
     * Constructor that defines conversion for both load cells and potentionmeter data
     * Defined offset and scale values from MCU_rev15_defs are used to convert from raw data to correct units (pounds)
     */
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

     /**
     * Overloaded constructor with default values for potentiometer data. 
     * Sets pot scale to 1.0 and offset to 0.0 so value stays same as last sample. 
     */
    SABInterface(
        float rlLoadCellScale,
        float rlLoadCellOffset,
        float rrLoadCellScale,
        float rrLoadCellOffset
    ) : SABInterface (rlLoadCellScale, rlLoadCellOffset, rrLoadCellScale, rrLoadCellOffset, 1.0, 0.0, 1.0, 0.0) {};


    /**
     * Parses CAN message into individual values for rear load cell and potentiometer readings.
     * Updates each sensor's lastSample value and converts data (rlLoadCell and rrLoadCell converted to pounds)
     */
    void retrieve_pots_and_load_cells_CAN(CAN_message_t &recvd_msg);
};

#endif /* __SABINTERFACE_H__ */
