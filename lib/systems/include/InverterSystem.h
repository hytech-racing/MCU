#ifndef INVERTERSYSTEM
#define INVERTERSYSTEM

class InverterSystem
{
public:
    InverterSystem(unsigned long init_time)
    {
    }

// inverter commands
    void request_enable_hv();
    
    // enable driver and enable inverter at this time
    void request_enable_inverter();

    void start_inverter();
    void command_no_torque();




// inverter feedback
    bool inverter_system_ready();
    bool dc_quit_on();
    bool quit_inverter_on();
    
    

private:
    unsigned long enable_request_time_;
};

#endif /* INVERTERSYSTEM */
