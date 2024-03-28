#ifndef VECTORNAVINTERFACE
#define VECTORNAVINTERFACE

#include "FlexCAN_T4.h"

template <typename message_queue>
class VNInterface
{
private:
    /* Watchdog last kicked time */
    
    
public:
    VNInterface(message_queue *msg_output_queue, uint32_t can_id) {};

    void receive_msg(CAN_message_t &msg);
    /* Kick watchdog */
    

    
    float get_yaw_rate();
    float get_vx_b();

};

#endif /* __WATCHDOG_INTERFACE_H__ */
