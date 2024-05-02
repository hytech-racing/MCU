#include <Arduino.h>


#include "ProtobufMsgInterface.h"
#include "MCU_rev15_defs.h"

EthernetUDP protobuf_send_socket;
EthernetUDP protobuf_recv_socket;
CAR_STATE state = CAR_STATE::STARTUP;
ParameterInterface params(state);
ETHInterfaces ethernet_interfaces = {&params};

void init_ethernet_device()
{
    Ethernet.begin(EthParams::default_MCU_MAC_address, EthParams::default_MCU_ip);
    protobuf_send_socket.begin(EthParams::default_protobuf_send_port);
    protobuf_recv_socket.begin(EthParams::default_protobuf_recv_port);
}

void test_ethernet()
{
    
        handle_ethernet_socket_receive(&protobuf_recv_socket, &recv_pb_stream_union_msg, ethernet_interfaces);
        if(params.params_need_sending())
        {
            
            auto config = params.get_config();
            if(!handle_ethernet_socket_send_pb(&protobuf_send_socket, config, config_fields)){
            }
            params.reset_params_need_sending();
        }
    
}

void setup()
{
    init_ethernet_device();
}

void loop()
{
    test_ethernet();
    // Serial.println("loopin");
}