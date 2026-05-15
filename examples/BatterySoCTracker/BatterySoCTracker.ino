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

float readBatteryVoltage() {
  return 3.85f; // Application-owned voltage divider / ADC conversion.
}

void setup() {
  Serial.begin(115200);
  node.battery(BatteryProfile::LiPo_1S(1000));
  node.socTracker()
      .initialSocPercent(80.0f)
      .voltageReader(readBatteryVoltage);

  EcoPowerReport p = node.powerReport();
  Serial.print(F("SoC estimate: "));
  Serial.println(p.socPercent);
  Serial.print(F("SoC confidence: "));
  Serial.println(ecoProfileConfidenceName(p.socConfidence));
}

void loop() {}
