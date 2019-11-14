#include "minitest.h"
#include "../alert_logic.h"

static void test_accepts_international_numbers() {
  CHECK(isValidPhoneNumber("+9779811111111"));
  CHECK(isValidPhoneNumber("+97798222222222"));
}


static void test_rejects_numbers_without_a_plus() {
  CHECK(!isValidPhoneNumber("9779811111111"));
}


static void test_rejects_letters_and_symbols() {
  CHECK(!isValidPhoneNumber("+97798abc1111"));
  CHECK(!isValidPhoneNumber("+977 9811111111"));
}


static void test_rejects_numbers_of_the_wrong_length() {
  CHECK(!isValidPhoneNumber("+1234567"));
  CHECK(!isValidPhoneNumber("+1234567890123456"));
  CHECK(isValidPhoneNumber("+12345678"));
  CHECK(isValidPhoneNumber("+123456789012345"));
}


static void test_rejects_empty_input() {
  CHECK(!isValidPhoneNumber(""));
  CHECK(!isValidPhoneNumber("+"));
  CHECK(!isValidPhoneNumber(0));
}


static void test_builds_the_sms_command() {
  char buffer[40];
  CHECK(buildSmsCommand("+9779811111111", buffer, sizeof(buffer)));
  CHECK(strcmp(buffer, "AT+CMGS=\"+9779811111111\"") == 0);
}


static void test_sms_command_needs_enough_room() {
  char buffer[10];
  CHECK(!buildSmsCommand("+9779811111111", buffer, sizeof(buffer)));
}


static void test_call_goes_to_the_last_contact() {
  CHECK(callIndex(5) == 4);
  CHECK(callIndex(1) == 0);
  CHECK(callIndex(0) == -1);
}

static void test_first_alert_is_always_allowed() {
  CHECK(canStartAlert(false, 0, 0, 120000));
}


static void test_alert_waits_for_the_cooldown() {
  CHECK(!canStartAlert(true, 119999, 0, 120000));
  CHECK(canStartAlert(true, 120000, 0, 120000));
}


static void test_cooldown_survives_the_millis_rollover() {
  uint32_t last = 0xFFFFFF00UL;
  CHECK(!canStartAlert(true, 0x00000100UL, last, 120000));
  CHECK(canStartAlert(true, 0x0001FFFFUL, last, 120000));
}


static void test_alert_message_contains_the_link() {
  char out[160];
  CHECK(buildAlertMessage("https://maps.example/1", out, sizeof(out)));
  CHECK(strstr(out, "https://maps.example/1") != 0);
  CHECK(strstr(out, "RESCUE") != 0);
}


static void test_alert_message_without_a_link_says_unknown() {
  char out[160];
  CHECK(buildAlertMessage("", out, sizeof(out)));
  CHECK(strstr(out, "unknown") != 0);
  CHECK(buildAlertMessage(0, out, sizeof(out)));
}


static void test_alert_message_needs_a_big_enough_buffer() {
  char out[10];
  CHECK(!buildAlertMessage("https://maps.example/1", out, sizeof(out)));
}


static void test_response_ok_is_found_in_the_text() {
  CHECK(responseIsOk("AT+CMGF=1\r\r\nOK\r\n"));
  CHECK(!responseIsOk("ERROR"));
  CHECK(!responseIsOk(""));
  CHECK(!responseIsOk(0));
}


int main() {
  test_accepts_international_numbers();
  test_rejects_numbers_without_a_plus();
  test_rejects_letters_and_symbols();
  test_rejects_numbers_of_the_wrong_length();
  test_rejects_empty_input();
  test_builds_the_sms_command();
  test_sms_command_needs_enough_room();
  test_call_goes_to_the_last_contact();
  test_alert_message_contains_the_link();
  test_alert_message_without_a_link_says_unknown();
  test_alert_message_needs_a_big_enough_buffer();
  test_response_ok_is_found_in_the_text();
  test_first_alert_is_always_allowed();
  test_alert_waits_for_the_cooldown();
  test_cooldown_survives_the_millis_rollover();
  return 0;
}
