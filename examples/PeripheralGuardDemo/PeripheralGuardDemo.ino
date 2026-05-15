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

const uint8_t SENSOR_POWER_PIN = 7;

void setup() {
  Serial.begin(115200);

  node.guard("external-sensor-power")
    .powerPin(SENSOR_POWER_PIN)
    .activeLevel(HIGH)
    .warmupTimeMs(30)
    .onWake([]() {
      Serial.println(F("Guard wake: sensor power on."));
    })
    .onSleep([]() {
      Serial.println(F("Guard sleep: sensor power off."));
    });

  node.sensor("guarded-sensor")
    .read([]() -> float { return (float)analogRead(A0); })
    .minIntervalMs(EcoTime::seconds(2))
    .maxIntervalMs(EcoTime::seconds(30))
    .changeThreshold(12.0f)
    .onSleep([]() {});

  node.begin();
  node.printDiagnostics(Serial);
}

void loop() {
  node.loop();
}
