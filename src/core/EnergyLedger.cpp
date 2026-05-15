#include "core/EnergyLedger.h"

EnergyLedger::EnergyLedger() {
  clear();
}

void EnergyLedger::clear() {
  lifetimeAggregateMode_ = false;
  lifetimeEnergy_mJ_ = 0.0f;
  lifetimeDurationMs_ = 0;
  cycleOpen_ = false;
#if ECOSENSE_ENABLE_FULL_LEDGER
  for (uint8_t i = 0; i < kEnergyStateCount; ++i) {
    lifetimeEnergyByState_[i] = 0.0f;
    lifetimeDurationByState_[i] = 0;
  }
#endif
  clearCycleStateOnly();
}

void EnergyLedger::clearCycleStateOnly() {
  cycleCount_ = 0;
  cycleAggregateMode_ = false;
  cycleEnergy_mJ_ = 0.0f;
  cycleDurationMs_ = 0;
#if ECOSENSE_ENABLE_FULL_LEDGER
  for (uint8_t i = 0; i < ECOSENSE_LEDGER_MAX_RECORDS; ++i) {
    cycleRecords_[i].state = EcoEnergyState::IDLE;
    cycleRecords_[i].durationMs = 0;
    cycleRecords_[i].currentMicroA = 0;
    cycleRecords_[i].energyMilliJoules = 0.0f;
  }
  for (uint8_t i = 0; i < kEnergyStateCount; ++i) {
    cycleEnergyByState_[i] = 0.0f;
    cycleDurationByState_[i] = 0;
  }
#endif
}

void EnergyLedger::beginCycle() {
  clearCycleStateOnly();
  cycleOpen_ = true;
}

void EnergyLedger::endCycle() {
  cycleOpen_ = false;
}

void EnergyLedger::clearCycle() {
  clearCycleStateOnly();
  cycleOpen_ = false;
}

bool EnergyLedger::record(EcoEnergyState state, uint32_t durationMs, uint32_t currentMicroA, float voltageV) {
  const float energy = EnergyModel::energyMilliJoules(voltageV, currentMicroA, durationMs);

  cycleEnergy_mJ_ += energy;
  cycleDurationMs_ += durationMs;
  lifetimeEnergy_mJ_ += energy;
  lifetimeDurationMs_ += durationMs;
  accumulateState(state, energy, durationMs);

#if ECOSENSE_ENABLE_FULL_LEDGER
  if (cycleCount_ < ECOSENSE_LEDGER_MAX_RECORDS) {
    cycleRecords_[cycleCount_].state = state;
    cycleRecords_[cycleCount_].durationMs = durationMs;
    cycleRecords_[cycleCount_].currentMicroA = currentMicroA;
    cycleRecords_[cycleCount_].energyMilliJoules = energy;
    ++cycleCount_;
    return true;
  }
#endif

  cycleAggregateMode_ = true;
  lifetimeAggregateMode_ = true;
  return false;
}

void EnergyLedger::accumulateState(EcoEnergyState state, float energyMilliJoules, uint32_t durationMs) {
  (void)state;
  (void)energyMilliJoules;
  (void)durationMs;
#if ECOSENSE_ENABLE_FULL_LEDGER
  const uint8_t index = ecoEnergyStateIndex(state);
  if (index >= kEnergyStateCount) {
    return;
  }
  cycleEnergyByState_[index] += energyMilliJoules;
  cycleDurationByState_[index] += durationMs;
  lifetimeEnergyByState_[index] += energyMilliJoules;
  lifetimeDurationByState_[index] += durationMs;
#endif
}

uint8_t EnergyLedger::count() const {
  return cycleCount_;
}

uint8_t EnergyLedger::cycleCount() const {
  return cycleCount_;
}

bool EnergyLedger::aggregateMode() const {
  return lifetimeAggregateMode_ || cycleAggregateMode_;
}

bool EnergyLedger::cycleAggregateMode() const {
  return cycleAggregateMode_;
}

bool EnergyLedger::cycleOpen() const {
  return cycleOpen_;
}

float EnergyLedger::totalEnergyMilliJoules() const {
  return lifetimeEnergy_mJ_;
}

float EnergyLedger::cycleEnergyMilliJoules() const {
  return cycleEnergy_mJ_;
}

uint32_t EnergyLedger::totalDurationMs() const {
  return lifetimeDurationMs_;
}

uint32_t EnergyLedger::cycleDurationMs() const {
  return cycleDurationMs_;
}

