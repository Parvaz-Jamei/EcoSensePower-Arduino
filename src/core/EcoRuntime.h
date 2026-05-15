#ifndef ECOSENSE_CORE_ECORUNTIME_H
#define ECOSENSE_CORE_ECORUNTIME_H

#include "core/EcoTypes.h"
#include "core/EcoTime.h"
#include "core/EcoScheduler.h"
#include "core/EnergyContract.h"
#include "core/AdaptiveSampler.h"
#include "core/EnergyLedger.h"
#include "core/BatteryProfile.h"
#include "core/BoardProfile.h"
#include "core/PeripheralGuard.h"
#include "ml/InferenceBudget.h"
#include "ml/AnomalyHook.h"
#include "core/SoCTracker.h"
#include "core/EnergyBudgetManager.h"
#include "harvester/HarvesterBase.h"
#include "radio/RadioEnergyAdapter.h"
#include "radio/RadioBatcher.h"

struct EcoSensorSlot {
  bool active;
  const char* name;
  EcoReadCallback readCallback;
  EcoVoidCallback wakeCallback;
  EcoVoidCallback sleepCallback;
  EnergyContract contract;
  float lastValue;
  bool hasValue;
  uint32_t nextDueMs;
  bool lastReadOk;
  bool calibratedCurrent;
  bool budgetSoftLimited;
  bool currentIntervalClamped;
  float estimatedDailyEnergy_mJ;
  EcoAnomalyCallback anomalyCallback;
  InferenceBudget inferenceBudget;
  uint16_t inferenceRunsToday;
  uint32_t inferenceWindowStartMs;
  bool inferenceLimitReached;
  bool inferenceSkippedEnergyDeficit;

  EcoSensorSlot()
    : active(false), name("sensor"), readCallback(0), wakeCallback(0), sleepCallback(0),
      contract(), lastValue(0.0f), hasValue(false), nextDueMs(0), lastReadOk(false),
      calibratedCurrent(false), budgetSoftLimited(false), currentIntervalClamped(false),
      estimatedDailyEnergy_mJ(0.0f), anomalyCallback(0), inferenceBudget(), inferenceRunsToday(0), inferenceWindowStartMs(0), inferenceLimitReached(false), inferenceSkippedEnergyDeficit(false) {}
};

class EcoSensorConfig {
public:
  EcoSensorConfig();
  explicit EcoSensorConfig(EcoSensorSlot* slot);

  EcoSensorConfig& read(EcoReadCallback callback);
  EcoSensorConfig& warmupTimeMs(uint32_t value);
  EcoSensorConfig& minIntervalMs(uint32_t value);
  EcoSensorConfig& maxIntervalMs(uint32_t value);
  EcoSensorConfig& initialIntervalMs(uint32_t value);
  EcoSensorConfig& changeThreshold(float value);
  EcoSensorConfig& priority(EcoPriority value);
  EcoSensorConfig& maxDailyEnergy_mJ(uint32_t value);
  EcoSensorConfig& maxEnergyPerWindow_mJ(float value, uint32_t windowMs);
  EcoSensorConfig& energyWindowMs(uint32_t windowMs);
  EcoSensorConfig& onWake(EcoVoidCallback callback);
  EcoSensorConfig& onSleep(EcoVoidCallback callback);
  EcoSensorConfig& calibratedCurrent(bool measured = true);
  EcoSensorConfig& onAnomaly(EcoAnomalyCallback callback);
  InferenceBudget& inferenceCost();

  bool valid() const;

private:
  EcoSensorSlot* slot_;
};

class EcoRuntime {
public:
  EcoRuntime();

  bool begin();
  void loop();
  EcoSensorConfig& sensor(const char* name);
  EcoGuardConfig& guard(const char* name);

