#include "test_support.h"
#include <EcoSensePower.h>

static float readStable() { return 10.0f; }
static bool yesAnomaly(float) { return true; }
static size_t payload64(const EcoReport&) { return 64; }
static uint32_t oneMsPerByte(size_t bytes) { return (uint32_t)bytes; }
static int g_reports = 0;
static void countReport(const EcoReport&) { ++g_reports; }

class FixedHarvester : public HarvesterBase {
public:
  explicit FixedHarvester(float mw) : mw_(mw) {}
  float inputPowerMilliWatt() const override { return mw_; }
  bool available() const override { return true; }
  EcoProfileConfidence confidence() const override { return EcoProfileConfidence::DATASHEET; }
private:
  float mw_;
};

int main() {
  // powerReport() must not underflow when deadline is due/past.
  {
    mockSetMillis(1000);
    EcoSensePower node;
    FixedHarvester harvester(1000.0f);
    node.harvester(&harvester);
    node.energyPolicy().targetNeutralOperation(true).energyIncome_mW(1000.0f);
    node.sensor("due").read(readStable).minIntervalMs(EcoTime::seconds(5)).maxIntervalMs(EcoTime::minutes(5));
    node.begin();
    EcoPowerReport report = node.powerReport();
    ASSERT_TRUE(report.harvestedEnergy_mJ < 1.0f);
  }

  // Diagnostic snapshot must report total count and caller-buffer truncation.
  {
    EcoSensePower node;
    for (uint8_t i = 0; i < ECOSENSE_MAX_SENSORS; ++i) {
      static const char* names[] = {"s0", "s1", "s2", "s3"};
      node.sensor(names[i]).minIntervalMs(1).maxIntervalMs(1);
    }
    node.enableDebug(true);
    EcoDiagnostic small[2];
    EcoDiagnosticSnapshot snap = node.collectDiagnosticsSnapshot(small, 2);
    ASSERT_EQ(2L, (long)snap.copied);
    ASSERT_TRUE(snap.total > snap.copied);
    ASSERT_TRUE(snap.truncated);
  }

  // SoC custom curve and Li-SOCl2 voltage-only confidence/unknown days behavior.
  {
    SoCTracker tracker;
    const float volts[] = {3.0f, 3.5f, 4.0f};
    const float socs[] = {0.0f, 50.0f, 100.0f};
    tracker.battery(BatteryProfile::LiPo_1S()).voltageCurve(volts, socs, 3).observedVoltage(3.5f);
    ASSERT_TRUE(tracker.hasCustomVoltageCurve());
    ASSERT_TRUE(tracker.socPercent() > 49.0f && tracker.socPercent() < 51.0f);

    SoCTracker liso;
    liso.battery(BatteryProfile::LiSOCl2_AA()).observedVoltage(3.55f);
    EcoSoCReport report = liso.report(20.0f);
    ASSERT_TRUE(report.flatCurveWarning);
    ASSERT_EQ((long)EcoProfileConfidence::PLACEHOLDER, (long)report.confidence);
    ASSERT_TRUE(report.estimatedDaysLeft < 0.0f);
  }

  // EnergyBudgetManager must distinguish DEFICIT vs SURPLUS and relax interval under surplus.
  {
    EnergyBudgetManager budget;
    budget.targetNeutralOperation(true).allowIntervalStretching(true).energyIncome_mW(0.01f);
    ASSERT_EQ((long)EcoEnergyBalance::DEFICIT, (long)budget.energyBalance(EcoTime::seconds(10), 1000.0f, 90.0f));
    uint32_t stretched = budget.recommendedIntervalMs(1000, 500, 10000, 90.0f, 1000.0f);
    ASSERT_TRUE(stretched > 1000);

    budget.energyIncome_mW(1000.0f);
    ASSERT_EQ((long)EcoEnergyBalance::SURPLUS, (long)budget.energyBalance(EcoTime::seconds(10), 1000.0f, 90.0f));
    uint32_t relaxed = budget.recommendedIntervalMs(4000, 1000, 10000, 90.0f, 1000.0f);
    ASSERT_TRUE(relaxed < 4000);
    ASSERT_TRUE(relaxed >= 1000);
  }

  // Runtime radio payload estimator must affect TX energy.
  {
    mockSetMillis(0);
    GenericRadioProfile radio;
    radio.txCurrent_uA(1000).sleepCurrent_uA(1).estimatedTxDurationMs(oneMsPerByte);
    EcoSensePower node;
    node.battery(BatteryProfile::LiPo_1S());
    node.radio(&radio).reportPayloadEstimator(payload64);
    node.sensor("radio").read(readStable).minIntervalMs(1).maxIntervalMs(1000).changeThreshold(1000.0f);
    node.onReport([](const EcoReport&) {});
    node.begin();
    node.loop();
    ASSERT_TRUE(node.ledger().cycleEnergyForState(EcoEnergyState::RADIO_TX) > 0.20f); // 3.7V * 1000uA * 64ms ~= 0.237mJ
  }

  // Runtime-integrated batching: non-critical samples batch, anomaly/critical bypasses.
  {
    mockSetMillis(0);
    GenericRadioProfile radio;
    radio.txCurrent_uA(1000).sleepCurrent_uA(1).estimatedTxDurationMs(oneMsPerByte);
    EcoSensePower node;
    g_reports = 0;
    node.radio(&radio);
    node.reporting().batchMaxSamples(3).maxReportIntervalMs(EcoTime::hours(1));
    node.sensor("batch").read(readStable).minIntervalMs(1).maxIntervalMs(1).changeThreshold(1000.0f);
    node.onReport(countReport);
    node.begin();
    node.loop(); // first read reports immediately
    ASSERT_EQ(1L, g_reports);
    mockSetMillis(10); node.loop();
    ASSERT_EQ(1L, g_reports);
    mockSetMillis(20); node.loop();
    ASSERT_EQ(1L, g_reports);
    mockSetMillis(30); node.loop();
    ASSERT_EQ(2L, g_reports);
  }

  // Inference daily window is a rolling 24h millis window and wrap-safe elapsed arithmetic works.
  {
    ASSERT_TRUE(EcoTime::elapsed(10UL, 0xFFFFFFF0UL) < EcoTime::seconds(60));
    mockSetMillis(0xFFFFFF00UL);
    EcoSensePower node;
    node.sensor("ml").read(readStable).minIntervalMs(1).maxIntervalMs(1000).onAnomaly(yesAnomaly).inferenceCost().current_uA(1000).durationMs(10).maxRunsPerDay(1);
    node.onReport([](const EcoReport&) {});
    node.begin();
    node.loop();
    mockSetMillis(0xFFFFFF10UL); node.loop();
    EcoDiagnostic diagnostics[ECOSENSE_MAX_DIAGNOSTICS];
    EcoDiagnosticSnapshot snap = node.collectDiagnosticsSnapshot(diagnostics, ECOSENSE_MAX_DIAGNOSTICS);
    bool foundLimit = false;
    for (uint8_t i = 0; i < snap.copied; ++i) {
      if (diagnostics[i].code == EcoDiagnosticCode::INFERENCE_RUN_LIMIT_REACHED) foundLimit = true;
    }
    ASSERT_TRUE(foundLimit);
  }

  return 0;
}
