#include "test_support.h"
#include <EcoSensePower.h>
int main() {
  EnergyContract c;
  c.minIntervalMs = EcoTime::seconds(10);
  c.maxIntervalMs = EcoTime::seconds(5);
  c.currentIntervalMs = 0;
  c.changeThreshold = -1.0f;
  const bool ok = c.validate();
  ASSERT_TRUE(!ok);
  ASSERT_EQ(c.maxIntervalMs, c.minIntervalMs);
  ASSERT_EQ(c.currentIntervalMs, c.minIntervalMs);
  ASSERT_TRUE(c.changeThreshold == 0.0f);
  return 0;
}
