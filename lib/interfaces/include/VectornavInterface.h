#ifndef VECTORNAVINTERFACE
#define VECTORNAVINTERFACE

/* Library */
#include "FlexCAN_T4.h"
#include "hytech.h"

/**
 * Struct that holds gps, velocity/accel, and gyro data
 */
struct vector_nav {
        float velocity_x;
        float velocity_y; 
        float velocity_z; 
        float linear_accel_x;
        float linear_accel_y;
        float linear_accel_z;
        float uncompLinear_accel[3]; // 3D uncompensated linear acceleration
        float yaw;
        float pitch;
        float roll;
        double latitude;
        double longitude;
        double ecef_coords[3]; // x,y,z
        uint64_t gps_time; // gps time
        uint8_t vn_status; // Vectornav status
        xyz_vec<float> angular_rates; //TODO WHAT IS THIS
    };


/**
 * Generic data type for CAN message queue
 */
template <typename message_queue>

/**
 * Interface for the VectorNAV. The VectorNAV is our GPS/IMU and it gives
 * extremely precise position and orientation data for the car.
 */
class VNInterface
{
private:
    /**
     * Circular buffer for CAN message queue. 
     */
    message_queue *msg_queue_;

    /**
     * CAN ID
     * Value is accessible with a getter but doesn't seem to be used
     */
    uint32_t can_id_;

    /**
     * Instance of vector_nav struct that holds data parsed from CAN message
     */
    vector_nav vn_data;
    
public:
    /**
     * Constructor that sets msg_queue_ buffer to pointer to actual CAN output 
     */
    VNInterface(message_queue *msg_output_queue) {
        msg_queue_ = msg_output_queue;
    };

    /** 
     * Functions to process received CAN message
     * Updates appropriate vn_data fields with data unpacked and converted according to formulas in hytech.h
     */

    /**
     * Updates velocity x, y, and z values. 
     */
    void retrieve_velocity_CAN(CAN_message_t &recvd_msg);
    
    /**
     * Updates linear_accel x, y and z values.
     */
    void retrieve_linear_accel_CAN(CAN_message_t &recvd_msg);

    /**
     * Updates values for 3D uncompensated linear acceleration
     * Stored in an array rather than individual x, y, z values
     */
    void retrieve_uncompLinear_accel_CAN(CAN_message_t &recvd_msg);
    
    /**
     * Updates yaw, pitch, and roll values
     */
    void retrieve_ypr_CAN(CAN_message_t &recvd_msg);

    /**
     * Updates lattitude and longitude values
     */
    void retrieve_lat_lon_CAN(CAN_message_t &recvd_msg);

    /**
     * Updates time value (units?) from GPS
     */
    void retrieve_gps_time_CAN(CAN_message_t &recvd_msg);

    /**
     * Updates vn_status
     * TODO - what type of values are these
     */
    void retrieve_vn_status_CAN(CAN_message_t &recvd_msg);

    /**
     * Updates position x/y coordinates
     * ECEF = Earth-centered Earth-fixed coordinates
     */
    void retrieve_vn_ecef_pos_xy_CAN(CAN_message_t &recvd_msg);

    /**
     * Updates position z coordinate
     * ECEF = Earth-centered Earth-fixed coordinates
     * Stored in same array as x/y
     */
    void retrieve_vn_ecef_pos_z_CAN(CAN_message_t &recvd_msg);

    /**
     * Updates x, y, and z angular velocity rate 
     */
    void receive_ang_rates_CAN(CAN_message_t &recvd_msg);

    /**
     * Getter for vn_data struct
     */
    vector_nav get_vn_struct();
    
    /**
     * Getter for CAN ID
     * Not actually used atm?
     */
    uint32_t get_id() { return can_id_;};
};
#include "VectornavInterface.tpp"
#endif /* __VECTORNAV_INTERFACE_H__ */
