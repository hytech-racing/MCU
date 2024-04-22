/* Include files */
/* System Includes*/
#include <Arduino.h>

/* Libraries */
#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include "MCU_rev15_defs.h"

// /* Interfaces */
#include "HytechCANInterface.h"
#include "MCP_ADC.h"
#include "ORBIS_BR10.h"
#include "MCUInterface.h"
#include "AMSInterface.h"
#include "WatchdogInterface.h"
#include "DashboardInterface.h"
#include "InverterInterface.h"
#include "TelemetryInterface.h"
#include "SABInterface.h"
#include "VectornavInterface.h"
#include "LoadCellInterface.h"

/* Systems */
#include "SysClock.h"
#include "Buzzer.h"
#include "SafetySystem.h"
#include "DrivetrainSystem.h"
#include "PedalsSystem.h"
#include "TorqueControllerMux.h"

#include "CASESystem.h"
// /* State machine */
#include "MCUStateMachine.h"
#include "HT08_CASE.h"

/*
    PARAMETER STRUCTS
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
    .glv_sense_channel = MCU15_GLV_SENSE_CHANNEL};

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
    .mechanical_activation_percentage = APPS_ACTIVATION_PERCENTAGE};

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

/*
    DATA SOURCES
*/

/* Two CAN lines on Main ECU rev15 */
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> INV_CAN;   // Inverter CAN (now both are on same line)
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> TELEM_CAN; // telemetry CAN (basically everything except inverters)

/* Set up CAN circular buffer */
// using CircularBufferType = Circular_Buffer<uint8_t, (uint32_t)32, sizeof(CAN_message_t)>;
using CircularBufferType = CANBufferType;

/* Sensors */
MCP_ADC<8> a1 = MCP_ADC<8>(ADC1_CS);
MCP_ADC<4> a2 = MCP_ADC<4>(ADC2_CS, 1000000); // 1M baud needed for 04s
MCP_ADC<4> a3 = MCP_ADC<4>(ADC3_CS, 1000000);

OrbisBR10 steering1(&Serial5);

// /*
//     INTERFACES
// */
VNInterface<CircularBufferType> vn_interface(&CAN3_txBuffer);
DashboardInterface dashboard(&CAN3_txBuffer);
AMSInterface ams_interface(8);
WatchdogInterface wd_interface(32);
MCUInterface main_ecu(&CAN3_txBuffer);
TelemetryInterface telem_interface(&CAN3_txBuffer, telem_read_channels);
SABInterface sab_interface(
    LOADCELL_RL_SCALE,  // RL Scale
    LOADCELL_RL_OFFSET, // RL Offset (Migos)
    LOADCELL_RR_SCALE,  // RR Scale
    LOADCELL_RR_OFFSET  //  RR Offset
);
LoadCellInterface load_cell_interface;

// /* Inverter Interface Type */
using InvInt_t = InverterInterface<CircularBufferType>;
struct inverters
{
    InvInt_t fl = InvInt_t(&CAN2_txBuffer, ID_MC1_SETPOINTS_COMMAND);
    InvInt_t fr = InvInt_t(&CAN2_txBuffer, ID_MC2_SETPOINTS_COMMAND);
    InvInt_t rl = InvInt_t(&CAN2_txBuffer, ID_MC3_SETPOINTS_COMMAND);
    InvInt_t rr = InvInt_t(&CAN2_txBuffer, ID_MC4_SETPOINTS_COMMAND);
} inv;

// /*
//     SYSTEMS
// */

SysClock sys_clock;
SteeringSystem steering_system(&steering1);
BuzzerController buzzer(BUZZER_ON_INTERVAL);

