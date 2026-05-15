#include "arch/avr/PeripheralGuardAVR.h"

#if defined(ARDUINO_ARCH_AVR)
#include <avr/power.h>
#include <avr/io.h>

AvrPeripheralGuard::AvrPeripheralGuard()
  : adcRequested_(false), adcState_(0), adcStateSaved_(false) {}

void AvrPeripheralGuard::disableADC() {
  adcRequested_ = true;
  if (!adcStateSaved_) {
    adcState_ = ADCSRA;
    adcStateSaved_ = true;
  }
  power_adc_disable();
}

void AvrPeripheralGuard::restoreADC() {
  if (adcRequested_ && adcStateSaved_) {
    power_adc_enable();
    ADCSRA = adcState_;
  }
  adcRequested_ = false;
}

void AvrPeripheralGuard::beforeSleep() {
  disableADC();
}

void AvrPeripheralGuard::afterWake() {
  restoreADC();
}

const char* AvrPeripheralGuard::name() const {
  return "avr-peripheral-guard-v2";
}
#endif