float EnergyLedger::averageCurrentMicroA(float voltageV) const {
  return EnergyModel::averageCurrentMicroA(cycleEnergy_mJ_, voltageV, cycleDurationMs_);
}

#if ECOSENSE_ENABLE_FULL_LEDGER
EcoEnergyState EnergyLedger::dominantFrom(const float* energyByState) const {
  uint8_t selected = 0;
  float selectedEnergy = energyByState[0];
  for (uint8_t i = 1; i < kEnergyStateCount; ++i) {
    if (energyByState[i] > selectedEnergy) {
      selected = i;
      selectedEnergy = energyByState[i];
    }
  }
  return static_cast<EcoEnergyState>(selected);
}
#endif

EcoEnergyState EnergyLedger::dominantState() const {
#if ECOSENSE_ENABLE_FULL_LEDGER
  return dominantFrom(lifetimeEnergyByState_);
#else
  return EcoEnergyState::IDLE;
#endif
}

EcoEnergyState EnergyLedger::dominantCycleState() const {
#if ECOSENSE_ENABLE_FULL_LEDGER
  return dominantFrom(cycleEnergyByState_);
#else
  return EcoEnergyState::IDLE;
#endif
}

float EnergyLedger::energyForState(EcoEnergyState state) const {
#if ECOSENSE_ENABLE_FULL_LEDGER
  const uint8_t index = ecoEnergyStateIndex(state);
  return index < kEnergyStateCount ? lifetimeEnergyByState_[index] : 0.0f;
#else
  (void)state;
  return 0.0f;
#endif
}

float EnergyLedger::cycleEnergyForState(EcoEnergyState state) const {
#if ECOSENSE_ENABLE_FULL_LEDGER
  const uint8_t index = ecoEnergyStateIndex(state);
  return index < kEnergyStateCount ? cycleEnergyByState_[index] : 0.0f;
#else
  (void)state;
  return 0.0f;
#endif
}

const EcoLedgerRecord& EnergyLedger::recordAt(uint8_t index) const {
#if ECOSENSE_ENABLE_FULL_LEDGER
  if (index >= cycleCount_) {
    index = 0;
  }
  return cycleRecords_[index];
#else
  (void)index;
  static EcoLedgerRecord empty = {EcoEnergyState::IDLE, 0, 0, 0.0f};
  return empty;
#endif
}

void EnergyLedger::printCycleTo(Print& out) const {
#if ECOSENSE_ENABLE_FULL_LEDGER
  out.println(F("[EcoSensePower Ledger: Full Duty Cycle]"));
  for (uint8_t i = 0; i < cycleCount_; ++i) {
    out.print(ecoEnergyStateName(cycleRecords_[i].state));
    out.print(F("  duration="));
    out.print((unsigned long)cycleRecords_[i].durationMs);
    out.print(F(" ms  current="));
    out.print((unsigned long)cycleRecords_[i].currentMicroA);
    out.print(F(" uA  energy="));
    out.print(cycleRecords_[i].energyMilliJoules, 6);
    out.println(F(" mJ"));
  }
  if (cycleAggregateMode_) {
    out.println(F("[EcoSensePower Ledger] aggregate mode active: cycle record buffer is full."));
  }
#else
  out.println(F("[EcoSensePower Ledger: Compact AVR Totals]"));
#endif
  out.println(F("[EcoSensePower Ledger] full duty cycle groups sleep + guard + wake/sense/process/report when recorded by runtime."));
  out.print(F("cycle_energy="));
  out.print(cycleEnergy_mJ_, 6);
  out.print(F(" mJ cycle_duration="));
  out.print((unsigned long)cycleDurationMs_);
  out.print(F(" ms dominant_state="));
  out.println(ecoEnergyStateName(dominantCycleState()));
}

void EnergyLedger::printTotalTo(Print& out) const {
  out.println(F("[EcoSensePower Ledger: Lifetime]"));
  out.print(F("total_energy="));
  out.print(lifetimeEnergy_mJ_, 6);
  out.print(F(" mJ total_duration="));
  out.print((unsigned long)lifetimeDurationMs_);
  out.print(F(" ms dominant_state="));
  out.println(ecoEnergyStateName(dominantState()));
  if (lifetimeAggregateMode_) {
    out.println(F("[EcoSensePower Ledger] aggregate mode was used; detailed records are disabled or full."));
  }
  out.println(F("[EcoSensePower Ledger] assumptions: board/profile currents are estimates unless marked measured."));
}

void EnergyLedger::printTo(Print& out) const {
  printCycleTo(out);
  printTotalTo(out);
}
