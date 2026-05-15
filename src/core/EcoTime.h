#ifndef ECOSENSE_CORE_ECOTIME_H
#define ECOSENSE_CORE_ECOTIME_H

#include <Arduino.h>
#include <stdint.h>

struct EcoTime {
  static uint32_t nowMs() {
    return millis();
  }

  static bool due(uint32_t now, uint32_t deadline) {
    return (int32_t)(now - deadline) >= 0;
  }

  static uint32_t elapsed(uint32_t now, uint32_t start) {
    return (uint32_t)(now - start);
  }

  static uint32_t remainingUntil(uint32_t now, uint32_t deadline) {
    return due(now, deadline) ? 0UL : (uint32_t)(deadline - now);
  }

  static uint32_t milliseconds(uint32_t value) {
    return value;
  }

  static uint32_t seconds(uint32_t value) {
    return value * 1000UL;
  }

  static uint32_t minutes(uint32_t value) {
    return value * 60UL * 1000UL;
  }

  static uint32_t hours(uint32_t value) {
    return value * 60UL * 60UL * 1000UL;
  }

  static uint32_t days(uint32_t value) {
    const uint32_t dayMs = 24UL * 60UL * 60UL * 1000UL;
    if (value > (uint32_t)(0xFFFFFFFFUL / dayMs)) {
      return 0xFFFFFFFFUL;
    }
    return value * dayMs;
  }

  static uint32_t fromHz(float hz) {
    if (hz <= 0.0f) {
      return 0UL;
    }
    const float interval = 1000.0f / hz;
    if (interval >= 4294967295.0f) {
      return 0xFFFFFFFFUL;
    }
    return interval < 1.0f ? 1UL : (uint32_t)(interval + 0.5f);
  }

  static float toHz(uint32_t intervalMs) {
    if (intervalMs == 0UL) {
      return 0.0f;
    }
    return 1000.0f / (float)intervalMs;
  }
};

#endif
