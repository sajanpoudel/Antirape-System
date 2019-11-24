#include "minitest.h"
#include "../alert_logic.h"

static void test_accepts_international_numbers() {
  CHECK(isValidPhoneNumber("+9779811111111"));
  CHECK(isValidPhoneNumber("+97798222222222"));
}


static void test_rejects_numbers_without_a_plus() {
  CHECK(!isValidPhoneNumber("9779811111111"));
}

int main() {
  test_accepts_international_numbers();
  test_rejects_numbers_without_a_plus();
  return 0;
}
