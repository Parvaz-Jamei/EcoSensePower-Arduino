#ifndef ECOSENSE_ARCH_AVR_SLEEPBACKENDAVR_H
#define ECOSENSE_ARCH_AVR_SLEEPBACKENDAVR_H

#include <Arduino.h>
#include <stdint.h>

#if defined(ARDUINO_ARCH_AVR)
class AvrSleepBackend {
public:
  AvrSleepBackend();
  void sleepFor(uint32_t ms);
  void idle();
  void powerDownOnce();
  const char* name() const;
  bool isRealSleep() const;
  bool supportsPowerDown() const;
};
#else
class AvrSleepBackend {
public:
  AvrSleepBackend() {}
  void sleepFor(uint32_t ms) { delay(ms); }
  void idle() {}
  void powerDownOnce() { delay(1); }
  const char* name() const { return "avr-backend-unavailable"; }
  bool isRealSleep() const { return false; }
  bool supportsPowerDown() const { return false; }
};
#endif

#endif
