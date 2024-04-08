#include "Buzzer.h"
#include "Logger.h"
void BuzzerController::deactivate()
{
    buzzer_on_ = false;
    dash_buzzer_was_on = false;
}
void BuzzerController::activate_buzzer(unsigned long act_time)
{
    last_activation_time_ = act_time;
    buzzer_on_ = true;
}

// will return true when it is sure that the buzzer is off and has been
// sounded on the dashboard
bool BuzzerController::done(unsigned long curr_time, bool dash_buzzer_on){

    if (dash_buzzer_on) {
        dash_buzzer_was_on = true;
    }

    bool buzzer_time_up = (curr_time - last_activation_time_) >= buzzer_period_;

    //buzzer only turns off if the buzzer time is up and dash buzzer did turn on
    buzzer_on_ = !(buzzer_time_up && dash_buzzer_was_on);

    // only returns true (done) when the buzzer is finished buzzing
    return (!buzzer_on_ && !dash_buzzer_on);
    
}