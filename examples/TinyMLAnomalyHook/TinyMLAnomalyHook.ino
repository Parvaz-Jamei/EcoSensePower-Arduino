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

EcoSensePower node;

float readScore() {
  return (float)analogRead(A0) / 1023.0f;
}

bool isAnomaly(float score) {
  return score > 0.75f;
}

void setup() {
  Serial.begin(115200);
  node.sensor("score")
      .read(readScore)
      .minIntervalMs(EcoTime::minutes(1))
      .maxIntervalMs(EcoTime::hours(1))
      .changeThreshold(0.10f)
      .onAnomaly(isAnomaly)
      .inferenceCost()
        .current_uA(8500)
        .durationMs(40)
        .maxRunsPerDay(200);
  node.onReport([](const EcoReport& report) { Serial.println(report.toText()); });
  node.begin();
}

void loop() { node.loop(); }
