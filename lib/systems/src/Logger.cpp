#include "Logger.h"

#ifdef ARDUINO


void hal_print(const char s[]) { Serial.print(s); }

void hal_println(const char s[]) { Serial.println(s); }

// Don't print more than 256 chars at a time
void hal_printf(const char format[], ...) {
  char buf[1024];
  va_list ap;
  va_start(ap, format);
  vsprintf(buf, format, ap);
  Serial.print(buf);
  va_end(ap);
}

#else

void hal_print(const char s[]) { printf(s); }

void hal_println(const char s[]) { printf("%s\n", s); }

void hal_printf(const char format[], ...) {
  va_list ap;
  va_start(ap, format);
  vprintf(format, ap);
  va_end(ap);
}

#endif
