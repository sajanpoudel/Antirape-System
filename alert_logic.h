#ifndef ALERT_LOGIC_H
#define ALERT_LOGIC_H

#include <string.h>

// Pure helpers for the server box. They avoid Arduino types so they can run in host tests.

// True for international phone numbers such as +9779811111111: a plus sign followed by
// 8 to 15 digits.
inline bool isValidPhoneNumber(const char* number) {
  if (number == 0 || number[0] != '+') return false;
  size_t digits = strlen(number) - 1;
  if (digits < 8 || digits > 15) return false;
  for (size_t i = 1; number[i] != '\0'; i++) {
    if (number[i] < '0' || number[i] > '9') return false;
  }
  return true;
}

#endif
