/* -------------------- INCLUDE STATEENTS -------------------- */

/* System Includes */
#include <Arduino.h>

/* Libraries */ 
#include "FlexCAN_T4.h"           // from FlexCAN_T4 library
#include "HyTech_CAN.h"           // from hytech_can library (deprecated, use can_lib library instead)
#include "MCU_rev15_defs.h"
// #include "NativeEthernet.h"

/* Interfaces */
#include "HytechCANInterface.h"   
#include "ThermistorInterface.h"
#include "MCUInterface.h"
#include "AMSInterface.h"
#include "WatchdogInterface.h"
#include "DashboardInterface.h"
#include "InverterInterface.h"
#include "TelemetryInterface.h"
#include "SABInterface.h"
#include "VectornavInterface.h"
#include "LoadCellInterface.h"
#include "ParameterInterface.h"
#include "Teensy_ADC.h"           // from shared-interfaces-lib
#include "MCP_ADC.h"              // from shared-interfaces-lib
#include "ORBIS_BR10.h"           // from shared-interfaces-lib (steering sensor)

/* Systems */
#include "SysClock.h"             // from shared-systems-lib
#include "Buzzer.h"
#include "SafetySystem.h"
#include "DrivetrainSystem.h"
#include "PedalsSystem.h"
#include "TorqueControllerMux.h"
#include "CASESystem.h"

/* State machine */
#include "MCUStateMachine.h"
#include "HT08_CASE.h"





/* -------------------- PARAMETER STRUCTS -------------------- */

/**
 * Constant definition for the ADC channels based on MCU_rev15_defs.h. See
 * TelemetryInterface.h for TelemtryInterfaceReadChannels struct documentation.
 */
const TelemetryInterfaceReadChannels telem_read_channels = {
    .accel1_channel = MCU15_ACCEL1_CHANNEL,
    .accel2_channel = MCU15_ACCEL2_CHANNEL,
    .brake1_channel = MCU15_BRAKE1_CHANNEL,
    .brake2_channel = MCU15_BRAKE2_CHANNEL,
    .pots_fl_channel = MCU15_FL_POTS_CHANNEL,
    .pots_fr_channel = MCU15_FR_POTS_CHANNEL,
    .loadcell_fl_channel = MCU15_FL_LOADCELL_CHANNEL,
    .loadcell_fr_channel = MCU15_FR_LOADCELL_CHANNEL,
    .analog_steering_channel = MCU15_STEERING_CHANNEL,
    .current_channel = MCU15_CUR_POS_SENSE_CHANNEL,
    .current_ref_channel = MCU15_CUR_NEG_SENSE_CHANNEL,
    .glv_sense_channel = MCU15_GLV_SENSE_CHANNEL,
    .therm_fl_channel = MCU15_THERM_FL_CHANNEL,
    .therm_fr_channel = MCU15_THERM_FR_CHANNEL
};

/**
 * Acceleration pedal parameters using both accel sensors. See PedalsSystem.h
 * for PedalsParams struct definition.
 */
const PedalsParams accel_params = {
    .min_pedal_1 = ACCEL1_PEDAL_MIN,
    .min_pedal_2 = ACCEL2_PEDAL_MIN,
    .max_pedal_1 = ACCEL1_PEDAL_MAX,
    .max_pedal_2 = ACCEL2_PEDAL_MAX,
    .min_sensor_pedal_1 = ACCEL1_PEDAL_OOR_MIN,
    .min_sensor_pedal_2 = ACCEL2_PEDAL_OOR_MIN,
    .max_sensor_pedal_1 = ACCEL1_PEDAL_OOR_MAX,
    .max_sensor_pedal_2 = ACCEL2_PEDAL_OOR_MAX,
    .activation_percentage = APPS_ACTIVATION_PERCENTAGE,
    .deadzone_margin = DEFAULT_PEDAL_DEADZONE,
    .implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN,
    .mechanical_activation_percentage = APPS_ACTIVATION_PERCENTAGE
};

/**
 * Acceleration pedal parameters using only the first accel sensor. Do not use
 * unless you have a compelling reason to do so, since this does NOT comply with
 * rules for APPS implausibilities (T.4.2)
 */
