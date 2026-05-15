#include "test_support.h"
#include <EcoSensePower.h>
static float readValue() { return 42.0f; }
int main() {
  EcoSensePower node;
  node.sensor("soil").read(readValue).minIntervalMs(EcoTime::seconds(1)).maxIntervalMs(EcoTime::seconds(2));
  node.begin();
  const uint8_t count = node.diagnosticCount();
  ASSERT_TRUE(count > 0);
  bool foundBackend = false;
  bool foundProfile = false;
  bool foundMeasurement = false;
  bool foundBoardPlaceholder = false;
  uint8_t genericBoardCount = 0;
  for (uint8_t i = 0; i < count; ++i) {
    EcoDiagnostic d = node.diagnosticAt(i);
    if (d.code == EcoDiagnosticCode::REAL_SLEEP_BACKEND_MISSING) foundBackend = true;
    if (d.code == EcoDiagnosticCode::GENERIC_BOARD_PROFILE) { foundProfile = true; ++genericBoardCount; }
    if (d.code == EcoDiagnosticCode::BOARD_PROFILE_PLACEHOLDER) foundBoardPlaceholder = true;
    if (d.code == EcoDiagnosticCode::NO_HARDWARE_MEASUREMENT) foundMeasurement = true;
  }
  ASSERT_TRUE(foundBackend);
  ASSERT_TRUE(foundProfile);
  ASSERT_TRUE(foundMeasurement);
  ASSERT_TRUE(foundBoardPlaceholder);
  ASSERT_EQ(genericBoardCount, 1);
  return 0;
}
