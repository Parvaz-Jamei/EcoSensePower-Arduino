#include "test_support.h"
#define ECOSENSE_ENABLE_BLUETOOTH_PROFILE_CATALOG 1
#define ECOSENSE_ENABLE_GPS_PROFILE_CATALOG 1
#include "EcoSensePowerBluetoothProfiles.h"
#include "EcoSensePowerGPSProfiles.h"

int main() {
  ASSERT_TRUE(EcoProfiles::BluetoothBLEGeneric().confidence() == EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(EcoProfiles::HM10BLEMeasured() == false);
  ASSERT_TRUE(EcoProfiles::GNSSGeneric().confidence == EcoProfileConfidence::PLACEHOLDER);
  ASSERT_TRUE(EcoProfiles::UBloxNEO6MMeasured() == false);
  return 0;
}
