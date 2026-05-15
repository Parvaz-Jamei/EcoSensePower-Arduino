#include "arch/esp32/SleepBackendESP32.h"

#if defined(ARDUINO_ARCH_ESP32)
#include <esp_sleep.h>

Esp32SleepBackend::Esp32SleepBackend() {}

void Esp32SleepBackend::lightSleepFor(uint32_t ms) {
  if (ms == 0) {
    return;
  }
  esp_sleep_enable_timer_wakeup((uint64_t)ms * 1000ULL);
  esp_light_sleep_start();
}

void Esp32SleepBackend::deepSleepFor(uint32_t ms) {
  if (ms == 0) {
    return;
  }
  esp_sleep_enable_timer_wakeup((uint64_t)ms * 1000ULL);
  esp_deep_sleep_start();
}

const char* Esp32SleepBackend::name() const {
  return "esp32-light-deep-sleep-v1";
}

bool Esp32SleepBackend::isRealSleep() const {
  return true;
}

const char* Esp32SleepBackend::wakeCauseName() const {
  switch (esp_sleep_get_wakeup_cause()) {
    case ESP_SLEEP_WAKEUP_TIMER: return "timer";
    case ESP_SLEEP_WAKEUP_EXT0: return "ext0";
    case ESP_SLEEP_WAKEUP_EXT1: return "ext1";
    case ESP_SLEEP_WAKEUP_TOUCHPAD: return "touchpad";
    case ESP_SLEEP_WAKEUP_ULP: return "ulp";
#if defined(ESP_SLEEP_WAKEUP_GPIO)
    case ESP_SLEEP_WAKEUP_GPIO: return "gpio";
#endif
#if defined(ESP_SLEEP_WAKEUP_UART)
    case ESP_SLEEP_WAKEUP_UART: return "uart";
#endif
    case ESP_SLEEP_WAKEUP_UNDEFINED: return "undefined";
    default: return "other";
  }
}
#endif
