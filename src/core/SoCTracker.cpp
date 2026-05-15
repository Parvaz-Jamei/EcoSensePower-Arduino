#include "core/SoCTracker.h"

SoCTracker::SoCTracker()
  : battery_(BatteryProfile::AA_Alkaline()), voltageReader_(0), lastVoltageV_(0.0f),
    consumed_mAh_(0.0f), harvested_mAh_(0.0f), chemistry_(ECO_BATTERY_ALKALINE_AA),
    hasVoltage_(false), hasInitialSoc_(false), initialSocPercent_(-1.0f),
    customVoltages_(0), customSocs_(0), customCurveCount_(0) {}

SoCTracker& SoCTracker::battery(const BatteryProfile& profile) { battery_ = profile; chemistry_ = profile.chemistry; return *this; }
SoCTracker& SoCTracker::voltageReader(EcoVoltageReadCallback callback) { voltageReader_ = callback; return *this; }
SoCTracker& SoCTracker::observedVoltage(float voltageV) { lastVoltageV_ = voltageV; hasVoltage_ = voltageV > 0.0f; return *this; }
SoCTracker& SoCTracker::chemistry(EcoBatteryChemistry chemistry) { chemistry_ = chemistry; battery_.chemistry = chemistry; return *this; }
SoCTracker& SoCTracker::voltageCurve(const float* voltage, const float* soc, uint8_t count) {
  customVoltages_ = voltage;
  customSocs_ = soc;
  customCurveCount_ = (voltage && soc && count >= 2) ? count : 0;
  return *this;
}
bool SoCTracker::hasCustomVoltageCurve() const { return customCurveCount_ >= 2 && customVoltages_ && customSocs_; }
SoCTracker& SoCTracker::initialSocPercent(float value) {
  if (value < 0.0f) {
    initialSocPercent_ = -1.0f;
    hasInitialSoc_ = false;
  } else {
    initialSocPercent_ = clampPercent(value);
    hasInitialSoc_ = true;
  }
  return *this;
}
bool SoCTracker::hasInitialSoc() const { return hasInitialSoc_; }
bool SoCTracker::hasCoulombEvidence() const { return consumed_mAh_ > 0.0f || harvested_mAh_ > 0.0f; }
bool SoCTracker::hasVoltageEvidence() const { return hasVoltage_ || voltageReader_ != 0; }
SoCTracker& SoCTracker::resetCoulombLedger() { consumed_mAh_ = 0.0f; harvested_mAh_ = 0.0f; return *this; }
SoCTracker& SoCTracker::debit(uint32_t current_uA, uint32_t durationMs) { consumed_mAh_ += ((float)current_uA * (float)durationMs) / 3600000000.0f; return *this; }
SoCTracker& SoCTracker::credit(float harvestedMilliWatt, uint32_t durationMs) {
  const float voltage = battery_.nominalVoltageV > 0.1f ? battery_.nominalVoltageV : 3.3f;
  const float current_mA = harvestedMilliWatt / voltage;
  harvested_mAh_ += current_mA * ((float)durationMs / 3600000.0f);
  return *this;
}

SoCTracker& SoCTracker::creditUsableEnergy_mJ(float usableEnergy_mJ) {
  if (usableEnergy_mJ <= 0.0f) {
    return *this;
  }
  const float voltage = battery_.nominalVoltageV > 0.1f ? battery_.nominalVoltageV : 3.3f;
  // 1 mJ = 1 mW*s. Convert usable stored energy to an equivalent mAh credit.
  harvested_mAh_ += usableEnergy_mJ / (voltage * 3600.0f);
  return *this;
}

float SoCTracker::readVoltage() const { return voltageReader_ ? voltageReader_() : lastVoltageV_; }
float SoCTracker::clampPercent(float value) { if (value < 0.0f) return 0.0f; if (value > 100.0f) return 100.0f; return value; }

float SoCTracker::piecewiseLookup(float voltage, const float* volts, const float* socs, uint8_t count) const {
  if (voltage <= 0.0f || !volts || !socs || count == 0) return -1.0f;
  if (voltage <= volts[0]) return socs[0];
  for (uint8_t i = 1; i < count; ++i) {
    if (voltage <= volts[i]) {
      const float dv = volts[i] - volts[i - 1];
      if (dv <= 0.0f) return socs[i];
      const float t = (voltage - volts[i - 1]) / dv;
      return clampPercent(socs[i - 1] + t * (socs[i] - socs[i - 1]));
    }
  }
  return socs[count - 1];
}

