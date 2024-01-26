// simple shared printing to allow us to make different loggers.
// allows for simple switching between std::cout and Serial.println() depending on
// platform

#ifndef LOGGER
#define LOGGER

#include <stddef.h>
#include <stdint.h>

// This is really weird, I might just get rid of HAL.
// The original purpose was for testing on native, but
// tbh it's just easier to test with a teensy.
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdarg>
#include <stdio.h>
#include <iostream>
#endif


void hal_print(const char s[]);
void hal_println(const char s[]);
void hal_printf(const char format[], ...);

#endif /* LOGGER */
