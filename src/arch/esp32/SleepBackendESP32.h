#ifndef ECOSENSE_ARCH_ESP32_SLEEPBACKENDESP32_H
#define ECOSENSE_ARCH_ESP32_SLEEPBACKENDESP32_H

#include <Arduino.h>
#include <stdint.h>

#if defined(ARDUINO_ARCH_ESP32)
class Esp32SleepBackend {
public:
  Esp32SleepBackend();
  void lightSleepFor(uint32_t ms);
  void deepSleepFor(uint32_t ms);
  const char* name() const;
  bool isRealSleep() const;
  const char* wakeCauseName() const;
};
#else
class Esp32SleepBackend {
public:
  Esp32SleepBackend() {}
  void lightSleepFor(uint32_t ms) { delay(ms); }
  void deepSleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "esp32-backend-unavailable"; }
  bool isRealSleep() const { return false; }
  const char* wakeCauseName() const { return "unavailable"; }
};
#endif

#endif
