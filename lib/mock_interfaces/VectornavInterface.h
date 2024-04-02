#ifndef VECTORNAVINTERFACE
#define VECTORNAVINTERFACE

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
        uint64_t gps_time; // gps time
        uint8_t vn_status; // status
    };

template <typename message_queue>
class VNInterface
{
private:
    /* Watchdog last kicked time */
    message_queue *msg_queue_;
    uint32_t can_id_;
    vector_nav vn_data;
    
public:
    VNInterface(message_queue *msg_output_queue) {
        msg_queue_ = msg_output_queue;
    };
    /* Kick watchdog */
    
    // getters
    vector_nav get_vn_struct();
    
    uint32_t get_id() { return can_id_;};
};
#endif /* __WATCHDOG_INTERFACE_H__ */
