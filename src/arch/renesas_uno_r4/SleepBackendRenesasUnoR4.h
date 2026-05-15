#ifndef ECOSENSE_ARCH_RENESAS_UNO_R4_SLEEPBACKENDRENESASUNOR4_H
#define ECOSENSE_ARCH_RENESAS_UNO_R4_SLEEPBACKENDRENESASUNOR4_H
#include <Arduino.h>
class SleepBackendRenesasUnoR4 {
public:
  void sleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "renesas_uno_r4-compile-placeholder"; }
  bool isRealSleep() const { return false; }
};
#endif
