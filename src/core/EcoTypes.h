#ifndef ECOSENSE_CORE_ECOTYPES_H
#define ECOSENSE_CORE_ECOTYPES_H

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "core/EcoSensePowerConfig.h"

enum EcoPriority : uint8_t {
  ECO_LOW = 0,
  ECO_NORMAL = 1,
  ECO_HIGH = 2,
  ECO_CRITICAL = 3
};

enum class EcoState : uint8_t {
  INIT,
  IDLE,
  WAKEUP,
  SENSE,
  PROCESS,
  REPORT,
  SLEEP
};

enum class EcoEnergyState : uint8_t {
  SLEEP,
  WAKEUP,
  SENSOR_WARMUP,
  SENSOR_READ,
  PROCESS,
  REPORT,
  RADIO_TX,
  RADIO_RX,
  RADIO_SLEEP,
  INFERENCE,
  IDLE,
  GUARD
};

enum class EcoDiagnosticSeverity : uint8_t {
  INFO,
  WARNING,
  RISK,
  CRITICAL
};

enum class EcoProfileConfidence : uint8_t {
  PLACEHOLDER,
  DATASHEET,
  MEASURED
};

inline EcoProfileConfidence ecoNormalizeProfileConfidence(bool isMeasured,
                                                          EcoProfileConfidence requested) {
  if (isMeasured) {
    return EcoProfileConfidence::MEASURED;
  }
  if (requested == EcoProfileConfidence::MEASURED) {
    return EcoProfileConfidence::PLACEHOLDER;
  }
  return requested;
}

inline void ecoFormatFloatFixed(char* out, size_t outSize, float value, uint8_t decimals) {
  if (!out || outSize == 0) {
    return;
  }
  out[0] = '\0';
  if (decimals > 4) {
    decimals = 4;
  }

  const bool negative = value < 0.0f;
  float absValue = negative ? -value : value;
  unsigned long scale = 1UL;
  for (uint8_t i = 0; i < decimals; ++i) {
    scale *= 10UL;
  }

  const float scaledFloat = absValue * (float)scale + 0.5f;
  unsigned long scaled = scaledFloat > 0.0f ? (unsigned long)scaledFloat : 0UL;
  const unsigned long whole = scale > 0UL ? scaled / scale : scaled;
  const unsigned long fraction = scale > 0UL ? scaled % scale : 0UL;

  if (decimals == 0) {
    snprintf(out, outSize, "%s%lu", negative ? "-" : "", whole);
    return;
  }

  char fractionText[5];
  fractionText[4] = '\0';
  unsigned long fractionCopy = fraction;
  for (int8_t i = 3; i >= 0; --i) {
    fractionText[i] = (char)('0' + (fractionCopy % 10UL));
    fractionCopy /= 10UL;
  }
  const uint8_t offset = (uint8_t)(4U - decimals);
  snprintf(out, outSize, "%s%lu.%s", negative ? "-" : "", whole, fractionText + offset);
}

enum class EcoEnergyBalance : uint8_t {
  UNKNOWN,
  DEFICIT,
  NEUTRAL,
  SURPLUS
};

