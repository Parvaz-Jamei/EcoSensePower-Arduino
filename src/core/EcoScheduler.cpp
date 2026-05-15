#include "core/EcoScheduler.h"

EcoScheduler::EcoScheduler()
  : maxSingleSleepMs_(1000UL) {}

uint32_t EcoScheduler::clampSleepMs(uint32_t requestedMs) const {
  if (requestedMs == 0) {
    return 0;
  }
  return ecoMinU32(requestedMs, maxSingleSleepMs_);
}

void EcoScheduler::setMaxSingleSleepMs(uint32_t maxMs) {
  maxSingleSleepMs_ = (maxMs == 0) ? 1 : maxMs;
}

uint32_t EcoScheduler::maxSingleSleepMs() const {
  return maxSingleSleepMs_;
}
