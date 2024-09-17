#include "DrivebrainETHInterface.h"

#include <Arduino.h>
void DrivebrainETHInterface::receive_pb_msg(const hytech_msgs_MCUData& msg_in)
{
    Serial.println("msg recvd");
    _latest_data = {};
}