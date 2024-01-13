#ifndef BUZZER
#define BUZZER

class BuzzerController

{
public:
    BuzzerController(int duration_of_activation_ms) {
        buzzer_period_ = duration_of_activation_ms;
    }

    void activate_buzzer(unsigned long act_time);

    bool done(unsigned long curr_time);
    bool buzzer_is_on() { return buzzer_on_; }

private:
    int buzzer_period_;
    unsigned long last_activation_time_;
    bool buzzer_on_;
};

#endif /* BUZZER */