enum class EcoDiagnosticCode : uint8_t {
  GENERIC_BOARD_PROFILE,
  BOARD_PROFILE_PLACEHOLDER,
  REAL_SLEEP_BACKEND_MISSING,
  ESP32_WIRELESS_GUARD_MISSING,
  SENSOR_NO_SLEEP_CALLBACK,
  SENSOR_NO_CALIBRATED_CURRENT,
  BATTERY_PROFILE_MISSING,
  BATTERY_PROFILE_PLACEHOLDER,
  REGULATOR_IQ_MISSING,
  SENSOR_LEAKAGE_MISSING,
  LEDGER_AGGREGATE_MODE,
  SENSOR_REGISTRY_FULL,
  GUARD_REGISTRY_FULL,
  NO_HARDWARE_MEASUREMENT,
  BUDGET_EXCEEDED,
  CURRENT_INTERVAL_CLAMPED,
  DEBUG_ENABLED,
  NO_REPORT_CALLBACK,
  SENSOR_STATIC_NAME_CAUTION,
  SHORT_MAX_INTERVAL,
  SENSOR_READ_CALLBACK_MISSING,
  SOC_LOW_CONFIDENCE,
  SOC_NO_INITIAL_SOC,
  SOC_VOLTAGE_ONLY,
  SOC_FLAT_DISCHARGE_WARNING,
  HARVESTER_PLACEHOLDER,
  ENERGY_NEUTRAL_NOT_VERIFIED,
  ENERGY_INCOME_INSUFFICIENT,
  RADIO_TX_DOMINATES_ENERGY,
  RADIO_PROFILE_PLACEHOLDER,
  RADIO_NO_SLEEP_HOOK,
  RADIO_BATCH_BUFFER_LIMITED,
  RADIO_PAYLOAD_ESTIMATOR_PLACEHOLDER,
  RADIO_RX_WINDOW_COST_HIGH,
  RADIO_CONFIRMED_UPLINK_WARNING,
  HARVESTING_EFFICIENCY_PLACEHOLDER,
  INFERENCE_SKIPPED_ENERGY_DEFICIT,
  INFERENCE_BUDGET_MISSING,
  INFERENCE_RUN_LIMIT_REACHED,
  RADIO_BURST_CURRENT_HIGH,
  HARVESTER_INTERMITTENT_SOURCE,
  HARVESTER_EFFICIENCY_UNKNOWN,
  SOC_LOW_CONFIDENCE_FLAT_CURVE,
  BATTERY_PULSE_LIMITATION,
  BATTERY_PROTECTION_CIRCUIT_UNKNOWN,
  ENERGY_WINDOW_BUDGET_ACTIVE,
  ENERGY_WINDOW_BUDGET_EXCEEDED,
  MULTIPLE_CRITICAL_SENSORS,
  SENSOR_PRIORITY_CONFLICT,
  SENSOR_REGISTRY_NEAR_CAPACITY,
  DIAGNOSTIC_BUFFER_TRUNCATED
};

struct EcoDiagnostic {
  EcoDiagnosticCode code;
  EcoDiagnosticSeverity severity;
  const char* subject;

  EcoDiagnostic()
    : code(EcoDiagnosticCode::NO_HARDWARE_MEASUREMENT), severity(EcoDiagnosticSeverity::INFO), subject(0) {}

  EcoDiagnostic(EcoDiagnosticCode c, EcoDiagnosticSeverity s, const char* sub)
    : code(c), severity(s), subject(sub) {}
};

inline const char* ecoProfileConfidenceName(EcoProfileConfidence confidence);

struct EcoDiagnosticSnapshot {
  uint8_t copied;
  uint8_t total;
  bool truncated;

  EcoDiagnosticSnapshot() : copied(0), total(0), truncated(false) {}
  EcoDiagnosticSnapshot(uint8_t c, uint8_t t, bool tr) : copied(c), total(t), truncated(tr) {}
};

typedef float (*EcoReadCallback)();
typedef void (*EcoVoidCallback)();

struct EcoReport;
typedef void (*EcoReportCallback)(const EcoReport& report);
typedef size_t (*EcoPayloadSizeCallback)(const EcoReport& report);

struct EcoPowerReport {
  float socPercent;
  float estimatedDaysLeft;
  EcoProfileConfidence socConfidence;
  bool hasInitialSoc;
  bool hasVoltageEvidence;
  bool hasCoulombEvidence;
  bool energyNeutralConfigured;
  bool energyIncomeSufficient;
  EcoEnergyBalance energyBalance;
  float harvestedEnergy_mJ;
  float usableHarvestedEnergy_mJ;
  float cycleCost_mJ;
  float radioTxEnergy_mJ;
  float radioRxEnergy_mJ;
  float inferenceEnergy_mJ;
  float sleepEnergy_mJ;
  EcoProfileConfidence radioConfidence;
  EcoProfileConfidence harvesterConfidence;
  bool diagnosticsTruncated;

