#include "test_support.h"
#include <EcoSensePower.h>
int main() {
  ASSERT_TRUE(ecoBatteryChemistryName(ECO_BATTERY_LIFEPO4_1S)[0] != 'u');
  ASSERT_TRUE(ecoBatteryChemistryName(ECO_BATTERY_CR2032)[0] != 'u');
  ASSERT_TRUE(ecoBatteryHasFlatDischargeCurve(ECO_BATTERY_LISOCL2_AA));
  ASSERT_TRUE(ecoBatteryHasFlatDischargeCurve(ECO_BATTERY_LIFEPO4_1S));
  ASSERT_TRUE(!ecoBatteryHasFlatDischargeCurve(ECO_BATTERY_LIPO_1S));
  ASSERT_TRUE(ecoBatteryHasPulseLimitations(ECO_BATTERY_CR2032));
  ASSERT_TRUE(ecoBatteryProtectionCircuitRecommended(ECO_BATTERY_LIION_18650));
  ASSERT_TRUE(ECO_BATTERY_LIPO_18650 == ECO_BATTERY_LIION_18650);
  SoCTracker tracker;
  tracker.battery(BatteryProfile::LiFePO4_1S()).observedVoltage(3.25f);
  ASSERT_TRUE(tracker.flatCurveWarning());
  ASSERT_TRUE(tracker.confidence() == EcoProfileConfidence::PLACEHOLDER);
  return 0;
}
