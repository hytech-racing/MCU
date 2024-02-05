#include "DashboardInterface.h"

void DashboardInterface::read(const CAN_message_t &can_msg)
{

    DASHBOARD_STATE_t msg;
    Unpack_DASHBOARD_STATE_hytech(&msg, can_msg.buf, NULL);

    _data.dial_mode = static_cast<DialMode_e>(msg.dial_state);
    
    _data.ssok = msg.ssok_above_threshold;
    _data.shutdown = msg.shutdown_h_above_threshold;

    // _data.button.start = msg.start_btn;
    // _data.button.mark = msg.mark_btn;
    // _data.button.mode = msg.mode_btn;
    // _data.button.mc_cycle = msg.mc_cycle_btn;
    // _data.button.launch_ctrl = msg.launch_ctrl_btn;
    // _data.button.torque_mode = msg.torque_mode_btn;
    // _data.button.led_dimmer = msg.led_dimmer_btn;

    _data.buzzer_state = msg.drive_buzzer;

}

void DashboardInterface::write()
{   

    DASHBOARD_MCU_STATE_t msg;
    msg.drive_buzzer = _data.buzzer_cmd;

    // TODO: use logic as to not write data for LEDs that have not changed
    // msg.bots_led = _data.LED[DashLED_e::BOTS_LED];
    // msg.launch_control_led = _data.LED[DashLED_e::LAUNCH_CONTROL_LED];
    // msg.mode_led = _data.LED[DashLED_e::MODE_LED];
    // msg.mech_brake_led = _data.LED[DashLED_e::MECH_BRAKE_LED];
    // msg.cockpit_brb_led = _data.LED[DashLED_e::COCKPIT_BRB_LED];
    // msg.inertia_led = _data.LED[DashLED_e::INERTIA_LED];
    // msg.glv_led = _data.LED[DashLED_e::GLV_LED];
    // msg.crit_charge_led = _data.LED[DashLED_e::CRIT_CHARGE_LED];
    // msg.start_led = _data.LED[DashLED_e::START_LED];
    // msg.mc_error_led = _data.LED[DashLED_e::MC_ERROR_LED];
    // msg.imd_led = _data.LED[DashLED_e::IMD_LED];
    // msg.ams_led = _data.LED[DashLED_e::AMS_LED];

    CAN_message_t can_msg;
    can_msg.id = Pack_DASHBOARD_MCU_STATE_hytech(&msg, can_msg.buf, &can_msg.len, NULL);
    
    // TODO fix
    // msg_queue_->push_back(can_msg, sizeof(CAN_message_t));

}

//figure out how to set enumed led colors or send (0,255 value)
void DashboardInterface::setLED(DashLED_e led, LEDColors_e color)
{
    // TODO this no worky
    // _data.LED[static_cast<int>(led)] = static_cast<int> color;
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

