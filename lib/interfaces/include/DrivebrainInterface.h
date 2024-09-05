#ifndef __DRIVEBRAININTERFACE_H__
#define __DRIVEBRAININTERFACE_H__
#include "DrivebrainData.h"
#include "MessageQueueDefine.h"

class DrivebrainInterface
{
    public:
        DrivebrainInterface(CANBufferType * msg_output_queue)
        {
            _msg_queue = msg_output_queue;
            _current_drivebrain_data.last_speed_setpoint_receive_time_millis= -1;
            _current_drivebrain_data.last_torque_lim_receive_time_millis= -1;
            _current_drivebrain_data.speed_setpoints_rpm = {};
            _current_drivebrain_data.torque_limits_nm = {};
        }

        void receive_db_torque_lim_message(CAN_message_t &msg, unsigned long curr_millis);
        void receive_db_speed_setpoint_message(CAN_message_t& msg, unsigned long curr_millis);
        
        DrivebrainData get_latest_db_data() {return _current_drivebrain_data; }
        
    private:

        DrivebrainData _current_drivebrain_data;
        CANBufferType * _msg_queue;

};

#endif // __DRIVEBRAININTERFACE_H__