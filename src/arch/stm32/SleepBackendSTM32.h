#ifndef ECOSENSE_ARCH_STM32_SLEEPBACKENDSTM32_H
#define ECOSENSE_ARCH_STM32_SLEEPBACKENDSTM32_H
#include <Arduino.h>
class SleepBackendSTM32 {
public:
  void sleepFor(uint32_t ms) { delay(ms); }
  const char* name() const { return "stm32-compile-placeholder"; }
  bool isRealSleep() const { return false; }
};
#endif
