#ifndef PARAMMSGINTERFACE
#define PARAMMSGINTERFACE
#include "ht_msgs.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include <pb_common.h>

// needs to hold all of the parameter update messages (technically we can receive multiple in one loop tick)

/// @brief
/// @tparam message_queue
template <typename message_queue>
class EthMsgInterface
{

public:
    EthMsgInterface(){};

    void receive_union_msg(pb_istream_t *stream)
    {
        ht_eth_big_union msg = ht_eth_big_union_init_zero;
        if(pb_decode(stream, ht_eth_big_union_fields, &msg))
        {
            
        }
        else {
            return 1;
        }

    }

private:

    void receive_config_msg_(const ht_eth_config &config_msg);
    void 
    // TODO this will get used later when we want to get all of the parameter values?
    // message_queue *msg_out_queue_;
    message_queue *msg_in_queue_;
};

#endif