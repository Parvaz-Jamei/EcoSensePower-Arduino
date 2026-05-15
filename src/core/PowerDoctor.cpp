#include "core/PowerDoctor.h"
#include "core/EcoRuntime.h"
#include <string.h>

PowerDoctor::PowerDoctor()
  : diagnosticCount_(0), truncated_(false) {}

void PowerDoctor::clear() const {
  diagnosticCount_ = 0;
  truncated_ = false;
}

void PowerDoctor::add(EcoDiagnosticCode code, EcoDiagnosticSeverity severity, const char* subject) const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  if (diagnosticCount_ >= ECOSENSE_MAX_DIAGNOSTICS) {
    truncated_ = true;
    diagnostics_[ECOSENSE_MAX_DIAGNOSTICS - 1] = EcoDiagnostic(EcoDiagnosticCode::DIAGNOSTIC_BUFFER_TRUNCATED, EcoDiagnosticSeverity::WARNING, "diagnostics");
    return;
  }
  diagnostics_[diagnosticCount_] = EcoDiagnostic(code, severity, subject);
  ++diagnosticCount_;
#else
  (void)code;
  (void)severity;
  (void)subject;
  truncated_ = true;
#endif
}

uint8_t PowerDoctor::collect(const EcoRuntime& runtime) const {
  clear();

  if (runtime.hasGenericBoardProfile()) {
    add(EcoDiagnosticCode::GENERIC_BOARD_PROFILE, EcoDiagnosticSeverity::WARNING, runtime.boardProfile().name);
  }
  if (!runtime.backendIsRealSleep()) {
    add(EcoDiagnosticCode::REAL_SLEEP_BACKEND_MISSING, EcoDiagnosticSeverity::RISK, runtime.backendName());
  }
#if defined(ARDUINO_ARCH_ESP32)
  if (!runtime.hasEsp32WirelessGuard()) {
    add(EcoDiagnosticCode::ESP32_WIRELESS_GUARD_MISSING, EcoDiagnosticSeverity::RISK, "esp32-wireless");
  }
#endif
  if (runtime.debugEnabled()) { add(EcoDiagnosticCode::DEBUG_ENABLED, EcoDiagnosticSeverity::WARNING, "debug"); }
  if (!runtime.hasBatteryProfile()) { add(EcoDiagnosticCode::BATTERY_PROFILE_MISSING, EcoDiagnosticSeverity::WARNING, runtime.batteryProfile().name); }
  if (runtime.batteryProfile().confidence == EcoProfileConfidence::PLACEHOLDER) { add(EcoDiagnosticCode::BATTERY_PROFILE_PLACEHOLDER, EcoDiagnosticSeverity::WARNING, runtime.batteryProfile().name); }
  if (runtime.boardProfile().confidence == EcoProfileConfidence::PLACEHOLDER) { add(EcoDiagnosticCode::BOARD_PROFILE_PLACEHOLDER, EcoDiagnosticSeverity::RISK, runtime.boardProfile().name); }
  if (!runtime.boardProfile().includesRegulatorIq) { add(EcoDiagnosticCode::REGULATOR_IQ_MISSING, EcoDiagnosticSeverity::RISK, runtime.boardProfile().name); }
  if (!runtime.boardProfile().includesSensorLeakage) { add(EcoDiagnosticCode::SENSOR_LEAKAGE_MISSING, EcoDiagnosticSeverity::WARNING, runtime.boardProfile().name); }
  if (!runtime.hasReportCallback()) { add(EcoDiagnosticCode::NO_REPORT_CALLBACK, EcoDiagnosticSeverity::WARNING, "report"); }
  if (runtime.sensorRegistryFull()) { add(EcoDiagnosticCode::SENSOR_REGISTRY_FULL, EcoDiagnosticSeverity::RISK, "sensor-registry"); }
  if (runtime.guardRegistryFull()) { add(EcoDiagnosticCode::GUARD_REGISTRY_FULL, EcoDiagnosticSeverity::RISK, "guard-registry"); }
  if (runtime.ledger().aggregateMode()) { add(EcoDiagnosticCode::LEDGER_AGGREGATE_MODE, EcoDiagnosticSeverity::WARNING, "ledger"); }
  if (runtime.hasAnyCurrentIntervalClamp()) { add(EcoDiagnosticCode::CURRENT_INTERVAL_CLAMPED, EcoDiagnosticSeverity::INFO, "energy-contract"); }

  const SoCTracker& soc = runtime.socTracker();
  if (!soc.hasInitialSoc()) { add(EcoDiagnosticCode::SOC_NO_INITIAL_SOC, EcoDiagnosticSeverity::WARNING, "soc"); }
  if (soc.confidence() == EcoProfileConfidence::PLACEHOLDER) { add(EcoDiagnosticCode::SOC_LOW_CONFIDENCE, EcoDiagnosticSeverity::WARNING, "soc"); }
  if (soc.hasVoltageEvidence() && !soc.hasCoulombEvidence()) { add(EcoDiagnosticCode::SOC_VOLTAGE_ONLY, EcoDiagnosticSeverity::INFO, "soc"); }
  if (soc.flatCurveWarning()) {
    add(EcoDiagnosticCode::SOC_FLAT_DISCHARGE_WARNING, EcoDiagnosticSeverity::RISK, "battery-chemistry");
    if (soc.hasVoltageEvidence() && !soc.hasCoulombEvidence()) {
      add(EcoDiagnosticCode::SOC_LOW_CONFIDENCE_FLAT_CURVE, EcoDiagnosticSeverity::RISK, "battery-chemistry");
    }
  }
  if (ecoBatteryHasPulseLimitations(runtime.batteryProfile().chemistry)) {
    add(EcoDiagnosticCode::BATTERY_PULSE_LIMITATION, EcoDiagnosticSeverity::WARNING, runtime.batteryProfile().name);
  }
  if (ecoBatteryProtectionCircuitRecommended(runtime.batteryProfile().chemistry)) {
    add(EcoDiagnosticCode::BATTERY_PROTECTION_CIRCUIT_UNKNOWN, EcoDiagnosticSeverity::INFO, runtime.batteryProfile().name);
  }

  if (runtime.energyPolicy().targetNeutralEnabled()) {
    add(EcoDiagnosticCode::ENERGY_NEUTRAL_NOT_VERIFIED, EcoDiagnosticSeverity::WARNING, "energy-policy");
    if (runtime.energyPolicy().confidence() == EcoProfileConfidence::PLACEHOLDER) { add(EcoDiagnosticCode::HARVESTER_PLACEHOLDER, EcoDiagnosticSeverity::WARNING, "harvester"); }
    if (runtime.harvestingEfficiencyPlaceholder()) {
      add(EcoDiagnosticCode::HARVESTING_EFFICIENCY_PLACEHOLDER, EcoDiagnosticSeverity::WARNING, "harvester-efficiency");
      add(EcoDiagnosticCode::HARVESTER_EFFICIENCY_UNKNOWN, EcoDiagnosticSeverity::WARNING, "harvester-efficiency");
    }
    if (runtime.energyIncomeInsufficient()) { add(EcoDiagnosticCode::ENERGY_INCOME_INSUFFICIENT, EcoDiagnosticSeverity::RISK, "harvester"); }
  }

  if (runtime.hasRadioAdapter()) {
    if (runtime.radioProfilePlaceholder()) { add(EcoDiagnosticCode::RADIO_PROFILE_PLACEHOLDER, EcoDiagnosticSeverity::WARNING, "radio"); }
    if (runtime.radioAdapter()->sleepCurrent_uA() == 0UL) { add(EcoDiagnosticCode::RADIO_NO_SLEEP_HOOK, EcoDiagnosticSeverity::INFO, "radio"); }
    if (runtime.radioTxDominatesEnergy()) { add(EcoDiagnosticCode::RADIO_TX_DOMINATES_ENERGY, EcoDiagnosticSeverity::RISK, "radio"); }
    if (runtime.radioAdapter()->txCurrent_uA() >= 1000000UL) { add(EcoDiagnosticCode::RADIO_BURST_CURRENT_HIGH, EcoDiagnosticSeverity::RISK, "radio"); }
    if (runtime.radioPayloadEstimatorPlaceholder()) { add(EcoDiagnosticCode::RADIO_PAYLOAD_ESTIMATOR_PLACEHOLDER, EcoDiagnosticSeverity::INFO, "radio-payload"); }
    if (runtime.radioRxWindowConfigured()) { add(EcoDiagnosticCode::RADIO_RX_WINDOW_COST_HIGH, EcoDiagnosticSeverity::WARNING, "radio-rx-window"); }
    if (runtime.radioConfirmedUplink()) { add(EcoDiagnosticCode::RADIO_CONFIRMED_UPLINK_WARNING, EcoDiagnosticSeverity::WARNING, "radio-uplink"); }
    if (runtime.radioBatchBufferLimited()) { add(EcoDiagnosticCode::RADIO_BATCH_BUFFER_LIMITED, EcoDiagnosticSeverity::WARNING, "radio-batcher"); }
  }

  const EcoSensorSlot* sensors = runtime.sensors();
  uint8_t criticalCount = 0;
  for (uint8_t i = 0; i < runtime.sensorCount(); ++i) {
    if (sensors[i].contract.priority == ECO_CRITICAL) { ++criticalCount; }
    if (sensors[i].contract.hasWindowBudget()) {
      add(EcoDiagnosticCode::ENERGY_WINDOW_BUDGET_ACTIVE, EcoDiagnosticSeverity::INFO, sensors[i].name ? sensors[i].name : "sensor");
      const float est = sensors[i].estimatedDailyEnergy_mJ / 86400000.0f * (float)sensors[i].contract.energyWindowMs;
      if (est > sensors[i].contract.maxWindowEnergy_mJ && sensors[i].contract.maxWindowEnergy_mJ > 0.0f) {
        add(EcoDiagnosticCode::ENERGY_WINDOW_BUDGET_EXCEEDED, EcoDiagnosticSeverity::RISK, sensors[i].name ? sensors[i].name : "sensor");
      }
    }
  }
  if (criticalCount > 1) { add(EcoDiagnosticCode::MULTIPLE_CRITICAL_SENSORS, criticalCount > 2 ? EcoDiagnosticSeverity::WARNING : EcoDiagnosticSeverity::INFO, "sensor-priority"); }
  if (criticalCount > 1 && criticalCount == runtime.sensorCount()) { add(EcoDiagnosticCode::SENSOR_PRIORITY_CONFLICT, EcoDiagnosticSeverity::WARNING, "sensor-priority"); }
  if (runtime.sensorCount() >= (ECOSENSE_MAX_SENSORS > 0 ? ECOSENSE_MAX_SENSORS - 1 : 0)) { add(EcoDiagnosticCode::SENSOR_REGISTRY_NEAR_CAPACITY, EcoDiagnosticSeverity::INFO, "sensor-registry"); }
  for (uint8_t i = 0; i < runtime.sensorCount(); ++i) {
    const EcoSensorSlot& sensor = sensors[i];
    const char* subject = sensor.name ? sensor.name : "sensor";
    if (!sensor.sleepCallback) {
      const EcoDiagnosticSeverity severity = runtime.hasMatchingGuardName(sensor.name) ? EcoDiagnosticSeverity::INFO : EcoDiagnosticSeverity::WARNING;
      add(EcoDiagnosticCode::SENSOR_NO_SLEEP_CALLBACK, severity, subject);
    }
    if (!sensor.calibratedCurrent) { add(EcoDiagnosticCode::SENSOR_NO_CALIBRATED_CURRENT, EcoDiagnosticSeverity::WARNING, subject); }
    if (sensor.contract.maxIntervalMs < EcoTime::minutes(1)) { add(EcoDiagnosticCode::SHORT_MAX_INTERVAL, EcoDiagnosticSeverity::WARNING, subject); }
    if (sensor.budgetSoftLimited) { add(EcoDiagnosticCode::BUDGET_EXCEEDED, EcoDiagnosticSeverity::RISK, subject); }
    if (sensor.readCallback == 0) { add(EcoDiagnosticCode::SENSOR_READ_CALLBACK_MISSING, EcoDiagnosticSeverity::CRITICAL, subject); }
    if (sensor.anomalyCallback && !sensor.inferenceBudget.hasBudget()) { add(EcoDiagnosticCode::INFERENCE_BUDGET_MISSING, EcoDiagnosticSeverity::WARNING, subject); }
    if (sensor.inferenceLimitReached) { add(EcoDiagnosticCode::INFERENCE_RUN_LIMIT_REACHED, EcoDiagnosticSeverity::INFO, subject); }
    if (sensor.inferenceSkippedEnergyDeficit) { add(EcoDiagnosticCode::INFERENCE_SKIPPED_ENERGY_DEFICIT, EcoDiagnosticSeverity::WARNING, subject); }
    if (runtime.debugEnabled()) { add(EcoDiagnosticCode::SENSOR_STATIC_NAME_CAUTION, EcoDiagnosticSeverity::INFO, subject); }
  }

  const bool measuredEnough = runtime.boardProfile().confidence == EcoProfileConfidence::MEASURED &&
    runtime.batteryProfile().confidence == EcoProfileConfidence::MEASURED &&
    runtime.boardProfile().notes && runtime.batteryProfile().notes;
  add(EcoDiagnosticCode::NO_HARDWARE_MEASUREMENT, measuredEnough ? EcoDiagnosticSeverity::INFO : EcoDiagnosticSeverity::RISK, "measurement");
  if (truncated_) { add(EcoDiagnosticCode::DIAGNOSTIC_BUFFER_TRUNCATED, EcoDiagnosticSeverity::WARNING, "diagnostics"); }
  return diagnosticCount_;
}

