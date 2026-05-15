#include "arch/avr/SleepBackendAVR.h"

#if defined(ARDUINO_ARCH_AVR)
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

AvrSleepBackend::AvrSleepBackend() {}

void AvrSleepBackend::sleepFor(uint32_t ms) {
  // Timed sleep must remain IDLE-based unless a verified watchdog-chained
  // scheduler is implemented. In AVR power-down, millis() may not advance
  // depending on wake source, so sleepFor(ms) must not pretend timed power-down.
  const uint32_t start = millis();
  while ((uint32_t)(millis() - start) < ms) {
    idle();
  }
}

void AvrSleepBackend::idle() {
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
  sleep_cpu();
  sleep_disable();
}

void AvrSleepBackend::powerDownOnce() {
#if defined(ECOSENSE_AVR_ENABLE_POWERDOWN)
  // Explicit one-shot path. Wake source, watchdog setup, and interrupt
  // configuration are application-owned. This is not a timed scheduler.
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
  sleep_disable();
#else
  idle();
#endif
}

const char* AvrSleepBackend::name() const {
#if defined(ECOSENSE_AVR_ENABLE_POWERDOWN)
  return "avr-idle-timed-plus-explicit-power-down";
#else
  return "avr-idle-sleep-v2";
#endif
}

bool AvrSleepBackend::isRealSleep() const {
  return true;
}

bool AvrSleepBackend::supportsPowerDown() const {
#if defined(ECOSENSE_AVR_ENABLE_POWERDOWN)
  return true;
#else
  return false;
#endif
}
#endif
