#ifndef ECOSENSE_ARCH_NRF52_SLEEPBACKENDNRF52_H
#define ECOSENSE_ARCH_NRF52_SLEEPBACKENDNRF52_H

#include <Arduino.h>
#include <stdint.h>

#if defined(ARDUINO_ARCH_NRF52) || defined(ARDUINO_ARCH_MBED_NANO)
class Nrf52SleepBackend {
public:
  void sleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "nrf52-placeholder"; }
  bool isRealSleep() const { return false; }
};
#else
class Nrf52SleepBackend {
public:
  void sleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "nrf52-backend-unavailable"; }
  bool isRealSleep() const { return false; }
};
#endif

#endif
