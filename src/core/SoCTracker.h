#ifndef ECOSENSE_CORE_SOCTRACKER_H
#define ECOSENSE_CORE_SOCTRACKER_H

#include "core/BatteryProfile.h"
#include "core/EnergyModel.h"
#include <stdint.h>

typedef float (*EcoVoltageReadCallback)();

enum class EcoSoCMethod : uint8_t {
  UNKNOWN,
  VOLTAGE_CURVE,
  COULOMB_LEDGER,
  HYBRID
};

struct EcoSoCReport {
  float socPercent;
  float estimatedDaysLeft;
  EcoProfileConfidence confidence;
  EcoSoCMethod method;
  bool flatCurveWarning;
  bool estimateOnly;
  const char* chemistryName;

  EcoSoCReport()
    : socPercent(-1.0f), estimatedDaysLeft(-1.0f), confidence(EcoProfileConfidence::PLACEHOLDER),
      method(EcoSoCMethod::UNKNOWN), flatCurveWarning(false), estimateOnly(true), chemistryName("unknown") {}
};

class SoCTracker {
public:
  SoCTracker();

  SoCTracker& battery(const BatteryProfile& profile);
  SoCTracker& voltageReader(EcoVoltageReadCallback callback);
  SoCTracker& observedVoltage(float voltageV);
  SoCTracker& chemistry(EcoBatteryChemistry chemistry);
  SoCTracker& voltageCurve(const float* voltage, const float* soc, uint8_t count);
  bool hasCustomVoltageCurve() const;
  SoCTracker& initialSocPercent(float value);
  bool hasInitialSoc() const;
  bool hasCoulombEvidence() const;
  bool hasVoltageEvidence() const;
  SoCTracker& resetCoulombLedger();
  SoCTracker& debit(uint32_t current_uA, uint32_t durationMs);
  SoCTracker& credit(float harvestedMilliWatt, uint32_t durationMs);
  SoCTracker& creditUsableEnergy_mJ(float usableEnergy_mJ);

  float socPercent() const;
  float estimatedDaysLeft(float averageCurrent_uA) const;
  EcoProfileConfidence confidence() const;
  EcoSoCReport report(float averageCurrent_uA) const;
  bool flatCurveWarning() const;
  const char* confidenceText() const;

private:
  BatteryProfile battery_;
  EcoVoltageReadCallback voltageReader_;
  float lastVoltageV_;
  float consumed_mAh_;
  float harvested_mAh_;
  EcoBatteryChemistry chemistry_;
  bool hasVoltage_;
  bool hasInitialSoc_;
  float initialSocPercent_;
  const float* customVoltages_;
  const float* customSocs_;
  uint8_t customCurveCount_;

  float voltageCurveSoc(float voltage) const;
  float piecewiseLookup(float voltage, const float* volts, const float* socs, uint8_t count) const;
  float coulombSoc() const;
  float readVoltage() const;
  static float clampPercent(float value);
};

#endif
