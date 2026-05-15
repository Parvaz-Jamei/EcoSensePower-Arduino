#include <EcoSensePower.h>
#include "test_support.h"

static float readValue() { return 42.0f; }
static EcoReport g_lastReport;
static int g_reportCount = 0;
static int g_anomalyCalls = 0;
static void captureReport(const EcoReport& report) { g_lastReport = report; ++g_reportCount; }
static bool anomalyCallback(float score) { (void)score; ++g_anomalyCalls; return false; }
static size_t payloadEstimatorSmall(const EcoReport&) { return 8; }

int main() {
  // powerReport remaining interval must not underflow when the first sensor is already due.
  mockSetMillis(1000);
  EcoSensePower dueNode;
  dueNode.energyPolicy().energyIncome_mW(10.0f).storageEfficiencyPercent(50.0f).targetNeutralOperation(true);
  dueNode.sensor("due").read(readValue).minIntervalMs(EcoTime::minutes(1)).maxIntervalMs(EcoTime::hours(1));
  dueNode.begin();
  EcoPowerReport dueReport = dueNode.powerReport();
  ASSERT_TRUE(dueReport.harvestedEnergy_mJ < 0.001f);
  ASSERT_TRUE(dueReport.usableHarvestedEnergy_mJ < 0.001f);

  // Diagnostics snapshot exposes total and truncation when caller buffer is small.
  EcoSensePower diagNode;
  for (uint8_t i = 0; i < ECOSENSE_MAX_SENSORS; ++i) { diagNode.sensor("sensor"); }
  EcoDiagnostic smallBuffer[2];
  EcoDiagnosticSnapshot snap = diagNode.collectDiagnosticsSnapshot(smallBuffer, 2);
  ASSERT_TRUE(snap.total >= snap.copied);
  ASSERT_TRUE(snap.copied == 2);
  ASSERT_TRUE(snap.truncated);

  // Regulator IQ should affect estimates when the board profile does not include it.
  g_reportCount = 0;
  EcoSensePower noIq;
  BatteryProfile noIqBattery = BatteryProfile::LiPo_1S(1000);
  noIqBattery.regulatorIq_uA = -1.0f;
  BoardProfile boardNoIq("test-board", 1000, 100, 1000, 1000, true, "measured currents excluding regulator", EcoProfileConfidence::MEASURED, false, true);
  noIq.battery(noIqBattery).board(boardNoIq).onReport(captureReport);
  noIq.sensor("s").read(readValue).minIntervalMs(EcoTime::seconds(10)).maxIntervalMs(EcoTime::seconds(10));
  noIq.begin();
  noIq.loop();
  const float estNoIq = g_lastReport.estimatedDailyEnergy_mJ;

  g_reportCount = 0;
  EcoSensePower withIq;
  BatteryProfile iqBattery = BatteryProfile::LiPo_1S(1000);
  iqBattery.regulatorIq_uA = 50.0f;
  withIq.battery(iqBattery).board(boardNoIq).onReport(captureReport);
  withIq.sensor("s").read(readValue).minIntervalMs(EcoTime::seconds(10)).maxIntervalMs(EcoTime::seconds(10));
  withIq.begin();
  withIq.loop();
  const float estWithIq = g_lastReport.estimatedDailyEnergy_mJ;
  ASSERT_TRUE(estWithIq > estNoIq);

  // If board already includes regulator IQ, do not double-count the battery metadata.
  g_reportCount = 0;
  EcoSensePower includedIq;
  BoardProfile boardWithIq("test-board-included", 1000, 100, 1000, 1000, true, "measured currents including regulator", EcoProfileConfidence::MEASURED, true, true);
  includedIq.battery(iqBattery).board(boardWithIq).onReport(captureReport);
  includedIq.sensor("s").read(readValue).minIntervalMs(EcoTime::seconds(10)).maxIntervalMs(EcoTime::seconds(10));
  includedIq.begin();
  includedIq.loop();
  ASSERT_TRUE(g_lastReport.estimatedDailyEnergy_mJ < estWithIq);

  // Radio payload size should materially affect TX energy estimates.
  GenericRadioProfile radio;
  radio.fixedTxDurationMs(0).txCurrent_uA(10000).confidence(EcoProfileConfidence::DATASHEET);
  EcoReport dummy;
  ASSERT_TRUE(radio.estimateTxEnergy_mJ(3.3f, 64) > radio.estimateTxEnergy_mJ(3.3f, 8));

  // RX window must be recorded when configured.
  g_reportCount = 0;
  EcoSensePower rxNode;
  GenericRadioProfile rxRadio;
  rxRadio.fixedTxDurationMs(10).rxWindowDurationMs(20).rxCurrent_uA(12000).confidence(EcoProfileConfidence::DATASHEET);
  rxNode.radio(&rxRadio).reportPayloadEstimator(payloadEstimatorSmall).onReport(captureReport);
  rxNode.sensor("r").read(readValue).minIntervalMs(EcoTime::seconds(10)).maxIntervalMs(EcoTime::seconds(10));
  rxNode.begin();
  rxNode.loop();
  ASSERT_TRUE(rxNode.ledger().cycleEnergyForState(EcoEnergyState::RADIO_RX) > 0.0f);

  // RadioBatcher aggregate summary must not silently drop non-critical samples.
  RadioBatcher batcher;
  batcher.batchMaxSamples(3).maxReportIntervalMs(EcoTime::hours(1));
  batcher.markSample(10, 10.0f);
  batcher.markSample(20, 12.0f);
  batcher.markSample(30, 8.0f);
  ASSERT_TRUE(batcher.shouldReport(30));
  EcoRadioBatchSummary summary = batcher.summary();
  ASSERT_EQ(summary.count, 3);
  ASSERT_TRUE(summary.minValue == 8.0f);
  ASSERT_TRUE(summary.maxValue == 12.0f);

  // Harvesting efficiency must distinguish input energy from usable/stored energy.
  EnergyBudgetManager policy;
  policy.energyIncome_mW(10.0f).storageEfficiencyPercent(50.0f).targetNeutralOperation(true);
  ASSERT_TRUE(policy.inputEnergyDuringInterval_mJ(1000) > policy.usableEnergyDuringInterval_mJ(1000));
  ASSERT_TRUE(policy.energyBalance(1000, 9.0f, 80.0f) == EcoEnergyBalance::DEFICIT);
  ASSERT_TRUE(policy.energyBalance(1000, 4.0f, 80.0f) == EcoEnergyBalance::SURPLUS);

  // Non-critical inference can be skipped under energy deficit.
  g_anomalyCalls = 0;
  EcoSensePower mlNode;
  mlNode.energyPolicy().targetNeutralOperation(true).energyIncome_mW(0.0f).minReservePercent(25);
  mlNode.socTracker().battery(BatteryProfile::LiPo_1S(1000)).initialSocPercent(10.0f);
  mlNode.sensor("ml").read(readValue).minIntervalMs(EcoTime::seconds(10)).maxIntervalMs(EcoTime::seconds(10)).onAnomaly(anomalyCallback).inferenceCost().current_uA(1000).durationMs(10).maxRunsPerDay(10).skipWhenEnergyDeficit(true);
  mlNode.begin();
  mlNode.loop();
  ASSERT_EQ(g_anomalyCalls, 0);
  EcoDiagnostic diagBuffer[ECOSENSE_MAX_DIAGNOSTICS];
  EcoDiagnosticSnapshot mlSnap = mlNode.collectDiagnosticsSnapshot(diagBuffer, ECOSENSE_MAX_DIAGNOSTICS);
  bool sawSkip = false;
  for (uint8_t i = 0; i < mlSnap.copied; ++i) {
    if (diagBuffer[i].code == EcoDiagnosticCode::INFERENCE_SKIPPED_ENERGY_DEFICIT) sawSkip = true;
  }
  ASSERT_TRUE(sawSkip);

  return 0;
}
