/*
  EcoSensePower ESP32DeepSleepSensorNode.

  ESP32 backend/sleep-planning example. EcoSensePower helps budget energy and plan
  sleep behavior, but it does not replace ESP32 WiFi/BLE APIs, Bluetooth stacks, GPS
  parsers, or board-specific power-management code.

  This example targets ESP32-class boards, not the AVR UNO/Nano smoke gate. Stop WiFi,
  BLE, sensors, and other peripherals in the application before entering deep sleep.
*/

#include <EcoSensePower.h>

EcoSensePower node;

void setup() {
  Serial.begin(115200);

#if defined(ARDUINO_ARCH_ESP32)
  node.guard("esp32-wireless")
    .esp32Wireless(true)
    .onSleep([]() {
      // Put WiFi.mode(WIFI_OFF), btStop(), NimBLE stop/deinit, etc. here if used.
      // EcoSensePower intentionally does not force WiFi/BLE dependencies into core.
    })
    .onWake([]() {
      // Re-enable application-owned radios here if needed.
    });
#else
  Serial.println(F("ESP32DeepSleepSensorNode compiles on non-ESP32 targets as a documentation/smoke example."));
#endif

  node.sensor("esp32-adc")
    .read([]() -> float { return (float)analogRead(A0); })
    .minIntervalMs(EcoTime::seconds(5))
    .maxIntervalMs(EcoTime::minutes(1))
    .changeThreshold(25.0f)
    .onSleep([]() {});

  node.onReport([](const EcoReport& report) {
    Serial.println(report.toText());
  });

  node.begin();
  node.printDiagnostics(Serial);
}

void loop() {
  node.loop();
}
