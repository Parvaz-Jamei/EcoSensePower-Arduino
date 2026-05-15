#ifndef ECOSENSEPOWER_H
#define ECOSENSEPOWER_H

#include <Arduino.h>
#include "core/EcoSensePowerConfig.h"
#include "core/EcoTypes.h"
#include "core/EcoRuntime.h"
#include "core/EcoScheduler.h"
#include "core/EnergyContract.h"
#include "core/AdaptiveSampler.h"
#include "core/EnergyModel.h"
#include "core/EnergyLedger.h"
#include "core/PowerDoctor.h"
#include "core/PeripheralGuard.h"
#include "core/BatteryProfile.h"
#include "core/BoardProfile.h"
#include "core/SensorProfile.h"

#include "core/ProfileConfidence.h"
#include "core/BatteryChemistry.h"
#include "core/SoCTracker.h"
#include "core/EnergyBudgetManager.h"
#include "core/MeasuredProfile.h"
#include "harvester/HarvesterBase.h"
#include "harvester/SolarHarvester.h"
#include "harvester/PiezoHarvester.h"
#include "harvester/ThermoelectricHarvester.h"
#include "harvester/WindHarvester.h"
#include "util/VoltageDivider.h"
#include "radio/RadioEnergyAdapter.h"
#include "radio/GenericRadioProfile.h"
#include "radio/RadioBatcher.h"
#include "ml/InferenceBudget.h"
#include "ml/AnomalyHook.h"

class EcoSensePower {
public:
  EcoSensePower();

  bool begin();
  void loop();

  EcoSensorConfig& sensor(const char* name);
  EcoGuardConfig& guard(const char* name);
  EcoSensePower& battery(const BatteryProfile& profile);
  EcoSensePower& board(const BoardProfile& profile);
  EcoSensePower& onReport(EcoReportCallback callback);
  EcoSensePower& enableDebug(bool enabled = true);
  SoCTracker& socTracker();
  const SoCTracker& socTracker() const;
  EnergyBudgetManager& energyPolicy();
  const EnergyBudgetManager& energyPolicy() const;
  EcoSensePower& harvester(HarvesterBase* harvester);
  EcoSensePower& radio(RadioEnergyAdapter* radio);
  EcoSensePower& reportPayloadEstimator(EcoPayloadSizeCallback callback);
  RadioBatcher& reporting();
  const RadioBatcher& reporting() const;
  EcoPowerReport powerReport() const;

  void printDiagnostics(Print& out) const;
  void printDiagnostics(Print& out, EcoDiagnosticSeverity minSeverity) const;
  uint8_t collectDiagnostics(EcoDiagnostic* buffer, uint8_t maxCount) const;
  EcoDiagnosticSnapshot collectDiagnosticsSnapshot(EcoDiagnostic* buffer, uint8_t maxCount) const;
  bool diagnosticsTruncated() const;
  uint8_t diagnosticCount() const;
  EcoDiagnostic diagnosticAt(uint8_t index) const;
  bool hasCriticalDiagnostics() const;
  const char* backendName() const;
  bool backendIsRealSleep() const;
  bool sensorRegistryFull() const;
  bool guardRegistryFull() const;

  EnergyLedger& ledger();
  const EnergyLedger& ledger() const;

  EcoRuntime& runtime();
  const EcoRuntime& runtime() const;

private:
  EcoRuntime runtime_;
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  PowerDoctor doctor_;
#endif
};

#endif
