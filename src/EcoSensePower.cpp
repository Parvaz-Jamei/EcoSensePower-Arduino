#include "EcoSensePower.h"

EcoSensePower::EcoSensePower()
  : runtime_()
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
    , doctor_()
#endif
{}

bool EcoSensePower::begin() {
  return runtime_.begin();
}

void EcoSensePower::loop() {
  runtime_.loop();
}

EcoSensorConfig& EcoSensePower::sensor(const char* name) {
  return runtime_.sensor(name);
}

EcoGuardConfig& EcoSensePower::guard(const char* name) {
  return runtime_.guard(name);
}

EcoSensePower& EcoSensePower::battery(const BatteryProfile& profile) {
  runtime_.setBatteryProfile(profile);
  return *this;
}

EcoSensePower& EcoSensePower::board(const BoardProfile& profile) {
  runtime_.setBoardProfile(profile);
  return *this;
}

EcoSensePower& EcoSensePower::onReport(EcoReportCallback callback) {
  runtime_.setReportCallback(callback);
  return *this;
}

EcoSensePower& EcoSensePower::enableDebug(bool enabled) {
  runtime_.setDebug(enabled);
  return *this;
}

SoCTracker& EcoSensePower::socTracker() { return runtime_.socTracker(); }
const SoCTracker& EcoSensePower::socTracker() const { return runtime_.socTracker(); }
EnergyBudgetManager& EcoSensePower::energyPolicy() { return runtime_.energyPolicy(); }
const EnergyBudgetManager& EcoSensePower::energyPolicy() const { return runtime_.energyPolicy(); }
EcoSensePower& EcoSensePower::harvester(HarvesterBase* harvester) { runtime_.setHarvester(harvester); return *this; }
EcoSensePower& EcoSensePower::radio(RadioEnergyAdapter* radio) { runtime_.setRadio(radio); return *this; }
EcoSensePower& EcoSensePower::reportPayloadEstimator(EcoPayloadSizeCallback callback) { runtime_.setPayloadEstimator(callback); return *this; }
RadioBatcher& EcoSensePower::reporting() { return runtime_.reporting(); }
const RadioBatcher& EcoSensePower::reporting() const { return runtime_.reporting(); }
EcoPowerReport EcoSensePower::powerReport() const {
  EcoPowerReport report = runtime_.powerReport();
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  EcoDiagnostic buffer[ECOSENSE_MAX_DIAGNOSTICS];
  EcoDiagnosticSnapshot snapshot = doctor_.collectSnapshot(runtime_, buffer, ECOSENSE_MAX_DIAGNOSTICS);
  report.diagnosticsTruncated = snapshot.truncated;
#else
  report.diagnosticsTruncated = false;
#endif
  return report;
}

void EcoSensePower::printDiagnostics(Print& out) const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  doctor_.print(runtime_, out);
#else
  (void)runtime_;
  out.println(F("[EcoSensePower Doctor] compact AVR diagnostics storage disabled"));
#endif
}

void EcoSensePower::printDiagnostics(Print& out, EcoDiagnosticSeverity minSeverity) const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  doctor_.print(runtime_, out, minSeverity);
#else
  (void)runtime_;
  (void)minSeverity;
  out.println(F("[EcoSensePower Doctor] compact AVR diagnostics storage disabled"));
#endif
}

uint8_t EcoSensePower::collectDiagnostics(EcoDiagnostic* buffer, uint8_t maxCount) const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  return doctor_.collect(runtime_, buffer, maxCount);
#else
  (void)buffer;
  (void)maxCount;
  return 0;
#endif
}

EcoDiagnosticSnapshot EcoSensePower::collectDiagnosticsSnapshot(EcoDiagnostic* buffer, uint8_t maxCount) const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  return doctor_.collectSnapshot(runtime_, buffer, maxCount);
#else
  (void)buffer;
  return EcoDiagnosticSnapshot(0, 0, maxCount == 0);
#endif
}

bool EcoSensePower::diagnosticsTruncated() const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  EcoDiagnostic buffer[ECOSENSE_MAX_DIAGNOSTICS];
  EcoDiagnosticSnapshot snapshot = doctor_.collectSnapshot(runtime_, buffer, ECOSENSE_MAX_DIAGNOSTICS);
  return snapshot.truncated;
#else
  return false;
#endif
}

uint8_t EcoSensePower::diagnosticCount() const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  return doctor_.collect(runtime_);
#else
  return 0;
#endif
}

EcoDiagnostic EcoSensePower::diagnosticAt(uint8_t index) const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  doctor_.collect(runtime_);
  return doctor_.diagnosticAt(index);
#else
  (void)index;
  return EcoDiagnostic();
#endif
}

bool EcoSensePower::hasCriticalDiagnostics() const {
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  doctor_.collect(runtime_);
  return doctor_.hasCriticalDiagnostics();
#else
  return false;
#endif
}

const char* EcoSensePower::backendName() const {
  return runtime_.backendName();
}

bool EcoSensePower::backendIsRealSleep() const {
  return runtime_.backendIsRealSleep();
}

bool EcoSensePower::sensorRegistryFull() const {
  return runtime_.sensorRegistryFull();
}

bool EcoSensePower::guardRegistryFull() const {
  return runtime_.guardRegistryFull();
}

EnergyLedger& EcoSensePower::ledger() {
  return runtime_.ledger();
}

const EnergyLedger& EcoSensePower::ledger() const {
  return runtime_.ledger();
}

EcoRuntime& EcoSensePower::runtime() {
  return runtime_;
}

const EcoRuntime& EcoSensePower::runtime() const {
  return runtime_;
}