const PedalsParams accel1_only_params = {
    .min_pedal_1 = ACCEL1_PEDAL_MIN,
    .min_pedal_2 = ACCEL1_PEDAL_MIN,
    .max_pedal_1 = ACCEL1_PEDAL_MAX,
    .max_pedal_2 = ACCEL1_PEDAL_MAX,
    .min_sensor_pedal_1 = ACCEL1_PEDAL_OOR_MIN,
    .min_sensor_pedal_2 = ACCEL1_PEDAL_OOR_MIN,
    .max_sensor_pedal_1 = ACCEL1_PEDAL_OOR_MAX,
    .max_sensor_pedal_2 = ACCEL1_PEDAL_OOR_MAX,
    .activation_percentage = APPS_ACTIVATION_PERCENTAGE,
    .deadzone_margin = DEFAULT_PEDAL_DEADZONE,
    .implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN,
    .mechanical_activation_percentage = APPS_ACTIVATION_PERCENTAGE};

/**
 * Acceleration pedal parameters using only the second accel sensor. Do not use
 * unless you have a compelling reason to do so, since this does NOT comply with
 * rules for APPS implausibilities (T.4.2)
 */
const PedalsParams accel2_only_params = {
    .min_pedal_1 = ACCEL2_PEDAL_MIN,
    .min_pedal_2 = ACCEL2_PEDAL_MIN,
    .max_pedal_1 = ACCEL2_PEDAL_MAX,
    .max_pedal_2 = ACCEL2_PEDAL_MAX,
    .min_sensor_pedal_1 = ACCEL2_PEDAL_OOR_MIN,
    .min_sensor_pedal_2 = ACCEL2_PEDAL_OOR_MIN,
    .max_sensor_pedal_1 = ACCEL2_PEDAL_OOR_MAX,
    .max_sensor_pedal_2 = ACCEL2_PEDAL_OOR_MAX,
    .activation_percentage = APPS_ACTIVATION_PERCENTAGE,
    .deadzone_margin = DEFAULT_PEDAL_DEADZONE,
    .implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN,
    .mechanical_activation_percentage = APPS_ACTIVATION_PERCENTAGE
};

/**
 * Brake pedal parameters using both sensors. See PedalsSystem.h for PedalsParams.h
 * definition and brake_params usage.
 */
const PedalsParams brake_params = {
    .min_pedal_1 = BRAKE1_PEDAL_MIN,
    .min_pedal_2 = BRAKE2_PEDAL_MIN,
    .max_pedal_1 = BRAKE1_PEDAL_MAX,
    .max_pedal_2 = BRAKE2_PEDAL_MAX,
    .min_sensor_pedal_1 = BRAKE1_PEDAL_OOR_MIN,
    .min_sensor_pedal_2 = BRAKE2_PEDAL_OOR_MIN,
    .max_sensor_pedal_1 = BRAKE1_PEDAL_OOR_MAX,
    .max_sensor_pedal_2 = BRAKE2_PEDAL_OOR_MAX,
    .activation_percentage = BRAKE_ACTIVATION_PERCENTAGE,
    .deadzone_margin = DEFAULT_PEDAL_DEADZONE,
    .implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN,
    .mechanical_activation_percentage = BRAKE_MECH_THRESH,
};

/**
 * Brake pedal parameters using only brake1 sensor. Contrary to the APPS, this is allowed
 * by rules, since only one brake pedal sensor is required (T.4.3). However, we prefer to
 * use both brake sensors unless we have a compelling reason not to.
 */
const PedalsParams brake1_only_params = {
    .min_pedal_1 = BRAKE1_PEDAL_MIN,
    .min_pedal_2 = BRAKE1_PEDAL_MIN,
    .max_pedal_1 = BRAKE1_PEDAL_MAX,
    .max_pedal_2 = BRAKE1_PEDAL_MAX,
    .min_sensor_pedal_1 = BRAKE1_PEDAL_OOR_MIN,
    .min_sensor_pedal_2 = BRAKE1_PEDAL_OOR_MIN,
    .max_sensor_pedal_1 = BRAKE1_PEDAL_OOR_MAX,
    .max_sensor_pedal_2 = BRAKE1_PEDAL_OOR_MAX,
    .activation_percentage = BRAKE_ACTIVATION_PERCENTAGE,
    .deadzone_margin = DEFAULT_PEDAL_DEADZONE,
    .implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN,
    .mechanical_activation_percentage = BRAKE_MECH_THRESH,
};

