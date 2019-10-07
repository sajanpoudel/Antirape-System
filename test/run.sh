#!/bin/sh
# Builds and runs the host side tests for the pure logic in alert_logic.h.
set -e
cd "$(dirname "$0")"
for t in test_*.cpp; do
  [ -e "$t" ] || continue
  g++ -std=c++11 -Wall -Wextra -I.. -o "/tmp/${t%.cpp}" "$t"
  "/tmp/${t%.cpp}"
done
echo "host tests passed"
