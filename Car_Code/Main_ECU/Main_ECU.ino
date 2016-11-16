#include <FlexCAN.h> // import teensy library
#include <Metro.h>

#define BMS_FAULT (1<<0)
#define IMD_FAULT (1<<1)
#define BSPD_FAULT (1<<2)

#define THERMISTORNOMINAL 10000
#define TEMPERATURENOMINAL 25
#define BCONSTANT 3900
#define SERIESRESISTOR 10000

// Values to check if IMD, BMS high
#define IMD_High 50
#define BMS_High 50

// Pins
#define OKHS_PIN 0
#define BMS_OK_PIN 1
#define THERMISTOR_PIN 4
#define SHUTDOWN_SSR_PIN 11
#define LATCH_SSR_PIN 10
#define BRAKE_LIGHT_PIN 13

#define STATE_MESSAGE_ID 0xD0

FlexCAN CAN(500000);
static CAN_message_t msg;
float OKHS = 0; // voltage after calculation
float DISCHARGE_OK = 0; // voltage after calculation
float GLVbattery = 0; // voltage after calculation
float shutdownCircuit = 0; // voltage after calculation
bool OKHSfault = false; // fault status of OKHS, fault if true
bool DISCHARGE_OKfault = false; // fault status of DISCHARGE_OK, fault if true
bool startPressed = false; // true if start button is pressed
float thermTemp = 0.0; // temperature of onboard thermistor (after calculation)
int thermValue = 0; //raw value from thermistor
bool startupDone = false; // true when reached drive state


// timer
Metro updateTimer = Metro(500);
Metro AIRtimer = Metro(500);
Metro FAKE_DRIVER_BUTTON_PRESS = Metro(3000);


enum State { GLVinit=0, waitIMDBMS, waitDriver, AIRClose, fatalFault, drive }; // NOTE: change and update
State curState = GLVinit; // curState is current state

//FUNCTION PROTOTYPES
bool readValues();
bool checkFatalFault();
bool sendCanMessage(int, int, int);
int sendCanUpdate();

//State Ouptuts for CAN Messages
byte stateOutput;


// setup code
void setup() {
    Serial.begin(115200); // init serial for PC communication

    // Set up SSR output pins
    pinMode(SHUTDOWN_SSR_PIN, OUTPUT);
    pinMode(LATCH_SSR_PIN, OUTPUT);
    pinMode(BRAKE_LIGHT_PIN, OUTPUT);

    CAN.begin(); // init CAN system
    Serial.println("CAN system and serial communication initialized");
    curState = GLVinit; // curState is current state
    Serial.println("Current state is GLVinit");
    startPressed = 0;
}

