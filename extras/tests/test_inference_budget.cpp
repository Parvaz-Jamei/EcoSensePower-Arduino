#include "test_support.h"
#include <EcoSensePower.h>
int main() {
  InferenceBudget b;
  b.current_uA(8500).durationMs(40).maxRunsPerDay(2);
  ASSERT_TRUE(b.hasBudget());
  ASSERT_TRUE(b.canRun(0));
  ASSERT_TRUE(b.canRun(1));
  ASSERT_TRUE(!b.canRun(2));
  ASSERT_TRUE(b.limitReached(2));
  ASSERT_TRUE(b.energyPerInference_mJ(3.3f) > 0.0f);
  return 0;
}
