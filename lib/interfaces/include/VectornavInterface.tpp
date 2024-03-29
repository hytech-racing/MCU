#include "VectornavInterface.h"


// constructor method implementation to do // Implementation of message reception
// Process the received CAN message here
template<typename message_queue>
void VNInterface<message_queue>::retrieve_velocity_CAN(CAN_message_t &recvd_msg) {
    VN_VEL_t vel_data;
    Unpack_VN_VEL_hytech(&vel_data, recvd_msg.buf, recvd_msg.len);
    vn_data.velocity = vel_data.velocity; // Correct access to vn_data within the class scope
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_linear_accel_CAN(CAN_message_t &recvd_msg) {
    VN_LINEAR_ACCEL_t linear_accel_data;
    Unpack_VN_LINEAR_ACCEL_hytech(&linear_accel_data, recvd_msg.buf, recvd_msg.len);
    vn_data.linear_accel_x = linear_accel_data.vn_lin_ins_accel_x_ro;
    vn_data.linear_accel_y = linear_accel_data.vn_lin_ins_accel_y_ro;
    vn_data.linear_accel_z = linear_accel_data.vn_lin_ins_accel_z_ro;
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_uncompLinear_accel_CAN(CAN_message_t &recvd_msg) {
    VN_LINEAR_ACCEL_UNCOMP_t linear_accel_uncomp_data;
    vn_data.uncompLinear_accel[0] = linear_accel_uncomp_data.vn_lin_uncomp_accel_x_ro;
    vn_data.uncompLinear_accel[1] = linear_accel_uncomp_data.vn_lin_uncomp_accel_y_ro;
    vn_data.uncompLinear_accel[2] = linear_accel_uncomp_data.vn_lin_uncomp_accel_z_ro;
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_ypr_CAN(CAN_message_t &recvd_msg) {
    VN_YPR_t ypr_data;
    Unpack_VN_YPR_hytech(&ypr_data, recvd_msg.buf, recvd_msg.len);
    vn_data.yaw = ypr_data.vn_yaw_ro;
    vn_data.roll = ypr_data.vn_roll_ro;
    vn_data.pitch = ypr_data.vn_pitch_ro;
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_lat_lon_CAN(CAN_message_t &recvd_msg) {
    VN_LAT_LON_t lat_lon_data;
    Unpack_VN_LAT_LON_hytech(&lat_lon_data, recvd_msg.buf, recvd_msg.len);
    vn_data.lateral = lat_lon_data.vn_gps_lat_ro;
    vn_data.longitudnal = lat_lon_data.vn_gps_lon_ro;
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_gps_time_CAN(CAN_message_t &recvd_msg) {
    VN_GPS_TIME_t gps_time_data;
    Unpack_VN_GPS_TIME_hytech(&gps_time_data, recvd_msg.buf, recvd_msg.len);
    vn_data.gps_time = gps_time_data.vn_gps_time;
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_vn_status_CAN(CAN_message_t &recvd_msg) {
    VN_STATUS_t status_data;
    Unpack_VN_STATUS_hytech(&status_data, recvd_msg.buf, recvd_msg.len);
    vn_data.vn_status = status_data.vn_gps_status;
}