// loop code
void loop() {
    readValues();
    checkFatalFault();
    Serial.print("TEMPERATURE: ");
    Serial.println(thermTemp);
    Serial.print("OKHS: ");
    Serial.println(OKHS);
    Serial.print("BMS: ");
    Serial.println(DISCHARGE_OK);
    Serial.println(thermValue);

    /*
     * Handle incoming CAN messages
     */
    while (CAN.read(msg)) {
      if (msg.id > 0xBF) {
        Serial.print(msg.id, HEX);
        Serial.print(": ");
        for (unsigned int i = 0; i < msg.len; i++) {
          Serial.print(msg.buf[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
      }

      // Scanning CAN for dashboard state message (start button)
      // Change values based on what message actually is
      if (curState == waitDriver && msg.id == STATE_MESSAGE_ID) {
        Serial.println(msg.buf[0], BIN);
        if (msg.buf[0] & 0x10) {
          startPressed = 1;
        }
      }
    }
    
    //check CAN for a message for software shutdown
    if (!startupDone) {
        switch (curState) {
            case GLVinit:
                stateOutput = 0b00000000;
                curState = waitIMDBMS; //going straight to waitIMD unti further notice
                break;
            case waitIMDBMS:
                stateOutput = 0b00000001;
                if (DISCHARGE_OK >= BMS_High) { // if BMS is high
                    if (OKHS >= IMD_High) { // if IMD is also high
                        curState = waitDriver; // both BMD and IMD are high, wait for start button press
                    }
                }
                break;
            case waitDriver:
                stateOutput = 0b00000010;
                /*can message for start button press received*/
                 
                if (startPressed || FAKE_DRIVER_BUTTON_PRESS.check()) {
                    AIRtimer.reset();
                    digitalWrite(SHUTDOWN_SSR_PIN, HIGH);   // close Shutoff SSR (Software Switch)
                    digitalWrite(LATCH_SSR_PIN, HIGH);      // close latch SSR
                    curState = AIRClose;
                }
                break;
            case AIRClose: // equivalent to VCCAIR in Google Doc state diagram
                stateOutput = 0b00000100;
                if(AIRtimer.check()){
                    if (!(curState == fatalFault)) {
                        digitalWrite(LATCH_SSR_PIN, LOW);  // Open latch SSR
                        curState = drive;
                    }
                }
                startPressed = false;
                break;
            case fatalFault:
                stateOutput = 0b00001000;
                break;
            case drive:
                stateOutput = 0b00010000;
                break;
            //send can message to throttle control
        }
    } else {
    }

    if(updateTimer.check()){
      sendCanUpdate();
      updateTimer.reset();
    }
}

bool readValues() {
    DISCHARGE_OK = analogRead(BMS_OK_PIN)/ 67.7;
    OKHS = analogRead(OKHS_PIN) / 67.7;
    thermValue = analogRead(THERMISTOR_PIN);
    //compute actual temperature with math
    float resistance = (5.0 * SERIESRESISTOR * 1023) / (3.3 * thermValue) - SERIESRESISTOR;
//    Serial.println(resistance);
    thermTemp = resistance / THERMISTORNOMINAL;
    thermTemp = log(thermTemp);
    thermTemp /= BCONSTANT;
    thermTemp += 1.0 / (TEMPERATURENOMINAL + 273.15);
    thermTemp = 1.0 / thermTemp;
    thermTemp -= 273.15;  
    return true;

}

bool checkFatalFault() { // returns true if fatal fault found 
    CAN_message_t faultMsg;
    faultMsg.buf[0] = 0;
    if (OKHS >= IMD_High) {
        faultMsg.buf[0] = faultMsg.buf[0] | IMD_FAULT;
    } else if (DISCHARGE_OK >= BMS_High) {
        faultMsg.buf[0] = faultMsg.buf[0] | BMS_FAULT;
    }
        
    while (CAN.read(msg)) {
        if (msg.id == 0x0001) {
            faultMsg.buf[0] = faultMsg.buf[0] | BSPD_FAULT;
        }
    }
    

    if (faultMsg.buf[0] != 0) {
        digitalWrite(SHUTDOWN_SSR_PIN, LOW);
        curState = fatalFault;
        faultMsg.id = 0x0002;
        faultMsg.len = 1;
        CAN.write(faultMsg);
        return true;
    } else {
        return false;
    }
}

bool sendCanMessage(int address, int msgLength, int data){
  
}

int sendCanUpdate(){

    //prepare to send the voltages as shorts in the CAN message
    short shortDischargeOk = (short) (DISCHARGE_OK * 10);
    short shortOKHS = (short) (OKHS * 10);
    short shortGLV = (short) (GLVbattery * 10);
    short shortShutdown = (short) (shutdownCircuit * 10);

    //send the message
    msg.id = 0x50;
    msg.len = 8;
    memcpy(&msg.buf[0], &shortDischargeOk, sizeof(short));
    memcpy(&msg.buf[2], &shortOKHS, sizeof(short));
    memcpy(&msg.buf[4], &shortGLV, sizeof(short));
    memcpy(&msg.buf[6], &shortShutdown, sizeof(short));

    int temp1 = CAN.write(msg);

    bool okhsCheck = OKHS >= IMD_High;
    bool dischargeCheck = DISCHARGE_OK >= BMS_High;
    short shortTemp = (short) thermTemp * 100;
    
    msg.id = 0x51;
    msg.len = 5;
    memcpy(&msg.buf[0], &shortTemp, sizeof(short));
    memcpy(&msg.buf[2], &okhsCheck, sizeof(bool));
    memcpy(&msg.buf[3], &dischargeCheck, sizeof(bool));
    memcpy(&msg.buf[4], &stateOutput, sizeof(byte));

    int temp2 = CAN.write(msg);

    return temp1 + temp2;
}