/**
 * Brake pedal parameters using only brake2 sensor. Contrary to the APPS, this is allowed
 * by rules, since only one brake pedal sensor is required (T.4.3). However, we prefer to
 * use both brake sensors unless we have a compelling reason not to.
 */
const PedalsParams brake2_only_params = {
    .min_pedal_1 = BRAKE2_PEDAL_MIN,
    .min_pedal_2 = BRAKE2_PEDAL_MIN,
    .max_pedal_1 = BRAKE2_PEDAL_MAX,
    .max_pedal_2 = BRAKE2_PEDAL_MAX,
    .min_sensor_pedal_1 = BRAKE2_PEDAL_OOR_MIN,
    .min_sensor_pedal_2 = BRAKE2_PEDAL_OOR_MIN,
    .max_sensor_pedal_1 = BRAKE2_PEDAL_OOR_MAX,
    .max_sensor_pedal_2 = BRAKE2_PEDAL_OOR_MAX,
    .activation_percentage = BRAKE_ACTIVATION_PERCENTAGE,
    .deadzone_margin = DEFAULT_PEDAL_DEADZONE,
    .implausibility_margin = DEFAULT_PEDAL_IMPLAUSIBILITY_MARGIN,
    .mechanical_activation_percentage = BRAKE_MECH_THRESH,
};





/* -------------------- DATA SOURCES -------------------- */

EthernetUDP protobuf_send_socket;
EthernetUDP protobuf_recv_socket;

/**
 * The Inverter CAN line (contains only the four Inverters).
 */
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> INV_CAN;

/**
 * The Telemetry CAN line (contains almost everything except the inverters). The Telemetry CAN line
 * gets updated by the TelemetryInterface.
 */
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN;

/**
 * The main 8-input ADC on the MCU that handles pedals data, hall effect current, and analog steering.
 */
MCP_ADC<8> a1 = MCP_ADC<8>(ADC1_CS);

/**
 * The 4-bit ADC on the front left corner board that handles FL suspention potentiometer and load cell data.
 * On the MCU, this is an LTC6820 that receives the corner board ADC data over isoSPI.
 */
MCP_ADC<4> a2 = MCP_ADC<4>(ADC2_CS, 1000000); // 1M baud needed for MCP3204s

/**
 * The 4-bit ADC on the front right corner board that handles FR suspention potentiometer and load cell data.
 * On the MCU, this is an LTC6820 that receives the corner board ADC data over isoSPI.
 */
MCP_ADC<4> a3 = MCP_ADC<4>(ADC3_CS, 1000000); // 1M baud needed for MCP3204s

/**
 * The Teensy ADC interface from shared-interfaces-lib. See TeensyADC.h for documentation.
 */
Teensy_ADC<2> mcu_adc = Teensy_ADC<2>(DEFAULT_ANALOG_PINS);

/**
 * The OrbisBR10 steering sensor interface from shared-interfaces-lib. On the MCU, this is an RS422 that
 * communicates over serial with the OrbisBR10 itself. The main Teensy has two pins (steering TX and RX)
 * to communicate through the RS422.
 */
OrbisBR10 steering1(&Serial5);





/* -------------------- INTERFACES -------------------- */

ParameterInterface param_interface;
ETHInterfaces ethernet_interfaces = {&param_interface};
VNInterface<CANBufferType> vn_interface(&CAN3_txBuffer);
DashboardInterface dashboard(&CAN3_txBuffer);
AMSInterface ams_interface(&CAN3_txBuffer, SOFTWARE_OK);
WatchdogInterface wd_interface(WATCHDOG_INPUT);
MCUInterface main_ecu(&CAN3_txBuffer);
TelemetryInterface telem_interface(&CAN3_txBuffer, telem_read_channels);
ThermistorInterface front_thermistors_interface(&CAN3_txBuffer);
SABInterface sab_interface(LOADCELL_RL_SCALE, LOADCELL_RL_OFFSET, LOADCELL_RR_SCALE, LOADCELL_RR_OFFSET);
LoadCellInterface load_cell_interface;
struct inverters
{
    InvInt_t fl = InvInt_t(&CAN2_txBuffer, ID_MC1_SETPOINTS_COMMAND);
    InvInt_t fr = InvInt_t(&CAN2_txBuffer, ID_MC2_SETPOINTS_COMMAND);
    InvInt_t rl = InvInt_t(&CAN2_txBuffer, ID_MC3_SETPOINTS_COMMAND);
    InvInt_t rr = InvInt_t(&CAN2_txBuffer, ID_MC4_SETPOINTS_COMMAND);
} inv;





