#ifndef VECTORNAVINTERFACE
#define VECTORNAVINTERFACE
#include "FlexCAN_T4.h"
#include "hytech.h"

// struct vectornav {
//         float velocity_x;
//         float velocity_y; 
//         float velocity_z; 
//         float linear_accel_x;
//         float linear_accel_y;
//         float linear_accel_z;
//         float uncompLinear_accel[3]; // 3D uncompensated linear acceleration
//         float yaw;
//         float pitch;
//         float roll;
//         double latitude;
//         double longitude;
//         double ecef_coords[3]; // x,y,z
//         uint64_t gps_time; // gps time
//         uint8_t vn_status; // status
//         xyz_vec<float> angular_rates; 
//     };

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
    

    // retrieve methods
    void retrieve_velocity_CAN(CAN_message_t &recvd_msg);
    
    void retrieve_linear_accel_CAN(CAN_message_t &recvd_msg);
    void retrieve_uncompLinear_accel_CAN(CAN_message_t &recvd_msg);
    void retrieve_ypr_CAN(CAN_message_t &recvd_msg);
    void retrieve_lat_lon_CAN(CAN_message_t &recvd_msg);
    void retrieve_gps_time_CAN(CAN_message_t &recvd_msg);
    void retrieve_vn_status_CAN(CAN_message_t &recvd_msg);
    void retrieve_vn_ecef_pos_xy_CAN(CAN_message_t &recvd_msg);
    void retrieve_vn_ecef_pos_z_CAN(CAN_message_t &recvd_msg);
    void receive_ang_rates_CAN(CAN_message_t &recvd_msg);
    // getters
    vectornav get_vn_struct();
    
    uint32_t get_id() { return can_id_;};
};
#include "VectornavInterface.tpp"
#endif /* __WATCHDOG_INTERFACE_H__ */
