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
RuleBasedAnomalyHook rule;

float readAnalogScore() {
  return (float)analogRead(A0) / 1023.0f;
}

bool anomalyCallback(float score) {
  return rule.anomaly(score);
}

void setup() {
  Serial.begin(115200);
  rule.threshold(0.8f);
  node.sensor("analog-score")
      .read(readAnalogScore)
      .minIntervalMs(EcoTime::minutes(5))
      .maxIntervalMs(EcoTime::hours(3))
      .changeThreshold(0.05f)
      .onAnomaly(anomalyCallback);
  node.begin();
}

void loop() { node.loop(); }
