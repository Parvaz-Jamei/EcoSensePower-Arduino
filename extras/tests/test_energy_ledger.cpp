#include "test_support.h"
#include <EcoSensePower.h>
int main() {
  EnergyLedger ledger;
  ledger.beginCycle();
  ASSERT_TRUE(ledger.cycleOpen());
  ledger.record(EcoEnergyState::SLEEP, EcoTime::seconds(1), 10, 3.0f);
  ledger.record(EcoEnergyState::SENSOR_READ, 10, 3000, 3.0f);
  ledger.endCycle();
  ASSERT_TRUE(!ledger.cycleOpen());
  ASSERT_EQ(ledger.cycleCount(), 2);
  ASSERT_EQ(ledger.cycleDurationMs(), EcoTime::seconds(1) + 10UL);
  ASSERT_TRUE(ledger.cycleEnergyMilliJoules() > 0.0f);
  ASSERT_TRUE(ledger.totalEnergyMilliJoules() == ledger.cycleEnergyMilliJoules());
  return 0;
}
