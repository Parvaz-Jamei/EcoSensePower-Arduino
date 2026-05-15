#include "test_support.h"
#include <EcoSensePower.h>

static float valueRead() { return 2.0f; }
static bool anomaly(float v) { return v > 1.0f; }
static uint32_t txDuration(size_t bytes) { return 100UL + (uint32_t)bytes; }

class WeakHarvester : public HarvesterBase {
public:
  float inputPowerMilliWatt() const override { return 0.001f; }
  bool available() const override { return true; }
  EcoProfileConfidence confidence() const override { return EcoProfileConfidence::PLACEHOLDER; }
};

int main() {
  SoCTracker emptySoc;
  ASSERT_TRUE(emptySoc.socPercent() < 0.0f);
  ASSERT_TRUE(!emptySoc.hasInitialSoc());
  emptySoc.initialSocPercent(80.0f).debit(1000, EcoTime::hours(1));
  ASSERT_TRUE(emptySoc.hasInitialSoc());
  ASSERT_TRUE(emptySoc.hasCoulombEvidence());
  ASSERT_TRUE(emptySoc.socPercent() < 80.0f);

  EnergyBudgetManager budget;
  budget.targetNeutralOperation(true).energyIncome_mW(0.001f).energyCostPerCycle_mJ(1000.0f);
  ASSERT_TRUE(!budget.incomeCoversCycle(EcoTime::minutes(5), 1000.0f));
  ASSERT_TRUE(budget.shouldStretchInterval(90.0f, EcoTime::minutes(5), 1000.0f));

  GenericRadioProfile radio;
  radio.txCurrent_uA(100000).rxCurrent_uA(12000).sleepCurrent_uA(3).estimatedTxDurationMs(txDuration);
  ASSERT_EQ(3L, (long)radio.sleepCurrent_uA());

  EcoSensePower node;
  WeakHarvester harvester;
  node.battery(BatteryProfile::LiPo_1S(1000));
  node.socTracker().initialSocPercent(75.0f).observedVoltage(3.8f);
  node.harvester(&harvester);
  node.energyPolicy().targetNeutralOperation(true).allowIntervalStretching(true).energyCostPerCycle_mJ(1000.0f);
  node.radio(&radio);
  node.sensor("score")
      .read(valueRead)
      .minIntervalMs(EcoTime::seconds(1))
      .maxIntervalMs(EcoTime::minutes(10))
      .changeThreshold(0.1f)
      .onAnomaly(anomaly)
      .inferenceCost()
        .current_uA(5000)
        .durationMs(10)
        .maxRunsPerDay(1);
  node.onReport([](const EcoReport&) {});
  node.begin();
  node.loop();
  ASSERT_TRUE(node.ledger().cycleEnergyForState(EcoEnergyState::INFERENCE) > 0.0f);
  ASSERT_TRUE(node.ledger().cycleEnergyForState(EcoEnergyState::RADIO_TX) > 0.0f);
  EcoPowerReport pr = node.powerReport();
  ASSERT_TRUE(pr.hasInitialSoc);
  ASSERT_TRUE(pr.hasVoltageEvidence);

  EcoDiagnostic diagnostics[ECOSENSE_MAX_DIAGNOSTICS];
  uint8_t count = node.collectDiagnostics(diagnostics, ECOSENSE_MAX_DIAGNOSTICS);
  bool foundSoc = false;
  bool foundEnergyIncome = false;
  for (uint8_t i = 0; i < count; ++i) {
    if (diagnostics[i].code == EcoDiagnosticCode::SOC_VOLTAGE_ONLY) foundSoc = true;
    if (diagnostics[i].code == EcoDiagnosticCode::ENERGY_INCOME_INSUFFICIENT) foundEnergyIncome = true;
  }
  ASSERT_TRUE(foundSoc || node.socTracker().hasCoulombEvidence());
  ASSERT_TRUE(foundEnergyIncome);
  return 0;
}