  EcoPowerReport()
    : socPercent(-1.0f), estimatedDaysLeft(-1.0f), socConfidence(EcoProfileConfidence::PLACEHOLDER),
      hasInitialSoc(false), hasVoltageEvidence(false), hasCoulombEvidence(false),
      energyNeutralConfigured(false), energyIncomeSufficient(false), energyBalance(EcoEnergyBalance::UNKNOWN),
      harvestedEnergy_mJ(0.0f), usableHarvestedEnergy_mJ(0.0f), cycleCost_mJ(0.0f),
      radioTxEnergy_mJ(0.0f), radioRxEnergy_mJ(0.0f), inferenceEnergy_mJ(0.0f), sleepEnergy_mJ(0.0f),
      radioConfidence(EcoProfileConfidence::PLACEHOLDER), harvesterConfidence(EcoProfileConfidence::PLACEHOLDER),
      diagnosticsTruncated(false) {}
};

struct EcoReport {
  const char* sensorName;
  float value;
  float previousValue;
  uint32_t intervalMs;
  bool firstRead;
  bool importantChange;
  bool readOk;
  bool budgetLimited;
  float estimatedDailyEnergy_mJ;
  EcoProfileConfidence boardConfidence;
  EcoProfileConfidence batteryConfidence;
  bool includesRegulatorIq;
  bool includesSensorLeakage;
  uint8_t batchSampleCount;
  float batchMinValue;
  float batchMaxValue;
  uint32_t batchFirstTimestampMs;
  uint32_t batchLastTimestampMs;
  EcoState state;
#if !ECOSENSE_PRESET_AVR_TINY
  mutable char text[ECOSENSE_REPORT_TEXT_SIZE];
#endif

  EcoReport()
    : sensorName(""), value(0.0f), previousValue(0.0f), intervalMs(0),
      firstRead(false), importantChange(false), readOk(false), budgetLimited(false),
      estimatedDailyEnergy_mJ(0.0f), boardConfidence(EcoProfileConfidence::PLACEHOLDER),
      batteryConfidence(EcoProfileConfidence::PLACEHOLDER), includesRegulatorIq(false),
      includesSensorLeakage(false), batchSampleCount(0), batchMinValue(0.0f), batchMaxValue(0.0f),
      batchFirstTimestampMs(0), batchLastTimestampMs(0), state(EcoState::REPORT)
#if !ECOSENSE_PRESET_AVR_TINY
      , text{0}
#endif
      {}

  const char* toText(char* buffer, size_t size) const {
    if (!buffer || size == 0) {
      return "";
    }
    const char* status = readOk ? "ok" : "read-failed";
#if ECOSENSE_PRESET_AVR_TINY
    snprintf(buffer, size,
             "eco %s %s %lu",
             sensorName ? sensorName : "sensor",
             status,
             (unsigned long)intervalMs);
#else
    const char* first = firstRead ? " first" : "";
    const char* important = importantChange ? " important-change" : "";
    const char* budget = budgetLimited ? " budget-soft-limit" : "";
    char valueText[16];
    char previousText[16];
    char dailyText[16];
    ecoFormatFloatFixed(valueText, sizeof(valueText), value, 3);
    ecoFormatFloatFixed(previousText, sizeof(previousText), previousValue, 3);
    ecoFormatFloatFixed(dailyText, sizeof(dailyText), estimatedDailyEnergy_mJ, 2);
    snprintf(buffer, size,
             "[EcoSensePower] sensor=%s value=%s previous=%s interval=%lu ms status=%s%s%s%s estDaily=%s mJ batch=%u profile=%s/%s regIq=%s leakage=%s",
             sensorName ? sensorName : "unknown",
             valueText,
             previousText,
             (unsigned long)intervalMs,
             status,
             first,
             important,
             budget,
             dailyText,
             (unsigned)batchSampleCount,
             ecoProfileConfidenceName(boardConfidence),
             ecoProfileConfidenceName(batteryConfidence),
             includesRegulatorIq ? "yes" : "no",
             includesSensorLeakage ? "yes" : "no");
#endif
    return buffer;
  }

