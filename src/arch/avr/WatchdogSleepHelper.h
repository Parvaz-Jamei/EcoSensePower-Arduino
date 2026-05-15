#ifndef ECOSENSE_ARCH_AVR_WATCHDOGSLEEPHELPER_H
#define ECOSENSE_ARCH_AVR_WATCHDOGSLEEPHELPER_H

#include <Arduino.h>
#include <stdint.h>

class WatchdogSleepHelper {
public:
  static void sleepForApprox(uint32_t ms);
};

#endif
