#ifndef PARAMMSGINTERFACE
#define PARAMMSGINTERFACE
#include "ht_msgs.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

// needs to hold all of the parameter update messages (technically we can receive multiple in one loop tick)

/// @brief 
/// @tparam message_queue 
template <typename message_queue>
class ParamMsgInterface
{

public:
    ParamMsgInterface(){};

    void receive_config_msg(ht_eth_config & config_msg);

private:
    // TODO this will get used later when we want to get all of the parameter values?
    // message_queue *msg_out_queue_;
    message_queue *msg_in_queue_;
};

#endif