  const char* toText() const {
#if ECOSENSE_PRESET_AVR_TINY
    static char compactText[ECOSENSE_REPORT_TEXT_SIZE];
    return toText(compactText, sizeof(compactText));
#else
    return toText(text, sizeof(text));
#endif
  }
};

inline const char* ecoStateName(EcoState state) {
  switch (state) {
    case EcoState::INIT: return "INIT";
    case EcoState::IDLE: return "IDLE";
    case EcoState::WAKEUP: return "WAKEUP";
    case EcoState::SENSE: return "SENSE";
    case EcoState::PROCESS: return "PROCESS";
    case EcoState::REPORT: return "REPORT";
    case EcoState::SLEEP: return "SLEEP";
    default: return "UNKNOWN";
  }
}

inline const char* ecoEnergyStateName(EcoEnergyState state) {
  switch (state) {
    case EcoEnergyState::SLEEP: return "SLEEP";
    case EcoEnergyState::WAKEUP: return "WAKEUP";
    case EcoEnergyState::SENSOR_WARMUP: return "SENSOR_WARMUP";
    case EcoEnergyState::SENSOR_READ: return "SENSOR_READ";
    case EcoEnergyState::PROCESS: return "PROCESS";
    case EcoEnergyState::REPORT: return "REPORT";
    case EcoEnergyState::RADIO_TX: return "RADIO_TX";
    case EcoEnergyState::RADIO_RX: return "RADIO_RX";
    case EcoEnergyState::RADIO_SLEEP: return "RADIO_SLEEP";
    case EcoEnergyState::INFERENCE: return "INFERENCE";
    case EcoEnergyState::IDLE: return "IDLE";
    case EcoEnergyState::GUARD: return "GUARD";
    default: return "UNKNOWN";
  }
}

inline const char* ecoDiagnosticSeverityName(EcoDiagnosticSeverity severity) {
  switch (severity) {
    case EcoDiagnosticSeverity::INFO: return "INFO";
    case EcoDiagnosticSeverity::WARNING: return "WARNING";
    case EcoDiagnosticSeverity::RISK: return "RISK";
    case EcoDiagnosticSeverity::CRITICAL: return "CRITICAL";
    default: return "UNKNOWN";
  }
}


inline const char* ecoEnergyBalanceName(EcoEnergyBalance balance) {
  switch (balance) {
    case EcoEnergyBalance::DEFICIT: return "DEFICIT";
    case EcoEnergyBalance::NEUTRAL: return "NEUTRAL";
    case EcoEnergyBalance::SURPLUS: return "SURPLUS";
    case EcoEnergyBalance::UNKNOWN:
    default: return "UNKNOWN";
  }
}

inline const char* ecoProfileConfidenceName(EcoProfileConfidence confidence) {
  switch (confidence) {
    case EcoProfileConfidence::PLACEHOLDER: return "PLACEHOLDER";
    case EcoProfileConfidence::DATASHEET: return "DATASHEET";
    case EcoProfileConfidence::MEASURED: return "MEASURED";
    default: return "UNKNOWN";
  }
}

