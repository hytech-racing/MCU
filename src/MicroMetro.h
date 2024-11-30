#ifndef MicroMetro_h
#define MicroMetro_h
#include "Arduino.h"

#include <inttypes.h>

class MicroMetro
{
public:
    // Constructor to initialize the timing interval
    MicroMetro(unsigned long long interval_micros) {
        this->autoreset = 0;
        interval(interval_micros);
        reset();
    }

    // Constructor with autoreset behavior
    MicroMetro(unsigned long long interval_micros, uint8_t autoreset) {
        this->autoreset = autoreset;
        interval(interval_micros);
        reset();
    }

    // Set the interval time in microseconds
    void interval(unsigned long long interval_micros) {
        this->interval_micros = interval_micros;
    }

    // Check if the interval has passed
    char check() {
        if (micros() - this->previous_micros >= this->interval_micros) {
            if (this->interval_micros <= 0 || this->autoreset) {
                this->previous_micros = micros();
            } else {
                this->previous_micros += this->interval_micros; 
            }
            return 1; // Indicate that the interval has passed
        }
        return 0; // Indicate that the interval has not passed
    }

    // Reset the timer to the current microseconds
    void reset() {
        this->previous_micros = micros();
    }

private:
    uint8_t autoreset; // Determines the autoreset behavior
    unsigned long long previous_micros; // Previous recorded time
    unsigned long long interval_micros; // Interval time in microseconds
};

#endif