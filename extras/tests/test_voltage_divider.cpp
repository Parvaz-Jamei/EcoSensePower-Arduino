#include "test_support.h"
#include <EcoSensePower.h>
int main() {
  VoltageDivider divider(A1, 1000.0f, 330.0f, 3.3f, 1023U);
  float full = divider.scaleRaw(1023U);
  ASSERT_TRUE(full > 13.0f && full < 13.4f);
  float half = divider.scaleRaw(512U);
  ASSERT_TRUE(half > 6.5f && half < 6.8f);
  ASSERT_TRUE(divider.dividerCurrent_uA(12.0f) > 8.0f);
  return 0;
}
