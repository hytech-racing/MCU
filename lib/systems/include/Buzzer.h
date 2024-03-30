#ifndef BUZZER
#define BUZZER


class BuzzerController

{
public:
    BuzzerController(int duration_of_activation_ms) {
        buzzer_period_ = duration_of_activation_ms;
    }
    void deactivate();
    void activate_buzzer(unsigned long act_time);

    bool done(unsigned long curr_time, bool buzzer_on);
    bool buzzer_is_on() { 
        if(buzzer_on_){
            // Serial.println("buzzer should be on now");
        }    
        return buzzer_on_; 
    }

private:
    unsigned long buzzer_period_;
    unsigned long last_activation_time_;
    bool buzzer_on_;

    bool dash_buzzer_was_on = false;
};

#endif /* BUZZER */
