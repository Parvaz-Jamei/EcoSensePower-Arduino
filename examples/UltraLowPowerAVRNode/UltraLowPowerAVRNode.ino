/*
  EcoSensePower UltraLowPowerAVRNode.

  AVR-focused compact Tiny/Core example. It demonstrates guarded sensor power control
  and conservative sleep/backend behavior without enabling the full profile catalog,
  full diagnostics storage, Bluetooth/BLE stacks, GPS parsers, or external libraries.

  This example is part of the AVR UNO/Nano smoke gate. It intentionally enables one
  guard slot before including EcoSensePower so node.guard("avr-sensor-power") is active
  while keeping everything else tiny.
*/

#ifndef ECOSENSE_MAX_GUARDS
#define ECOSENSE_MAX_GUARDS 1
#endif
#include <EcoSensePower.h>

EcoSensePower node;

const uint8_t SENSOR_POWER_PIN = 7;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  digitalWrite(SENSOR_POWER_PIN, LOW);

  node.board(BoardProfile::ArduinoUnoPlaceholder());
  node.battery(BatteryProfile::AA_Alkaline(2400));

  node.guard("avr-sensor-power")
    .powerPin(SENSOR_POWER_PIN)
    .activeLevel(HIGH)
    .warmupTimeMs(20);

  node.sensor("avr-node")
    .read([]() -> float {
      return (float)analogRead(A0);
    })
    .minIntervalMs(EcoTime::seconds(10))
    .maxIntervalMs(EcoTime::minutes(2))
    .changeThreshold(15.0f)
    .onSleep([]() {});

  node.onReport([](const EcoReport& report) {
    char reportText[96];
    Serial.println(report.toText(reportText, sizeof(reportText)));
  });

  node.begin();
  Serial.print(F("EcoSensePower backend: "));
  Serial.println(node.backendName());
  node.printDiagnostics(Serial);
  Serial.println(F("AVR Phase 2: conservative idle sleep by default; optional power-down is compile-flag controlled."));
  Serial.println(F("Measure real current before battery-life claims."));
}

void loop() {
  node.loop();
}
