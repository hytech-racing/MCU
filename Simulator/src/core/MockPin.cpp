#include "Arduino.h"
#include "MockPin.h"
#include "HTException.h"

inline bool isInput(int pinMode) { return (pinMode & 1) == INPUT; }

MockPin::MockPin() {}

MockPin::MockPin(int pin) { 
    fPin = pin; 
}

unsigned MockPin::vehicle_read() {
    if (!isInput(fMode))
        throw InvalidPinConfigurationException(fPin, INPUT, fMode);

    if (fInputValue < 0) {
        if (fMode == INPUT_PULLUP) return 1;
        else throw InvalidPinConfigurationException(fPin, INPUT_PULLUP, fMode);
    }
    
    return fInputValue;
}

void MockPin::vehicle_write(unsigned value) {
    if (fMode != OUTPUT)
        throw InvalidPinConfigurationException(fPin, OUTPUT, fMode);
    fOutputValue = value;
}

void MockPin::vehicle_pinMode(int mode) {
    if (fMode != -1)
        throw DoublePinModeException(fPin, fMode, mode);
    fMode = mode;
}

std::string decodePinMode(int mode) {
    switch(mode) {
        case -1: return "__NOT_INITIALIZED__";
        case INPUT: return "INPUT";
        case OUTPUT: return "OUTPUT";
        case INPUT_PULLUP: return "INPUT_PULLUP";
        case RESERVED: return "RESERVED";
    }
    return "__UNEXPECTED VALUE__";
}