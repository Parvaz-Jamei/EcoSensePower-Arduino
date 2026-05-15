#include "arch/esp32/PeripheralGuardESP32.h"

#if defined(ARDUINO_ARCH_ESP32)
Esp32PeripheralGuard::Esp32PeripheralGuard()
  : beforeSleep_(0), afterWake_(0) {}

void Esp32PeripheralGuard::onBeforeSleep(EcoVoidCallback callback) {
  beforeSleep_ = callback;
}

void Esp32PeripheralGuard::onAfterWake(EcoVoidCallback callback) {
  afterWake_ = callback;
}

void Esp32PeripheralGuard::beforeSleep() {
  if (beforeSleep_) beforeSleep_();
}

void Esp32PeripheralGuard::afterWake() {
  if (afterWake_) afterWake_();
}

bool Esp32PeripheralGuard::hasWirelessGuard() const {
  return beforeSleep_ != 0 || afterWake_ != 0;
}

const char* Esp32PeripheralGuard::name() const {
  return "esp32-callback-wireless-guard";
}
#endif
