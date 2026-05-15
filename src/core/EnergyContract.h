#ifndef ECOSENSE_CORE_ENERGYCONTRACT_H
#define ECOSENSE_CORE_ENERGYCONTRACT_H

#include "core/EcoTypes.h"

struct EnergyContract {
  uint32_t minIntervalMs;
  uint32_t maxIntervalMs;
  uint32_t currentIntervalMs;
  float changeThreshold;
  EcoPriority priority;
  uint32_t warmupTimeMs;
  uint32_t maxDailyEnergy_mJ;
  float maxWindowEnergy_mJ;
  uint32_t energyWindowMs;

  EnergyContract();
  void setDefaults();
  bool validate();
  bool hasDailyBudget() const;
  bool hasWindowBudget() const;
  EnergyContract& maxEnergyPerWindow_mJ(float value, uint32_t windowMs);
  EnergyContract& energyWindow(uint32_t windowMs);
};

#endif
