#include "test_support.h"
#include <EcoSensePower.h>
class TestHarvester : public HarvesterBase {
public:
  float inputPowerMilliWatt() const override { return 0.01f; }
  bool available() const override { return true; }
};
int main() {
  TestHarvester h;
  EnergyBudgetManager b;
  b.harvester(&h).targetNeutralOperation(true).minReservePercent(25).allowIntervalStretching(true).energyCostPerCycle_mJ(100.0f);
  ASSERT_TRUE(b.shouldStretchInterval(20.0f));
  ASSERT_TRUE(!b.incomeCoversCycle(EcoTime::minutes(5), 100.0f));
  ASSERT_TRUE(b.shouldStretchInterval(80.0f, EcoTime::minutes(5), 100.0f));
  ASSERT_EQ((long)EcoTime::minutes(15), (long)b.recommendedIntervalMs(EcoTime::minutes(10), EcoTime::hours(1), 20.0f));
  b.energyIncome_mW(1000.0f).harvester(nullptr);
  ASSERT_TRUE(b.incomeCoversCycle(EcoTime::minutes(5), 100.0f));
  return 0;
}
