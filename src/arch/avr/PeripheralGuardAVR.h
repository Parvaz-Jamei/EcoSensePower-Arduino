#ifndef ECOSENSE_ARCH_AVR_PERIPHERALGUARDAVR_H
#define ECOSENSE_ARCH_AVR_PERIPHERALGUARDAVR_H

#include <Arduino.h>
#include <stdint.h>

#if defined(ARDUINO_ARCH_AVR)
class AvrPeripheralGuard {
public:
  AvrPeripheralGuard();
  void disableADC();
  void restoreADC();
  void beforeSleep();
  void afterWake();
  const char* name() const;
private:
  bool adcRequested_;
  uint8_t adcState_;
  bool adcStateSaved_;
};
#else
class AvrPeripheralGuard {
public:
  AvrPeripheralGuard() {}
  void disableADC() {}
  void restoreADC() {}
  void beforeSleep() {}
  void afterWake() {}
  const char* name() const { return "avr-guard-unavailable"; }
};
#endif

#endif
