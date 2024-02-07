#include "DashboardInterface.h"

void DashboardInterface::read(const CAN_message_t &can_msg)
{

    DASHBOARD_STATE_t msg;
    Unpack_DASHBOARD_STATE_hytech(&msg, can_msg.buf, NULL);

    _data.dial_mode = static_cast<DialMode_e>(msg.dial_state);
    
    _data.ssok = msg.ssok_above_threshold;
    _data.shutdown = msg.shutdown_h_above_threshold;

    _data.button.start = msg.start_button;
    _data.button.mark = msg.mark_button;
    _data.button.mode = msg.mode_button;
    _data.button.mc_cycle = msg.motor_controller_cycle_button;
    _data.button.launch_ctrl = msg.launch_ctrl_button;
    _data.button.torque_mode = msg.torque_mode_button;
    _data.button.led_dimmer = msg.led_dimmer_button;

    _data.buzzer_state = msg.drive_buzzer;

}

void DashboardInterface::write()
{   

    DASHBOARD_MCU_STATE_t msg;
    msg.drive_buzzer = _data.buzzer_cmd;

    // TODO: use logic as to not write data for LEDs that have not changed
    msg.bots_led = _data.LED[static_cast<int>(DashLED_e::BOTS_LED)];
    msg.launch_control_led = _data.LED[static_cast<int>(DashLED_e::LAUNCH_CONTROL_LED)];
    msg.mode_led = _data.LED[static_cast<int>(DashLED_e::MODE_LED)];
    msg.mechanical_brake_led = _data.LED[static_cast<int>(DashLED_e::MECH_BRAKE_LED)];
    msg.cockpit_brb_led = _data.LED[static_cast<int>(DashLED_e::COCKPIT_BRB_LED)];
    msg.inertia_status_led = _data.LED[static_cast<int>(DashLED_e::INERTIA_LED)];
    msg.start_status_led = _data.LED[static_cast<int>(DashLED_e::START_LED)];
    msg.motor_controller_error_led = _data.LED[static_cast<int>(DashLED_e::MC_ERROR_LED)];
    msg.imd_led = _data.LED[static_cast<int>(DashLED_e::IMD_LED)];
    msg.ams_led = _data.LED[static_cast<int>(DashLED_e::AMS_LED)];

    msg.glv_led = _data.LED[static_cast<int>(DashLED_e::GLV_LED)];
    msg.pack_charge_led = _data.LED[static_cast<int>(DashLED_e::CRIT_CHARGE_LED)];
    
    CAN_message_t can_msg;
    can_msg.id = Pack_DASHBOARD_MCU_STATE_hytech(&msg, can_msg.buf, &can_msg.len, NULL);
    
    // this circular buffer implementation requires that you push your data in a array buffer
    // all this does is put the msg into a uint8_t buffer and pushes it onto the queue
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg));
    msg_queue_->push_back(buf, sizeof(CAN_message_t));

}

//figure out how to set enumed led colors or send (0,255 value)
void DashboardInterface::setLED(DashLED_e led, LEDColors_e color)
{

    _data.LED[static_cast<int>(led)] = static_cast<int>(color);
}

DialMode_e DashboardInterface::getDialMode() {return _data.dial_mode;}

bool DashboardInterface::startButtonPressed() {return _data.button.start;}
bool DashboardInterface::specialButtonPressed() {return _data.button.mark;}
bool DashboardInterface::torqueButtonPressed() {return _data.button.mode;}
bool DashboardInterface::inverterResetButtonPressed() {return _data.button.mc_cycle;}
bool DashboardInterface::launchControlButtonPressed() {return _data.button.launch_ctrl;}
bool DashboardInterface::torqueLoadingButtonPressed() {return _data.button.torque_mode;}
bool DashboardInterface::nightModeButtonPressed() {return _data.button.led_dimmer;}

bool DashboardInterface::safetySystemOK() {return _data.ssok;}
bool DashboardInterface::shutdownHAboveThreshold() {return _data.shutdown;}

void DashboardInterface::soundBuzzer(bool state) {_data.buzzer_cmd = state;}
bool DashboardInterface::checkBuzzer() {return _data.buzzer_state;}

