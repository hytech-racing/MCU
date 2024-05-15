#ifndef VECTORNAVINTERFACE
#define VECTORNAVINTERFACE
#include "SharedDataTypes.h"


template <typename message_queue>
class VNInterface
{
private:
    /* Watchdog last kicked time */
    message_queue *msg_queue_;
    uint32_t can_id_;
    vectornav vn_data;
    
public:
    VNInterface(message_queue *msg_output_queue) {
        msg_queue_ = msg_output_queue;
    };
    /* Kick watchdog */
    
    // getters
    vectornav get_vn_struct();
    
    uint32_t get_id() { return can_id_;};
};
#endif /* __WATCHDOG_INTERFACE_H__ */
