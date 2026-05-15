#include "core/EcoRuntime.h"
#include "arch/generic/SleepBackend.h"
#include "core/EnergyModel.h"
#include <string.h>
#include <math.h>

#if defined(ARDUINO_ARCH_AVR)
#include "arch/avr/SleepBackendAVR.h"
#endif

#if defined(ARDUINO_ARCH_ESP32)
#include "arch/esp32/SleepBackendESP32.h"
#endif

EcoSensorConfig::EcoSensorConfig()
  : slot_(0) {}

EcoSensorConfig::EcoSensorConfig(EcoSensorSlot* slot)
  : slot_(slot) {}

EcoSensorConfig& EcoSensorConfig::read(EcoReadCallback callback) {
  if (slot_) slot_->readCallback = callback;
  return *this;
}

EcoSensorConfig& EcoSensorConfig::warmupTimeMs(uint32_t value) {
  if (slot_) slot_->contract.warmupTimeMs = value;
  return *this;
}

EcoSensorConfig& EcoSensorConfig::minIntervalMs(uint32_t value) {
  if (slot_) {
    const bool currentWasDefault = (slot_->contract.currentIntervalMs == ECOSENSE_DEFAULT_MIN_INTERVAL_MS);
    slot_->contract.minIntervalMs = value;
    if (currentWasDefault || slot_->contract.currentIntervalMs < value) {
      slot_->contract.currentIntervalMs = value;
      slot_->currentIntervalClamped = true;
    }
    if (!slot_->contract.validate()) {
      slot_->currentIntervalClamped = true;
    }
  }
  return *this;
}

EcoSensorConfig& EcoSensorConfig::maxIntervalMs(uint32_t value) {
  if (slot_) {
    slot_->contract.maxIntervalMs = value;
    if (!slot_->contract.validate()) {
      slot_->currentIntervalClamped = true;
    }
  }
  return *this;
}

EcoSensorConfig& EcoSensorConfig::initialIntervalMs(uint32_t value) {
  if (slot_) {
    slot_->contract.currentIntervalMs = value;
    if (!slot_->contract.validate()) {
      slot_->currentIntervalClamped = true;
    }
  }
  return *this;
}

EcoSensorConfig& EcoSensorConfig::changeThreshold(float value) {
  if (slot_) {
    slot_->contract.changeThreshold = value;
    if (!slot_->contract.validate()) {
      slot_->currentIntervalClamped = true;
    }
  }
  return *this;
}

EcoSensorConfig& EcoSensorConfig::priority(EcoPriority value) {
  if (slot_) slot_->contract.priority = value;
  return *this;
}

EcoSensorConfig& EcoSensorConfig::maxDailyEnergy_mJ(uint32_t value) {
  if (slot_) slot_->contract.maxDailyEnergy_mJ = value;
  return *this;
}

EcoSensorConfig& EcoSensorConfig::maxEnergyPerWindow_mJ(float value, uint32_t windowMs) {
  if (slot_) slot_->contract.maxEnergyPerWindow_mJ(value, windowMs);
  return *this;
}

EcoSensorConfig& EcoSensorConfig::energyWindowMs(uint32_t windowMs) {
  if (slot_) slot_->contract.energyWindow(windowMs);
  return *this;
}

EcoSensorConfig& EcoSensorConfig::onWake(EcoVoidCallback callback) {
  if (slot_) slot_->wakeCallback = callback;
  return *this;
}

EcoSensorConfig& EcoSensorConfig::onSleep(EcoVoidCallback callback) {
  if (slot_) slot_->sleepCallback = callback;
  return *this;
}

EcoSensorConfig& EcoSensorConfig::calibratedCurrent(bool measured) {
  if (slot_) slot_->calibratedCurrent = measured;
  return *this;
}

EcoSensorConfig& EcoSensorConfig::onAnomaly(EcoAnomalyCallback callback) {
  if (slot_) slot_->anomalyCallback = callback;
  return *this;
}

InferenceBudget& EcoSensorConfig::inferenceCost() {
  static InferenceBudget invalidBudget;
  return slot_ ? slot_->inferenceBudget : invalidBudget;
}

bool EcoSensorConfig::valid() const {
  return slot_ != 0;
}

EcoRuntime::EcoRuntime()
  : invalidConfig_(), invalidGuardConfig_(), sensorCount_(0), guardCount_(0), state_(EcoState::INIT),
    reportCallback_(0), debugEnabled_(false), initialized_(false), hasBatteryProfile_(false),
    sensorRegistryFull_(false), guardRegistryFull_(false), guardsAwake_(false), battery_(BatteryProfile::AA_Alkaline()),
    board_(BoardProfile::Generic()), sampler_(), scheduler_(), ledger_(),
