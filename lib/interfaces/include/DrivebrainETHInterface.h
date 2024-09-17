#ifndef __DRIVEBRAINETHINTERFACE_H__
#define __DRIVEBRAINETHINTERFACE_H__
#include "hytech_msgs.pb.h"
#include "DrivebrainData.h"

class DrivebrainETHInterface
{
    public:
        DrivebrainETHInterface() = default;

        void receive_pb_msg(const hytech_msgs_MCUData& msg_in);

        DrivebrainData_s get_latest_data() { return _latest_data; }

    private:

        DrivebrainData_s _latest_data = {};

};

#endif // __DRIVEBRAINETHINTERFACE_H__