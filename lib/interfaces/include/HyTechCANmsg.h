#ifndef HYTECHCANMSG
#define HYTECHCANMSG

template<typename msg_type>
struct ht_can_msg
{
    uint32_t id;
    msg_type msg_class;
    size_t size;
};

#endif /* HYTECHCANMSG */
