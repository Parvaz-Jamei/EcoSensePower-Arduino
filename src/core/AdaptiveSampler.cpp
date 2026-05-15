#include "core/AdaptiveSampler.h"
#include <math.h>

AdaptiveSampler::AdaptiveSampler()
  : additiveStepMs_(1000UL), shrinkFactor_(2) {}

uint32_t AdaptiveSampler::update(EnergyContract& contract, float previousValue, float newValue, bool hasPrevious, bool* importantChange) {
  contract.validate();
  bool important = false;

  if (!hasPrevious) {
    important = true;
  } else {
    const float diff = fabs(newValue - previousValue);
    if (diff < contract.changeThreshold) {
      uint32_t next = contract.currentIntervalMs + additiveStepMs_;
      if (next < contract.currentIntervalMs) {
        next = contract.maxIntervalMs;
      }
      contract.currentIntervalMs = ecoMinU32(next, contract.maxIntervalMs);
    } else {
      important = true;
      uint32_t next = contract.currentIntervalMs / shrinkFactor_;
      contract.currentIntervalMs = ecoMaxU32(next, contract.minIntervalMs);
    }
  }

  if (contract.currentIntervalMs < contract.minIntervalMs) {
    contract.currentIntervalMs = contract.minIntervalMs;
  }
  if (contract.currentIntervalMs > contract.maxIntervalMs) {
    contract.currentIntervalMs = contract.maxIntervalMs;
  }
  if (importantChange) {
    *importantChange = important;
  }
  return contract.currentIntervalMs;
}

void AdaptiveSampler::setAdditiveStepMs(uint32_t stepMs) {
  additiveStepMs_ = (stepMs == 0) ? 1 : stepMs;
}

void AdaptiveSampler::setShrinkFactor(uint8_t factor) {
  shrinkFactor_ = (factor < 2) ? 2 : factor;
}