/* -------------------- SYSTEMS -------------------- */

SysClock sys_clock;
SteeringSystem steering_system(&steering1, &telem_interface, STEERING_IIR_ALPHA);
BuzzerController buzzer(BUZZER_ON_INTERVAL);
SafetySystem safety_system(&ams_interface, &wd_interface);
PedalsSystem pedals_system(accel_params, brake_params);
using DriveSys_t = DrivetrainSystem<InvInt_t>;
DriveSys_t drivetrain = DriveSys_t({&inv.fl, &inv.fr, &inv.rl, &inv.rr}, &main_ecu, INVERTER_ENABLING_TIMEOUT_INTERVAL);
TorqueControllerMux torque_controller_mux(SIMPLE_TC_REAR_TORQUE_SCALE, SIMPLE_TC_REGEN_TORQUE_SCALE, &telem_interface);
// TODO ensure that case uses max regen torque, right now its not
CASEConfiguration case_config = {
    // Following used for generated code
    .AbsoluteTorqueLimit = 21.42, // N-m, Torque limit used for yaw pid torque split overflow
    .yaw_pid_p = 1.15,
    .yaw_pid_i = 0.0,
    .yaw_pid_d = 0.0,
    .tcs_pid_p_lowerBound_front = 55.0, // if tcs_pid_p_lowerBound_front > tcs_pid_p_upperBound_front, inverse relationship, no error
    .tcs_pid_p_upperBound_front = 42.0,
    .tcs_pid_p_lowerBound_rear = 32.0,
    .tcs_pid_p_upperBound_rear = 42.0,
    .tcs_pid_i = 0.0,
    .tcs_pid_d = 0.0,
    .useLaunch = false,
    .usePIDTV = true,
    .useTCSLimitedYawPID = true,
    .useNormalForce = true,
    .useTractionControl = true,
    .usePowerLimit = true,
    .usePIDPowerLimit = false,
    .useDecoupledYawBrakes = true,
    .useDiscontinuousYawPIDBrakes = true,
    .launchDeadZone = 20.0,        // N-m
    .launchVelThreshold = 0.15,    // m/s
    .tcsVelThreshold = 1.5,        // m/s
    .yawPIDMaxDifferential = 10.0, // N-m
    .yawPIDErrorThreshold = 0.1,   // rad/s
    .yawPIDVelThreshold = 0.35,    // m/s
    .yawPIDCoastThreshold = 2.5,   // m/s
    .yaw_pid_brakes_p = 0.1,
    .yaw_pid_brakes_i = 0.0,
    .yaw_pid_brakes_d = 0.0,
    .decoupledYawPIDBrakesMaxDIfference = 2, // N-m
    .discontinuousBrakesPercentThreshold = 0.7,
    .TorqueMode = 21.42, // N-m
    .RegenLimit = -15.0, // N-m
    .useNoRegen5kph = true,
    .useTorqueBias = true,
    .DriveTorquePercentFront = 0.5, // DON'T TOUCH UNTIL LOAD CELL ADHERES TO DRIVE BIAS
    .BrakeTorquePercentFront = 0.6,
    .MechPowerMaxkW =51.5,            // kW
    .launchLeftRightMaxDiff = 2.0,     // N-m
    .tcs_pid_lower_rpm_front = 0.0,    // RPM
    .tcs_pid_upper_rpm_front = 5000.0, // RPM
    .tcs_pid_lower_rpm_rear = 0.0,     // RPM
    .tcs_pid_upper_rpm_rear = 5000.0,  // RPM
    .maxNormalLoadBrakeScalingFront = 1.15,
    .tcs_saturation_front = 20,
    .tcs_saturation_rear = 20,
    .TCSGenLeftRightDiffLowerBound = 2,  // N-m
    .TCSGenLeftRightDiffUpperBound = 20, // N-m
    .TCSWheelSteerLowerBound = 2,        // Deg
    .TCSWheelSteerUpperBound = 25,       // Deg
    .useRPM_TCS_GainSchedule = true,    // If both are false, then P values defaults to lower bound per axle
    .useNL_TCS_GainSchedule = false,
    .TCS_NL_startBoundPerc_FrontAxle = 0.5,
    .TCS_NL_endBoundPerc_FrontAxle = 0.4,
    .TCS_NL_startBoundPerc_RearAxle = 0.5,
    .TCS_NL_endBoundPerc_RearAxle = 0.6,
    .useNL_TCS_SlipSchedule = true,
    .launchSL_startBound_Front = 0.25,
    .launchSL_endBound_Front = 0.25,
    .launchSL_startBound_Rear = 0.3,
    .launchSL_endBound_Rear = 0.4,
    .TCS_SL_startBound_Front = 0.25,
    .TCS_SL_endBound_Front = 0.15,
    .TCS_SL_startBound_Rear = 0.3,
    .TCS_SL_endBound_Rear = 0.4,
    .TCS_SL_NLPerc_startBound_Front = 0.5,
    .TCS_SL_NLPerc_endBound_Front = 0.4,
    .TCS_SL_NLPerc_startBound_Rear = 0.5,
    .TCS_SL_NLPerc_endBound_Rear = 0.6,

    // Following used for calculate_torque_request in CASESystem.tpp
    .max_rpm = 20000,
    .max_regen_torque = 21.42,
    .max_torque = 21.42,
};

