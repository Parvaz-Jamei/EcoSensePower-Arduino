#ifndef ECOSENSE_ARCH_ESP32_PERIPHERALGUARDESP32_H
#define ECOSENSE_ARCH_ESP32_PERIPHERALGUARDESP32_H

#include <Arduino.h>
#include "core/EcoTypes.h"

#if defined(ARDUINO_ARCH_ESP32)
class Esp32PeripheralGuard {
public:
  Esp32PeripheralGuard();
  void onBeforeSleep(EcoVoidCallback callback);
  void onAfterWake(EcoVoidCallback callback);
  void beforeSleep();
  void afterWake();
  bool hasWirelessGuard() const;
  const char* name() const;
private:
  EcoVoidCallback beforeSleep_;
  EcoVoidCallback afterWake_;
};
#else
class Esp32PeripheralGuard {
public:
  Esp32PeripheralGuard() {}
  void onBeforeSleep(EcoVoidCallback callback) { (void)callback; }
  void onAfterWake(EcoVoidCallback callback) { (void)callback; }
  void beforeSleep() {}
  void afterWake() {}
  bool hasWirelessGuard() const { return false; }
  const char* name() const { return "esp32-guard-unavailable"; }
};
#endif

#endif