#if ECOSENSE_ENABLE_SOC_TRACKER
    socTracker_(),
#endif
    energyPolicy_(),
    harvester_(0), radio_(0), payloadEstimator_(0), radioBatcher_(),
    lastEnergyIncomeInsufficient_(false), lastRadioBatchLimited_(false) {
  for (uint8_t i = 0; i < ECOSENSE_MAX_SENSORS; ++i) {
    configs_[i] = EcoSensorConfig(&sensors_[i]);
  }
#if ECOSENSE_MAX_GUARDS > 0
  for (uint8_t i = 0; i < ECOSENSE_MAX_GUARDS; ++i) {
    guardConfigs_[i] = EcoGuardConfig(&guards_[i]);
  }
#endif
}

bool EcoRuntime::begin() {
  state_ = EcoState::INIT;
  traceState(state_);
  uint32_t now = EcoTime::nowMs();
  for (uint8_t i = 0; i < sensorCount_; ++i) {
    if (!sensors_[i].contract.validate()) {
      sensors_[i].currentIntervalClamped = true;
    }
    sensors_[i].nextDueMs = now;
  }
  guardsAwake_ = false;
  initialized_ = true;
  state_ = EcoState::IDLE;
  traceState(state_);
  return true;
}

void EcoRuntime::loop() {
  if (!initialized_) {
    begin();
  }

  const uint32_t now = EcoTime::nowMs();
  const int8_t index = findDueSensor(now);

  if (index >= 0) {
    processSensor(sensors_[(uint8_t)index], now);
    return;
  }

  state_ = EcoState::IDLE;
  traceState(state_);
  const uint32_t nextDeadline = nextDeadlineMs();
  const uint32_t sleepRequest = (nextDeadline > now) ? (nextDeadline - now) : 0;
  const uint32_t sleepMs = scheduler_.clampSleepMs(sleepRequest);
  if (sleepMs > 0) {
    if (!ledger_.cycleOpen()) {
      ledger_.beginCycle();
    }
    state_ = EcoState::SLEEP;
    traceState(state_);
    runGuardsSleep();
    ledger_.record(EcoEnergyState::SLEEP, sleepMs, currentFor(EcoEnergyState::SLEEP), voltage());
    backendSleep(sleepMs);
  }
}

EcoSensorConfig& EcoRuntime::sensor(const char* name) {
  EcoSensorSlot* slot = allocateSensor(name);
  if (!slot) {
    sensorRegistryFull_ = true;
    return invalidConfig_;
  }
  return configs_[(uint8_t)(slot - sensors_)];
}

EcoGuardConfig& EcoRuntime::guard(const char* name) {
  EcoGuardSlot* slot = allocateGuard(name);
  if (!slot) {
    guardRegistryFull_ = true;
    return invalidGuardConfig_;
  }
#if ECOSENSE_MAX_GUARDS > 0
  return guardConfigs_[(uint8_t)(slot - guards_)];
#else
  (void)slot;
  return invalidGuardConfig_;
#endif
}

void EcoRuntime::setBatteryProfile(const BatteryProfile& profile) {
  battery_ = profile;
#if ECOSENSE_ENABLE_SOC_TRACKER
  socTracker_.battery(profile);
#endif
  hasBatteryProfile_ = true;
}

void EcoRuntime::setBoardProfile(const BoardProfile& profile) {
  board_ = profile;
}

void EcoRuntime::setReportCallback(EcoReportCallback callback) {
  reportCallback_ = callback;
}

void EcoRuntime::setDebug(bool enabled) {
  debugEnabled_ = enabled;
}

