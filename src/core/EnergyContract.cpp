#include "core/EnergyContract.h"

EnergyContract::EnergyContract() {
  setDefaults();
}

void EnergyContract::setDefaults() {
  minIntervalMs = ECOSENSE_DEFAULT_MIN_INTERVAL_MS;
  maxIntervalMs = ECOSENSE_DEFAULT_MAX_INTERVAL_MS;
  currentIntervalMs = minIntervalMs;
  changeThreshold = ECOSENSE_DEFAULT_CHANGE_THRESHOLD;
  priority = ECO_NORMAL;
  warmupTimeMs = 0;
  maxDailyEnergy_mJ = 0;
  maxWindowEnergy_mJ = 0.0f;
  energyWindowMs = 0UL;
}

bool EnergyContract::validate() {
  bool changed = false;
  if (minIntervalMs == 0) {
    minIntervalMs = 1;
    changed = true;
  }
  if (maxIntervalMs < minIntervalMs) {
    maxIntervalMs = minIntervalMs;
    changed = true;
  }
  if (currentIntervalMs < minIntervalMs) {
    currentIntervalMs = minIntervalMs;
    changed = true;
  }
  if (currentIntervalMs > maxIntervalMs) {
    currentIntervalMs = maxIntervalMs;
    changed = true;
  }
  if (changeThreshold < 0.0f) {
    changeThreshold = 0.0f;
    changed = true;
  }
  return !changed;
}

bool EnergyContract::hasDailyBudget() const {
  return maxDailyEnergy_mJ > 0;
}

bool EnergyContract::hasWindowBudget() const {
  return maxWindowEnergy_mJ > 0.0f && energyWindowMs > 0UL;
}

EnergyContract& EnergyContract::maxEnergyPerWindow_mJ(float value, uint32_t windowMs) {
  maxWindowEnergy_mJ = value < 0.0f ? 0.0f : value;
  energyWindowMs = windowMs;
  return *this;
}

EnergyContract& EnergyContract::energyWindow(uint32_t windowMs) {
  energyWindowMs = windowMs;
  return *this;
}
