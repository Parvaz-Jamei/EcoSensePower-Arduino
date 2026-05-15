#include "arch/generic/SleepBackend.h"

void GenericSleepBackend::sleepFor(uint32_t ms) {
  delay(ms);
}

const char* GenericSleepBackend::name() const {
  return "generic-delay-fallback";
}

bool GenericSleepBackend::isRealSleep() const {
  return false;
}