uint8_t PowerDoctor::collect(const EcoRuntime& runtime, EcoDiagnostic* buffer, uint8_t maxCount) const {
  return collectSnapshot(runtime, buffer, maxCount).copied;
}

EcoDiagnosticSnapshot PowerDoctor::collectSnapshot(const EcoRuntime& runtime, EcoDiagnostic* buffer, uint8_t maxCount) const {
  const uint8_t total = collect(runtime);
  uint8_t copyCount = 0;
  const bool callerTruncated = buffer && maxCount < total;
  if (buffer && maxCount > 0) {
    copyCount = total < maxCount ? total : maxCount;
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
    for (uint8_t i = 0; i < copyCount; ++i) { buffer[i] = diagnostics_[i]; }
#else
    copyCount = 0;
#endif
  }
  return EcoDiagnosticSnapshot(copyCount, total, truncated_ || callerTruncated);
}

bool PowerDoctor::diagnosticsTruncated() const { return truncated_; }

uint8_t PowerDoctor::diagnosticCount() const { return diagnosticCount_; }
EcoDiagnostic PowerDoctor::diagnosticAt(uint8_t index) const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  return index < diagnosticCount_ ? diagnostics_[index] : EcoDiagnostic();
#else
  (void)index;
  return EcoDiagnostic();