CASESystem<CANBufferType> case_system(&CAN3_txBuffer, 100, 70, 550, case_config);

/**
 * Main MCU state machine that handles entering various states (READY_TO_DRIVE, etc).
 */
MCUStateMachine<DriveSys_t> fsm(&buzzer, &drivetrain, &dashboard, &pedals_system, &torque_controller_mux, &safety_system);





/* -------------------- GROUPING STRUCTS (To limit parameter count in utilizing functions) -------------------- */
CANInterfaces<CANBufferType> CAN_receive_interfaces = {&inv.fl, &inv.fr, &inv.rl, &inv.rr, &vn_interface, &dashboard, &ams_interface, &sab_interface};





/* -------------------- FUNCTION HEADERS -------------------- */

/**
 * Initialize CAN communication on the Inverter CAN and Telemetry CAN lines,
 * setting the proper pins/baud rates/etc.
 */
void init_all_CAN_devices();

/**
 * Calls the tick() function of each interface at the appropriate rate, based on
 * the current_system_tick. This function should ensure that no tick() function
 * is being triggered more often than intended.
 * @param current_system_tick The current SysTick_s object. SysTick_s comes from
 *                            SysClock.h in the shared-systems-lib.
 */
void tick_all_interfaces(const SysTick_s &current_system_tick);

/**
 * Calls the tick() function of each system at the appropriate rate, based on the
 * current_system_tick. Contrary to tick_all_interfaces, this function will call
 * each system's tick() function every loop, and it is the responsibility of the
 * system's tick() function to only trigger when necessary.
 * @param current_system_tick The current SysTick_s object. SysTick_s comes from
 *                            SysClock.h in the shared-systems-lib.
 */
void tick_all_systems(const SysTick_s &current_system_tick);

/**
 * Work in progress by BEN.
 * TODO: Update documentation once Ethernet work is complete.
 */
void handle_ethernet_interface_comms();





