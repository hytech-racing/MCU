#ifndef MESSAGEHANDLER
#define MESSAGEHANDLER
#include "Logger.h"
template <typename interfaceType, typename msgType>
class MessageHandler
{
public:
    /// @brief msg sender class templated to allow for multiple interface types and msg types. simply handles sending of msgs at a rate.
    /// @param interface the pointer to the interface in which will be used to send the data.
    /// @param msg_to_send pointer to the message instance in which will be sent
    /// @param period_to_send_ms period in which the data message will be sent
    MessageHandler(interfaceType *interface, msgType *msg_to_send, int period_to_send_ms, unsigned long init_time)
    {
        period_ = period_to_send_ms;
        prev_send_time_ = init_time;
        msg_ = msg_to_send;
        interface_ = interface;
    }
    /// @brief determines if the period has passed and when it has it de-referrences the message pointer and sends it using the interface.
    // https://vorbrodt.blog/2021/06/23/templates-linking-and-everything-in-between/
    void handle_sending(unsigned long curr_time)
    {
        if ((curr_time - prev_send_time_) > prev_send_time_)
        {
            if (interface_ != nullptr && msg_ != nullptr)
            {
                interface_->write(*msg_);

                prev_send_time_ = curr_time;
            }
            else
            {
                hal_println("ERROR: interface or msg is nullptr, not sending");
            }
        }
    }

private:
    int period_;
    unsigned long prev_send_time_;
    interfaceType *interface_;
    msgType *msg_;
};

#endif