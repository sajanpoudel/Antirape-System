#include "minitest.h"
#include "../alert_logic.h"

static void test_accepts_international_numbers() {
  CHECK(isValidPhoneNumber("+9779811111111"));
  CHECK(isValidPhoneNumber("+97798222222222"));
}

int main() {
  test_accepts_international_numbers();
  return 0;
}
