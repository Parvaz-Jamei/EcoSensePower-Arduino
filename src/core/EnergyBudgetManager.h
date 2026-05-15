#ifndef ECOSENSE_CORE_ENERGYBUDGETMANAGER_H
#define ECOSENSE_CORE_ENERGYBUDGETMANAGER_H

#include "core/EcoTypes.h"
#include "harvester/HarvesterBase.h"
#include <stdint.h>

class EnergyBudgetManager {
public:
  EnergyBudgetManager();
  EnergyBudgetManager& harvester(HarvesterBase* harvester);
  EnergyBudgetManager& targetNeutralOperation(bool enabled = true);
  EnergyBudgetManager& minReservePercent(uint8_t reservePercent);
  EnergyBudgetManager& allowIntervalStretching(bool enabled = true);
  EnergyBudgetManager& energyIncome_mW(float value);
  EnergyBudgetManager& storageEfficiencyPercent(float value);
  EnergyBudgetManager& energyCostPerCycle_mJ(float value);

  float availableInputPower_mW() const;
  float storageEfficiencyPercent() const;
  float inputEnergyDuringInterval_mJ(uint32_t intervalMs) const;
  float harvestedEnergyDuringInterval_mJ(uint32_t intervalMs) const; // usable/stored energy after efficiency
  float usableEnergyDuringInterval_mJ(uint32_t intervalMs) const;
  bool incomeCoversCycle(uint32_t intervalMs, float cycleCost_mJ) const;
  EcoEnergyBalance energyBalance(uint32_t intervalMs, float cycleCost_mJ, float socPercent = -1.0f) const;
  bool shouldStretchInterval(float socPercent) const;
  bool shouldStretchInterval(float socPercent, uint32_t intervalMs, float cycleCost_mJ) const;
  uint32_t recommendedIntervalMs(uint32_t currentIntervalMs, uint32_t maxIntervalMs, float socPercent) const;
  uint32_t recommendedIntervalMs(uint32_t currentIntervalMs, uint32_t maxIntervalMs, float socPercent, float cycleCost_mJ) const;
  uint32_t recommendedIntervalMs(uint32_t currentIntervalMs, uint32_t minIntervalMs, uint32_t maxIntervalMs, float socPercent, float cycleCost_mJ) const;
  bool hasHarvester() const;
  bool targetNeutralEnabled() const;
  bool allowIntervalStretching() const;
  float configuredCycleCost_mJ() const;
  EcoProfileConfidence confidence() const;
  bool efficiencyPlaceholder() const;

private:
  HarvesterBase* harvester_;
  bool targetNeutral_;
  bool allowStretch_;
  uint8_t minReservePercent_;
  float fixedIncome_mW_;
  float storageEfficiencyPercent_;
  float cycleCost_mJ_;
};

#endif
