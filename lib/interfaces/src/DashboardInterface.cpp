#include "DashboardInterface.h"

void DashboardInterface::read(const CAN_message_t &can_msg)
{

    // Reads the current dashboard from the CAN buffer
    DASHBOARD_STATE_t dash_state;
    Unpack_DASHBOARD_STATE_hytech(&dash_state, can_msg.buf, can_msg.len);

    // Writes the data from the CAN buffer into the local struct.
    data_.dial_mode = static_cast<DialMode_e>(dash_state.dial_state);
    
    data_.ssok = dash_state.ssok_above_threshold;                     //not set in Dashboard code
    data_.shutdown = dash_state.shutdown_h_above_threshold;           //not set in Dashboard code

    data_.button.start = dash_state.start_button;
    data_.button.mark = dash_state.mark_button;
    data_.button.mode = dash_state.mode_button;                       //not set in Dashboard code
    data_.button.mc_cycle = dash_state.motor_controller_cycle_button;
    data_.button.launch_ctrl = dash_state.launch_ctrl_button;         //not set in Dashboard code
    data_.button.torque_mode = dash_state.torque_mode_button;
    data_.button.led_dimmer = dash_state.led_dimmer_button;
    data_.button.left_shifter = dash_state.left_shifter_button;
    data_.button.right_shifter = dash_state.right_shifter_button;

    data_.buzzer_state = dash_state.drive_buzzer;

}

CAN_message_t DashboardInterface::write()
{   

    // Creating struct to populate with data
    DASHBOARD_MCU_STATE_t dash_mcu_state;

    dash_mcu_state.drive_buzzer = data_.buzzer_cmd;
    dash_mcu_state.dial_state = static_cast<uint8_t>(data_.cur_dial_mode);

    // Writing LEDs
    dash_mcu_state.launch_control_led = data_.LED[static_cast<int>(DashLED_e::LAUNCH_CONTROL_LED)];
    dash_mcu_state.mode_led = data_.LED[static_cast<int>(DashLED_e::MODE_LED)];
    dash_mcu_state.mechanical_brake_led = data_.LED[static_cast<int>(DashLED_e::MECH_BRAKE_LED)];
    dash_mcu_state.cockpit_brb_led = data_.LED[static_cast<int>(DashLED_e::COCKPIT_BRB_LED)];
    dash_mcu_state.inertia_status_led = data_.LED[static_cast<int>(DashLED_e::INERTIA_LED)];
    dash_mcu_state.start_status_led = data_.LED[static_cast<int>(DashLED_e::START_LED)];
    dash_mcu_state.motor_controller_error_led = data_.LED[static_cast<int>(DashLED_e::MC_ERROR_LED)];
    dash_mcu_state.bots_led = data_.LED[static_cast<int>(DashLED_e::BOTS_LED)];
    dash_mcu_state.imd_led = data_.LED[static_cast<int>(DashLED_e::IMD_LED)];
    dash_mcu_state.ams_led = data_.LED[static_cast<int>(DashLED_e::AMS_LED)];
    dash_mcu_state.glv_led = data_.LED[static_cast<int>(DashLED_e::GLV_LED)];
    dash_mcu_state.pack_charge_led = data_.LED[static_cast<int>(DashLED_e::CRIT_CHARGE_LED)];
    
    CAN_message_t can_msg;
    auto id = Pack_DASHBOARD_MCU_STATE_hytech(&dash_mcu_state, can_msg.buf, &can_msg.len, (uint8_t*) &can_msg.flags.extended);
    can_msg.id = id;
    uint8_t buf[sizeof(CAN_message_t)] = {};
    memmove(buf, &can_msg, sizeof(CAN_message_t));
    msg_queue_->push_back(buf, sizeof(CAN_message_t));

    return can_msg;

}

void DashboardInterface::setLED(DashLED_e led, LEDColors_e color)
{
    data_.LED[static_cast<uint8_t>(led)] = static_cast<uint8_t>(color);
}

void DashboardInterface::tick(MCUInterface* mcu, 
                                int car_state, 
                                bool buzzer, 
                                bool drivetrain_error, 
                                TorqueLimit_e torque,
                                float min_cell_voltage,
                                AnalogConversion_s glv_voltage,
                                int launch_state,
                                DialMode_e dial_mode)
{

    data_.cur_dial_mode = dial_mode;
    
    soundBuzzer(buzzer);

    setLED(DashLED_e::AMS_LED, mcu->bms_ok_is_high() ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::IMD_LED, mcu->imd_ok_is_high() ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::BOTS_LED, mcu->get_bots_ok() ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::START_LED, car_state == int(MCU_STATE::READY_TO_DRIVE) ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::MC_ERROR_LED, !drivetrain_error ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::COCKPIT_BRB_LED, mcu->brb_ok_is_high() ? LEDColors_e::ON : LEDColors_e::RED);

    switch(launch_state){
    case 1:
        setLED(DashLED_e::LAUNCH_CONTROL_LED, LEDColors_e::RED);
        break;
    case 2:
        setLED(DashLED_e::LAUNCH_CONTROL_LED, LEDColors_e::YELLOW);
        break;
    case 3:
        setLED(DashLED_e::LAUNCH_CONTROL_LED, LEDColors_e::ON);
        break;
    default:
        setLED(DashLED_e::LAUNCH_CONTROL_LED, LEDColors_e::OFF);
        break;
    }

    switch(torque){
    case TorqueLimit_e::TCMUX_LOW_TORQUE:
        setLED(DashLED_e::MODE_LED, LEDColors_e::OFF);
        break;
    case TorqueLimit_e::TCMUX_MID_TORQUE:
        setLED(DashLED_e::MODE_LED, LEDColors_e::YELLOW);
        break;
    case TorqueLimit_e::TCMUX_FULL_TORQUE:
        setLED(DashLED_e::MODE_LED, LEDColors_e::ON);
        break;
    default:
        setLED(DashLED_e::MODE_LED, LEDColors_e::RED);
        break;
    }

    uint16_t scaled_cell_voltage = (uint16_t)map((uint32_t)(min_cell_voltage*1000), 3300, 4200, 0, 255);// scale voltage
    data_.LED[static_cast<int>(DashLED_e::CRIT_CHARGE_LED)] = std::max(0, std::min((int)scaled_cell_voltage, 255));// clamp voltage

    write();
}

DialMode_e DashboardInterface::getDialMode() {return data_.dial_mode;}
bool DashboardInterface::startButtonPressed() {return data_.button.start;}
bool DashboardInterface::specialButtonPressed() {return data_.button.mark;}
bool DashboardInterface::torqueModeButtonPressed() {return data_.button.torque_mode;}
bool DashboardInterface::inverterResetButtonPressed() {return data_.button.mc_cycle;}
bool DashboardInterface::launchControlButtonPressed() {return data_.button.launch_ctrl;}
bool DashboardInterface::nightModeButtonPressed() {return data_.button.led_dimmer;}
bool DashboardInterface::leftShifterButtonPressed() {return data_.button.left_shifter;}
bool DashboardInterface::rightShifterButtonPressed() {return data_.button.right_shifter;}
bool DashboardInterface::safetySystemOK() {return data_.ssok;}
bool DashboardInterface::shutdownHAboveThreshold() {return data_.shutdown;}
void DashboardInterface::soundBuzzer(bool state) {data_.buzzer_cmd = state;}
bool DashboardInterface::checkBuzzer() {return data_.buzzer_state;}