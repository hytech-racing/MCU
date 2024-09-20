#ifndef __PRINTLOGGER_H__
#define __PRINTLOGGER_H__
#include <stddef.h>
#include <stdint.h>
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdarg>
#include <stdio.h>
#include <iostream>
#endif

#ifdef ARDUINO
template <typename T>
void logger_println(T out){
    Serial.println(out);
}
#else
template <typename T>
void logger_println(T out){
    std::cout << out<<std::endl;
}
#endif

class RateLimitedLogger
{
    private:
        unsigned long last_out_time_;
    public:
        RateLimitedLogger()
        {
            last_out_time_ = 0;
        }
        
        template <typename T>
        void log_out(T out, unsigned long current_millis, unsigned long period=100) {
            if((current_millis - last_out_time_) > period)
            {
                logger_println<T>(out);
                last_out_time_ = current_millis;
            }
        }
};
#endif // __PRINTLOGGER_H__