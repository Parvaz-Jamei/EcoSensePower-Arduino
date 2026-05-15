#include "test_support.h"
#include <EcoSensePower.h>
int main() {
  SoCTracker unknown;
  ASSERT_TRUE(unknown.socPercent() < 0.0f);
  ASSERT_TRUE(!unknown.hasInitialSoc());
  ASSERT_TRUE(!unknown.hasVoltageEvidence());
  ASSERT_TRUE(!unknown.hasCoulombEvidence());

  SoCTracker soc;
  soc.battery(BatteryProfile::LiPo_1S(1000)).initialSocPercent(80.0f).observedVoltage(4.0f).debit(1000, EcoTime::hours(1));
  EcoSoCReport r = soc.report(100.0f);
  ASSERT_TRUE(r.socPercent > 50.0f);
  ASSERT_TRUE(r.socPercent < 100.0f);
  ASSERT_TRUE(r.estimatedDaysLeft > 0.0f);
  ASSERT_TRUE(soc.hasInitialSoc());
  ASSERT_TRUE(soc.hasVoltageEvidence());
  ASSERT_TRUE(soc.hasCoulombEvidence());

  SoCTracker flat;
  flat.battery(BatteryProfile::LiSOCl2_AA()).observedVoltage(3.5f);
  ASSERT_TRUE(flat.flatCurveWarning());
  ASSERT_TRUE(flat.socPercent() >= 0.0f);
  return 0;
}