SoCTracker& EcoRuntime::socTracker() { static SoCTracker fallback;
#if ECOSENSE_ENABLE_SOC_TRACKER
  return socTracker_;
#else
  return fallback;
#endif
}
const SoCTracker& EcoRuntime::socTracker() const { static SoCTracker fallback;
#if ECOSENSE_ENABLE_SOC_TRACKER
  return socTracker_;
#else
  return fallback;
#endif
}
EnergyBudgetManager& EcoRuntime::energyPolicy() { return energyPolicy_; }
const EnergyBudgetManager& EcoRuntime::energyPolicy() const { return energyPolicy_; }
void EcoRuntime::setHarvester(HarvesterBase* harvester) {
  harvester_ = harvester;
  energyPolicy_.harvester(harvester);
}
void EcoRuntime::setRadio(RadioEnergyAdapter* radio) { radio_ = radio; }
void EcoRuntime::setPayloadEstimator(EcoPayloadSizeCallback callback) { payloadEstimator_ = callback; }
RadioBatcher& EcoRuntime::reporting() { return radioBatcher_; }
const RadioBatcher& EcoRuntime::reporting() const { return radioBatcher_; }
RadioEnergyAdapter* EcoRuntime::radioAdapter() const { return radio_; }
bool EcoRuntime::hasRadioAdapter() const { return radio_ != 0; }
bool EcoRuntime::radioProfilePlaceholder() const { return radio_ != 0 && radio_->confidence() == EcoProfileConfidence::PLACEHOLDER; }
bool EcoRuntime::radioTxDominatesEnergy() const {
#if ECOSENSE_ENABLE_FULL_LEDGER
  const float total = ledger_.cycleEnergyMilliJoules();
  if (total <= 0.0f) return false;
  return (ledger_.cycleEnergyForState(EcoEnergyState::RADIO_TX) / total) > 0.60f;
#else
  return false;
#endif
}
bool EcoRuntime::radioPayloadEstimatorPlaceholder() const { return radio_ != 0 && payloadEstimator_ == 0; }
bool EcoRuntime::radioBatchBufferLimited() const { return lastRadioBatchLimited_; }
bool EcoRuntime::radioRxWindowConfigured() const { return radio_ != 0 && radio_->expectsRxWindow(); }
bool EcoRuntime::radioConfirmedUplink() const { return radio_ != 0 && radio_->confirmedUplink(); }
EcoProfileConfidence EcoRuntime::radioConfidence() const { return radio_ ? radio_->confidence() : EcoProfileConfidence::PLACEHOLDER; }
bool EcoRuntime::harvestingEfficiencyPlaceholder() const { return energyPolicy_.targetNeutralEnabled() && energyPolicy_.efficiencyPlaceholder(); }
bool EcoRuntime::energyIncomeInsufficient() const { return lastEnergyIncomeInsufficient_; }
EcoPowerReport EcoRuntime::powerReport() const {
  EcoPowerReport r;
#if ECOSENSE_ENABLE_SOC_TRACKER
  const float avgCurrent = ledger_.averageCurrentMicroA(voltage());
  EcoSoCReport soc = socTracker_.report(avgCurrent);
  r.socPercent = soc.socPercent;
  r.estimatedDaysLeft = soc.estimatedDaysLeft;
  r.socConfidence = soc.confidence;
  r.hasInitialSoc = socTracker_.hasInitialSoc();
  r.hasVoltageEvidence = socTracker_.hasVoltageEvidence();
  r.hasCoulombEvidence = socTracker_.hasCoulombEvidence();
#else
  r.socPercent = -1.0f;
  r.estimatedDaysLeft = -1.0f;
  r.socConfidence = EcoProfileConfidence::PLACEHOLDER;
  r.hasInitialSoc = false;
  r.hasVoltageEvidence = false;
  r.hasCoulombEvidence = false;
#endif
  r.energyNeutralConfigured = energyPolicy_.targetNeutralEnabled();
  r.cycleCost_mJ = ledger_.cycleEnergyMilliJoules();
  const uint32_t now = EcoTime::nowMs();
  const uint32_t interval = EcoTime::remainingUntil(now, nextDeadlineMs());
  r.harvestedEnergy_mJ = energyPolicy_.inputEnergyDuringInterval_mJ(interval);
  r.usableHarvestedEnergy_mJ = energyPolicy_.usableEnergyDuringInterval_mJ(interval);
  r.energyIncomeSufficient = energyPolicy_.incomeCoversCycle(interval, r.cycleCost_mJ);
  r.energyBalance = energyPolicy_.energyBalance(interval, r.cycleCost_mJ, r.socPercent);
  r.radioTxEnergy_mJ = ledger_.cycleEnergyForState(EcoEnergyState::RADIO_TX);
  r.radioRxEnergy_mJ = ledger_.cycleEnergyForState(EcoEnergyState::RADIO_RX);
  r.inferenceEnergy_mJ = ledger_.cycleEnergyForState(EcoEnergyState::INFERENCE);
  r.sleepEnergy_mJ = ledger_.cycleEnergyForState(EcoEnergyState::SLEEP);
  r.radioConfidence = radio_ ? radio_->confidence() : EcoProfileConfidence::PLACEHOLDER;
  r.harvesterConfidence = energyPolicy_.confidence();
  r.diagnosticsTruncated = false;
  return r;
}

bool EcoRuntime::debugEnabled() const { return debugEnabled_; }
bool EcoRuntime::hasReportCallback() const { return reportCallback_ != 0; }
bool EcoRuntime::hasGenericBoardProfile() const { return board_.name && strcmp(board_.name, "Generic Arduino") == 0; }
bool EcoRuntime::hasBatteryProfile() const { return hasBatteryProfile_; }
bool EcoRuntime::sensorRegistryFull() const { return sensorRegistryFull_; }
bool EcoRuntime::guardRegistryFull() const { return guardRegistryFull_; }

