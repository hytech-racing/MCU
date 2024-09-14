#include "VectornavInterface.h"


// constructor method implementation to do // Implementation of message reception
// Process the received CAN message here
template<typename message_queue>
void VNInterface<message_queue>::retrieve_velocity_CAN(CAN_message_t &recvd_msg) {
    VN_VEL_t vel_data;
    Unpack_VN_VEL_hytech(&vel_data, recvd_msg.buf, recvd_msg.len);
    vn_data.velocity_x = HYTECH_vn_body_vel_x_ro_fromS(vel_data.vn_body_vel_x_ro); // Correct access to vn_data within the class scope
    vn_data.velocity_y = HYTECH_vn_body_vel_y_ro_fromS(vel_data.vn_body_vel_y_ro);
    vn_data.velocity_z = HYTECH_vn_body_vel_z_ro_fromS(vel_data.vn_body_vel_z_ro);
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_linear_accel_CAN(CAN_message_t &recvd_msg) {
    VN_LINEAR_ACCEL_t linear_accel_data;
    Unpack_VN_LINEAR_ACCEL_hytech(&linear_accel_data, recvd_msg.buf, recvd_msg.len);
    vn_data.linear_accel_x = HYTECH_vn_lin_ins_accel_x_ro_fromS(linear_accel_data.vn_lin_ins_accel_x_ro);
    vn_data.linear_accel_y = HYTECH_vn_lin_ins_accel_y_ro_fromS(linear_accel_data.vn_lin_ins_accel_y_ro);
    vn_data.linear_accel_z = HYTECH_vn_lin_ins_accel_z_ro_fromS(linear_accel_data.vn_lin_ins_accel_z_ro);
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_uncompLinear_accel_CAN(CAN_message_t &recvd_msg) {
    VN_LINEAR_ACCEL_UNCOMP_t linear_accel_uncomp_data;
    Unpack_VN_LINEAR_ACCEL_UNCOMP_hytech(&linear_accel_uncomp_data, recvd_msg.buf, recvd_msg.len);

    vn_data.uncompLinear_accel[0] = HYTECH_vn_lin_uncomp_accel_x_ro_fromS(linear_accel_uncomp_data.vn_lin_uncomp_accel_x_ro);
    vn_data.uncompLinear_accel[1] = HYTECH_vn_lin_uncomp_accel_y_ro_fromS(linear_accel_uncomp_data.vn_lin_uncomp_accel_y_ro);
    vn_data.uncompLinear_accel[2] = HYTECH_vn_lin_uncomp_accel_z_ro_fromS(linear_accel_uncomp_data.vn_lin_uncomp_accel_z_ro);
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_ypr_CAN(CAN_message_t &recvd_msg) {
    VN_YPR_t ypr_data;
    Unpack_VN_YPR_hytech(&ypr_data, recvd_msg.buf, recvd_msg.len);
    vn_data.yaw = HYTECH_vn_yaw_ro_fromS(ypr_data.vn_yaw_ro);
    vn_data.roll = HYTECH_vn_roll_ro_fromS(ypr_data.vn_roll_ro);
    vn_data.pitch = HYTECH_vn_pitch_ro_fromS(ypr_data.vn_pitch_ro);
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_lat_lon_CAN(CAN_message_t &recvd_msg) {
    VN_LAT_LON_t lat_lon_data;
    Unpack_VN_LAT_LON_hytech(&lat_lon_data, recvd_msg.buf, recvd_msg.len);
    vn_data.latitude = HYTECH_vn_gps_lat_ro_fromS(lat_lon_data.vn_gps_lat_ro);
    vn_data.longitude = HYTECH_vn_gps_lon_ro_fromS(lat_lon_data.vn_gps_lon_ro);
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_gps_time_CAN(CAN_message_t &recvd_msg) {
    VN_GPS_TIME_MSG_t gps_time_data;
    Unpack_VN_GPS_TIME_MSG_hytech(&gps_time_data, recvd_msg.buf, recvd_msg.len);
    vn_data.gps_time = gps_time_data.vn_gps_time;
}

template<typename message_queue>
void VNInterface<message_queue>::retrieve_vn_status_CAN(CAN_message_t &recvd_msg) {
    VN_STATUS_t status_data;
    Unpack_VN_STATUS_hytech(&status_data, recvd_msg.buf, recvd_msg.len);
    vn_data.vn_status = status_data.vn_gps_status;
}

template <typename message_queue>
void VNInterface<message_queue>::retrieve_vn_ecef_pos_xy_CAN(CAN_message_t &recvd_msg) {
    VN_ECEF_POS_XY_t ecef_xy;
    Unpack_VN_ECEF_POS_XY_hytech(&ecef_xy, recvd_msg.buf, recvd_msg.len);
    vn_data.ecef_coords[0] = HYTECH_vn_ecef_pos_x_ro_fromS(ecef_xy.vn_ecef_pos_x_ro);
    vn_data.ecef_coords[1] = HYTECH_vn_ecef_pos_y_ro_fromS(ecef_xy.vn_ecef_pos_y_ro);
}

template <typename message_queue>
void VNInterface<message_queue>::retrieve_vn_ecef_pos_z_CAN(CAN_message_t &recvd_msg) {
    VN_ECEF_POS_Z_MSG_t ecef_z;
    Unpack_VN_ECEF_POS_Z_MSG_hytech(&ecef_z, recvd_msg.buf, recvd_msg.len);
    vn_data.ecef_coords[2] = HYTECH_vn_ecef_pos_z_msg_ro_fromS(ecef_z.vn_ecef_pos_z_ro);
}

template <typename message_queue>
void VNInterface<message_queue>::receive_ang_rates_CAN(CAN_message_t & recvd_msg)
{
    VN_ANGULAR_RATE_t ang_rates;
    Unpack_VN_ANGULAR_RATE_hytech(&ang_rates,  recvd_msg.buf, recvd_msg.len);
    vn_data.angular_rates.x = HYTECH_angular_rate_x_ro_fromS(ang_rates.angular_rate_x_ro);
    vn_data.angular_rates.y = HYTECH_angular_rate_y_ro_fromS(ang_rates.angular_rate_y_ro);
    vn_data.angular_rates.z = HYTECH_angular_rate_z_ro_fromS(ang_rates.angular_rate_z_ro);
}
/**
 * @brief 
 * getter method for returning vn_data structure
 * @tparam message_queue 
 * @return vectornav 
 */
template<typename message_queue>
vectornav VNInterface<message_queue>::get_vn_struct() {
    return vn_data; 
}
