#ifndef ECOSENSE_ARCH_RP2040_SLEEPBACKENDRP2040_H
#define ECOSENSE_ARCH_RP2040_SLEEPBACKENDRP2040_H

#include <Arduino.h>
#include <stdint.h>

#if defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED_RP2040)
class Rp2040SleepBackend {
public:
  void sleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "rp2040-placeholder"; }
  bool isRealSleep() const { return false; }
};
#else
class Rp2040SleepBackend {
public:
  void sleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "rp2040-backend-unavailable"; }
  bool isRealSleep() const { return false; }
};
#endif

#endif