bool EcoRuntime::hasEsp32WirelessGuard() const {
#if ECOSENSE_MAX_GUARDS > 0
  for (uint8_t i = 0; i < guardCount_; ++i) {
    if (guards_[i].active && guards_[i].esp32Wireless) {
      return true;
    }
  }
#endif
  return false;
}

bool EcoRuntime::hasAnyCurrentIntervalClamp() const {
  for (uint8_t i = 0; i < sensorCount_; ++i) {
    if (sensors_[i].currentIntervalClamped) {
      return true;
    }
  }
  return false;
}

bool EcoRuntime::guardsAwake() const {
  return guardsAwake_;
}

bool EcoRuntime::hasMatchingGuardName(const char* name) const {
  if (!name) {
    return false;
  }
#if ECOSENSE_MAX_GUARDS > 0
  for (uint8_t i = 0; i < guardCount_; ++i) {
    if (guards_[i].active && guards_[i].name && strcmp(guards_[i].name, name) == 0) {
      return true;
    }
  }
#endif
  return false;
}

const BatteryProfile& EcoRuntime::batteryProfile() const { return battery_; }
const BoardProfile& EcoRuntime::boardProfile() const { return board_; }
const EcoSensorSlot* EcoRuntime::sensors() const { return sensors_; }
uint8_t EcoRuntime::sensorCount() const { return sensorCount_; }
const EcoGuardSlot* EcoRuntime::guards() const {
#if ECOSENSE_MAX_GUARDS > 0
  return guards_;
#else
  return 0;
#endif
}
uint8_t EcoRuntime::guardCount() const { return guardCount_; }
EcoState EcoRuntime::state() const { return state_; }

const char* EcoRuntime::backendName() const {
#if defined(ARDUINO_ARCH_AVR)
  static AvrSleepBackend backend;
  return backend.name();
#elif defined(ARDUINO_ARCH_ESP32)
  static Esp32SleepBackend backend;
  return backend.name();
#else
  static GenericSleepBackend backend;
  return backend.name();
#endif
}

bool EcoRuntime::backendIsRealSleep() const {
#if defined(ARDUINO_ARCH_AVR)
  static AvrSleepBackend backend;
  return backend.isRealSleep();
#elif defined(ARDUINO_ARCH_ESP32)
  static Esp32SleepBackend backend;
  return backend.isRealSleep();
#else
  static GenericSleepBackend backend;
  return backend.isRealSleep();
#endif
}

bool EcoRuntime::supportsPowerDown() const {
#if defined(ARDUINO_ARCH_AVR)
  static AvrSleepBackend backend;
  return backend.supportsPowerDown();
#elif defined(ARDUINO_ARCH_ESP32)
  return true;
#else
  return false;
#endif
}

EnergyLedger& EcoRuntime::ledger() { return ledger_; }
const EnergyLedger& EcoRuntime::ledger() const { return ledger_; }

EcoSensorSlot* EcoRuntime::allocateSensor(const char* name) {
  for (uint8_t i = 0; i < sensorCount_; ++i) {
    if (sensors_[i].name == name || (sensors_[i].name && name && strcmp(sensors_[i].name, name) == 0)) {
      return &sensors_[i];
    }
  }
  if (sensorCount_ >= ECOSENSE_MAX_SENSORS) {
    return 0;
  }
  EcoSensorSlot& slot = sensors_[sensorCount_];
  slot.active = true;
  slot.name = name ? name : "sensor";
  slot.nextDueMs = EcoTime::nowMs();
  configs_[sensorCount_] = EcoSensorConfig(&slot);
  ++sensorCount_;
  return &slot;
}

EcoGuardSlot* EcoRuntime::allocateGuard(const char* name) {
#if ECOSENSE_MAX_GUARDS > 0
  for (uint8_t i = 0; i < guardCount_; ++i) {
    if (guards_[i].name == name || (guards_[i].name && name && strcmp(guards_[i].name, name) == 0)) {
      return &guards_[i];
    }
  }
  if (guardCount_ >= ECOSENSE_MAX_GUARDS) {
    return 0;
  }
  EcoGuardSlot& slot = guards_[guardCount_];
  slot.active = true;
  slot.name = name ? name : "guard";
  guardConfigs_[guardCount_] = EcoGuardConfig(&slot);
  ++guardCount_;
  return &slot;
#else
  (void)name;
  return 0;
#endif
}

