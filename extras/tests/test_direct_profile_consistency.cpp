#include "test_support.h"
#include <EcoSensePower.h>

static bool confidenceMeasuredConsistent(bool measured, EcoProfileConfidence confidence) {
  return (measured && confidence == EcoProfileConfidence::MEASURED) ||
         (!measured && confidence != EcoProfileConfidence::MEASURED);
}

int main() {
  BoardProfile boardFalseMeasured("custom board", 10000UL, 100UL, 1000UL, 5000UL,
                                  false, "bad direct profile", EcoProfileConfidence::MEASURED);
  ASSERT_TRUE(!boardFalseMeasured.measured);
  ASSERT_TRUE(boardFalseMeasured.confidence != EcoProfileConfidence::MEASURED);
  ASSERT_TRUE(confidenceMeasuredConsistent(boardFalseMeasured.measured, boardFalseMeasured.confidence));

  BatteryProfile batteryFalseMeasured("custom battery", 1000UL, 3.7f,
                                      false, "bad direct battery", EcoProfileConfidence::MEASURED,
                                      ECO_BATTERY_LIPO_1S);
  ASSERT_TRUE(!batteryFalseMeasured.measured);
  ASSERT_TRUE(batteryFalseMeasured.confidence != EcoProfileConfidence::MEASURED);
  ASSERT_TRUE(confidenceMeasuredConsistent(batteryFalseMeasured.measured, batteryFalseMeasured.confidence));

  EcoSensorProfile sensorFalseMeasured("custom sensor", 10UL, 1000UL, 1UL,
                                       false, EcoProfileConfidence::MEASURED,
                                       "bad direct sensor");
  ASSERT_TRUE(!sensorFalseMeasured.measured);
  ASSERT_TRUE(sensorFalseMeasured.confidence != EcoProfileConfidence::MEASURED);
  ASSERT_TRUE(confidenceMeasuredConsistent(sensorFalseMeasured.measured, sensorFalseMeasured.confidence));

  BoardProfile boardTruePlaceholder("measured board", 10000UL, 100UL, 1000UL, 5000UL,
                                    true, "owner-measured profile", EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(boardTruePlaceholder.measured);
  ASSERT_TRUE(boardTruePlaceholder.confidence == EcoProfileConfidence::MEASURED);
  ASSERT_TRUE(confidenceMeasuredConsistent(boardTruePlaceholder.measured, boardTruePlaceholder.confidence));

  BatteryProfile batteryTrueDatasheet("measured battery", 1000UL, 3.7f,
                                      true, "owner-measured battery", EcoProfileConfidence::DATASHEET,
                                      ECO_BATTERY_LIPO_1S);
  ASSERT_TRUE(batteryTrueDatasheet.measured);
  ASSERT_TRUE(batteryTrueDatasheet.confidence == EcoProfileConfidence::MEASURED);
  ASSERT_TRUE(confidenceMeasuredConsistent(batteryTrueDatasheet.measured, batteryTrueDatasheet.confidence));

  EcoSensorProfile sensorTruePlaceholder("measured sensor", 10UL, 1000UL, 1UL,
                                         true, EcoProfileConfidence::PLACEHOLDER,
                                         "owner-measured sensor");
  ASSERT_TRUE(sensorTruePlaceholder.measured);
  ASSERT_TRUE(sensorTruePlaceholder.confidence == EcoProfileConfidence::MEASURED);
  ASSERT_TRUE(confidenceMeasuredConsistent(sensorTruePlaceholder.measured, sensorTruePlaceholder.confidence));

  return 0;
}