float SoCTracker::voltageCurveSoc(float voltage) const {
  if (voltage <= 0.0f) return -1.0f;
  if (hasCustomVoltageCurve()) return piecewiseLookup(voltage, customVoltages_, customSocs_, customCurveCount_);
  static const float lipoV[] = {3.20f, 3.50f, 3.70f, 3.85f, 4.00f, 4.20f};
  static const float lipoS[] = {0.0f, 10.0f, 40.0f, 60.0f, 85.0f, 100.0f};
  static const float alkV[] = {0.90f, 1.05f, 1.15f, 1.25f, 1.35f, 1.55f};
  static const float alkS[] = {0.0f, 10.0f, 30.0f, 55.0f, 80.0f, 100.0f};
  static const float nimhV[] = {1.00f, 1.10f, 1.18f, 1.24f, 1.32f, 1.45f};
  static const float nimhS[] = {0.0f, 10.0f, 35.0f, 65.0f, 90.0f, 100.0f};
  static const float lisoV[] = {3.00f, 3.20f, 3.35f, 3.55f, 3.65f};
  static const float lisoS[] = {0.0f, 5.0f, 20.0f, 80.0f, 100.0f};
  static const float lifeV[] = {2.80f, 3.00f, 3.15f, 3.25f, 3.35f, 3.60f};
  static const float lifeS[] = {0.0f, 10.0f, 30.0f, 65.0f, 90.0f, 100.0f};
  static const float crV[] = {2.00f, 2.40f, 2.70f, 2.90f, 3.05f, 3.20f};
  static const float crS[] = {0.0f, 10.0f, 35.0f, 60.0f, 85.0f, 100.0f};
  switch (chemistry_) {
    case ECO_BATTERY_LIPO_1S:
    case ECO_BATTERY_LIPO_1S_400:
    case ECO_BATTERY_LIION_18650:
      return piecewiseLookup(voltage, lipoV, lipoS, 6);
    case ECO_BATTERY_LIPO_2S:
      return piecewiseLookup(voltage / 2.0f, lipoV, lipoS, 6);
    case ECO_BATTERY_NIMH_AA:
    case ECO_BATTERY_NIMH_AAA:
      return piecewiseLookup(voltage, nimhV, nimhS, 6);
    case ECO_BATTERY_LISOCL2_AA: return piecewiseLookup(voltage, lisoV, lisoS, 5);
    case ECO_BATTERY_LIFEPO4_1S: return piecewiseLookup(voltage, lifeV, lifeS, 6);
    case ECO_BATTERY_CR2032:
    case ECO_BATTERY_CR123A:
      return piecewiseLookup(voltage, crV, crS, 6);
    case ECO_BATTERY_D_ALKALINE:
    case ECO_BATTERY_ALKALINE_AA:
    default: return piecewiseLookup(voltage, alkV, alkS, 6);
  }
}

float SoCTracker::coulombSoc() const {
  if (battery_.capacity_mAh == 0 || !hasInitialSoc_) return -1.0f;
  const float net = consumed_mAh_ - harvested_mAh_;
  return clampPercent(initialSocPercent_ - (net * 100.0f / (float)battery_.capacity_mAh));
}

float SoCTracker::socPercent() const {
  const bool voltageEvidence = hasVoltageEvidence();
  const bool coulombEvidence = hasCoulombEvidence() && hasInitialSoc_;
  const float c = coulombEvidence ? coulombSoc() : -1.0f;
  const float v = voltageEvidence ? voltageCurveSoc(readVoltage()) : -1.0f;
  if (v < 0.0f && c < 0.0f) {
    return hasInitialSoc_ ? initialSocPercent_ : -1.0f;
  }
  if (ecoBatteryHasFlatDischargeCurve(chemistry_) && c >= 0.0f) return c;
  if (v < 0.0f) return c;
  if (c < 0.0f) return v;
  return clampPercent((0.65f * c) + (0.35f * v));
}

float SoCTracker::estimatedDaysLeft(float averageCurrent_uA) const {
  const float soc = socPercent();
  const bool voltageOnlyFlat = ecoBatteryHasFlatDischargeCurve(chemistry_) && hasVoltageEvidence() && !(hasCoulombEvidence() && hasInitialSoc_);
  if (voltageOnlyFlat) return -1.0f;
  if (averageCurrent_uA <= 0.0f || battery_.capacity_mAh == 0 || soc < 0.0f) return -1.0f;
  const float remaining_mAh = (soc / 100.0f) * (float)battery_.capacity_mAh;
  return remaining_mAh / (averageCurrent_uA / 1000.0f) / 24.0f;
}

EcoProfileConfidence SoCTracker::confidence() const {
  if (!hasInitialSoc_ && !hasVoltageEvidence() && !hasCoulombEvidence()) return EcoProfileConfidence::PLACEHOLDER;
  if (battery_.confidence == EcoProfileConfidence::MEASURED && hasInitialSoc_ && hasCoulombEvidence()) return EcoProfileConfidence::MEASURED;
  if (ecoBatteryHasFlatDischargeCurve(chemistry_) && hasVoltageEvidence() && !hasCoulombEvidence()) return EcoProfileConfidence::PLACEHOLDER;
  if (battery_.confidence == EcoProfileConfidence::DATASHEET || hasVoltageEvidence() || hasInitialSoc_) return EcoProfileConfidence::DATASHEET;
  return EcoProfileConfidence::PLACEHOLDER;
}

EcoSoCReport SoCTracker::report(float averageCurrent_uA) const {
  EcoSoCReport r;
  r.socPercent = socPercent();
  r.estimatedDaysLeft = estimatedDaysLeft(averageCurrent_uA);
  r.confidence = confidence();
  const bool v = hasVoltageEvidence();
  const bool c = hasCoulombEvidence() && hasInitialSoc_;
  r.method = (v && c) ? EcoSoCMethod::HYBRID : (c ? EcoSoCMethod::COULOMB_LEDGER : (v ? EcoSoCMethod::VOLTAGE_CURVE : EcoSoCMethod::UNKNOWN));
  r.flatCurveWarning = flatCurveWarning();
  r.estimateOnly = r.confidence != EcoProfileConfidence::MEASURED;
  r.chemistryName = ecoBatteryChemistryName(chemistry_);
  return r;
}

bool SoCTracker::flatCurveWarning() const { return ecoBatteryHasFlatDischargeCurve(chemistry_); }
const char* SoCTracker::confidenceText() const { return ecoProfileConfidenceName(confidence()); }
