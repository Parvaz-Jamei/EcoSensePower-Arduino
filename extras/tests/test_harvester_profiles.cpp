#include "test_support.h"
#include <EcoSensePower.h>

int main() {
  SolarHarvester solar;
  ASSERT_TRUE(!solar.available());
  ASSERT_TRUE(solar.confidence() == EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(solar.storageEfficiencyPercent() > 0.0f);
  ASSERT_TRUE(solar.notes() != 0 && solar.notes()[0] != '\0');
  solar.fixedMilliWatt(10.0f).storageEfficiencyPercent(120.0f);
  ASSERT_TRUE(solar.available());
  ASSERT_TRUE(solar.inputPowerMilliWatt() > 9.0f);
  ASSERT_TRUE(solar.storageEfficiencyPercent() == 100.0f);
  solar.storageEfficiencyPercent(-5.0f);
  ASSERT_TRUE(solar.storageEfficiencyPercent() == 0.0f);
  solar.fixedMilliWatt(-1.0f);
  ASSERT_TRUE(solar.inputPowerMilliWatt() == 0.0f);

  PiezoHarvester piezo;
  ASSERT_TRUE(!piezo.available());
  ASSERT_TRUE(piezo.confidence() == EcoProfileConfidence::PLACEHOLDER);
  piezo.fixedMilliWatt(1.5f).storageEfficiencyPercent(50.0f);
  ASSERT_TRUE(piezo.available());
  ASSERT_TRUE(piezo.inputPowerMilliWatt() > 1.0f);
  ASSERT_TRUE(piezo.notes() != 0 && piezo.notes()[0] != '\0');

  ThermoelectricHarvester teg;
  teg.fixedMilliWatt(2.0f);
  ASSERT_TRUE(teg.available());
  ASSERT_TRUE(teg.confidence() == EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(teg.notes() != 0 && teg.notes()[0] != '\0');

  WindHarvester wind;
  wind.fixedMilliWatt(3.0f).confidence(EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(wind.inputPowerMilliWatt() > 2.0f);
  ASSERT_TRUE(wind.confidence() == EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(wind.notes() != 0 && wind.notes()[0] != '\0');
  return 0;
}
