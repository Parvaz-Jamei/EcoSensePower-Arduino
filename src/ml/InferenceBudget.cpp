#include "ml/InferenceBudget.h"
InferenceBudget::InferenceBudget() : current_(0), duration_(0), maxRunsPerDay_(0), skipWhenEnergyDeficit_(false), allowCriticalBypass_(true) {}
InferenceBudget& InferenceBudget::current_uA(uint32_t value) { current_ = value; return *this; }
InferenceBudget& InferenceBudget::durationMs(uint32_t value) { duration_ = value; return *this; }
InferenceBudget& InferenceBudget::maxRunsPerDay(uint16_t value) { maxRunsPerDay_ = value; return *this; }
InferenceBudget& InferenceBudget::skipWhenEnergyDeficit(bool enabled) { skipWhenEnergyDeficit_ = enabled; return *this; }
InferenceBudget& InferenceBudget::allowCriticalBypass(bool enabled) { allowCriticalBypass_ = enabled; return *this; }
uint32_t InferenceBudget::current_uA() const { return current_; }
uint32_t InferenceBudget::durationMs() const { return duration_; }
uint16_t InferenceBudget::maxRunsPerDay() const { return maxRunsPerDay_; }
bool InferenceBudget::shouldSkipWhenEnergyDeficit() const { return skipWhenEnergyDeficit_; }
bool InferenceBudget::criticalBypassAllowed() const { return allowCriticalBypass_; }
bool InferenceBudget::hasBudget() const { return current_ > 0UL && duration_ > 0UL; }
bool InferenceBudget::canRun(uint16_t runsToday) const { return maxRunsPerDay_ == 0 || runsToday < maxRunsPerDay_; }
bool InferenceBudget::limitReached(uint16_t runsToday) const { return maxRunsPerDay_ > 0 && runsToday >= maxRunsPerDay_; }
float InferenceBudget::energyPerInference_mJ(float voltage) const { return EnergyModel::energyMilliJoules(voltage, current_, duration_); }
float InferenceBudget::dailyEnergy_mJ(float voltage) const { return energyPerInference_mJ(voltage) * (float)maxRunsPerDay_; }