inline const char* ecoDiagnosticCodeName(EcoDiagnosticCode code) {
  switch (code) {
    case EcoDiagnosticCode::GENERIC_BOARD_PROFILE: return "GENERIC_BOARD_PROFILE";
    case EcoDiagnosticCode::BOARD_PROFILE_PLACEHOLDER: return "BOARD_PROFILE_PLACEHOLDER";
    case EcoDiagnosticCode::REAL_SLEEP_BACKEND_MISSING: return "REAL_SLEEP_BACKEND_MISSING";
    case EcoDiagnosticCode::ESP32_WIRELESS_GUARD_MISSING: return "ESP32_WIRELESS_GUARD_MISSING";
    case EcoDiagnosticCode::SENSOR_NO_SLEEP_CALLBACK: return "SENSOR_NO_SLEEP_CALLBACK";
    case EcoDiagnosticCode::SENSOR_NO_CALIBRATED_CURRENT: return "SENSOR_NO_CALIBRATED_CURRENT";
    case EcoDiagnosticCode::BATTERY_PROFILE_MISSING: return "BATTERY_PROFILE_MISSING";
    case EcoDiagnosticCode::BATTERY_PROFILE_PLACEHOLDER: return "BATTERY_PROFILE_PLACEHOLDER";
    case EcoDiagnosticCode::REGULATOR_IQ_MISSING: return "REGULATOR_IQ_MISSING";
    case EcoDiagnosticCode::SENSOR_LEAKAGE_MISSING: return "SENSOR_LEAKAGE_MISSING";
    case EcoDiagnosticCode::LEDGER_AGGREGATE_MODE: return "LEDGER_AGGREGATE_MODE";
    case EcoDiagnosticCode::SENSOR_REGISTRY_FULL: return "SENSOR_REGISTRY_FULL";
    case EcoDiagnosticCode::GUARD_REGISTRY_FULL: return "GUARD_REGISTRY_FULL";
    case EcoDiagnosticCode::NO_HARDWARE_MEASUREMENT: return "NO_HARDWARE_MEASUREMENT";
    case EcoDiagnosticCode::BUDGET_EXCEEDED: return "BUDGET_EXCEEDED";
    case EcoDiagnosticCode::CURRENT_INTERVAL_CLAMPED: return "CURRENT_INTERVAL_CLAMPED";
    case EcoDiagnosticCode::DEBUG_ENABLED: return "DEBUG_ENABLED";
    case EcoDiagnosticCode::NO_REPORT_CALLBACK: return "NO_REPORT_CALLBACK";
    case EcoDiagnosticCode::SENSOR_STATIC_NAME_CAUTION: return "SENSOR_STATIC_NAME_CAUTION";
    case EcoDiagnosticCode::SHORT_MAX_INTERVAL: return "SHORT_MAX_INTERVAL";
    case EcoDiagnosticCode::SENSOR_READ_CALLBACK_MISSING: return "SENSOR_READ_CALLBACK_MISSING";
    case EcoDiagnosticCode::SOC_LOW_CONFIDENCE: return "SOC_LOW_CONFIDENCE";
    case EcoDiagnosticCode::SOC_NO_INITIAL_SOC: return "SOC_NO_INITIAL_SOC";
    case EcoDiagnosticCode::SOC_VOLTAGE_ONLY: return "SOC_VOLTAGE_ONLY";
    case EcoDiagnosticCode::SOC_FLAT_DISCHARGE_WARNING: return "SOC_FLAT_DISCHARGE_WARNING";
    case EcoDiagnosticCode::HARVESTER_PLACEHOLDER: return "HARVESTER_PLACEHOLDER";
    case EcoDiagnosticCode::ENERGY_NEUTRAL_NOT_VERIFIED: return "ENERGY_NEUTRAL_NOT_VERIFIED";
    case EcoDiagnosticCode::ENERGY_INCOME_INSUFFICIENT: return "ENERGY_INCOME_INSUFFICIENT";
    case EcoDiagnosticCode::RADIO_TX_DOMINATES_ENERGY: return "RADIO_TX_DOMINATES_ENERGY";
    case EcoDiagnosticCode::RADIO_PROFILE_PLACEHOLDER: return "RADIO_PROFILE_PLACEHOLDER";
    case EcoDiagnosticCode::RADIO_NO_SLEEP_HOOK: return "RADIO_NO_SLEEP_HOOK";
    case EcoDiagnosticCode::RADIO_BATCH_BUFFER_LIMITED: return "RADIO_BATCH_BUFFER_LIMITED";
    case EcoDiagnosticCode::RADIO_PAYLOAD_ESTIMATOR_PLACEHOLDER: return "RADIO_PAYLOAD_ESTIMATOR_PLACEHOLDER";
    case EcoDiagnosticCode::RADIO_RX_WINDOW_COST_HIGH: return "RADIO_RX_WINDOW_COST_HIGH";
    case EcoDiagnosticCode::RADIO_CONFIRMED_UPLINK_WARNING: return "RADIO_CONFIRMED_UPLINK_WARNING";
    case EcoDiagnosticCode::HARVESTING_EFFICIENCY_PLACEHOLDER: return "HARVESTING_EFFICIENCY_PLACEHOLDER";
    case EcoDiagnosticCode::INFERENCE_SKIPPED_ENERGY_DEFICIT: return "INFERENCE_SKIPPED_ENERGY_DEFICIT";
    case EcoDiagnosticCode::INFERENCE_BUDGET_MISSING: return "INFERENCE_BUDGET_MISSING";
    case EcoDiagnosticCode::INFERENCE_RUN_LIMIT_REACHED: return "INFERENCE_RUN_LIMIT_REACHED";
    case EcoDiagnosticCode::RADIO_BURST_CURRENT_HIGH: return "RADIO_BURST_CURRENT_HIGH";
    case EcoDiagnosticCode::HARVESTER_INTERMITTENT_SOURCE: return "HARVESTER_INTERMITTENT_SOURCE";
    case EcoDiagnosticCode::HARVESTER_EFFICIENCY_UNKNOWN: return "HARVESTER_EFFICIENCY_UNKNOWN";
    case EcoDiagnosticCode::SOC_LOW_CONFIDENCE_FLAT_CURVE: return "SOC_LOW_CONFIDENCE_FLAT_CURVE";
    case EcoDiagnosticCode::BATTERY_PULSE_LIMITATION: return "BATTERY_PULSE_LIMITATION";
    case EcoDiagnosticCode::BATTERY_PROTECTION_CIRCUIT_UNKNOWN: return "BATTERY_PROTECTION_CIRCUIT_UNKNOWN";
    case EcoDiagnosticCode::ENERGY_WINDOW_BUDGET_ACTIVE: return "ENERGY_WINDOW_BUDGET_ACTIVE";
    case EcoDiagnosticCode::ENERGY_WINDOW_BUDGET_EXCEEDED: return "ENERGY_WINDOW_BUDGET_EXCEEDED";
    case EcoDiagnosticCode::MULTIPLE_CRITICAL_SENSORS: return "MULTIPLE_CRITICAL_SENSORS";
    case EcoDiagnosticCode::SENSOR_PRIORITY_CONFLICT: return "SENSOR_PRIORITY_CONFLICT";
    case EcoDiagnosticCode::SENSOR_REGISTRY_NEAR_CAPACITY: return "SENSOR_REGISTRY_NEAR_CAPACITY";
    case EcoDiagnosticCode::DIAGNOSTIC_BUFFER_TRUNCATED: return "DIAGNOSTIC_BUFFER_TRUNCATED";
    default: return "UNKNOWN_DIAGNOSTIC";
  }
}

