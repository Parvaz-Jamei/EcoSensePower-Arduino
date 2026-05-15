#include "core/EnergyBudgetManager.h"

EnergyBudgetManager::EnergyBudgetManager()
  : harvester_(0), targetNeutral_(false), allowStretch_(true), minReservePercent_(25), fixedIncome_mW_(0.0f), storageEfficiencyPercent_(70.0f), cycleCost_mJ_(0.0f) {}

EnergyBudgetManager& EnergyBudgetManager::harvester(HarvesterBase* harvester) { harvester_ = harvester; return *this; }
EnergyBudgetManager& EnergyBudgetManager::targetNeutralOperation(bool enabled) { targetNeutral_ = enabled; return *this; }
EnergyBudgetManager& EnergyBudgetManager::minReservePercent(uint8_t reservePercent) { minReservePercent_ = reservePercent > 100 ? 100 : reservePercent; return *this; }
EnergyBudgetManager& EnergyBudgetManager::allowIntervalStretching(bool enabled) { allowStretch_ = enabled; return *this; }
EnergyBudgetManager& EnergyBudgetManager::energyIncome_mW(float value) { fixedIncome_mW_ = value < 0.0f ? 0.0f : value; return *this; }
EnergyBudgetManager& EnergyBudgetManager::storageEfficiencyPercent(float value) { if (value < 0.0f) value = 0.0f; if (value > 100.0f) value = 100.0f; storageEfficiencyPercent_ = value; return *this; }
EnergyBudgetManager& EnergyBudgetManager::energyCostPerCycle_mJ(float value) { cycleCost_mJ_ = value < 0.0f ? 0.0f : value; return *this; }
float EnergyBudgetManager::availableInputPower_mW() const { return (harvester_ && harvester_->available()) ? harvester_->inputPowerMilliWatt() : fixedIncome_mW_; }
float EnergyBudgetManager::storageEfficiencyPercent() const { return harvester_ && harvester_->available() ? harvester_->storageEfficiencyPercent() : storageEfficiencyPercent_; }
float EnergyBudgetManager::inputEnergyDuringInterval_mJ(uint32_t intervalMs) const { return availableInputPower_mW() * ((float)intervalMs / 1000.0f); }
float EnergyBudgetManager::harvestedEnergyDuringInterval_mJ(uint32_t intervalMs) const { return usableEnergyDuringInterval_mJ(intervalMs); }
float EnergyBudgetManager::usableEnergyDuringInterval_mJ(uint32_t intervalMs) const { return inputEnergyDuringInterval_mJ(intervalMs) * (storageEfficiencyPercent() / 100.0f); }
bool EnergyBudgetManager::incomeCoversCycle(uint32_t intervalMs, float cycleCost_mJ) const { return usableEnergyDuringInterval_mJ(intervalMs) >= cycleCost_mJ; }

EcoEnergyBalance EnergyBudgetManager::energyBalance(uint32_t intervalMs, float cycleCost_mJ, float socPercent) const {
  if (!targetNeutral_ || cycleCost_mJ <= 0.0f || intervalMs == 0UL) {
    if (socPercent >= 0.0f && socPercent < (float)minReservePercent_) return EcoEnergyBalance::DEFICIT;
    return EcoEnergyBalance::UNKNOWN;
  }
  const float usable = usableEnergyDuringInterval_mJ(intervalMs);
  if ((socPercent >= 0.0f && socPercent < (float)minReservePercent_) || usable < cycleCost_mJ) {
    return EcoEnergyBalance::DEFICIT;
  }
  if (usable >= (cycleCost_mJ * 1.25f)) {
    return EcoEnergyBalance::SURPLUS;
  }
  return EcoEnergyBalance::NEUTRAL;
}
bool EnergyBudgetManager::hasHarvester() const { return harvester_ && harvester_->available(); }
bool EnergyBudgetManager::targetNeutralEnabled() const { return targetNeutral_; }
bool EnergyBudgetManager::allowIntervalStretching() const { return allowStretch_; }
float EnergyBudgetManager::configuredCycleCost_mJ() const { return cycleCost_mJ_; }
EcoProfileConfidence EnergyBudgetManager::confidence() const { return hasHarvester() ? harvester_->confidence() : EcoProfileConfidence::PLACEHOLDER; }
bool EnergyBudgetManager::efficiencyPlaceholder() const { return confidence() == EcoProfileConfidence::PLACEHOLDER; }

bool EnergyBudgetManager::shouldStretchInterval(float socPercent) const {
  return shouldStretchInterval(socPercent, 0UL, cycleCost_mJ_);
}

bool EnergyBudgetManager::shouldStretchInterval(float socPercent, uint32_t intervalMs, float cycleCost_mJ) const {
  if (!allowStretch_) return false;
  if (socPercent >= 0.0f && socPercent < (float)minReservePercent_) return true;
  if (!targetNeutral_) return false;
  const float cost = cycleCost_mJ > 0.0f ? cycleCost_mJ : cycleCost_mJ_;
  if (cost <= 0.0f) return true;
  if (intervalMs == 0UL) return availableInputPower_mW() <= 0.0f;
  return energyBalance(intervalMs, cost, socPercent) == EcoEnergyBalance::DEFICIT;
}

uint32_t EnergyBudgetManager::recommendedIntervalMs(uint32_t currentIntervalMs, uint32_t maxIntervalMs, float socPercent) const {
  return recommendedIntervalMs(currentIntervalMs, maxIntervalMs, socPercent, cycleCost_mJ_);
}

uint32_t EnergyBudgetManager::recommendedIntervalMs(uint32_t currentIntervalMs, uint32_t maxIntervalMs, float socPercent, float cycleCost_mJ) const {
  return recommendedIntervalMs(currentIntervalMs, currentIntervalMs, maxIntervalMs, socPercent, cycleCost_mJ);
}

uint32_t EnergyBudgetManager::recommendedIntervalMs(uint32_t currentIntervalMs, uint32_t minIntervalMs, uint32_t maxIntervalMs, float socPercent, float cycleCost_mJ) const {
  const EcoEnergyBalance balance = energyBalance(currentIntervalMs, cycleCost_mJ > 0.0f ? cycleCost_mJ : cycleCost_mJ_, socPercent);
  if (!allowStretch_) return currentIntervalMs;
  if (balance == EcoEnergyBalance::DEFICIT) {
    uint32_t stretched = currentIntervalMs + (currentIntervalMs / 2UL);
    if (stretched < currentIntervalMs || stretched > maxIntervalMs) stretched = maxIntervalMs;
    return stretched;
  }
  if (balance == EcoEnergyBalance::SURPLUS && currentIntervalMs > minIntervalMs) {
    uint32_t relaxed = currentIntervalMs - (currentIntervalMs / 4UL);
    if (relaxed < minIntervalMs || relaxed > currentIntervalMs) relaxed = minIntervalMs;
    return relaxed;
  }
  return currentIntervalMs;
}
