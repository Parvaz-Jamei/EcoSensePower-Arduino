#include "test_support.h"
#include <EcoSensePower.h>

static bool consistent(const BoardProfile& profile) {
  return (profile.measured && profile.confidence == EcoProfileConfidence::MEASURED) ||
         (!profile.measured && profile.confidence != EcoProfileConfidence::MEASURED);
}

int main() {
  BoardProfile sensorOnlyMeasured = MeasuredProfileBuilder()
    .name("sensor only measured")
    .sensorReadCurrent_uA(1500UL, EcoProfileConfidence::MEASURED)
    .build();
  ASSERT_TRUE(consistent(sensorOnlyMeasured));
  ASSERT_TRUE(!sensorOnlyMeasured.measured);
  ASSERT_TRUE(sensorOnlyMeasured.confidence == EcoProfileConfidence::PLACEHOLDER);

  BoardProfile mixedMeasuredPlaceholder = MeasuredProfileBuilder()
    .name("mixed measured placeholder")
    .activeCurrent_uA(42000UL, EcoProfileConfidence::MEASURED)
    .sleepCurrent_uA(12UL, EcoProfileConfidence::MEASURED)
    .sensorReadCurrent_uA(3200UL, EcoProfileConfidence::MEASURED)
    .processCurrent_uA(9000UL, EcoProfileConfidence::PLACEHOLDER)
    .build();
  ASSERT_TRUE(consistent(mixedMeasuredPlaceholder));
  ASSERT_TRUE(!mixedMeasuredPlaceholder.measured);
  ASSERT_TRUE(mixedMeasuredPlaceholder.confidence == EcoProfileConfidence::PLACEHOLDER);

  BoardProfile allMeasured = MeasuredProfileBuilder()
    .name("all measured")
    .activeCurrent_uA(42000UL, EcoProfileConfidence::MEASURED)
    .sleepCurrent_uA(12UL, EcoProfileConfidence::MEASURED)
    .sensorReadCurrent_uA(3200UL, EcoProfileConfidence::MEASURED)
    .processCurrent_uA(9000UL, EcoProfileConfidence::MEASURED)
    .build();
  ASSERT_TRUE(consistent(allMeasured));
  ASSERT_TRUE(allMeasured.measured);
  ASSERT_TRUE(allMeasured.confidence == EcoProfileConfidence::MEASURED);

  BoardProfile mixedDatasheetMeasured = MeasuredProfileBuilder()
    .name("mixed datasheet measured")
    .activeCurrent_uA(42000UL, EcoProfileConfidence::MEASURED)
    .sleepCurrent_uA(12UL, EcoProfileConfidence::DATASHEET)
    .sensorReadCurrent_uA(3200UL, EcoProfileConfidence::MEASURED)
    .processCurrent_uA(9000UL, EcoProfileConfidence::MEASURED)
    .build();
  ASSERT_TRUE(consistent(mixedDatasheetMeasured));
  ASSERT_TRUE(!mixedDatasheetMeasured.measured);
  ASSERT_TRUE(mixedDatasheetMeasured.confidence == EcoProfileConfidence::DATASHEET);

  BoardProfile allDatasheet = MeasuredProfileBuilder()
    .name("all datasheet")
    .activeCurrent_uA(42000UL, EcoProfileConfidence::DATASHEET)
    .sleepCurrent_uA(12UL, EcoProfileConfidence::DATASHEET)
    .sensorReadCurrent_uA(3200UL, EcoProfileConfidence::DATASHEET)
    .processCurrent_uA(9000UL, EcoProfileConfidence::DATASHEET)
    .build();
  ASSERT_TRUE(consistent(allDatasheet));
  ASSERT_TRUE(!allDatasheet.measured);
  ASSERT_TRUE(allDatasheet.confidence == EcoProfileConfidence::DATASHEET);
  return 0;
}