inline const char* ecoDiagnosticMessage(EcoDiagnosticCode code) {
  switch (code) {
    case EcoDiagnosticCode::GENERIC_BOARD_PROFILE: return "Generic board fallback is active; replace it with a measured or datasheet board profile before battery-life claims.";
    case EcoDiagnosticCode::BOARD_PROFILE_PLACEHOLDER: return "Board profile confidence is placeholder; board current values need datasheet or measured evidence.";
    case EcoDiagnosticCode::REAL_SLEEP_BACKEND_MISSING: return "Generic delay fallback active; real sleep backend missing for this target.";
    case EcoDiagnosticCode::ESP32_WIRELESS_GUARD_MISSING: return "ESP32 backend active but no wireless guard is configured.";
    case EcoDiagnosticCode::SENSOR_NO_SLEEP_CALLBACK: return "Sensor has no sensor-specific onSleep callback; a separate guard may still be configured.";
    case EcoDiagnosticCode::SENSOR_NO_CALIBRATED_CURRENT: return "Sensor has no calibrated current profile.";
    case EcoDiagnosticCode::BATTERY_PROFILE_MISSING: return "Battery profile was not explicitly set.";
    case EcoDiagnosticCode::BATTERY_PROFILE_PLACEHOLDER: return "Battery profile is placeholder/nominal; capacity depends on real conditions.";
    case EcoDiagnosticCode::REGULATOR_IQ_MISSING: return "Energy estimate does not include regulator quiescent current.";
    case EcoDiagnosticCode::SENSOR_LEAKAGE_MISSING: return "Energy estimate does not include sensor leakage current.";
    case EcoDiagnosticCode::LEDGER_AGGREGATE_MODE: return "Ledger aggregate mode active; per-state details were truncated.";
    case EcoDiagnosticCode::SENSOR_REGISTRY_FULL: return "Sensor registry full; extra sensor() calls return invalid no-op config.";
    case EcoDiagnosticCode::GUARD_REGISTRY_FULL: return "Guard registry full; extra guard() calls return invalid no-op config.";
    case EcoDiagnosticCode::NO_HARDWARE_MEASUREMENT: return "No hardware current measurement evidence is available inside the library.";
    case EcoDiagnosticCode::BUDGET_EXCEEDED: return "Estimated daily energy exceeds maxDailyEnergy_mJ; adaptive interval was increased.";
    case EcoDiagnosticCode::CURRENT_INTERVAL_CLAMPED: return "One or more currentInterval values were clamped to min/max contract limits.";
    case EcoDiagnosticCode::DEBUG_ENABLED: return "Serial/debug mode is enabled and increases active time/current.";
    case EcoDiagnosticCode::NO_REPORT_CALLBACK: return "No report callback configured.";
    case EcoDiagnosticCode::SENSOR_STATIC_NAME_CAUTION: return "Sensor/guard names should have static lifetime in long-running sketches.";
    case EcoDiagnosticCode::SHORT_MAX_INTERVAL: return "Max interval is short; adaptive sampling may not significantly reduce energy.";
    case EcoDiagnosticCode::SENSOR_READ_CALLBACK_MISSING: return "Sensor has no read callback.";
    case EcoDiagnosticCode::SOC_LOW_CONFIDENCE: return "SoC estimate confidence is low; add initial SoC, voltage, or measured current evidence.";
    case EcoDiagnosticCode::SOC_NO_INITIAL_SOC: return "SoC tracker has no initial SoC; coulomb-based remaining capacity is unknown.";
    case EcoDiagnosticCode::SOC_VOLTAGE_ONLY: return "SoC is voltage-only; accuracy depends strongly on battery chemistry and load.";
    case EcoDiagnosticCode::SOC_FLAT_DISCHARGE_WARNING: return "Battery chemistry has a flat discharge curve; voltage-only SoC can be misleading.";
    case EcoDiagnosticCode::HARVESTER_PLACEHOLDER: return "Harvester energy income profile is placeholder or unavailable.";
    case EcoDiagnosticCode::ENERGY_NEUTRAL_NOT_VERIFIED: return "Energy-neutral operation is configured but not verified by hardware measurements.";
    case EcoDiagnosticCode::ENERGY_INCOME_INSUFFICIENT: return "Harvested energy over the interval is below estimated cycle cost; interval stretching may be needed.";
    case EcoDiagnosticCode::RADIO_TX_DOMINATES_ENERGY: return "Radio TX appears to dominate the cycle energy budget.";
    case EcoDiagnosticCode::RADIO_PROFILE_PLACEHOLDER: return "Radio current/duration profile is placeholder.";
    case EcoDiagnosticCode::RADIO_NO_SLEEP_HOOK: return "Radio adapter does not provide a verified low-power sleep hook.";
    case EcoDiagnosticCode::RADIO_BATCH_BUFFER_LIMITED: return "Radio batch buffer limit may force extra transmissions.";
    case EcoDiagnosticCode::RADIO_PAYLOAD_ESTIMATOR_PLACEHOLDER: return "Radio payload size estimator is using the conservative default estimate.";
    case EcoDiagnosticCode::RADIO_RX_WINDOW_COST_HIGH: return "Radio RX window energy is configured and may materially affect duty-cycle energy.";
    case EcoDiagnosticCode::RADIO_CONFIRMED_UPLINK_WARNING: return "Confirmed uplink / ACK behavior can add RX windows and retransmission energy.";
    case EcoDiagnosticCode::HARVESTING_EFFICIENCY_PLACEHOLDER: return "Harvesting storage/charging efficiency is placeholder; usable energy may be lower than input energy.";
    case EcoDiagnosticCode::INFERENCE_SKIPPED_ENERGY_DEFICIT: return "Non-critical inference was skipped because the energy policy reports a deficit.";
    case EcoDiagnosticCode::INFERENCE_BUDGET_MISSING: return "Anomaly/ML hook is configured without a measured inference energy budget.";
    case EcoDiagnosticCode::INFERENCE_RUN_LIMIT_REACHED: return "Inference run limit was reached in the active 24h window.";
    case EcoDiagnosticCode::RADIO_BURST_CURRENT_HIGH: return "Radio profile has high burst-current risk; supply and storage must handle peak current.";
    case EcoDiagnosticCode::HARVESTER_INTERMITTENT_SOURCE: return "Harvester source is intermittent; storage and duty-cycle assumptions must be documented.";
    case EcoDiagnosticCode::HARVESTER_EFFICIENCY_UNKNOWN: return "Harvester conversion/storage efficiency is placeholder or unknown.";
    case EcoDiagnosticCode::SOC_LOW_CONFIDENCE_FLAT_CURVE: return "Voltage-only SoC is low-confidence for flat-discharge chemistries.";
    case EcoDiagnosticCode::BATTERY_PULSE_LIMITATION: return "Battery chemistry/profile has pulse-current limitations; radio bursts may reduce usable capacity.";
    case EcoDiagnosticCode::BATTERY_PROTECTION_CIRCUIT_UNKNOWN: return "Rechargeable lithium profile needs documented charger/protection/regulator behavior.";
    case EcoDiagnosticCode::ENERGY_WINDOW_BUDGET_ACTIVE: return "Energy contract has a per-window budget; validate cycle timing and duty-cycle assumptions.";
    case EcoDiagnosticCode::ENERGY_WINDOW_BUDGET_EXCEEDED: return "Estimated cycle energy may exceed the configured per-window budget.";
    case EcoDiagnosticCode::MULTIPLE_CRITICAL_SENSORS: return "Multiple sensors are marked critical; verify priority scheduling reflects real operational priorities.";
    case EcoDiagnosticCode::SENSOR_PRIORITY_CONFLICT: return "All registered sensors are critical; priority scheduling loses meaning.";
    case EcoDiagnosticCode::SENSOR_REGISTRY_NEAR_CAPACITY: return "Sensor registry is near capacity; additional sensors may be rejected.";
    case EcoDiagnosticCode::DIAGNOSTIC_BUFFER_TRUNCATED: return "Diagnostic buffer is full; some diagnostics were truncated.";
    default: return "Unknown diagnostic.";
  }
}

inline uint8_t ecoEnergyStateIndex(EcoEnergyState state) {
  return static_cast<uint8_t>(state);
}

inline uint32_t ecoMinU32(uint32_t a, uint32_t b) {
  return (a < b) ? a : b;
}

inline uint32_t ecoMaxU32(uint32_t a, uint32_t b) {
  return (a > b) ? a : b;
}

#endif
