#ifndef ECOSENSE_CORE_ADAPTIVESAMPLER_H
#define ECOSENSE_CORE_ADAPTIVESAMPLER_H

#include "core/EnergyContract.h"

class AdaptiveSampler {
public:
  AdaptiveSampler();

  uint32_t update(EnergyContract& contract, float previousValue, float newValue, bool hasPrevious, bool* importantChange);
  void setAdditiveStepMs(uint32_t stepMs);
  void setShrinkFactor(uint8_t factor);

private:
  uint32_t additiveStepMs_;
  uint8_t shrinkFactor_;
};

#endif