#endif
}
bool PowerDoctor::hasCriticalDiagnostics() const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  for (uint8_t i = 0; i < diagnosticCount_; ++i) { if (diagnostics_[i].severity == EcoDiagnosticSeverity::CRITICAL) return true; }
#endif
  return false;
}

void PowerDoctor::print(const EcoRuntime& runtime, Print& out) const {
  print(runtime, out, EcoDiagnosticSeverity::INFO);
}

void PowerDoctor::print(const EcoRuntime& runtime, Print& out, EcoDiagnosticSeverity minSeverity) const {
  collect(runtime);
  out.println(F("[EcoSensePower Doctor]"));
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  for (uint8_t i = 0; i < diagnosticCount_; ++i) {
    const EcoDiagnostic diagnostic = diagnostics_[i];
    if ((uint8_t)diagnostic.severity < (uint8_t)minSeverity) { continue; }
    out.print(F("- "));
    out.print(ecoDiagnosticSeverityName(diagnostic.severity));
    out.print(F(" ["));
    out.print(ecoDiagnosticCodeName(diagnostic.code));
    out.print(F("]"));
    if (diagnostic.subject) { out.print(F(" subject=")); out.print(diagnostic.subject); }
    out.print(F(": "));
    out.println(ecoDiagnosticMessage(diagnostic.code));
  }
#else
  (void)minSeverity;
  out.println(F("- compact AVR diagnostics storage disabled"));
#endif
}
