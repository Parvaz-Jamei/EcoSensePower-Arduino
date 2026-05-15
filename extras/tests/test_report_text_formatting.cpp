#include "test_support.h"
#include <core/EcoTypes.h>
#include <string.h>

int main() {
  EcoReport report;
  report.sensorName = "soil";
  report.value = 12.3456f;
  report.previousValue = -1.234f;
  report.intervalMs = 300000UL;
  report.readOk = true;
  report.firstRead = true;
  report.importantChange = true;
  report.estimatedDailyEnergy_mJ = 98.765f;
  report.batchSampleCount = 3;
  report.boardConfidence = EcoProfileConfidence::PLACEHOLDER;
  report.batteryConfidence = EcoProfileConfidence::DATASHEET;
  report.includesRegulatorIq = false;
  report.includesSensorLeakage = true;

  const char* text = report.toText();
  ASSERT_TRUE(strstr(text, "sensor=soil") != 0);
  ASSERT_TRUE(strstr(text, "value=12.346") != 0);
  ASSERT_TRUE(strstr(text, "previous=-1.234") != 0);
  ASSERT_TRUE(strstr(text, "estDaily=98.77") != 0);
  ASSERT_TRUE(strstr(text, "profile=PLACEHOLDER/DATASHEET") != 0);
  ASSERT_TRUE(strstr(text, "%f") == 0);
  ASSERT_TRUE(strstr(text, "%g") == 0);
  ASSERT_TRUE(strstr(text, "?") == 0);

  char formatted[16];
  ecoFormatFloatFixed(formatted, sizeof(formatted), -0.125f, 3);
  ASSERT_TRUE(strstr(formatted, "-0.125") != 0);
  ecoFormatFloatFixed(formatted, sizeof(formatted), 1.995f, 2);
  ASSERT_TRUE(strstr(formatted, "2.00") != 0);

  return 0;
}