int8_t EcoRuntime::findDueSensor(uint32_t now) const {
  int8_t selected = -1;
  EcoPriority selectedPriority = ECO_LOW;
  uint32_t selectedDeadline = 0;
  for (uint8_t i = 0; i < sensorCount_; ++i) {
    if (!sensors_[i].active || !EcoTime::due(now, sensors_[i].nextDueMs)) {
      continue;
    }
    const EcoPriority priority = sensors_[i].contract.priority;
    if (selected < 0 || priority > selectedPriority ||
        (priority == selectedPriority && (int32_t)(sensors_[i].nextDueMs - selectedDeadline) < 0)) {
      selected = (int8_t)i;
      selectedPriority = priority;
      selectedDeadline = sensors_[i].nextDueMs;
    }
  }
  return selected;
}

uint32_t EcoRuntime::nextDeadlineMs() const {
  if (sensorCount_ == 0) {
    return EcoTime::nowMs() + 1000UL;
  }
  uint32_t deadline = sensors_[0].nextDueMs;
  for (uint8_t i = 1; i < sensorCount_; ++i) {
    if ((int32_t)(sensors_[i].nextDueMs - deadline) < 0) {
      deadline = sensors_[i].nextDueMs;
    }
  }
  return deadline;
}

size_t EcoRuntime::estimatePayloadBytes(const EcoReport& report) const {
  if (payloadEstimator_) {
    const size_t estimated = payloadEstimator_(report);
    return estimated == 0 ? 1 : estimated;
  }
  // Conservative default: approximate a compact sensor/value/status report.
  return 24;
}

