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
#include <harvester/HarvesterBase.h>

EcoSensePower node;
NullHarvester harvester;

void setup() {
  Serial.begin(115200);

  node.sensor("harvest-demo")
    .read([]() -> float { return (float)analogRead(A0); })
    .minIntervalMs(EcoTime::seconds(5))
    .maxIntervalMs(EcoTime::minutes(1))
    .changeThreshold(15.0f);

  node.onReport([](const EcoReport& report) {
    Serial.println(report.toText());
    Serial.print(F("Harvester available: "));
    Serial.println(harvester.available() ? F("yes") : F("no"));
    Serial.print(F("Input power estimate mW: "));
    Serial.println(harvester.inputPowerMilliWatt());
  });

  node.begin();
  node.printDiagnostics(Serial);
}

void loop() {
  node.loop();
}
