#include "SABInterface.h"

void SABInterface::retrieve_pots_and_load_cells_CAN(CAN_message_t &recvd_msg)
{
    SAB_CB_t sab_data;
    Unpack_SAB_CB_hytech(&sab_data, recvd_msg.buf, recvd_msg.len);

    rlLoadCell.lastSample = sab_data.RL_load_cell;
    rrLoadCell.lastSample = sab_data.RR_load_cell;
    pot3.lastSample = sab_data.pot3;
    pot4.lastSample = sab_data.pot4;

    rlLoadCell.convert();
    rrLoadCell.convert();
    pot3.convert();
    pot4.convert();
}