void EcoRuntime::processSensor(EcoSensorSlot& slot, uint32_t now) {
  if (!ledger_.cycleOpen()) {
    ledger_.beginCycle();
  }

  state_ = EcoState::WAKEUP;
  traceState(state_);
  runGuardsWake();
  if (slot.wakeCallback) {
    slot.wakeCallback();
  }
  ledger_.record(EcoEnergyState::WAKEUP, 1, currentFor(EcoEnergyState::WAKEUP), voltage());

  if (slot.contract.warmupTimeMs > 0) {
    delay(slot.contract.warmupTimeMs);
    ledger_.record(EcoEnergyState::SENSOR_WARMUP, slot.contract.warmupTimeMs, currentFor(EcoEnergyState::SENSOR_WARMUP), voltage());
  }

  state_ = EcoState::SENSE;
  traceState(state_);
  const uint32_t readStart = EcoTime::nowMs();
  float value = 0.0f;
  bool readOk = false;
  if (slot.readCallback) {
    value = slot.readCallback();
    readOk = !isnan(value);
  }
  const uint32_t readDuration = EcoTime::elapsed(EcoTime::nowMs(), readStart);
  ledger_.record(EcoEnergyState::SENSOR_READ, readDuration == 0 ? 1 : readDuration, currentFor(EcoEnergyState::SENSOR_READ), voltage());

  state_ = EcoState::PROCESS;
  traceState(state_);
  bool important = false;
  slot.inferenceSkippedEnergyDeficit = false;
  const float previous = slot.lastValue;
  const bool first = !slot.hasValue;
  if (readOk) {
    sampler_.update(slot.contract, slot.lastValue, value, slot.hasValue, &important);
    if (slot.anomalyCallback) {
      if (slot.inferenceWindowStartMs == 0UL || EcoTime::elapsed(EcoTime::nowMs(), slot.inferenceWindowStartMs) >= EcoTime::hours(24)) {
        slot.inferenceWindowStartMs = EcoTime::nowMs();
        slot.inferenceRunsToday = 0;
        slot.inferenceLimitReached = false;
        slot.inferenceSkippedEnergyDeficit = false;
      }
      const float cycleCost_mJ = estimateDailyEnergyMilliJoules(slot) * ((float)slot.contract.currentIntervalMs / 86400000.0f);
#if ECOSENSE_ENABLE_SOC_TRACKER
      const float inferenceSoc = socTracker_.socPercent();
#else
      const float inferenceSoc = -1.0f;
#endif
      const bool deficit = energyPolicy_.targetNeutralEnabled() &&
        energyPolicy_.energyBalance(slot.contract.currentIntervalMs, cycleCost_mJ, inferenceSoc) == EcoEnergyBalance::DEFICIT;
      if (deficit && slot.inferenceBudget.shouldSkipWhenEnergyDeficit()) {
        slot.inferenceSkippedEnergyDeficit = true;
      } else if (slot.inferenceBudget.canRun(slot.inferenceRunsToday)) {
        const bool anomaly = slot.anomalyCallback(value);
        ++slot.inferenceRunsToday;
        const uint32_t duration = slot.inferenceBudget.durationMs() == 0 ? 1UL : slot.inferenceBudget.durationMs();
        const uint32_t current = slot.inferenceBudget.current_uA() == 0 ? currentFor(EcoEnergyState::PROCESS) : slot.inferenceBudget.current_uA();
        ledger_.record(EcoEnergyState::INFERENCE, duration, current, voltage());
        if (anomaly) { important = true; }
      } else {
        slot.inferenceLimitReached = true;
      }
    }
    slot.lastValue = value;
    slot.hasValue = true;
  }
  applyBudgetSoftLimit(slot);
  slot.lastReadOk = readOk;
  ledger_.record(EcoEnergyState::PROCESS, 1, currentFor(EcoEnergyState::PROCESS), voltage());

  const bool criticalReport = important || !readOk;
  bool batchDue = false;
  EcoRadioBatchSummary batchSummary;
  if (radio_ && !criticalReport) {
    radioBatcher_.markSample(EcoTime::nowMs(), value);
    batchDue = radioBatcher_.shouldReport(EcoTime::nowMs());
    batchSummary = radioBatcher_.summary();
    lastRadioBatchLimited_ = radioBatcher_.limited();
  }
  const bool shouldReport = reportCallback_ && (first || criticalReport || batchDue);

  if (shouldReport) {
    state_ = EcoState::REPORT;
    traceState(state_);
    EcoReport report;
    report.sensorName = slot.name;
    report.value = value;
    report.previousValue = previous;
    report.intervalMs = slot.contract.currentIntervalMs;
    report.firstRead = first;
    report.importantChange = important;
    report.readOk = readOk;
    report.budgetLimited = slot.budgetSoftLimited;
    report.estimatedDailyEnergy_mJ = slot.estimatedDailyEnergy_mJ;
    report.boardConfidence = board_.confidence;
    report.batteryConfidence = battery_.confidence;
    report.includesRegulatorIq = board_.includesRegulatorIq;
    report.includesSensorLeakage = board_.includesSensorLeakage;
    report.batchSampleCount = batchDue ? batchSummary.count : (uint8_t)1;
    report.batchMinValue = batchDue ? batchSummary.minValue : value;
    report.batchMaxValue = batchDue ? batchSummary.maxValue : value;
    report.batchFirstTimestampMs = batchDue ? batchSummary.firstTimestampMs : EcoTime::nowMs();
    report.batchLastTimestampMs = batchDue ? batchSummary.lastTimestampMs : EcoTime::nowMs();
    report.state = state_;
    reportCallback_(report);
    ledger_.record(EcoEnergyState::REPORT, 1, currentFor(EcoEnergyState::REPORT), voltage());
    if (radio_) {
      radio_->wake();
      const size_t payloadBytes = estimatePayloadBytes(report);
      const uint32_t txMs = radio_->estimateTxDurationMs(payloadBytes);
      ledger_.record(EcoEnergyState::RADIO_TX, txMs == 0 ? 1 : txMs, radio_->txCurrent_uA(), voltage());
      if (radio_->expectsRxWindow()) {
        const uint32_t rxMs = radio_->estimateRxWindowDurationMs();
        ledger_.record(EcoEnergyState::RADIO_RX, rxMs == 0 ? 1 : rxMs, radio_->rxCurrent_uA(), voltage());
      }
      radio_->sleep();
      ledger_.record(EcoEnergyState::RADIO_SLEEP, 1, radio_->sleepCurrent_uA(), voltage());
      if (batchDue) { radioBatcher_.clear(EcoTime::nowMs()); }
    }
  }

  state_ = EcoState::SLEEP;
  traceState(state_);
  if (slot.sleepCallback) {
    slot.sleepCallback();
  }
  runGuardsSleep();
  (void)now;
  slot.nextDueMs = EcoTime::nowMs() + slot.contract.currentIntervalMs;
  const float cycle_mJ = ledger_.cycleEnergyMilliJoules();
  if (cycle_mJ > 0.0f && voltage() > 0.1f) {
#if ECOSENSE_ENABLE_SOC_TRACKER
    const float uAms = (cycle_mJ * 1000000.0f) / voltage();
    socTracker_.debit((uint32_t)(uAms > 4294967295.0f ? 4294967295UL : uAms), 1UL);
#endif
  }
  if (harvester_) {
    const float usable_mJ = energyPolicy_.usableEnergyDuringInterval_mJ(slot.contract.currentIntervalMs);
#if ECOSENSE_ENABLE_SOC_TRACKER
    socTracker_.creditUsableEnergy_mJ(usable_mJ);
#else
    (void)usable_mJ;
#endif
  }
  ledger_.endCycle();
}

