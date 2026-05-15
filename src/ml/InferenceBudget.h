#ifndef ECOSENSE_ML_INFERENCEBUDGET_H
#define ECOSENSE_ML_INFERENCEBUDGET_H

#include <stdint.h>
#include "core/EnergyModel.h"

class InferenceBudget {
public:
  InferenceBudget();
  InferenceBudget& current_uA(uint32_t value);
  InferenceBudget& durationMs(uint32_t value);
  InferenceBudget& maxRunsPerDay(uint16_t value);
  InferenceBudget& skipWhenEnergyDeficit(bool enabled = true);
  InferenceBudget& allowCriticalBypass(bool enabled = true);
  uint32_t current_uA() const;
  uint32_t durationMs() const;
  uint16_t maxRunsPerDay() const;
  bool shouldSkipWhenEnergyDeficit() const;
  bool criticalBypassAllowed() const;
  bool hasBudget() const;
  bool canRun(uint16_t runsToday) const;
  bool limitReached(uint16_t runsToday) const;
  float energyPerInference_mJ(float voltage) const;
  float dailyEnergy_mJ(float voltage) const;
private:
  uint32_t current_;
  uint32_t duration_;
  uint16_t maxRunsPerDay_;
  bool skipWhenEnergyDeficit_;
  bool allowCriticalBypass_;
};

#endif
