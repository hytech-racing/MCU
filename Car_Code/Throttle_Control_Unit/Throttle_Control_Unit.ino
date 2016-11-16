#include <FlexCAN.h> // import teensy library
#include <Metro.h>

//ports
#define BRAKE_ANALOG_PORT 3 //analog port of brake sensor
#define THROTTLE_PORT_1 6 //first throttle sensor port
#define THROTTLE_PORT_2 9 //second throttle sensor port
// TODO: These values need to be determined from testing
//constants
#define MIN_THROTTLE_1 0//compare pedal travel
#define MAX_THROTTLE_1 1024
#define MIN_THROTTLE_2 0
#define MAX_THROTTLE_2 1024
#define MIN_BRAKE 0
#define MAX_BRAKE 1024

//Description of Throttle Control Unit
//Senses the angle of each pedal to determine safely how much torque the motor controller should produce with the motor
//Reads a signal from the Brake System Plausibility Device located on the same board to sense if the BSPD has detected a fault.

FlexCAN CAN(500000);
static CAN_message_t msg;

int voltageThrottlePedal1 = 0; //voltage of 1st throttle
int voltageThrottlePedal2 = 0; //voltage of 2nd throttle
int voltageBrakePedal = 0;//voltage of brakepedal

// additional values to report
bool implausibilityStatus = false; // for pedal not brake
bool throttleCurve = false; // false -> normal, true -> boost
float thermTemp = 0.0; // temperature of onboard thermistor
bool brakePlausibility = false; // fault if BSPD signal too low - still to be designed
bool brakePedalActive = false; // true if brake is considered pressed

//FSAE requires that torque be shut off if an implausibility persists for over 100 msec (EV2.3.5).
//A deviation of more than 10% pedal travel between the two throttle sensors
//A failure of position sensor wiring which can cause an open circuit, short to ground, or short to sensor power.
bool torqueShutdown = false; //

// FUNCTION PROTOTYPES
void readValues();
bool checkDeactivateTractiveSystem();
int sendCanUpdate();

//TCU states
enum TCU_STATE{
    INITIAL_POWER,
    SHUTDOWN_CIRC_INIT,
    TS_ACTIVE,
    TS_NOT_ACTIVE,
    INVERTER_ENABLE,
    RTD_WAIT,
    RTD
} state;
byte stateOutput;

// timer
Metro stateTimer = Metro(500); // Used for how often to send state
Metro updateTimer = Metro(500); // Read in values from pins
Metro implausibilityTimer = Metro(50); // Used for throttle error check
Metro throttleTimer = Metro(500); // Used for sending commands to Motor Controller

// setup code
void setup() {
    Serial.begin(115200); // init serial for PC communication

    CAN.begin(); // init CAN system
    Serial.println("CAN system and serial communication initialized");
    //To detect an open circuit
    //enable the pullup resistor on the Teensy input pin >>>
    pinMode(BRAKE_ANALOG_PORT, INPUT_PULLUP);
    pinMode(THROTTLE_PORT_1, INPUT_PULLUP);
    pinMode(THROTTLE_PORT_2, INPUT_PULLUP);
    //open circuit will show a high signal outside of the working range of the sensor.
    state = INITIAL_POWER;
    stateOutput = 1;
}


//FSAE requires that torque be shut off if an implausibility persists for over 100 msec (EV2.3.5).
    //A deviation of more than 10% pedal travel between the two throttle sensors
    //A failure of position sensor wiring which can cause an open circuit, short to ground, or short to sensor power.

    //To detect a position sensor wiring failure
    //find the ranges of values coming from each sensor during normal operation of the foot pedals
    //Any values outside of these ranges could be caused by an open circuit, short to ground, or short to sensor power.

