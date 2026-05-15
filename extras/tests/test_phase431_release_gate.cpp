#include <EcoSensePower.h>
#include "test_support.h"

static float readValue() { return 50.0f; }
static int g_anomalyCalls431 = 0;
static bool anomaly431(float score) { (void)score; ++g_anomalyCalls431; return false; }

static float runHarvestCredit(float efficiencyPercent) {
  mockSetMillis(1000);
  EcoSensePower node;
  BatteryProfile battery = BatteryProfile::LiPo_1S(1000);
  battery.confidence = EcoProfileConfidence::DATASHEET;
  node.battery(battery);
  node.socTracker().initialSocPercent(50.0f);
  SolarHarvester solar;
  solar.fixedMilliWatt(100.0f).storageEfficiencyPercent(efficiencyPercent).confidence(EcoProfileConfidence::DATASHEET);
  node.harvester(&solar);
  node.energyPolicy().targetNeutralOperation(true).allowIntervalStretching(false);
  node.sensor("solar-credit")
    .read(readValue)
    .minIntervalMs(EcoTime::hours(1))
    .maxIntervalMs(EcoTime::hours(1))
    .initialIntervalMs(EcoTime::hours(1));
  node.begin();
  node.loop();
  return node.socTracker().socPercent();
}

int main() {
  // Harvester SoC credit must use usable/stored energy after efficiency, not raw input power.
  const float soc50 = runHarvestCredit(50.0f);
  const float soc100 = runHarvestCredit(100.0f);
  ASSERT_TRUE(soc100 > soc50);

  // Public powerReport() must propagate diagnostic truncation from the PowerDoctor snapshot.
  mockSetMillis(0);
  EcoSensePower noisy;
  noisy.enableDebug(true);
  noisy.energyPolicy().targetNeutralOperation(true).energyIncome_mW(0.0f);
  GenericRadioProfile radio;
  radio.rxWindowDurationMs(1000).confirmedUplink(true); // adds radio diagnostics while keeping dependency-free.
  noisy.radio(&radio);
  static const char* names[] = {"s0", "s1", "s2", "s3"};
  for (uint8_t i = 0; i < 4; ++i) {
    noisy.sensor(names[i]).maxIntervalMs(EcoTime::seconds(10));
  }
  noisy.sensor("overflow");
  EcoPowerReport power = noisy.powerReport();
  EcoDiagnostic buffer[2];
  EcoDiagnosticSnapshot snap = noisy.collectDiagnosticsSnapshot(buffer, 2);
  ASSERT_TRUE(snap.truncated);
  ASSERT_TRUE(power.diagnosticsTruncated);

  // Inference skip diagnostics must clear after energy recovers and inference is allowed to run.
  mockSetMillis(0);
  g_anomalyCalls431 = 0;
  EcoSensePower ml;
  ml.energyPolicy().targetNeutralOperation(true).energyIncome_mW(0.0f).minReservePercent(25);
  ml.socTracker().battery(BatteryProfile::LiPo_1S(1000)).initialSocPercent(10.0f);
  ml.sensor("ml")
    .read(readValue)
    .minIntervalMs(EcoTime::seconds(10))
    .maxIntervalMs(EcoTime::seconds(10))
    .onAnomaly(anomaly431)
    .inferenceCost()
      .current_uA(1000)
      .durationMs(10)
      .maxRunsPerDay(10)
      .skipWhenEnergyDeficit(true);
  ml.begin();
  ml.loop();
  ASSERT_EQ(g_anomalyCalls431, 0);

  ml.energyPolicy().energyIncome_mW(100000.0f);
  ml.socTracker().initialSocPercent(90.0f);
  mockSetMillis(EcoTime::seconds(20));
  ml.loop();
  ASSERT_TRUE(g_anomalyCalls431 > 0);
  EcoDiagnostic all[ECOSENSE_MAX_DIAGNOSTICS];
  EcoDiagnosticSnapshot recovered = ml.collectDiagnosticsSnapshot(all, ECOSENSE_MAX_DIAGNOSTICS);
  for (uint8_t i = 0; i < recovered.copied; ++i) {
    ASSERT_TRUE(all[i].code != EcoDiagnosticCode::INFERENCE_SKIPPED_ENERGY_DEFICIT);
  }

  return 0;
}
