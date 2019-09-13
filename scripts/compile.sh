#!/bin/sh
# Compiles the server box sketch for an Arduino Mega with arduino-cli.
# Needs the RadioHead and LiquidCrystal libraries (arduino-cli lib install RadioHead LiquidCrystal).
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TMP="$(mktemp -d)"
mkdir -p "$TMP/Antirape-watch"
cp "$ROOT"/*.ino "$TMP/Antirape-watch/"
cp "$ROOT"/*.h "$TMP/Antirape-watch/" 2>/dev/null || true
arduino-cli compile --fqbn "${FQBN:-arduino:avr:mega}" "$TMP/Antirape-watch" > /dev/null
rm -rf "$TMP"
echo "sketch compiles"