SafetySystem safety_system(&ams_interface, &wd_interface);
// SafetySystem safety_system(&ams_interface, &wd_interface, &dashboard);
PedalsSystem pedals_system(accel_params, brake_params);
using DriveSys_t = DrivetrainSystem<InvInt_t>;
DriveSys_t drivetrain = DriveSys_t({&inv.fl, &inv.fr, &inv.rl, &inv.rr}, &main_ecu, INVERTER_ENABLING_TIMEOUT_INTERVAL);
TorqueControllerMux torque_controller_mux(1.0, 0.4);
// TODO ensure that case uses max regen torque, right now its not
CASEConfiguration case_config = {
    // Following used for generated code
    .AbsoluteTorqueLimit = AMK_MAX_TORQUE, // N-m
    .yaw_pid_p = 1.33369,
    .yaw_pid_i = 0.25,
    .yaw_pid_d = 0.0,
    .tcs_pid_p = 40.0,
    .tcs_pid_i = 0.0,
    .tcs_pid_d = 0.0,
    .useLaunch = false,
    .usePIDTV = true,
    .useTCSLimitedYawPID = true,
    .useNormalForce = false,
    .useTractionControl = true,
    .usePowerLimit = false,
    .usePIDPowerLimit = false,
    .useDecoupledYawBrakes = false,
    .useDiscontinuousYawPIDBrakes = true,
    .tcsSLThreshold = 0.2,
    .launchSL = 0.2,
    .launchDeadZone = 20,        // N-m
    .launchVelThreshold = 0.75,  // m/s
    .tcsVelThreshold = 2.5,      // m/s
    .yawPIDMaxDifferential = 10, // N-m
    .yawPIDErrorThreshold = 0.1, // rad/s
    .yawPIDVelThreshold = 1,     // m/s
    .yawPIDCoastThreshold = 2.5, // m/s
    .yaw_pid_brakes_p = 0.25,
    .yaw_pid_brakes_i = 0,
    .yaw_pid_brakes_d = 0,
    .decoupledYawPIDBrakesMaxDIfference = 2, // N-m
    .discontinuousBrakesPercentThreshold = 0.4,
    .TorqueMode = AMK_MAX_TORQUE, // N-m
    .RegenLimit = -10.0,          // N-m

    // Following used for calculate_torque_request in CASESystem.tpp
    .max_rpm = AMK_MAX_RPM,
    .max_regen_torque = AMK_MAX_TORQUE,
    .max_torque = AMK_MAX_TORQUE,
};
// Torque limit used for yaw pid torque split overflow
// Yaw PID P
// Yaw PID I
// Yaw PID D
// TCS PID P
// TCS PID I
// TCS PID D
// Use launch
// Use PID TV
// Use normal force TV
// Use Traction Control (TCS)
// Use power limit
// Use PID power limit
// TCS activation threshold
// TCS launch SL target
// TCS launch torque deadzone (N-m)
// Max motor rpm
// Max regen torque
// Max torque
CASESystem<CircularBufferType> case_system(&CAN3_txBuffer, 100, 70, case_config);

/* Declare state machine */
MCUStateMachine<DriveSys_t> fsm(&buzzer, &drivetrain, &dashboard, &pedals_system, &torque_controller_mux, &safety_system);

// /*
//     GROUPING STRUCTS (To limit parameter count in utilizing functions)
// */

CANInterfaces<CircularBufferType> CAN_receive_interfaces = {&inv.fl, &inv.fr, &inv.rl, &inv.rr, &vn_interface, &dashboard, &ams_interface, &sab_interface};

/*
    FUNCTION DEFINITIONS
*/

/* Initialize CAN communication */
void init_all_CAN_devices();
/* Tick interfaces */
void tick_all_interfaces(const SysTick_s &current_system_tick);
/* Tick all systems */
void tick_all_systems(const SysTick_s &current_system_tick);
/* Reset inverters */
void drivetrain_reset();

/*
    SETUP
*/

void setup()
{

    // initialize CAN communication
    init_all_CAN_devices();

    SPI.begin();
    a1.init();
    a2.init();
    a3.init();

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

    a2.setChannelScale(MCU15_FL_LOADCELL_CHANNEL, LOADCELL_FL_SCALE /*Todo*/);
    a3.setChannelScale(MCU15_FR_LOADCELL_CHANNEL, LOADCELL_FR_SCALE /*Todo*/);

    a2.setChannelOffset(MCU15_FL_LOADCELL_CHANNEL, LOADCELL_FL_OFFSET /*Todo*/);
    a3.setChannelOffset(MCU15_FR_LOADCELL_CHANNEL, LOADCELL_FR_OFFSET /*Todo*/);

    // get latest tick from sys clock
    SysTick_s curr_tick = sys_clock.tick(micros());

    /*
        Init Interfaces
    */

    main_ecu.init();                      // initial shutdown circuit readings,
    wd_interface.init(curr_tick.millis);  // initialize wd kick time
    ams_interface.init(curr_tick.millis); // initialize last heartbeat time
    steering1.init();
    steering1.setOffset(PRIMARY_STEERING_SENSE_OFFSET);

    Serial.begin(115200);

    /*
        Init Systems
    */

    safety_system.init();

    // Drivetrain set all inverters disabled
    drivetrain.disable(); // write inv_en and inv_24V_en low: writing high in previous code though, should double check
    // would an error list be good for debugging? i.e. which inverter has error

    // ControllerMux set max torque to 20 NM, torque mode to whatever makes most sense
    // Preventing drivers from forgetting to toggle torque mode and end up self-derating at comp
    // Not strictly necessary at the moment, just don't forget
}

