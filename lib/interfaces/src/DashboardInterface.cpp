#include "DashboardInterface.h"

void DashboardInterface::read(const CAN_message_t &can_msg)
{

    DASHBOARD_STATE_t dash_state;
    Unpack_DASHBOARD_STATE_hytech(&dash_state, can_msg.buf, can_msg.len);

    _data.dial_mode = static_cast<ControllerMode_e>(dash_state.dial_state);

    _data.ssok = dash_state.ssok_above_threshold;
    _data.shutdown = dash_state.shutdown_h_above_threshold;

    _data.button.start = dash_state.start_button;
    _data.button.mark = dash_state.mark_button;
    _data.button.mode = dash_state.mode_button;
    _data.button.mc_cycle = dash_state.motor_controller_cycle_button;
    _data.button.launch_ctrl = dash_state.launch_ctrl_button;
    _data.button.torque_mode = dash_state.torque_mode_button;
    _data.button.led_dimmer = dash_state.led_dimmer_button;
    _data.button.left_shifter = dash_state.left_shifter_button;
    _data.button.right_shifter = dash_state.right_shifter_button;

    _data.buzzer_state = dash_state.drive_buzzer;

    update_torque_mode_(_data.button.torque_mode);
}

// TODO this should be part of the CAN message not in this interface.
void DashboardInterface::update_torque_mode_(bool button_pressed)
{
    // detect high-to-low transition
    Serial.println("prev button state: ");
    Serial.println(prev_button_pressed_state_);
    Serial.println("button pressed: ");
    Serial.println(button_pressed);
    Serial.println("torque mode limit");
    Serial.println(static_cast<int>(_data.torque_limit_mode));
    if (prev_button_pressed_state_ == true && button_pressed == false)
    {
        
        _data.torque_limit_mode = static_cast<TorqueLimit_e>((static_cast<int>(_data.torque_limit_mode) + 1) % (static_cast<int>(TorqueLimit_e::TCMUX_NUM_TORQUE_LIMITS)));
    }
    prev_button_pressed_state_ = button_pressed;
}

CAN_message_t DashboardInterface::write()
{

    DASHBOARD_MCU_STATE_t dash_mcu_state;
    dash_mcu_state.drive_buzzer = _data.buzzer_cmd;

    dash_mcu_state.dial_state = static_cast<uint8_t>(_data.cur_dial_mode);

    // TODO: use logic as to not write data for LEDs that have not changed
    dash_mcu_state.launch_control_led = _data.LED[static_cast<int>(DashLED_e::LAUNCH_CONTROL_LED)];
    dash_mcu_state.mode_led = _data.LED[static_cast<int>(DashLED_e::MODE_LED)];
    dash_mcu_state.mechanical_brake_led = _data.LED[static_cast<int>(DashLED_e::MECH_BRAKE_LED)];
    dash_mcu_state.cockpit_brb_led = _data.LED[static_cast<int>(DashLED_e::COCKPIT_BRB_LED)];
    dash_mcu_state.inertia_status_led = _data.LED[static_cast<int>(DashLED_e::INERTIA_LED)];
    dash_mcu_state.start_status_led = _data.LED[static_cast<int>(DashLED_e::START_LED)];
    dash_mcu_state.motor_controller_error_led = _data.LED[static_cast<int>(DashLED_e::MC_ERROR_LED)];

    dash_mcu_state.bots_led = _data.LED[static_cast<int>(DashLED_e::BOTS_LED)];
    dash_mcu_state.imd_led = _data.LED[static_cast<int>(DashLED_e::IMD_LED)];
    dash_mcu_state.ams_led = _data.LED[static_cast<int>(DashLED_e::AMS_LED)];

    dash_mcu_state.glv_led = _data.LED[static_cast<int>(DashLED_e::GLV_LED)];
    dash_mcu_state.pack_charge_led = _data.LED[static_cast<int>(DashLED_e::CRIT_CHARGE_LED)];

    CAN_message_t can_msg;
    auto id = Pack_DASHBOARD_MCU_STATE_hytech(&dash_mcu_state, can_msg.buf, &can_msg.len, (uint8_t *)&can_msg.flags.extended);
    can_msg.id = id;
    // this circular buffer implementation requires that you push your data in a array buffer
    // all this does is put the msg into a uint8_t buffer and pushes it onto the queue
    uint8_t buf[sizeof(CAN_message_t)] = {};
    memmove(buf, &can_msg, sizeof(CAN_message_t));
    msg_queue_->push_back(buf, sizeof(CAN_message_t));

    return can_msg;
}

// figure out how to set enumed led colors or send (0,255 value)
void DashboardInterface::setLED(DashLED_e led, LEDColors_e color)
{

    _data.LED[static_cast<uint8_t>(led)] = static_cast<uint8_t>(color);
}

void DashboardInterface::tick10(MCUInterface *mcu,
                                int car_state,
                                bool buzzer,
                                bool drivetrain_error,
                                TorqueLimit_e torque,
                                float min_cell_voltage,
                                AnalogConversion_s glv_voltage,
                                int launch_state,
                                ControllerMode_e dial_mode)
{

    // TODO unfuck this
    _data.cur_dial_mode = dial_mode;
    soundBuzzer(buzzer);

    setLED(DashLED_e::AMS_LED, mcu->bms_ok_is_high() ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::IMD_LED, mcu->imd_ok_is_high() ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::BOTS_LED, mcu->get_bots_ok() ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::START_LED, car_state == int(MCU_STATE::READY_TO_DRIVE) ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::MC_ERROR_LED, !drivetrain_error ? LEDColors_e::ON : LEDColors_e::RED);
    setLED(DashLED_e::COCKPIT_BRB_LED, mcu->brb_ok_is_high() ? LEDColors_e::ON : LEDColors_e::RED);

    switch (launch_state)
    {
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

    switch (torque)
    {
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

    uint16_t scaled_cell_voltage = (uint16_t)map((uint32_t)(min_cell_voltage * 1000), 3300, 4200, 0, 255);          // scale voltage
    _data.LED[static_cast<int>(DashLED_e::CRIT_CHARGE_LED)] = std::max(0, std::min((int)scaled_cell_voltage, 255)); // clamp voltage
    // _data.LED[DashLED_e::GLV_LED] = (uint8_t)map(glv_voltage.raw)

    write();
}

ControllerMode_e DashboardInterface::getDialMode() { return _data.dial_mode; }
TorqueLimit_e DashboardInterface::getTorqueLimitMode() {return _data.torque_limit_mode; }
bool DashboardInterface::startButtonPressed() { return _data.button.start; }
bool DashboardInterface::specialButtonPressed() { return _data.button.mark; }
bool DashboardInterface::torqueModeButtonPressed() { return _data.button.torque_mode; }
bool DashboardInterface::inverterResetButtonPressed() { return _data.button.mc_cycle; }
bool DashboardInterface::launchControlButtonPressed() { return _data.button.launch_ctrl; }
bool DashboardInterface::nightModeButtonPressed() { return _data.button.led_dimmer; }
bool DashboardInterface::leftShifterButtonPressed() { return _data.button.left_shifter; }
bool DashboardInterface::rightShifterButtonPressed() { return _data.button.right_shifter; }

bool DashboardInterface::safetySystemOK() { return _data.ssok; }
bool DashboardInterface::shutdownHAboveThreshold() { return _data.shutdown; }

void DashboardInterface::soundBuzzer(bool state) { _data.buzzer_cmd = state; }
bool DashboardInterface::checkBuzzer() { return _data.buzzer_state; }
