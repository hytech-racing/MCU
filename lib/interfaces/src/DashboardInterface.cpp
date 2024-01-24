#include "DashboardInterface.h"

void DashboardInterface::read(const Dashboard_status &msg)
{
    data.dial_mode = static_cast<DialMode_e>(msg.get_dial_state());
    
    data.ssok = msg.get_ssok_above_threshold();
    data.shutdown = msg.get_shutdown_h_above_threshold();

    data.button.start = msg.get_start_btn();
    data.button.mark = msg.get_mark_btn();
    data.button.mode = msg.get_mode_btn();
    data.button.mc_cycle = msg.get_mc_cycle_btn();
    data.button.launch_ctrl = msg.get_launch_ctrl_btn();
    data.button.torque_mode = msg.get_torque_mode_btn();
    data.button.led_dimmer = msg.get_led_dimmer_btn();

}

Dashboard_status DashboardInterface::write()
{
    Dashboard_status msg{};
}

DialMode_e DashboardInterface::getDialMode() {return data.dial_mode;}

bool DashboardInterface::startButtonPressed() {return data.button.start;}
bool DashboardInterface::specialButtonPressed() {return data.button.mark;}
bool DashboardInterface::torqueButtonPressed() {return data.button.mode;}
bool DashboardInterface::inverterResetButtonPressed() {return data.button.mc_cycle;}
bool DashboardInterface::launchControlButtonPressed() {return data.button.launch_ctrl;}
bool DashboardInterface::torqueLoadingButtonPressed() {return data.button.torque_mode;}
bool DashboardInterface::nightModeButtonPressed() {return data.button.led_dimmer;}

bool DashboardInterface::safetySystemOK() {return data.ssok;}

// bool DashboardInterface::torqueVectoringOffButtonPressed() {}

void DashboardInterface::soundBuzzer(bool state) {data.buzzer = state;}

void DashboardInterface::amsLED(LEDColors_e color) {data.LED.ams = static_cast<int>(color);}
void DashboardInterface::imdLED(LEDColors_e color) {data.LED.imd = static_cast<int>(color);}
void DashboardInterface::modeLED(LEDColors_e color) {data.LED.mode = static_cast<int>(color);}
void DashboardInterface::mcErrorLED(LEDColors_e color) {data.LED.mc_error = static_cast<int>(color);}
void DashboardInterface::startLED(LEDColors_e color) {data.LED.start = static_cast<int>(color);}
void DashboardInterface::InertiaSwitchLED(LEDColors_e color) {data.LED.inertia = static_cast<int>(color);}
void DashboardInterface::mechanicalBrakeLED(LEDColors_e color) {data.LED.mech_brake = static_cast<int>(color);}
void DashboardInterface::generalPurposeLED(LEDColors_e color) {data.LED.gen_purp = static_cast<int>(color);}
void DashboardInterface::botsLED(LEDColors_e color) {data.LED.bots = static_cast<int>(color);}
void DashboardInterface::cockpitBrbLED(LEDColors_e color) {data.LED.cockpit_brb = static_cast<int>(color);}
void DashboardInterface::critChargeLED(LEDColors_e color) {data.LED.crit_charge = static_cast<int>(color);}
void DashboardInterface::glvLED(LEDColors_e color) {data.LED.glv = static_cast<int>(color);}
void DashboardInterface::launchControlLED(LEDColors_e color) {data.LED.launch_control = static_cast<int>(color);}