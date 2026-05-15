#ifndef ECOSENSE_CORE_ENERGYLEDGER_H
#define ECOSENSE_CORE_ENERGYLEDGER_H

#include "core/EcoTypes.h"
#include "core/EnergyModel.h"

struct EcoLedgerRecord {
  EcoEnergyState state;
  uint32_t durationMs;
  uint32_t currentMicroA;
  float energyMilliJoules;
};

class EnergyLedger {
public:
  EnergyLedger();

  void clear();
  void beginCycle();
  void endCycle();
  void clearCycle();
  bool record(EcoEnergyState state, uint32_t durationMs, uint32_t currentMicroA, float voltageV);

  uint8_t count() const;
  uint8_t cycleCount() const;
  bool aggregateMode() const;
  bool cycleAggregateMode() const;
  bool cycleOpen() const;
  float totalEnergyMilliJoules() const;
  float cycleEnergyMilliJoules() const;
  uint32_t totalDurationMs() const;
  uint32_t cycleDurationMs() const;
  float averageCurrentMicroA(float voltageV) const;
  EcoEnergyState dominantState() const;
  EcoEnergyState dominantCycleState() const;
  float energyForState(EcoEnergyState state) const;
  float cycleEnergyForState(EcoEnergyState state) const;
  const EcoLedgerRecord& recordAt(uint8_t index) const;
  void printTo(Print& out) const;
  void printCycleTo(Print& out) const;
  void printTotalTo(Print& out) const;

private:
  static const uint8_t kEnergyStateCount = 12;

#if ECOSENSE_ENABLE_FULL_LEDGER
  EcoLedgerRecord cycleRecords_[ECOSENSE_LEDGER_MAX_RECORDS];
#endif
  uint8_t cycleCount_;
  bool cycleAggregateMode_;
  float cycleEnergy_mJ_;
  uint32_t cycleDurationMs_;
#if ECOSENSE_ENABLE_FULL_LEDGER
  float cycleEnergyByState_[kEnergyStateCount];
  uint32_t cycleDurationByState_[kEnergyStateCount];
#endif

  bool lifetimeAggregateMode_;
  float lifetimeEnergy_mJ_;
  uint32_t lifetimeDurationMs_;
#if ECOSENSE_ENABLE_FULL_LEDGER
  float lifetimeEnergyByState_[kEnergyStateCount];
  uint32_t lifetimeDurationByState_[kEnergyStateCount];
#endif
  bool cycleOpen_;

  void clearCycleStateOnly();
  void accumulateState(EcoEnergyState state, float energyMilliJoules, uint32_t durationMs);
#if ECOSENSE_ENABLE_FULL_LEDGER
  EcoEnergyState dominantFrom(const float* energyByState) const;
#endif
};

#endif
