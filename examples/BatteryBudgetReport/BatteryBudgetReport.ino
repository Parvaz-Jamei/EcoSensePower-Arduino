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

void setup() {
  Serial.begin(115200);
  node.battery(BatteryProfile::AA_Alkaline(2400));
  node.board(BoardProfile::Generic());

  node.sensor("battery-demo")
    .read([]() -> float {
      return (float)analogRead(A0);
    })
    .warmupTimeMs(10)
    .minIntervalMs(EcoTime::seconds(1))
    .maxIntervalMs(EcoTime::minutes(1))
    .changeThreshold(5.0f)
    .maxDailyEnergy_mJ(25000UL)
    .onSleep([]() {});

  node.onReport([](const EcoReport& report) {
    Serial.println(report.toText());
  });

  node.begin();
  node.printDiagnostics(Serial);
}

void loop() {
  node.loop();
  static bool printed = false;
  if (!printed && millis() > EcoTime::seconds(3)) {
    node.ledger().printCycleTo(Serial);
    node.ledger().printTotalTo(Serial);
    Serial.println(F("Battery estimate assumptions: no regulator current, no sensor leakage, no radio payload current."));
    printed = true;
  }
}
