#include "SABInterface.h"

void SABInterface::retrieve_pots_and_load_cells_CAN(CAN_message_t &recvd_msg)
{
    SAB_SUSPENSION_t sab_data;
    Unpack_SAB_SUSPENSION_hytech(&sab_data, recvd_msg.buf, recvd_msg.len);

    rlLoadCell.lastSample = sab_data.load_cell_rl;
    rrLoadCell.lastSample = sab_data.load_cell_rr;
    pot3.lastSample = sab_data.potentiometer_rl;
    pot4.lastSample = sab_data.potentiometer_rr;

    rlLoadCell.convert();
    rrLoadCell.convert();
    pot3.convert();
    pot4.convert();
}