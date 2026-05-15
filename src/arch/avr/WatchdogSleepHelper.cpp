#include "arch/avr/WatchdogSleepHelper.h"

#if defined(ARDUINO_ARCH_AVR) && !defined(ECOSENSE_HOST_TEST)
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

static volatile bool ecosenseWdtFired = false;
ISR(WDT_vect) { ecosenseWdtFired = true; }

static uint8_t ecosenseWdtBits(uint32_t ms) {
  if (ms >= 8000UL) return WDTO_8S;
  if (ms >= 4000UL) return WDTO_4S;
  if (ms >= 2000UL) return WDTO_2S;
  if (ms >= 1000UL) return WDTO_1S;
  if (ms >= 500UL) return WDTO_500MS;
  if (ms >= 250UL) return WDTO_250MS;
  if (ms >= 120UL) return WDTO_120MS;
  return WDTO_60MS;
}

void WatchdogSleepHelper::sleepForApprox(uint32_t ms) {
  // Explicit opt-in helper only. It does not alter fuses and does not disable BOD.
  while (ms > 0UL) {
    const uint32_t chunk = ms >= 8000UL ? 8000UL : ms;
    ecosenseWdtFired = false;
    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDIE) | ecosenseWdtBits(chunk);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
    wdt_disable();
    if (chunk >= ms) break;
    ms -= chunk;
  }
}
#else
void WatchdogSleepHelper::sleepForApprox(uint32_t ms) {
  delay(ms);
}
#endif
