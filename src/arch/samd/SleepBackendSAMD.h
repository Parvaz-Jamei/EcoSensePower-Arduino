#ifndef ECOSENSE_ARCH_SAMD_SLEEPBACKENDSAMD_H
#define ECOSENSE_ARCH_SAMD_SLEEPBACKENDSAMD_H

#include <Arduino.h>
#include <stdint.h>

#if defined(ARDUINO_ARCH_SAMD)
class SamdSleepBackend {
public:
  void sleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "samd-placeholder"; }
  bool isRealSleep() const { return false; }
};
#else
class SamdSleepBackend {
public:
  void sleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "samd-backend-unavailable"; }
  bool isRealSleep() const { return false; }
};
#endif

#endif
