/*
  EcoSensePower BasicAdaptiveSensor.

  Minimal dependency-free core runtime example for Arduino users. It demonstrates
  adaptive sampling and compact report output without pulling in profile catalogs,
  Bluetooth/BLE stacks, GPS parsers, WiFi libraries, or external drivers.

  This example is part of the AVR UNO/Nano compact Tiny/Core smoke gate. Full
  ecosystem profile demos target larger boards such as ESP32, SAMD, Mega, Nano 33 BLE,
  Nano ESP32, Portenta, and GIGA.
*/

#include <EcoSensePower.h>
EcoSensePower node;

void setup() {
  Serial.begin(115200);
  node.sensor("soil")
    .read([]() -> float { return (float)analogRead(A0); })
    .minIntervalMs(EcoTime::minutes(5))
    .maxIntervalMs(EcoTime::hours(6))
    .changeThreshold(20.0f);
  node.onReport([](const EcoReport& report) { char reportText[96];
    Serial.println(report.toText(reportText, sizeof(reportText))); });
  node.begin();
}

void loop() { node.loop(); }