/* -------------------- SETUP FUNCTION -------------------- */
void setup()
{

    // ---------- Begin SerialMonitor ----------
    Serial.begin(115200);

    // ---------- initialize CAN communication ----------
    init_all_CAN_devices();

    // ---------- Initialize Ethernet communication ----------
    // Ethernet.begin(EthParams::default_MCU_MAC_address, EthParams::default_MCU_ip);
    // protobuf_send_socket.begin(EthParams::default_protobuf_send_port);
    // protobuf_recv_socket.begin(EthParams::default_protobuf_recv_port);

    /* Do this to send message VVV */
    // protobuf_socket.beginPacket(EthParams::default_TCU_ip, EthParams::default_protobuf_port);
    // protobuf_socket.write(buf, len);
    // protobuf_socker.endPacket();

    // ---------- Initialize SPI communication ----------
    SPI.begin();
    a1.init();
    a2.init();
    a3.init();
    mcu_adc.init();

    // ---------- Initialize offsets/scales for each ADC channel ----------
    a1.setChannelScale(MCU15_ACCEL1_CHANNEL, (1.0 / (float)(ACCEL1_PEDAL_MAX - ACCEL1_PEDAL_MIN)));
    a1.setChannelScale(MCU15_ACCEL2_CHANNEL, (1.0 / (float)(ACCEL2_PEDAL_MAX - ACCEL2_PEDAL_MIN)));
    a1.setChannelScale(MCU15_BRAKE1_CHANNEL, (1.0 / (float)(BRAKE1_PEDAL_MAX - BRAKE1_PEDAL_MIN)));
    a1.setChannelScale(MCU15_BRAKE2_CHANNEL, (1.0 / (float)(BRAKE2_PEDAL_MAX - BRAKE2_PEDAL_MIN)));
    a1.setChannelOffset(MCU15_ACCEL1_CHANNEL, -ACCEL1_PEDAL_MIN);
    a1.setChannelOffset(MCU15_ACCEL2_CHANNEL, -ACCEL2_PEDAL_MIN);
    a1.setChannelOffset(MCU15_BRAKE1_CHANNEL, -BRAKE1_PEDAL_MIN);
    a1.setChannelOffset(MCU15_BRAKE2_CHANNEL, -BRAKE2_PEDAL_MIN);
    a1.setChannelOffset(MCU15_STEERING_CHANNEL, -1 * SECONDARY_STEERING_SENSE_CENTER);
    a1.setChannelScale(MCU15_STEERING_CHANNEL, STEERING_RANGE_DEGREES / ((float)SECONDARY_STEERING_SENSE_RIGHTMOST_BOUND - (float)SECONDARY_STEERING_SENSE_LEFTMOST_BOUND));
    a1.setChannelClamp(MCU15_STEERING_CHANNEL, -STEERING_RANGE_DEGREES / 0.5 * 1.15, STEERING_RANGE_DEGREES / 0.5 * 1.15); // 15% tolerance on each end of the steering sensor
    a1.setChannelScale(MCU15_GLV_SENSE_CHANNEL, GLV_SENSE_SCALE);

    a2.setChannelScale(MCU15_FL_LOADCELL_CHANNEL, LOADCELL_FL_SCALE);
    a2.setChannelOffset(MCU15_FL_LOADCELL_CHANNEL, LOADCELL_FL_OFFSET);

    a3.setChannelScale(MCU15_FR_LOADCELL_CHANNEL, LOADCELL_FR_SCALE);
    a3.setChannelOffset(MCU15_FR_LOADCELL_CHANNEL, LOADCELL_FR_OFFSET);

    mcu_adc.setAlphas(MCU15_THERM_FL, 0.95);
    mcu_adc.setAlphas(MCU15_THERM_FR, 0.95);

    // ---------- Get latest tick from SysClock ----------
    SysTick_s curr_tick = sys_clock.tick(micros());

    // ---------- Call the init() function on each interface ----------
    main_ecu.init();                      // initial shutdown circuit readings,
    wd_interface.init(curr_tick.millis);  // initialize wd kick time
    ams_interface.init(curr_tick);        // initialize last heartbeat time

    // TODO: Consolidate this into one function. main.cpp should ONLY need to
    //       call the init() function for each interface. Calling a second
    //       function should not be required.
    steering1.init();
    steering1.setOffset(PRIMARY_STEERING_SENSE_OFFSET);

    // ---------- Call the init() function on each system ----------
    safety_system.init();
    drivetrain.disable();

}





