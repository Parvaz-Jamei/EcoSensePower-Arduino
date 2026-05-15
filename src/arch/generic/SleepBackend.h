#ifndef ECOSENSE_ARCH_GENERIC_SLEEPBACKEND_H
#define ECOSENSE_ARCH_GENERIC_SLEEPBACKEND_H

#include <Arduino.h>
#include <stdint.h>

class GenericSleepBackend {
public:
  void sleepFor(uint32_t ms);
  const char* name() const;
  bool isRealSleep() const;
};

#endif
