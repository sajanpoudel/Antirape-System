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

int main() {
  test_accepts_international_numbers();
  test_rejects_numbers_without_a_plus();
  test_rejects_letters_and_symbols();
  test_rejects_numbers_of_the_wrong_length();
  test_rejects_empty_input();
  return 0;
}