/* -------------------- LOOP FUNCTION -------------------- */
void loop()
{
    // ---------- Get latest tick from sys clock ----------
    SysTick_s curr_tick = sys_clock.tick(micros());

    // handle_ethernet_interface_comms();

    // ---------- Process received CAN messages ----------
    process_ring_buffer(CAN2_rxBuffer, CAN_receive_interfaces, curr_tick.millis); // Inverter CAN
    process_ring_buffer(CAN3_rxBuffer, CAN_receive_interfaces, curr_tick.millis); // Telemetry CAN

    // ---------- Tick interfaces ----------
    tick_all_interfaces(curr_tick);

    // ---------- Tick systems ----------
    tick_all_systems(curr_tick);

    // ---------- Inverter procedure before entering state machine ----------
    if (dashboard.inverterResetButtonPressed() && drivetrain.drivetrain_error_occured())
    {
        drivetrain.reset_drivetrain();
    }

    // ---------- Tick state machine ----------
    fsm.tick_state_machine(curr_tick.millis);

    // ---------- Give the state of the car to the param interface ----------
    param_interface.update_car_state(fsm.get_state());

    // ---------- Tick safety system ----------
    safety_system.software_shutdown(curr_tick);

    // ---------- Send all CAN messages ----------
    send_all_CAN_msgs(CAN2_txBuffer, &INV_CAN);
    send_all_CAN_msgs(CAN3_txBuffer, &TELEM_CAN);

    // ---------- Debug prints (5Hz) ----------
    if (curr_tick.triggers.trigger5)
    {
        Serial.print("Steering system reported angle (deg): ");
        Serial.println(steering_system.getSteeringSystemData().angle);
        Serial.print("Steering system status: ");
        Serial.println(static_cast<uint8_t>(steering_system.getSteeringSystemData().status));
        Serial.print("Primary sensor angle: ");
        Serial.println(steering1.convert().angle);
        Serial.print("Secondary sensor angle: ");
        Serial.print(a1.get().conversions[MCU15_STEERING_CHANNEL].conversion);
        Serial.print("  raw: ");
        Serial.println(a1.get().conversions[MCU15_STEERING_CHANNEL].raw);
        Serial.print("Sensor divergence: ");
        Serial.println(steering1.convert().angle - a1.get().conversions[MCU15_STEERING_CHANNEL].conversion);
        Serial.println();
        Serial.println("Pedal outputs:");
        Serial.print("Accel 1 raw: ");
        Serial.println(a1.get().conversions[MCU15_ACCEL1_CHANNEL].raw);
        Serial.print("Accel 2 raw: ");
        Serial.println(a1.get().conversions[MCU15_ACCEL2_CHANNEL].raw);
        Serial.print("Accel percent: ");
        Serial.println(pedals_system.getPedalsSystemDataCopy().accelPercent);
        Serial.print("Brake 1 raw: ");
        Serial.println(a1.get().conversions[MCU15_BRAKE1_CHANNEL].raw);
        Serial.print("Brake 2 raw: ");
        Serial.println(a1.get().conversions[MCU15_BRAKE2_CHANNEL].raw);
        Serial.print("Brake percent: ");
        Serial.println(pedals_system.getPedalsSystemDataCopy().brakePercent);
        Serial.println();
        Serial.print("Derating factor: ");
        Serial.println(ams_interface.get_acc_derate_factor());
        Serial.print("Filtered min cell voltage: ");
        Serial.println(ams_interface.get_filtered_min_cell_voltage());
        Serial.print("Filtered max cell temp: ");
        Serial.println(ams_interface.get_filtered_max_cell_temp());
        Serial.println();

        Serial.println();
    }
    
}





/* -------------------- FUNCTION IMPLEMENTATIONS (see function headers for documentation) -------------------- */
void init_all_CAN_devices()
{
    // Inverter CAN line
    INV_CAN.begin();
    INV_CAN.setBaudRate(INV_CAN_BAUDRATE);
    INV_CAN.setMaxMB(16);
    INV_CAN.enableFIFO();
    INV_CAN.enableFIFOInterrupt();
    INV_CAN.onReceive(on_can2_receive);
    INV_CAN.mailboxStatus();

    // Telemetry CAN line
    TELEM_CAN.begin();
    TELEM_CAN.setBaudRate(TELEM_CAN_BAUDRATE);
    TELEM_CAN.setMaxMB(16);
    TELEM_CAN.enableFIFO();
    TELEM_CAN.enableFIFOInterrupt();
    TELEM_CAN.onReceive(on_can3_receive);
    TELEM_CAN.mailboxStatus();
}

