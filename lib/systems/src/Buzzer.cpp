#include "Buzzer.h"
#include "Logger.h"
void BuzzerController::activate_buzzer(unsigned long act_time)
{
    last_activation_time_ = act_time;
    buzzer_on_ = true;
}

bool BuzzerController::done(unsigned long curr_time){

    buzzer_on_ = ((curr_time - last_activation_time_) > buzzer_period_);
    return buzzer_on_;
    
}