void loop()
{
    // Serial.println("test");
    // get latest tick from sys clock
    SysTick_s curr_tick = sys_clock.tick(micros());

    // process received CAN messages
    process_ring_buffer(CAN2_rxBuffer, CAN_receive_interfaces, curr_tick.millis);
    process_ring_buffer(CAN3_rxBuffer, CAN_receive_interfaces, curr_tick.millis);

    // tick interfaces
    tick_all_interfaces(curr_tick);

    // tick systems
    tick_all_systems(curr_tick);

    // inverter procedure before entering state machine
    // reset inverters
    if (dashboard.inverterResetButtonPressed() && drivetrain.drivetrain_error_occured())
    {
        drivetrain.reset_drivetrain();
    }
    // tick state machine
    fsm.tick_state_machine(curr_tick.millis);

    // tick safety system
    safety_system.software_shutdown(curr_tick);

    // send CAN
    send_all_CAN_msgs(CAN2_txBuffer, &INV_CAN);
    send_all_CAN_msgs(CAN3_txBuffer, &TELEM_CAN);
}

/*
    Initialize CAN comm.
*/

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

/*
    TICK INTERFACES
*/

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
            telem_interface.get_glv_voltage(a1.get()),
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

        PedalsSystemData_s data2 = pedals_system.getPedalsSystemDataCopy();

        telem_interface.tick(
            a1.get(),
            a2.get(),
            a3.get(),
            steering1.convert(),
            &inv.fl,
            &inv.fr,
            &inv.rl,
            &inv.rr,
            data2.accelImplausible,
            data2.brakeImplausible,
            data2.accelPercent,
            data2.brakePercent,
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
    }

    if (t.trigger100) // 100Hz
    {

        a1.tick();
        a2.tick();
        a3.tick();
        load_cell_interface.tick(
            (LoadCellInterfaceTick_s){
                .FLConversion = a2.get().conversions[MCU15_FL_LOADCELL_CHANNEL],
                .FRConversion = a3.get().conversions[MCU15_FR_LOADCELL_CHANNEL],
                .RLConversion = sab_interface.rlLoadCell.convert(),
                .RRConversion = sab_interface.rrLoadCell.convert()});
    }
    // // Untriggered
    main_ecu.read_mcu_status(); // should be executed at the same rate as state machine
                                // DO NOT call in main_ecu.tick()
}

// /*
//     TICK SYSTEMS
// */

void tick_all_systems(const SysTick_s &current_system_tick)
{
    // tick pedals system

    // Serial.println("accel1");
    // Serial.println(a1.get().conversions[MCU15_ACCEL1_CHANNEL].raw);
    // Serial.println("accel2");
    // Serial.println(a1.get().conversions[MCU15_ACCEL2_CHANNEL].raw);
    // Serial.println("brake1");
    // Serial.println(a1.get().conversions[MCU15_BRAKE1_CHANNEL].raw);
    // Serial.println("brake2");
    // Serial.println(a1.get().conversions[MCU15_BRAKE2_CHANNEL].raw);

    pedals_system.tick(
        current_system_tick,
        a1.get().conversions[MCU15_ACCEL1_CHANNEL],
        a1.get().conversions[MCU15_ACCEL2_CHANNEL],
        a1.get().conversions[MCU15_BRAKE1_CHANNEL]);

    // tick steering system
    steering_system.tick(
        (SteeringSystemTick_s){
            .tick = current_system_tick,
            .secondaryConversion = a1.get().conversions[MCU15_STEERING_CHANNEL]});

    // Serial.println("Steering angle");
    // Serial.println(steering_system.getSteeringSystemData().angle);
    // Serial.println("Steering status");
    // Serial.println(static_cast<int>(steering_system.getSteeringSystemData().status));

    // tick drivetrain system
    drivetrain.tick(current_system_tick);
    // // tick torque controller mux

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
        3);

    torque_controller_mux.tick(
        current_system_tick,
        drivetrain.get_dynamic_data(),
        pedals_system.getPedalsSystemData(),
        steering_system.getSteeringSystemData(),
        load_cell_interface.getLoadCellForces(),
        dashboard.getDialMode(),
        dashboard.torqueModeButtonPressed(),
        vn_interface.get_vn_struct(),
        controller_output);
}