void loop() {
    if (updateTimer.check()) {
        readValues();
        updateTimer.reset();
    }
    if (implausibilityTimer.check()) {
        checkDeactivateTractiveSystem();
        implausibilityTimer.reset();
    }
    if(stateTimer.check()){
        sendCanUpdate();
        stateTimer.reset();
    }
    switch(state) {
        //TODO: check if reqs are met to move to each state
        case INITIAL_POWER:
            stateOutput = 1;
            state = SHUTDOWN_CIRC_INIT;
            break;
        case SHUTDOWN_CIRC_INIT:
            stateOutput = 2;
            state = TS_ACTIVE;
            break;
        case TS_ACTIVE:
            stateOutput = 3;
            state = INVERTER_ENABLE;
            break;
        case INVERTER_ENABLE:
            stateOutput = 4;
            state = RTD_WAIT;
            break;
        case RTD_WAIT:
            stateOutput = 5;
            state = RTD;
            break;
        case RTD:
            stateOutput = 6;
            readValues();
            checkDeactivateTractiveSystem();
            break;
    }
}
    //Error Message Instructions
    //an error message should be sent out on CAN Bus detailing which implausibility has been detected.
    //periodically sent until the implausibility ceases to exist.
    //If the implausibility ceases, a corresponding message should be sent on CAN Bus.
    //If an implausibility ceases to be detected, normal throttle controls should be reinstated
    //i.e. the vehicle does not need to be restarted to reset an implausibility fault.
/*
int giveError(int errorID) {
   CAN.write(errorID)
   return 1; //placeholder
}
*/
void readValues() {
    voltageThrottlePedal1 = analogRead(THROTTLE_PORT_1);
    voltageThrottlePedal2 = analogRead(THROTTLE_PORT_2);
    voltageBrakePedal = analogRead(BRAKE_ANALOG_PORT);
    //TODO: decide/set torque values for input values
}

bool checkDeactivateTractiveSystem() {
    // Check for errors - AKA implausibility checking
    // Throttle 10% check
    float deviationCheck = ((float) voltageThrottlePedal1) / ((float) voltageThrottlePedal2);
    if (deviationCheck > 1.10 || (1 / deviationCheck) > 1.10) {
        // TODO: implausibility
    }
    // Checks for failure of position sensor wiring
    // Check for open circuit or short to ground
    if (voltageThrottlePedal1 < MIN_THROTTLE_1 || voltageThrottlePedal2 < MIN_THROTTLE_2) {
        //TODO: implausibility
    }
    // Check for short to power
    if (voltageThrottlePedal1 > MAX_THROTTLE_1 || voltageThrottlePedal2 > MAX_THROTTLE_2) {
        //TODO: implausibility
    }
    // Check brake pedal sensor
    if (voltageBrakePedal > MAX_BRAKE || voltageBrakePedal < MIN_BRAKE) {
        //TODO: implausibility
    }
    return true;
}

void checkBrakeImplausibility() {
    // TODO: TCU should read in signal from BSPD
    // Fault occurs when signal is too low
    // NOT when fault on brake pedal sensor
}

int sendCanUpdate(){
    short shortThrottle1 = (short) voltageThrottlePedal1 * 100;
    short shortThrottle2 = (short) voltageThrottlePedal2 * 100;
    short shortBrake = (short) voltageBrakePedal * 100;
    short shortTemp = (short) thermTemp * 100;

    msg.id = 0x30;
    msg.len = 8;
    
    memcpy(&msg.buf[0], &shortThrottle1, sizeof(short));
    memcpy(&msg.buf[2], &shortThrottle2, sizeof(short));
    memcpy(&msg.buf[4], &shortBrake, sizeof(short));
    memcpy(&msg.buf[6], &shortTemp, sizeof(short));

    int temp1 = CAN.write(msg);

    byte statuses = stateOutput;
    
    if(implausibilityStatus) statuses += 16;
    if(throttleCurve) statuses += 32;
    if(brakePlausibility) statuses += 64;
    if(brakePedalActive) statuses += 128;

    msg.id = 0x31;
    msg.len = 1;
    msg.buf[0] = statuses;
    
    int temp2 = CAN.write(msg);
    
    return temp1 + temp2;
}