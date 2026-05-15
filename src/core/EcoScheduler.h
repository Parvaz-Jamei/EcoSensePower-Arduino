#ifndef ECOSENSE_CORE_ECOSCHEDULER_H
#define ECOSENSE_CORE_ECOSCHEDULER_H

#include "core/EcoTypes.h"

class EcoScheduler {
public:
  EcoScheduler();
  uint32_t clampSleepMs(uint32_t requestedMs) const;
  void setMaxSingleSleepMs(uint32_t maxMs);
  uint32_t maxSingleSleepMs() const;

private:
  uint32_t maxSingleSleepMs_;
};

#endif
