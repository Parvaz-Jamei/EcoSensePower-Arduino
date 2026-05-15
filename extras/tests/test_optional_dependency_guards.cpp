#include "test_support.h"
#define ECOSENSE_PRESET_AVR_TINY 1
#include "EcoSensePower.h"
#include "integrations/optional/ArduinoBLEEnergyAdapter.h"
#include "integrations/optional/TinyGPSPlusEnergyAdapter.h"
#include "integrations/optional/AdafruitGPSEnergyAdapter.h"

int main() {
  ASSERT_TRUE(ECOSENSE_ENABLE_PROFILE_CATALOG == 0);
  ASSERT_TRUE(ECOSENSE_ENABLE_BLUETOOTH_PROFILE_CATALOG == 0);
  ASSERT_TRUE(ECOSENSE_ENABLE_GPS_PROFILE_CATALOG == 0);
  ASSERT_TRUE(ECOSENSE_ENABLE_ARDUINO_BLE_ADAPTER == 0);
  ASSERT_TRUE(ECOSENSE_ENABLE_TINYGPSPLUS_ADAPTER == 0);
  ASSERT_TRUE(ECOSENSE_ENABLE_ADAFRUIT_GPS_ADAPTER == 0);
  ArduinoBLEEnergyAdapter ble;
  ASSERT_TRUE(ble.confidence() == EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(TinyGPSPlusEnergyAdapter::placeholderProfile().confidence == EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(AdafruitGPSEnergyAdapter::placeholderProfile().confidence == EcoProfileConfidence::PLACEHOLDER);
  return 0;
}
