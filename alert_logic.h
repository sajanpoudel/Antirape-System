#ifndef ALERT_LOGIC_H
#define ALERT_LOGIC_H

#include <stdint.h>
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

// Builds the AT command that starts an SMS to a number, for example AT+CMGS="+977...".
// Returns false when the buffer is too small.
inline bool buildSmsCommand(const char* number, char* out, size_t size) {
  const char* prefix = "AT+CMGS=\"";
  size_t needed = strlen(prefix) + strlen(number) + 2;  // closing quote and the terminator
  if (size < needed) return false;
  strcpy(out, prefix);
  strcat(out, number);
  strcat(out, "\"");
  return true;
}

// Which contact the alert calls: the last registered one.
inline int callIndex(int contactCount) {
  return contactCount > 0 ? contactCount - 1 : -1;
}

// True when a new alert may start: none has run yet, or the cooldown since the last one is over.
// The counters are 32 bit like millis() on an Uno and may wrap around.
inline bool canStartAlert(bool hasAlerted, uint32_t now, uint32_t lastAlertAt, uint32_t cooldownMs) {
  if (!hasAlerted) return true;
  return (uint32_t)(now - lastAlertAt) >= cooldownMs;
}

#endif
