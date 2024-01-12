#ifndef INVERTER
#define INVERTER

class InverterComponent{
    public:
        InverterComponent(unsigned long init_time){

        }
        void request_enable_inverter(unsigned long cur_time_ms);
        void start_inverter(unsigned long cur_time_ms);

    private:
        unsigned long enable_request_time_;
        

};




#endif /* INVERTER */
