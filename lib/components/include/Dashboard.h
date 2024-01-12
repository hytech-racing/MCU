
// The driver interface is used/returned by the driver
struct DashDriverInterface {
    int dial_position;
    bool start_button;
    bool buzzer;
    //RENAME THIS (We think it means safety system (IMD?))
    bool SSOK;
    //corresponds to BRB or inertia (idk)
    bool shutdown;
    struct buttons {
        // part of dashboard states
        bool start;
        //just buttons
        bool mark;
        bool mode;
        bool mc_cycle; // clears encoder error codes
        bool launch_control;
        bool torque_mode;
        bool led_dimmer;
    } button;
};

enum DialMode {MODE_1, MODE_2, ACCEL_LAUNCH_CONTROL, SKIDPAD, AUTOCROSS, ENDURANCE};

struct DashComponentInterface {
    //enum for dial position read by controller mux
    DialMode dial_mode;
};
class DashComponent {
    public:
        DashComponent(){
            
        };
        DashComponentInterface evaluate_dashboard(
                const DashDriverInterface& data);
        bool start_button_pressed();
    private:
        

        
        
};