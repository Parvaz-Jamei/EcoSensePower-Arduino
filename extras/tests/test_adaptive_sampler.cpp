#include "test_support.h"
#include <EcoSensePower.h>
int main() {
  EnergyContract c;
  c.minIntervalMs = EcoTime::seconds(10);
  c.maxIntervalMs = EcoTime::minutes(1);
  c.currentIntervalMs = EcoTime::seconds(20);
  c.changeThreshold = 5.0f;
  AdaptiveSampler sampler;
  sampler.setAdditiveStepMs(EcoTime::seconds(5));
  bool important = false;
  sampler.update(c, 100.0f, 101.0f, true, &important);
  ASSERT_TRUE(!important);
  ASSERT_EQ(c.currentIntervalMs, EcoTime::seconds(25));
  sampler.update(c, 101.0f, 130.0f, true, &important);
  ASSERT_TRUE(important);
  ASSERT_TRUE(c.currentIntervalMs >= c.minIntervalMs);
  ASSERT_TRUE(c.currentIntervalMs < EcoTime::seconds(25));
  return 0;
}