void tick_all_interfaces(const SysTick_s &current_system_tick)
{

    TriggerBits_s t = current_system_tick.triggers;

    if (t.trigger10) // 10Hz
    {
        dashboard.tick10(
            &main_ecu,
            int(fsm.get_state()),
            buzzer.buzzer_is_on(),
            drivetrain.drivetrain_error_occured(),
            torque_controller_mux.getTorqueLimit(),
            ams_interface.get_filtered_min_cell_voltage(),
            a1.get().conversions[MCU15_GLV_SENSE_CHANNEL],
            static_cast<int>(torque_controller_mux.activeController()->get_launch_state()),
            dashboard.getDialMode());

        main_ecu.tick(
            static_cast<int>(fsm.get_state()),
            drivetrain.drivetrain_error_occured(),
            safety_system.get_software_is_ok(),
            static_cast<int>(torque_controller_mux.getDriveMode()),
            static_cast<int>(torque_controller_mux.getTorqueLimit()),
            torque_controller_mux.getMaxTorque(),
            buzzer.buzzer_is_on(),
            pedals_system.getPedalsSystemData(),
            ams_interface.pack_charge_is_critical(),
            dashboard.launchControlButtonPressed());

        front_thermistors_interface.tick(mcu_adc.get().conversions[MCU15_THERM_FL_CHANNEL],
                                         mcu_adc.get().conversions[MCU15_THERM_FR_CHANNEL]);

        PedalsSystemData_s pedals_system_data_copy = pedals_system.getPedalsSystemDataCopy();
        telem_interface.tick(
            a1.get(),
            a2.get(),
            a3.get(),
            steering1.convert(),
            &inv.fl,
            &inv.fr,
            &inv.rl,
            &inv.rr,
            pedals_system_data_copy.accelImplausible,
            pedals_system_data_copy.brakeImplausible,
            pedals_system_data_copy.accelPercent,
            pedals_system_data_copy.brakePercent,
            a1.get().conversions[MCU15_ACCEL1_CHANNEL],
            a1.get().conversions[MCU15_ACCEL2_CHANNEL],
            a1.get().conversions[MCU15_BRAKE1_CHANNEL],
            a1.get().conversions[MCU15_BRAKE2_CHANNEL],
            pedals_system.getMechBrakeActiveThreshold(),
            {});

    }

    if (t.trigger50) // 50Hz
    {
        steering1.sample();
        ams_interface.tick(current_system_tick);
    }

    if (t.trigger100) // 100Hz
    {
        a1.tick();
        a2.tick();
        a3.tick();
        mcu_adc.tick();
        load_cell_interface.tick(
            (LoadCellInterfaceTick_s)
            {
                .FLConversion = a2.get().conversions[MCU15_FL_LOADCELL_CHANNEL],
                .FRConversion = a3.get().conversions[MCU15_FR_LOADCELL_CHANNEL],
                .RLConversion = sab_interface.rlLoadCell.convert(),
                .RRConversion = sab_interface.rrLoadCell.convert()
            }
        );

    }

    main_ecu.read_mcu_status(); // Should be executed at the same rate as state machine.
                                // DO NOT call in main_ecu.tick()
}

void tick_all_systems(const SysTick_s &current_system_tick)
{

    pedals_system.tick(
        current_system_tick,
        a1.get().conversions[MCU15_ACCEL1_CHANNEL],
        a1.get().conversions[MCU15_ACCEL2_CHANNEL],
        a1.get().conversions[MCU15_BRAKE1_CHANNEL],
        a1.get().conversions[MCU15_BRAKE2_CHANNEL]);

    steering_system.tick(
        (SteeringSystemTick_s){
            .tick = current_system_tick,
            .secondaryConversion = a1.get().conversions[MCU15_STEERING_CHANNEL]});

    drivetrain.tick(current_system_tick);

    DrivetrainCommand_s controller_output = case_system.evaluate(
        current_system_tick,
        vn_interface.get_vn_struct(),
        steering_system.getSteeringSystemData(),
        drivetrain.get_dynamic_data(),
        load_cell_interface.getLoadCellForces().loadCellConversions, // should CASE use filtered load cells?
        pedals_system.getPedalsSystemData(),
        0,
        fsm.get_state(),
        dashboard.startButtonPressed(),
        vn_interface.get_vn_struct().vn_status);

    torque_controller_mux.tick(
        current_system_tick,
        drivetrain.get_dynamic_data(),
        pedals_system.getPedalsSystemData(),
        steering_system.getSteeringSystemData(),
        load_cell_interface.getLoadCellForces(),
        dashboard.getDialMode(),
        ams_interface.get_acc_derate_factor(),
        dashboard.torqueModeButtonPressed(),
        vn_interface.get_vn_struct(),
        controller_output);

}

void handle_ethernet_interface_comms()
{
    // function that will handle receiving and distributing of all messages to all ethernet interfaces
    // via the union message. this is a little bit cursed ngl.
    // TODO un fuck this and make it more sane
    // Serial.println("bruh");
    handle_ethernet_socket_receive(&protobuf_recv_socket, &recv_pb_stream_union_msg, ethernet_interfaces);

    // this is just kinda here i know.
    if (param_interface.params_need_sending())
    {
        // Serial.println("handling ethernet");
        auto config = param_interface.get_config();
        if (!handle_ethernet_socket_send_pb(&protobuf_send_socket, config, config_fields))
        {
            // TODO this means that something bad has happend
        }
        param_interface.reset_params_need_sending();
    }

}