void EcoRuntime::applyBudgetSoftLimit(EcoSensorSlot& slot) {
  slot.budgetSoftLimited = false;
  slot.estimatedDailyEnergy_mJ = estimateDailyEnergyMilliJoules(slot);

  const float cycleCost_mJ = slot.estimatedDailyEnergy_mJ * ((float)slot.contract.currentIntervalMs / 86400000.0f);
  energyPolicy_.energyCostPerCycle_mJ(cycleCost_mJ);
#if ECOSENSE_ENABLE_SOC_TRACKER
  const float soc = socTracker_.socPercent();
#else
  const float soc = -1.0f;
#endif
  lastEnergyIncomeInsufficient_ = energyPolicy_.targetNeutralEnabled() &&
    energyPolicy_.energyBalance(slot.contract.currentIntervalMs, cycleCost_mJ, soc) == EcoEnergyBalance::DEFICIT;

  uint32_t policyInterval = energyPolicy_.recommendedIntervalMs(slot.contract.currentIntervalMs, slot.contract.minIntervalMs, slot.contract.maxIntervalMs, soc, cycleCost_mJ);
  if (policyInterval != slot.contract.currentIntervalMs) {
    if (policyInterval > slot.contract.currentIntervalMs) { slot.budgetSoftLimited = true; }
    slot.contract.currentIntervalMs = policyInterval;
    slot.contract.validate();
    slot.estimatedDailyEnergy_mJ = estimateDailyEnergyMilliJoules(slot);
    if (slot.budgetSoftLimited) return;
  }

  if (!slot.contract.hasDailyBudget()) {
    return;
  }
  if (slot.estimatedDailyEnergy_mJ <= (float)slot.contract.maxDailyEnergy_mJ) {
    return;
  }
  slot.budgetSoftLimited = true;
  if (slot.contract.currentIntervalMs < slot.contract.maxIntervalMs) {
    uint32_t next = slot.contract.currentIntervalMs * 2UL;
    if (next < slot.contract.currentIntervalMs || next > slot.contract.maxIntervalMs) {
      next = slot.contract.maxIntervalMs;
    }
    slot.contract.currentIntervalMs = next;
    if (!slot.contract.validate()) {
      slot.currentIntervalClamped = true;
    }
    slot.estimatedDailyEnergy_mJ = estimateDailyEnergyMilliJoules(slot);
  }
}

float EcoRuntime::estimateDailyEnergyMilliJoules(const EcoSensorSlot& slot) const {
  const uint32_t intervalMs = slot.contract.currentIntervalMs == 0 ? 1UL : slot.contract.currentIntervalMs;
  float cycle_mJ = 0.0f;
  cycle_mJ += EnergyModel::energyMilliJoules(voltage(), currentFor(EcoEnergyState::SLEEP), intervalMs);
  cycle_mJ += EnergyModel::energyMilliJoules(voltage(), currentFor(EcoEnergyState::WAKEUP), 1UL);
  cycle_mJ += EnergyModel::energyMilliJoules(voltage(), currentFor(EcoEnergyState::SENSOR_WARMUP), slot.contract.warmupTimeMs);
  cycle_mJ += EnergyModel::energyMilliJoules(voltage(), currentFor(EcoEnergyState::SENSOR_READ), 1UL);
  cycle_mJ += EnergyModel::energyMilliJoules(voltage(), currentFor(EcoEnergyState::PROCESS), 1UL);
  if (reportCallback_) {
    cycle_mJ += EnergyModel::energyMilliJoules(voltage(), currentFor(EcoEnergyState::REPORT), 1UL);
    if (radio_) {
      EcoReport defaultReport;
      defaultReport.sensorName = slot.name;
      defaultReport.intervalMs = slot.contract.currentIntervalMs;
      cycle_mJ += EnergyModel::energyMilliJoules(voltage(), radio_->txCurrent_uA(), radio_->estimateTxDurationMs(estimatePayloadBytes(defaultReport)));
      if (radio_->expectsRxWindow()) {
        cycle_mJ += EnergyModel::energyMilliJoules(voltage(), radio_->rxCurrent_uA(), radio_->estimateRxWindowDurationMs());
      }
      cycle_mJ += EnergyModel::energyMilliJoules(voltage(), radio_->sleepCurrent_uA(), 1UL);
    }
  }
  if (slot.anomalyCallback && slot.inferenceBudget.hasBudget()) {
    cycle_mJ += slot.inferenceBudget.energyPerInference_mJ(voltage());
  }
  const float cyclesPerDay = 86400000.0f / (float)intervalMs;
  return cycle_mJ * cyclesPerDay;
}

