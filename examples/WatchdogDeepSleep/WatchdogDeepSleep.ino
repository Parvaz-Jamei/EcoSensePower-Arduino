/*
  EcoSensePower example.

  This sketch demonstrates energy budgeting, adaptive duty-cycle behavior, sleep planning,
  diagnostics, or confidence-bounded profiles. It is not a replacement for sensor drivers,
  radio protocol stacks, WiFi/BLE managers, GPS parsers, or a navigation framework.

  Default examples are dependency-free unless this file explicitly says otherwise. Real
  BLE communication needs an optional user-side library such as ArduinoBLE on supported
  boards. Real GPS/NMEA parsing needs an optional user-side parser such as TinyGPSPlus
  or Adafruit GPS.

  AVR UNO/Nano use compact Tiny/Core mode. Full ecosystem profile demos are intended for
  capable boards such as ESP32, SAMD, Mega, Nano 33 BLE, Nano ESP32, Portenta, GIGA,
  and similar boards with more SRAM/flash.
*/

#include <EcoSensePower.h>
#include <arch/avr/WatchdogSleepHelper.h>
#include <profiles/batteries/nimh_aaa.h>
#include <profiles/boards/arduino_pro_mini_3v3.h>

void setup() {
  Serial.begin(115200);
  EcoSensePower node;
  node.battery(EcoProfiles::NiMHAAA()).board(EcoProfiles::ArduinoProMini3V3());
  Serial.println(F("Approximate watchdog sleep helper demo. Timing is approximate and AVR-only on hardware."));
}

void loop() {
  WatchdogSleepHelper::sleepForApprox(EcoTime::seconds(1));
}