  void setBatteryProfile(const BatteryProfile& profile);
  void setBoardProfile(const BoardProfile& profile);
  void setReportCallback(EcoReportCallback callback);
  void setDebug(bool enabled);
  SoCTracker& socTracker();
  const SoCTracker& socTracker() const;
  EnergyBudgetManager& energyPolicy();
  const EnergyBudgetManager& energyPolicy() const;
  void setHarvester(HarvesterBase* harvester);
  void setRadio(RadioEnergyAdapter* radio);
  void setPayloadEstimator(EcoPayloadSizeCallback callback);
  RadioBatcher& reporting();
  const RadioBatcher& reporting() const;
  RadioEnergyAdapter* radioAdapter() const;
  bool hasRadioAdapter() const;
  bool radioProfilePlaceholder() const;
  bool radioTxDominatesEnergy() const;
  bool radioPayloadEstimatorPlaceholder() const;
  bool radioBatchBufferLimited() const;
  bool radioRxWindowConfigured() const;
  bool radioConfirmedUplink() const;
  EcoProfileConfidence radioConfidence() const;
  bool harvestingEfficiencyPlaceholder() const;
  bool energyIncomeInsufficient() const;
  EcoPowerReport powerReport() const;

  bool debugEnabled() const;
  bool hasReportCallback() const;
  bool hasGenericBoardProfile() const;
  bool hasBatteryProfile() const;
  bool sensorRegistryFull() const;
  bool guardRegistryFull() const;
  bool hasEsp32WirelessGuard() const;
  bool hasAnyCurrentIntervalClamp() const;
  bool guardsAwake() const;
  bool hasMatchingGuardName(const char* name) const;
  const BatteryProfile& batteryProfile() const;
  const BoardProfile& boardProfile() const;
  const EcoSensorSlot* sensors() const;
  uint8_t sensorCount() const;
  const EcoGuardSlot* guards() const;
  uint8_t guardCount() const;
  EcoState state() const;
  const char* backendName() const;
  bool backendIsRealSleep() const;
  bool supportsPowerDown() const;
  EnergyLedger& ledger();
  const EnergyLedger& ledger() const;

private:
  EcoSensorSlot sensors_[ECOSENSE_MAX_SENSORS];
  EcoSensorConfig configs_[ECOSENSE_MAX_SENSORS];
  EcoSensorConfig invalidConfig_;
#if ECOSENSE_MAX_GUARDS > 0
  EcoGuardSlot guards_[ECOSENSE_MAX_GUARDS];
  EcoGuardConfig guardConfigs_[ECOSENSE_MAX_GUARDS];
#endif
  EcoGuardConfig invalidGuardConfig_;
  uint8_t sensorCount_;
  uint8_t guardCount_;
  EcoState state_;
  EcoReportCallback reportCallback_;
  bool debugEnabled_;
  bool initialized_;
  bool hasBatteryProfile_;
  bool sensorRegistryFull_;
  bool guardRegistryFull_;
  bool guardsAwake_;
  BatteryProfile battery_;
  BoardProfile board_;
  AdaptiveSampler sampler_;
  EcoScheduler scheduler_;
  EnergyLedger ledger_;
#if ECOSENSE_ENABLE_SOC_TRACKER
  SoCTracker socTracker_;
#endif
  EnergyBudgetManager energyPolicy_;
  HarvesterBase* harvester_;
  RadioEnergyAdapter* radio_;
  EcoPayloadSizeCallback payloadEstimator_;
  RadioBatcher radioBatcher_;
  bool lastEnergyIncomeInsufficient_;
  bool lastRadioBatchLimited_;

  EcoSensorSlot* allocateSensor(const char* name);
  EcoGuardSlot* allocateGuard(const char* name);
  int8_t findDueSensor(uint32_t now) const;
  uint32_t nextDeadlineMs() const;
  size_t estimatePayloadBytes(const EcoReport& report) const;
  void processSensor(EcoSensorSlot& slot, uint32_t now);
  void applyBudgetSoftLimit(EcoSensorSlot& slot);
  float estimateDailyEnergyMilliJoules(const EcoSensorSlot& slot) const;
  void backendSleep(uint32_t ms);
  uint32_t currentFor(EcoEnergyState state) const;
  float voltage() const;
  void traceState(EcoState state) const;
  void runGuardsWake();
  void runGuardsSleep();
};

#endif