void EcoRuntime::backendSleep(uint32_t ms) {
#if defined(ARDUINO_ARCH_AVR)
  static AvrSleepBackend backend;
  backend.sleepFor(ms);
#elif defined(ARDUINO_ARCH_ESP32)
  static Esp32SleepBackend backend;
  backend.lightSleepFor(ms);
#else
  static GenericSleepBackend backend;
  backend.sleepFor(ms);
#endif
}

uint32_t EcoRuntime::currentFor(EcoEnergyState state) const {
  uint32_t base = board_.activeCurrent_uA;
  switch (state) {
    case EcoEnergyState::SLEEP: base = board_.sleepCurrent_uA; break;
    case EcoEnergyState::SENSOR_WARMUP: base = board_.sensorReadCurrent_uA; break;
    case EcoEnergyState::SENSOR_READ: base = board_.sensorReadCurrent_uA; break;
    case EcoEnergyState::PROCESS: base = board_.processCurrent_uA; break;
    case EcoEnergyState::REPORT: base = board_.activeCurrent_uA; break;
    case EcoEnergyState::WAKEUP: base = board_.activeCurrent_uA; break;
    case EcoEnergyState::RADIO_TX: base = radio_ ? radio_->txCurrent_uA() : board_.activeCurrent_uA; break;
    case EcoEnergyState::RADIO_RX: base = radio_ ? radio_->rxCurrent_uA() : board_.activeCurrent_uA; break;
    case EcoEnergyState::RADIO_SLEEP: base = radio_ ? radio_->sleepCurrent_uA() : board_.sleepCurrent_uA; break;
    case EcoEnergyState::INFERENCE: base = board_.processCurrent_uA; break;
    case EcoEnergyState::GUARD: base = board_.activeCurrent_uA; break;
    case EcoEnergyState::IDLE: base = board_.activeCurrent_uA; break;
    default: base = board_.activeCurrent_uA; break;
  }
  if (!board_.includesRegulatorIq && battery_.regulatorIq_uA > 0.0f) {
    base += (uint32_t)(battery_.regulatorIq_uA + 0.5f);
  }
  return base;
}

float EcoRuntime::voltage() const {
  return battery_.nominalVoltageV;
}

void EcoRuntime::traceState(EcoState state) const {
  if (debugEnabled_) {
    Serial.print(F("[EcoSensePower FSM] "));
    Serial.println(ecoStateName(state));
  }
}

void EcoRuntime::runGuardsWake() {
#if ECOSENSE_MAX_GUARDS > 0
  if (guardCount_ == 0 || guardsAwake_) {
    return;
  }
  const uint32_t start = EcoTime::nowMs();
  bool executed = false;
  bool anyActiveGuard = false;
  for (uint8_t i = 0; i < guardCount_; ++i) {
    EcoGuardSlot& guard = guards_[i];
    if (!guard.active) continue;
    anyActiveGuard = true;
    if (guard.powerPin >= 0) {
      pinMode((uint8_t)guard.powerPin, OUTPUT);
      digitalWrite((uint8_t)guard.powerPin, guard.activeLevel);
      executed = true;
    }
    if (guard.wakeCallback) {
      guard.wakeCallback();
      executed = true;
    }
    if (guard.warmupTimeMs > 0) {
      delay(guard.warmupTimeMs);
      executed = true;
    }
  }
  if (anyActiveGuard) {
    guardsAwake_ = true;
  }
  if (executed) {
    const uint32_t duration = EcoTime::elapsed(EcoTime::nowMs(), start);
    ledger_.record(EcoEnergyState::GUARD, duration == 0 ? 1 : duration, currentFor(EcoEnergyState::GUARD), voltage());
  }
#else
  guardsAwake_ = false;
#endif
}

void EcoRuntime::runGuardsSleep() {
#if ECOSENSE_MAX_GUARDS > 0
  if (guardCount_ == 0 || !guardsAwake_) {
    return;
  }
  const uint32_t start = EcoTime::nowMs();
  bool executed = false;
  for (uint8_t i = 0; i < guardCount_; ++i) {
    EcoGuardSlot& guard = guards_[i];
    if (!guard.active) continue;
    if (guard.sleepCallback) {
      guard.sleepCallback();
      executed = true;
    }
    if (guard.powerPin >= 0) {
      const uint8_t inactive = (guard.activeLevel == HIGH) ? LOW : HIGH;
      digitalWrite((uint8_t)guard.powerPin, inactive);
      executed = true;
    }
  }
  guardsAwake_ = false;
  if (executed) {
    const uint32_t duration = EcoTime::elapsed(EcoTime::nowMs(), start);
    ledger_.record(EcoEnergyState::GUARD, duration == 0 ? 1 : duration, currentFor(EcoEnergyState::GUARD), voltage());
  }
#else
  guardsAwake_ = false;
#endif
}
