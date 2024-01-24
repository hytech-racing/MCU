/* Prototype main function for logic soothing */

/* Include files */
#include <Arduino.h>
#include "TeensyTimerTool.h"

#include "MCU_rev15_defs.h"

#include "AnalogSensorsInterface.h"
#include "MCP3208.h"
#include "SteeringEncoderInterface.h"
#include "ORBIS_BR10.h"
#include "MCUStateMachine.h"
#include "InverterInterface.h"

#include "PedalsSystem.h"
#include "SteeringSystem.h"
#include "DrivetrainSystem.h"
#include "InverterSystem.h"

#include "HytechCANInterface.h"
#include "FlexCAN_T4.h"
#include "MessageHandler.h"

// Hardware/Interfaces
DashboardInterface dashboardInterface();
// InverterInterface fl_inv;
// InverterInterface fr_inv;
// InverterInterface rl_inv;
// InverterInterface rr_inv;
MCP3208 ADC1(ADC1_CS);
OrbisBR10 OrbisBR10(STEERING_SERIAL);

// Systems
BuzzerController buzzer(500);
// DrivetrainSystem drivetrain({&lf_inv, &rf_inv, &lr_inv, &rr_inv}, 5000);
// MCUStateMachine state_machine(&buzzer, &drivetrain, &dashboardInterface);
PedalsSystem pedalsSystem;
SteeringSystem steeringSystem;

// Data
AnalogConversionPacket_s<MCP3208_NUM_CHANNELS> ADC1Output;
SteeringEncoderConversion_s steeringEncoderOutput;
PedalsSystemOutput_s pedalsSystemOutput;
SteeringSystemOutput_s steeringSystemOutput;

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> FRONT_INV_CAN;
CAN_message_t msg;
MessageHandler<FlexCAN_T4_Base, CAN_message_t> msg_writer(&FRONT_INV_CAN, &msg, 100, millis());

using namespace TeensyTimerTool;
PeriodicTimer kiloTimer;
bool kiloBusy;
long kiloCounter;
void kiloCallback();

void setup()
{
    // drivetrain.give_inverters();
    FRONT_INV_CAN.begin();
    FRONT_INV_CAN.setBaudRate(500000);
    FRONT_INV_CAN.setMaxMB(16);
    FRONT_INV_CAN.enableFIFO();
    FRONT_INV_CAN.enableFIFOInterrupt();
    FRONT_INV_CAN.onReceive(on_can2_receive);
    FRONT_INV_CAN.mailboxStatus();

    kiloBusy = false;
    kiloCounter = 0;
    kiloTimer.begin(kiloCallback, 1'000);
}

// do not use
void loop()
{
    
}

/// @brief 1hz periodic function
void callback1()
{

}

/// @brief 10hz periodic function
void callback10()
{

}

/// @brief 100hz periodic function
void callback100()
{
    // Sample Sensors
    ADC1.sample();
    OrbisBR10.sample();

    // Convert Sensors
    ADC1Output = ADC1.convert();
    steeringEncoderOutput = OrbisBR10.convert();

    // Process Systems
    pedalsSystemOutput = pedalsSystem.evaluate(
        &ADC1Output.conversions[MCU15_ACCEL1_CHANNEL],
        &ADC1Output.conversions[MCU15_ACCEL2_CHANNEL],
        &ADC1Output.conversions[MCU15_BRAKE1_CHANNEL],
        &ADC1Output.conversions[MCU15_BRAKE2_CHANNEL]
    );
    steeringSystemOutput = steeringSystem.evaluate(
        &steeringEncoderOutput,
        &ADC1Output.conversions[MCU15_STEERING_CHANNEL]
    );
}

/// @brief 1khz primary periodic function
void kiloCallback()
{
    if (!kiloBusy)
    {
        kiloBusy = true; // Do not allow kiloCallback to be interrupted by itself

        // Do 1khz stuff here
        AllMsgs received_can_msgs;
        process_ring_buffer(received_can_msgs, CAN1_rxBuffer);
        process_ring_buffer(received_can_msgs, CAN2_rxBuffer);
        process_ring_buffer(received_can_msgs, CAN3_rxBuffer);

        if(std::get<0>(received_can_msgs.dashboard_status)){
            // dash.receive(std::get<1>(received_can_msgs.dashboard_status));
        }
        
        msg_writer.handle_sending(millis());
        // msg_writer.test();
        // state_machine.get_state();
        
        // Callback chain
        if (kiloCounter % 10 == 0)
            callback100();
        if (kiloCounter % 100 == 0)
            callback10();
        if (kiloCounter % 1000 == 0)
            callback1();
        kiloCounter++;
        kiloBusy = false;
    }
}